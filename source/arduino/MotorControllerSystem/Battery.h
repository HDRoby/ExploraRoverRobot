#ifndef Battery_h
#define Battery_h

#include "Arduino.h"
#include "MotorControllerDefines.h"


class Battery
{
  public:
    Battery(uint8_t v_sense_pin, uint8_t i_sense_pin);
    void setVoltageScaleFactor(float scale);
    void setCurrentScaleFactor(float scale);
    float getVoltage();
    float getCurrent();
    
  private:  
    uint8_t _v_sense_pin;
    uint8_t _i_sense_pin;    
    float _voltage_scale_factor;
    float _current_scale_factor;    
};

#endif
