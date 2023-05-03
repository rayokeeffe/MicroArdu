#include "NRF52_Radio_library.h"
#include <Adafruit_Microbit.h>

Adafruit_Microbit_Matrix matrix;
NRF52_Radio MicrobitRadio = NRF52_Radio();
const int POWER = 7;
const int GROUPCODE = 10;
const int FREQBAND = 50;

FrameBuffer* myDataSendData;
String message;

void setup() {
  Serial.begin(115200);
  Serial.println("nRF52 Radio Library starting....");
  matrix.begin();
  pinMode(PIN_BUTTON_A, INPUT);
  pinMode(PIN_BUTTON_B, INPUT);

  myDataSendData = new FrameBuffer();
  MicrobitRadio.setTransmitPower(POWER);
  //MicrobitRadio.hello("Test");
  MicrobitRadio.enable(); 
  MicrobitRadio.setGroup(GROUPCODE);
  MicrobitRadio.setFrequencyBand(FREQBAND);

}


void loop() {
  // put your main code here, to run repeatedly:

  //Rx
  FrameBuffer* myData = MicrobitRadio.recv();
  if (myData != NULL) {
    // Print the received data
    Serial.print("Received data: ");
    for (int i = 0; i < myData->length; i++) {
      String Rec_string = String((char)myData->payload[i]);
      Serial.print(Rec_string);
      //Serial.println(message);
      //Serial.print(" ");
      //if (i > 9)
      //{
      //  message +=Rec_string;
      //}
    }
    Serial.println();
    Serial.println(message);
    message = "";
  }

  if (digitalRead(PIN_BUTTON_A) == 0)
  {
    String Data = "Hello MicroBit";
    //Tx
    Serial.println("Sending data: ");
    //Data = Data.substring(0, 30);             
    //myDataSendData->length = Data.length() + 3;  
    //myDataSendData->group = GROUPCODE;
    //myDataSendData->version = 12;
    //myDataSendData->protocol = 14;
    for (uint8_t i = 0; i < Data.length(); i++) {
      myDataSendData->payload[i] = Data.charAt(i);
      //Serial.println(Data.charAt(i));
    }
  
    MicrobitRadio.send(myDataSendData);
    for (int i = 0; i < myDataSendData->length; i++) {
      String Tx_string = String((char)myDataSendData->payload[i]);
      if (i > 9)
      {
        message +=Tx_string;
      }
    }
    Serial.println();
    Serial.println(message);
    message = "";
  }

}
