/*
This is similar to ArtnetReceive but uses a callback to read the data.
This example may be copied under the terms of the MIT license, see the LICENSE file for details
*/

#include "Artnet/Artnet.h"

Artnet artnet;

void setup() {
    Serial.begin(9600);

	// Start listening for Art-Net packages
	// Call onDmxFrame when receiving one
    artnet.begin();
    artnet.setArtDmxCallback(onDmxFrame);
}

void loop() {
	// Process pending Art-Net packages
    artnet.read();
}

void onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data)
{
  // Print out the data received
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
  
  // Control the RGB LED with the first 3 channels of universe 11
  if (universe == 11 && length >= 3) {
      RGB.control(true);
      
      RGB.color(data[0], data[1], data[2]);
      RGB.brightness(255);
  } else {
      RGB.control(false);
  }
}
