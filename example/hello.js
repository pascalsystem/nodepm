// Listen configuration NodePM additional data
var listenConf = require('./NodePM');
// Listen configuration for socket key default
var serverSocketPort = listenConf.getListen('default', 8080);

// Load the http module to create an http server.
var http = require('http');

var serverDefault = http.createServer(function (request, response) {
    response.writeHead(200, {"Content-Type": "text/plain"});
    response.end("Hello World\n");
}).listen(serverSocketPort);
console.log("Start Hello World: " + serverListenDefault.toString());
