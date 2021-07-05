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

#ifndef DOS2020_MIDIFILE_MIDIFILE_H
#define DOS2020_MIDIFILE_MIDIFILE_H

#include <J/STDINT.H>

#define MIDIFILE_TIME_MASK (1)
#define MIDIFILE_TICK_TIME (0)
#define MIDIFILE_SMPTE_TIME (1)

/* Header for a track of MIDI events in memory.
   Variable length struct whose length is given in bytes by .length.
   Singly-linked list where .next == NULL means last track.
 */
typedef struct MIDITrack {
  struct MIDITrack far* next;
  j_uint32 length;
  j_uint8 data[1];
} MIDITrack;

typedef MIDITrack far* MIDITrackPtr;

typedef struct MIDIFile {

  j_uint8 flags;
  j_uint8 format;
  j_uint16 nTracks;
  j_uint16 ticksPerQuarterNote;

  MIDITrackPtr tracks;

} MIDIFile;

void ReadMIDIFile(const char* filename, MIDIFile* out);

void FreeMIDITracks(MIDIFile* f);

#endif /* DOS2020_MIDIFILE_MIDIFILE_H */
