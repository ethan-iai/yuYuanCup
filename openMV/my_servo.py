import time
from pyb import Servo

class MyServo:

    def __init__(self):
        self.pan = Servo(1)                         # P7
        self.tilt = Servo(2)                        # P8
        self.last_delta_pixel = 0
        self.integrator_components = [0, 0, 0]
        self.integrator = 0
        self.inte_max = 150
        self.Kp = 0.5                               # proportional gain
        self.Tt = 0.05                              # integral time constant
        self.Td = 0.05                               # derivativa time constant
        self.corresponding_angle = 0.2              # per pixel
        self.maxspeed = 128

    def init(self):
        self.last_delta_pixel = 0
        self.integrator_components = [0, 0, 0]
        self.pan.angle(0)
        self.tilt.angle(0)

    def get_integrator_value(self):
        self.integrator = 0
        for x in range(3):
            self.integrator += self.integrator_components[x]
        if self.integrator > self.inte_max:
            self.integrator = self.inte_max
        elif self.integrator < -self.inte_max:
            self.integrator = -self.inte_max

    def scan(self, count):
        if count % 2 == 0:
            self.pan.speed(self.maxspeed)
        elif count % 2 == 1:
            self.pan.speed(-self.maxspeed)
        return self.pan.speed()

    def rotate_steering_gear(self, delta_pixel):
        expected_pixel = 0
        self.integrator_components.insert(0, delta_pixel)
        self.integrator_components.pop()

        #P
        expected_pixel += self.Kp * delta_pixel

        #D
        derivative = delta_pixel - self.last_delta_pixel
        self.last_delta_pixel = delta_pixel
        expected_pixel += self.Td * derivative

        #I
        self.get_integrator_value()
        if self.integrator < -self.inte_max:
            self.integrator = -self.inte_max
        elif self.integrator > self.inte_max:
            self.integrator = self.inte_max
        expected_pixel += self.Tt * self.integrator

        self.last_delta_pixel = delta_pixel

        expected_angle = self.pan.angle() + expected_pixel * self.corresponding_angle
        if expected_angle < -90:
            expected_angle = -90
        elif expected_angle > 90:
            expected_angle = 90

        self.pan.angle(expected_angle)





