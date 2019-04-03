(function () {
  'use strict';

  // dynamic d3 bar chart for english letter frequency
  // make more general for other kinds of data
  // add character text labels and percentages
  // .text(function(d) { return d.key; });

  angular.module('learnCryptoApp.directives')
    .directive('d3BarChart', ['d3', function(d3) {
      function link(scope, element, attr) {
        var data = scope.data;
        var numBars = _.size(data);
        var svgHeight = attr.height;
        var svgWidth = attr.width;
        var barSpacing = 2;
        var barWidth = (svgWidth - numBars * barSpacing) / numBars;
        var svg = d3.select(element[0]).append('svg')
                    .attr({width: svgWidth, height: svgHeight});

        function chart(data, init) {
          var maxVal = _.max(_.values(data));
          if (maxVal == 0)
            var barHeight = 0;
          else
            var barHeight = svgHeight / maxVal;
          var rect = svg.selectAll('rect');
          var rects = rect.data(d3.entries(data));
          if (init == true) 
            rects.enter().append('rect')
                          
          rects.attr('x', function(d, i) { return i * (barWidth + barSpacing) })
                .attr('y', function(d) { return svgHeight - d.value * barHeight; })
                .attr({ height: svgHeight, width: barWidth, fill: attr.fill });
        };

        chart(data, true);

        scope.$watch('data', function(data) {
          chart(data, false);
        }, true);
      }
      return {
        restrict: 'E',
        scope: { data: '=' },
        link: link
      }
    }]);

}());