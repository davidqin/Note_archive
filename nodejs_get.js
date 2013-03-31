var http = require('http');

var req = http.get({host:'localhost', port:4000, path:'/',agent:false},function(res) {
    console.log(res);
    resultdata = ""
    res.on('data',function(chunk) {
        resultdata += chunk;
    });

    res.on('end',function() {
        console.log('return ' + resultdata);
    });
});

req.on('error',function(err) {
    console.log('problem with request: ' + err.message);
});