open Utils;

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
  let text =
    string_of_int(numerator) ++ " mod " ++ string_of_int(denominator);
  let answer = numerator mod denominator;
  {text, answer};
};

type level =
  | Easy
  | Normal
  | Hard;

let createProblem = (level: level) =>
  switch (level) {
  | Easy => createEasyModuloProblem()
  | Normal => createNormalModuloProblem()
  | Hard => createChallengingModuloProblem()
  };

type state = {
  level,
  problem,
  userAnswer: string,
  answered: option(bool),
};

let initialState = () => {
  level: Easy,
  problem: createProblem(Easy),
  userAnswer: "",
  answered: None,
};

type action =
  | UpdateLevel(level)
  | UpdateUserAnswer(string)
  | CheckAnswer
  | NextQuestion;

let reducer = (action, state) =>
  switch (action) {
  | UpdateLevel(level) =>
    ReasonReact.Update({...state, level, problem: createProblem(level)})
  | UpdateUserAnswer(userAnswer) =>
    ReasonReact.Update({...state, userAnswer})
  | CheckAnswer =>
    ReasonReact.Update({
      ...state,
      answered:
        Some(
          int_of_string_opt(state.userAnswer) == Some(state.problem.answer),
        ),
    })
  | NextQuestion =>
    ReasonReact.Update({
      ...state,
      answered: None,
      problem: createProblem(state.level),
      userAnswer: "",
    })
  };

let component = ReasonReact.reducerComponent("ModularArithmeticProblem");

open BsReactstrap;

let make = _children => {
  ...component,
  initialState,
  reducer,
  render: self =>
    [|
      <Row>
        <Col md=2>
          <Label> (ReasonReact.string("Choose a difficulty:")) </Label>
        </Col>
        <Col>
          <ButtonGroup size="sm">
            <Button
              onClick=(_ => self.send(UpdateLevel(Easy)))
              active=(self.state.level == Easy)>
              "Easy"
            </Button>
            <Button
              onClick=(_ => self.send(UpdateLevel(Normal)))
              active=(self.state.level == Normal)>
              "Normal"
            </Button>
            <Button
              onClick=(_ => self.send(UpdateLevel(Hard)))
              active=(self.state.level == Hard)>
              "Hard"
            </Button>
          </ButtonGroup>
        </Col>
      </Row>,
      <Row>
        <Col>
          <FormGroup>
            <Label for_="answer"> (self.state.problem.text ++ " ") </Label>
            <Input
              type_="text"
              name="answer"
              id="answer"
              value=self.state.userAnswer
              onChange=(
                e => self.send(UpdateUserAnswer(getTargetString(e)))
              )
            />
          </FormGroup>
          <Button onClick=(_ => self.send(CheckAnswer))>
            "Check Answer"
          </Button>
          (
            switch (self.state.answered) {
            | None => ReasonReact.null
            | Some(v) =>
              Array.append(
                [|
                  <Button onClick=(_ => self.send(NextQuestion))>
                    "Next Question"
                  </Button>,
                |],
                if (v) {
                  [|<div> (ReasonReact.string("You got it right!")) </div>|];
                } else {
                  [|
                    <div>
                      (
                        ReasonReact.string(
                          "You got it wrong! The correct answer is: "
                          ++ string_of_int(self.state.problem.answer),
                        )
                      )
                    </div>,
                  |];
                },
              )
              |> ReasonReact.array
            }
          )
        </Col>
      </Row>,
    |]
    |> ReasonReact.array,
};