/*
Send ArtNet commands to client.
This example may be copied under the terms of the MIT license, see the LICENSE file for details
*/

#include "Artnet/Artnet.h"

Artnet artnet;

void setup() {
    Serial.begin(9600);

	// Start listening for Art-Net packages
	// Call onDmxFrame when receiving one
    artnet.begin();
    artnet.sendBroadcast();
}

void loop() {   
}