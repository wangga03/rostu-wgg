#!/usr/bin/env python3

import cv2
import numpy as np
import time
import math
import rospy
from std_msgs.msg import Int16

cap = cv2.VideoCapture(0)
tengahx = 304
tengahy = 237
# Mengatur lebar dan tinggi frame
cap.set(3, 640)
cap.set(4, 480)
# Elliptical kernel
kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE,(3,3))

low = np.load('/home/tech-sas/catkin_ws/src/cv_basics/scripts/data1.npy')
up = np.load('/home/tech-sas/catkin_ws/src/cv_basics/scripts/data2.npy')

#publish data camera
datajarak_cam= rospy.Publisher('nilai_jrk',Int16,queue_size=10)
datasudut_cam= rospy.Publisher('nilai_sdt',Int16,queue_size=10)
datax_cam= rospy.Publisher('nilai_x',Int16,queue_size=10)
datay_cam= rospy.Publisher('nilai_y',Int16,queue_size=10)
rospy.init_node("node_camera", anonymous=False)


while(True):
    fps = cap.get(cv2.CAP_PROP_FPS)

    num_frames = 1
    start = time.time()
    for i in range(0, num_frames) :

        # Mengambil data frame dari kamera
        ret, frame = cap.read()

    # Mengkonversi frame menjadi HSV
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # Mengambil data range warna bola
    lower = low
    upper = up

    # Melakukan thresholding pada frame HSV
    thresholding = cv2.inRange(hsv, lower, upper)

    # Melakukan morfologi opening pada hasil thresholding
    opening = cv2.morphologyEx(thresholding, cv2.MORPH_OPEN, kernel)
    
    # Mencari contour pada hasil morfologi opening
    objCntr = cv2.findContours(opening.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[-2] 
    if len(objCntr) > 0:
        global xbola
        global ybola
        # Mencari contour terbesar
        c = max(objCntr, key=cv2.contourArea)
        # Membuat lingkaran terkecil yang mengelilingi bola
        ((x, y), radius) = cv2.minEnclosingCircle(c)
        
        # Mendapatkan posisi bola pada gambar
        M = cv2.moments(c)
        x = int(M["m10"] / M["m00"])
        y = int(M["m01"] / M["m00"])

        string = " " + str(x) + "," + str(y)
        
        if radius > 0:
            cv2.circle(frame, (int(x), int(y)), int(radius), (0, 0, 255), 2)
            cv2.circle(frame, (x,y), 5, (0, 255, 0), -1)
            cv2.putText(frame, string, (x,y), cv2.FONT_HERSHEY_TRIPLEX, 0.5, (0, 255, 0))
        
        x2 = tengahx - x
        y2 = y - tengahy
        
        # Jarak bola dalam frame (pixel)
        r = math.sqrt(x2**2 + y2**2)
        int(r)
        
        # Mendapatkan jarak bola terhadap robot
        if int(r) < 183:
            jarak = 0.0034*int(r)**2 + 0.056*int(r) - 3E-14
        if int(r) >= 183 and int(r) <= 210:
            jarak = 0.2062*int(r)**2 - 73.552*int(r) + 6703
        if int(r) > 210:
            jarak = 5.2466*int(r)**2 - 2222*int(r) + 235656


        # jarak -= 22W
        int(jarak)

        # Mendapatkan sudut bola
        sdt = math.atan2(y2,x2)
        sudut = math.degrees(sdt)
        sudut_real = sudut + 180

        int(sudut)

        # Mendapatkan posisi bola di lapangan
        a = 0
        b = 50
        deltax = - math.cos (sdt+math.pi)*int(jarak)
        deltay = math.sin (sdt+math.pi)*int(jarak)
        
        xbola = deltax + b
        ybola = deltay + a

        # print(f"X2:{x2}, Y2:{y2}, r:{r}, jarak:{jarak}, sdt:{sdt}, sudut:{sudut}, sudut_real:{sudut_real}, deltax:{deltax}, deltay:{deltay}")

        # int(xbola)
        # int(ybola)

        datajarak_cam.publish(int(jarak))
        datasudut_cam.publish(int(sudut_real))
        datax_cam.publish(int(xbola))
        datay_cam.publish(int(ybola))


        cv2.putText(frame, "Jarak: {}cm".format(int(jarak)), (10, frame.shape[0] - 50), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 1)
        cv2.putText(frame, "Sudut: {}derajat".format(int(sudut_real)), (10, frame.shape[0] - 30), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 1)
        cv2.putText(frame, "xbola: {}, ybola: {}".format(int(xbola), int(ybola)), (10, frame.shape[0] - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 1)
    
    elif len(objCntr) == 0:
        print("Ga ada objek")
        segala_hal = 0
        datajarak_cam.publish(segala_hal)
        datasudut_cam.publish(segala_hal)
        datax_cam.publish(segala_hal)
        datay_cam.publish(segala_hal)
    

    # Garis Bantu
    cv2.line(frame, (tengahx, 0), (tengahx, 640), color = (255, 255, 255), thickness = 1)
    cv2.line(frame, (0, tengahy), (640, tengahy), color = (255, 255, 255), thickness = 1)
    # Menggambarkan ulang frame
    cv2.imshow('frame',frame)

    end = time.time()
    seconds = end - start
    fps  = num_frames / seconds
    int(fps)
    #print("fps {0} xbola {1} ybola {2} sudut {3}".format(int(fps), int(xbola), int(ybola), int(sudut)))

    k = cv2.waitKey(5) & 0xFF
    if k == 27:
        break

cap.release()
cv2.destroyAllWindows()

