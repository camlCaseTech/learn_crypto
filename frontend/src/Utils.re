let stringOfChars = chars => {
  let buf = Buffer.create(16);
  List.iter(Buffer.add_char(buf), chars);
  Buffer.contents(buf);
};

let explode = s => {
  let rec exp = (i, l) =>
    if (i < 0) {
      l;
    } else {
      exp(i - 1, [s.[i], ...l]);
    };
  exp(String.length(s) - 1, []);
};

let charToString = char => String.make(1, char);

let leftPad = (word: string, num: int, pad_char: string) =>
  String.length(word) < num ?
    {
      let number_to_fill = num - String.length(word);
      let padding = String.make(number_to_fill, pad_char.[0]);
      padding ++ word;
    } :
    word;

/* map over each char of string, but keep the type as string */

let mapString = (f: string => 'a, str: string) =>
  Array.map(s => f(s), Js.String.split("", str));