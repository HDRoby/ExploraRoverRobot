
/*
 * Demo code to test the MotorControllerSystem and the libraries:
 * Battery, MotorController and QuadratureEncoder
 * 
 * Accepts input on the serial line and changes motor speed where [-1.0:1.0]
 * Prints a set of measures in json format using ArduinoJson library
 * 
 * IMPORTANT: 
 * Q2_A is still on pin 7 and MUST be moved to pin2 that on the NANO can raise an interrupt
 * 
 */


#include "MotorControllerDefines.h"
#include "Battery.h"
#include "MotorController.h"
#include "QuadratureEncoder.h"
#include "JsonSerializable.h"
#include "HullFloodSensor.h"
#include "SerialCommand.h"
#include <ArduinoJson.h>


Battery mainBattery(MAIN_BATT_V_SENSE_PIN, MAIN_BATT_I_SENSE_PIN);
Battery motorBattery(MOTORS_BATT_V_SENSE_PIN, MOTORS_BATT_I_SENSE_PIN);

MotorController motor_left(MOTOR_L_PWM_1_PIN, MOTOR_L_PWM_2_PIN, MOTOR_L_I_SENSE_PIN);
MotorController motor_right(MOTOR_R_PWM_1_PIN, MOTOR_R_PWM_2_PIN, MOTOR_R_I_SENSE_PIN);

QuadratureEncoder encoder_left(Q1_B, Q2_B);
QuadratureEncoder encoder_right(Q1_A, Q2_A);

HullFloodSensor floodSensor(HULL_FLOOD_SENSE_PIN);

SerialCommand commands;

void setup() {
  
  Serial.begin(9600); 

  commands.addCommand("speed",setMotorsSpeed);  
  commands.addCommand("stop",stopMotors);  

  motor_left.setAttribute("left");
  motor_right.setAttribute("right");
  
  mainBattery.setVoltageScaleFactor(2.0);
  mainBattery.setAttribute("main");
  
  motorBattery.setVoltageScaleFactor(2.0);
  motorBattery.setAttribute("motor");

  encoder_left.setupInterruptHandler(ISREncoderLeft);
  encoder_left.setAttribute("left");
  
  encoder_right.setupInterruptHandler(ISREncoderRight);
  encoder_right.setAttribute("right");

  floodSensor.setAttribute("bottom");

  stopMotors();
}

void loop() {
  commands.readSerial();    
  printJson();  
  delay(500);
}

void printJson()
{  
  serializeJson(motor_left.getJson(), Serial);
  Serial.println();

  serializeJson(motor_right.getJson(), Serial);
  Serial.println();

  serializeJson(mainBattery.getJson(), Serial);
  Serial.println();

  serializeJson(motorBattery.getJson(), Serial);
  Serial.println();

  serializeJson(encoder_left.getJson(), Serial);
  Serial.println();

  serializeJson(encoder_right.getJson(), Serial);
  Serial.println();

  serializeJson(floodSensor.getJson(), Serial);
  Serial.println();

}

void ISREncoderLeft()
{
  encoder_left.handleInterrupt();
}

void ISREncoderRight()
{
  encoder_right.handleInterrupt();
}

void setMotorsSpeed() {
  char *arg;
  
  arg = commands.next();
  if (arg != NULL) {    
     motor_left.setSpeed((float)atoi(arg)/100);    
  }
  arg = commands.next();
  if (arg != NULL) {    
     motor_right.setSpeed((float)atoi(arg)/100);    
  }
}

void stopMotors() {  
  motor_right.setSpeed(0);    
  motor_left.setSpeed(0);    
}
