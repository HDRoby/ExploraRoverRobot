# Motion Control System

We will use Dual H-Bridge Driver Motor Controller

## Features: 
Compact size, light weight.
Apply to control ordinary DC motor, smart car motor, etc.
Reversible control and PWM speed control.
Design of high-speed switch.
Ultra low internal resistance, low heat.


## Technical Specifications:
Operating Voltage: DC5V-12V
Standby Current: <30mA ± 5mA
Working Current: 0A-30A (Max) / each channel.
PWM mode: Duty cycle: 0-98%.
Frequency: General Motors: 16 kHz; Coreless Motor: 80 kHz; TEC: 500Hz-80kHz.
Input Voltage Level: Low: 0-0.5 V; High: 2.5 V-13 V (typical unit level: 3.3 V, 5 V, 12 V)
Current Sampling: CT Pin Output 

Voltage (V) = current (A) * 0.155

Item size: 6.2 x 5.3 x 1.8cm


## Pinout


1-6  | 7-12
---- | ----
CT_A | CT_B
EN_A | EN_B
IN1_A | IN1_B
IN2_A | IN2_B
GND | GND
V+  A | V+ B

![Dual H-Bridge](images/Dual_H-Bridge.jpg_1)

## Motor control protocol

### Low level communication

Commands sent to the controller:

to set the wheel diameter, used to compute the speed and to drive the robot using speed vector in the robot world:
```
'wheel_diam_mm': 120
```

to set each motor speed as percentage of the max speed
```
'motor':{
          'side': 'left',
          'enable': True,
          'rot': 'cw',
          'pwm': 98          
        }
```

valid values:
```
  side = {'left', 'right'}
  enable = {True, False}
  rot = {'cw', 'ccw'}
  pwm = [MIN_PWM,..,MAX_PWM] 
  
  with this controller: 
    MIN_PWM = 0
    MAX_PWM = 98
```

Values read from the controller:

```
'motor':{
          'side': 'left',
          'enable': True,
          'rot': 'cw',
          'pwm': 98,
          'current_ma': 1450,
          'speed_rpm': 54,
          'speed_m_s': 0.339           
        }
```

valid values:
```
  current_ma =  Voltage (mV) / 0.155 
```
*note*: speed_rpm is after gear reduction

to compute the actual speed in [m/s], given the wheel diameter in [m]: speed = (rpm / 60) * PI * d