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

#include "MIDIFILE.H"

#include "VERIFY.H"
#include "BSWAP.H"

#if 0
#include <alloc.h> /* TODO: allow 32-bit flat memory model */
#endif
#include <stdlib.h>

#include <J/BUILDENV.H>

#if !defined(__COMPACT__) && !defined(__LARGE__) \
 && !defined(__HUGE__) && !defined(J_BITS32)
#  error MIDIFILE.C must be build using the compact, large or huge model.
#endif

/*******************************************************************************
 * PRIVATE DATA AND PROTOTYPES
 ******************************************************************************/

#include <J/PACK.H>

typedef struct MIDIChunk {
  j_uint8 type[4];
  j_uint32 length;
} MIDIChunk;

typedef struct MIDIHeaderChunk {

  j_uint8 type[4];
  j_uint32 length;

  j_uint16 format;
  j_uint16 nTracks;
  j_uint16 timing;
} MIDIHeaderChunk;

#include <J/UNPACK.H>

/* TODO: allow 32-bit flat memory model */
static void far* Allocate(size_t n);
static void Free(void far* ptr);

static void ReadHeader(FILE* f, MIDIFile* out);
static void ReadTracks(FILE* f, MIDIFile* out);

/*******************************************************************************
 * PUBLIC FUNCTIONS
 ******************************************************************************/

void ReadMIDIFile(const char* filename, MIDIFile* out) {

  FILE* f = NULL;

  VERIFY(filename != NULL);
  VERIFY(out != NULL);

  f = fopen(filename, "rb");
  if (!f) {
    fprintf(stderr, "Unable to open %s - ", filename);
    perror("");
    exit(1);
  }

  ReadHeader(f, out);
  ReadTracks(f, out);

  if (f) {
    fclose(f);
  }
}

void FreeMIDITracks(MIDIFile* f) {

  MIDITrackPtr t0 = f->tracks;
  MIDITrackPtr t1;

  VERIFY(f != NULL);

  while (t0) {
    t1 = t0;
    t0 = t1->next;

    Free(t1);
  }

}

/*******************************************************************************
 * PRIVATE FUNCTION DEFINITIONS
 ******************************************************************************/

static void far* Allocate(size_t n) {
#if 0
  return farmalloc(n);
#else
  return malloc(n);
#endif
}

static void Free(void far* ptr) {
  VERIFY(ptr != NULL);

#if 0
  farfree(ptr);
#else
  free(ptr);
#endif
}

static void ReadHeader(FILE* f, MIDIFile* out) {

  MIDIHeaderChunk hdr;

  VERIFY(f != NULL);
  VERIFY(out != NULL);

  fread(&hdr, sizeof(MIDIHeaderChunk), 1, f);
  VERIFY_STDIO(f);

  hdr.length = BSWAP32(hdr.length);

  out->flags = MIDIFILE_TICK_TIME;
  out->format = BSWAP16(hdr.format);
  out->nTracks = BSWAP16(hdr.nTracks);
  out->ticksPerQuarterNote = BSWAP16(hdr.timing);

  VERIFY(
    hdr.type[0] == 'M' && hdr.type[1] == 'T' &&
    hdr.type[2] == 'h' && hdr.type[3] == 'd'
  );

  VERIFY(hdr.length >= 6);
  VERIFY(out->format < 3);
  VERIFY((out->ticksPerQuarterNote & 0x8000) == 0);

  if (hdr.length > 6) {
    fseek(f, hdr.length - 6, SEEK_CUR);
    VERIFY_STDIO(f);
  }

}

static void ReadTracks(FILE* f, MIDIFile* out) {

  MIDIChunk c;
  MIDITrackPtr currentTrack = NULL;
  MIDITrackPtr lastTrack = NULL;

  VERIFY(f != NULL);
  VERIFY(out != NULL);

  while (1) {

    fread(&c, sizeof(MIDIChunk), 1, f);
    if (feof(f)) {
      break;
    }

    VERIFY_STDIO(f);

    if (
      c.type[0] == 'M' && c.type[1] == 'T' &&
      c.type[2] == 'r' && c.type[3] == 'k'
    ) {
      /* Found a track - copy the whole thing into memory */

      c.length = BSWAP32(c.length);

      /* ?FIXME: Slightly wasteful - allocates x1 pointer too many */
      currentTrack = (MIDITrackPtr) Allocate(c.length + sizeof(MIDITrack));
      VERIFY(currentTrack != NULL);

      fread(currentTrack->data, c.length, 1, f);
      VERIFY_STDIO(f);

      currentTrack->length = c.length;
      currentTrack->next = NULL;

      if (lastTrack) {
        lastTrack->next = currentTrack;
      }
      else {
        out->tracks = currentTrack;
      }

      lastTrack = currentTrack;

    }
    else {
      /* Unknown chunk type - skip it */
      fseek(f, BSWAP32(c.length), SEEK_CUR);
      VERIFY_STDIO(f);
    }

  }

}
