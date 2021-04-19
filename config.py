from serial import Serial

_ARDUINO_PORT = "COM7"
ARD = Serial(port=_ARDUINO_PORT, baudrate=9600)