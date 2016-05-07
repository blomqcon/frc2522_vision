var express = require('express');
var http = require('http');
var bodyParser = require('body-parser');
var path = require('path');

var app = express();
var server = http.createServer(app);

// all environments
app.use(express.static(path.join(__dirname, 'public')));
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

app.set('port', process.env.VCAP_APP_PORT || 3001);

//api
var api = require('./api');
app.get('/api/getTargetLocation', api.targetScreenLocation);

var camera = require('./camera');
//app.get('/api/camera/setBlinkRate', camera.setBlinkRate);
//app.get('/api/camera/setPosition', camera.setPosition);

http.createServer(app).listen(app.get('port'), function() {
  console.log('Express server listening on port ' + app.get('port'));
});