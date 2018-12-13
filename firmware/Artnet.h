/*The MIT License (MIT)

Copyright (c) 2016 Stef Sijben
https://github.com/Stef-Sijben/Particle-Artnet
Copyright (c) 2014 Nathanaël Lécaudé
https://github.com/natcl/Artnet, http://forum.pjrc.com/threads/24688-Artnet-to-OctoWS2811

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef ARTNET_H
#define ARTNET_H

#include "application.h"

// UDP specific
#define ART_NET_PORT 6454
#define BROATCAST_ADDRESS {255, 255, 255, 255};
// Opcodes
#define ART_POLL 0x2000
#define ART_DMX 0x5000
// Opcodes taken from artnet4j
#define ART_POLL_REPLY 0x2100
#define ART_OUTPUT 0x5000
#define ART_ADDRESS 0x6000
#define ART_INPUT 0x7000
#define ART_TOD_REQUEST 0x8000
#define ART_TOD_DATA 0x8100
#define ART_TOD_CONTROL 0x8200
#define ART_RDM 0x8300
#define ART_RDMSUB 0x8400
#define ART_MEDIA 0x9000
#define ART_MEDIA_PATCH 0x9100
#define ART_MEDIA_CONTROL 0x9200
#define ART_MEDIA_CONTROL_REPLY 0x9300
#define ART_VIDEO_SETUP 0xa010
#define ART_VIDEO_PALETTE 0xa020
#define ART_VIDEO_DATA 0xa040
#define ART_MAC_MASTER 0xf000
#define ART_MAC_SLAVE 0xf100
#define ART_FIRMWARE_MASTER 0xf200
#define ART_FIRMWARE_REPLY 0xf300
#define ART_IP_PROG 0xf800
#define ART_IP_PROG_REPLY 0xf900


// Buffers
#define MAX_BUFFER_ARTNET 530
// Packet
#define ART_NET_ID "Art-Net\0"
#define PROTOCOL_VERSION 14
#define ART_DMX_START 18

class Artnet
{
public:
  Artnet();

  void begin();
  uint16_t read();
  void sendBroadcast();
  void printPacketHeader();
  void printPacketContent();

  // Return a pointer to the start of the DMX data
  inline uint8_t* getDmxFrame(void)
  {
    return artnetPacket + ART_DMX_START;
  }

  inline uint16_t getOpcode(void)
  {
    return opcode;
  }

  inline uint8_t getSequence(void)
  {
    return sequence;
  }

  inline uint16_t getUniverse(void)
  {
    return incomingUniverse;
  }

  inline uint16_t getLength(void)
  {
    return dmxDataLength;
  } 

  inline void setArtDmxCallback(void (*fptr)(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data)) 
  {
    artDmxCallback = fptr;
  }

private:
  UDP Udp;
  
  uint8_t artnetPacket[MAX_BUFFER_ARTNET];
  uint16_t packetSize;
  uint16_t opcode;
  uint8_t sequence;
  uint16_t incomingUniverse;
  uint16_t dmxDataLength;
  void (*artDmxCallback)(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data);
};

#endif

