# Project To-Do List

**IMPORTANT** </br>
CPU Frequency is built around  a speed of *1 MHZ*

## Deliverables
- [X] Set up repository 
- [ ] Circuit Schematic
- [ ] Simulation
- [ ] 5 Minute Demonstration Video
- [ ] Report

## Drivers
- [ ] Timer 
- [ ] ADC 
- [ ] UART

## Hardware
- [ ] Draft Circuit Schematic 
- [ ] Use transistors for something
- [ ] Finish Proteus Schematic

## Hardware & Software
- [ ] DIO: LEDs for living room light, bedroom light, and fan; buzzer for alarms.
- [ ] LCD: Display temperature, light status, fan status, door status, and system mode. 
- [ ] Keypad: Enter a 4-digit password, navigate menus, and manually control appliances.
- [ ] Timers: Use for buzzer timing, LED blinking, periodic sensor sampling, or a software clock.
- [ ] ADC: Read LM35 temperature sensor and LDR; automatically control fan and light based on thresholds.
- [ ] UART: Support commands: LIGHT1 ON/OFF, FAN ON/OFF, STATUS, AUTO, MANUAL.

## Software
- [ ] Add int to string converion for an LCD
- [ ] delay_ms & delay_us
- [ ] Interrupts: Use for a doorbell, motion sensor, or emergency button; display a message and activate the buzzer.
- [ ] System Modes: Manual Mode: Appliances are controlled using the keypad or UART. <br>
Automatic Mode: Fan and lights are controlled automatically according to sensor readings.
- [ ] Password System: Default password: 1234. <br>
Three incorrect attempts activate the buzzer and display "ACCESS DENIED".



## Bonus
- [ ] EEPROM to save password and mode