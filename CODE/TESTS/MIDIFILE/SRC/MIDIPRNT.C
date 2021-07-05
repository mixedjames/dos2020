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

#include "MIDIPRNT.H"
#include "VERIFY.H"

/*******************************************************************************
 * PRIVATE DATA AND PROTOTYPES
 ******************************************************************************/

/* General MIDI spec defines 128 notes. These are absolute values (i.e. no
   concept of "key" is applied.

   Middle C is note 60.

   To look up a note name given a MIDI note value...
   value = notesNames[note % 8];
 */
static const char* noteNames[] = {
  "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"
};

/* General MIDI spec names 128 instrument "programs". The spec uses a 1-based
   index but files use a 0-based one to allow encoding in a single 7-bit value.

   These are then subcategorised into 16 groups of 8 instrument.
 */
static const char* instrumentGroup[] = {
  "Piano", "Chromatic Percussion", "Organ", "Guitar", "Bass", "Strings",
  "Ensemble", "Brass", "Reed", "Pipe", "Synth Lead", "Synth Pad",
  "Synth Effects", "Ethnic", "Percussive", "Sound effects"
};

static j_uint8* data;
static j_uint8* end;

static j_uint32 deltaT;
static j_uint32 time;

static j_uint16 lastStatus = 0xffff;
static j_uint8 status;
static j_uint8 channel;

static void PrintEvent(void);
static void PrintChannelEvent(void);
static void PrintSystemEvent(void);
static void PrintMetaEvent(void);
static j_uint32 ReadVLQ(void);

/*******************************************************************************
 * PUBLIC FUNCTIONS
 ******************************************************************************/

void PrintMIDITrack(MIDITrackPtr t) {

  VERIFY(t != NULL);

  time = 0;
  data = t->data;
  end = data + t->length;

  while (data < end) {
    PrintEvent();
  }

}

/*******************************************************************************
 * PRIVATE FUNCTION DEFINITIONS
 ******************************************************************************/

static void PrintEvent(void) {

  deltaT = ReadVLQ();
  time += deltaT;

  VERIFY(data < end);

  if (*data & 0x80) {
    /* Current data byte is the status code */
    status = *data++;
    lastStatus = status;
    VERIFY(data < end);
  }
  else {
    /* Current event uses a running status */
    VERIFY(lastStatus != 0xffff);
    status = lastStatus;
  }

  if (status == 0xff) {
    PrintMetaEvent();
  }
  else if ((status & 0xf0) == 0xf0) {
    PrintSystemEvent();
  }
  else {
    PrintChannelEvent();
  }
}

static void PrintChannelEvent(void) {

  channel = status & 0x0f;

  switch ((status >> 4) & 7) {
  case 0:
    VERIFY(end - data >= 2);
    printf("%lu: Note %s off (n: %hhu, v: %hhu, channel: %hhu)\n",
      time, noteNames[data[0] % 12], data[0], data[1], status & 0xf);
    data += 2;
    break;

  case 1:
    VERIFY(end - data >= 2);
    printf("%lu: Note %s on (n: %hhu, v: %hhu, channel: %hhu)\n",
      time, noteNames[data[0] % 12], data[0], data[1], status & 0xf);
    data += 2;
    break;

  case 2:
    VERIFY(end - data >= 2);
    printf("%lu: Aftertouch %s (n: %hhu, p: %hhu, channel: %hhu)\n",
      time, noteNames[data[0] % 12], data[0], data[1], status & 0xf);
    data += 2;
    break;

  case 3:
    VERIFY(end - data >= 2);
    if (data[0] == 7) {
      /* Note: volume is a 14 bit quantity specified by two control codes:
         7 = most-significant 7 bit (what we're listening to)
         39 = least-significant bits (we ignore this)
       */
      printf("%lu: Channel volume MSB set to %hhu\n", time, data[1]);
    }
    else if (data[0] == 10) {
      printf("%lu: Channel pan MSB set to %hhu\n", time, data[1]);
    }
    else {
      printf("%lu: Control change - controller %hhu, value %hhu (channel: %hhu)\n",
        time, data[0], data[1], status & 0xf);
    }
    data += 2;
    break;

  case 6:
    VERIFY(end - data >= 2);
    printf("%lu: Pitch wheel change (channel: %hhu)\n",
      time, status & 0xf);
    data += 2;
    break;

  case 4:
    VERIFY(end - data >= 1);
    printf("%lu: Program (instrument) changed to %s (p: %hhu, channel: %hhu)\n",
      time, instrumentGroup[data[0] / 8], data[0], status & 0xf);
    data++;
    break;

  case 5:
    VERIFY(end - data >= 1);
    printf("%lu: Aftertouch - no note (p: %hhu, channel: %hhu)\n",
      time, data[0], status & 0xf);
    data++;
    break;

  default:
    VERIFY(0);
  }

}

static void PrintSystemEvent(void) {
  /* FIXME: implement this! */
  VERIFY(0);
}

static void PrintMetaEvent(void) {

  j_uint8 type;
  j_uint32 l;

  VERIFY(end - data >= 2);

  type = *data++;
  l = ReadVLQ();

  /* Unsigned --> signed conversion valid because VLQs are defined to have
     the top nibble as 0 */
  VERIFY(end - data >= (j_int32)l);

  switch (type) {
  case 3:
    printf("Track name: %*s\n", (unsigned int)l, data);
    break;

  case 0x2f:
    printf("End of track\n");
    break;

  case 0x51:
    printf("Tempo set to %hhu us/quarter-note\n", data[0]);
    break;

  default:
    printf("Meta event %hhx (%lu bytes, dT = %lu)\n", type, l, deltaT);
  }

  data += l;

}

static j_uint32 ReadVLQ() {

  j_uint32 result = 0;

  if (*data & 0x80) {

    result = *data++ & 0x7f;

    while (1) {
      VERIFY(data < end);

      result = (result << 7) | (*data & 0x7f);
      if ((*data & 0x80) == 0) {
        data++;
        break;
      }

      data++;
    }

    return result;
  }
  else {
    VERIFY(data < end);
    return *data++;
  }

}
