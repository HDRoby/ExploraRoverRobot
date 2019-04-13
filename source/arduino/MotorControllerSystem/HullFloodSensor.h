#ifndef HullFloodSensor_h
#define HullFloodSensor_h

#include "Arduino.h"
#include "MotorControllerDefines.h"
#include "JsonSerializable.h"

class HullFloodSensor: public JsonSerializable
{
  public:
    HullFloodSensor(uint8_t sense_pin);
    float getValue();
    virtual StaticJsonDocument<200> getJson();
    
  private:  
    uint8_t _sense_pin;    
};

#endif
