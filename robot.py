#!/usr/bin/python

import smbus
import sys
import RPi.GPIO as GPIO
import time

bus = smbus.SMBus(1)
address = 0x12

GPIO.setmode(GPIO.BOARD)
trig = 8
echo = 10
GPIO.setup(trig,GPIO.OUT)
GPIO.setup(echo,GPIO.IN)
GPIO.output(trig, False)

varCommande = sys.argv[1]
commande = int(varCommande)
if commande == 14 or commande == 15:
	while commande != 15:
		bus.write_byte(address, 1)
		time.sleep(0.5)
		GPIO.output(trig, True)
		time.sleep(0.00001)
		GPIO.output(trig, False)
		while GPIO.input(echo) == 0:
			start_pulse = time.time()

		while GPIO.input(echo) == 1:
			end_pulse = time.time()

		distance = round((end_pulse - start_pulse) * 340 * 100 / 2, 1)

		if distance > 30:
			bus.write_byte(address, 4)
		elif distance >= 15 and distance <= 30:
			bus.write_byte(address, 5)
			time.sleep(1)			
		else:
			bus.write_byte(address, 6)
	
	bus.write_byte(address, 0)

else:
	bus.write_byte(address, commande)

GPIO.cleanup()
