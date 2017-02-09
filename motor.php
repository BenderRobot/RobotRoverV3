<?php

$state = $_GET["state"];
$dir = "mddl";
if($state == 3)
{
	$cmd = "sudo /etc/init.d/dirc_auto ";
	$state = "start";
	exec($cmd .$state);
}
elseif($state == 2)
{
	$cmd = "sudo /etc/init.d/dirc_auto ";
	$state = "stop";
	exec($cmd .$state);
	$cmd = "sudo python /var/www/html/dirc_manual.py ";
	$state = "19";
	exec($cmd .$state);

}
elseif($state == 99)
{
	$cmd = "sudo sh /var/www/html/stream_cam.sh";
	exec($cmd);
}
elseif($state == 88)
{
	$cmd = "sudo sh /var/www/html/save_pic.sh";
	exec($cmd);
}
else
{
	$cmd = "sudo python /var/www/html/dirc_manual.py ";
	exec($cmd .$state);
}


header("Location: index.html");

?>
