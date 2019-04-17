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

let int_of_string_opt = x =>
  try (Some(int_of_string(x))) {
  | Failure(_) => None
  };

let leftPad = (word: string, num: int, pad_char: string) =>
  String.length(word) < num ?
    {
      let number_to_fill = num - String.length(word);
      let padding = String.make(number_to_fill, pad_char.[0]);
      padding ++ word;
    } :
    word;

let catSomes = (type a, mas: list(option(a))) : list(a) =>
  List.fold_left(
    (acc, x) =>
      switch (x) {
      | None => acc
      | Some(a) => List.append(acc, [a])
      },
    [],
    mas,
  );

let arrayCatSomes = (type a, mas: array(option(a))) : array(a) =>
  Array.fold_left(
    (acc, x) =>
      switch (x) {
      | None => acc
      | Some(a) => Array.append(acc, [|a|])
      },
    [||],
    mas,
  );

/* map over each char of string, but keep the type as string */

let mapString = (f: string => 'a, str: string) =>
  Array.map(s => f(s), Js.String.split("", str));

let mapiString = (f: (int, string) => 'a, str: string) =>
  Array.mapi((i, s) => f(i, s), Js.String.split("", str));

let getTargetString = (event: ReactEventRe.Form.t) : string => ReactDOMRe.domElementToObj(
                                                                  ReactEventRe.Form.target(
                                                                    event,
                                                                  ),
                                                                )##value;

/* generic pow function */
let pow = (one, mul, a, n) => {
  let rec g = (p, x) =>
    fun
    | 0 => x
    | i =>
      g(
        mul(p, p),
        if (i mod 2 == 1) {
          mul(p, x);
        } else {
          x;
        },
        i / 2,
      );

  g(a, one, n);
};

let int_pow = pow(1, ( * ));

let float_pow = pow(1.0, ( *. ));

let string_rev = s => {
  let len = String.length(s);
  String.init(len, i => s.[len - 1 - i]);
};

let int_of_string_opt = x =>
  try (Some(int_of_string(x))) {
  | Failure(_) => None
  };