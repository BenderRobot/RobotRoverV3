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
	$cmd = "sudo python /var/www/dirc_manual.py ";
	$state = "19";
	exec($cmd .$state);

}
elseif($state == 6 and $dir == "dwn" or $state == 6 and $dir == "mddl")
{
	$cmd = "sudo /etc/init.d/cam_up ";
	$state = "start";
	exec($cmd .$state);
	$dir = "up";
}
elseif($state == 7 and $dir == "up" or $state == 7 and $dir == "dwn")
{
	$cmd = "sudo python /var/www/dirc_manual.py ";
	exec($cmd .$state);
	$dir = "mddl";
}
elseif($state == 8 and $dir == "up" or $state == 8 and $dir == "mddl")
{
	$cmd = "sudo /etc/init.d/cam_down ";
	$state = "start";
	exec($cmd .$state);
	$dir = "dwn";
}
elseif($state == 9)
{
	if($dir == "dwn")
	{
		$cmd = "sudo /etc/init.d/cam_down ";
	}
	elseif($dir == "up")
	{
		$cmd = "sudo /etc/init.d/cam_up ";
	}
	$state = "stop";
	exec($cmd .$state);
}
else
{
	$cmd = "sudo python /var/www/dirc_manual.py ";
	exec($cmd .$state);
}


header("Location: index.html");

?>
