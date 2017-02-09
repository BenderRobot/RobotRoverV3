#!/usr/bin/python

import smbus
import sys
import time
 
bus = smbus.SMBus(1)
address = 0x12

varCommande = sys.argv[1]
commande = int(varCommande)

if commande == 5:
	for i in range(3):
		time.sleep(0.3)
		bus.write_byte(address, 5)
else:
	bus.write_byte(address, commande)
	print commande

#time.sleep(0.2)
block = bus.read_byte(address)
if block != 0:
	angleT = block
	angleP = bus.read_byte(address)		

angleT = angleT - 80
angleP = angleP - 80
print angleT
print angleP
speed ""
cmd = ""
on = 0
if commande == 10:
	on = 0
	cmd = "Robot Stop"
elif commande == 11:
	on = 1
	cmd = "Robot Start"
elif commande == 19:
	cmd = "Stop"
elif commande == 20:
	cmd = "Forward"
elif commande == 21:
	cmd = "Backward"
elif commande == 22:
	cmd = "Turn left"
elif commande == 23:
	cmd = "Turn Right"
elif commande == 30:
	cmd = "Camera UP"
elif commande == 31:
	cmd = "Camera Down"
elif commande == 32:
	cmd = "Camera Left"
elif commande == 33:
	cmd = "Camera Right"
elif commande == 34:
	cmd = "Camera Middle"
elif commande >= 40:
	cmd = "Change Speed"
	if commande == 40:
		speed = "Low"
	elif commande == 41:
		speed = "Medium"
	elif commande == 41:
		speed = "High"

on = str(on)
print cmd
toWrite = [cmd, "#", str(angleT), "#", str(angleP), "#", on, "#", speed]
print toWrite
file = open("status.txt", "w")
file.write("".join(toWrite))
file.close()
