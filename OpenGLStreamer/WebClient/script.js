function FunctionSignatureState()
{
	this.file_offset = 0;
	this.flags = 0;
	this.id = 0;
	this.name ="";
	this.arg_names = {};
}




function Parser(ba) {
	this.array = ba;
	this.i8Array = new Int8Array(ba);
	this.index = 0;
	this.functions = {};
}

var Mode = {
    FULL: 0,
    SCAN: 1,
    SKIP: 2
};

var Event = {
    EVENT_ENTER: 0,
    EVENT_LEAVE: 1,
    EVENT_RESET: 2
};

Parser.prototype.read_byte = function()
{
	return this.i8Array[this.index++];
};

Parser.prototype.read_uint = function()
{
	var value = 0;
    do {
        c = this.i8Array[this.index++];
        value |= (c & 0x7f) << shift;
        shift += 7;
    } while(c & 0x80);

    return value;
}

Parser.prototype.parse_function_sig = function() {
    id = read_uint();

    sig = functions[id];

    if (!sig) {
        /* parse the signature */
        sig = new FunctionSigState;
        sig.id = id;
        sig.name = read_string();
        sig.num_args = read_uint();
        
        for (i = 0; i < sig.num_args; ++i) {
            arg_names[i] = read_string();
        }
        sig.arg_names = arg_names;
        sig.flags = lookupCallFlags(sig.name);
        sig.fileOffset = this.index.
        functions[id] = sig;

        /**
         * Try to autodetect the API.
         *
         * XXX: Ideally we would allow to mix multiple APIs in a single trace,
         * but as it stands today, retrace is done separately for each API.
         */
 /*       if (api == API_UNKNOWN) {
            const char *n = sig->name;
            if ((n[0] == 'g' && n[1] == 'l' && n[2] == 'X') || // glX*
                (n[0] == 'w' && n[1] == 'g' && n[2] == 'l' && n[3] >= 'A' && n[3] <= 'Z') || // wgl[A-Z]*
                (n[0] == 'C' && n[1] == 'G' && n[2] == 'L')) { // CGL*
                api = trace::API_GL;
            } else if (n[0] == 'e' && n[1] == 'g' && n[2] == 'l' && n[3] >= 'A' && n[3] <= 'Z') { // egl[A-Z]*
                api = trace::API_EGL;
            } else if ((n[0] == 'D' &&
                        ((n[1] == 'i' && n[2] == 'r' && n[3] == 'e' && n[4] == 'c' && n[5] == 't') || // Direct*
                         (n[1] == '3' && n[2] == 'D'))) || // D3D*
                       (n[0] == 'C' && n[1] == 'r' && n[2] == 'e' && n[3] == 'a' && n[4] == 't' && n[5] == 'e')) { // Create*
                api = trace::API_DX;
            } else {
                // TODO 
            }
        }*/

        /**
         * Note down the signature of special functions for future reference.
         *
         * NOTE: If the number of comparisons increases we should move this to a
         * separate function and use bisection.
         */
        if (sig.num_args == 0 &&
            strcmp(sig.name, "glGetError") == 0) {
            glGetErrorSig = sig;
        }

    } else if (this.index < sig.fileOffset) {
        /* skip over the signature */
        skip_string(); /* name */
        num_args = read_uint();
        for (i = 0; i < num_args; ++i) {
             skip_string(); /*arg_name*/
        }
    }

    assert(sig);
    return sig;
}

Parser.prototype.parse_enter = function(mode)
{
	var thread_id = 0;

    thread_id = read_uint();
    

    sig = parse_function_sig();

    call = new Call(sig, sig.flags, thread_id);

    call.no = next_call_no++;

    if (parse_call_details(call, mode)) {
        calls.push_back(call);
    } else {
        delete call;
    }
};

Parser.prototype.parse_call = function(mode) 
{ 

	do {
		    c = this.read_byte();
		    switch (c) {
		    case Event.EVENT_ENTER:
		        this.parse_enter(mode);
		        break;
		    case Event.EVENT_LEAVE:

		        call = parse_leave(mode);
		        if (call) {
		            this.adjust_call_flags(call);
		            return call;
		        }
		        break;
		    case Event.EVENT_RESET:

		        this.resetSignatures();
		        next_call_no = 0;
		        break;
		    default:
		        console.log("error: unknown event "+ c + "\n");
		        exit(1);
		    case -1:
		        if (!calls.empty()) {
		            /*call = calls.front();
		            call->flags |= CALL_FLAG_INCOMPLETE;
		            calls.pop_front();
		            adjust_call_flags(call);
		            return call;
					*/
		        }
		        return NULL;
		    }
		} while(true);
};



    function analyze_data(blob)
	{
	    var myReader = new FileReader();
	    myReader.readAsArrayBuffer(blob);
	   
	    myReader.addEventListener("loadend", function(e)
	    {		
			var p = new Parser(this.result);
			p.parse_call(Mode.FULL);
			message(this.result.byteLength, "data");
	    });

	}
    
    function message(msg, type){
		
		var log = document.getElementById("log");
		var newParagraph = document.createElement("p");
		var newTextNode = document.createTextNode(msg);
		
		if( type !== undefined) { 
			newParagraph.setAttribute("class",type);
		} 
		
		newParagraph.appendChild(newTextNode);
		log.appendChild(newParagraph);
	
	}
    
	function connect(){
    try{

	var socket;
	var host = "ws://localhost:1234";
    var socket = new WebSocket(host);

        message('Socket Status: '+socket.readyState, "event");

        socket.onopen = function(){
       		 message('Socket Status: '+socket.readyState+' (open)', "event");
        }

        socket.onmessage = function(msg){
       		 //message(msg.data, "data");
		analyze_data(msg.data);
        }

        socket.onclose = function(){
       		 message('Socket Status: '+socket.readyState+' (Closed)', "event");
        }			

    } catch(exception){
   		 message('Error'+exception, "exception");
    }
}
    
 	window.addEventListener("load", connect, true);
    	
   
