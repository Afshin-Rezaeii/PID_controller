# PID_controller
Speed control of DC motor using PID controller and simulation with Proteus
## Introduction
we will consider the digital control version of DC motor speed problem. A digital DC motor model can be obtained from conversion of the analog model, 
as we will describe.The controller for this example will be designed by a PID method.
The open-loop transfer function for DC motor's speed was derived as:

![MotorSpeed_ControlPID_eq12367307253716340627](https://user-images.githubusercontent.com/69188686/129372684-cc1f73f1-c2ea-43cb-b678-b0e0ce2f7c60.png)

Where: 
* electrical resistance (R) = 1 ohm
* electrical inductance (L) = 0.5 H
* electromotive force constant (Ke=Kt) = 0.01 Nm/Amp
* moment of inertia of the rotor (J) = 0.01 kg*m^2/s^2
* damping ratio of the mechanical system (b) = 0.1 Nms
* input (V): Source Voltage
* output (theta dot): Rotating speed
* The rotor and shaft are assumed to be rigid

The design requirements for 1 rad/sec step input are

* Settling time: Less than 2 seconds
* Overshoot: Less than 5%
* Steady-state error: Less than 1%
