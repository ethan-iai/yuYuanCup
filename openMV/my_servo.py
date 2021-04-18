from pyb import Servo, millis
from math import pi, isnan

class MyServo:

    _kp = _ki = _kd = _integrator = _imax = 0
    _last_error = _last_derivative = _last_t = 0
    _RC = 1 / (2 * pi * 20)

    def __init__(self, p=0, i=0, d=0, imax=0):
        self.pan = Servo(1)                         # P7
        self.tilt = Servo(2)                        # P8
        self._kp = float(p)
        self._ki = float(i)
        self._kd = float(d)
        self._imax = abs(imax)
        self._last_derivative = float('nan')
        self.corresponding_angle = 0.5            # per pixel
        self.scan_speed = 240

        self._mode_angle_map = { 1 : 0, 2 : 0, }

    def init(self, mode=1, tilt_angle=0):
        # self.pan.angle(self._mode_angle_map[mode])
        self.tilt.angle(tilt_angle)

    def get_pid(self, error, scaler):
        tnow = millis()
        dt = tnow - self._last_t
        output = 0
        if self._last_t == 0 or dt > 1000:
            dt = 0
            self.pid_clear()
        self._last_t = tnow
        delta_time = float(dt) / float(1000)
        output += error * self._kp
        if abs(self._kd) > 0 and dt > 0:
            if isnan(self._last_derivative):
                derivative = 0
                self._last_derivative = 0
            else:
                derivative = (error - self._last_error) / delta_time
            derivative = self._last_derivative + ((delta_time / (self._RC + delta_time)) * (derivative - self._last_derivative))
            self._last_error = error
            self._last_derivative = derivative
            output += self._kd * derivative
        output *= scaler
        if abs(self._ki) > 0 and dt > 0:
            self._integrator += (error * self._ki) * scaler * delta_time
            if self._integrator < -self._imax:
                self._integrator = -self._imax
            elif self._integrator > self._imax:
                self._integrator = self._imax
            output += self._integrator
        return output

    def pid_clear(self):
        self._integrator = 0
        self._last_derivative = float('nan')

    def rotate_steering_gear(self, delta_pixel):
        delta_pixel = -delta_pixel
        pan_output = self.get_pid(delta_pixel, 1) / 2
        self.pan.angle(self.pan.angle() + pan_output)
        return self.pan.angle()

    def scan(self, count):
        parity = 0
        if count % 2 == 0:
            if parity == 1:
                self.pid_clear()
            parity = 0
            self.rotate_steering_gear(self.scan_speed)
        elif count % 2 == 1:
            if parity == 0:
                self.pid_clear()
            parity = 1
            self.rotate_steering_gear(-self.scan_speed)
        return self.pan.angle()
