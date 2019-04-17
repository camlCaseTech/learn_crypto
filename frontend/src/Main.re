let component = ReasonReact.statelessComponent("Main");

open BsReactstrap;
let make = _children => {
  ...component,
  render: _self =>
    <Container>
      <Encoder
        encodeType="Ascii"
        encoder=(x => Cryptography.toAscii(x, true))
      />
      <Encoder
        encodeType="Binary"
        encoder=(x => Cryptography.toBinary(x, true))
        decoder=(
          Some(x => Cryptography.fromBinary(Js.String.split(" ", x)))
        )
      />
      <Encoder
        encodeType="Hex"
        encoder=(x => Cryptography.toHex(x, true))
        decoder=(Some(x => Cryptography.fromHex(Js.String.split(" ", x))))
      />
      <CaesarCipherEncoder />
      <VignereCipherEncoder />
      <ModularArithmeticProblem />
      <BarChart id="bar_chart" />
    </Container>,
};

let readObject: Js.Dict.t(float) => unit = [%bs.raw
  {|
    function(d) {
      console.log("read object");
      console.log(d)
    }
  |}
];

readObject(
  Js.Dict.fromArray(Belt.Map.String.toArray(Cryptography.englishFreq)),
);

let s = "hey what is up";
let (encoded, oneTimepad) = Cryptography.encodeXOR(s);
let decoded = Cryptography.decodeXOR(encoded, oneTimepad);
Js.Console.log(s);
Js.Console.log(encoded);
Js.Console.log(oneTimepad);
Js.Console.log(decoded);