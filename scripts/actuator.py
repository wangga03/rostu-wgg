#!/usr/bin/env python3

import rospy
import math 
import time
from std_msgs.msg import Int16, String, UInt16, Float32,_String,UInt8

datax = 411
datay = 240
datasdt = 280
datajrk = 100
datatof = 110
dataimu = 0
jarak = 0
p = 0
i = 0
integral = 0
outw = 0
outy = 0
pre_error_sudut = 0
pre_yaw = 0
trigger = 0
PHI = math.pi
grip = 0
compass = 0
flag = 0
xp =0
start_pos = 0
compass_robot = 50
set_point_arah = 35
target_y = 0
target_x = 0
flag = 0
kp = 5
ki = 0
kd = 0.5
status = 'idle'

def callbackjarak(data):
    global datajrk
    datajrk = data.data
    # rospy.loginfo(rospy.get_caller_id() + 'jarak =  %s', data.data)

def callbacksudut(data):
    global datasdt
    datasdt = data.data
    #rospy.loginfo(rospy.get_caller_id() + 'sudut =  %s', data.data)

def callbackxcam(data):
    global datax
    datax = data.data
    #rospy.loginfo(rospy.get_caller_id() + 'x =  %s', data.data)

def callbackycam(data):
    global datay
    datay = data.data
    #rospy.loginfo(rospy.get_caller_id() + 'y =  %s', data.data)

def callbacktof(data):
    global datatof
    #datatof = data.data

def callbackposx (data): 
    global pos_x
    pos_x = data.data
    # rospy.loginfo(rospy.get_caller_id() + ' x =  %s', data.data)

def callbackposy (data): 
    global pos_y
    pos_y = data.data
    # rospy.loginfo(rospy.get_caller_id() + ' y =  %s', data.data)

def callbackposyaw (data): 
    global pos_yaw
    pos_yaw = data.data
    #rospy.loginfo(rospy.get_caller_id() + ' yaw =  %s', data.data)
 
def callbackmag (data): 
    global compass
    compass = data.data
    # rospy.loginfo(rospy.get_caller_id() + ' compass =  %s', data.data)

def callbackenc1 (data):
    global enc1
    enc1 = data.data

def callbacktarget(data) : 
    global target_x,target_y
    str_target = data.data
    target = str_target.split()
    target_x = int(target[0])
    target_y = int(target[1])
    flag = 0

def callbackflag(data) : 
    global flag_data, flag
    flag_data = data.data
    flag = flag_data

def callbackstatus(data):
    global status
    status = data.data
    rospy.loginfo(rospy.get_caller_id() + ' status =  %s', data.data)






def to_position():
    #posisioning 
    #robot menyerong kekanan
    # hello_str = '0 -0.5 0'
    # pub.publish(hello_str)
    # rospy.loginfo(hello_str)
    # rospy.sleep(2)
    hello_str = '0 -0.5 0'
    pub.publish(hello_str)
    rospy.loginfo(hello_str)
    rospy.sleep(2)
    hello_str = '0.5 0 0'
    pub.publish(hello_str)
    rospy.loginfo(hello_str)
    rospy.sleep(1)

    # hello_str = '0 0 0.5'
    # pub.publish(hello_str)
    # rospy.loginfo(hello_str)
    # rospy.sleep(2)
    # hello_str = '0 0 -0.5'
    # pub.publish(hello_str)
    # rospy.loginfo(hello_str)
    rospy.sleep(2)
    hello_str = '0 0 0'
    pub.publish(hello_str)
    rospy.loginfo(hello_str)
    rospy.sleep(2)



def PID_posisi2(x_target,y_target):
    global pos_x,pos_yaw,i,pre_yaw,compass,enc1,flag,xp,set_zero_compass,start_pos,pos_x,pos_y,set_point_arah
    current_x = pos_x
    current_y = pos_y
    delta_x = abs(current_x - x_target)
    delta_y = abs(current_y- y_target)
    radius = (delta_x**2 + delta_y**2)**0.5
    # zero_deg = 50
    
    sudut_target = math.atan2((y_target - current_y),(x_target-current_x))*180/math.pi
    if (sudut_target < 0) : 
       sudut_target = sudut_target + 360  

    if (sudut_target > 359) :  
        sudut_target = sudut_target - 360 
    

