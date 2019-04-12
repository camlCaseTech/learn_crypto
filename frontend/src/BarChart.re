let drawChart = [%bs.raw
  {|
    function() {
        var d3 = require("d3");
        // const data = [12, 5, 6, 6, 9, 10];
        // const svg = d3.select("body").append("svg").attr("width", 700).attr("height", 300);

        const data = [12, 5, 6, 6, 9, 10];
        const w = 700;
        const h = 300;

        const svg = d3.select("body")
          .append("svg")
          .attr("width", w)
          .attr("height", h)
          .style("margin-left", 100);

        svg.selectAll("rect")
          .data(data)
          .enter()
          .append("rect")
          .attr("x", (d, i) => i * 70)
          .attr("y", (d, i) => h - 10 * d)
          .attr("width", 65)
          .attr("height", (d, i) => d * 10)
          .attr("fill", "green")
    }
   |}
];

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

let component = ReasonReact.reducerComponent("BarChart");

open BsReactstrap;

let make = (~id: string, _children) => {
  ...component,
  initialState,
  reducer,
  didMount: self => drawChart(),
  render: self => <Row> <div id=("#" ++ id) /> </Row>,
};