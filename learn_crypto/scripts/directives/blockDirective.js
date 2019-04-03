(function () {
  'use strict';

  angular.module('learnCryptoApp.directives')
    .directive('d3Block', ['d3', function(d3) {
      function link(scope, element, attr) {
        var data = scope.data;
        var svgWidth = 300;
        var svgHeight = 450;
        var svg = d3.select(element[0])
                    .append('svg')
                    .attr({width: svgWidth, height: svgHeight});

        scope.$watch('data', function(data) {
          var rect = svg.selectAll('rect')
          var rects = rect.data(data);
          rects.enter().append('rect')
                .attr('x', function(d, i) { return i })
                .attr('y', function(d) { return d })
                .attr({ height: svgHeight, width: svgWidth });
        }, true);
      }
      return {
        restrict: 'E',
        scope: { data: '=' },
        link: link
      }
    }]);

}());