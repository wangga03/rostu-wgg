#!/usr/bin/env python3

import rospy
from std_msgs.msg import Int16, String, UInt16, Float32, UInt8
datax = 411
datay = 240
datasdt = 280
datajrk = 100
datatof = 110
dataimu = 0
jarak = 0
p = 0
integral = 0
outw = 0
outy = 0
pre_error_sudut = 0
trigger = 0

def callbackx(data):
    global datax
    #rospy.loginfo(rospy.get_caller_id() + 'X =  %s', data.data)
    datax = data.data
def callbacky(data):
    global datay
    #rospy.loginfo(rospy.get_caller_id() + 'Y =  %s', data.data)
    datay = data.data
def callbacksdt(data):
    global datasdt
    #rospy.loginfo(rospy.get_caller_id() + 'Sdt =  %s', data.data)
    datasdt = data.data
def callbackjrk(data):
    global datajrk
    #rospy.loginfo(rospy.get_caller_id() + 'Sdt =  %s', data.data)
    datajrk = data.data
def callbacktof(data):
    global datatof
    #rospy.loginfo(rospy.get_caller_id() + 'Sdt =  %s', data.data)
    datatof = data.data
def callbackimu(data):
    global dataimu
    #rospy.loginfo(rospy.get_caller_id() + 'X =  %s', data.data)
    dataimu = data.data
def callbackx2(data):
    global datax2
    #rospy.loginfo(rospy.get_caller_id() + 'X =  %s', data.data)
    datax2 = data.data
def callbacky2(data):
    global datay2
    #rospy.loginfo(rospy.get_caller_id() + 'Y =  %s', data.data)
    datay2 = data.data
def callbacksdt2(data):
    global datasdt2
    #rospy.loginfo(rospy.get_caller_id() + 'Sdt =  %s', data.data)
    datasdt2 = data.data
def callbackjrk2(data):
    global datajrk2
    #rospy.loginfo(rospy.get_caller_id() + 'Sdt =  %s', data.data)
    datajrk2 = data.data
def callbacktof2(data):
    global datatof2
    #rospy.loginfo(rospy.get_caller_id() + 'Sdt =  %s', data.data)
    datatof2 = data.data
def callbackimu2(data):
    global dataimu2
    #rospy.loginfo(rospy.get_caller_id() + 'X =  %s', data.data)
    dataimu2 = data.data

def ngitung():
    global datasdt, p, integral, outw, pre_error_sudut

    if datasdt > 0:
        datasdt_set_point = 155
        kp = 4.5
        ki = 0.4
        kd = 2

        if datasdt >= 0 and datasdt <=90:
            datasdt = datasdt + 360
    
        error_sdt = datasdt_set_point - datasdt 
        p = (error_sdt/1000)*kp 
        integral += (error_sdt/1000)*ki 
        derivative = ((error_sdt/1000) - pre_error_sudut)*kd
        pre_error_sudut = (error_sdt/1000)
        if error_sdt <= 2 and error_sdt >= -2:
            integral = 0

        # w : kecepatan sudut
        outw = p + integral + derivative

        if outw > 0.6:
            outw = 0.6
        
        if outw < -0.6:
            outw = -0.6

    if datasdt == 0 or datasdt_set_point == 155:
        outw = 0

    # if datasdt > 270 and datasdt <=360:
    #     error_sdt = datasdt_set_point - datasdt 
    #     p = (error_sdt/1000)*kp
    #     integral += (errorsdt/1000)*ki 
    
    # if datasdt >= 0 and datasdt <=90:
    #     error_sdt = datasdt_set_point - (datasdt + 360)
    #     p = (error_sdt/1000)*kp
    #     integral += (errorsdt/1000)*ki 

    # if datasdt < 270:
    #     aw = 0.1
    
    # if datasdt >= 270:
    #     p = -0.1

def ngitung2():
    #global datax, datay, p, integral, outy, jarak
    global datajrk, outy
    

    if datajrk > 0:
        '''
        posisi_cam_x_tengah = 320.
        posisi_cam_y_tengah = 240.

        if datax > 640 and datax < 0:
            datax = 320
        if datay > 480 and datay < 0:
            datay = 240
        '''
        
        jrk_set_point = 28
        kp = 5 
        ki = 0.4
        kd = 2

        #jarak = ((datax - posisi_cam_x_tengah)**2 + (datay - posisi_cam_y_tengah)**2)**0.5 
    
        error_jrk = datajrk - jrk_set_point
        p = (error_jrk/1000)*kp 
        outy = p

    if datajrk == 0 or datajrk == 28:
        outy = 0
    # integral += (error_jrk/1000)*ki 
    # derivative = (error_jrk/1000) - pre_error_sudut
    # pre_error_sudut = (error_sdt/1000)

    # if error_sdt <= 2 and error_sdt >= -2:
    #     integral = 0

    # outw = p + integral + derivative

    # if outw > 0.6:
    #     outw = 0.6
    
    # if outw < -0.6:
    #     outw = -0.6

    # if datasdt > 270 and datasdt <=360:
    #     error_sdt = datasdt_set_point - datasdt 
    #     p = (error_sdt/1000)*kp
    #     integral += (errorsdt/1000)*ki 
    
    # if datasdt >= 0 and datasdt <=90:
    #     error_sdt = datasdt_set_point - (datasdt + 360)
    #     p = (error_sdt/1000)*kp
    #     integral += (errorsdt/1000)*ki 

    # if datasdt < 270:
    #     aw = 0.1
    
    # if datasdt >= 270:
    #     p = -0.1