#PID posisi x
    kp = 8
    ki = 0
    kd = 0.5

    
    
    # if (set_point_arah >= 180 and set_point_arah <360):
    #     set_point_arah_hitung = set_point_arah - 180
    # if (compass >= 180 and compass <360) :
    #     compas_hitung = compass - 180

    # if (set_point_arah >= 0 and set_point_arah <180):
    #     set_point_arah_hitung = set_point_arah 
    # if (compass >= 0 and compass <180) :
    #     compas_hitung = compass

    yaw_error =   set_point_arah - compass
    # if (yaw_error > 180) : 
    #    yaw_error = 360 - yaw_error  

    # if (yaw_error < -180) :  
    #     yaw_error = (360 + yaw_error )
    if(abs(yaw_error)<180):
        yaw_error = abs(yaw_error)
    else : yaw_error = abs(yaw_error) - 360
    
    p = (yaw_error/1000) * kp
    i += (yaw_error/1000)* ki
    d = ((yaw_error/1000)- pre_yaw) * kd
    pre_yaw = yaw_error/1000

    yaw_pid= (p+i+d)*(-1)



    if yaw_pid > 0.6 : yaw_pid =  0.6
    if yaw_pid < -0.6 : yaw_pid = -0.6

    if (set_zero_compass <= 180):           
        set_point_arah = sudut_target + set_zero_compass
        if (set_point_arah < 0) : 
            set_point_arah = set_point_arah + 360  

        if (set_point_arah > 359) :  
            set_point_arah = set_point_arah - 360 
    if (set_zero_compass > 180):           
        set_point_arah = sudut_target - set_zero_compass
        if (set_point_arah < 0) : 
            set_point_arah = set_point_arah + 360  

        if (set_point_arah > 359) :  
            set_point_arah = set_point_arah - 360 

    if(flag == 0 ):
        # set_point_arah = compass   
        set_point_arah = set_point_arah
   
    if ((compass > set_point_arah- 90 and compass < set_point_arah +90) ) :
        flag = 1

    if(flag==1 and radius > 40):
 
        xp = 0.5

    if (flag==1 and radius <= 40) :
        xp = 0 
        # set_point_arah = set_zero_compass
        flag = 2


    hello_str = '{0} 0 {1}'.format(float(xp),float(yaw_pid))
    pub.publish(hello_str)
    pub_rad.publish(sudut_target)
    
    rospy.loginfo(rospy.get_caller_id() + ' radius : %d ', radius)
    rospy.loginfo(rospy.get_caller_id() + ' set_zero_compass : %d ', set_zero_compass)
    rospy.loginfo(rospy.get_caller_id() + ' error : %d set_point_arah : %d',yaw_error, set_point_arah)

    rospy.loginfo(hello_str)
    rospy.loginfo (rospy.get_caller_id() + 'delta x = %d delta y = %d',delta_x,delta_y)
    rospy.loginfo (rospy.get_caller_id() + 'sudut target : %d ',sudut_target)
    rospy.loginfo (rospy.get_caller_id() + 'printflag : %d ',flag)   



def PID_posisi(target):
    global pos_x,pos_yaw,i,pre_yaw,compass,enc1,flag,xp,set_zero_compass,start_pos
    
    

