//var frc2522cv = require('bindings')('addon.node');
//var frc2522cv = require('../node_frc2522cv/make/windows_x86_64/build/Release/addon');
var frc2522cv = require('../node_frc2522cv/make/linux_x86_64/build/Release/addon');
var cleanup = require('./cleanup').Cleanup(cleanup);

function cleanup() {
	frc2522cv.cleanup();	
}

module.exports.targetScreenLocation = function(req, res) {
	console.log("Request for target location");
	res.status(200).send(frc2522cv.targetScreenLocation({}));
}