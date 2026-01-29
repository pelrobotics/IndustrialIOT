import requests
import time
from datetime import datetime

def get_asset_data():
    # Replace with real sensors if available
    response = requests.get("http://ip-api.com/json/")
    data = response.json()
    lat = data["lat"]
    lon = data["lon"]
    temperature = 75  # placeholder: replace with real sensor
    vibration = 0.5   # placeholder: replace with real sensor
    return lat, lon, temperature, vibration

def check_for_maintenance(temperature, vibration):
    if temperature > 80:
        print("⚠️ Temperature too high! Schedule maintenance.")
    if vibration > 1.0:
        print("⚠️ Vibration too high! Possible wear detected.")

while True:
    lat, lon, temp, vib = get_asset_data()
    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    print(f"[{timestamp}] Lat:{lat}, Lon:{lon}, Temp:{temp}, Vib:{vib}")
    check_for_maintenance(temp, vib)
    time.sleep(60)
