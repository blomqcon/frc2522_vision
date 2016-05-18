"use strict";

var http = require('http');
var bone = require('octalbonescript');

var xServoPin = 'P9_14';
var yServoPin = 'P9_16';

bone.pinMode('USR3', 'out'); //On-board led
bone.pinMode(xServoPin, bone.ANALOG_OUTPUT);
bone.pinMode(yServoPin, bone.ANALOG_OUTPUT);
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


let xServo = new Servo(bone, xServoPin, 0.0);
let yServo = new Servo(bone, yServoPin, 0.0);

var angle = 0.0;
var incre = 45.0;

setInterval(function() {
	if((angle >= 90.0) || (angle <= -90.0)) {
		incre = -incre;
	}
	angle += incre;
	xServo.setAngle(angle);
}, 500);



