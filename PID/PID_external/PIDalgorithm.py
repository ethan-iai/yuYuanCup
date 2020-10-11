import math

class PID:
    def __init__(self):
        self.last_delta = 0
        self.integrator = 0
        self.inte_max = 100
        self.Kp = 0.5 #比例增益,与比例度呈倒数关系
        self.Tt = 0.5 #积分时间常数
        self.Td = 0.5 #微分时间常数
        self.expected_speed_A = 0.0
        self.expected_speed_B = 0.0
        self.expected_speed_C = 0.0
        self.expected_speed_D = 0.0
        self.maxspeed = 10.0

    def get_expected_speed(self, delta_pixel, length):
        # 估算 1 pixel 对应 0.2 度
        expected_pixel = 0
        # Propotion
        expected_pixel += self.Kp * delta_pixel
        # Derivative
        derivative = delta_pixel - self.last_delta_pixel
        self.last_delta_pixel = delta_pixel
        expected_pixel = self.Td * derivative
        # Itergrative
        self.integrator += delta_pixel
        if self.integrator < -self.inte_max:
            self.integrator = -self.inte_max
        elif self.integrator > self.inte_max:
            self.integrator = self.inte_max
        expected_pixel += self.Tt * self.integrator

        # 根据expected_pixel和length计算expected_speed

        expected_speed = 0
        return expected_speed


