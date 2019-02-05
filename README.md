# Explora Rover Robot
6 wheels drive, all terrain, autonomous robot designed as a platform to experiment with autonomous driving vehicle.

Explora Robot is based on a well known commercial chassis widely available for hobbists 
[Dagu Thumper 6WD](https://www.sparkfun.com/products/11056).

![Dagu Thumper 6WD](images/6WDdimension.jpg)

Aim of this project is to design and build a robotic platform that will provide a set of interfaces, both software and hardware, that allow to build new layers with extended functionalities. Initial capabilities will include:

- indoor and outdoor navigation
- remote control and monitoring
- obstacle detection and avoidance
- simultaneus location and mapping (SLAM)
- viewpoints and landmark navigation
- terrain traversability estimation
- terrain negotiation
- path planning
- energy management and harvesting
- center of mass and pose estimation

## Tenets

- The system is open for modification without major disruption in all the parts.
- The robot can operate outdoor but its not designed for harsh environment. i.e. wet or dirty surfaces are allowed while waterproof is not in the scope.
- The energy consumption is frugal and a certain degree of autonomy is pursued. i.e. solar panel for energy harvesting or self recharging station could be implemented.
- The communication is bi-directional and mainly intended for monitoring and configuration than control (RC style).
- The robot can take advantage of many and concurrent localisation systems to establish its position in the environment. i.e. GPS, vision, LIDAR, utrasound, odometry, IMU, ...


## High level systems

![Systems](images/High_level_systems.png)

### Power management system

This is responsible for providing power to the rover and all its subsystems, to monitor and recharge the batteries using both an external power source and solar panels. The system monitors the current drawn in real time by its major components: motors and all sub-systems; where possible each sub-system will provide its own power consumpion. Communications with the microcontroller (Arduino Micro) and other sub-systems is achieved via UART for the physical layer and with MQTT broker at ISO Application Layer (there will be a process on the main board (Raspberry Pi) that will have a process that act as a MQTT broker and that can communicate with a UART). 

Two mechanichal switches isolate the batteries from the rest of the system and a matrix of relays allow to re-route energy where needed:
- Motors and Electronics with separated batteries
- Motors and Electronics with joined batteries
- Only Electronics with its own battery
- Only Electronics with joined batteries



![Power management system](images/Power_Supply_System.svg)



### Motion control system

![Motion control system](images/MotionControlSystem.png)

### Communication system

![Communication system](images/CommunicationSystem.png)

