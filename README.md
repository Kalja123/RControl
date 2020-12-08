# RControl
Arduino library RControl. Performs data exchange between the Arduino and the smartphone in WiFi and Bluetooth networks.

The __Esp8266 module__ is used for the WiFi network. The connection is made with the SoftwareSerial service.

The __HC-05 module(BC417143)__ is used for the Bluetooth network. The connection is made with the SoftwareSerial service.

The library can work with any of the networks. Each of the networks has its own part of the library. For data exchange, the Arduino pins are __RX=2__, __TX=3__. Modules must be connected to them, but you can change the pins to your own in the library.
## WiFi
1.	In beginning, you must add the library to your project. _**#include <RControl.h>**_
2.	Create a variable _**RControlWifi r1;**_
3.	In setup()you must write the pins description lines:


    Analog pins: r1.pinA="{pin Nr(without a,d...);min value;max value;in/out;descripion}"; 

    example:  _**r1.pinA="{18;0;1023;in;humidity senser, value/10=dryness}{11;0;255;out;temp}";**_

    digital pins r1.pinD="{pin Nr(without a,d...);in/out;descripion}";

    example: _**r1.pinD="{12;out;relay 1}{8;out;relay 2}{7;out;relay 3}";**_
4.	In setup() you must initialize the connection:

    _**r1.init();**_ with default values (speed=115200, Ip="192.168.5.1",  Port="1001");

    or change information _**r1.init((Serial speed) speed=115200,(TCP server IP) Ip="192.168.5.1", ,(TCP server port) Port="1001");**_
5.	The last step in  loop()  in main loop write _**r1.listen();**_.


In mobile app create new TCP with default data (Ip="192.168.5.1", Port="1001") or your data.
Your WiFi module will be a access point, connect to it in smartphone settings.

## Bluetooth 
1.	In beginning, you must add the library to your project. _**#include <RControl.h>**_
2.	Create a variable _**RControlBleutooth r1;**_
3.	In setup()you must write the pins description lines:


    Analog pins: r1.pinA="{pin Nr(without a,d...);min value;max value;in/out;descripion}"; 

    example:  _**r1.pinA="{18;0;1023;in;humidity senser, value/10=dryness}{11;0;255;out;temp}";**_

    digital pins r1.pinD="{pin Nr(without a,d...);in/out;descripion}";

    example: _**r1.pinD="{12;out;relay 1}{8;out;relay 2}{7;out;relay 3}";**_
4.	In setup() you must initialize the connection:

    _**r1.init();**_ with default values (speed=9600);

    or change information _**r1.init((Serial speed) speed=9600);**_
5.	The last step in  loop()  in main loop write _**r1.listen();**_.

In mobile app change connection type to Bluetooth and select Bleutooth device.
