#!/usr/bin/python

import smbus
import time

bus = smbus.SMBus(1)
address = 0x12

while True:
	time.sleep(1.0)
	bus.write_byte(address, 8)