#PID posisi x
    kp = 15
    ki = 0
    kd = 0.5

    yaw_error =   set_zero_compass - compass
    p = (yaw_error/1000) * kp
    i += (yaw_error/1000)* ki
    d = ((yaw_error/1000)- pre_yaw) * kd
    pre_yaw = yaw_error/1000

    yaw_pid= (p+i +d)*(-1)


    if yaw_pid > 0.6 : yaw_pid =  0.6
    if yaw_pid < -0.6 : yaw_pid = -0.6

    if (enc1< target and flag == 0) :
        xp = 0.5

    if (enc1 > target and flag == 0 ) : 
        xp = 0
        flag = 1
        set_zero_compass = set_zero_compass + 90
    
    if (flag ==  1 and (compass > set_zero_compass- 3 and compass <set_zero_compass+3) ) :
        flag = 2
        start_pos = enc1

    if (flag == 2 and enc1 < start_pos +600) :
        xp = 0.5

    if (flag == 2 and enc1 > start_pos + 600):
        xp= 0 
        flag = 3
    
    if ( enc1 > start_pos + 600 and flag == 3 ) : 
        xp = 0
        flag = 4
        set_zero_compass = set_zero_compass + 135

    if (flag ==  4 and (compass > set_zero_compass- 3 and compass <set_zero_compass+3) ) :
        flag = 5
        start_pos = enc1

    if (flag == 5 and enc1 < start_pos +600) :
        xp = 0.5

    if (flag == 5 and enc1 > start_pos + 600):
        xp= 0 
        flag = 6
    
    if ( enc1 > start_pos + 600 and flag == 6 ) : 
        xp = 0
        flag = 7
        set_zero_compass = set_zero_compass - 135


    # if (flag == 1 and enc1 > target2  ) :
    #     xp = -0.5

        
    # if (flag == 1 and enc1 < target2) : 
    #     xp = 0
    #     flag == 2

    rospy.loginfo(' compas : % d, flag : %f, enc : %g', compass, flag, enc1)

    hello_str = '{0} 0 {1}'.format(float(xp),float(yaw_pid))
    pub.publish(hello_str)
    rospy.loginfo(hello_str)

        

def PID_posisi3(x_target,y_target):
    global pos_x,pos_yaw,i,pre_yaw,compass,enc1,flag,xp,set_zero_compass,start_pos,pos_x,pos_y,set_point_arah, kp, ki, kd
    current_x = pos_x
    current_y = pos_y
    delta_x = abs(current_x - x_target)
    delta_y = abs(current_y- y_target)
    radius = (delta_x**2 + delta_y**2)**0.5
    # zero_deg = 50
    
    sudut_target = math.atan2((y_target - current_y),(x_target-current_x))*180/math.pi
    if (sudut_target < 0) : 
       sudut_target = sudut_target + 360  

    if (sudut_target > 359) :  
        sudut_target = sudut_target - 360 
    

#PID posisi x


    
    
    # if (set_point_arah >= 180 and set_point_arah <360):
    #     set_point_arah_hitung = set_point_arah - 180
    # if (compass >= 180 and compass <360) :
    #     compas_hitung = compass - 180

    # if (set_point_arah >= 0 and set_point_arah <180):
    #     set_point_arah_hitung = set_point_arah 
    # if (compass >= 0 and compass <180) :
    #     compas_hitung = compass

    yaw_error =   set_point_arah - compass
    # if (yaw_error > 180) : 
    #    yaw_error = 360 - yaw_error  

    # if (yaw_error < -180) :  
    #     yaw_error = (360 + yaw_error )
    if(abs(yaw_error)<180):
        yaw_error = yaw_error
    else : yaw_error = abs(yaw_error) - 360
    
    p = (yaw_error/1000) * kp
    i += (yaw_error/1000)* ki
    d = ((yaw_error/1000)- pre_yaw) * kd
    pre_yaw = yaw_error/1000

    yaw_pid= (p+i+d)*(-1)



    if yaw_pid > 0.6 : yaw_pid =  0.6
    if yaw_pid < -0.6 : yaw_pid = -0.6


    if(flag == 0 ):
        # set_point_arah = compass   
        if (set_zero_compass <= 180):           
            set_point_arah = sudut_target + set_zero_compass
            if (set_point_arah < 0) : 
                set_point_arah = set_point_arah + 360  

            if (set_point_arah > 359) :  
                set_point_arah = set_point_arah - 360 
        set_point_arah = set_point_arah
        kp = 25
        kd = 10
    if ((compass +360 > set_point_arah- 3 +360 and compass + 360 < set_point_arah +3 +360) ) :
        flag = 1
        kp = 15
        kd = 1

    if(flag==1 and radius > 40):
        
        if (set_zero_compass <= 180):           
            set_point_arah = sudut_target + set_zero_compass
            if (set_point_arah < 0) : 
                set_point_arah = set_point_arah + 360  

            if (set_point_arah > 359) :  
                set_point_arah = set_point_arah - 360 
        if (set_zero_compass > 180):           
            set_point_arah = sudut_target - set_zero_compass
            if (set_point_arah < 0) : 
                set_point_arah = set_point_arah + 360  

            if (set_point_arah > 359) :  
                set_point_arah = set_point_arah - 360 
        xp = 0.5

    if (flag==1 and radius <= 40) :
        xp = 0 
        # set_point_arah = set_zero_compass
        flag = 2
    
    if (flag == 2 ):
        pub_running.publish('run')


    hello_str = '{0} 0 {1}'.format(float(xp),float(yaw_pid))
    pub.publish(hello_str)
    pub_rad.publish(sudut_target)
    
    # rospy.loginfo(rospy.get_caller_id() + ' radius : %d ', radius)
    # rospy.loginfo(rospy.get_caller_id() + ' set_zero_compass : %d ', set_zero_compass)
    rospy.loginfo(rospy.get_caller_id() + ' error : %d set_point_arah : %d compass : %d',yaw_error, set_point_arah,compass)

    rospy.loginfo(hello_str)
    # rospy.loginfo (rospy.get_caller_id() + 'delta x = %d delta y = %d',delta_x,delta_y)
    # rospy.loginfo (rospy.get_caller_id() + 'sudut target : %d ',sudut_target)
    # rospy.loginfo (rospy.get_caller_id() + 'printflag : %d ',flag)   

    


