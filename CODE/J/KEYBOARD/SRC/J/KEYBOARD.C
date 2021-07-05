/*
  KEYBOARD.C
  Copyright (C) 2021 James Heggie

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU Lesser Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.

  Package: KEYBOARD
*/

#include <J/KEYBOARD.H>

#include <J/BUILDENV.H>
#include <J/CIRCBUFF.H>

#if BITS32
#  error 32 bit keyboard handler not yet implemented
#endif

#include <stddef.h>
#include <dos.h>
#include <conio.h>

/*******************************************************************************
 * Private macros, data and prototypes
 * (No function definitions. Data should all be static)
 ******************************************************************************/

#define KEYBOARD_INT (9)

static volatile unsigned char prefix = 0;
static void interrupt (*OldKbdInt)(void) = 0;

#define BUFFER_LENGTH 3
DEFINE_VOLATILE_CIRCULAR_BUFFER_TYPE(KeyEventBuffer, KeyEvent, BUFFER_LENGTH);
static KeyEventBuffer keyEventBuffer;

static char keyDown[64] = {0};

static char keycodes[128] = {
   /* 00 - 0F */
   0, KC_ESCAPE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6,
   KC_7, KC_8, KC_9, KC_0, 0, 0, KC_BACKSPACE, KC_TAB,

   /* 10 - 1F */
   KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I,
   KC_O, KC_P, 0, 0, KC_RETURN, 0, KC_A, KC_S,

   /* 20 - 2F */
   KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, 0,
   0, 0, 0, 0, KC_Z, KC_X, KC_C, KC_V,

   /* 30 - 3F */
   KC_B, KC_N, KC_M, 0, 0, 0, 0, 0,
   0, KC_SPACE, 0, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,

   /* 40 - 4F */
   KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,

   /* 50 - 5F */
   0, 0, 0, 0, 0, 0, 0, KC_F11,
   KC_F12, 0, 0, 0, 0, 0, 0, 0,

   /* 60 - 6F */
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

   /* 70 - 7F */
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0
};

static char extendedKeycodes[128] = {
  /* 00 - 0F */
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  /* 10 - 1F */
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  /* 20 - 2F */
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  /* 30 - 3F */
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  /* 40 - 4F */
  0, 0, 0, 0, 0, 0, 0, 0,
  KC_UP, 0, 0, KC_LEFT, 0, KC_RIGHT, 0, 0,

  /* 50 - 5F */
  KC_DOWN, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  /* 60 - 6F */
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  /* 70 - 7F */
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

};

static void interrupt KbdHandler(void);

/*******************************************************************************
 * Public function definitions
 ******************************************************************************/

int Keyboard_Install(void) {

  if (OldKbdInt) {
    return 0;
  }

  OldKbdInt = _dos_getvect(KEYBOARD_INT);
  _dos_setvect(KEYBOARD_INT, KbdHandler);

  CB_INIT(keyEventBuffer);

  return 1;
}

void Keyboard_Uninstall(void) {

  if (!OldKbdInt) {
    return;
  }

  _dos_setvect(KEYBOARD_INT, OldKbdInt);

}

int Keyboard_GetEvent(KeyEvent* e) {

  int result = 0;
  KeyEvent nullEvent = {0};

  _disable();

  if (!CB_IS_EMPTY(keyEventBuffer)) {
    *e = CB_NEXT_ITEM(keyEventBuffer, nullEvent);
    CB_REMOVE_ITEM(keyEventBuffer);
    result = 1;
  }

  _enable();
  return result;
}

/*******************************************************************************
 * Private function definitions
 * (Should all be static)
 ******************************************************************************/

static void interrupt KbdHandler(void) {

  unsigned char scanCode; /* Raw data read from kbd controller */
  KeyEvent e;             /* Nice friendly standardised data created by us */
  j_uint8 keyDownMapOffset = 0;

  scanCode = inp(0x60);

  switch (scanCode) {

  /* These are prefix bytes which say the next keycode is an extended key
   */
  case 0xF0:
  case 0xE0:
    prefix = scanCode;
    break;

  default:

    if (prefix == 0xf0 || prefix == 0xe0) {
      keyDownMapOffset = 8;
    }

    /* Bit 7 set = released, clear = pressed */
    if (scanCode & 0x80) {
      e.type = KEY_RELEASED;
      keyDown[keyDownMapOffset + (scanCode & 0x7f) / 8] &=
        ~(1 << (scanCode & 7));
    }
    else {
      /* Bit 7 is clear by definition --> can use scanCode unmodified */
      if(keyDown[keyDownMapOffset + scanCode / 8] & (1 << (scanCode & 7))) {
        e.type = KEY_REPEATED;
      }
      else {
        e.type = KEY_PRESSED;
        keyDown[keyDownMapOffset + scanCode / 8] |= (1 << (scanCode & 7));
      }
    }

    switch (prefix) {
    case 0xF0:
    case 0xE0:
      e.code = extendedKeycodes[scanCode & 0x7F];
      break;

    default:
      e.code = keycodes[scanCode & 0x7F];
    }

    CB_ADD_ITEM(keyEventBuffer, e);

    prefix = 0;
  }

  /* Send end-of-interrupt to PIC */
  outp(0x20,0x20);
}
