var counter = 0;

var testFunc = function() {
    setTimeout(function(){
        console.log('call test function: ' + counter.toString());
        counter++;
        testFunc();
    }, 1000);
};

console.log('Start app without socket');
testFunc();