class PID:

    def __init__(self):
        self.last_delta_pixel = 0
        self.integrator_components = [0, 0, 0]
        self.integrator = 0
        self.inte_max = 150
        self.Kp = 0.6 #比例增益,与比例度呈倒数关系
        self.Tt = 0.1 #积分时间常数
        self.Td = 0.5 #微分时间常数

    def clear(self):
        self.last_delta_pixel = 0
        self.integrator_components = [0, 0, 0]

    def get_integrator_value(self):
        self.integrator = 0
        for x in self.integrator_components:
            self.integrator += x

    def get_expected_pixel(self, delta_pixel):

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

        return expected_pixel
