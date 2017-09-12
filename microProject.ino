#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

MDNSResponder mdns;

// Replace with your network credentials
const char* ssid = "Kasun";
const char* password = "12345678";

ESP8266WebServer server(80);

String webPage = "";

int m11 = D0;
int m12 = D1;
int m21=D2;
int m22=D3;
const int trigPin = D6;
const int echoPin = D7;
//int ENA=D5;
//int ENB=D6;
long duration;
long cm;
int distance;
void setup(void){
  webPage += "<center><h1>Micro Controller Project</h1></center><style>.button{background-color: #4CAF50;}</style><style>.stopBtn{background-color: #FF0000;}</style><center><h1><p><a href=\"left\"><button style=\"width:150px;height:100px;\"><h1>Left</h1></button></a>&nbsp;<a href=\"right\"><button id=\"b\" style=\"width:150px;height:100px;\" ><h1>Right</h1></button></a></p></h1></center><script>function f1(){location.href=\"http://192.168.43.208/backward\";}function f2(){location.href=\"http://192.168.43.208/stop\";}</script>";
  webPage += "<p> <center><a href=\"forward\"><button class=\"button\" style=\"width:150px;height:100px;\"><h1>Forward</h1></button></a></center>&nbsp;<a href=\"backward\"><center><button class=\"button\" style=\"width:150px;height:100px;\"><h1>Backward</h1></button></a></p></center>";
  webPage += "<p> <center><a href=\"stop\"><button class=\"stopBtn\" style=\"width:200px;height:100px;\"><h1>Stop</h1></button></a></center><script>document.onkeydown=myFunction ;function myFunction(event) {  var x = event.which || event.keyCode;if(x=='38'){location.href=\"http://192.168.43.208/forward\";}else if(x=='40'){location.href=\"http://192.168.43.208/backward\";}else if(x=='37'){location.href=\"http://192.168.43.208/left\";}else if(x=='39'){location.href=\"http://192.168.43.208/right\";}else if(x=='32'){location.href=\"http://192.168.43.208/stop\";}}</script><script>document.onkeyup=stopFunction;function stopFunction{location.href=\"http://192.168.43.208/stop\";}</script>";
  
  
  // preparing GPIOs
  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  pinMode(m21, OUTPUT);
  pinMode(m22, OUTPUT);
 // pinMode(ENA,OUTPUT);
  //pinMode(ENB,OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
//Serial.begin(9600); // Starts the serial communication
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }
  
  server.on("/", [](){
    server.send(200, "text/html", webPage);
  });
  server.on("/forward", [](){
   // analogWrite(ENA,100);
    //analogWrite(ENB,100);
    server.send(200, "text/html", webPage);
    digitalWrite(m11, HIGH);
    digitalWrite(m12, LOW);
    digitalWrite(m21, HIGH);
    digitalWrite(m22, LOW);
    delay(1000);
  });
  server.on("/backward", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(m11, LOW);
    digitalWrite(m12, HIGH);
    digitalWrite(m21, LOW);
    digitalWrite(m22, HIGH);
    delay(1000); 
  });
  server.on("/right", [](){
    server.send(200, "text/html", webPage);
   digitalWrite(m11, HIGH);
    digitalWrite(m12, LOW);
    digitalWrite(m21, LOW);
    digitalWrite(m22, LOW);
    delay(1000);
  });
  server.on("/left", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(m11, LOW);
    digitalWrite(m12, LOW);
    digitalWrite(m21, HIGH);
    digitalWrite(m22, LOW);
    delay(1000); 
  });
  server.on("/stop", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(m11, LOW);
    digitalWrite(m12, LOW);
    digitalWrite(m21, LOW);
    digitalWrite(m22, LOW);
    delay(1000);
  });
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void){
  server.handleClient();
  sensorDistance();
} 


void sensorDistance(){
  // Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
distance=(duration/29)/2;
// Calculating the distance
//distance= (duration*0.034)/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance); 

delay(4000);
}

