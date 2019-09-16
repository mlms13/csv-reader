# CSV File Input Reader

Allow users to choose local CSV files, which are parsed and displayed in a table. This demonstrates the basics of file picking and parsing. In this case [Relude CSV](https://github.com/reazen/relude-csv) is used to parse the text.

## Run It

```sh
# install dependencies
npm install

# compile, bundle, and run a dev server
# then open localhost:1234 in your browser
# click inside the dotted line to open the file picker
# and choose any valid CSV
npm run dev
```

## TODO

Using an `<input type="file" />` is working well, and the files' string contents can be read when the `onChange` event is triggered, however...

- I can't seem to get dropping files from the desktop to work. It just redirects the page, and no amount of `preventDefault` or `stopPropagation` has fixed this.
- The demo uses CSVs, and I've logged JSON files to make sure that flow is working. I haven't tested binary files like images or any other types.
- We set a file mask to encourage the right extension, but if you pick the wrong thing, it will fail the parse and we pretend you picked nothing.
