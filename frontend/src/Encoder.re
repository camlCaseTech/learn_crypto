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

let make = (~encodeType: string, ~encoder: string => string, _children) => {
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
            <Label for_="encoder-output"> (encodeType ++ " Output") </Label>
            <Input
              type_="text"
              name="encoder-output"
              id="encoder-output"
              value=(encoder(self.state.input))
              readOnly=true
            />
          </FormGroup>
        </Form>
      </Col>
    </Row>,
};