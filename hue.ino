/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <WiFi.h>
#include <BluetoothSerial.h>

int pins[] = {27,15, 14, 4};
int thresholds[] = {38, 31, 36, 32};
String colors[] = {"hue_red", "hue_green", "hue_purple", "hue_blue"};






BluetoothSerial SerialBT;


const char* ssid     = "SSID"; // your network SSID (name)
const char* password = "password"; // your network password
const char* IFTTT_KEY = "IFTTT_KEY"; // your IFTTT key

const char* host = "maker.ifttt.com";


void setup()
{
  
    Serial.begin(115200);
    SerialBT.begin("ESP32test"); 
    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    delay(10000);
    
}



void changeColor(String color){
  
      Serial.print("connecting to ");
      Serial.println(host);
  
      // Use WiFiClient class to create TCP connections
      WiFiClient client;
      const int httpPort = 80;
      if (!client.connect(host, httpPort)) {
          Serial.println("connection failed");
          return;
      }
  
      // We now create a URI for the request
      String url = "/trigger/"+ color + IFTTT_KEY; //{API_KEY} is the private key
  
      Serial.print("Requesting URL: ");
      Serial.println(url);
  
      // This will send the request to the server
      client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                   "Host: " + host + "\r\n" +
                   "Connection: close\r\n\r\n");
      unsigned long timeout = millis();
      while (client.available() == 0) {
          if (millis() - timeout > 5000) {
              Serial.println(">>> Client Timeout !");
              client.stop();
              return;
          }
      }
  
      // Read all the lines of the reply from server and print them to Serial
      while(client.available()) {
          String line = client.readStringUntil('\r');
          Serial.print(line);
      }
  
      Serial.println();
      Serial.println("closing connection");

  }

void plotVals(){
    // Used for bluetooth debugging
  for(int i = 0; i < 4; i++){
    
      int read = touchRead(pins[i]);
      SerialBT.print(read);
      SerialBT.print(" ");
    }
    SerialBT.println("");
}
void loop()
{

    plotVals();
    for(int i = 0; i < 4; i++){
      Serial.print("Threshold Number ");
      Serial.print(i);
      Serial.print(": ");
      int read = touchRead(pins[i]);
      Serial.println(read);
      if(read < thresholds[i]){
        for(int j = 0; j < 4; j++){
          if(touchRead(pins[i]) > thresholds[i]) break;
        }
        changeColor(colors[i]);
        delay(3000);
       }
    }
}
