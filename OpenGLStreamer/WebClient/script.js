function connectWebSocket() {
	try {
	    var socket = new WebSocket("ws://localhost:1234");
	    var processCall = Module.cwrap('processCall', null, ['number','number']);
	    console.log('Socket Status: '+socket.readyState, "event");

	    socket.onopen = function(){
	        console.log('Socket Status: '+socket.readyState+' (open)', "event");
	    };
	    socket.onclose = function(){
	        console.log('Socket Status: '+socket.readyState+' (closed)', "event");
	    };
	    socket.onmessage = function(msg){
	        var myReader = new FileReader();
	        myReader.addEventListener("loadend", function(e) {
	            var data = new Uint8Array(this.result);
	            var nDataBytes = data.length * data.BYTES_PER_ELEMENT;
	            var dataPtr = Module._malloc(nDataBytes);
	            var dataHeap = new Uint8Array(Module.HEAPU8.buffer, dataPtr, nDataBytes);
	            dataHeap.set(data);
	            processCall(dataHeap.byteOffset, data.length);
	            console.log("Frame processed");
	            Module._free(dataHeap.byteOffset);

	        });
	        myReader.readAsArrayBuffer(msg.data);
	    };
	}
	catch(exception)
	{
	    console.log('Error'+exception, "exception");
	}
} 
   
