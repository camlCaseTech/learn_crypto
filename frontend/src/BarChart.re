/*
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
 */

let drawChart2: Js.Dict.t(float) => unit = [%bs.raw
  {|
    function(datap) {
      const d3 = require("d3");
      const data = [];
      Object.keys(datap).forEach(function(key) {
        data.push({char: key, freq: datap[key]});
      });
      data.sort((obj1, obj2) => {
        return (obj1.char > obj2.char) - (obj1.char < obj2.char);
      });

      const margin = {top: 20, right: 20, bottom: 30, left: 40};
      const width = 1000;
      const height = 500;

      // set the ranges
      const x = d3.scaleBand()
                .range([0, width])
                .padding(0.1);
      const y = d3.scaleLinear()
                .range([height, 0]);

      // append the svg object to the body of the page
      // append a 'group' element to 'svg'
      // moves the 'group' element to the top left margin
      const svg = d3.select("body").append("svg")
                    .attr("width", width + margin.left + margin.right)
                    .attr("height", height + margin.top + margin.bottom)
                    .append("g")
                    .attr("transform",
                          "translate(" + margin.left + "," + margin.top + ")");

      // Scale the range of the data in the domains
      x.domain(data.map(function(d) { return d.char; }));
      y.domain([0, d3.max(data, function(d) { return d.freq; })]);

      // append the rectangles for the bar chart
      svg.selectAll(".bar")
         .data(data)
         .enter()
         .append("rect")
         .attr("class", "bar")
         .attr("x", function(d) { return x(d.char); })
         .attr("width", x.bandwidth())
         .attr("y", function(d) { return y(d.freq); })
         .attr("height", function(d) { return height - y(d.freq); })
         .attr("fill", "green");

      // add the x Axis
      svg.append("g")
         .attr("transform", "translate(0," + height + ")")
         .call(d3.axisBottom(x));

      // add the y Axis
      // svg.append("g")
      //    .call(d3.axisLeft(y));
    }
  |}
];

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
  didMount: self =>
    drawChart2(
      Js.Dict.fromArray(Belt.Map.String.toArray(Cryptography.englishFreq)),
    ),
  render: self => <Row> <div id=("#" ++ id) /> </Row>,
};