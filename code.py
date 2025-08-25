import cvzone 
import cv2
from cvzone.HandTrackingModule import HandDetector
from cvzone.SerialModule import SerialObject
import time  # Import the time module



cap = cv2.VideoCapture(0)
detector = HandDetector(maxHands=1, detectionCon=int(0.7))
myserial = SerialObject("COM7", 9600, 1)

while True:
    success , img = cap.read()
    img = detector.findHands(img)
    lmList, bbox = detector.findPosition(img)
    if lmList:
        fingers = detector.fingersUp()
        print(fingers)
        myserial.sendData(fingers)
        #time.sleep(0.1)
    cv2.imshow("Image",img)
    cv2.waitKey(1)