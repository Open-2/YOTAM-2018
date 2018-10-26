# |=|=| YOTAM Camera Code |=|=| #

# ||| IMPORTS |||
import sensor, image, time, math
from pyb import UART, LED

# =+= ROBOT TOGGLE =+=
robot = 2  #1 = Yeast, 2 = Mind

camDebug = True
FPSDebug = False

centreX = 120
centreY = 120

# ||| THRESHOLD SETUP||| - (L Min, L Max, A Min, A Max, B Min, B Max)
if robot == 2:
    camThresholds = [((44, 66, 43, 83, 19, 79),),    #Ball
                     ((27, 41, -23, 5, -38, -16),),  #Blue Goal
                     ((60, 87, -88, -30, -44, 71),)] #Yellow Goal
else:
    camThresholds = [((34, 67, 57, 89, 4, 62),),     #Ball
                     ((27, 41, -23, 5, -38, -16),),  #Blue Goal
                     ((39, 81, -13, 27, 16, 67),)]   #Yellow Goal

# ||| SCANS FOR BIGGEST BLOB |||
def biggestBlob(bBlob):
    if not bBlob:
        return None
    maxBlob = bBlob[0]
    for blob in bBlob:
        if blob.area() > maxBlob.area():
            maxBlob = blob
    return maxBlob

class Sender:
    def __init__(self):
        self.uart = UART(3, 9600, timeout_char = 1000)

    def sendData(self, sendBuffer):
        self.uart.writechar(255)
        for i in sendBuffer:
            self.uart.writechar(i)
class Reader:
    def __init__(self,thresholds,debugCam=False):
        self.setupCam()

        self.thresholds = thresholds
        self.debug = debugCam

    def update(self):
        img = sensor.snapshot()

        ballBlob = self.getXY(biggestBlob(img.find_blobs(self.thresholds[0],x_stride=2,y_stride=2)))
        blueBlob = self.getXY(biggestBlob(img.find_blobs(self.thresholds[1],x_stride=15,y_stride=8,merge=True,margin=34,pixels_threshold=100)))
        yellowBlob = self.getXY(biggestBlob(img.find_blobs(self.thresholds[2],x_stride=15,y_stride=8,merge=True,margin=34,pixels_threshold=50)))

        if self.debug:
            img.draw_cross(centreX, centreY)
            if ballBlob != None:
                img.draw_cross(ballBlob[0], ballBlob[1])
                img.draw_line((centreX, centreY, ballBlob[0], ballBlob[1]),color=(255,92,0),thickness=2)
            if blueBlob != None:
                img.draw_cross(blueBlob[0], blueBlob[1])
                img.draw_line((centreX, centreY, blueBlob[0], blueBlob[1]),color=(0,75,255),thickness=2)
            if yellowBlob != None:
                img.draw_cross(yellowBlob[0], yellowBlob[1])
                img.draw_line((centreX, centreY, yellowBlob[0], yellowBlob[1]),color=(255,255,0),thickness=2)


        self.data = (ballBlob[0],ballBlob[1],blueBlob[0],blueBlob[1],yellowBlob[0],yellowBlob[1])

    def getXY(self,blob):
            return (blob.cx(),blob.cy()) if blob else (0,0)

    def getData(self):
        return self.data

    def setupCam(self):
        sensor.reset()
        sensor.set_pixformat(sensor.RGB565)
        sensor.set_framesize(sensor.QVGA)
        sensor.skip_frames(time = 1000)
        sensor.set_auto_gain(False)
        sensor.set_auto_whitebal(False)
        sensor.set_windowing((55, 0,240,240))

        sensor.set_saturation(3)
        sensor.set_brightness(-2)
        sensor.set_contrast(3)

        LED(1).on()
        time.sleep(100)
        LED(1).off()

send = Sender()
cam = Reader(camThresholds,debugCam=camDebug)

clock = time.clock()
while True:
    cam.update()
    send.sendData(cam.getData())
    if FPSDebug:
        print(clock.fps())
        clock.tick()
