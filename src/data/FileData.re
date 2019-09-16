type t('a) = {
  name: string,
  size: float,
  data: 'a,
};

let make = (name, size, data) => {name, size, data};

let fromFile = (file, data) =>
  Webapi.File.(make(name(file), size(file), data));
