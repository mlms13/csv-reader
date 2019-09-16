open Relude.Globals;

[@react.component]
let make = (~data: list(list(string))) => {
  let columns =
    List.map(col => <td> {React.string(col)} </td>) >> List.toArray;

  let children =
    List.map(row => <tr> {React.array(columns(row))} </tr>, data)
    |> List.toArray;

  <table> {React.array(children)} </table>;
};
