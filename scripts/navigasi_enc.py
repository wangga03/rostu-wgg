#!/usr/bin/env python3

import math
import rospy
from std_msgs.msg import Float32,String

x=0
y=0
sudut = 0
datamag = 0
countmag = 0
dataen1 = 0
dataen2 = 0
count = 0
count1 = 0
sudut = 0
pre_sudut = 0
pre_enc1 = 0
pre_enc2 = 0 
sum_set_tangent = 0
dt = 0
pre_time = 0
panjang_enc2 = 20
panjang_enc1 =30
status = 'idle'

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
    dataen2 = data.data
    # rospy.loginfo(rospy.get_caller_id() + ' Nilai encoderpre_sudut 2 : %d',data.data)

def callbackmag(data):
    global datamag
    datamag = data.data

def callbackstatus(data):
    global status
    status = data.data

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
    #     elif datamag >= 360 :pre_sudut
    #         datamag = datamag - 360
    #     else : datamag = datamag

    #     count = 0
    #     countmag = 0 
        # rospy.loginfo(rospy.get_caller_id()+' data compass : %d',datamag)




def get_current_position(pre_x,pre_y):
    global dataen1,dataen2,datamag,pre_enc1,pre_enc2,pre_time,dt,pre_sudut,panjang_enc2,panjang_enc1
    current_time = rospy.get_time() 
    current_enc1 = dataen1
    current_enc2 = dataen2
    current_sudut = datamag

    # dt = (current_time - pre_time).to_sec()
    
    d_enc1 = current_enc1 - pre_enc1
    d_enc2 = current_enc2 - pre_enc2
    d_sudut = current_sudut - pre_sudut
 
    pre_enc1 = current_enc1
    pre_enc2 = current_enc2
    pre_sudut = current_sudut
    pre_time = current_time

    # x2 = set_tangent * math.cos(set_deg*3.14/180)
    # y2 = set_tangent * math.sin(set_deg*3.14/180)

    x2 = d_enc1
    y2 = d_enc2*0.95 
    sudut2 = d_sudut

    # rospy.loginfo(rospy.get_caller_id() + " x2 : %d",x2 )
    # rospy.loginfo(rospy.get_caller_id() + " y2 : %d", y2)
    # rospy.loginfo(rospy.get_caller_id() + " sudut2 : %d", sudut2)
    globalx = (x2*math.cos((45-current_sudut) * math.pi/180)- y2 *math.sin((45-current_sudut) * math.pi/180))*(-1)
    globaly = (x2*math.sin((45-current_sudut) * math.pi/180)- y2 *math.cos((45-current_sudut) * math.pi/180))*(-1)
    # current_x = pre_x + x2
    # current_y = pre_y + y2
    current_sudut = pre_sudut + sudut2
    current_x = pre_x + globalx
    current_y = pre_y - globaly

    # rospy.loginfo(rospy.get_caller_id() + " x : %d",current_x )
    # rospy.loginfo(rospy.get_caller_id() + " y : %d", current_y)
    # rospy.loginfo(rospy.get_caller_id() + " sudut: %d", current_sudut)

    return [current_x,current_y,current_sudut]


def main():
    global rate,x,y,sudut,status
    rospy.init_node('Navigation_node',anonymous=False)
    #deklarasi Sub ROS
    rospy.Subscriber('enc1',Float32,callback=callbackencx)
    rospy.Subscriber('enc2',Float32,callback=callbackeny)
    rospy.Subscriber('mag',Float32,callback=callbackmag)
    rospy.Subscriber('topic_status',String,callback=callbackstatus)


    rospy.sleep(20)


    #deklarasi Pub ROS
    pub_pos_x = rospy.Publisher('topic_position_x',Float32,queue_size=10)
    pub_pos_y = rospy.Publisher('topic_position_y',Float32,queue_size=10)
    pub_pos_yaw = rospy.Publisher('topic_position_yaw',Float32,queue_size=10)
    
    rate = rospy.Rate(10)
    while not rospy.is_shutdown():

        if (status == 'reset'):
            rospy.loginfo(rospy.get_caller_id() + ' reseting.....')
            x=0
            y=0
            sudut = 0
            rospy.sleep(1)
            rospy.loginfo(rospy.get_caller_id() + 'clear....')
            status = 'idle'
            rospy.sleep(1)


        pub_pos_x.publish(x)
        pub_pos_y.publish(y)
        pub_pos_yaw.publish(sudut)

        x,y,sudut = get_current_position(x,y)

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
