<?php

$state = $_GET["state"];

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
	$cmd = "sudo python /var/www/dirc_manual.py ";
	$state = "19";
	exec($cmd .$state);

}
else
{
	$cmd = "sudo python /var/www/dirc_manual.py ";
	exec($cmd .$state);
}


header("Location: index.html");

?>
