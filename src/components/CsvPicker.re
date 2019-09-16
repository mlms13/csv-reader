open Relude.Globals;

[@react.component]
let make = () => {
  let (file, setFile) = React.useState(() => None);

  switch (file) {
  | None =>
    <FileInput
      label="Please choose a CSV file"
      transform=FileInput.CSV
      onChange={const >> setFile}
    />
  | Some(FileData.{name, data, _}) =>
    <div> <h1> {React.string(name)} </h1> <CsvTable data /> </div>
  };
};
