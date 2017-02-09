/* start script javascript*/
var xhrWrite,xhrRead,buttonstate=0,power=0,rec=0,led=0,cmd=0,test=0,startDist=0,dist=0,time=0;
xhrWrite = new XMLHttpRequest();
xhrRead = new XMLHttpRequest();
var butCamRight,butCamLeft,butCamUp,butCamMiddle,butCamDown,butFrwrd,butRight,butBckwrd,butLeft,butpress;
screen.orientation.lock('landscape');
navigator.vibrate = navigator.vibrate || navigator.webkitVibrate || navigator.mozVibrate || navigator.msVibrate || null;
function onoff(e)
{
	var src="";
	if(e.id == "pwr" && power == 0){ buttonstate = 1; power = 1; cmd = 11; src = 'images/pwr_on.png';}
	else if(e.id == "pwr" && power == 1){ buttonstate = 0; power = 0; cmd = 10; src = 'images/pwr_off.png';}
	else if(e.id == "rec" && rec == 0){ buttonstate = 1; rec = 1; cmd = 41; src = 'images/rec_on.png';}
	else if(e.id == "rec" && rec == 1){ buttonstate = 0; rec = 0; cmd = 40; src = 'images/rec_off.png';}
	else if(e.id == "led" && led == 0){ buttonstate = 1; led = 1; cmd = 5; src = 'images/led_on.png';}
	else if(e.id == "led" && led == 1){ buttonstate = 0; led = 0; cmd = 4; src = 'images/led_off.png';}

	if(buttonstate)
	{
		e.src = src;
		var url ='motor.php?state=';
		url += cmd;
		xhrWrite.open('GET', url, false);
		xhrWrite.send();
	}
	else
	{
		e.src = src;
		var url ='motor.php?state=';
		url += cmd;
		xhrWrite.open('GET', url, false);
		xhrWrite.send();
	}
	loadStatus();
}
function init() {
	alert(test);
	butFrwrd = document.getElementById("butFrwrd");
	butRight = document.getElementById("butRight");
	butBckwrd = document.getElementById("butBckwrd");
	butLeft = document.getElementById("butLeft");
	butCamUp = document.getElementById("butCamUp");
	butCamMiddle = document.getElementById("butCamMiddle");
	butCamDown = document.getElementById("butCamDown");
	butCamRight = document.getElementById("butCamRight");
	butCamLeft = document.getElementById("butCamLeft");
	loadStatus();
	butpress = 0;
}
function press1(id, cmd) {
	butpress = 1;
	var NAME = document.getElementById(id);
	NAME.className = "myButton pressed";
	var url ='motor.php?state=';
	url += cmd;
	xhrWrite.open('GET', url, false);
	xhrWrite.send();
	startDist = 1;
	navigator.vibrate([30]);
	loadStatus();
}
function release1(id, cmd) {
	if (butpress) {
		butpress = 0;
		var NAME = document.getElementById(id);
		NAME.className = "myButton";
		var url ='motor.php?state=';
		url += cmd;
		xhrWrite.open('GET', url, false);
		xhrWrite.send();
		loadStatus();
	}
}
function loadStatus() {
	xhrRead.onreadystatechange = function() {
		var status = xhrRead.responseText;
		var tab_status = status.split('#');
		document.getElementById("distance").innerHTML = "<p>" + dist + " cm</p>";
		document.getElementById("vitesse").innerHTML = "<p>" + tab_status[4] + "</p>";
		document.getElementById("lastCmd").innerHTML = "<a>" + tab_status[0] + "</a>";
		document.getElementById("horizontal").innerHTML = "<p>" + tab_status[1] + "</p>";
		document.getElementById("vertical").innerHTML = "<p>" + tab_status[2] + "</p>";
		if (tab_status[3] == 1 && test == 0) {
			click_pwr();
			test = 1;
		}
	};
	xhrRead.open("GET", "status.txt", true);
	xhrRead.send();
}
function click_pwr() {
	e = document.getElementById("pwr");
	onoff(e);
}
function stream(cmd) {
	var url ='motor.php?state=';
	url += cmd;
	xhrWrite.open('GET', url, false);
	xhrWrite.send();;
	reload(5000);
}
function reload(time){
	setTimeout(function() {
		location.reload();
	}, time);
}
function testError() {
	stream(99);
}
function goBack() {
	window.history.back();
}
function take_pic() {
	var url ='motor.php?state=';
	cmd = 88;
	url += cmd;
	xhrWrite.open('GET', url, false);
	xhrWrite.send();
}
function distance() {
	var now = new Date();
	

/* end script */
