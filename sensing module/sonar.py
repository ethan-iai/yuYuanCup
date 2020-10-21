#openmv利用超声波测距
import time,utime,pyb
from pyb import Pin

wave_echo_pin = Pin('P7', Pin.IN, Pin.PULL_NONE)
wave_trig_pin = Pin('P8', Pin.OUT_PP, Pin.PULL_DOWN)

wave_distance = 0
tim_counter = 0
flag_wave = 0

#超声波启动
def wave_start():
    wave_trig_pin.value(1)
    utime.sleep_us(15)
    wave_trig_pin.value(0)

#超声波距离计算
def wave_distance_calculation():
    #全局变量声明
    global tim_counter
    #频率f为0.2MHZ 高电平时间t=计数值*1/f
    wave_distance = tim_counter*5*0.017
    #输出最终的测量距离（单位cm）
    print('wave_distance',wave_distance)

#超声波数据处理
def wave_distance_process():
    global flag_wave
    if (flag_wave == 0):
        wave_start()
    if (flag_wave == 2):
        wave_distance_calculation()
        flag_wave = 0

#配置定时器
tim =pyb.Timer(1, prescaler=720, period=65535)  #相当于freq=0.2M

#外部中断配置
def callback(line):
    global flag_wave,tim_counter
    #上升沿触发处理
    if (wave_echo_pin.value()):
        tim.init(prescaler=720, period=65535)
        flag_wave = 1
    #下降沿
    else:
        tim.deinit()
        tim_counter = tim.counter()
        tim.counter(0)
        extint.disable()
        flag_wave = 2
#中断配置
extint = pyb.ExtInt(wave_echo_pin, pyb.ExtInt.IRQ_RISING_FALLING, pyb.Pin.PULL_DOWN, callback)

while (True):
    wave_distance_process()
    time.sleep(100)