def ngitung():
    global datasdt, p, integral, outw, pre_error_sudut

    datasdt_set_point = 360
    kp = 5
    ki = 0
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

    outw = p + integral + derivative
    # if datasdt >= 0 and datasdt <=90:

    if outw > 0.6:
        outw = 0.6
    
    if outw < -0.6:
        outw = -0.6

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
    global datax, datay, jarak, p, integral, outy, outw
    posisi_cam_x_tengah = 320.
    posisi_cam_y_tengah = 240.

    if datax > 640 and datax < 0:
        datax = 320
    if datay > 480 and datay < 0:
        datay = 240
    
    jrk_set_point = 25
    kp = 10
    ki = 0.4
    kd = 2

    #jarak = ((datax - posisi_cam_x_tengah)**2 + (datay - posisi_cam_y_tengah)**2)**0.5 
 
    error_jrk = datajrk - jrk_set_point
    p = (error_jrk/1000)*kp 
    outy = p
    

    if(outy > 0.6) : outy = 0.6
    if(outy < -0.6) : outy = -0.6
    if(outw <0.1 and outw >0.1) outy = 0
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
    #     p = -0.1running = 'hold'

def kejar_bola():
    ulang = True
    start_timer = time.time()
    while(ulang):
        if (status == 'reset'): ulang = False
        end_timer = time.time()
        count = end_timer - start_timer

        if(count > 8 and outy < 0.15) : ulang = False
        if(outy < 0.2) : ambil_bola()
        if (outy >= 0.2) : stop_bola()
        ngitung()
        ngitung2()
        hello_str = "{0} 0 {1}".format (float(outy), float(outw))

        rospy.loginfo(rospy.get_caller_id()+' '+hello_str)

        pub.publish(hello_str)
        rospy.loginfo(hello_str)

def arah_bola():
    ulang = True
    start_timer = time.time()
    while(ulang):
        if (status == 'reset'): ulang = False
        end_timer = time.time()
        count = end_timer - start_timer

        if(count > 8 and outy < 0.1) : ulang = False
        if(outy < 0.2) : ambil_bola()
        if (outy >= 0.2) : stop_bola()
        ngitung()
        ngitung2()
        hello_str = "0 0 {0}".format (float(outw))

        rospy.loginfo(rospy.get_caller_id()+' '+hello_str)

        pub.publish(hello_str)
        rospy.loginfo(hello_str)


def hadap(target_mag):
    global compass 
    error_mag = target_mag - compass
    if(abs(error_mag)<180):
        error_mag = error_mag
    else : error_mag = abs(error_mag) - 360

    hello_str = '0 0 {0}'.format(float(error_mag))
    pub.publish(hello_str)


def tendang():
    charge()
    rospy.sleep(1)
    charge_stop()
    rospy.sleep(1)
    kick()

def ambil_bola():
    global grip
    grip = 1
    grip_pub.publish(grip)
    rospy.loginfo(grip)
    
def stop_bola():
    global grip
    grip = 0
    grip_pub.publish(grip)
    rospy.loginfo(grip)

