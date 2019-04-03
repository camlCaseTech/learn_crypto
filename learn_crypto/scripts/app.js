(function () {
  'use strict';

  // create the angular app
  angular.module('learnCryptoApp', [
    'learnCryptoApp.controllers',
    'learnCryptoApp.directives'
    ]);

  // setup dependency injection
  angular.module('d3', []);
  angular.module('learnCryptoApp.controllers', []);
  angular.module('learnCryptoApp.directives', ['d3']);

}());