# MultiSpectLED
Array of 15 1W LEDs spanning 280nm to 940nm
![alt text](https://github.com/benkrasnow/MultiSpectLED/blob/main/MultiSpectLED.gif?raw=true)

Notes:  The 280nm LED has a forward voltage drop of between 5V and 7.5V depending on the voltage bin.  This is higher that I expected when I designed the circuit, and it will not work if the power supply is really 5.0V.  It should have a boost converter instead of a buck converter.  However, I happened to receive an LED with a 5.1V drop, and my 5V wall adapter supplies 5.35V at 500mA, so the system works with the buck converter, just barely.  This part of the circuit should be redesigned if 280nm is needed.

Originally, I planned to use Luxeon IR LEDs from Lumileds for the 850 and 940nm.  The thermal pad on these is tied to the anode, so it will not work with the current PCB design.  

Heatsink and fan: https://www.amazon.com/dp/B00006B8EX
The fan runs nice and quiet on 5V, and provides more than enough airflow

USB-C 5V 4A power adapter:  Digikey 1597-106060004-ND

Total cost about $250, and the 280nm LED alone is $24

![alt text](https://github.com/benkrasnow/MultiSpectLED/blob/main/top3D.jpg?raw=true)
.

![alt text](https://github.com/benkrasnow/MultiSpectLED/blob/main/bottom3D.jpg?raw=true)

Thermal performance looks very good.  At 16C ambient, the hottest part is the inductor at 23C.
![alt text](https://github.com/benkrasnow/MultiSpectLED/blob/main/thermal.jpg?raw=true)
