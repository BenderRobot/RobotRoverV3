#!/usr/bin/python

import smbus
import sys

bus = smbus.SMBus(1)
address = 0x12

varCommande = sys.argv[1]
commande = int(varCommande)

if commande == 30:
	for i in range(3):
		time.sleep(0.3)
		bus.write_byte(address, commande)
		
else:
	bus.write_byte(address, commande)

