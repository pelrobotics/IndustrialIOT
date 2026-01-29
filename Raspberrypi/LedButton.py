import RPi.GPIO as GPIO
import time

# Pin setup
LED_PIN = 18
BUTTON_PIN = 4

GPIO.setmode(GPIO.BCM)          # Use BCM pin numbering
GPIO.setup(LED_PIN, GPIO.OUT)   # LED as output
GPIO.setup(BUTTON_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP)  # Button as input with pull-up

try:
    while True:
        button_state = GPIO.input(BUTTON_PIN)
        if button_state == GPIO.LOW:  # Button pressed
            GPIO.output(LED_PIN, GPIO.HIGH)
        else:
            GPIO.output(LED_PIN, GPIO.LOW)
        time.sleep(0.1)  # small delay to debounce
except KeyboardInterrupt:
    print("Exiting program")
finally:
    GPIO.cleanup()
