# |=|=| YOTAM Camera Code |=|=|

# ||| IMPORTS |||
import sensor, image, time, math
from pyb import UART, LED

# =+= ROBOT TOGGLE =+=
robot = 1  #0 = Yeast, 1 = Mind

# === DEBUGGING & TOGGLES (Set to false before Competitions) ===
draw_cross = True      #Draws centre cross
draw_rect = True       #Draws rectangle around blobs
draw_line = False       #Draws line from centre cross to centre of blobs
xy_coords = True       #Print the X & Y coords of the Blobs
led_flash = True       #Flashes LED quickly
print_out = False       #Prints the output values
fake_output = False     #Fakes output values
odistcent = False       #Calculates the distance to the objects on the mirror
angle_print = False     #Prints the ball angle
draw_text = False       #Draws OutBuffer onto Screen

# =+= ULTIMATE MASTER DEBUG TOGGLE INCASE WE FORGET =+=
master_debug = False     #If true it turns off all the debug options
if master_debug:
  draw_cross = False
  draw_rect = False
  draw_line = False
  xy_coords = False
  led_flash = False
  print_out = False
  fake_output = False
  bdistcent = False
  angle_print = False
  draw_text = False

# ||| DEFINES |||
centreX = 120
centreY = 120
BDistanceCentre = 0
angle = 360

# ||| THRESHOLD SETUP AND WHITEBAL ||| - (L Min, L Max, A Min, A Max, B Min, B Max)
if robot == 1: #Mind
    # ||| TABLE 11 |||
    #ball = [(43, 81, 28, 57, 19, 73)]
    #blueGoal = [(42, 56, -45, -6, -51, -18)]
    #yellowGoal = [(79, 99, -37, -1, 28, 99)]

    # ||| TABLE 12 |||
    #ball = [(47, 76, 10, 68, 3, 83)]
    #blueGoal = [(32, 45, -26, 4, -38, -19)]
    #yellowGoal = [(79, 99, -37, -1, 28, 99)]

    #Hotel Room
    ball = [(46, 72, 26, 89, 2, 68)]
    blueGoal = [(42, 56, -45, -6, -51, -18)]
    yellowGoal = [(76, 95, -33, 7, 37, 97)]


    curr_wbal = (-6.02073, -2.868481, 5.986629)
    vwin_val = (55, 0,240,240)
else: #Yeast
    #ball = [(46, 79, 14, 78, 31, 84)]
    #blueGoal = [(42, 51, -3, 25, -71, -37)]
    #yellowGoal = [(69, 100, -23, 9, 24, 87)]

    ball = [(32, 68, 27, 80, -4, 75)]#[(40, 50, 4, 38, 0, 60)]
    blueGoal = [(42, 51, -3, 25, -71, -37)]
    yellowGoal = [(47, 65, -17, 17, 47, 72)]

    curr_wbal = (-6.02073, -3.454361, 5.986629)
    vwin_val = (40, 0, 249,240)

# ||| UART SETUP |||
uart = UART(3, 9600, timeout_char = 1000)

# ||| SENSOR SETUP |||
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 1000)

# ||| GAIN |||
curr_gain = sensor.get_gain_db()
sensor.set_auto_gain(False, gain_db=curr_gain)

# ||| EXPOSURE |||
curr_exposure = sensor.get_exposure_us()
sensor.set_auto_exposure(False, exposure_us = int(curr_exposure))

# ||| WHITE BAL |||
sensor.set_auto_whitebal(False,
rgb_gain_db=curr_wbal)

# ||| SET VALUES & WINDOWING |||
sensor.set_windowing(vwin_val)
sensor.set_saturation(3)
sensor.set_brightness(3)  #Change to -3
sensor.set_contrast(3)

# ||| INDICATOR LED |||
LED(1).on()
time.sleep(100)
LED(1).off()

# ||| SCANS FOR BIGGEST BLOB |||
def BiggestBlob(bBlob):
    if not bBlob:
        return None
    maxBlob = bBlob[0]
    for blob in bBlob:
        if blob.area() > maxBlob.area():
            maxBlob = blob
    return maxBlob

