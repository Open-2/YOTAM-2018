## YOTAM Camera Code


import sensor, image, time
from pyb import UART, LED

robot = 1

#DEBUGGING & TOGGLES
scanning_defines = 0
draw_cross = True
draw_rect = True
draw_line = True
xy_coords = True

#DEFINES
centreX = 145 #190 #160
centreY = 115  #110 #120

# (L Min, L Max, A Min, A Max, B Min, B Max)
if robot == 1:
    ball = [(48,64,37,77,12,43)]
    blueGoal = [(0,0,0,0,0,0)]
    yellowGoal = [(0,0,0,0,0)]
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

LED(1).on()
time.sleep(100)
LED(1).off()
sensor.set_saturation(3)
sensor.set_brightness(-2)
sensor.set_contrast(0)

if scanning_defines == 1:
    def BiggestBlob(bBlob):
        maxBlob = None
        bbArea = 0

        for blob in bBlob:

          if maxBlob == None:
              maxBlob = blob
              bbArea = blob.area()
          else:
              blobArea = blob.area()

              if blobArea > bbArea:
                  maxBlob = blob
                  bbArea = blobArea

        return maxBlob
else:
    def BiggestBlob(bBlob):
        if not bBlob:
            return None
        maxBlob = bBlob[0]
        for blob in bBlob:
            if blob.area() > maxBlob.area():
                maxBlob = blob
        return maxBlob


while(True):

    outBuffer = [255,0,0,0,0,0,0]

    img = sensor.snapshot()

    ballBlob = BiggestBlob(img.find_blobs(ball))
    yellowBlob = BiggestBlob(img.find_blobs(yellowGoal,x_stride=6,y_stride=4,merge=True,margin=34,area_threshold=15))
    blueBlob = BiggestBlob(img.find_blobs(blueGoal,x_stride=6,y_stride=4,merge=True,margin=34,area_threshold=15))



    if ballBlob:
        outBuffer[1] = ballBlob.cx()
        outBuffer[2] = ballBlob.cy()

    if blueBlob:
        outBuffer[3] = blueBlob.cx()
        outBuffer[4] = blueBlob.cy()

    if yellowBlob:
        outBuffer[5] = yellowBlob.cx()
        outBuffer[6] = yellowBlob.cy()

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
            print('Ball', yellowBlob.cx(), yellowBlob.cy())

        if blueBlob != None and xy_coords:
            print('Ball', blueBlob.cx(), blueBlob.cy())

        #Draws Cross in Centre of Screen
        if draw_cross != None:
            img.draw_cross(centreX, centreY)

