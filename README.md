Lab6_382
========

###Lab Overview

This lab is designed to provide you with experience using the pulse-width modulation features of the MSP430. You will need to program the MSP430 to generate pulse-width-modulated waveforms to control the speed / direction of your robot's motors. In this lab, you will make your robot move forward, backwards, a small (< 45 degree) turn left/right, and a large (> 45 dgree) turn left/right.

###Driving Motors

There were two motor used in the lab, one for each wheel. The amount of torque provided by the motor was directly proportional to the amount of voltage provided. A positive voltage would move the wheel forward, a negative voltage would move it in reverse.

###Prelab

See attached Prelab. 

###Required Functionality

The prelab I did was not too helpful because i don't think I went about doing it properly. Dr Coulston ended up drawing a useful schematic in class one day, so I ended up basing the design off of that. A lot of other people seemed to do the same, so I thought that if I ran into any problems, it would be helpful that we had the same starting approach.

![alt text](http://i59.tinypic.com/214nz4g.png)

Afterwards, The robot was relatively easy to hook up, I ended up using capacitors to help get a steady signal and reduce voltage fluctuations. The actual robot layout can be seen below. This same design layout was used for the A functionality part of the lab since the IR sensor was easy to install and did not affect the Required functionality part of the lab. I ended up writing one function at a time and testing it to see if it worked. Afterwards I just stacked commands together to achieve the required functionality. 

![alt text](http://i58.tinypic.com/105acmr.jpg)

A video of the required functionality can be seen below.

<embed width="440" height="420" type="application/x-shockwave-flash" src="http://v8.tinypic.com/player.swf?file=2mrs74n&s=8"><br><font size="1"><a href="http://tinypic.com/player.php?v=2mrs74n&s=8">Required Functionality (Uploaded at 1531, 11/25/2014)</a>

###A Functionality

For A Functionality, I basically combined the code from the Required functionality with the code from the previous lab with a few minor changes. I just had to define what the code should do in the event a button was pressed, and I also had to define what the buttons were as well. I ended up creating a header file for this part to accomodate the code from the last lab as well. 

To debug this part, I just tried running the program over and over again with changes added to fix problems as they came up. Then I tried to run each command through the remote and things just worked out.

A video of the A functionality can be seen below.

<embed width="440" height="420" type="application/x-shockwave-flash" src="http://v8.tinypic.com/player.swf?file=24wg9le&s=8"><br><font size="1"><a href="http://tinypic.com/player.php?v=24wg9le&s=8">A Functionality (Uploaded at 1531, 11/25/2014)</a>

###Conclusion

Everything worked in the lab, the bigger problems initially were burning the circuit components such as the fuses and logic chips and trying to figure out why it happened. Once I made the mistake of trying to send voltages to both motors at the same time and it took me a while to realize I shouldn't have done that. I took a closer look at the instructions to try preventing stuff like that happening. Other problems I had were just getting the wiring down correctly. Sometimes I got my pins messed up or plugged into the wrong rail and I ended up burning more stuff. 

Documentation:
C2C Cabusora recommended that instead of trying to create separate functions for my turns, I should just create one that kept turning for a set amount of time. He also helped me with the 6 pins from the MSP board and trying to coordinate them onto the circuit board correctly without me burning more components.
