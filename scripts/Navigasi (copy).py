#!/usr/bin/env python3

import math
import rospy
from std_msgs.msg import Float32,String

x=0
y=0
datamag = 0
countmag = 0
dataen1 = 0
count = 0
count1 = 0
sudut = 0
pre_deg1 = 50
pre_tangent1 = 0


def callbackencx(data):
    global dataen1
    dataen1 = data.data

    # count1 = count1 + 1
    # if count1 == 5 : #buffer

    #     dataen1 = data.data
    #     # rospy.loginfo(rospy.get_caller_id() +" data Tangent : %d", dataen1)
    #     count1 = 0 

def callbackeny(data):
    global dataen2
    dataen2 = (data.data)

def callbackmag(data):
    global datamag
    datamag = data.data

    # flag=0
    # #buffer
    # if (count == 0 and data.data >=0 and data.data <= 90):
    #     flag = 1
    # elif (count ==0 and data.data > 360 and data.data >= 270):
    #     flag = 2
    # elif (count == 0 and data.data >90 and data.data <270):
    #     flag = 0

    # if flag == 0 :
    #     countmag = countmag + data.data

    # elif flag == 1 :
    #     if (data.data >= 180 and data.data <=360) :
    #         countmag = countmag + data.data - 360
    #     else : 
    #         countmag = countmag + data.data
    # else :
    #     if(data.data >= 0 and data.data <=180) :
    #         countmag = countmag + data.data + 360
    #     else : 
    #         countmag = countmag +data.data
    # count = count+1
    # if count == 5 : #buffer rata rata
    #     datamag = countmag/ 5
        
    #     if (datamag < 0):
    #         datamag = datamag + 360
    #     elif datamag >= 360 :
    #         datamag = datamag - 360
    #     else : datamag = datamag

    #     count = 0
    #     countmag = 0 
        # rospy.loginfo(rospy.get_caller_id()+' data compass : %d',datamag)




def get_current_position(pre_x,pre_y,pre_tangent,pre_deg):
    global datamag,dataen1, pre_deg1,pre_tangent1
    current_tangent = dataen1
    current_deg = datamag
    set_deg = current_deg - pre_deg1
    set_tangent = current_tangent - pre_tangent1
    pre_deg1 = current_deg
    pre_tangent1 = current_tangent
    rospy.loginfo(rospy.get_caller_id() + ' data perubahan sudut = %d',set_deg) 
    rospy.loginfo(rospy.get_caller_id() + ' data perubahan tangen = %d', set_tangent)   

    x2 = set_tangent * math.cos(set_deg)
    y2 = set_tangent * math.sin(set_deg)

    current_x = pre_x + x2
    current_y = pre_y + y2

    return [current_x,current_y,current_tangent,set_deg]


def main():
    global rate,x,y,sudut
    rospy.init_node('Navigation_node',anonymous=False)
    #deklarasi Sub ROS
    rospy.Subscriber('enc1',Float32,callback=callbackencx)
    rospy.Subscriber('enc2',Float32,callback=callbackeny)
    rospy.Subscriber('mag',Float32,callback=callbackmag)

    rospy.sleep(20)

    zero_deg = datamag
    tangent = dataen1
    rospy.loginfo_once(rospy.get_caller_id() + ' data Zero degree = %d',zero_deg)

    #deklarasi Pub ROS
    pub_pos_x = rospy.Publisher('topic_position_x',Float32,queue_size=10)
    pub_pos_y = rospy.Publisher('topic_position_y',Float32,queue_size=10)
    pub_pos_yaw = rospy.Publisher('topic_position_yaw',Float32,queue_size=10)
    
    rate = rospy.Rate(10)
    while not rospy.is_shutdown():
        
        pub_pos_x.publish(x)
        pub_pos_y.publish(y)
        pub_pos_yaw.publish(sudut)

        x,y,tangent,sudut = get_current_position(x,y,tangent,zero_deg)

        #rospy.loginfo(rospy.get_caller_id () + ' data navigasi = ' +  pos_str)

        # rospy.loginfo("-----------------------------------------------------------------------------------")
        # rospy.loginfo("                                                                                   ")
        # rospy.loginfo("                                                                                   ")
        rate.sleep()


if __name__ == '__main__':
    try : 
        main()
    except rospy.ROSInterruptException:
        pass