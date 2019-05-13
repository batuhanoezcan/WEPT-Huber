#include <FahrzeugLib.h>

#define sensorLinks 11 
#define sensorRechts 12 
#define sensorMitte 10

CMotor MotorRechts(5,4);
CMotor MotorLinks(3,2);

CAntrieb Antrieb (&MotorLinks, &MotorRechts);

boolean messenLinks(){
  return digitalRead(sensorLinks);
}

boolean messenMitte(){
  return digitalRead(sensorMitte);
}

boolean messenRechts(){
  return digitalRead(sensorRechts);
}

void setup() {
  Serial.begin(9600);
  pinMode(sensorLinks, INPUT);
  pinMode(sensorRechts, INPUT);
  pinMode(sensorMitte, INPUT);
}

void loop() {
  if((messenRechts() == false) && (messenLinks() == false) && (messenMitte() == true)){
    Antrieb.Kurve(0, 200, true);
  }
  
  else if(messenLinks() == true){
    Antrieb.Kurve(-90, 175, true);
  }
  else if(messenRechts() == true){
    Antrieb.Kurve(75, 175, true);
  }
}
