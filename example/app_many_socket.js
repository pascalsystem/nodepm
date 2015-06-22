// Listen configuration NodePM additional data
var listenConf = require('./NodePM');
// Listen configuration for socket key default
var serverListenDefault = listenConf.getListen('default', 8080);
// Listen configuration for socket key default
var serverListenAdditional = listenConf.getListen('additional', 8090);

// Load the http module to create an http server.
var http = require('http');
console.log('start app');

// Hello world - DEFAULT http server for NodePM
var serverDefault = http.createServer(function (request, response) {
    console.log('Get request default server');
    response.writeHead(200, {"Content-Type": "text/plain"});
    response.end("Hello World - DEFAULT\n");
}).listen(serverListenDefault);
console.log("Start Hello World - DEFAULT server, LISTEN: " + serverListenDefault.toString());

// Hello world - ADDITIONAL http server for NodePM
var serverDefault = http.createServer(function (request, response) {
    console.log('Get request additional server');
    response.writeHead(200, {"Content-Type": "text/plain"});
    response.end("Hello World - ADDITIONAL\n");
}).listen(serverListenAdditional);
console.log("Start Hello World - ADDITIONAL server, LISTEN: " + serverListenAdditional.toString());

// Running application info log
console.log('Application running');