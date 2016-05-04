var bone = require('bonescript');

bone.pinMode('USR3', 'out'); //On-board led
bone.pinMode('P9_14', bone.OUTPUT); //Servo output

bone.digitalWrite('USR3', 1);

var led = (function (bone) {
	var state = 0;
	var rate = 100;
	var timer = setInterval(toggleLED, rate);
	
	function toggleLED() {
		state = state ? 0 : 1;
		bone.digitalWrite('USR3', state);
	}
	
	function stopTimer() {
		clearInterval(timer);
		timer = null;
	}
	
	function setBlinkRate(r) {
		rate = r;
		stopTimer();
		timer = setInterval(toggleLED, rate);
	}

	return {
		setBlinkRate: setBlinkRate
	};
}(bone));


var camera = (function (bone) {
	var duty_min = 0.03;
	var position = 0;
	var increment = 0.01;
	//var timer = setInterval(scan, 100);
	
	function scan() {
		setPosition(position + increment);
		var duty_cycle = (position * 0.115) + duty_min;
		//bone.analogWrite('P9_14', duty_cycle, 60, scheduleNextUpdate);
		console.log("Duty Cycle: " + parseFloat(duty_cycle * 100).toFixed(1) + " %");   
	}
	
	function setPosition(pos) {
		if(pos <= 0) {
			position = 0;
			increment = -increment;
		} else if(pos >= 1) {
			position = 1;
			increment = -increment;
		} else {
			position = pos;
		}
	}
	
	return {
		setPosition: setPosition
	};
}(bone));



module.exports.setBlinkRate = function(req, res) {
	led.setBlinkRate(req.query.rate);
	res.status(200).send("Rate set to " + req.query.rate + "ms!");
}

module.exports.setPosition = function(req, res) {
	camera.setPosition(req.query.pos)
	res.status(200).send("Position set to " + req.query.pos + "!");
}