/* start script javascript*/
	var xhr,buttonstate=0,power=0,auto=0, led=0,cmd=0;
	xhr = new XMLHttpRequest();
	var butCamUp,butCamMiddle,butCamDown,butFrwrd,butFrwrdRight,butRight,butBckwrdRight,butBckwrd,butBckwrdLeft,butLeft,butFrwrdLeft, butpress;
	function onoff(e)
	{
		if(e.id == "pwr" && power == 0){ buttonstate = 1; power = 1; cmd = 1;}
		else if(e.id == "pwr" && power == 1){ buttonstate = 0; power = 0; cmd = 0;}
		else if(e.id == "auto" && auto == 0 && power == 1){ buttonstate = 1; auto = 1; cmd = 3;}
		else if(e.id == "auto" && auto == 1){ buttonstate = 0; auto = 0; cmd = 2;}
		else if(e.id == "led" && led == 0 && power == 1){ buttonstate = 1; led = 1; cmd = 5;}
		else if(e.id == "led" && led == 1){ buttonstate = 0; led = 0; cmd = 4;}
		var blabel, bstyle, bcolor;

		if(buttonstate)
		{
			blabel="ON";
			bstyle="#808080";
			bcolor="#00FF00";
			var url ='motor.php?state=';
			url += cmd;
			xhr.open('GET', url, false);
			xhr.send();
		}
		else
		{
			blabel="OFF";
			bstyle="#e0e0e0";
			bcolor="black";
			var url ='motor.php?state=';
			url += cmd;
			xhr.open('GET', url, false);
			xhr.send();
		}
		var child=e.firstChild;
		child.style.background= bstyle;
		child.style.color= bcolor;
		child.innerHTML= blabel;
	}
	function init() {
		butFrwrd = document.getElementById("butFrwrd");
		butFrwrdRight = document.getElementById("butFrwrdRight");
		butRight = document.getElementById("butRight");
		butBckwrdRight = document.getElementById("butBckwrdRight");
		butBckwrd = document.getElementById("butBckwrd");
		butBckwrdLeft = document.getElementById("butBckwrdLeft");
		butLeft = document.getElementById("butLeft");
		butFrwrdLeft = document.getElementById("butFrwrdLeft");
		butCamUp = document.getElementById("butCamUp");
		butCamMiddle = document.getElementById("butCamMiddle");
		butCamDown = document.getElementById("butCamDown");
		butpress = 0;
	}
	function press1(id, cmd) {
		butpress = 1;
		var NAME = document.getElementById(id);
		NAME.className = "myButton pressed";
		var url ='motor.php?state=';
		url += cmd;
		xhr.open('GET', url, false);
		xhr.send();
		
	}
	function release1(id, cmd) {
		if (butpress) {
			butpress = 0;
			var NAME = document.getElementById(id);
			NAME.className = "myButton";
			var url ='motor.php?state=';
			url += cmd;
			xhr.open('GET', url, false);
			xhr.send();
		}
	}
/* end script */
