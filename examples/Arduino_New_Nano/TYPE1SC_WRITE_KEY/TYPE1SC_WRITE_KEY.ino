#include "TYPE1SC.h"

#include "aws_credentials.h"

#define DebugSerial Serial
#define M1Serial Serial1

TYPE1SC TYPE1SC(M1Serial, DebugSerial);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

#if defined(ARDUINO_NANO_ESP32)
  M1Serial.begin(115200, SERIAL_8N1, D0, D1); 
#else
  M1Serial.begin(115200);
#endif
  DebugSerial.begin(115200);
  DebugSerial.println("TYPE1SC Module Start!!!");

  /* Board Reset */
  TYPE1SC.reset();
  delay(2000);

  /* TYPE1SC Module Initialization */
  if (TYPE1SC.init()) {
    DebugSerial.println("TYPE1SC Module Error!!!");
  }

  /* Network Regsistraiton Check */
  while (TYPE1SC.canConnect() != 0) {
    DebugSerial.println("Network not Ready !!!");
    delay(2000);
  }

  DebugSerial.println("TYPE1SC Module Ready!!!");

  /* DELETE Certification Profile 1-255 */
  int delProfile = 9;
  if (TYPE1SC.delCert(delProfile) == 0) {
    DebugSerial.println("Delete Certification Profile!!!");
  }
  delay(2000);

  /* Write root CA, Don't edit the file name */
  if (TYPE1SC.writeKEY("rootCA.pem", 0, rootCA) == 0) {
    DebugSerial.println("Root CA Write!!!");
  }
  delay(5000);

  /* Write client CA, Don't edit the file name */
  if (TYPE1SC.writeKEY("cert.pem.crt", 0, clientCrt) == 0) {
    DebugSerial.println("Client CA Write!!!");
  }
  delay(5000);

  /* Write client KEY, Don't edit the file name */
  if (TYPE1SC.writeKEY("private.pem.key", 1, clientKey) == 0) {
    DebugSerial.println("Client KEY Write!!!");
  }
  delay(5000);

  /* ADD Certification Profile 1-255 */
  int addProfile = 9;
  if (TYPE1SC.addCert(addProfile) == 0) {
    DebugSerial.println("ADD Certification Profile!!!");
  }
}

void loop() { delay(1000); }
