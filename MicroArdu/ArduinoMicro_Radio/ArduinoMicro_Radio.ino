#include "NRF52_Radio_library.h"
#include <Adafruit_Microbit.h>

Adafruit_Microbit_Matrix matrix; // only needed for the matrix display

NRF52_Radio MicrobitRadio = NRF52_Radio();

const int POWER = 7; // (0..7) Set transmission power for Bluetooth radio (other settings don't seem to make a difference).
const int GROEPCODE = 10; // (0..255) Group code for Bluetooth radio. Make sure all participating Microbits use the same (unique) code!
const int FREQUENTIEBAND = 50; // (0..100) Frequency group for Bluetooth radio. Make sure all participating Microbits use the same (unique) code!

FrameBuffer* myDataSendData; // Here the data is stored (when sending) or received (when receiving).

void setup() { // set a number of things once when starting up.
Serial.begin(9600);
Serial.println("nRF52 Radio Library is starting up.");
matrix.begin();
pinMode(PIN_BUTTON_A, INPUT);
pinMode(PIN_BUTTON_B, INPUT);

myDataSendData = new FrameBuffer();
MicrobitRadio.setTransmitPower(POWER);
MicrobitRadio.hello("Test");
MicrobitRadio.enable(); // Turn on the radio
MicrobitRadio.setGroup(GROEPCODE);
MicrobitRadio.setFrequencyBand(FREQUENTIEBAND);
}

// The two lines below (the empty functions) are called 'forward declarations', I use them for readability.
// The actual functions are located below the loop() block.
void verzenden(String bericht);
String ontvangen();

void loop() { // the main program, this block is continuously looped.

String ontvangst = ontvangen(); // check if data has been received every time the loop is run
if (ontvangst.length() > 0) { // if data has been received, print the data
Serial.println(ontvangst);
}

// For the demo, no anti-dither or state change detection is used, so now there are many duplicate lines when reading the buttons.
if (!digitalRead(PIN_BUTTON_A)) {
verzenden("A");
}
if (!digitalRead(PIN_BUTTON_B)) {
verzenden("B");
}

// Display received data on the matrix display.
if (ontvangst == "A") {
matrix.print("A");
} else if (ontvangst == "B") {
matrix.print("B");
} else {
matrix.clear(); // clear the display
}
}

// Currently, sending and receiving only works with Strings. If you want to use another data type, you must first convert it.
// Conversion you may need for sending; from float to String:
// float f = 123.456; // example with float, you can also do this with integer or char.
// String mystring;
// mystring = String(f); // here the float is converted to String, you can also do this with integer or char.
// Conversion you may need for receiving; from String to float;
// Serial.println(ontvangst.toFloat());
