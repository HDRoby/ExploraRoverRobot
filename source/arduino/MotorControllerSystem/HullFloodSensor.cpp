#include "Arduino.h"
#include "HullFloodSensor.h"

HullFloodSensor::HullFloodSensor(uint8_t sense_pin)
{
  _sense_pin = sense_pin;
}

float HullFloodSensor::getValue()
{
  return ADC_TO_VOLT(analogRead(_sense_pin));
}

StaticJsonDocument<200> HullFloodSensor::getJson()
{
  StaticJsonDocument<200> doc = getBasicJsonDocument();

  doc["sensor"] = "flood";
  doc["value"] = getValue();

  return doc;
}
