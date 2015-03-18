#!/bin/sh
#
# Script de demarage de la diffusion en streaming de la webcam

/home/pi/mjpg-streamer-code-182/mjpg-streamer/mjpg_streamer -i "/home/pi/mjpg-streamer-code-182/mjpg-streamer/input_uvc.so -d /dev/video0 -r 352x288  -f 15" -o "/home/pi/mjpg-streamer-code-182/mjpg-streamer/output_http.so -w ./www -p 8080"

