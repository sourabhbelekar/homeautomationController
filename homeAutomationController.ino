#include <EEPROM.h>

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

void setup(void) {

  pinMode(buttonPin, INPUT);
  pinMode(D5,OUTPUT);
  pinMode(D6,OUTPUT);
  
  EEPROM.begin(10);
  restoreState();
}

void loop() {

if(digitalRead(buttonPin) == HIGH )
    {
      digitalWrite(D6,!digitalRead(D6));
      saveState();
    }


if (digitalRead(buttonPin2) == HIGH){
    digitalWrite(D5,!digitalRead(D5));
    saveState();
  }

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
