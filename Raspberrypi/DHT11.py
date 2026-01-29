#sudo apt update
#sudo apt install python3-pip
#pip3 install Adafruit_DHT

import Adafruit_DHT
import time

# Sensor type and GPIO
DHT_SENSOR = Adafruit_DHT.DHT11
DHT_PIN = 4   # GPIO number (BCM)

print("Reading DHT11 Sensor...")

try:
    while True:
        humidity, temperature = Adafruit_DHT.read(DHT_SENSOR, DHT_PIN)

        if humidity is not None and temperature is not None:
            print(f"Temperature: {temperature} °C")
            print(f"Humidity: {humidity} %")
            print("----------------------")
        else:
            print("Failed to read from DHT11")

        time.sleep(2)

except KeyboardInterrupt:
    print("Program stopped")
