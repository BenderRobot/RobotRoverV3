<?php
error_reporting(E_ALL | E_STRICT);

define ("NBRE_COLONNES", 4);

$tabl_liens = array();

// Parcours le répertoire courant
function liste_repertoire() {
	$dir_nom = './pictures';
	$dir = opendir($dir_nom);
	while($element = readdir($dir)) {
		if($element != '.' && $element != '..' && $element != 'f_pic.php' && $element != 'twitter.py' && $element != 'upload_dropbox.py') {
			$chemin_fichier = $dir_nom.'/'.$element;
			ajoute_lien($chemin_fichier, $element);
		}
	}
	closedir($dir);
}

// Crée le lien dans le tableau global
function ajoute_lien($chemin_image, $file) {
	// Rajoute le lien vers l'image au tableau global $GLOBALS['tabl_liens']
	$lien = '<img id="myImg" src="'.$chemin_image.'" onclick="modif(this)" width="170" height="120" alt="'.$file.'">'."\n";
	array_push($GLOBALS['tabl_liens'], $lien);
}

// Gère l'affichage du tableau $GLOBALS['tabl_liens']
function affichage() {
	$compteur = 1;
	foreach ($GLOBALS['tabl_liens'] as $val_lien) {
		if ($compteur % NBRE_COLONNES == 1) {
			echo '<br>';
		}
		echo $val_lien;
		$compteur++;
	}
}
?>
<!DOCTYPE html>
<html>
<head>
	<meta name="viewport" content="width=device-width, user-scalable=no"/>
	<meta name="apple-mobile-web-app-capable" content="yes">
	<meta name="apple-mobile-web-app-status-bar-style" content="black">
	<link rel="apple-touch-icon" href="images/touch-icon-iphone.png">
	<link rel="apple-touch-icon" sizes="76x76" href="images/touch-icon-ipad.png">
	<link href="images/startupiphone.png"
		media="(device-width: 320px)
		and (device-height: 480px)
		and (-webkit-device-pixel-ratio: 2)"
		rel="apple-touch-startup-image">
	<link media="only screen and (max-device-width: 480px)" rel="stylesheet" href="iPhone.css"/>
	<link media="only screen and (min-device-width: 481px)" rel="stylesheet" href="iPad.css"/>
	<script type='text/javascript' src="f_javascript.js"></script>
<title>Rover Bot Gallery</title>
</head>
<body>
	<div id="toolbar">
		<div id="titre_principale">
			<a>GALLERY MENU</a>
			<div id="ico_bck">
				<div href="" onclick="goBack()">
				<img id="bck" src="images/back.png" />
			</div></div>
		</div>
	</div>
	<section>
	<?php
		liste_repertoire();
		affichage();
	?>
	</section>
	<div id="myModal" class="modal">
		<span class="close"><img width="50" height="50" src="images/icon_x.png" /></span>
		<img class="modal-content" id="img01">
		<div id="caption"></div>
	</div>
	
	<div id="ico_delete">
		<img id="delete" src="images/delete_off.png" onclick="menu_pic(this)" />
	</div>
	<div id="ico_cloud">
		<img id="cloud" src="images/cloud_off.png" onclick="menu_pic(this)" />
	</div>
	<div id="ico_twit">
		<img id="twit" src="images/twit_off.png" onclick="menu_pic(this)" />
	</div>
	<div id="foot">
		<a> Copyright Reserved Bender & Co </a>
	</div>
</body>
</html>
<script>
(function(a,b,c){
		if(c in b&&b[c]){
			var d,e=a.location,f=/^(a|html)$/i;
			a.addEventListener("click",function(a){d=a.target;while(!f.test(d.nodeName))d=d.parentNode;
			"href"in d&&(d.href.indexOf("http")||~d.href.indexOf(e.host))&&(a.preventDefault(),e.href=d.href)},!1)
			}
		})(document,window.navigator,"standalone")
var param_gal = 0, del=0, cloud=0, twit=0, buttonstate=0;
var xhr = new XMLHttpRequest();
// Get the image and insert it inside the modal - use its "alt" text as a caption
var modal = document.getElementById('myModal');
var modalImg = document.getElementById("img01");
var captionText = document.getElementById("caption");
function modif(e){
	if(param_gal == 0) {
		var img = document.getElementById(e);
		modal.style.display = "block";
		modalImg.src = e.src;
		modalImg.alt = e.alt;
		captionText.innerHTML = e.alt;
	}
	else if(param_gal == 1) {
		var r = confirm("Are you sure to delete this picture?");
		if (r == true) {
			var url ='pictures/f_pic.php?state=';
			var state = 'delete';
			var pic = e.alt;
			url += state;
			url += '&picture=';
			url += pic;
			reload(1000);
			xhr.open('GET', url, false);
			xhr.send();
		} else {
			alert("You pressed Cancel!");
		}
	}
	else if(param_gal == 2) {
		var url ='pictures/f_pic.php?state=';
		var state = 'cloud';
		var pic = e.alt;
		var txt_conf = 'Are you sure to upload this picture :';
		txt_conf += pic;
		txt_conf += ', on cloud DropBox';
		var r = confirm(txt_conf);	
		if (r == true) {
			url += state;
			url += '&picture=';
			url += pic;
			reload(1000);
			xhr.open('GET', url, false);
			xhr.send();
		} else {
			alert("You pressed Cancel!");
		}
	}
	else if(param_gal == 3) {
		var url ='pictures/f_pic.php?state=';
		var state = 'tweet';
		var pic = e.alt;
		var tweet = prompt("Please enter your tweet", "tweet here");
		var txt_conf = 'Are you sure to send this picture :';
		txt_conf += pic;
		txt_conf += ', with this tweet :';
		txt_conf += tweet;
		var r = confirm(txt_conf);
		if (r == true) {
			url += state;
			url += '&picture=';
			url += pic;
			url += '&message=';
			url += tweet;
			reload(1000);
			xhr.open('GET', url, false);
			xhr.send();
		} else {
			alert("You pressed Cancel!");
		}
	}
}
function menu_pic(e) {
	var src="";
	if(e.id == "delete" && del == 0 && buttonstate == 0){ buttonstate = 1; del = 1; param_gal = 1; src = 'images/delete_on.png';}
	else if(e.id == "delete" && del == 1){ buttonstate = 0; del = 0; param_gal = 0; src = 'images/delete_off.png';}
	else if(e.id == "cloud" && cloud == 0 && buttonstate == 0){ buttonstate = 1; cloud = 1; param_gal = 2; src = 'images/cloud_on.png';}
	else if(e.id == "cloud" && cloud == 1){ buttonstate = 0; cloud = 0; param_gal = 0; src = 'images/cloud_off.png';}
	else if(e.id == "twit" && twit == 0 && buttonstate == 0){ buttonstate = 1; twit = 1; param_gal = 3; src = 'images/twit_on.png';}
	else if(e.id == "twit" && twit == 1){ buttonstate = 0; twit = 0; param_gal = 0; src = 'images/twit_off.png';}
	else{ src = e.src;}
	if(buttonstate) {
		e.src = src;
	} else {
		e.src = src;
	}
}
// Get the <span> element that closes the modal
// When the user clicks on <span> (x), close the modal
var span = document.getElementsByClassName("close")[0];
span.onclick = function() { 
    modal.style.display = "none";
}
</script>
</body>
</html>
