#!/usr/bin/env python3
import rospy
from  std_msgs.msg import String


def main() :
    rospy.init_node('Kalibrasi_node',anonymous=False)
    pub_status = rospy.Publisher('topic_status',String,queue_size=10)

    rospy.sleep(2)
    hello_str = 'kalibrasi'
    pub_status.publish(hello_str)
    



if __name__ == '__main__':
    try : 
        main()
    except rospy.ROSInterruptException:
        pass