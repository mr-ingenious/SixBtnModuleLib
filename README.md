# SixBtnModuleLib

## Purpose
This library is intended for use with an input module containing 6 pushbuttons and resistors forming a net of voltage dividers.

## Hardware
The circuit contains six pushbuttons arranged like a star with a center button ("OK" button) and an extra button on the lower right corner ("BACK" button).

### Circuit design
The circuit has three connectors, see J1:
1. Vcc for 3,3V (5V would also work)
2. Ua connected to the analog pin of the arduino
3. Ground

The series resistor Rv embodies the first part of the voltage divider. The other resistors have different values and are each connected to one pin of the pushbuttons and Rv. The different resistor values of R1 to R6 are explained below.

If a pushbutton has been pressed, a current flows through Rv and the resistor connected to the switch pressed. Example: If switch S3 is pressed, the current flows from Vcc through Rv and R3 to the ground. The J1 pin 2 which is connected to the analog pin of the arduino measures the voltage between these two resistors and provides the measurement as a value between 0 and 1023. In the example, the voltage over R3 is somewhere around 1.4V (with Vcc = 3.3V). In this case, the arduino analogread() function would return a value near 440.

![six_button_module_Schaltplan](https://user-images.githubusercontent.com/82120163/126395178-ff381c78-d783-4711-82cd-a7b7c0909d42.png)

The resistors have different values which I chose with the following design goals:
1. The full resolution of the "analog in" pin is 1024, being capable of detecting differences of up to ~3 mV for each step (at 3.3V Vcc). To make use of the full range and for a reliable detection of the different pushbutton events, I divided the 1024 by 7, which is 146. This means, that pushing each of the pushbuttons returns a specific and roughly equal distance to the neighboring pushbuttons. Additionally, there is also some distance to 0 and 1023.
For example, when pushing button 1, a value of 146 shall be returned by the arduino analogread() function, pushing button 2 a value of 292 is returned etc. up to a value of 877 for button 6. 

2. The maximum current floating from Vcc to GND shall not exceed 5 mA. With 3.3 Volts, the overall resistance shall not be lower than 660 ohms.

The different resistance values for all the resistors can be calculated. But I had to adapt the theoretical values with resistors I already had, see below:

| Pushbutton | Resistor | Resistance |
| ------------- | ------------- | ------------- |
| -  | Rv | 2.7k Ohms |
| S1 | R1 | 330 ohms |
| S2 | R2 | 1071 ohms |
| S3 | R3 | 2140 ohms |
| S4 | R4 | 3.6k ohms |
| S5 | R5 | 7.2k ohms |
| S6 |  R6 | 20.5k ohms |


### PCB
The PCB looks like shown in the image below, which I did not realize. Instead, I used a perfboard and wired all parts manually.

![six_button_module_Leiterplatte](https://user-images.githubusercontent.com/82120163/126395160-31a94af6-2b2b-467b-ab51-85cfec6fb9fa.png)


## Softwae library
