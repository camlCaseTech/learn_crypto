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