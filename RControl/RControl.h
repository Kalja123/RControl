#ifndef RControl_h 
#define RControl_h
#include <Arduino.h>

class RControl  {
  public:
    String pinA;
	String pinD;
	float temp;
void RX_TX(uint8_t newRX=2,uint8_t newTX=3);
boolean find(String string, String value);
String sendToUno(String command, const int timeout);
};
class RControlWifi :public RControl{
  public:
    init(long speed=115200,String Ip="192.168.5.1", String Port="1001"); 
	void listen();
 private:
    void ACommands(String message);
void DCommands(String message);
void sendDataWifi(String str);
String  readWifiSerialMessage();
String sendToWifi(String command, const int timeout);

};
class RControlBluetooth:public RControl {
  public:
     init(long speedd=9600);    
	void listen();
 private:
 void ACommands(String message);
void DCommands(String message);
void sendDataBluetooth(String command, const int timeout);
String  readBluetoothSerialMessage();



};
#endif
