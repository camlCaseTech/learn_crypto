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

let toHex = (str: string, spaceSeparatedPairs: bool) => {
  let space = if (spaceSeparatedPairs) {" "} else {""};
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

let int_of_hex_string = (str: string) =>
  switch (int_of_string_opt(Js.String.get(str, 0))) {
  | Some(i) => i
  | None =>
    switch (str) {
    | "a" => 10
    | "b" => 11
    | "c" => 12
    | "d" => 13
    | "e" => 14
    | "f" => 15
    | _ => 0
    }
  };

let fromHex = (codes: array(string)) =>
  Js.String.concatMany(
    Array.map(
      (code: string) =>
        if (Js.String.length(code) == 2) {
          let asciiCode =
            Array.fold_left(
              (a, b) => a + b,
              0,
              mapiString(
                (i: int, c: string) =>
                  int_of_hex_string(c) * int_pow(16, i),
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

let asciiToAlphabetOrder = (char: string) => {
  let sUpper = Js.String.toUpperCase(char);
  int_of_float(Js.String.charCodeAt(0, sUpper)) - 65;
};

/*
 let alphabetOrderToAscii = (code: int) => {
   let sUpper = Js.String.toUpperCase(char);
   int_of_float(Js.String.charCodeAt(0, sUpper)) - 65;
 };
 */

/* the key should be a non-empty list of  */
let encodeVignereCipherSafe = (str: string, key: array(int)) => {
  /* A is 0, B is 1, ... Z is 25 */
  let keyLength = Array.length(key);
  Js.String.concatMany(
    mapiString(
      (i, s) =>
        if (s == " ") {
          " ";
        } else {
          let k = key[i mod keyLength];
          encodeCaesarCipher(s, k);
        },
      str,
    ),
    "",
  );
};

/* make this safer */
let encodeVignereCipher = (str: string, key: string) => {
  let keyIntArray =
    arrayCatSomes(
      mapString(
        k => {
          let code = asciiToAlphabetOrder(k);
          if (code >= 0 || code < 25) {
            Some(code);
          } else {
            None;
          };
        },
        key,
      ),
    );

  encodeVignereCipherSafe(str, keyIntArray);
};

let decodeVignereCipherSafe = (str: string, key: array(int)) => {
  let keyLength = Array.length(key);
  Js.String.concatMany(
    mapiString(
      (i, s) =>
        if (s == " ") {
          " ";
        } else {
          let k = key[i mod keyLength];
          let code = Js.String2.charCodeAt(s, 0) |> int_of_float;
          decodeCaesarCipher([|code|], k);
        },
      str,
    ),
    "",
  );
};

let decodeVignereCipher = (str: string, key: string) => {
  let keyIntArray =
    arrayCatSomes(
      mapString(
        k => {
          let code = asciiToAlphabetOrder(k);
          if (code >= 0 || code < 25) {
            Some(code);
          } else {
            None;
          };
        },
        key,
      ),
    );

  decodeVignereCipherSafe(str, keyIntArray);
};

let encodeMD5: string => string = [%bs.raw
  {|
   function (message) {
     var CryptoJS = require("crypto-js");
     return CryptoJS.MD5(message).toString(CryptoJS.enc.Hex);
   }
   |}
];

let encodeSHA256: string => string = [%bs.raw
  {|
   function (message) {
     var CryptoJS = require("crypto-js");
     return CryptoJS.SHA256(message).toString(CryptoJS.enc.Hex);
   }
   |}
];

let encodeSHA3: string => string = [%bs.raw
  {|
   function (message) {
     var CryptoJS = require("crypto-js");
     return CryptoJS.SHA3(message).toString(CryptoJS.enc.Hex);
   }
   |}
];