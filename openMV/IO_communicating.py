from pyb import Pin

class input_from_due:

    def __init__(self, ip_pin):
        self.pin = ip_pin
        self.io_input = Pin(ip_pin, Pin.IN, Pin.PULL_UP)

    def value(self):
        return self.io_input.value()

class control_button:

    def __init__(self, power_supply_pin, control_pin):
        self.pin = control_pin
        self.power_supply_pin = power_supply_pin
        self.operation = Pin(control_pin, Pin.IN, Pin.PULL_UP)
        self.power = Pin(power_supply_pin, Pin.OUT_PP)
        self.power.high()

    def value(self):
        return self.operation.value()
