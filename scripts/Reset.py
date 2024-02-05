#!/usr/bin/env python3
import rospy
from  std_msgs.msg import String


def main() :
    rospy.init_node('reset_node',anonymous=False)
    pub_status = rospy.Publisher('topic_status',String,queue_size=10)

    rospy.sleep (2)

    pub_status.publish('reset')



if __name__ == '__main__':
    try : 
        main()
    except rospy.ROSInterruptException:
        pass