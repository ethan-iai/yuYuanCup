import sensor, image, math

class CameraAsSensor(object):

    def __init__(self, mode, color):
        self.mode = mode
        # 0: standby 1: red_LED 2: green_LED 3: red_home 4: green_home
        self.color = color
        self.thresholds = [
            (59, 100, 12, 127, -7, 33),  #(59, 100, 3, 127, -7, 33),   (64, 94, 10, 127, -7, 40)(36, 100, 28, 127, 35, 127),     # red_LED_thresholds
            (61, 100, -102, -29, -32, 24),                  #(61, 100, -102, -14, -39, 4)(36, 79, -65, -9, -13, 127) green_LED_thresholds
            (0, 30, 0, 64, -128, 0),                        # blue_LED_thresholds
            (0, 5, 1, 19, -1, 10),                          # red_home_thresholds
            (0, 7, -13, -9, 2, 10)]                         # green_home_thresholds

        # pixels_threshold = 3, area_threshold = 6, merge = True, margin = 20
        self.recognize_conditions = [(3, 6, True, 20),      # red_LED
            (3, 6, True, 20),                               # green_LED
            (3, 6, True, 20),                               # blue_LED
            (150, 150, True, False),                        # red_home
            (150, 150, True, False)]                        # green_home

    def init(self, inverse):
        sensor.reset()
        sensor.set_pixformat(sensor.RGB565)
        sensor.set_framesize(sensor.QVGA)
        sensor.skip_frames(time=1000)
        # sensor.set_brightness(0)
        # sensor.set_auto_exposure(False, 1800)          # reduce camera exposure
        sensor.set_auto_gain(False)                     # must be turned off for color tracking
        sensor.set_auto_whitebal(False)                 # must be turned off for color tracking
        if inverse == 1:
            sensor.set_vflip(True)

    def photo_taking(self):
        return sensor.snapshot()

    def recognition(self, img):

        if self.mode == 1 or self.mode == 2:            # LED_recognition(red/green)

            max_of_threshold = 0
            center_of_threshold = 0

            for blob in img.find_blobs([self.thresholds[self.mode-1]], pixels_threshold=3, area_threshold=6, merge=True, margin=20):
                img.draw_keypoints([(blob.cx(), blob.cy(), int(math.degrees(blob.rotation())))], size=20)
                if blob.area() > max_of_threshold:
                    max_of_threshold = blob.area()
                    center_of_threshold = blob.cx()

            if max_of_threshold > 0:
                return center_of_threshold

            elif max_of_threshold == 0:
                return -1

        elif self.mode == 3 or self.mode == 4:         # home_recognition(red/green)

            max_of_threshold = 0
            center_of_threshold = 0

        for blob in img.find_blobs([self.thresholds[self.mode]], pixels_threshold=150, area_threshold=150, merge=True):
            if blob.area() > max_of_threshold:
                max_of_threshold = blob.area()
                center_of_threshold = blob.cx()
                number_of_blob = 0
            if blob.elongation() > 0.5:
                img.draw_edges(blob.min_corners(), color=(255, 0, 0))
            img.draw_rectangle(blob.rect())
            img.draw_cross(blob.cx(), blob.cy())
            img.draw_keypoints([(blob.cx(), blob.cy(), int(math.degrees(blob.rotation())))], size=20)

        if max_of_threshold > 0:
            return center_of_threshold

        elif max_of_threshold == 0:
            return -1

    def find_blue(self, img):
        pass
