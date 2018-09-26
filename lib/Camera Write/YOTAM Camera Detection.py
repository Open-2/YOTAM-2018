## YOTAM Camera Code

import sensor, image, time, math
from pyb import UART, LED

robot = 1

#DEBUGGING & TOGGLES (Set to false before Competitions)
draw_cross = True      #Draws centre cross
draw_rect = True       #Draws rectangle around blobs
draw_line = True       #Draws line from centre cross to centre of blobs
xy_coords = True       #Print the X & Y coords of the Blobs
led_flash = True       #Flashes LED quickly
print_out = False       #Prints the output values
<<<<<<< HEAD
fake_output = True     #Fakes output values
bdistcent = True
=======
fake_output = False     #Fakes output values
bdistcent = False
>>>>>>> 7007fe6e71f3671e4b9a0b06cb6ca3c177c133c4

#DEFINES
centreX = 120
centreY = 120
BDistanceCentre = 0


# (L Min, L Max, A Min, A Max, B Min, B Max)
if robot == 1:
    ball = [(36, 62, 21, 90, 24, 74)]
    blueGoal = [(19, 32, -4, 17, -47, -26)]
    yellowGoal = [(36, 58, -8, 20, 22, 62)]

else:
    ball = [(0,0,0,0,0,0)]
    blueGoal = [(0,0,0,0,0,0)]
    yellowGoal = [(0,0,0,0,0,0)]

uart = UART(3, 9600, timeout_char = 1000)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
sensor.set_windowing((40,0,240,240))

LED(1).on()
time.sleep(100)
LED(1).off()
sensor.set_saturation(3)
sensor.set_brightness(-2)
sensor.set_contrast(0)


#SCANS FOR BIGGEST BLOB
def BiggestBlob(bBlob):
    if not bBlob:
        return None
    maxBlob = bBlob[0]
    for blob in bBlob:
        if blob.area() > maxBlob.area():
            maxBlob = blob
    return maxBlob


while(True):



    outBuffer = [255,1,1,1,1,1,1]

    img = sensor.snapshot()

    ballBlob = BiggestBlob(img.find_blobs(ball))
    yellowBlob = BiggestBlob(img.find_blobs(yellowGoal,x_stride=6,y_stride=4,merge=True,margin=34,area_threshold=15))
    blueBlob = BiggestBlob(img.find_blobs(blueGoal,x_stride=6,y_stride=4,merge=True,margin=34,area_threshold=15))

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



##Debugging & Drawing

        #Draw Rectangle
        if ballBlob != None and draw_rect:
            img.draw_rectangle(ballBlob.rect())
            img.draw_cross(ballBlob.cx(), ballBlob.cy())
            img.draw_string(ballBlob.cx(), ballBlob.cy(), str(ballBlob.code()),
                             color=(255, 0, 0))

        if yellowBlob != None and draw_rect:
            img.draw_rectangle(yellowBlob.rect())
            img.draw_cross(yellowBlob.cx(), yellowBlob.cy())
            img.draw_string(yellowBlob.cx(), yellowBlob.cy(), str(yellowBlob.code()),
                             color=(255, 0, 0))

        if blueBlob != None and draw_rect:
            img.draw_rectangle(blueBlob.rect())
            img.draw_cross(blueBlob.cx(), blueBlob.cy())
            img.draw_string(blueBlob.cx(), blueBlob.cy(), str(blueBlob.code()),
                             color=(255, 0, 0))



        #Draw Line
        if ballBlob != None and draw_line:
            img.draw_line((centreX, centreY, ballBlob.cx(), ballBlob.cy()))

        if yellowBlob != None and draw_line:
            img.draw_line((centreX, centreY, yellowBlob.cx(), yellowBlob.cy()))

        if blueBlob != None and draw_line:
            img.draw_line((centreX, centreY, blueBlob.cx(), blueBlob.cy()))


        #Print X and Y Coords
        if ballBlob != None and xy_coords:
            print('Ball', ballBlob.cx(), ballBlob.cy())

        if yellowBlob != None and xy_coords:
            print('Yellow', yellowBlob.cx(), yellowBlob.cy())

        if blueBlob != None and xy_coords:
            print('Blue', blueBlob.cx(), blueBlob.cy())


        #Draws Cross in Centre of Screen
        if draw_cross:
            img.draw_cross(centreX, centreY)


        #Flashes the LED quickly
        if led_flash:
            LED(2).on()
            LED(2).off()


        #Print OutBuffer
        if print_out:
            for i in outBuffer:
                try:
                    print(i)
                except Exception as X:
                    print(X)

        if ballBlob != None and bdistcent:
            BDistanceCentre = math.sqrt(((outBuffer[1]-120)**2) + ((outBuffer[2]-120)**2))
            print(BDistanceCentre)


