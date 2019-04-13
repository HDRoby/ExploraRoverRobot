#ifndef MotorController_h
#define MotorController_h

#include "Arduino.h"
#include "MotorControllerDefines.h"


class MotorController
{
  public:
    MotorController(uint8_t pwm_1_pin, uint8_t pwm_2_pin, uint8_t i_sense_pin);
    float getCurrent();
    float getSpeed();
    // range [-1, +1] the sign indicates rotation ccw or cc
    void setSpeed(float speed);
    
  private:
    uint8_t absSpeedToDutyCycle(float speed);
    void applySpeed();
  
    uint8_t _pwm_1_pin;
    uint8_t _pwm_2_pin;
    uint8_t _i_sense_pin;    
    float _speed;

    /* 
     * motor controller datasheet requires d.c < 98% 
     * 98% * 255 = 250 
     */    
    static const uint8_t _max_duty_cycle = 250; 
};

#endif
