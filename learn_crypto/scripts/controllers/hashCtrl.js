(function () {
  'use strict';

// real time hashing of user input
// uses Google's crypto-js library for MD5, SHA-256, or SHA-3

angular.module('learnCryptoApp.controllers')
  .controller('hashCtrl', ['$scope', function($scope) {
    $scope.hashes = { hashName: "MD5" };

    $scope.createHash = function(message, hashType) {
      if (hashType == "MD5")
        return CryptoJS.MD5(message).toString(CryptoJS.enc.Hex);
      else if (hashType == "SHA-256")
        return CryptoJS.SHA256(message).toString(CryptoJS.enc.Hex);
      else if (hashType == "SHA-3")
        return CryptoJS.SHA3(message).toString(CryptoJS.enc.Hex);
      else
        return "Error";
    };
  }]);

}());