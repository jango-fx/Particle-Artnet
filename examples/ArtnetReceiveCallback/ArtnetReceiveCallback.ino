// This #include statement was automatically added by the Particle IDE.
#include "Artnet/Artnet.h"

Artnet artnet;

void setup() {
    Serial.begin(9600);
    
    artnet.begin();
    artnet.setArtDmxCallback(onDmxFrame);
    
    pinMode(D7, OUTPUT);
    digitalWrite(D7, HIGH);
}

void loop() {
    artnet.read();
}

void onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data)
{
  // print out our data
  Serial.print("universe number = ");
  Serial.print(universe);
  Serial.print("\tdata length = ");
  Serial.print(length);
  Serial.print("\tsequence n0. = ");
  Serial.println(sequence);
  Serial.print("\tDMX data: ");
  for (int i = 0 ; i < length ; i++)
  {
    Serial.print(data[i]);
    Serial.print("  ");
  }
  Serial.println();
  Serial.println();

    digitalWrite(D7, data[0] != 0);
}
