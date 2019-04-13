
/*
 * Demo code to test the MotorControllerSystem and the libraries:
 * Battery, MotorController and QuadratureEncoder
 * 
 * It loops through a range of speeds [-50% to 50%] of the max speed.
 * Prints a set of measures:
 * Batteries (main and motors): V, I
 * Motors (left and right): 
 *    Speed (as %), 
 *    I drawn (at the moment not converted -> still is V fromADC), 
 *    measured speed (From quadrature encoder, at the moment not converted)   
 * Hull flood sensor: at the moment only the V from ADC 
 * 
 * IMPORTANT: 
 * Q2_A is still on pin 7 and MUST be moved to pin2 that on the NANO can raise an interrupt
 * 
 */


#include "MotorControllerDefines.h"
#include "Battery.h"
#include "MotorController.h"
#include "QuadratureEncoder.h"

Battery mainBattery(MAIN_BATT_V_SENSE_PIN, MAIN_BATT_I_SENSE_PIN);
Battery motorBattery(MOTORS_BATT_V_SENSE_PIN, MOTORS_BATT_I_SENSE_PIN);

MotorController motor_left(MOTOR_L_PWM_1_PIN, MOTOR_L_PWM_2_PIN, MOTOR_L_I_SENSE_PIN);
MotorController motor_right(MOTOR_R_PWM_1_PIN, MOTOR_R_PWM_2_PIN, MOTOR_R_I_SENSE_PIN);

QuadratureEncoder encoder_left(Q1_B, Q2_B);
QuadratureEncoder encoder_right(Q1_A, Q2_A);

float m_speed = 0.0;
float dir = 1;
uint16_t hullFlood;

void setup() {
  Serial.begin(9600); 

  mainBattery.setVoltageScaleFactor(2.0);
  motorBattery.setVoltageScaleFactor(2.0);

  encoder_left.setupInterruptHandler(ISREncoderLeft);
  encoder_right.setupInterruptHandler(ISREncoderRight);
}

void loop() {
  hullFlood = analogRead(HULL_FLOOD_SENSE_PIN);
  
  motor_left.setSpeed(m_speed);
  motor_right.setSpeed(m_speed);

  printToSerial();

  updateMotorsSpeed();  
  
  delay(2000);
}

void ISREncoderLeft()
{
  encoder_left.handleInterrupt();
}

void ISREncoderRight()
{
  encoder_right.handleInterrupt();
}

void updateMotorsSpeed()
{
  m_speed += 0.05 * dir;

  if (m_speed > 0.5) dir = -1;
  if (m_speed < -0.5) dir = 1;
}

void printToSerial()
{
  Serial.print("Batt main [V,I]: ");
  Serial.print(mainBattery.getVoltage());
  Serial.print(" ");
  Serial.print(mainBattery.getCurrent());
  Serial.print(" ");
  
  Serial.print("Batt motors [V,I]: ");
  Serial.print(motorBattery.getVoltage());
  Serial.print(" ");
  Serial.print(motorBattery.getCurrent());
  Serial.print(" ");
  
  Serial.print("Motor L [dc,I,enc]: ");
  Serial.print(motor_left.getSpeed());
  Serial.print(" ");
  Serial.print(motor_left.getCurrent());
  Serial.print(" ");
  Serial.print(encoder_left.getSpeed());
  Serial.print(" ");

  Serial.print("Motor R [dc,I,enc]: ");
  Serial.print(motor_right.getSpeed());
  Serial.print(" ");
  Serial.print(motor_right.getCurrent());
  Serial.print(" ");
  Serial.print(encoder_right.getSpeed());
  Serial.print(" ");

  Serial.print("Hull flood: ");
  Serial.print(hullFlood);
  
  Serial.println("");
}
