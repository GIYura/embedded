import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(7, GPIO.OUT)
while True:
	print "LED ON"

	GPIO.output(7, GPIO.HIGH)
	time.sleep(1)

	print "LED OFF"

	GPIO.output(7, GPIO.LOW)
	time.sleep(1)
