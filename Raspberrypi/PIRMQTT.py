import RPi.GPIO as GPIO
import time
import paho.mqtt.client as paho

PIR_PIN = 4  

GPIO.setmode(GPIO.BCM)
GPIO.setup(PIR_PIN, GPIO.IN)

print("PIR Sensor Initializing...")
time.sleep(2)
print("PIR Ready")

BROKER = "broker.mqttdashboard.com"
PORT = 1883
TOPIC = "GROUP14/pir"

def on_publish(client, userdata, mid):
    print("Data Published, mid:", mid)

client = paho.Client()
client.on_publish = on_publish
client.connect(BROKER, PORT)
client.loop_start()

try:
    while True:
        if GPIO.input(PIR_PIN):
            message = "Motion Detected"
            print(message)
        else:
            message = "No Motion"
            print(message)

        client.publish(TOPIC, message, qos=1)
        time.sleep(1)

except KeyboardInterrupt:
    print("Program Stopped")

finally:
    GPIO.cleanup()
    client.loop_stop()
