from machine import Pin
from time import sleep
import esp32
led = Pin(2,Pin.OUT)
while True:
    print(esp32.hall_sensor())
    led.value(not led.value())
    sleep(0.5)