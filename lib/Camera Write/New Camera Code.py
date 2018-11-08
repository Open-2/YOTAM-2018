# Untitled - By: 24395 - Mon Nov 5 2018

import sensor, image, time, math
from pyb import UART, LED


# -+- Robot A -+- #

BALL_A = [(44, 66, 43, 83, 19, 79)]
BLUE_GOAL_A = [(42, 56, -45, -6, -51, -18)]
YELLOW_GOAL_A = [(76, 95, -33, 7, 37, 97)]

WHITE_BAL_A = (-6.02073, -4.99849, -0.1370855)

VWIN_A = (55, 0, 240, 240)
CENTRE_X_A = 91
CENTRE_Y_A = 66
MAX_RADIUS_A = 87

# -+- Robot B -+- #

BALL_B = [(16, 66, 43, 83, 19, 79)]
BLUE_GOAL_B = [(42, 56, -45, -6, -51, -18)]
YELLOW_GOAL_B = [(76, 95, -33, 7, 37, 97)]

WHITE_BAL_B = (-6.02073, -2.868481, 5.986629)

VWIN = (58, 0, 174, 164)
CENTRE_X_B = 88
CENTRE_Y_B = 85
MAX_RADIUS_B = 88


# --- Stuff to Change --- #

ROBOT = "A"

DEBUG_WHITEBALANCE = False
debug = True


# -------------- #

exec("VWIN = VWIN_" + ROBOT)
exec("CENTRE_X = CENTRE_X_" + ROBOT)
exec("CENTRE_Y = CENTRE_Y_" + ROBOT)
exec("MAX_RADIUS = MAX_RADIUS_" + ROBOT)
exec("WHITE_BAL = WHITE_BAL_" + ROBOT)
exec("BALL = BALL_" + ROBOT)
exec("BLUE_GOAL = BLUE_GOAL_" + ROBOT)
exec("YELLOW_GOAL = YELLOW_GOAL_" + ROBOT)

debugCount = 0
DEBUG_COUNT_MAX = 30

# No blob angle
NO_ANGLE = 255

# Sensor Reset
sensor.reset()

sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.set_windowing(VWIN)
sensor.skip_frames(time=100)

# White Bal #

if DEBUG_WHITEBALANCE:
    sensor.set_auto_whitebal(True)
else:
    sensor.set_auto_whitebal(False, rgb_gain_db=WHITE_BAL)

    sensor.set_brightness(0)
    sensor.set_contrast(3)
    sensor.set_saturation(2)
    sensor.set_auto_exposure(False, exposure_us=10000)
    sensor.set_auto_gain(False, gain_db=15)
    sensor.skip_frames(time=500)

uart = UART(3, 115200, timeout_char=10)

def send(data):
    uart.writechar(255)
    for i in data:
        uart.writechar(i)

def biggestBlob(bBlob):
    if not bBlob:
        return None
    maxBlob = bBlob[0]
    for blob in bBlob:
        if blob.area() > maxBlob.area():
            maxBlob = blob
    return maxBlob

def scan(orangeThreshold,blueThreshold,yellowThreshold,debug):
    img = sensor.snapshot()

    ballBlob = getCoords(biggestBlob(img.find_blobs(orangeThreshold,x_stride=2,y_stride=2)))
    blueBlob = getCoords(biggestBlob(img.find_blobs(blueThreshold,x_stride=5, y_stride=5, area_threshold=200, pixel_threshold=200, merge=True, margin=23)))
    yellowBlob = getCoords(biggestBlob(img.find_blobs(yellowThreshold,x_stride=5, y_stride=5, area_threshold=200, pixel_threshold=200, merge=True, margin=23)))

    if debug:
        img.draw_cross(CENTRE_X, CENTRE_Y)
        if ballBlob != None:
            img.draw_cross(ballBlob[0], ballBlob[1])
            img.draw_line((CENTRE_X, CENTRE_Y, ballBlob[0], ballBlob[1]),color=(255,92,0),thickness=2)
        if blueBlob != None:
            img.draw_cross(blueBlob[0], blueBlob[1])
            img.draw_line((CENTRE_X, CENTRE_Y, blueBlob[0], blueBlob[1]),color=(0,75,255),thickness=2)
        if yellowBlob != None:
            img.draw_cross(yellowBlob[0], yellowBlob[1])
            img.draw_line((CENTRE_X, CENTRE_Y, yellowBlob[0], yellowBlob[1]),color=(255,255,0),thickness=2)

    data = (ballBlob[0],ballBlob[1],blueBlob[0],blueBlob[1],yellowBlob[0],yellowBlob[1])
    return data


def getCoords(blob):
    return (blob.cx(),blob.cy()) if blob else (NO_ANGLE,NO_ANGLE)




while True:
    if DEBUG_WHITEBALANCE:
        # Print out white balance values
        debugCount += 1
        if debugCount >= DEBUG_COUNT_MAX:
            print(sensor.get_rgb_gain_db())
            debugCount = 0

    else:
            data = scan(BALL,BLUE_GOAL,YELLOW_GOAL,debug)
            send(data)





