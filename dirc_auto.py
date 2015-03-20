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
turn = 5
count_turn = 0

def sonar():
	GPIO.output(trig, True)
	time.sleep(0.00001)
	GPIO.output(trig, False)

	while GPIO.input(echo) == 0:
		start_pulse = time.time()

	while GPIO.input(echo) == 1:
		end_pulse = time.time()

	distance = round((end_pulse - start_pulse) * 340 * 100 / 2, 1)
	return distance

while True:

	time.sleep(0.3)
	distance = sonar()
	if distance <= 17:
		bus.write_byte(address, 6)
		#print distance
		#print ' back'
		go = 0
	elif distance > 17 and distance <= 35:
		if turn == 5 and count_turn < 2:
			bus.write_byte(address, turn)
			#print distance
			#print ' turn right'
			time.sleep(1)
			count_turn += 1
		else:
			bus.write_byte(address, 7)
			#print distance
			#print ' turn left'
			time.sleep(1)
			count_turn = 0
		go = 0	
	elif distance > 35 and go == 0:
		bus.write_byte(address, 4)
		#print distance
		#print ' go'
		go = 1
	else:
		#print distance
		#print ' null'
		go = go
		
GPIO.cleanup()
