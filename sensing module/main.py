import sensor, image, time, math ,pyb ,ustruct, json
from PIDalgorithm import PID
from pyb import RTC
from pyb import UART

isReseted = 0
mode = 1
expected_speed = [0, 0, 0, 0]
length = 20
red_pid = PID()
green_pid = PID()
blue_pid = PID()
redhome_pid = PID()
greenhome_pid = PID()

uart = UART(3, 115200)

rtc = RTC()
rtc.datetime((0, 0, 0, 0, 0, 0, 0, 0))

threshold_index = 0 # 0 for red, 1 for green, 2 for blue

thresholds = [(30, 100, 15, 127, 15, 127), # generic_red_thresholds
              (30, 100, -64, -8, -32, 32), # generic_green_thresholds
              (0, 30, 0, 64, -128, 0)] # generic_blue_thresholds
thresholdsForLED = []
thresholdsForReturning = []
thresholdForFilter = (90, 100, -128, 127, -128, 127)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 1000)
sensor.set_brightness(0)
sensor.set_auto_exposure(False, 1200) #降低相机镜头曝光度
sensor.set_auto_gain(False) # must be turned off for color tracking
sensor.set_auto_whitebal(False) # must be turned off for color tracking
clock = time.clock()

while(True):
    clock.tick()
    img = sensor.snapshot()
    if rtc.datetime()[-2] == 32:
        print("Return Home!")

    if mode == 1: # Mode 1 is for red LED recognition
        #img = sensor.snapshot().binary([thresholdForFilter], invert=False, zero=True)
        #环境光滤波
        for blob in img.find_blobs([thresholds[0]], pixels_threshold=50, area_threshold=50, merge=True):
            img.draw_keypoints([(blob.cx(), blob.cy(), int(math.degrees(blob.rotation())))], size=20)
            print("Find Red Blob:", - 160 + blob.cx())
            expected_speed = red_pid.get_expected_speed(- 160 + blob.cx(), length)
            print(expected_speed)
            expected_speed_out = json.dumps(set(expected_speed))
            uart.write(expected_speed_out +'\n')

     #   for blob in img.find_blobs([thresholds[2]], pixels_threshold=50, area_threshold=50, merge=True):
     #       img.draw_keypoints([(blob.cx(), blob.cy(), int(math.degrees(blob.rotation())))], size=20)
     #       print("Find Blue Blob:", - 160 + blob.cx())

    elif mode == 2: # Mode 2 is for green LED recognition
        #img = sensor.snapshot().binary([thresholdForFilter], invert=False, zero=True)
        #环境光滤波
        for blob in img.find_blobs([thresholds[1]], pixels_threshold=50, area_threshold=50, merge=True):
            img.draw_keypoints([(blob.cx(), blob.cy(), int(math.degrees(blob.rotation())))], size=20)
            print("Find Green Blob:", - 160 + blob.cx())
            expected_speed = green_pid.get_expected_speed(- 160 + blob.cx(), length)
            print(expected_speed)
            expected_speed_out = json.dumps(set(expected_speed))
            uart.write(expected_speed_out +'\n')

     #   for blob in img.find_blobs([thresholds[2]], pixels_threshold=50, area_threshold=50, merge=True):
     #       img.draw_keypoints([(blob.cx(), blob.cy(), int(math.degrees(blob.rotation())))], size=20)
     #       print("Find Blue Blob:", - 160 + blob.cx())

    elif mode == 3: #Mode 3 is for returning home (red)
        if isReseted == 0:
            isReseted = 1
            sensor.reset()
            sensor.set_pixformat(sensor.RGB565)
            sensor.set_framesize(sensor.QVGA)
            sensor.skip_frames(time = 1000)

        for blob in img.find_blobs([thresholds[threshold_index]], pixels_threshold=200, area_threshold=200, merge=True):
            if blob.elongation() > 0.5:
                img.draw_edges(blob.min_corners(), color=(255,0,0))
            img.draw_rectangle(blob.rect())
            img.draw_cross(blob.cx(), blob.cy())
            img.draw_keypoints([(blob.cx(), blob.cy(), int(math.degrees(blob.rotation())))], size=20)
            print("Home Direction:", - 160 + blob.cx())
            expected_speed = redhome_pid.get_expected_speed(- 160 + blob.cx(), length)
            print(expected_speed)

    elif mode == 4: #Mode 4 is for returning home (green)
        if isReseted == 0:
            isReseted = 1
            sensor.reset()
            sensor.set_pixformat(sensor.RGB565)
            sensor.set_framesize(sensor.QVGA)
            sensor.skip_frames(time = 1000)

        for blob in img.find_blobs([thresholds[threshold_index+1]], pixels_threshold=200, area_threshold=200, merge=True):
            if blob.elongation() > 0.5:
                img.draw_edges(blob.min_corners(), color=(255,0,0))
            img.draw_rectangle(blob.rect())
            img.draw_cross(blob.cx(), blob.cy())
            img.draw_keypoints([(blob.cx(), blob.cy(), int(math.degrees(blob.rotation())))], size=20)
            print("Home Direction:", - 160 + blob.cx())
            expected_speed = greenhome_pid.get_expected_speed(- 160 + blox.cx(), length)
            print(expected_speed)

    #print(clock.fps())
