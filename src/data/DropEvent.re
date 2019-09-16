module DataTransfer = {
  type t;
  [@bs.get] external files: t => array(Webapi.File.t) = "files";
};

type t;
external unsafeFromMouseEvent: ReactEvent.Mouse.t => t = "%identity";
[@bs.get] external dataTransfer: t => DataTransfer.t = "dataTransfer";

let filesFromMouseEvent: ReactEvent.Mouse.t => array(Webapi.File.t) =
  evt => unsafeFromMouseEvent(evt) |> dataTransfer |> DataTransfer.files;
