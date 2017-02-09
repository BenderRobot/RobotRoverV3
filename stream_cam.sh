#!/bin/sh
#
# Script de demarage de la diffusion en streaming de la webcam

raspistill -bm --nopreview -w 640 -h 480 -q 6 -o /ram/pic.jpg -tl 200 -t 9999999 -th 0:0:0 &

LD_LIBRARY_PATH=/usr/local/lib mjpg_streamer -i "input_file.so -f /ram -n pic.jpg" -o "output_http.so -w /usr/local/www"
#/home/pi/mjpg-streamer-code-182/mjpg-streamer/mjpg_streamer -i "/home/pi/mjpg-streamer-code-182/mjpg-streamer/input_file.so -f /ram -n pic.jpg" -o "/home/pi/mjpg-streamer-code-182/mjpg-streamer/output_http.so -w /usr/local/www"

