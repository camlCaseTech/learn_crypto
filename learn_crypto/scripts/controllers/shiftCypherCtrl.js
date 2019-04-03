(function () {
  'use strict';

// dynamically calculates letter frequency of user input and compares to actual english language frequency
// to be added: ascii to binary conversion and xor

angular.module('learnCryptoApp.controllers')
  .controller('shiftCypherCtrl', ['$scope', function($scope) {
    $scope.codeArray = [];
    $scope.binary = [];
    $scope.randArray = [];
    $scope.xorArray = [];

    // offsets user text by selected number
    $scope.asciiCode = function(text, offset) {
      if (text == undefined) return;
      $scope.codeArray = [];
      for (var i = 0; i < text.length; i++) {
        var textUpper = text.toUpperCase();
        if (textUpper.charCodeAt(i) >= 65 && textUpper.charCodeAt(i) <= 90) {
          var asciiOffset = (parseInt(textUpper.charCodeAt(i)) + parseInt(offset) + 13) % 26;
          var codeStr = String.fromCharCode(asciiOffset + 65);
          $scope.codeArray.push(codeStr);
        } else {
          $scope.codeArray.push(String.fromCharCode(32));
        }
      }
      return $scope.codeArray;
    }

    // calculates frequency of user text input
    $scope.charFrequency = function(str) {
      if (str == undefined) return;
      var charCount = $scope.charFreq;
      for (var i = 65; i < 91; i++)
        charCount[String.fromCharCode(i)] = 0;
      for (var i = 0; i < str.length; i++) {
        if (str[i] in charCount)
          charCount[str[i]] += 1;
      }
      var charFreq = {};
      for (var letter in charCount) 
        charFreq[letter] = (charCount[letter] / str.length);
      $scope.charFreq = charFreq;
    }

    $scope.toBinary = function(str, spaceSeparatedOctets) {
      $scope.binary = [];
      function zeroPad (num) {
        return "00000000".slice(String(num).length) + num;
      }
      return str.replace(/[\s\S]/g, function(str) {
        str = zeroPad(str.charCodeAt().toString(2));
        return !1 == spaceSeparatedOctets ? $scope.binary.push(str) : $scope.binary.push(str + " ");
      });
    };

    $scope.toAscii = function(bin) {
      return bin.replace(/\s*[01]{8}\s*/g, function(bin) {
        return String.fromCharCode(parseInt(bin, 2) % 26 + 65);
      });
    };

    $scope.randUniform = function(binary) {
      $scope.randArray = [];
      for (var i = 0; i < binary.length; i++) {
        if (Math.random() < 0.5)
          $scope.randArray.push(0);
        else
          $scope.randArray.push(1);
      }
      return $scope.randArray;
    };

    $scope.xorBinary = function(binary, randBinary) {
      $scope.xorArray = [];
      var binaryArray = _.map(binary.split(''), function(num){ return parseInt(num); });
      for (var i = 0; i < binaryArray.length; i++) {
        if (binaryArray[i] + randBinary[i] == 1)
          $scope.xorArray.push(1);
        else
          $scope.xorArray.push(0);
      }
      return $scope.xorArray;
    };

    // updates based on letter frequency of user input
    $scope.charFreq = {
      'A': 0,
      'B': 0,
      'C': 0,
      'D': 0,
      'E': 0,
      'F': 0,
      'G': 0,
      'H': 0,
      'I': 0,
      'J': 0,
      'K': 0,
      'L': 0,
      'M': 0,
      'N': 0,
      'O': 0,
      'P': 0,
      'Q': 0,
      'R': 0,
      'S': 0,
      'T': 0,
      'U': 0,
      'V': 0,
      'W': 0,
      'X': 0,
      'Y': 0,
      'Z': 0
    };
    // actual letter frequency of english language
    $scope.englishFreq = {
      'A': 0.08167,
      'B': 0.01492,
      'C': 0.02782,
      'D': 0.04253,
      'E': 0.12702,
      'F': 0.02288,
      'G': 0.02015,
      'H': 0.06094,
      'I': 0.06966,
      'J': 0.00153,
      'K': 0.00772,
      'L': 0.04025,
      'M': 0.02406,
      'N': 0.06749,
      'O': 0.07507,
      'P': 0.01929,
      'Q': 0.00095,
      'R': 0.05987,
      'S': 0.06327,
      'T': 0.09056,
      'U': 0.02758,
      'V': 0.00978,
      'W': 0.02360,
      'X': 0.00150,
      'Y': 0.01974,
      'Z': 0.00074
    };
  }]);

}());