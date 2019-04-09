open Utils;

type state = {
  input: string,
  offset: string,
};

let initialState = () => {input: "", offset: "0"};

type action =
  | UpdateText(string)
  | UpdateOffset(string);

let reducer = (action, state) =>
  switch (action) {
  | UpdateText(input) => ReasonReact.Update({...state, input})
  | UpdateOffset(offset) => ReasonReact.Update({...state, offset})
  };

let component = ReasonReact.reducerComponent("CaesarCipherEncoder");

open BsReactstrap;

let make = (_children) => {
  ...component,
  initialState,
  reducer,
  render: self =>
    <Row>
      <Col>
        <h2> (ReasonReact.string("Caesar Cipher Encoder")) </h2>
        <Form>
          <FormGroup>
            <Label for_="encoder-input"> "Normal Input" </Label>
            <Input
              type_="text"
              name="encoder-input"
              id="encoder-input"
              placeholder="Insert some text"
              value=self.state.input
              onChange=(e => self.send(UpdateText(getTargetString(e))))
            />
          </FormGroup>
          <FormGroup>
            <Label for_="encoder-input"> "Offset" </Label>
            <Input
              type_="text"
              name="encoder-input"
              id="encoder-input"
              value=self.state.offset
              onChange=(e => self.send(UpdateOffset(getTargetString(e))))
              
            />
          </FormGroup>
          <FormGroup>
            <Label for_="encoder-output"> "Caesar Cipher Encoder Output" </Label>
            <Input
              type_="text"
              name="encoder-output"
              id="encoder-output"
              value=(
              switch (int_of_string_opt(self.state.offset)) {
              | Some(offset) => Cryptography.encodeCaesarCipher(self.state.input, offset)
              | None => ""
              }
              )
              readOnly=true
            />
          </FormGroup>
        </Form>
      </Col>
    </Row>,
};