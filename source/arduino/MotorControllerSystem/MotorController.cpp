#include "Arduino.h"
#include "MotorController.h"

MotorController::MotorController(uint8_t pwm_1_pin, uint8_t pwm_2_pin, uint8_t i_sense_pin)
{
  _pwm_1_pin = pwm_1_pin;
  _pwm_2_pin = pwm_2_pin;
  _i_sense_pin = i_sense_pin;

  pinMode(_pwm_1_pin, OUTPUT);
  pinMode(_pwm_2_pin, OUTPUT);

  setSpeed(0);
}

float MotorController::getCurrent()
{
  return ADC_TO_VOLT(analogRead(_i_sense_pin));
}

float MotorController::getSpeed()
{
  return _speed;
}

uint8_t MotorController::absSpeedToDutyCycle(float speed)
{
  return (uint8_t) (speed * (float)_max_duty_cycle);
}

void MotorController::setSpeed(float speed)
{
  _speed = speed;
  if (_speed < -1) _speed = -1.0; 
  if (_speed > 1) _speed = 1.0; 

  applySpeed();
}

void MotorController::applySpeed()
{
  uint8_t duty_cycle = absSpeedToDutyCycle(abs(_speed));

  if (_speed < 0)
  {
    analogWrite(_pwm_1_pin, duty_cycle);
    analogWrite(_pwm_2_pin, 0);
  }
  else 
  {
    analogWrite(_pwm_1_pin, 0);    
    analogWrite(_pwm_2_pin, duty_cycle);
  }
}
