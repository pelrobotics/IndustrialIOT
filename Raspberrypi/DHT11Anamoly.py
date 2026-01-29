import Adafruit_DHT
import time
from datetime import datetime

# DHT11 setup
DHT_SENSOR = Adafruit_DHT.DHT11
DHT_PIN = 4   # GPIO number (BCM)

# Normal operating range
TEMP_MIN = 20
TEMP_MAX = 35
HUM_MIN = 30
HUM_MAX = 70

print("DHT11 Anomaly Detection Started...")
time.sleep(2)

try:
    while True:
        humidity, temperature = Adafruit_DHT.read(DHT_SENSOR, DHT_PIN)
        now = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

        if humidity is not None and temperature is not None:
            print(f"{now} | Temp: {temperature}°C | Humidity: {humidity}%")

            # Anomaly Detection
            if (temperature < TEMP_MIN or temperature > TEMP_MAX or
                humidity < HUM_MIN or humidity > HUM_MAX):
                print("⚠️ ANOMALY DETECTED: ABNORMAL ENVIRONMENT ⚠️")
            else:
                print("Environment Normal")

            print("----------------------------------")
        else:
            print("Sensor read failed")

        time.sleep(3)

except KeyboardInterrupt:
    print("Program stopped")
