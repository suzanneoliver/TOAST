#include <SoftwareSerial.h>

SoftwareSerial mySerial(13,12); //RX,T

void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  while(!Serial)
  { 
    ;
  }

  Serial.println("Test 1");

  mySerial.begin(19200);
  mySerial.println("Test 2");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (mySerial.available())
  {
    Serial.write(mySerial.read());
  }

  if (Serial.available())
  {
    mySerial.write(Serial.read());
  }
}
