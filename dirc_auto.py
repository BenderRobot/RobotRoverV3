#!/usr/bin/python


import smbus
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
go = 0

while True:
	time.sleep(0.3)
	GPIO.output(trig, True)
	time.sleep(0.00001)
	GPIO.output(trig, False)

	while GPIO.input(echo) == 0:
		start_pulse = time.time()

	while GPIO.input(echo) == 1:
		end_pulse = time.time()

	distance = round((end_pulse - start_pulse) * 340 * 100 / 2, 1)

	if distance <= 17:
		bus.write_byte(address, 6)
		go = 0
	elif distance > 17 and distance <= 35:
		bus.write_byte(address, 5)
		time.sleep(1)
		go = 0	
	elif distance > 35 and go == 0:
		bus.write_byte(address, 4)
		go = 1
	else:
		go = go
		
GPIO.cleanup()
