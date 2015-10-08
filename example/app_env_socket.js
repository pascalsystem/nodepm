var http = require('http');

var listenEnvPort = process.env.PORT ? (isNaN(parseInt(process.env.PORT)) ? process.env.PORT : parseInt(process.env.PORT)) : 9111;
console.log('START APP ENV SOCKET APPLICATION ON port: ' + listenEnvPort.toString());
var serverDefault = http.createServer(function (request, response) {
    console.log('Get request default server');
    response.writeHead(200, {"Content-Type": "text/plain"});
    response.end((typeof process.env.PORT === 'undefined') ? 'undefined' : process.env.PORT);
}).listen(listenEnvPort);
