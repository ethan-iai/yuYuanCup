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
        self.Kp = 0.7                               # proportional gain
        self.Tt = 0.1                               # integral time constant
        self.Td = 0.1                               # derivativa time constant
        self.corresponding_angle = 0.5              # per pixel
        self.spin_direction = -1                    # -1 for left, 1 for right

    def init(self):
        self.last_delta_pixel = 0
        self.integrator_components = [0, 0, 0]
        self.pan.angle(0)
        self.tilt.angle(0)
        self.spin_direction = -self.spin_direction

    def get_integrator_value(self):
        self.integrator = 0
        for x in self.integrator_components:
            self.integrator += x

    def scan(self):
        if self.pan.angle() == 0:
            self.spin_direction = 1
        elif self.pan.angle() == 180:
            self.spin_direction = -1
        self.pan.speed(self.spin_direction * 100)
        return self.spin_direction

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

        expected_angle = self.pan.angle() + expected_pixel * self.corresponding_angle
        if expected_angle < 0:
            expected_angle = 0
        elif expected_angle > 180:
            expected_angle = 180

        self.pan.angle(expected_angle)





