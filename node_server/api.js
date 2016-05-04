var frc2522cv = require('bindings')('addon.node');

module.exports.getTargetLocation = function(req, res) {
	console.log("Request for target location");
	res.status(200).send(frc2522cv.getBinderLocation())
    res.status(200).send({'targetLoc': frc2522cv.add(3, 5)});
}

module.exports.test = function(req, res) {
	res.status(200).send(frc2522cv.getBinderLocation().key);
}