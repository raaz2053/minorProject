
#include<Servo.h>
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11);
SoftwareSerial mySerial1(12, 13); //gsm ko Tx to D8 and Rx to D9

Servo myservo;
int pos = 0;
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup()
{

  Serial.begin(9600);
  mySerial1.begin(9600);   //gsmModule baud
  Serial.println("Keyless bike");
  Serial.println("\n");
  Serial.println("Raju Sharan");
  Serial.println("Samrat Malla");
  Serial.println("Subham Shrestha");
  Serial.println("YuvRaj Panti");

  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  Serial.println("\n\nAdafruit finger detect test");
  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) {
      delay(1);
    }
  }

  finger.getTemplateCount();
  Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  Serial.println("Waiting for valid finger...");
  myservo.attach(9);
}

void loop()                     // run over and over again
{
  getFingerprintIDez();
  digitalWrite(12, HIGH);
  delay(50);            //don't ned to run this at full speed.

}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }

  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);

  return finger.fingerID;
}





// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK) {
    Serial.print("Oe gadha khatey... arkako bike chalauxas.. calling owner");
    MakeCall();
  }


  // found a match!
  Serial.print("Found ");
  if (finger.fingerID == 2) {
    Serial.print("Raju");
    servo();
  }
  else if (finger.fingerID == 3) {
    Serial.print("Samrat");
    servo();
  }
  else if (finger.fingerID == 1) {
    Serial.print("YuvRaj Panti");
    servo();
  }
  // Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID;
}

void MakeCall()
{
  mySerial1.println("ATD9848548444;"); // ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!
  delay(45000);
  mySerial1.println("ATH");
}

void servo() {
  for (pos = 0; pos <= 90; pos++) {
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
