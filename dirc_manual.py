#!/usr/bin/python

import smbus
import sys
import time

bus = smbus.SMBus(1)
address = 0x12

varCommande = sys.argv[1]
commande = int(varCommande)

if commande == 4:
	for i in range(3):
		time.sleep(0.3)
		bus.write_byte(address, 4)
		
else:
	bus.write_byte(address, commande)

