open Relude.Globals;

module BlobLike = {
  type t;
  external fromString: string => t = "%identity";
  external fromFile: Webapi.File.t => t = "%identity";
  let fromJSON: Js.Json.t => t = Js.Json.stringify >> fromString;
};

type t;

[@bs.new] external make: array(BlobLike.t) => t = "Blob";
[@bs.send] external text: t => Js.Promise.t(string) = "text";

let fromString: string => t = BlobLike.fromString >> Array.pure >> make;
let fromStrings: array(string) => t = Array.map(BlobLike.fromString) >> make;
let fromFile: Webapi.File.t => t = BlobLike.fromFile >> Array.pure >> make;
let fromFiles: array(Webapi.File.t) => t =
  Array.map(BlobLike.fromFile) >> make;

let readFileAsText: Webapi.File.t => Js.Promise.t(string) = fromFile >> text;
