#ifndef Battery_h
#define Battery_h

#include "Arduino.h"
#include "MotorControllerDefines.h"
#include "JsonSerializable.h"

class Battery: public JsonSerializable
{
  public:
    Battery(uint8_t v_sense_pin, uint8_t i_sense_pin);
    void setVoltageScaleFactor(float scale);
    void setCurrentScale30A();
    void setCurrentScale5A();
    float getVoltage();
    float getCurrent();
    virtual StaticJsonDocument<200> getJson();
    
  private:  
    uint8_t _v_sense_pin;
    uint8_t _i_sense_pin;    
    float _voltage_scale_factor;
    float _current_scale_factor;    
};

#endif
