"use strict";

var http = require('http');
//var bone = require('bonescript');
//var bone = require('/bonescript-0.5.0-beta5/main.js');
//var bone = require('octalbonescript');
var bone = {pinMode: function() {}, digitalWrite: function() {}, analogWrite: function() {}, ANALOG_OUTPUT: 0};


var xServoPin = 'P9_14';
var yServoPin = 'P9_15';

bone.pinMode('USR3', 'out'); //On-board led
bone.pinMode(xServoPin, bone.ANALOG_OUTPUT);
bone.digitalWrite('USR3', 1);

class Servo {
	constructor(bone, servoPin, angle) {
		this.cycle_length = 20.0; //ms
		this.cycle_min = 0.9; //ms
		this.cycle_max = 2.1; //ms
		this.frequency = 1000.0 / this.cycle_length; //50 Hz
	
		this.duty_min = this.cycle_min / this.cycle_length; //4.5%
		this.duty_max = this.cycle_max / this.cycle_length; //10.5%
		
		this.bone = bone;
		this.servoPin = servoPin;
		this.angle = angle;
	}
		
	setAngle(a) {
		if(a < -90.0)
			this.angle = -90.0;
		else if(a > 90.0)
			this.angle = 90.0;
		else
			this.angle = a;
		
		var duty_cycle = this.duty_min + ((this.duty_max - this.duty_min) * ((this.angle + 90.0) / 180.0));
		this.bone.analogWrite(this.servoPin, duty_cycle, this.frequency);
	}
	
	getAngle() {
		return this.angle;
	}
}


var getTargetOptions = {
  host: 'localhost',
  path: '/api/getTargetLocation',
  port: '3001'
};

let xServo = new Servo(bone, xServoPin, 0.0);
let yServo = new Servo(bone, yServoPin, 0.0);

setInterval(function() {
	console.log("X angle: " + xServo.getAngle());
	console.log("Y angle: " + yServo.getAngle());
	console.log();
	
	http.request(getTargetOptions, function(response) {
		var data = '';

		response.on('data', function (chunk) { data += chunk;});

		response.on('end', function () {
			var json = JSON.parse(data);
			console.log(json);
			
			if((json.centerPoint.x - json.targetPoint.x) > 10.0) {
				xServo.setAngle(xServo.getAngle() - 1.0);
			} else if((json.centerPoint.x - json.targetPoint.x) < -10.0) {
				xServo.setAngle(xServo.getAngle() + 1.0);
			}
			
			if((json.centerPoint.y - json.targetPoint.y) > 10.0) {
				yServo.setAngle(yServo.getAngle() - 1.0);
			} else if((json.centerPoint.y - json.targetPoint.y) < -10.0) {
				yServo.setAngle(yServo.getAngle() + 1.0);
			}
		});
	}).end();
}, 100);



/*var led = (function (bone) {
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
}(bone));*/


/*var camera = (function (bone) {
	var duty_min = 0.03;
	var position = 0;
	var increment = 0.01;
	//var timer = setInterval(scan, 100);
	
	function scan() {
		setPosition(position + increment);
		var duty_cycle = (position * 0.115) + duty_min;
		//bone.analogWrite('P9_14', duty_cycle, 50, scheduleNextUpdate);
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
}(bone));*/

/*module.exports.setBlinkRate = function(req, res) {
	led.setBlinkRate(req.query.rate);
	res.status(200).send("Rate set to " + req.query.rate + "ms!");
}

module.exports.setPosition = function(req, res) {
	camera.setPosition(req.query.pos)
	res.status(200).send("Position set to " + req.query.pos + "!");
}*/



