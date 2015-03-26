var xhr;
xhr = new XMLHttpRequest();
var buttonstate=0;
var buttonstateled=0;
var buttonstateauto=0;
function onoff(e)
{
	buttonstate= 1 - buttonstate;
	var blabel, bstyle, bcolor;
	if(buttonstate)
	{
		blabel="ON";
		bstyle="white";
		bcolor="blue";
		var url ='motor.php?state=1';
		xhr.open('GET', url, false);
		xhr.send();
	}
	else
	{
		blabel="OFF";
		bstyle="#028E9B";
		bcolor="black";
		var url ='motor.php?state=0';
		xhr.open('GET', url, false);
		xhr.send();
	}
	var child=e.firstChild;
	child.style.background= bstyle;
	child.style.color= bcolor;
	child.innerHTML= blabel;
}
	
function onoffled(e)
{
	buttonstateled= 1 - buttonstateled;
	var blabel, bstyle, bcolor;
	if(buttonstateled)
	{
		blabel="ON";
		bstyle="white";
		bcolor="blue";
		var url ='motor.php?state=4';
		xhr.open('GET', url, false);
		xhr.send();
	}
	else
	{
		blabel="OFF";
		bstyle="#028E9B";
		bcolor="black";
		var url ='motor.php?state=5';
		xhr.open('GET', url, false);
		xhr.send();
	}
	var child=e.firstChild;
	child.style.background= bstyle;
	child.style.color= bcolor;
	child.innerHTML= blabel;
}
function onoffauto(e)
{
	buttonstateauto= 1 - buttonstateauto;
	var blabel, bstyle, bcolor;
	if(buttonstateauto)
	{
		blabel="AUTO";
		bstyle="white";
		bcolor="blue";
		var url ='motor.php?state=3';
		xhr.open('GET', url, false);
		xhr.send();
	}
	else
	{
		blabel="MAN";
		bstyle="#028E9B";
		bcolor="black";
		var url ='motor.php?state=2';
		xhr.open('GET', url, false);
		xhr.send();
	}
	var child=e.firstChild;
	child.style.background= bstyle;
	child.style.color= bcolor;
	child.innerHTML= blabel;
}
