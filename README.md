# MultiSpectLED
Array of 15 1W LEDs spanning 280nm to 940nm
![alt text](https://github.com/benkrasnow/MultiSpectLED/blob/main/MultiSpectLED.gif?raw=true)


Notes:  The 280nm LED has a forward voltage drop of between 5V and 7.5V depending on the voltage bin.  This is higher that I expected when I designed the circuit, and it will not work if the power supply is really 5.0V.  It should have a boost converter instead of a buck converter.  However, I happened to receive an LED with a 5.1V drop, and my 5V wall adapter supplies 5.35V at 500mA, so the system works with the buck converter, just barely.  This part of the circuit should be redesigned if 280nm is needed.

The "enable" pin on the PAM2804 buck controller is very high-impedance, and will float around while the MCU is being programmed.  This causes bright flashes, and potentially can draw too much current from the supply, so pull-down resistors *MUST* be added between each PWM control line and ground.  I haven't updated the PCB yet, and fixed it in the prototype by adding resistors:

![alt text](https://github.com/benkrasnow/MultiSpectLED/blob/main/resistor_bodge.jpg?raw=true)

The heatsink has a 45mm wide rasied section, and the PCB is designed so that all exposed copper is ground within this 45mm strip. I used the PCB itself as a drill guide to drill 2.5mm holes, and then tapped them M3.  I used M3x4 screws to hold the PCB to the heatsink.

Originally, I planned to use Luxeon IR LEDs from Lumileds for the 850 and 940nm.  The thermal pad on these is tied to the anode, so it will not work with the current PCB design.  

Heatsink and fan: https://www.amazon.com/dp/B00006B8EX
The fan runs nice and quiet on 5V, and provides more than enough airflow

USB-C 5V 4A power adapter:  Digikey 1597-106060004-ND  This should have enough current capacity to run up to 8 LEDs at full power.

Each LED channel is configured for 500mA , which is set by the 0.2 ohm resistor and internal 0.1V reference of the buck controller IC, PAM2804.
Dimming is achieved with PWM, and I used "software PWM" to get 15 separate channels from the Teensy-LC.  The SoftPWM library defaults to 60Hz update, which I noticed flickering, so I edited SoftPWM.cpp to use 120Hz instead.  MCUs with 15+ hardware PWM channels exist, but are more expensive, and not easy to find these days!

The Teensy-LC also provides easy programability for external triggering, remote control via USB serial, etc

The +5V power connection on the Teensy-LC between its USB micro plug and Vin pin should be cut.  There is a thin link between two exposed pads on the underside for this purpose.  This allows the Teensy to be powered only by the Vin pin, which is connected to the USB-C power rail in this design (it must be powered for programming).  If the link is not cut, and both USB connections are made with mismatched voltages (eg 4.9V vs 5.3V), bad currents may flow.



Total cost is about $180, and the 280nm LED alone is $24

![alt text](https://github.com/benkrasnow/MultiSpectLED/blob/main/top3D.jpg?raw=true)
.

![alt text](https://github.com/benkrasnow/MultiSpectLED/blob/main/bottom3D.jpg?raw=true)

Thermal performance looks very good.  At 16C ambient, the hottest part is the inductor at 23C.
![alt text](https://github.com/benkrasnow/MultiSpectLED/blob/main/thermal.jpg?raw=true)
