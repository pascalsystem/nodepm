var fs = require('fs');
var http = require('http');

/**
 * Sockets configuration
 * 
 * @returns {ProcessSocketConfig}
 */
var ProcessSocketConfig = function() {
    this.__sockets = {};
    this.__servers = {};
};

/**
 * Get listen
 * 
 * @param {string} key
 * @param {number} defaultPort
 * @returns {string|number}
 */
ProcessSocketConfig.prototype.getListen = function(key, defaultPort) {
    if (typeof key !== 'string') {
        throw new Error('get listen required first parameter string type');
    }
    if (typeof defaultPort !== 'undefined' && typeof defaultPort !== 'number') {
        throw new Error('get listen required second parameter number or undefined');
    }
    if (typeof this.__sockets[key] !== 'undefined') {
        return this.__sockets[key];
    }
    return defaultPort;
};

/**
 * Add socket configuration
 * 
 * @param {string} key
 * @param {string} filePath
 * @returns {void}
 */
ProcessSocketConfig.prototype.__addSocket = function(key, filePath) {
    if (typeof key === 'string' && typeof filePath === 'string') {
        try {
            fs.unlinkSync(filePath);
        } catch (err) {
            if ((typeof err === 'object') && (typeof err.errno === 'number') && (err.errno === 34)) {
                
            } else {
                throw new Error('PascalSystem Socket can`t restart socket unix file path: ' + filePath);
            }
        }
        this.__sockets[key] = filePath;
    } else if (typeof key === 'string' && typeof filePath === 'number') {
        this.__sockets[key] = filePath;
    } else {
        throw new Error('PascalSystem Socket required key and file path socket is string');
    }
};

var conf = new ProcessSocketConfig();

http.Server.prototype._pmNodeListen = http.Server.prototype.listen;
http.Server.prototype.listen = function(socketData, callback) {
    if ((typeof callback !== 'undefined') && (typeof callback !== 'undefined')) {
        throw new Error('PascalSystem Socket not supported second params another then function or undefined');
    }
    var res = this._pmNodeListen(socketData, function() {
        if (typeof socketData === 'string') {
            fs.chmodSync(socketData, 0777);
        }
        if (typeof callback === 'function') {
            callback();
        }
    });
    conf.__servers[socketData] = this;
    return res;
}
process.on('SIGTERM', function(){
    setTimeout(function(){
        console.log('Close application without wait for close http servers');
        process.exit(1);
    }, 5 * 1000);
    for (var k in conf.__servers) {
        conf.__servers[k].close();
    }
    console.log('Close application with close http servers');
    process.exit();    
});

/**
 * Check data in process arguments
 * 
 */
if ((typeof process === 'object') && (typeof process.argv === 'object') && (typeof process.argv.length == 'number')) {
    for (var i=0;i<process.argv.length;i++) {
        var val = process.argv[i];
        var prefixSocket = '--NODEPMSOCKET:';
        var posConfig = val.toString().indexOf(prefixSocket);
        if (posConfig !== -1) {
            var subConfigData = val.toString().substr(posConfig + prefixSocket.length).trim().split(' ' + prefixSocket);
            for (var j=0; j<subConfigData.length; j++) {
                var socketData = subConfigData[j].toString().trim();
                console.log(socketData);
                if (socketData.split(':').length !== 2 ) {
                    throw new Error('PascalSystem Socket configuration is not correct: required `:` separator');
                }
                if (socketData.split(':')[1].toString().indexOf('/') === 0) {
                    conf.__addSocket(
                            socketData.split(':')[0].toString(),
                            socketData.split(':')[1].toString()
                    );
                } else {
                    var socketDataNumber = new Number(socketData.split(':')[1].toString());
                    if (isNaN(socketDataNumber)) {
                        throw new Error('PascalSystem Socket configuration is not correct: required `:` number after separator');
                    } else {
                        conf.__addSocket(
                                socketData.split(':')[0].toString(),
                                parseInt(socketDataNumber)
                        );
                    }
                }
            }
        }
    } 
}

/**
 * Export configuration object
 * 
 */
module.exports = conf;