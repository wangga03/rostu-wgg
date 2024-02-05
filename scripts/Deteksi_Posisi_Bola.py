import cv2
import numpy as np
import time
import math

cap = cv2.VideoCapture(0)

# Mengatur lebar dan tinggi frame
cap.set(3, 640)
cap.set(4, 480)
                                   # Elliptical kernel
kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE,(3,3))

low = np.load('data1.npy')
up = np.load('data2.npy')

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
        
        x2 = 320 - x
        y2 = y - 240
        
        # Jarak bola dalam frame (pixel)
        r = math.sqrt(x2**2 + y2**2)
        int(r)
        
        # Mendapatkan jarak bola terhadap robot
        if int(r) < 183:
            r2 = 0.0034*int(r)**2 + 0.056*int(r) - 3E-14
        if int(r) >= 183 and int(r) <= 210:
            r2 = 0.2062*int(r)**2 - 73.552*int(r) + 6703
        if int(r) > 210:
            r2 = 5.2466*int(r)**2 - 2222*int(r) + 235656

        int(r2)

        # Mendapatkan sudut bola
        sdt = math.atan2(y2,x2)
        sudut = math.degrees(sdt) + 180

        int(sudut)

        # Mendapatkan posisi bola di lapangan
        a = 0
        b = 50
        deltax = - math.cos (sdt+math.pi)*int(r2)
        deltay = math.sin (sdt+math.pi)*int(r2)
        xbola = deltax + b
        ybola = deltay + a

        int(xbola)
        int(ybola)

        cv2.putText(frame, "Jarak: {}cm".format(int(r2)), (10, frame.shape[0] - 50), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 1)
        cv2.putText(frame, "Sudut: {}derajat".format(int(sudut)), (10, frame.shape[0] - 30), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 1)
        cv2.putText(frame, "xbola: {}, ybola: {}".format(int(xbola), int(ybola)), (10, frame.shape[0] - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 1)
        
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
