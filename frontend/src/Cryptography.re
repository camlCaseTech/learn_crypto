open Utils;

let toAscii = (str, withSpace) => {
  let space = if (withSpace) {" "} else {""};
  Js.String.concatMany(
    mapString(
      s =>
        Js.Int.toString(int_of_float(Js.String2.charCodeAt(s, 0))) ++ space,
      str,
    ),
    "",
  );
};

let toBinary = (str: string, spaceSeparatedOctets: bool) => {
  let space = if (spaceSeparatedOctets) {" "} else {""};
  Js.String.concatMany(
    mapString(
      s =>
        leftPad(
          Js.Int.toStringWithRadix(
            int_of_float(Js.String2.charCodeAt(s, 0)),
            ~radix=2,
          ),
          8,
          "0",
        )
        ++ space,
      str,
    ),
    "",
  );
};

let fromBinary = (codes: array(string)) =>
  Js.String.concatMany(
    Array.map(
      (code: string) =>
        if (Js.String.length(code) == 8) {
          let asciiCode =
            Array.fold_left(
              (a, b) => a + b,
              0,
              mapiString(
                (i: int, c: string) =>
                  if (int_of_string(c) == 1) {
                    int_pow(2, i);
                  } else {
                    0;
                  },
                string_rev(code),
              ),
            );
          Js.String.fromCharCode(asciiCode);
        } else {
          Js.String.fromCharCode(32);
        },
      codes,
    ),
    "",
  );

let toHex = (str: string, spaceSeparatedOctets: bool) => {
  let space = if (spaceSeparatedOctets) {" "} else {""};
  Js.String.concatMany(
    mapString(
      s =>
        leftPad(
          Js.Int.toStringWithRadix(
            int_of_float(Js.String2.charCodeAt(s, 0)),
            ~radix=16,
          ),
          2,
          "0",
        )
        ++ space,
      str,
    ),
    "",
  );
};

let encodeCaesarCipher = (str: string, offset: int) =>
  Js.String.concatMany(
    mapString(
      s => {
        let sUpper = Js.String.toUpperCase(s);
        let code = int_of_float(Js.String.charCodeAt(0, sUpper));
        if (code >= 65 && code <= 90) {
          let asciiOffset = (code + offset + 13) mod 26;
          Js.String.fromCharCode(asciiOffset + 65);
        } else {
          Js.String.fromCharCode(32);
        };
      },
      str,
    ),
    "",
  );

let decodeCaesarCipher = (codes: array(int), offset: int) =>
  Js.String.concatMany(
    Array.map(
      code =>
        if (code >= 65 && code <= 90) {
          let asciiOffset = (code - offset - 13) mod 26;
          Js.String.fromCharCode(asciiOffset + 65);
        } else {
          Js.String.fromCharCode(32);
        },
      codes,
    ),
    "",
  );
