var frc2522cv = require('bindings')('addon.node');

module.exports.getTargetLocation = function(req, res) {
	console.log();
    res.status(200).send({'targetLoc': frc2522cv.add(3, 5)});
}