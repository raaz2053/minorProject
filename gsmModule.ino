#include <SoftwareSerial.h>
SoftwareSerial mySerial(12,13); //gsm ko Tx to D8 and Rx to D9
char msg;
char call;

void setup()
{
  mySerial.begin(9600);   //gsmModule baud  
  Serial.begin(9600);    //Serial Monitor (Arduino)baud
  Serial.println("GSM SIM900A BEGIN");
  Serial.println("K garne ta baklol??");
  Serial.println("call disconnect garna 'h' press gar");
  Serial.println("call receive garna 'i' press gar");
  Serial.println("message pathauna 's' press gar");
  Serial.println("call garna 'c' press gar");  
  Serial.println("redial garna 'r' press gar");
  Serial.println("message padhna 'm' press gar");
  Serial.println();
  delay(100);
}

void loop()
{  
  if (Serial.available()>0)
   switch(Serial.read())
  {
    case 's':
      SendMessage();
      break;
    case 'c':
      MakeCall();
      break;
    case 'h':
      HangupCall();
      break;
    case 'e':
      RedialCall();
      break;
    case 'i':
      ReceiveCall();
      break;
      case 'm':
      ReceiveMessage();
      break;
  }
 if (mySerial.available()>0)
 Serial.write(mySerial.read());
}

 /*void SendMessage()
{
  mySerial.println("AT+CMGF=1");//Text Mode
  delay(1000);
  mySerial.println("AT+CMGS=\"90011\"\r");
  delay(1000);
 mySerial.println("ATD+9779845550055;");
 delay(1000);
 
  mySerial.println("hello bijesh");//K lekhna mann xa lekh
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
*/
void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+9779843401965\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("I am SMS from GSM Module");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
void ReceiveMessage()
{
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to recieve a live SMS
  delay(1000);
  if (mySerial.available()>0)
  {
    msg=mySerial.read();
    Serial.print(msg);
  }
}

void MakeCall()
{
  mySerial.println("ATD9848548444;"); // ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!
  Serial.println("Calling  "); // print response over serial port
  delay(1000);
}


void HangupCall()
{
  mySerial.println("ATH");
  Serial.println("Hangup Call");
  delay(1000);
}

void ReceiveCall()
{
  mySerial.println("ATA");
  delay(1000);
  {
    call=mySerial.read();
    Serial.print(call);
  }
}

void RedialCall()
{
  mySerial.println("ATDL");
  Serial.println("Redialing");
  delay(1000);
}
