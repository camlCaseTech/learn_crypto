open Utils;

type state = {
  input: string,
  b: bool,
};

let initialState = () => {input: "", b: true};

type action =
  | UpdateText(string);

let reducer = (action, state) =>
  switch (action) {
  | UpdateText(input) => ReasonReact.Update({...state, input})
  };

let component = ReasonReact.reducerComponent("Encoder");

open BsReactstrap;

let make =
    (
      ~encodeType: string,
      ~encoder: string => string,
      ~decoder: option(string => string)=None,
      _children,
    ) => {
  ...component,
  initialState,
  reducer,
  render: self =>
    <Row>
      <Col>
        <h2> (ReasonReact.string(encodeType)) </h2>
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
            <Label for_="encoder-output">
              (encodeType ++ " Encoded Output")
            </Label>
            <Input
              type_="text"
              name="encoder-output"
              id="encoder-output"
              value=(encoder(self.state.input))
              readOnly=true
            />
          </FormGroup>
          (
            switch (decoder) {
            | Some(decoder') =>
              let v = encoder(self.state.input);
              let d = decoder'(v);
              <FormGroup>
                <Label for_="decoder-output">
                  (encodeType ++ " Decoded Output")
                </Label>
                <Input
                  type_="text"
                  name="decoder-output"
                  id="decoder-output"
                  value=d
                  readOnly=true
                />
              </FormGroup>;
            | None => ReasonReact.null
            }
          )
        </Form>
      </Col>
    </Row>,
};