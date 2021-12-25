// Import Dependencies

#include <SPI.h> //Serial Interface
#include <Servo.h> //Servo Library
#include "EmonLib.h" // Electric Monitoring Library for measuring AC current
EnergyMonitor emon1;

#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#include <Servo.h>
Servo actuator;

//Initialize Variables
int a;
int l;
int t;
int h;
int p;
String ctrl;
int ctr2;


void setup() {
  // Initialize Serial
  Serial.begin(9600);

  // Initalize Current Meter Parameters
  emon1.current(1, 10);

  // Initialize servo connection
  actuator.attach(10);

  // Initialize Temperature Humidity Sensor
  dht.begin();
}

void loop() {

  //Servo Reading
  a = actuator.read();

  //Light Reading
  l = analogRead(A0);

  //Humidity and Temp reading
  t = dht.readTemperature();
  h = dht.readHumidity();

  //Power reading
  p = emon1.calcIrms(1480) * 237;

  //Create data string for logging and serial
  String dataString = String(a) + " " + String(l) + " " + String(t) + " " + String(h) + " " + String(p);

  // Read and Write via serial
  Serial.println(dataString);
  ctrl = Serial.readStringUntil('\n');
  ctr2 = ctrl.toInt();
  // Issue read command to servo
  actuator.write(ctr2);
  delay(1000);
}
