import sensor, image, time, math ,pyb ,ustruct, json
from PIDalgorithm import PID
from pyb import RTC
from pyb import UART
from pyb import Pin

isReseted = 0
mode = 1    #默认识别红色，若识别绿色按下开关
#expected_speed = [0, 0, 0, 0]
#length = 20
red_pid = PID()
green_pid = PID()
blue_pid = PID()
redhome_pid = PID()
greenhome_pid = PID()

#setting io:
uart = UART(3, 115200)
button = Pin('P3', Pin.IN, Pin.PULL_UP) #开启上拉电阻

#setting timer:
rtc = RTC()
rtc.datetime((0, 0, 0, 0, 0, 0, 0, 0))

#setting thresholds:
threshold_index = 0 # 0 for red, 1 for green, 2 for blue

thresholds = [(30, 100, 15, 127, 15, 127), # generic_red_thresholds
              (30, 100, -64, -8, -32, 32), # generic_green_thresholds
              (0, 30, 0, 64, -128, 0)] # generic_blue_thresholds
thresholdsForLED = []
thresholdsForReturning = []
#thresholdForFilter = (90, 100, -128, 127, -128, 127)


#setting camera:
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
    value_of_button = button.value()
    if value_of_button == 0:
        mode = 2

    if rtc.datetime()[-3] * 60 + rtc.datetime()[-2] == 125:
        print("Return home")
        if mode == 1:
            mode = 3
        elif mode == 2:
            mode = 4
        output = 1002
        output_out = json.dumps(set(output))
        uart.write(output_out + '\n')

    if mode == 1: # Mode 1 is for red LED recognition
        #img = sensor.snapshot().binary([thresholdForFilter], invert=False, zero=True)
        #环境光滤波

        number_of_blob = 0
        for blob in img.find_blobs([thresholds[0]], pixels_threshold=50, area_threshold=50, merge=True):
            number_of_blob += 1
            img.draw_keypoints([(blob.cx(), blob.cy(), int(math.degrees(blob.rotation())))], size=20)
            print("Find Red Blob:", - 160 + blob.cx())
            red_expected_pixel = red_pid.get_expected_pixel(- 160 + blob.cx())
            print(red_expected_pixel)
            expected_pixel_out = json.dumps(set(red_expected_pixel))
            uart.write(expected_pixel_out + '\n')
        if number_of_blob == 0:
            output = 1001
            output_out = json.dumps(set(output))
            uart.write(output_out + '\n')

     #   for blob in img.find_blobs([thresholds[2]], pixels_threshold=50, area_threshold=50, merge=True):
     #       img.draw_keypoints([(blob.cx(), blob.cy(), int(math.degrees(blob.rotation())))], size=20)
     #       print("Find Blue Blob:", - 160 + blob.cx())

    elif mode == 2: # Mode 2 is for green LED recognition
        #img = sensor.snapshot().binary([thresholdForFilter], invert=False, zero=True)
        #环境光滤波

        number_of_blob = 0
        for blob in img.find_blobs([thresholds[1]], pixels_threshold=50, area_threshold=50, merge=True):
            number_of_blob += 1
            img.draw_keypoints([(blob.cx(), blob.cy(), int(math.degrees(blob.rotation())))], size=20)
            print("Find Green Blob:", - 160 + blob.cx())
            green_expected_pixel = green_pid.get_expected_pixel(- 160 + blob.cx())
            print(green_expected_pixel)
            expected_pixel_out = json.dumps(set(green_expected_pixel))
            uart.write(expected_pixel_out +'\n')
        if number_of_blob == 0:
            output = 1001
            output_out = json.dumps(set(output))
            uart.write(output_out + '\n')

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
            continue

        number_of_blob = 0
        for blob in img.find_blobs([thresholds[threshold_index]], pixels_threshold=200, area_threshold=200, merge=True):
            if blob.elongation() > 0.5:
                img.draw_edges(blob.min_corners(), color=(255,0,0))
            number_of_blob += 1
            img.draw_rectangle(blob.rect())
            img.draw_cross(blob.cx(), blob.cy())
            img.draw_keypoints([(blob.cx(), blob.cy(), int(math.degrees(blob.rotation())))], size=20)
            print("Home Direction:", - 160 + blob.cx())
            redhome_expected_pixel = redhome_pid.get_expected_pixel(- 160 + blob.cx())
            print(redhome_expected_pixel)
            expected_pixel_out = json.dumps(set(redhome_expected_pixel))
            uart.write(expected_pixel_out + '\n')
        if number_of_blob == 0:
            output = 1001
            output_out = json.dumps(set(output))
            uart.write(output_out + '\n')
        
    elif mode == 4: #Mode 4 is for returning home (green)
        if isReseted == 0:
            isReseted = 1
            sensor.reset()
            sensor.set_pixformat(sensor.RGB565)
            sensor.set_framesize(sensor.QVGA)
            sensor.skip_frames(time = 1000)
            continue

        number_of_blob = 0
        for blob in img.find_blobs([thresholds[threshold_index+1]], pixels_threshold=200, area_threshold=200, merge=True):
            if blob.elongation() > 0.5:
                img.draw_edges(blob.min_corners(), color=(255,0,0))
            number_of_blob += 1
            img.draw_rectangle(blob.rect())
            img.draw_cross(blob.cx(), blob.cy())
            img.draw_keypoints([(blob.cx(), blob.cy(), int(math.degrees(blob.rotation())))], size=20)
            print("Home Direction:", - 160 + blob.cx())
            greenhome_expected_pixel = greenhome_pid.get_expected_pixel(- 160 + blox.cx())
            print(greenhome_expected_pixel)
            expected_pixel_out = json.dumps(set(greenhome_expected_pixel))
            uart.write(expected_pixel_out + '\n')
        if number_of_blob == 0:
            output = 1001
            output_out = json.dumps(set(output))
            uart.write(output_out + '\n')

    #print(clock.fps())
