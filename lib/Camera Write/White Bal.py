# Untitled - By: Henry - Sat Oct 6 2018

import sensor, image, time

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
clock = time.clock()

#sensor.set_saturation(3)
#sensor.set_brightness(3) #-3
#sensor.set_contrast(3)

sensor.set_windowing((40, 0,240,240))

while(True):
    clock.tick()
    img = sensor.snapshot()
    print(clock.fps(), \
sensor.get_rgb_gain_db())



