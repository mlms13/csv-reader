# CSV File Input Reader

Allow users to choose local CSV files, which are parsed and displayed in a table. This demonstrates the basics of file picking and parsing. In this case [Relude CSV](https://github.com/reazen/relude-csv) is used to parse the text.

## What This Is

This is not a useful application (it just displays CSV files in an HTML table) and this is not a library, ready to be installed in your project (though there definitely may be some ideas worth copy-and-pasting). Instead, this is:

- An exploration using a GADT to drive the parsing and UI file mask for a React file picker
- An example of binding to the browser's [Blob](https://github.com/mlms13/csv-reader/blob/master/src/data/Blob.re) and [Drop Event](https://github.com/mlms13/csv-reader/blob/master/src/data/DropEvent.re) APIs... arguably this should be upstreamed to [reason-react](https://github.com/reasonml/reason-react/) and [bs-webapi-incubator](https://github.com/mlms13/csv-reader/blob/master/src/components/FileInput.re).
- A demonstration of the [Relude CSV](https://github.com/mlms13/csv-reader/blob/master/src/data/DropEvent.re) string parser library
- A playground for exploring bundling and dead-code-elimination within the Relude ecosystem

If you're building a Reason React UI that needs to support file pickers, maybe something in here will be worth stealing. :)

## How It Works

Ultimately, the [File Input](https://github.com/mlms13/csv-reader/blob/master/src/components/FileInput.re) component is just a wrapper around `<input type="file" />`. The component expects to be constructed with a `transform` prop of type:

```reason
type transform('a) =
  | String: transform(string)
  | File: transform(File.t)
  | Image: transform(Blob.t)
  | JSON: transform(Js.Json.t)
  | CSV: transform(list(list(string)));
```

The `onChange` function you pass the the component will be called with a string if you used `transform=String`; it will be called with JSON if you passed `transform=JSON`, etc.

## Limitations

- When an invalid file is picked, the component doesn't show an error, it simply passes `None` as the `onChange` value to its parent, which doesn't differentiate "you picked an invalid file" from "you picked no files." This could easily be fixed by passing a `result` to the parent instead of an `option` (and by using typed errors instead of strings).
- This project tests CSVs, and I've tried JSON enough to confirm that it seems to work, but everything else is basically untested.

## Run It

```sh
# install dependencies
npm install

# compile, bundle, and run a dev server
# then open localhost:1234 in your browser
# click inside the dotted line to open the file picker
# and choose any valid CSV, or drop one in the box
npm run dev
```
