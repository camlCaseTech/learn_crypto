open Utils;

type state = {
  input: string,
  key: string,
};

let initialState = () => {input: "", key: ""};

type action =
  | UpdateText(string)
  | UpdateKey(string);

let reducer = (action, state) =>
  switch (action) {
  | UpdateText(input) => ReasonReact.Update({...state, input})
  | UpdateKey(key) => ReasonReact.Update({...state, key})
  };

let component = ReasonReact.reducerComponent("VignereCipherEncoder");

open BsReactstrap;

let make = _children => {
  ...component,
  initialState,
  reducer,
  render: self =>
    <Row>
      <Col>
        <h2> (ReasonReact.string("Vignere Cipher Encoder")) </h2>
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
            <Label for_="encoder-input"> "Key" </Label>
            <Input
              type_="text"
              name="encoder-input"
              id="encoder-input"
              value=self.state.key
              onChange=(e => self.send(UpdateKey(getTargetString(e))))
            />
          </FormGroup>
          <FormGroup>
            <Label for_="encoder-output">
              "Vigenere Cipher Encoder Output"
            </Label>
            <Input
              type_="text"
              name="encoder-output"
              id="encoder-output"
              value=(
                Cryptography.encodeVignereCipher(
                  self.state.input,
                  self.state.key,
                )
              )
              readOnly=true
            />
          </FormGroup>
          <FormGroup>
            <Label for_="encoder-output">
              "Vignere Cipher Decoder Output"
            </Label>
            <Input
              type_="text"
              name="encoder-output"
              id="encoder-output"
              value={
                      let encoded =
                        Cryptography.encodeVignereCipher(
                          self.state.input,
                          self.state.key,
                        );
                      Cryptography.decodeVignereCipher(
                        encoded,
                        self.state.key,
                      );
                    }
              readOnly=true
            />
          </FormGroup>
        </Form>
      </Col>
    </Row>,
};