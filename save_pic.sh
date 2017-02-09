#!/bin/sh
#
# Script de sauvegarde d'une photo
jour=$(date +%d)
mois=$(date +%m)
annee=$(date +%Y)
heure=$(date +%H)
minute=$(date +%M)
seconde=$(date +%S)
chemin="/var/www/html/pictures/$annee-$mois-$jour-$heure:$minute:$seconde.jpg"
sudo cp /ram/pic.jpg $chemin
sudo chmod 766 $chemin
