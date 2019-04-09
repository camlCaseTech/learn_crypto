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

let component = ReasonReact.reducerComponent("Ascii");

open BsReactstrap;

let make = _children => {
  ...component,
  initialState,
  reducer,
  render: self =>
    <Container>
      <Row>
        <Col>
          <h2> (ReasonReact.string("Ascii")) </h2>
          <Form>
            <FormGroup>
              <Label for_="ascii-input"> "Normal Input" </Label>
              <Input
                type_="text"
                name="ascii-input"
                id="ascii-input"
                placeholder="Insert some text"
                value=self.state.input
                onChange=(e => self.send(UpdateText(getTargetString(e))))
              />
            </FormGroup>
            <FormGroup>
              <Label for_="ascii-output"> "Ascii Output" </Label>
              <Input
                type_="text"
                name="ascii-output"
                id="ascii-output"
                value=(Cryptography.toAscii(self.state.input, true))
                readOnly=true
              />
            </FormGroup>
          </Form>
        </Col>
      </Row>
    </Container>,
};