def positioning():
    hello_str = "0.5 0 0" #maju
    pub.publish(hello_str)
    rospy.loginfo(hello_str)
    rospy.sleep(2)
    hello_str = "0 0.5 0" #kanan
    pub.publish(hello_str)
    rospy.loginfo(hello_str)
    rospy.sleep(3)
    hello_str = "0.5 0 0" #kanan
    pub.publish(hello_str)
    rospy.loginfo(hello_str)
    rospy.sleep(2)
    hello_str = "0 0 0" #kanan
    pub.publish(hello_str)
    rospy.loginfo(hello_str)

def dribble():
    global datajrk
    if datajrk == 28:
        db = 0
    else:
        db = 1
    pub_db.publish(db)

def kejar_bola():
    ngitung()
    ngitung2()
    dribble()
    

    hello_str = "{0} 0 {1} {2} {3} {4} {5}".format (float(outy), float(outw), int(datajrk), int(datasdt), int(datay), int(datatof))
    pub.publish(hello_str)
    rospy.loginfo(hello_str)
    #rospy.loginfo(jarak)

def charging():
    global trigger
    trigger = 10 #charging
    pub_kick.publish(trigger)
    rospy.loginfo(trigger)

def charge_stop():
    trigger = 5 #stop charging
    pub_kick.publish(trigger)
    rospy.loginfo(trigger)

def kick_kuat():
    if datatof < 60 :
        trigger = 20 #kick trigger kuat
        pub_kick.publish(trigger)
    rospy.loginfo(trigger)

def kick_lemah():
    global trigger
    if datatof < 60 :
        trigger = 30 #kick trigger lemah
        pub_kick.publish(trigger)
    rospy.loginfo(trigger)

# def test_kicker():
#     global pub_kick
#     rospy.init_node('Guidance', anonymous=False)

#     rospy.Subscriber('nilai_x', Int16, callbackx)
#     rospy.Subscriber('nilai_y', Int16, callbacky)
#     rospy.Subscriber('nilai_sdt', Int16, callbacksdt)
#     rospy.Subscriber('nilai_jrk', Int16, callbackjrk)
#     rospy.Subscriber('topic_sensor_tof', UInt16, callbacktof)
#     rospy.Subscriber('topic_sensor_imu', Float32, callbackimu)
    
#     rospy.Subscriber('nilai_x2', Int16, callbackx)
#     rospy.Subscriber('nilai_y2', Int16, callbacky)
#     rospy.Subscriber('nilai_sdt2', Int16, callbacksdt)
#     rospy.Subscriber('nilai_jrk2', Int16, callbackjrk)
#     rospy.Subscriber('topic_sensor_tof2', UInt16, callbacktof)
#     rospy.Subscriber('topic_sensor_imu2', Float32, callbackimu)

#     pub_kick = rospy.Publisher('kick_node', UInt16, queue_size=10)
#     pub_kick = rospy.Publisher('kick_node2', UInt16, queue_size=10)
#     pub = rospy.Publisher('topic_multi_data', String, queue_size=10)
#     pub = rospy.Publisher('topic_multi_data2', String, queue_size=10)

#     rate = rospy.Rate(0.1) # 10hz
#     rospy.sleep(1)
#     charging()
#     rospy.sleep(10)
#     i = 0
#     while not rospy.is_shutdown():
#         if i < 1:
#             kick_lemah()
#         if i == 1:
#             charge_stop()
#         i=i+12
#         rospy.sleep(5)

def Guidance():
    global pub, pub_kick, pub_db
    rospy.init_node('Guidance', anonymous=False)

    rospy.Subscriber('nilai_x', Int16, callbackx)
    rospy.Subscriber('nilai_y', Int16, callbacky)
    rospy.Subscriber('nilai_sdt', Int16, callbacksdt)
    rospy.Subscriber('nilai_jrk', Int16, callbackjrk)
    rospy.Subscriber('topic_sensor_tof', UInt16, callbacktof)
    rospy.Subscriber('topic_sensor_imu', Int16, callbackimu)
    
    rospy.Subscriber('nilai_x2', Int16, callbackx)
    rospy.Subscriber('nilai_y2', Int16, callbacky)
    rospy.Subscriber('nilai_sdt2', Int16, callbacksdt)
    rospy.Subscriber('nilai_jrk2', Int16, callbackjrk)
    rospy.Subscriber('topic_sensor_tof2', UInt16, callbacktof)
    rospy.Subscriber('topic_sensor_imu2', Int16, callbackimu)
    

    pub_kick = rospy.Publisher('kick_node', UInt16, queue_size=10)
    pub_kick = rospy.Publisher('kick_node2', UInt16, queue_size=10)
    #pub = rospy.Publisher('topic_multi_data', String, queue_size=10)
    pub = rospy.Publisher('topic_multi_data2', String, queue_size=10)
    pub_db = rospy.Publisher('topic_grip2', UInt8, queue_size=10)

    rate = rospy.Rate(10) # 10hz
    #charging()
    #i = 057600 baud

    # rospy.sleep(10)
    # positioning()
    rospy.sleep(3)
    while not rospy.is_shutdown():
        kejar_bola()
        # hello_str = "0 0 0 {0} {1} {2} {3} {4} {5} {6}".format (float(dataimu)/100, float(datatof), int(jarak), int(datajrk), int(datay), int(datasdt), int(datatof))
        # pub.publish(hello_str)
        # rospy.loginfo(hello_str)
        # if i < 2:
        #     kick_lemah()
        # i=i+1
        # if i == 2:
        #     charge_stop()
        # kick_lemah()
        rate.sleep()
    
    # pub_data_motor = rospy.Publisher('NUC_node', Int16, queue_size=1)
    # pub_data_motor.publish(datax)

    # spin() simply keeps python from exiting until this node is stopped

if __name__ == '__main__':
    Guidance()
    # test_kicker()
