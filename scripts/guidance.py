#!/usr/bin/env python3

import rospy
import math 
import time
from std_msgs.msg import Int16, String, UInt16, Float32,_String,UInt8

x = 0
y = 0
flag =0
status ='idle'
running = 'hold'
start = 'stop'


def callbackstart(data):
    global start
    start = data.data

def callbackrunning (data) :
    global running
    running = data.data

def callbackstatus(data):
    global status 
    status = data.data

def main() : 
    global x,y,flag,status,running,start

    rospy.init_node('Node_guidance',anonymous=False)
    pub_flag = rospy.Publisher('topic_flag', Int16, queue_size=10)
    pub_target= rospy.Publisher('topic_target',String,queue_size=10)
    pub = rospy.Publisher('topic_multi_data',String,queue_size=10 )
    pub_status = rospy.Publisher('topic_status', String, queue_size=10)

    rospy.Subscriber('topic_start',String,callback=callbackstart)
    rospy.Subscriber('topic_status',String,callback=callbackstatus)
    rospy.Subscriber('topic_running', String,callback=callbackrunning)
   
    # time.sleep(1)
    # #while not rospy.is_shutdown() : 
    # target = '{0} {1}'.format(int(x),int(y))
    # pub_target.publish(target)
    # pub_flag.publish(flag)

    while not rospy.is_shutdown():
        if (start == "start"):
            if(running == 'run'):
                running = 'hold'
                pub_target.publish('-15 -180')
                pub_status.publish('posisi')
                pub_flag.publish(0)
                

                while running == 'hold':
                    if(status == 'reset') :
                        start ='stop'
                        status = 'idle'

                if (running == 'run') :
                    running = 'hold' 
                    pub_target.publish('-180 -180')
                    pub_status.publish('posisi')
                    pub_flag.publish(0)
                     

                    while running == 'hold':
                        if(status == 'reset') :
                            start ='stop'
                            status = 'idle'
                            
                    if (running == 'run'):
                        running = 'hold'
                        pub_status.publish('kejarbola')
                        pub_flag.publish(0)

                        while running == 'hold':
                            if(status == 'reset') :
                                start ='stop'
                                status = 'idle'
                    
                        if (running == 'run'):
                            running = 'hold'
                            pub_status.publish('hadap')
                            pub_flag.publish(0)

                            while running == 'hold':
                                if(status == 'reset') :
                                    start ='stop'
                                    status = 'idle'

                            if (running == 'run') :
                                    running = 'hold' 
                                    # pub_target.publish('40 -155')
                                    pub_status.publish('tendanglemah')
                                    # pub_flag.publish(0)

                                    while running == 'hold':
                                        if(status == 'reset') :
                                            start ='stop'
                                            status = 'idle'
                                    
                                    if(running == 'run'):
                                        running = 'hold'
                                        pub_target.publish('-165 -180')
                                        pub_status.publish('posisi')
                                        pub_flag.publish(0)


                                        while running == 'hold':
                                            if(status == 'reset') :
                                                start ='stop'
                                                status = 'idle'

                                        if (running == 'run'):
                                            running = 'hold'
                                            pub_status.publish('hadap')
                                            pub_flag.publish(0)

                                            while running == 'hold':
                                                if(status == 'reset') :
                                                    start ='stop'
                                                    status = 'idle'
                                            
                                            if (running == 'run'):
                                                running = 'hold' 
                                              # pub_target.publish('120 -155')
                                                pub_status.publish('arahbola')
                                                pub_flag.publish(0)

                                                while running == 'hold':
                                                    if(status == 'reset') :
                                                        start ='stop'
                                                        status = 'idle'

                                            
                                                if(running == 'run'):
                                                    running = 'hold'
                                                    pub_target.publish('-165 -180')
                                                    pub_status.publish('posisi')
                                                    pub_flag.publish(0)
                                                    while running == 'hold':
                                                        if(status == 'reset') :
                                                            start ='stop'
                                                            status = 'idle'
                                                    
                                                    if (running == 'run'):
                                                        running = 'hold'
                                                        pub_status.publish('hadap')
                                                        pub_flag.publish(0)
                                                        while running == 'hold':
                                                            if(status == 'reset') :
                                                                start ='stop'
                                                                status = 'idle'
                                                        
                                                        if (running == 'run') :
                                                            running = 'hold' 
                                                            # pub_target.publish('40 -155')
                                                            pub_status.publish('tendanglemah')
                                                            # pub_flag.publish(0)
                                                            while running == 'hold':
                                                                if(status == 'reset') :
                                                                    start ='stop'
                                                                    status = 'idle'
                                                    
                                                        start = 'stop'
    
            
    
    


        

if __name__ == '__main__':
    try : 
        main()
    except rospy.ROSInterruptException:
        pass