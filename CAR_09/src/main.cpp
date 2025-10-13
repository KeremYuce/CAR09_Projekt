#include <Arduino.h>

// Gleichstrommotor 1
int GSM1 = 10;
int in1 = 9;
int in2 = 8;
// Gleichstrommotor 2
int GSM2 = 5;
int in3 = 7;
int in4 = 6;

// IR-Sensor Pin
int IRmitteSensorPin = A5;  // Der Sensor ist am analogen Pin A0 angeschlossen
int IRrechtsSensorPin = A1;  // Der Sensor ist am analogen Pin A0 angeschlossen
int IRlinksSensorPin = A0;  // Der Sensor ist am analogen Pin A0 angeschlossen


void setup() {
  pinMode(GSM1, OUTPUT);
  pinMode(GSM2, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.begin(9600);  // Serielle Kommunikation für die Ausgabe
}

void loop() {
  // Motorsteuerung
  digitalWrite(in1, HIGH);  // Motor 1 beginnt zu rotieren
  digitalWrite(in2, LOW);
  analogWrite(GSM1, 200);  // Motor 1 soll mit der Geschwindigkeit "200"

  digitalWrite(in3, HIGH);  // Motor 2 beginnt zu rotieren
  digitalWrite(in4, LOW);
  analogWrite(GSM2, 200);  // Motor 2 soll ebenfalls mit der Geschwindigkeit "200"
  
  delay(2000);  // Warte 2 Sekunden, bevor der Sensorwert ausgelesen wird

  // Aufruf der Funktion zum Messen der Entfernung
    int sensorValuemitte = analogRead(IRmitteSensorPin);
    Serial.print("Sensorwert mitte: ");
    Serial.println(sensorValuemitte);  // Ausgabe des gemessenen Werts auf dem seriellen Monitor
  delay(500);  // Kleine Verzögerung, um die Stabilität des Werts zu prüfen

// Aufruf der Funktion zum Messen der Entfernung
    int sensorValuerechts = analogRead(IRrechtsSensorPin);
    Serial.print("Sensorwert rechts: ");
    Serial.println(sensorValuerechts);  // Ausgabe des gemessenen Werts auf dem seriellen Monitor
  delay(500);  // Kleine Verzögerung, um die Stabilität des Werts zu prüfen

  // Aufruf der Funktion zum Messen der Entfernung
    int sensorValuelinks = analogRead(IRlinksSensorPin);
    Serial.print("Sensorwert links: ");
    Serial.println(sensorValuelinks);  // Ausgabe des gemessenen Werts auf dem seriellen Monitor
  delay(500);  // Kleine Verzögerung, um die Stabilität des Werts zu prüfen


}