def stop_motor():
    hello_str = '0 0 0'
    pub.publish(hello_str)
    rospy.loginfo(hello_str)
    stop_bola()

def charge():
    global trigger
    trigger = 10
    kick_pub.publish(trigger)
    rospy.loginfo(trigger)

def charge_stop():
    trigger = 5
    kick_pub.publish(trigger)
    rospy.loginfo(trigger)

def kick():
    global trigger
    trigger = 20
    kick_pub.publish(trigger)
    rospy.loginfo(trigger)


def sub_inisiasi() :
    global pub,pub_rad
    global rate
    global kick_pub
    global grip_pub,set_zero_compass,target_x,target_y,status,pub_running
    rospy.init_node('Node_Actuator', anonymous=False)
    rospy.Subscriber('jarak_cam',Int16,callback=callbackjarak)
    rospy.Subscriber('sudut_cam',Int16,callback=callbacksudut)
    rospy.Subscriber('x_cam',Int16,callback=callbackxcam)
    rospy.Subscriber('y_cam',Int16,callback=callbackycam)
    rospy.Subscriber('topic_sensor_tof',UInt16,callback=callbacktof)
    rospy.Subscriber('topic_position_x',Float32,callback=callbackposx)
    rospy.Subscriber('topic_position_y',Float32,callback=callbackposy)
    rospy.Subscriber('topic_position_yaw',Float32,callback=callbackposyaw)
    rospy.Subscriber('mag',Float32,callback=callbackmag)
    rospy.Subscriber('enc1',Float32,callback=callbackenc1)
    rospy.Subscriber('topic_target',String,callbacktarget)
    rospy.Subscriber('topic_flag',Int16,callbackflag)
    rospy.Subscriber('topic_status',String,callbackstatus)
    

    # rospy.Subscriber('enc2',Float32,callback=callbackeny)
    # rospy.Subscriber('mag',Float32,callback=callbackmag)

    pub_rad = rospy.Publisher('topic_rad',Float32, queue_size=10)
    kick_pub = rospy.Publisher('topic_kick',UInt8, queue_size=10)
    grip_pub = rospy.Publisher('topic_grip', UInt8, queue_size=10)
    pub = rospy.Publisher('topic_multi_data', String, queue_size=10)
    pub_running = rospy.Publisher('topic_running', String, queue_size=10)
    rate= rospy.Rate(10)
    rospy.sleep(30)

    set_zero_compass = 35
    
    
    # to_position()
    #kejar_bola()
    #stop_motor()
    #tendang()
    while not rospy.is_shutdown():
        # kejar_bola()
        # rospy.loginfo(rospy.get_caller_id() + status)
        if (status == 'idle'):
            hello_str = '0 0 0'
            pub.publish(hello_str)

        if (status == 'kalibrasi') :
            rospy.loginfo(rospy.get_caller_id() + 'Sedang Mengkalibrasi Magnet...')
            hello_str = '0 0 0.5'
            pub.publish(hello_str)
            rospy.sleep(5)
            rospy.loginfo(rospy.get_caller_id() + 'Kalibrasi Selesai!')
            status = 'idle'
        
        if (status == 'reset'):
            rospy.sleep(1)
            stop_bola()
            status = 'idle'

        
        if (status == 'posisi') :
            PID_posisi3(target_x,target_y)
        
        if(status == 'tendanglemah'):
            charge()
            rospy.sleep(5)
            charge_stop()
            rospy.sleep(1)
            kick()
            pub_running.publish('run')
            status='idle'
            
        if(status == 'tendangkuat'):
            charge()
            rospy.sleep(7)
            charge_stop()
            rospy.sleep(1)
            kick()
            pub_running.publish('run')
            status='idle'

        if (status == 'kejarbola'):
            kejar_bola()
            pub_running.publish('run')
            status = 'idle'
        
        if (status == 'arahbola'):
            arah_bola()
            pub_running.publish('run')
            status = 'idle'


        # if (status == 'arah'):
        #     posisi_arah()
        
        #PID_posisi(600)
        # PID_posisi3(100,100)
       # kejar_bola()
        #kick()
        #rospy.sleep(2)

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

        
def main():
    sub_inisiasi()

if __name__ == '__main__':
    try : 
        main()
    except rospy.ROSInterruptException:
        pass
    ki = 0
    kd = 0.5