# ||| MAIN LOOP |||
while(True):
    outBuffer = [255,0,0,0,0,0,0]
    img = sensor.snapshot()
    ballBlob = BiggestBlob(img.find_blobs(ball,x_stride=4,y_stride=4,pixels_threshold=20, area_thresgold=10))
    yellowBlob = BiggestBlob(img.find_blobs(yellowGoal,x_stride=15,y_stride=8,merge=True,margin=34,pixels_threshold=100))
    blueBlob = BiggestBlob(img.find_blobs(blueGoal,x_stride=15,y_stride=8,merge=True,margin=34,pixels_threshold=50))

    #Fake Outputs Debugging
    if fake_output:
        outBuffer[1] = 1
        outBuffer[2] = 2
        outBuffer[3] = 3
        outBuffer[4] = 4
        outBuffer[5] = 5
        outBuffer[6] = 6
    else:
        if ballBlob:
            outBuffer[1] = ballBlob.cx()
            outBuffer[2] = ballBlob.cy()

        if yellowBlob:
            outBuffer[3] = yellowBlob.cx()
            outBuffer[4] = yellowBlob.cy()

        if blueBlob:
            outBuffer[5] = blueBlob.cx()
            outBuffer[6] = blueBlob.cy()
    for i in outBuffer:
        try:
            uart.writechar(i)
        except Exception as X:
            print(X)

# ||| Debugging & Drawing |||
        #Draw Rectangle
        if draw_rect:
            if ballBlob != None:
                img.draw_rectangle(ballBlob.rect(),color=(255,92,0))
                img.draw_cross(ballBlob.cx(), ballBlob.cy())
                img.draw_string(ballBlob.cx(), ballBlob.cy(), str(ballBlob.code()),
                                 color=(255, 0, 0))
            if yellowBlob != None:
                img.draw_rectangle(yellowBlob.rect(),color=(255,255,0))
                img.draw_cross(yellowBlob.cx(), yellowBlob.cy())
                img.draw_string(yellowBlob.cx(), yellowBlob.cy(), str(yellowBlob.code()),
                                 color=(255, 0, 0))
            if blueBlob != None:
                img.draw_rectangle(blueBlob.rect(),color=(0,75,255))
                img.draw_cross(blueBlob.cx(), blueBlob.cy())
                img.draw_string(blueBlob.cx(), blueBlob.cy(), str(blueBlob.code()),
                                 color=(255, 0, 0))

        #Draw Line
        if draw_line:
            if ballBlob != None:
                img.draw_line((centreX, centreY, outBuffer[1], outBuffer[2]),
                                color=(255,92,0),thickness=2)
            if yellowBlob != None:
                img.draw_line((centreX, centreY, outBuffer[3], outBuffer[4]),
                                color=(255,255,0),thickness=2)
            if blueBlob != None:
                img.draw_line((centreX, centreY, outBuffer[5], outBuffer[6]),
                                color=(0,75,255),thickness=2)

        #Print X and Y Coords
        if xy_coords:
            if ballBlob != None:
                print('Ball', ballBlob.cx(), ballBlob.cy())
            if yellowBlob != None:
                print('Yellow', yellowBlob.cx(), yellowBlob.cy())
            if blueBlob != None:
                print('Blue', blueBlob.cx(), blueBlob.cy())

        #Draws Cross in Centre of Screen
        if draw_cross:
            img.draw_cross(centreX, centreY)

        #Flashes the LED quickly
        if led_flash:
            LED(2).on()
            LED(2).off()
            LED(1).on()
            LED(1).off()

        #Print ball angle
        if angle_print:
            angle = (450 - math.degrees(math.atan2(outBuffer[1] - centreX, outBuffer[2] - centreY)))- 90
            angle = ballAngle = (angle%360)
            print(angle)

        #Print OutBuffer
        if print_out:
            for i in outBuffer:
                try:
                    print(i)
                except Exception as X:
                    print(X)

        #Object Distance to Centre
        if odistcent:
            if ballBlob != None:
                BDistanceCentre = math.sqrt(((outBuffer[1]-centreX)**2) + ((outBuffer[2]-centreY)**2))
                print('Ball:',BDistanceCentre)

            if yellowBlob != None:
                YGDistanceCentre = math.sqrt(((outBuffer[3]-centreX)**2) + ((outBuffer[4]-centreY)**2))
                print('Yellow Goal:',YGDistanceCentre)

            if blueBlob != None:
                BGDistanceCentre = math.sqrt(((outBuffer[5]-centreX)**2) + ((outBuffer[6]-centreY)**2))
                print('Blue Goal:',BGDistanceCentre)

        #Prints OutBuffer onto Screen
        if draw_text:
            img.draw_string(5, 5, "S " + " ".join(str(x) for x in outBuffer[1:7]))
