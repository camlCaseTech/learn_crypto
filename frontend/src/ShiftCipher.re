/*
 let asciiCode = (textCode: string, offset: int) =>
   if (textCode == "") {
     None;
   } else {
     let textUpper = Js.String2.toUpperCase(textCode);
     Some(
       String.mapi(
         (i: int, _c: char) => {
           let code = int_of_float(Js.String2.charCodeAt(textCode, i));
           if (code >= 65 && code <= 90) {
             let asciiOffset = (code + offset + 13) mod 26;
             Js.String2.fromCharCode(asciiOffset + 65).[0];
           } else {
             Js.String2.fromCharCode(32).[0];
           };
         },
         textUpper,
       ),
     );
   };
 */

/* map over each char of string, but keep the type as string */
let mapString = (f: string => 'a, str: string) =>
  Array.map(s => f(s), Js.String.split("", str));

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

let string_of_chars = chars => {
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
/*
 let toBinary = (str: string, spaceSeparatedOctets: bool) => {
   let space = if (spaceSeparatedOctets) {" "} else {""};
   /* Js.String2.charCodeAt */
   Belt_MapString.map(str, s => s);
 };
 */

let charToString = char => String.make(1, char);

let leftPad = (word: string, num: int, pad_char: string) =>
  String.length(word) < num ?
    {
      let number_to_fill = num - String.length(word);
      let padding = String.make(number_to_fill, pad_char.[0]);
      padding ++ word;
    } :
    word;

let toBinary = (str: string, spaceSeparatedOctets: bool) => {
  let space = if (spaceSeparatedOctets) {" "} else {""};
  let output = ref("");
  let i = ref(0);
  let length = Js.String.length(str);
  /* Generally it would be better to use a mapping function
   * but Js.String2.charCodeAt requires an index and there
   * is not a map (char -> string) function.
   */
  while (i^ < length) {
    let binaryByteAsString =
      leftPad(
        Js.Int.toStringWithRadix(
          int_of_float(Js.String2.charCodeAt(charToString(str.[i^]), 0)),
          ~radix=2,
        ),
        8,
        "0",
      )
      ++ space;
    i := i^ + 1;
    output := output^ ++ binaryByteAsString;
  };
  output^;
};

/*
         if (textUpper.charCodeAt(i) >= 65 && textUpper.charCodeAt(i) <= 90) {
           var asciiOffset = (parseInt(textUpper.charCodeAt(i)) + parseInt(offset) + 13) % 26;
           var codeStr = String.fromCharCode(asciiOffset + 65);
           $scope.codeArray.push(codeStr);
         } else {
           $scope.codeArray.push(String.fromCharCode(32));
         }
 */
let encodeCaesarCipher = (str: string, offset: int) =>
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
  );

/*
 let toBinary = (str: string, spaceSeparatedOctets: bool) => {
   let space = if (spaceSeparatedOctets) {" "} else {""};
   /* Js.String2.charCodeAt */
   String.mapi(
     (i: int, _c: char) => {
       /* binary += str[i].charCodeAt(0).toString(2) + space; */
       Js.Int.toStringWithRadix(int_of_float(Js.String2.charCodeAt(str, i)), ~radix: 2)[0] },
       /* ++ space, */
     str,
   )
 }
 */
/*
 let fromBase = (base: int, digits: list(int)) : option(int) => {
   let toDecimal = (acc: option(int), digit: int) : option(int) =>
     switch (acc) {
     | None => None
     | Some(n) => digit >= 0 && digit < base ? Some(n * base + digit) : None
     };

   List.fold_left(toDecimal, Some(0), digits);
 };

 let rec toBase = (base: int, input: int) : list(int) =>
   input < base ? [input] : toBase(base, input / base) @ [input mod base];

 let rebase =
     (inBase: int, digits: list(int), outBase: int)
     : option(list(int)) => {
   let length = List.length(digits);
   let numZeros = digits |> List.filter(digit => digit == 0) |> List.length;

   if (inBase <= 0 || outBase <= 0 || length == numZeros) {
     None;
   } else {
     switch (fromBase(inBase, digits)) {
     | Some(n) => Some(toBase(outBase, n))
     | _ => None
     };
   };
 };
 */
/*
   let toBinary = (str, spaceSeparatedOctets) => {
     let binary = [];
     let space;
     if (spaceSeparatedOctets) {
       space = " ";
     } else {
       space = "";
     }
     for (let i = 0; i < str.length; i++) {
       binary += str[i].charCodeAt(0).toString(2) + space;
     }
     return binary;
   };
 */

/*
 let asciiCode = (textCode, offset) => {
     if (textCode === undefined) return;
     let codeArray = [];
     for (var i = 0; i < textCode.length; i++) {
       let textUpper = textCode.toUpperCase();
       if (textUpper.charCodeAt(i) >= 65 && textUpper.charCodeAt(i) <= 90) {
         let asciiOffset =
           (parseInt(textUpper.charCodeAt(i)) + parseInt(offset) + 13) % 26;
         let codeStr = String.fromCharCode(asciiOffset + 65);
         codeArray.push(codeStr);
       } else {
         codeArray.push(String.fromCharCode(32));
       }
     }
     return codeArray;
   };

   let toBinary = (str, spaceSeparatedOctets) => {
     let binary = [];
     let space;
     if (spaceSeparatedOctets) {
       space = " ";
     } else {
       space = "";
     }
     for (let i = 0; i < str.length; i++) {
       binary += str[i].charCodeAt(0).toString(2) + space;
     }
     return binary;
   };

   let zeroPad = num => {
     return "00000000".slice(String(num).length) + num;
   };


   let toBinary = (str, spaceSeparatedOctets) => {
     let binary = [];
     return str.replace(/[\s\S]/g, function(str) {
       str = zeroPad(str.charCodeAt().toString(2));
       return !1 === spaceSeparatedOctets
         ? binary.push(str)
         : binary.push(str + " ");
     });
   };


   let toAscii = function(bin) {
     return bin.replace(, function(bin) {
       return String.fromCharCode((parseInt(bin, 2) % 26) + 65);
     });
   };
   */