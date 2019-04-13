#ifndef QuadratureEncoder_h
#define QuadratureEncoder_h

#include "Arduino.h"
#include "MotorControllerDefines.h"

class QuadratureEncoder
{
  public:
    QuadratureEncoder(uint8_t q1_pin, uint8_t q2_interrupt_pin);
    void setupInterruptHandler(void (*ISR)(void));
    void handleInterrupt();
    float getSpeed();
    
  private:   
    
    uint8_t _q1_pin;
    uint8_t _q2_interrupt_pin;
    float _speed;
    
    volatile uint32_t _encoder_pos;
    long _new_position; // not unsegnid because they carry the direction ccw/cc
    long _old_position;
    uint32_t _new_time;
    uint32_t _old_time;
};

#endif
