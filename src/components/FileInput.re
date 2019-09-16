open Relude.Globals;
open Webapi;

type transform('a) =
  | String: transform(string)
  | File: transform(File.t)
  | Image: transform(Blob.t)
  | JSON: transform(Js.Json.t)
  | CSV: transform(list(list(string)));

let jsonParseAsIO: string => IO.t(Js.Json.t, string) =
  str =>
    IO.tries(() => Js.Json.parseExn(str))
    |> IO.mapError(_ => "Failed to parse JSON");

let csvParseAsIO: string => IO.t(list(list(string)), string) =
  str =>
    IO.fromResult(ReludeCsv.parse(str))
    |> IO.mapError(_ => "Failed to parse CSV");

let parseTextFile = (file, parse) =>
  Blob.readFileAsText(file)
  |> RJs.Promise.toIO
  |> IO.mapError(_ => "Failed to read file")
  |> IO.flatMap(parse)
  |> IO.map(FileData.fromFile(file));

let transformFile:
  type output.
    (File.t, transform(output)) => IO.t(FileData.t(output), string) =
  file =>
    fun
    | String => parseTextFile(file, v => IO.pure(v))
    | File => FileData.fromFile(file, file) |> IO.pure
    | Image => Blob.fromFile(file) |> FileData.fromFile(file) |> IO.pure
    | JSON => parseTextFile(file, jsonParseAsIO)
    | CSV => parseTextFile(file, csvParseAsIO);

[@bs.deriving abstract]
type props('a) = {
  label: string,
  transform: transform('a),
  onChange: option(FileData.t('a)) => unit,
};

[@bs.obj]
external makeProps:
  (
    ~label: string,
    ~transform: transform('a),
    ~onChange: option(FileData.t('a)) => unit,
    unit
  ) =>
  props('a) =
  "";

let make: type a. props(a) => React.element =
  props => {
    let label = labelGet(props);
    let transform = transformGet(props);
    let onChange = onChangeGet(props);

    let triggerChangeFromFiles = files =>
      Array.head(files)
      |> IO.fromOption(_ => "No file selected")
      |> IO.flatMap(transformFile(_, transform))
      |> IO.unsafeRunAsync(
           fun
           | Belt.Result.Error(_err) => onChange(None)
           | Belt.Result.Ok(content) => onChange(Some(content)),
         );

    let onChange = evt => {
      let files: array(File.t) = ReactEvent.Form.target(evt)##files;
      triggerChangeFromFiles(files);
    };

    let onDrop = evt => {
      Js.log("On drop, looking for files");
      ReactEvent.Mouse.stopPropagation(evt);
      ReactEvent.Mouse.preventDefault(evt);
      let files: array(File.t) = DropEvent.filesFromMouseEvent(evt);
      triggerChangeFromFiles(files);
    };

    let accept =
      switch (transform) {
      | String => "*"
      | File => "*"
      | Image => "image/*"
      | JSON => ".json"
      | CSV => ".csv"
      };

    <label className="file-picker" onDrop>
      <span> {React.string(label)} </span>
      <input type_="file" onChange accept />
    </label>;
  };
