#include <RControl.h>
#include <SoftwareSerial.h>
#include <Arduino.h>


uint8_t RX=2;
uint8_t TX=3;
SoftwareSerial wifiSerial(RX,TX); 
SoftwareSerial BluetoothSerial(RX,TX); 

 int responseTime = 10; //communication timeout
 int i=0;
 

RControlWifi:: init(long speedd=115200,String Ip="192.168.5.1", String Port="1001")
{  
wifiSerial.begin(speedd);
while (!wifiSerial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
sendToWifi("AT+CWMODE=2",responseTime); // configure as access point
  sendToWifi("AT+CIPAP_DEF=\""+Ip+"\"",responseTime); // get ip address
  sendToWifi("AT+CIPMUX=1",responseTime); // configure for multiple connections
  sendToWifi("AT+CIPSERVER=1,"+Port,responseTime); // turn on server on port 80

  sendToUno("Wifi connection is running!",responseTime);

 }
void RControlWifi::listen (){
	
	if(wifiSerial.available()>0){
    
    String message = readWifiSerialMessage();
    sendToUno(message,responseTime);
    
    if(find(message,"PinA")){
      //turn on built in LED:
     
       sendDataWifi("\\n"+pinA);
    }else 
		if(find(message,"PinD")){
      //turn off built in LED:
     
        sendDataWifi(pinD);
    }else
    if(find(message,"AC")){
      ACommands(message);
    }else
    if(find(message,"DC")){
      DCommands(message);
    }else
	if(find(message,"test")){
     sendDataWifi("OK");
    }
    
   
	}
  delay(responseTime);
}
void RControlWifi::ACommands(String message)
{
 message=message.substring(message.indexOf(":")+3,message.length());
 String Type =message.substring(0,message.indexOf(","));

 float result=0;
     message=message.substring(message.indexOf(",")+1,message.length());
 uint8_t s=atoi(message.substring(0,message.indexOf(",")).c_str());
  if(Type=="Out"){
    
    message=message.substring(message.indexOf(",")+1,message.length());
  int value=message.substring(0,message.length()).toInt();
 
  analogWrite(s,value);}
  
  
   
	 result=analogRead(s);
  sendDataWifi(String(result)); 
delay(10);  
    }
  
void RControlWifi::DCommands(String message)
{
 message=message.substring(11,message.length());
 String Type =message.substring(0,message.indexOf(","));
int result=0;
 message=message.substring(message.indexOf(",")+1,message.length());

 uint8_t s=atoi(message.substring(0,message.indexOf(",")).c_str());
  
  message=message.substring(message.indexOf(",")+1,message.length());
if(Type=="Out"){
   if(digitalRead(s)==HIGH){digitalWrite(s,LOW);}
   else{ digitalWrite(s,HIGH);}
   }
  
  else{
    
    result=digitalRead(s);

  sendDataWifi(String(result));  
    
    }
  }

/*
* Name: sendData
* Description: Function used to send string to tcp client using cipsend
* Params: 
* Returns: void
*/

void RControlWifi::sendDataWifi(String str){
 
  String len="";
  len+=str.length();
   
  sendToWifi("AT+CIPSEND=0,"+len,responseTime);
  delay(100);
  sendToWifi(str,responseTime);
  delay(100);
 
}


boolean RControl::find(String string, String value){
  return string.indexOf(value)>=0;
}


/*
* Name: readWifiSerialMessage
* Description: Function used to read data from ESP8266 Serial.
* Params: 
* Returns: The response from the esp8266 (if there is a reponse)
*/
String  RControlWifi::readWifiSerialMessage(){
  char value[100]; 
  int index_count =0;
  while(wifiSerial.available()>0){
    value[index_count]=wifiSerial.read();
    index_count++;
    value[index_count] = '\0'; // Null terminate the string
  }
  String str(value);
  str.trim();
  return str;
}
/*
* Name: sendToWifi
* Description: Function used to send data to ESP8266.
* Params: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
* Returns: The response from the esp8266 (if there is a reponse)
*/
String RControlWifi::sendToWifi(String command, const int timeout){
  String response = "";
  wifiSerial.println(command); // send the read character to the esp8266
  long int time = millis();
  while( (time+timeout) > millis())
  {
    while(wifiSerial.available())
    {
    // The esp has data so display its output to the serial window 
    char c = wifiSerial.read(); // read the next character.
    response+=c;
    }  
  }
 
  return response;
}

/*
* Name: sendToUno
* Description: Function used to send data to Arduino.
* Params: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
* Returns: The response from the esp8266 (if there is a reponse)
*/
String RControl::sendToUno(String command, const int timeout){
	
  String response = "";
  Serial.println(command); // send the read character to the esp8266
  long int time = millis();
  while( (time+timeout) > millis())
  {
    while(Serial.available())
    {
      // The esp has data so display its output to the serial window 
      char c = Serial.read(); // read the next character.
      response+=c;
    }  
  }
  
  return response;
}
RControlBluetooth:: init(long speedd=9600)
{ BluetoothSerial.begin(speedd);
Serial.begin(speedd);
   sendToUno("Bluetooth is running!",responseTime);
 }
void RControlBluetooth::listen (){
	if(BluetoothSerial.available()>0){
    delay(4);
    String message = readBluetoothSerialMessage();
    sendToUno(message,responseTime);
   
    
    if(find(message,"PinA")){
    
     
       sendDataBluetooth("\\n"+pinA,responseTime);
    }else if(find(message,"PinD")){
    
     
        sendDataBluetooth(pinD,responseTime);
    }else
    if(find(message,"AC")){
      ACommands(message);
    }else
    if(find(message,"DC")){
      DCommands(message);
    }else
	if(find(message,"test")){
     sendDataBluetooth("OK",responseTime);
    }
    
   
  }
  delay(responseTime);
}
void RControlBluetooth::ACommands(String message)
{
 message=message.substring(2,message.length());
 String Type =message.substring(0,message.indexOf(","));

 float result=0;
     message=message.substring(message.indexOf(",")+1,message.length());
 uint8_t s=atoi(message.substring(0,message.indexOf(",")).c_str());
  if(Type=="Out"){
    
    message=message.substring(message.indexOf(",")+1,message.length());
  int value=message.substring(0,message.length()).toInt();
 
  analogWrite(s,value);}
  
  else{
	  
    
	 result=analogRead(s);
 
  sendDataBluetooth(String(result),responseTime);  
    }
  }
void RControlBluetooth::DCommands(String message)
{
 message=message.substring(2,message.length());
 
 String Type =message.substring(0,message.indexOf(","));
int result=0;
 message=message.substring(message.indexOf(",")+1,message.length());

 uint8_t s=atoi(message.substring(0,message.indexOf(",")).c_str());
  
  message=message.substring(message.indexOf(",")+1,message.length());
  
if(Type=="Out"){
   if(digitalRead(s)==1){digitalWrite(s,LOW);}
   else{ digitalWrite(s,HIGH);}
   }
  
  else{
    
    result=digitalRead(s);
 
  sendDataBluetooth(String(result),responseTime);  
    
    }
  }

/*
* Name: sendDataBluetooth
* Description: Function used to send string to Bluetooth
* Params: command - the data/command to send; 
* Returns: void
*/


void RControlBluetooth::sendDataBluetooth(String command, const int timeout){
 
 BluetoothSerial.println(command);
  delay(100);
  
}





/*
* Name: readBluetoothSerialMessage
* Description: Function used to read data from HC-05 Serial.
* Params: 
* Returns: The response from the HC-05 (if there is a reponse)
*/
String  RControlBluetooth::readBluetoothSerialMessage(){
  char value[100]; 
  int index_count =0;
 
  while(BluetoothSerial.available()>0){
    value[index_count]=BluetoothSerial.read();
    index_count++;
    value[index_count] = '\0'; // Null terminate the string
  }
  String str(value);
  str.trim();
  return str;
  
}

