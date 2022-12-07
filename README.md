# ECEN2440_FinalProject

This project is designed to be a functional night light. It uses a comparator along with a photoresistor to turn on an LED light when the ambient light is below a specified threshold. An analog voltage input is taken in to the comparator which then outputs a digital voltage and then the MSP sends a digital logic level high output to the LED. The digital input is put into a scheduler that is used to turn on the LED. When it is bright in the room, the scheduler is cleared and the LED is turned off.
You need to connect the probe pin to P4.0 and the LED pin to P6.1
