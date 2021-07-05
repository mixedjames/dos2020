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
#include <dos.h>
#include <J/BUILDENV.H>
#include <J/STDINT.H>
#include <J/KEYBOARD.H>

#include "GM.H"

/*******************************************************************************
 * PRIVATE DATA AND PROTOTYPES
 ******************************************************************************/

#define NOTE_ON(device, note) (device)->NoteOn((device), 0, note, 0x7f)
#define NOTE_OFF(device, note) (device)->NoteOff((device), 0, note, 0x7f)

/*******************************************************************************
 * PUBLIC FUNCTIONS
 ******************************************************************************/

int main() {

  int ec = 0;
  KeyEvent e;

  j_uint16 port;
  MusicOutputDevice* mod = NULL;

  if (!Keyboard_Install()) {
    fprintf(stderr, "Unable to install keyboard handler.\n");
    ec = 1; goto epilogue;
  }

  port = DetectGeneralMIDIDevice();
  if (port != 0) {
    printf("Found a General MIDI device on port 0x%4x\n", port);
  }
  else {
    fprintf(stderr, "Unable to detect a General MIDI device.\n");
    ec = 1; goto epilogue;
  }

  if (CreateGeneralMIDIDevice(&mod, port)) {
    fprintf(stderr, "CreateGeneralMIDIDevice failed.\n");
    ec = 1; goto epilogue;
  }

  printf("Press A,S,D,F,G,H,J, or K for music. Press escape to exit.\n");

  while (1) {
    if (!Keyboard_GetEvent(&e)) continue;

    if (e.type == KEY_PRESSED) {
      switch (e.code) {
      case KC_ESCAPE:
        goto epilogue;

      case KC_A: printf("C "); NOTE_ON(mod, 60); break;
      case KC_S: printf("D "); NOTE_ON(mod, 62); break;
      case KC_D: printf("E "); NOTE_ON(mod, 64); break;
      case KC_F: printf("F "); NOTE_ON(mod, 65); break;
      case KC_G: printf("G "); NOTE_ON(mod, 67); break;
      case KC_H: printf("A "); NOTE_ON(mod, 69); break;
      case KC_J: printf("B "); NOTE_ON(mod, 71); break;
      case KC_K: printf("C "); NOTE_ON(mod, 72); break;
      }
    }
    else if (e.type == KEY_RELEASED) {
      switch (e.code) {
      case KC_A: NOTE_OFF(mod, 60); break;
      case KC_S: NOTE_OFF(mod, 62); break;
      case KC_D: NOTE_OFF(mod, 64); break;
      case KC_F: NOTE_OFF(mod, 65); break;
      case KC_G: NOTE_OFF(mod, 67); break;
      case KC_H: NOTE_OFF(mod, 69); break;
      case KC_J: NOTE_OFF(mod, 71); break;
      case KC_K: NOTE_OFF(mod, 72); break;
      }
    }
  }

epilogue:

  if (mod) { mod->Destroy(mod); }

  Keyboard_Uninstall();

  return ec;
}

/*******************************************************************************
 * PRIVATE FUNCTION DEFINITIONS
 ******************************************************************************/
