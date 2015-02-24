<?php

$commande = $_GET["state"];
$cmd = "sudo python /var/www/robot.py ";
exec($cmd .$commande);

header("Location: index.html");

?>
