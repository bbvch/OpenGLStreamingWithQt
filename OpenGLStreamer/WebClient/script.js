
   
    function analyze_data(blob)
	{
	    var myReader = new FileReader();
	    myReader.readAsArrayBuffer(blob);
	   
	    myReader.addEventListener("loadend", function(e)
	    {			
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
    	
   
