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
      <Encoder encodeType="Hex" encoder=(x => Cryptography.toHex(x, true)) />
      <CaesarCipherEncoder />
    </Container>,
};