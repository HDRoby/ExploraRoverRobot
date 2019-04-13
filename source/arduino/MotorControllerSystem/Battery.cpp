#include "Arduino.h"
#include "Battery.h"

Battery::Battery(uint8_t v_sense_pin, uint8_t i_sense_pin)
{
  _v_sense_pin = v_sense_pin;
  _i_sense_pin = i_sense_pin;
  
  /* 
   *  default we have no scaling factors.
   *  the scaling factor depends on the resistor partitioner,  
   *  if present or not. Usually is either 1.0 or 2.0 
   */
  
  _voltage_scale_factor = 1.0;
  _current_scale_factor = 1.0;
}

void Battery::setVoltageScaleFactor(float scale)
{
  _voltage_scale_factor = scale;
}

void Battery::setCurrentScaleFactor(float scale)
{
  _current_scale_factor = scale;
}

float Battery::getVoltage()
{
  return _voltage_scale_factor * ADC_TO_VOLT(analogRead(_v_sense_pin));
}

float Battery::getCurrent()
{
  return _current_scale_factor * ADC_TO_VOLT(analogRead(_i_sense_pin));
}

StaticJsonDocument<200> Battery::getJson()
{
  StaticJsonDocument<200> doc = getBasicJsonDocument();

  doc["device"] = "battery";
  doc["volt"] = getVoltage();
  doc["current"] = getCurrent();

  return doc;
}
