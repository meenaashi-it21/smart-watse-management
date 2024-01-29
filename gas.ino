#include <ESP8266WiFi.h>
String apiKey = "T43BYW9QYLESAE36"; // Enter your Write API key from ThingSpeak
const char *ssid = "Indhu"; // replace with your wifi ssid and wpa2 key
const char *pass = "indhu2403";
const char* server = "api.thingspeak.com";
WiFiClient client;
const int trigPin = 14;   
const int echoPin = 12;
long duration;  
int distance; 
void setup()
{
Serial.begin(115200);
delay(10);
Serial.println("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, pass);
while (WiFi.status() != WL_CONNECTED)
{
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
 pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output  
 pinMode(echoPin, INPUT); // Sets the echoPin as an Input  
 Serial.begin(9600); // Starts the serial communication  
  
}
void loop()
{
float h = 4;
float j = 3;
  

if (isnan(h)   and  isnan(j) and isnan(distance))
{
Serial.println("Failed to read from MQ-8 sensor!");
return;
}
 
if (client.connect(server, 80)) // "184.106.153.149" or api.thingspeak.com
{
String postStr = apiKey;
postStr += "&field1=";
postStr += "&field3=";
postStr += "&field2=";
postStr += String(h/1023*100);
postStr += String(j/1023*100);
postStr+= (duration*0.034/2); 
postStr += "r\n";
client.print("POST /update HTTP/1.1\n");
client.print("Host: api.thingspeak.com\n");
client.print("Connection: close\n");
client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
client.print("Content-Type: application/x-www-form-urlencoded\n");
client.print("Content-Length: ");
client.print(postStr.length());
client.print("\n\n\n");
client.print(postStr);
Serial.print("Carbon: ");
Serial.println(h/1023*100);
Serial.print("Methane: ");
Serial.println(j/1023*100);
// Clears the trigPin  
 digitalWrite(trigPin, LOW);  
 delayMicroseconds(2);  
 // Sets the trigPin on HIGH state for 10 micro seconds  
 digitalWrite(trigPin, HIGH);  
 delayMicroseconds(10);  
 digitalWrite(trigPin, LOW);  
 // Reads the echoPin, returns the sound wave travel time in microseconds  
 duration = pulseIn(echoPin, HIGH);  
 // Calculating the distance  
 distance= duration*0.034/2;  
 // Prints the distance on the Serial Monitor  
 Serial.print("Distance: ");  
 Serial.println(distance);  
 delay(2000);  
Serial.println("Data Send to Thingspeak");
}
 
 
  
delay(500);
client.stop();
Serial.println("Waiting...");
 
// thingspeak needs minimum 15 sec delay between updates.
delay(1500);
}
