class PID:

    def __init__(self):
        self.last_delta_pixel = 0
        self.integrator = 0
        self.inte_max = 100
        self.Kp = 0.5 #比例增益,与比例度呈倒数关系
        self.Tt = 0.5 #积分时间常数
        self.Td = 0.5 #微分时间常数
        #self.expected_speed_A = 0.0
        #self.expected_speed_B = 0.0
        #self.expected_speed_C = 0.0
        #self.expected_speed_D = 0.0
        #self.maxspeed = 10.0

    '''
    def velocity_function(self, dicision_coefficient):
        fun_name = "velocity_function_" + str(dicision_coefficient)
        velocity_method = getattr(self, fun_name, self.velocity_function_other)
        return velocity_method

    def velocity_function_0(self, distance_coefficient, direction_coefficient):
        self.expected_speed_A = self.expected_speed_B = self.expected_speed_C =self.expected_speed_D = self.maxspeed * distance_coefficient

    def velocity_function_1(self, distance_coefficient, direction_coefficient):
        self.expected_speed_A = self.expected_speed_D = self.maxspeed * distance_coefficient
        self.expected_speed_B = self.expected_speed_C = self.maxspeed * distance_coefficient * direction_coefficient

    def velocity_function_2(self, distance_coefficient, direction_coefficient):
        self.expected_speed_B =self.expected_speed_C = self.maxspeed * distance_coefficient
        self.expected_speed_A = self.expected_speed_D = self.maxspeed * distance_coefficient * direction_coefficient

    def velocity_function_other(self, distance_coefficient, direction_coefficient):
        pass

    def speed_culculation(self, expected_pixel, length):
        deceleration_distance = 10
        corresponding_angle = 0.2
        straight_range = 3
        distance_coefficient = (length >= deceleration_distance and 1 or (length / deceleration_distance) )
        direction_coefficient = 1 - abs(expected_pixel) * corresponding_angle / 45
        decision_coefficient = 0
        if expected_pixel > straight_range:
            decision_coefficient = 1    #右
        elif expected_pixel < -straight_range:
            decision_coefficient = 2    #左
        self.velocity_function(decision_coefficient)(distance_coefficient,direction_coefficient)
    '''

    def get_expected_pixel(self, delta_pixel):
        expected_pixel = 0
        #P
        expected_pixel += self.Kp * delta_pixel
        #D
        derivative = delta_pixel - self.last_delta_pixel
        self.last_delta_pixel = delta_pixel
        expected_pixel = self.Td * derivative
        #I
        self.integrator += delta_pixel
        if self.integrator < -self.inte_max:
            self.integrator = -self.inte_max
        elif self.integrator > self.inte_max:
            self.integrator = self.inte_max
        expected_pixel += self.Tt * self.integrator
        
        #self.speed_culculation(expected_pixel, length)
        #根据expected_pixel和length计算expected_speed

        return expected_pixel


