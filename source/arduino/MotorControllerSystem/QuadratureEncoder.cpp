#include "Arduino.h"
#include "QuadratureEncoder.h"
 
QuadratureEncoder::QuadratureEncoder(uint8_t q1_pin, uint8_t q2_interrupt_pin)
{
  _q1_pin = q1_pin;
  _q2_interrupt_pin = q2_interrupt_pin;

  _encoder_pos = 0;
  _new_position;
  _old_position = 0;
  _new_time;
  _old_time = 0;

  
  pinMode(_q1_pin, INPUT);
  pinMode(_q1_pin, INPUT);
  digitalWrite(_q1_pin, INPUT_PULLUP);
  pinMode(_q2_interrupt_pin, INPUT);
  digitalWrite(_q2_interrupt_pin, INPUT_PULLUP);
}

void QuadratureEncoder::setupInterruptHandler(void (*ISR)(void))
{
  attachInterrupt(digitalPinToInterrupt(_q2_interrupt_pin), ISR, RISING);
}

float QuadratureEncoder::getSpeed()
{
  _new_position = _encoder_pos;
  _new_time = millis();
  
  float v = (float)(_new_position - _old_position) / (float)(_new_time - _old_time);  
  
  _old_position = _new_position;
  _old_time = _new_time;

  return v;
}

void QuadratureEncoder::handleInterrupt()
{
  if (digitalRead(_q1_pin) == digitalRead(_q2_interrupt_pin)) {
    _encoder_pos--;
  } else {
    _encoder_pos++;
  }
}
