<?php

$state = $_GET["state"];

if($state == 14)
{
	$cmd = "sudo /etc/init.d/dirc_auto ";
	$state = "start";
	exec($cmd .$state);
}
elseif($state == 15)
{
	$cmd = "sudo /etc/init.d/dirc_auto ";
	$state = "stop";
	exec($cmd .$state);
	$cmd = "sudo python /var/www/dirc_manual.py ";
	$state = "8";
	exec($cmd .$state);

}
else
{
	$cmd = "sudo python /var/www/dirc_manual.py ";
	exec($cmd .$state);
}


header("Location: index.html");

?>
