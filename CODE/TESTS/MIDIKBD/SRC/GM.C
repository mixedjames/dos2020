/*
  This file is part of DOS2020.

  DOS2020 is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Foobar is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with DOS2020.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "GM.H"

#include <stdlib.h>
#include <stdio.h>
#include <dos.h>
#include <assert.h>

/*******************************************************************************
 * PRIVATE FUNCTION DECLARATION, AND DATA/TYPE DEFINITIONS
 ******************************************************************************/

typedef struct GMDevice {
  MusicOutputDevice mod;

  j_uint16 port;

} GMDevice;

/* MusicOutputDevice interface methods */
static void Destroy(MusicOutputDevice* self);
static void NoteOn(
    MusicOutputDevice* self,
    j_uint8 channel, j_uint8 note, j_uint8 velocity);
static void NoteOff(
    MusicOutputDevice* self,
    j_uint8 channel, j_uint8 note, j_uint8 velocity);

/* Other local functions */
static void WriteGM(j_uint16 port, j_uint8 data);
static int DetectGMDeviceOnPort(j_uint16 port);
static int InitGMDevice(j_uint16 port);

/*******************************************************************************
 * PUBLIC FUNCTION DEFINITIONS
 ******************************************************************************/

j_uint16 DetectGeneralMIDIDevice() {

  /* I think there are two possible port bases for GM: 0x300 and 0x330
     I've not seen a spec but that's what various examples seem to do.
     We try both.
   */

  if (DetectGMDeviceOnPort(0x300)) {
    return 0x300;
  }
  else if (DetectGMDeviceOnPort(0x330)) {
    return 0x330;
  }
  else {
    return 0;
  }

}

int CreateGeneralMIDIDevice(MusicOutputDevice** out, j_uint16 port) {

  int ec = 0;
  GMDevice* gmDev = NULL;

  gmDev = (GMDevice*) malloc(sizeof(GMDevice));
  if (!gmDev) {
    fprintf(stderr, "Unable to allocate GMDevice\n");
    ec = 1; goto epilogue;
  }

  gmDev->mod.Destroy = Destroy;
  gmDev->mod.NoteOn = NoteOn;
  gmDev->mod.NoteOff = NoteOff;

  gmDev->port = port;

  if (!InitGMDevice(port)) {
    fprintf(stderr, "Unable to initialise GM device on port %u\n", port);
    ec = 1; goto epilogue;
  }

epilogue:

  if (ec) {
    if (gmDev) {
      free(gmDev);
    }
  }
  else {
    *out = &gmDev->mod;
  }

  return ec;
}

/*******************************************************************************
 * PRIVATE FUNCTION DEFINITIONS
 ******************************************************************************/

static void Destroy(struct MusicOutputDevice* self) {
  free(self);
}

static void NoteOn(
  struct MusicOutputDevice* self,
  j_uint8 channel, j_uint8 note, j_uint8 velocity
) {

  j_uint16 port = ((GMDevice*) self)->port;

  WriteGM(port, 0x90 | (channel & 0xf));
  WriteGM(port, 0x7f & note);
  WriteGM(port, velocity & 0x7f);
}

static void NoteOff(
  struct MusicOutputDevice* self,
  j_uint8 channel, j_uint8 note, j_uint8 velocity
) {

  j_uint16 port = ((GMDevice*) self)->port;

  WriteGM(port, 0x80 | (channel & 0xf));
  WriteGM(port, 0x7f & note);
  WriteGM(port, velocity & 0x7f);
}

static void WriteGM(j_uint16 port, j_uint8 data) {

  while (inp(port+1) & 0x80) {}
  outp(port, data);

}

static int DetectGMDeviceOnPort(j_uint16 port) {

  /* GM/Roland MPU 401 devices have x2 bidirectional ports:
     base + 0 = DATA
     base + 1 = STATUS/COMMAND

     Reportedly some knock-off compatibles never implemented the COMMAND
     port - doesn't matter mostly, but does mean that such cards will never
     send acknowledge bytes on the DATA port; this means any loops waiting for
     acknowledge should include a timeout

     I think STATUS reads still work.
   */

  delay(10);

  /* Ok to write to device if bit 6 of STATUS is clear */
  if (inp(port+1) & 0x40) {
    return 0;
  }

  outp(port, 0xf8);
  delay(10);

  if (inp(port+1) & 0x40) {
    return 0;
  }

  return 1;

}

static int InitGMDevice(j_uint16 port) {

  /* Send reset command */
  while (inp(port+1) & 0x40) {}
  outp(port+1, 0xFF);

  /* Wait for acknowledge to appear at data port
     Ok to write if STATUS bit 7 clear
   */
  while (inp(port+1) & 0x80) {}
  if (inp(port) != 0xfe) {
    return 0;
  }

  /* Send "switch to UART mode" command (note: no acknowledge sent for this) */
  while (inp(port+1) & 0x40) {}
  outp(port+1, 0x3f);

  return 1;
}