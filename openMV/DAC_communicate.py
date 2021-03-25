from pyb import Pin, DAC

class OutputToDue(object):

    def __init__(self, op_pin):
        self.pin = op_pin
        self.dac_output = DAC(op_pin)
    
    # setting transportting:
    # range of number: 0 - 255 !!!
    def write_message(self, number):
        if number > 150:
            number = 150
        elif number < 3:
            number = 0
        self.dac_output.write(int(number))


