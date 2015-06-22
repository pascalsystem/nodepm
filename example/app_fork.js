// Listen configuration NodePM additional data
var listenConf = require('./NodePM');
// Listen configuration for socket key default
var serverListenDefault = listenConf.getListen('default', 9080);

// Load the http module to create an http server.
var http = require('http');
console.log('start app');

// Hello world forked app - DEFAULT http server for NodePM
var serverDefault = http.createServer(function (request, response) {
    console.log('Get request default server');
    response.writeHead(200, {"Content-Type": "text/plain"});
    response.end("Hello World forked app - DEFAULT\n");
}).listen(serverListenDefault);
console.log("Start Hello World forked app - DEFAULT server, LISTEN: " + serverListenDefault.toString());

// Running application info log
console.log('Application running');