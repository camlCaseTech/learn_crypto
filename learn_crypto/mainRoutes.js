// not yet in use, temporary routing stub
angular.module("cryptoApp", ["d3", "hashCtrl", "ngRoute"])
	.config(function ($routeProvider) {
		$routeProvider.when("/temp", {
			templateUrl: "/views/temp.html"
		});
		$routeProvider.when("/temp2", {
			templateUrl: "/views/temp2.html"
		});
		$routeProvider.otherwise({
			templateUrl: "/views/temp.html"
		});
	});