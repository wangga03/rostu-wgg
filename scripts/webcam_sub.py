#!/usr/bin/env python3
# Description:
# - Subscribes to real-time streaming video from your built-in webcam.
#
# Author:
# - Addison Sears-Collins
# - https://automaticaddison.com
 
# Import the necessary libraries
import rospy # Python library for ROS
from std_msgs.msg import Int16
from sensor_msgs.msg import Image # Image is the message type
from cv_bridge import CvBridge # Package to convert between ROS and OpenCV Images
import cv2 # OpenCV library
import numpy as np
import math

kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE,(3,3))

low = np.array([0,200,140])
up = np.array([60,255,255])

#up = np.save('/home/datatest.npy', np.array([[1,2,3] , [4,5,6]]))

def callback(data):
   
  # Used to convert between ROS and OpenCV images
  br = CvBridge()
 
  # Output debugging information to the terminal
  #rospy.loginfo("receiving video frame")
   
  # Convert ROS Image message to OpenCV image
  current_frame = br.imgmsg_to_cv2(data)

  # Mengkonversi frame menjadi HSV
  hsv = cv2.cvtColor(current_frame, cv2.COLOR_BGR2HSV)

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
      
      #if radius > 0:
          #cv2.circle(frame, (int(x), int(y)), int(radius), (0, 0, 255), 2)
          #cv2.circle(frame, (x,y), 5, (0, 255, 0), -1)
          #cv2.putText(frame, string, (x,y), cv2.FONT_HERSHEY_TRIPLEX, 0.5, (0, 255, 0))
      
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

      #cv2.putText(frame, "Jarak: {}cm".format(int(r2)), (10, frame.shape[0] - 50), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 1)
      #cv2.putText(frame, "Sudut: {}derajat".format(int(sudut)), (10, frame.shape[0] - 30), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 1)
      #cv2.putText(frame, "xbola: {}, ybola: {}".format(int(xbola), int(ybola)), (10, frame.shape[0] - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 1)
  
  #print("{0} xbola {1} ybola {2} sudut".format(int(xbola), int(ybola), int(sudut)))

  pubx = rospy.Publisher('nilai_x2', Int16, queue_size=1)
  puby = rospy.Publisher('nilai_y2', Int16, queue_size=1)
  pubsdt = rospy.Publisher('nilai_sdt2', Int16, queue_size=1)
  pubjrk = rospy.Publisher('nilai_jrk2', Int16, queue_size=1)

  pubx.publish(int(x))
  puby.publish(int(y))
  pubsdt.publish(int(sudut))
  pubjrk.publish(int(r2))
  rospy.loginfo(int(y))
  # Display image
  #cv2.imshow("camera", hsv)
   
  cv2.waitKey(1)
      
def receive_message():
 
  # Tells rospy the name of the node.
  # Anonymous = True makes sure the node has a unique name. Random
  # numbers are added to the end of the name. 
  rospy.init_node('video_sub_py2', anonymous=False)
   
  # Node is subscribing to the video_frames topic
  rospy.Subscriber('video_frames2', Image, callback)

  # spin() simply keeps python from exiting until this node is stopped
  rospy.spin()
 
  # Close down the video stream when done
  cv2.destroyAllWindows()
  
if __name__ == '__main__':
  receive_message()
