var sys = require('sys');
var http = require('http');
var fs = require('fs');
var exec = require('child_process').exec;

function decimalToHex(r, g, b) {
	var hexStr = "";
	var hex = "";
	var colors = [r, g, b];
	for(var c in colors) {
		hex = colors[c].toString(16);
		if(hex.length == 1) hex = "0" + hex;
		hexStr += hex;
	}

	return hexStr;
}

var hexColors = [];

var hexStr = "";
for(var r = 0; r < 256; r += 16) {
	for(var g = 0; g < 256; g += 16) {
		for(var b = 0; b < 256; b += 16) {
			hexColors.push(decimalToHex(r, g, b));
		}
	}
}

function slowDownload(i, limit) {
	if(i < limit) {
		exec("sleep 1", function() {
			downloadColor(hexColors[i]);
			slowDownload(i + 1, limit);
		});
	}
}

//slowDownload(hexColors.length - 20, hexColors.length);

function downloadColor(color) {
	try {
		var colorSite = http.createClient(80, "labs.ideeinc.com");

		var request = colorSite.request('GET', '/coloursearch/services/rest?method=color.search&colors=' + color + '&imageset=flickr&quantity=2&page=0', {'host': 'labs.ideeinc.com'});

		request.end();

		request.on('response', function(response) {
			response.on('data', function(chunk) {
				// Connect to the amazon server that hosts the image thumbnail
				var amazon = http.createClient(80, "s3.amazonaws.com");

				// The result is in JSON, load it into an object
				var result = eval('(' + chunk + ')');

				var link;
				for(var i = 1; i < result.result.length; i++) {
					// Array numerical indexes:
					// 	index 0 -- the image id
					//  	index 1 -- the amazon link
					//  	index 2 -- the flickr link

					link = result.result[i][1];

					// Download the image and save it to the images folder. Filename is the color of the image in hex.
					exec("wget " + link + " -O ./images/" + color + "-" + i + ".jpg");
					console.log("Downloaded " + color);
				}
			});
		});
	} catch(SyntaxError) {
		exec("sleep 2", function() {
			downloadColor(color);
		});
	}

}

downloadColor("c04080");
