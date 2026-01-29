import RPi.GPIO as GPIO
import time

PIR_PIN = 4   # GPIO number (BCM)

GPIO.setmode(GPIO.BCM)
GPIO.setup(PIR_PIN, GPIO.IN)

print("PIR Sensor Initializing...")
time.sleep(2)
print("PIR Ready")

try:
    while True:
        if GPIO.input(PIR_PIN):
            print("Motion Detected!")
            time.sleep(1)
        else:
            print("No Motion")
            time.sleep(1)

except KeyboardInterrupt:
    print("Program stopped")

finally:
    GPIO.cleanup()
