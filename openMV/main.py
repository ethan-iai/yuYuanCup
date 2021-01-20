import sensor, image, time, math ,pyb ,ustruct
from camera_controlling import camera_as_sensor
from PID_external import PID
from DAC_communicating import output_to_due
from IO_communicating import input_from_due, control_button
from pyb import RTC, Timer

RED = 1
GREEN = 2
pid = PID()

#setting timer:
rtc = RTC()
rtc.datetime((0, 0, 0, 0, 0, 0, 0, 0))

#setting input and output:
returning_pin = input_from_due('P9')
output_pin = output_to_due('P6')

#setting camera:
camera = camera_as_sensor(0, RED)
camera.initialization()

clock = time.clock()

while(True):
    clock.tick()
    img = camera.photo_taking()

    #read the value of returning pin
    value_of_returning = returning_pin.value()
    if value_of_returning == 1 and camera.mode < 3:
        camera.mode += 2
        pid.clear()
    elif value_of_returning == 0 and camera.mode > 2:
        camera.mode -= 2
        pid.clear()

    print("Mode = ",camera.mode)

    delta_pixel = camera.recognition(img)
    if delta_pixel > 0:
        expected_pixel = pid.get_expected_pixel(delta_pixel)
        output_pin.write_message(expected_pixel / 2 + 100)
        print("Expected pixel: ", expected_pixel)

    else:
        pid.clear()
        output_pin.write_message(0)
        print(0)

    #print(clock.fps())