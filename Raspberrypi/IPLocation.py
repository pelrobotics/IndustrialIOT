import requests

response = requests.get("http://ip-api.com/json/")
data = response.json()

lat = data["lat"]
lon = data["lon"]

maps_link = f"https://www.google.com/maps?q={lat},{lon}"

print("Latitude:", lat)
print("Longitude:", lon)
print("Google Maps Link:")
print(maps_link)
