
 #include <RControl.h>
 

RControlWifi r1;


void setup()
{
  // r1.pinA="{pin Nr(without a,d...);min value;max value;in/out;descripion}";
  r1.pinA="{18;0;1023;in;humidity senser, value/10=dryness}{11;0;255;out;temp}";
//r1.pinD="{pin Nr(without a,d...);in/out;descripion}";
r1.pinD="{12;out;relay 1}{8;out;relay 2}{7;out;relay 3}";

  pinMode(18, INPUT); 
   pinMode(11, OUTPUT); 
pinMode(12, OUTPUT);  
  pinMode(8,OUTPUT);  
 pinMode(7,OUTPUT);
 
  Serial.begin(115200);
  
  r1.init(); //default values r1.init(Serial speed=115200, Ip="192.168.5.1",  Port="1001");
}


void loop()
{
  
  r1.listen();


 }
