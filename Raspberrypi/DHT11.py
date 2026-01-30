import RPi.GPIO as GPIO
import time

DHT_PIN = 4

GPIO.setmode(GPIO.BCM)

def read_dht11():
    data = []

    # Send start signal
    GPIO.setup(DHT_PIN, GPIO.OUT)
    GPIO.output(DHT_PIN, GPIO.LOW)
    time.sleep(0.018)  # 18 ms
    GPIO.output(DHT_PIN, GPIO.HIGH)
    time.sleep(0.00004)
    GPIO.setup(DHT_PIN, GPIO.IN)

    # Wait for response
    while GPIO.input(DHT_PIN) == 1:
        pass
    while GPIO.input(DHT_PIN) == 0:
        pass
    while GPIO.input(DHT_PIN) == 1:
        pass

    # Read 40 bits
    for i in range(40):
        while GPIO.input(DHT_PIN) == 0:
            pass
        start = time.time()
        while GPIO.input(DHT_PIN) == 1:
            pass
        duration = time.time() - start

        if duration > 0.00005:
            data.append(1)
        else:
            data.append(0)

    # Convert bits to bytes
    humidity = int("".join(str(bit) for bit in data[0:8]), 2)
    humidity_dec = int("".join(str(bit) for bit in data[8:16]), 2)
    temperature = int("".join(str(bit) for bit in data[16:24]), 2)
    temperature_dec = int("".join(str(bit) for bit in data[24:32]), 2)
    checksum = int("".join(str(bit) for bit in data[32:40]), 2)

    # Verify checksum
    if (humidity + humidity_dec + temperature + temperature_dec) & 0xFF != checksum:
        return None, None

    return temperature, humidity

try:
    while True:
        temp, hum = read_dht11()
        if temp is not None and hum is not None:
            print(f"Temperature: {temp} °C")
            print(f"Humidity: {hum} %")
            print("----------------------")
        else:
            print("Checksum error / No response")

        time.sleep(3)

except KeyboardInterrupt:
    GPIO.cleanup()

