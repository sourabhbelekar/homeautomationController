/*
  This a simple example of the aREST UI Library for the ESP8266.
  See the README file for more details.

  Written in 2014-2016 by Marco Schwartz under a GPL license.
*/
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


void setup(void) {

  pinMode(buttonPin, INPUT);
  pinMode(D5,OUTPUT);
  pinMode(D6,OUTPUT);
  
}

void loop() {

if(digitalRead(buttonPin) == HIGH )
    {
      digitalWrite(D6,!digitalRead(D6));
    }


if (digitalRead(buttonPin2) == HIGH){
    digitalWrite(D5,!digitalRead(D5));

  }

}
