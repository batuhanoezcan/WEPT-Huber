#include <FahrzeugLib.h>
//Die Fahrzeuglibary wird hier integriert. 

#define trigger1 7 
#define echo1 A5 
#define trigger2 9 
#define echo2 A4
#define trigger3 8
#define echo3 A3 

//Hier werden den verschiedenen Parametern die jeweiligen Ports zugewiesen.

long dauer = 0;
long distance = 0;

//Es werden zwei Variablen für die Dauer des Signals, sowie die Distance erstellt. Diese werden später für das 
//Berechnen der Distanz zum Objekt verwendet. 

CMotor MotorRechts(5,4);
CMotor MotorLinks(3,2);
//Die Ports der beiden Motoren werden gesetzt.

CAntrieb Antrieb (&MotorLinks, &MotorRechts);

long messenMitte() {
digitalWrite(trigger1, LOW);
delay(5);
digitalWrite(trigger1, HIGH);
delay(5);
digitalWrite(trigger1, LOW);
dauer = pulseIn(echo1, HIGH);
distance = (dauer/2) * 0.03432;
return distance;   
}

long messenLinks() {
  digitalWrite(trigger2, LOW);
  delay(5);
  digitalWrite(trigger2, HIGH);
  delay(5);
  digitalWrite(trigger2, LOW);
  dauer = pulseIn(echo2, HIGH);
  distance = (dauer/2) * 0.03432;
  return distance;
}

long messenRechts() {
  digitalWrite(trigger3, LOW);
  delay(5);
  digitalWrite(trigger3, HIGH);
  delay(5);
  digitalWrite(trigger3, LOW);
  dauer = pulseIn(echo3, HIGH);
  distance = (dauer/2) * 0.03432;
  return distance;
}

//Es werden drei Funktionen erstellt, wobei jede den Abstand vom jeweiligen Sensor zum Objekt misst.
//Dabei wird über den Trigger Port ein Signal ausgegeben und über den echo Port eingelesen. 
//Wir messen dabei die Zeit, welche vom aussenden der Welle bis zum einlesen vergeht. 
//Daraus berechnen wir schlussendlich die Distanz des Sensors zum Objekt.


void setup() {
  Serial.begin(9600);
  pinMode(trigger1, OUTPUT);
  pinMode(trigger2, OUTPUT);
  pinMode(trigger3, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(echo2, INPUT);
  pinMode(echo3, INPUT);
}

//In der Setup Methode werden die jeweiligen Ein- und Ausgänge als In- oder Output definiert.

void loop() {
  Serial.println(messenMitte());
  if((messenMitte() > 16) && (messenRechts() > 16) && (messenLinks() > 16)){
    Antrieb.Kurve(0, 120, true);
  }
  else if(messenLinks() < 26){
    Antrieb.Kurve(75, 135, true);
  }
  else if(messenRechts() < 22){
    Antrieb.Kurve(-90, 135, true);
  }
}

//In der loop Methode, welche wir über die ganze Zeit ausführen, werden nun durch das Ausüben der oben 
//implementierten Funktionen die Abstände der jeweiligen Sensoren zum Objekt vermessen und dadurch die Motoren 
//angesteuert. Durch die individuelle Ansteuerung der beiden Sensoren, kann das HTL-Car eine Kurve fahren und 
//so den Rundkurs meistern.
