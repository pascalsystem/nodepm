var i = 0;
var j = 0;
var sigCounter = 100;
var sigTime = 500;

setInterval(function(){
    i++;
    console.log('CONSOLE: ' + i.toString());
}, 500);

var sigTermFunc = function(done) {
    if (j < sigCounter) {
        j++;
        setTimeout(function(){
            console.log('SIGTERM -> counter -> ' + j.toString());
            sigTermFunc();
        }, sigTime);
    } else {
        done();
    }
};

process.on('SIGTERM', function(){
    if ((typeof process._terminate === 'boolean') && process._terminate) {
        return;
    }
    process._terminate = true;
    console.log('SIGTERM -> start');
    sigTermFunc(function(){
        console.log('SIGTERM -> end');
        process.exit();
    });
});