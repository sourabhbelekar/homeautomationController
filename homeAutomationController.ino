#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include <aREST.h>
#include <aREST_UI.h>
#include <Ticker.h>
#include <ESP8266HTTPClient.h>

Ticker heartbeat;

int refreshTime=10;
int ticker=0;
#define D0 16
#define D1 5
#define D2 4
#define D3 0
#define D4 2
#define D5 14
#define D6 12
#define D7 13
#define D8 15
#define D9 03
#define D10 01

#define buttonPin D1
#define buttonPin2 D2

#define eepromLocation 0

#define deviceName "Classroom 205"
#define registerDeviceURL "http://raspberrypi/register"

// WiFi parameters
const char* ssid = "Haha";
const char* password = "12345678";


// The port to listen for incoming TCP connections
#define LISTEN_PORT           80

// Create an instance of the server
WiFiServer server(LISTEN_PORT);

// Create aREST instance
aREST_UI rest = aREST_UI();


void setup(void) {

  pinMode(buttonPin, INPUT);
  pinMode(buttonPin2, INPUT);

  
  Serial.begin(115200);
  
  
  rest.title("Class 205 Controller");

  // Create button to control pin 5
  rest.button(5,"Fan");
  rest.button(6,"Light");

  // Give name and ID to device
  rest.set_id("1");
  rest.set_name("esp8266");
 
  
  EEPROM.begin(10);
  restoreState();




  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
  heartbeat.attach(1.0, updateStatusCounter);
}

void loop() {


if(ticker<=0){
  
        String postData="";
      
      IPAddress ip = WiFi.localIP();
      postData.concat("{\"name\" :\"");
      postData.concat(deviceName);
      postData.concat("\",\"ipaddr\" : \"");
      postData.concat(ip.toString());
      postData.concat("\"}");
    
    if(WiFi.status()== WL_CONNECTED){
       HTTPClient http;    
     
       http.begin(registerDeviceURL);      
       http.addHeader("Content-Type", "application/json");  
     
       int httpCode = http.POST(postData);   
       String payload = http.getString();    
    
       
       Serial.println(postData);
       Serial.println(httpCode);   
       Serial.println(payload);    
     
      http.end();  
      ticker=refreshTime;
    }
  }

if(digitalRead(buttonPin) == HIGH )
    {
      digitalWrite(D6,!digitalRead(D6));
      saveState();
    }


if (digitalRead(buttonPin2) == HIGH){
    digitalWrite(D5,!digitalRead(D5));
    saveState();
  }

// Handle REST calls
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while (!client.available()) {
    delay(1); 
  }
  rest.handle(client);
  saveState();


}
// Save the state of the lights using bitWrite()
void saveState(){
  unsigned char lights = 0;

   bitWrite(lights, 0, digitalRead(D5));
   bitWrite(lights, 1, digitalRead(D6));
   
  //Serial.println("Storing state to EEPROM");
  //Serial.println(lights);
  EEPROM.write(eepromLocation, lights);
  EEPROM.commit();
}

// restore the lights using bitRead() 
void restoreState(){
  unsigned char lights = EEPROM.read(eepromLocation);

   digitalWrite(D5, bitRead(lights, 0));
   digitalWrite(D6, bitRead(lights, 1));
  // Serial.println("Reading state from EEPROM");
  // Serial.println(lights);
}
void updateStatusCounter(){

ticker = ticker-1;
  }
