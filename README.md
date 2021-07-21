# SixBtnModuleLib

## Purpose
This arduino library is intended for use with an input module containing 6 pushbuttons and resistors forming a net of voltage dividers.

## Hardware
The circuit contains six pushbuttons arranged like a star with a center button ("OK" button) and an extra button on the lower right corner ("BACK" button).

### Circuit design
The circuit has three connectors, see J1:
1. Vcc for 3,3V (5V would also work)
2. Ua connected to the analog pin of the arduino
3. Ground

The series resistor Rv embodies the first part of the voltage divider. The other resistors have different values and are each connected to one pin of the pushbuttons and Rv. The different resistor values of R1 to R6 are explained below the schematic.

If a pushbutton has been pressed, a current flows through Rv and the resistor connected to the switch pressed. Example: If switch S3 is pressed, the current flows from Vcc through Rv and R3 to the ground. The J1 pin 2 is connected to the analog pin of the Arduino. The Arduino measures the voltage over resistor R3 and converts the measurement into a value between 0 and 1023. In the example, the voltage over R3 is somewhere around 1.4V (with Vcc = 3.3V). In this case, the arduino analogRead() function would return a value of approx. 440.

![six_button_module_Schaltplan](https://user-images.githubusercontent.com/82120163/126395178-ff381c78-d783-4711-82cd-a7b7c0909d42.png)

The resistors have different values which I chose with the following design goals:
1. The full resolution of the "analog in" pin is 1024, being capable of detecting differences of up to ~3 mV for each step (with 3.3V Vcc). To make use of the full range and for a reliable detection of the different pushbutton events, I divided the 1024 by 7, which is 146. This means, that pushing each of the pushbuttons returns a specific and roughly equal resistor voltage difference to the neighboring pushbuttons. Additionally, there is also some voltage distance to 0 and 1023.
For example, when pushing button 1, a value of 146 shall be returned by the arduino analogRead() function, pushing button 2 a value of 292 is calculated etc. up to a value of 877 for button 6. 

2. The maximum current floating from Vcc to GND shall not exceed 5 mA. With 3.3V, the overall resistance shall therefore more than 660 ohms.

The different resistance values for all the resistors can be calculated. I had to adapt the theoretical values with resistors I already had with nearly good resistor voltage differences for each of them, see below: 

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


## Software library
### Design goals
1. easy to use
2. does just one thing: read different pressed pushbuttons via analogread() and provide the correct button pressed
3. low memory footprint
4. fast

### Usage
The common use of the library is shown in the sketch located in the examples folder.

It is important, that the readButtons() function is cyclically called within the loop() function. Even though it can be called in every loop() cycle, it only executes internally after a defined time span "read interval" has exceeded. In case a button is pressed, the readButtons() method returns a byte value. If no button is pressed, it returns BUTTON_NONE, otherwise one of the following: BUTTON_LEFT, BUTTON_RIGHT, BUTTON_UP, BUTTON_DOWN, BUTTON_CENTER, BUTTON_BACK. 

Readings are performed periodic based on the set value for the button read interval.

### Possible future extensions
- [ ] possibility to assign callback functions to buttons
- [ ] add possibility to distinguish between a pushbutton "click", "retrigger" and "hold"
- [ ] make expected button value for each button configurable
