#ifndef MotorControllerDefines_h
#define MotorControllerDefines_h


#define MAIN_BATT_I_SENSE_PIN       A0
#define MAIN_BATT_V_SENSE_PIN       A3

#define MOTORS_BATT_I_SENSE_PIN     A1
#define MOTORS_BATT_V_SENSE_PIN     A2

#define MOTOR_L_I_SENSE_PIN         A4
#define MOTOR_L_PWM_1_PIN           10
#define MOTOR_L_PWM_2_PIN           9

#define MOTOR_R_I_SENSE_PIN         A5
#define MOTOR_R_PWM_1_PIN           6
#define MOTOR_R_PWM_2_PIN           5

#define HULL_FLOOD_SENSE_PIN        A6

#define Q1_A                        8
#define Q2_A                        7 // this MUST be moved to pin 2 because only pin 2 and 3 are interruptible !
#define Q1_B                        4
#define Q2_B                        3

#define QUANTUM                     5.0 / 1024.0;
#define ADC_TO_VOLT(adc) adc * QUANTUM 

#define LEFT                        0
#define RIGHT                       1

#endif
