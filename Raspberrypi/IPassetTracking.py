import requests
import time
from datetime import datetime

def get_location():
    response = requests.get("http://ip-api.com/json/")
    if response.status_code == 200:
        data = response.json()
        lat = data.get("lat")
        lon = data.get("lon")
        return lat, lon
    else:
        print("Failed to get location")
        return None, None

def generate_maps_link(lat, lon):
    return f"https://www.google.com/maps?q={lat},{lon}"

# Track asset every X seconds
tracking_interval = 60  # seconds

while True:
    lat, lon = get_location()
    if lat and lon:
        maps_link = generate_maps_link(lat, lon)
        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        print(f"[{timestamp}] Latitude: {lat}, Longitude: {lon}")
        print(f"Google Maps Link: {maps_link}\n")
    time.sleep(tracking_interval)
