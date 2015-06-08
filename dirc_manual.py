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
		reponse = bus.read_byte(address)
else:
	bus.write_byte(address, commande)

reponse = bus.read_byte(address)
file = open("status.txt", "w")
file.write("status :\n")
file.write(reponse)
file.close()
