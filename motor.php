<?php

$state = $_GET["state"];

if($state == 14)
{
	$cmd = "sudo /etc/init.d/dirc_auto.py ";
	$state = "start";
}
elseif($state == 15)
{
	$cmd = "sudo /etc/init.d/dirc_auto.py ";
	$state = "stop";
}
else
{
	$cmd = "sudo python /var/www/dirc_manual.py ";
}

exec($cmd .$state);

header("Location: index.html");

?>
