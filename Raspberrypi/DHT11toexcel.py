import Adafruit_DHT
import time
import csv
from datetime import datetime

# DHT11 setup
DHT_SENSOR = Adafruit_DHT.DHT11
DHT_PIN = 4  # GPIO number (BCM)

# CSV file name
file_name = "dht11_data.csv"

# Create file & write header (only once)
with open(file_name, mode='a', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(["Date", "Time", "Temperature (C)", "Humidity (%)"])

print("DHT11 Data Logging Started...")

try:
    while True:
        humidity, temperature = Adafruit_DHT.read(DHT_SENSOR, DHT_PIN)
        now = datetime.now()

        if humidity is not None and temperature is not None:
            date = now.strftime("%Y-%m-%d")
            time_now = now.strftime("%H:%M:%S")

            print(f"{date} {time_now} | Temp: {temperature}C | Humidity: {humidity}%")

            with open(file_name, mode='a', newline='') as file:
                writer = csv.writer(file)
                writer.writerow([date, time_now, temperature, humidity])

        else:
            print("Failed to read DHT11")

        time.sleep(5)  # Log every 5 seconds

except KeyboardInterrupt:
    print("Data logging stopped")
