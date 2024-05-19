# Autonomous-Car-Control-Dashboard
Communicating and Controlling an Autonomous Car Prototype

# 
## Table of contents:
- [Introduction](#introduction)
- [Project Features](#project-features)
- [Project Structure](#project-structure)
- [Application Preview](#Application-preview)
***
### Introduction
This project is a dashboard that allows the user to communicate with an autonomous car prototype. The user can control the car by sending commands to it through UART commands. The system adjusts motor speed, direction, and wheel angle based on received commands after checking them then displays them on LCD Dashboard with time.

### Project Features
- **User Interface**: The user can control the car by sending commands to it through UART commands.
- **LCD Dashboard**: The system adjusts motor speed, direction, and wheel angle based on received commands after checking them then displays them on LCD Dashboard with time.
- **UART Communication**: The system communicates with the car through UART communication.
- **Error Handling**: The system checks the received commands and displays an error message if the command is invalid.
- **Time**: The system displays the time on the LCD Dashboard.
***
### Project Structure

```
Autonomous-Car-Control-Dashboard src
├─ App
|  ├─  main.c 
├─ HAL
|  ├─  DC_Motor
|  │  ├─ DC_Motor_Interface.h
|  │  ├─ DC_Motor.h
|  │  ├─ DC_Motor.c
|  ├─  Servo_Motor
|  │  ├─ Servo_Motor.h
|  │  ├─ Servo_Motor.c
|  ├─  LCD
|  │  ├─ LCD_Interface.h
|  │  ├─ LCD.h
|  │  ├─ LCD.c
├─ MCAL
|  ├─  USART
|  │  ├─ USART.h
|  │  ├─ USART.c
|  ├─  Systick_Timer
|  │  ├─ Systick_Timer.h
|  │  ├─ Systick_Timer.c
|  ├─  GPIO
|  │  ├─ Gpio_Interface.h
|  │  ├─ Gpio_Private.h
|  │  ├─ GPIO.h
|  │  ├─ GPIO.c
|  ├─  RCC
|  │  ├─ Rcc_Private.h
|  │  ├─ RCC.h
|  │  ├─ RCC.c
|  ├─  PWM
|  │  ├─ PWM.h
|  │  ├─ PWM.c
├─ Services
|  ├─  Includes
|  │  ├─  Dashboard.h
|  │  ├─  Frame.h
|  │  ├─  Services.h
|  ├─  Dashboard.c
|  ├─  Frame.c
|  ├─  Dashboard.c
|  ├─  Services.c
├─ Libraries
|  ├─  Macros.h
|  ├─  Std_Types.h
|  ├─  Utils.h
Simulation
Video
README.md
```
***

### Application Preview
