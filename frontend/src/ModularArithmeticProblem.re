type problem = {
  text: string,
  answer: int,
};

let createEasyModuloProblem = () : problem => {
  Random.self_init();
  let numerator = Random.int(100) + 1;
  let denominator =
    switch (Random.int(3)) {
    | 0 => 2
    | 1 => 5
    | _ => 10
    };
  let text =
    string_of_int(numerator) ++ " mod " ++ string_of_int(denominator);
  let answer = numerator mod denominator;
  {text, answer};
};

let createNormalModuloProblem = () : problem => {
  Random.self_init();
  let numerator = Random.int(100) + 1;
  let denominator =
    switch (Random.int(12)) {
    | 11 => 60
    | 10 => 12
    | x => x + 1
    };
  let text =
    string_of_int(numerator) ++ " mod " ++ string_of_int(denominator);
  let answer = numerator mod denominator;
  {text, answer};
};

/* large number */
let createChallengingModuloProblem = () => {
  Random.self_init();
  let d = Random.int(3);
  let denominator =
    switch (d) {
    | 0 => 2
    | 1 => 5
    | _ => 10
    };
  let numerator = Random.int(100) + 1;
  let a = numerator mod denominator;
  let s = string_of_int(numerator) ++ " mod " ++ string_of_int(denominator);
  (a, s);
};

type level =
  | Easy
  | Normal
  | Hard;

type state = {
  level,
  problem,
  userAnswer: string,
};

let initialState = () => {
  level: Easy,
  problem: {
    text: "9 mod 7",
    answer: 2,
  },
  userAnswer: "",
};

type action =
  | UpdateLevel(level);

let reducer = (action, state) =>
  switch (action) {
  | UpdateLevel(level) => ReasonReact.Update({...state, level})
  };

let component = ReasonReact.reducerComponent("ModularArithmeticProblem");

open BsReactstrap;

let make = _children => {
  ...component,
  initialState,
  reducer,
  render: self =>
    <Row>
      <Row>
        <FormGroup>
          <Label for_="answer"> (self.state.problem.text ++ " ") </Label>
          <Input
            type_="text"
            name="answer"
            id="answer"
            value=self.state.userAnswer
            onChange=(_ => ())
          />
        </FormGroup>
      </Row>
      <br />
      <Row>
        <ButtonGroup size="sm">
          <Button onClick=(_ => self.send(UpdateLevel(Easy)))>
            "Easy"
          </Button>
          <Button onClick=(_ => self.send(UpdateLevel(Normal)))>
            "Normal"
          </Button>
          <Button onClick=(_ => self.send(UpdateLevel(Hard)))>
            "Hard"
          </Button>
        </ButtonGroup>
      </Row>
    </Row>,
};