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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "VERIFY.H"
#include "MIDIFILE.H"
#include "MIDIPRNT.H"

/*******************************************************************************
 * PRIVATE DATA AND PROTOTYPES
 ******************************************************************************/

static unsigned long int track = 1;

static void PrintUsage(void);
static void ReadFile(const char* filename);

/*******************************************************************************
 * PUBLIC FUNCTIONS
 ******************************************************************************/

int main(int argc, char* argv[]) {

  int i;

  if (argc == 1) {
    PrintUsage();
    exit(0);
  }

  for (i = 1; i < argc; ++i) {
    if (argv[i][0] != '-' && argv[i][0] != '/') {
      break;
    }

    switch (argv[i][1]) {

    case '?': /* Fallthrough intentional */
    case 'h':
      PrintUsage();
      exit(0);

    case 't':
      i++;
      if (i < argc) {
        errno = 0;
        track = strtoul(argv[i], NULL, 0);
        if (errno || track > 0xffff || track == 0) {
          fprintf(stderr, "-t switch must be followed by a valid track number.");
          exit(1);
        }
      }
      else {
        fprintf(stderr, "-t switch must be followed by a valid track number.");
        exit(1);
      }
      break;

    default:
      fprintf(stderr, "Unrecognised switch: %s\n", argv[i]);
    }
  }

  if (i == argc) {
    fputs("No file specified.", stderr);
    exit(1);
  }

  ReadFile(argv[i]);

  return 0;
}

/*******************************************************************************
 * PRIVATE FUNCTION DEFINITIONS
 ******************************************************************************/

static void PrintUsage() {
  puts(
    "MIDIFILE - A demo program showing how to read a .mid file.\n"
    "  by James Heggie\n"
    "\n"
    "Usage:"
    "  MIDIFILE.EXE [options] midifile\n"
    "  Where [options] can be...\n"
    "    -h/-?\tDisplay this message\n"
    "    -t n\tSelect the track to print\n"
  );
}

static void ReadFile(const char* filename) {

  MIDIFile file = {0};
  MIDITrackPtr t;

  j_uint16 ti;
  MIDITrackPtr printMe;

  ReadMIDIFile(filename, &file);

  printf("%s: format %hhu, %u tracks, %u ticks/quarternote\n",
    filename, file.format, file.nTracks, file.ticksPerQuarterNote);

  for (t = file.tracks, ti = 1; t != NULL; t = t->next, ti++) {
    printf("Track; %lu bytes long.\n", t->length);

    if (ti == track) {
      printMe = t;
    }
  }

  if (printMe) {
    PrintMIDITrack(printMe);
  }
  else {
    fprintf(stderr, "Track %lu does not exist to print.\n", track);
  }

  FreeMIDITracks(&file);

}
