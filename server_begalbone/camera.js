"use strict";

var http = require('http');
//var bone = require('bonescript');
//var bone = require('/bonescript-0.5.0-beta5/main.js');
var bone = require('octalbonescript');
//var bone = {pinMode: function() {}, digitalWrite: function() {}, analogWrite: function() {}, ANALOG_OUTPUT: 0};

class Servo {
	constructor(pin, angle) {
		this.cycle_length = 20.0; //ms
		this.cycle_min = 0.9; //ms
		this.cycle_max = 2.1; //ms
		this.frequency = 1000.0 / this.cycle_length; //50 Hz
	
		this.duty_min = this.cycle_min / this.cycle_length; //4.5%
		this.duty_max = this.cycle_max / this.cycle_length; //10.5%
		
		this.servoPin = pin;
		this.setAngle(angle);
	}
		
	setAngle(a) {
		if(a < -90.0)
			this.angle = -90.0;
		else if(a > 90.0)
			this.angle = 90.0;
		else
			this.angle = a;
		
		var duty_cycle = this.duty_min + ((this.duty_max - this.duty_min) * ((this.angle + 90.0) / 180.0));
		console.log(this.servoPin, duty_cycle, this.frequency);
		console.log(bone.analogWrite);
		bone.analogWrite(this.servoPin, duty_cycle, this.frequency);
	}
	
	getAngle() {
		return this.angle;
	}
}

class BlinkLed {
    constructor(pin, rate) {
        this.pin = pin;
        this.state = 0;
        this.setBlinkRate(rate);
    }

    setBlinkRate(rate) {
		this.rate = rate;
		clearInterval(this.timer);
		this.timer = setInterval(() => this.toggleLED(), this.rate);
	}

    toggleLED() {
    	console.log(this.pin, this.state);
    	this.state = this.state ? 0 : 1;
		bone.digitalWrite(this.pin, this.state);
    }
};




function autotrackFunc() {
	var getTargetOptions = {
	  host: 'localhost',
	  path: '/api/getTargetLocation',
	  port: '3001'
	};

	http.request(getTargetOptions, function(response) {
		var data = '';
		response.on('data', function (chunk) { data += chunk;});

		response.on('end', function () {
			var json = JSON.parse(data);
			
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
}


//var xServoPin = 'P9_14';
var xServoPin = 'P9_22';
var yServoPin = 'P9_16';
var ledPin = 'USR3';

bone.pinMode(ledPin, 'out'); //On-board led
bone.pinMode(xServoPin, bone.ANALOG_OUTPUT);
bone.pinMode(yServoPin, bone.ANALOG_OUTPUT);

let xServo = new Servo(xServoPin, 0.0);
let yServo = new Servo(yServoPin, 0.0);
let led = new BlinkLed(ledPin, 1000);
var autoTrack = null;


/***********************************************/
/******************  API   *********************/
/***********************************************/
module.exports.setBlinkRate = function(req, res) {
	led.setBlinkRate(req.query.rate);
	res.status(200).send();
}

module.exports.enableAutoTrack = function(req, res) {
	if(req.query.auto && !(autoTrack)) {
		console.log("enabling auto track...");
		autoTrack = setInterval(autotrackFunc, 100);
	} else if((req.query.auto) && autoTrack) {
		console.log("disabling auto track...");
		clearInterval(autoTrack);
		autoTrack = null;
	}
	res.status(200).send();
}

module.exports.getAngles = function(req, res) {
	res.status(200).send({x: xServo.getAngle(), y: yServo.getAngle()});
}

module.exports.setAngles = function(req, res) {
	if(!(autoTrack)) {
		xServo.setAngle(req.query.x);
		yServo.setAngle(req.query.y);
	}
	res.status(200).send({x: xServo.getAngle(), y: yServo.getAngle()});
}
