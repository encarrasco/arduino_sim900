#include <SoftwareSerial.h>
SoftwareSerial SIM(7, 8); //Seleccionamos los pines 7 como Rx y 8 como Tx


void setup()
{
SIM.begin(115200);  //Configura velocidad del puerto serie para el Serial1
Serial.begin(115200);  //Configura velocidad del puerto serie del Arduino

}


void loop()
{
csv_send();
}

void csv_send(){

String a="write_api_key=XXXXXXXXXXXXXXXX&time_format=absolute&updates="; //60  char
String b="2004-06-14T12:12:22,1|2004-06-14T12:13:22,2|";
String c=a+b;
SIM.println(F("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\""));  
delay(2000);
SIM.println(F("AT+SAPBR=3,1,\"APN\",\"bam.entelpcs.cl\""));  
delay(2000);
SIM.println(F("AT+SAPBR=3,1,\"USER\",\"entelpcs\""));  
delay(2000);
SIM.println(F("AT+SAPBR=1,1"));  
delay(8000);
SIM.println(F("AT+HTTPINIT")); 
delay(3000);
SIM.println(F("AT+HTTPSSL=1")); 
delay(3000);
SIM.println(F("AT+HTTPPARA=\"CID\",\"1\"")); 
delay(3000);
SIM.println(F("AT+HTTPPARA=\"PROPORT\",\"80\"")); 
delay(3000);
SIM.println(F("AT+HTTPPARA=\"URL\",\"https://api.thingspeak.com/channels/XXXXXX/bulk_update.csv\"")); 
delay(3000);
SIM.println(F("AT+HTTPPARA=\"CONTENT\",\"application/x-www-form-urlencoded\"")); 
delay(3000);
SIM.println("AT+HTTPDATA="+String(tama(nombre_archivo)+60)+",20000"); 
delay(1000);
//SIM.println(a_enviar); 
SIM.print(a);
leerSD_corrido_SIM900(nombre_archivo);
delay(3000);
SIM.println(F("At+HTTPACTION=1")); 
delay(10000);
SIM.println(F("AT+HTTPREAD")); 
delay(5000);
SIM.println(F("AT+SAPBR=0,1")); 
delay(3000);
SIM.println(F("AT+HTTPTERM")); 
Serial.println(F("enviado"));
delay(2000);
SIM.end();
}
