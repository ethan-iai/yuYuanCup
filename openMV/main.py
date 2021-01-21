import time, math
from camera_control import CameraAsSensor
from PID_external import PID
from DAC_communicate import OutputToDue
from IO_communicate import InputFromDue, Button
from my_servo import MyServo
from pyb import RTC, Timer

RED = 1
GREEN = 2
ORDERED = 1
UNORDERED = 2

mode = ORDERED

# setting PID:
pid = ()

# setting servos:
servos = ()
servos.init()

# setting timer:
rtc = RTC()
rtc.datetime((0, 0, 0, 0, 0, 0, 0, 0))

# setting input and output:
returning_pin = InputFromDue('P9')
mode_pin = InputFromDue('P5')
output_pin = OutputToDue('P6')

# setting camera:
camera = CameraAsSensor(0, RED)   # setting the color to recognize !!!
camera.init()

clock = time.clock()

while(True):
    clock.tick()
    img = camera.photo_taking()

    # read the value of returning pin:
    value_of_returning = returning_pin.value()
    if value_of_returning == 1 and camera.mode < 3:
        camera.mode += 2
        pid.clear()
    elif value_of_returning == 0 and camera.mode > 2:
        camera.mode -= 2
        pid.clear()

    #camera.mode = 1     # for debugging
    print("Camera mode = ", camera.mode)

    # read the value of mode pin:
    value_of_mode = mode_pin.value()
    if value_of_mode == 1:
        mode = UNORDERED

    #mode = 1            # for debugging
    print("Control mode = ", mode)

    center_of_target = camera.recognition(img)
    delta_pixel = 0

    if mode == UNORDERED:
        if center_of_target >= 0:
            delta_pixel = center_of_target - 160
            expected_pixel = pid.get_expected_pixel(delta_pixel)
            output_pin.write_message(expected_pixel / 2 + 100)
            print("Expected pixel: ", expected_pixel)
        else:
            pid.clear()
            output_pin.write_message(0)
            print(0)

    elif mode == ORDERED:
        if center_of_target >= 0:
            delta_pixel = center_of_target - 160
            servos.rotate_steering_gear(delta_pixel)
            expected_angle = servos.pan.angle() - 90
            output_pin.write_message(expected_angle / 2 + 100)
            print("Expected angle: ", expected_angle)
        else:
            servos.scan()
            output_pin.write_message(0)
            print(0)

    #print(clock.fps())
