# piot-home
Raspberry PI IOT Home Automation.

Raspberry PI tasks
- collects data from all sensors
- display data from sensor to LCD display
- publish data using MQTT to server
- react to rotary encoder rotation events (navigate on display)
- react to rotary encoder button events (perform actions)
- communicate with Arduino (act as remote terminal) using serial protocol
## Todo
Rotary encoder interrupts:
- button pressed
  - sleep mode -> turn on display, show current status of sensors
  - other -> TBD
- rotated
  - sleep mode - turn on display, show current status of sensors

Serial
- periodically get sensor value 
