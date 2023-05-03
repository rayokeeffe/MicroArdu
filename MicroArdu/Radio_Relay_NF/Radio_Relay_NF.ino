#include <NRF52_Radio_library.h>
#include <Adafruit_Microbit.h>
#include <multi_channel_relay.h>

//Initalise functions
Adafruit_Microbit_Matrix matrix;
NRF52_Radio MicrobitRadio = NRF52_Radio();
Multi_Channel_Relay relay;

//Global variables
const int POWER = 7;
const int GROUPCODE = 10;
const int FREQBAND = 50;
String message;
FrameBuffer* myDataSendData;


void setup() {
  Serial.begin(115200);
  Serial.println("nRF52 Radio & Relays Starting...");

  // Set up Front Push Buttons
  pinMode(PIN_BUTTON_A, INPUT);
  pinMode(PIN_BUTTON_B, INPUT);
  
  // Set I2C address and start relay
  relay.begin(0x11);
  Serial.println("Relay OK");

  //Setup Radio Paramters
  myDataSendData = new FrameBuffer();
  MicrobitRadio.setTransmitPower(POWER);
  MicrobitRadio.enable(); 
  MicrobitRadio.setGroup(GROUPCODE);
  MicrobitRadio.setFrequencyBand(FREQBAND);
  Serial.println("Radio OK");
}

void loop() {
  // put your main code here, to run repeatedly:

}
