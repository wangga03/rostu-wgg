#ifndef _ROS_robotic_sas_auv_ros_Actuator_h
#define _ROS_robotic_sas_auv_ros_Actuator_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace robotic_sas_auv_ros
{

  class Actuator : public ros::Msg
  {
    public:
      typedef float _thruster_1_type;
      _thruster_1_type thruster_1;
      typedef float _thruster_2_type;
      _thruster_2_type thruster_2;
      typedef float _thruster_3_type;
      _thruster_3_type thruster_3;
      typedef float _thruster_4_type;
      _thruster_4_type thruster_4;
      typedef float _thruster_5_type;
      _thruster_5_type thruster_5;
      typedef float _thruster_6_type;
      _thruster_6_type thruster_6;
      typedef float _thruster_7_type;
      _thruster_7_type thruster_7;
      typedef float _thruster_8_type;
      _thruster_8_type thruster_8;

    Actuator():
      thruster_1(0),
      thruster_2(0),
      thruster_3(0),
      thruster_4(0),
      thruster_5(0),
      thruster_6(0),
      thruster_7(0),
      thruster_8(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_thruster_1;
      u_thruster_1.real = this->thruster_1;
      *(outbuffer + offset + 0) = (u_thruster_1.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_thruster_1.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_thruster_1.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_thruster_1.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->thruster_1);
      union {
        float real;
        uint32_t base;
      } u_thruster_2;
      u_thruster_2.real = this->thruster_2;
      *(outbuffer + offset + 0) = (u_thruster_2.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_thruster_2.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_thruster_2.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_thruster_2.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->thruster_2);
      union {
        float real;
        uint32_t base;
      } u_thruster_3;
      u_thruster_3.real = this->thruster_3;
      *(outbuffer + offset + 0) = (u_thruster_3.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_thruster_3.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_thruster_3.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_thruster_3.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->thruster_3);
      union {
        float real;
        uint32_t base;
      } u_thruster_4;
      u_thruster_4.real = this->thruster_4;
      *(outbuffer + offset + 0) = (u_thruster_4.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_thruster_4.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_thruster_4.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_thruster_4.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->thruster_4);
      union {
        float real;
        uint32_t base;
      } u_thruster_5;
      u_thruster_5.real = this->thruster_5;
      *(outbuffer + offset + 0) = (u_thruster_5.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_thruster_5.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_thruster_5.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_thruster_5.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->thruster_5);
      union {
        float real;
        uint32_t base;
      } u_thruster_6;
      u_thruster_6.real = this->thruster_6;
      *(outbuffer + offset + 0) = (u_thruster_6.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_thruster_6.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_thruster_6.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_thruster_6.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->thruster_6);
      union {
        float real;
        uint32_t base;
      } u_thruster_7;
      u_thruster_7.real = this->thruster_7;
      *(outbuffer + offset + 0) = (u_thruster_7.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_thruster_7.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_thruster_7.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_thruster_7.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->thruster_7);
      union {
        float real;
        uint32_t base;
      } u_thruster_8;
      u_thruster_8.real = this->thruster_8;
      *(outbuffer + offset + 0) = (u_thruster_8.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_thruster_8.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_thruster_8.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_thruster_8.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->thruster_8);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_thruster_1;
      u_thruster_1.base = 0;
      u_thruster_1.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_thruster_1.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_thruster_1.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_thruster_1.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->thruster_1 = u_thruster_1.real;
      offset += sizeof(this->thruster_1);
      union {
        float real;
        uint32_t base;
      } u_thruster_2;
      u_thruster_2.base = 0;
      u_thruster_2.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_thruster_2.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_thruster_2.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_thruster_2.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->thruster_2 = u_thruster_2.real;
      offset += sizeof(this->thruster_2);
      union {
        float real;
        uint32_t base;
      } u_thruster_3;
      u_thruster_3.base = 0;
      u_thruster_3.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_thruster_3.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_thruster_3.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_thruster_3.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->thruster_3 = u_thruster_3.real;
      offset += sizeof(this->thruster_3);
      union {
        float real;
        uint32_t base;
      } u_thruster_4;
      u_thruster_4.base = 0;
      u_thruster_4.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_thruster_4.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_thruster_4.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_thruster_4.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->thruster_4 = u_thruster_4.real;
      offset += sizeof(this->thruster_4);
      union {
        float real;
        uint32_t base;
      } u_thruster_5;
      u_thruster_5.base = 0;
      u_thruster_5.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_thruster_5.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_thruster_5.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_thruster_5.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->thruster_5 = u_thruster_5.real;
      offset += sizeof(this->thruster_5);
      union {
        float real;
        uint32_t base;
      } u_thruster_6;
      u_thruster_6.base = 0;
      u_thruster_6.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_thruster_6.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_thruster_6.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_thruster_6.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->thruster_6 = u_thruster_6.real;
      offset += sizeof(this->thruster_6);
      union {
        float real;
        uint32_t base;
      } u_thruster_7;
      u_thruster_7.base = 0;
      u_thruster_7.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_thruster_7.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_thruster_7.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_thruster_7.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->thruster_7 = u_thruster_7.real;
      offset += sizeof(this->thruster_7);
      union {
        float real;
        uint32_t base;
      } u_thruster_8;
      u_thruster_8.base = 0;
      u_thruster_8.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_thruster_8.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_thruster_8.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_thruster_8.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->thruster_8 = u_thruster_8.real;
      offset += sizeof(this->thruster_8);
     return offset;
    }

    virtual const char * getType() override { return "robotic_sas_auv_ros/Actuator"; };
    virtual const char * getMD5() override { return "e45d5cfc79f081bd6970a4a740eced18"; };

  };

}
#endif
