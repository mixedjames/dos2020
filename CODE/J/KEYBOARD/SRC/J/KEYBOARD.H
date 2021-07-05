/*
  KEYBOARD.H
  Copyright (C) 2021  James Heggie

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

#ifndef DOS2020_J_KEYBOARD_H
#define DOS2020_J_KEYBOARD_H

#include <J/KEYCODES.H>
#include <J/STDINT.H>
#include <J/BUILDENV.H>

typedef enum KeyEventType {
  KEY_PRESSED,
  KEY_RELEASED,
  KEY_REPEATED
} KeyEventType;

typedef struct KeyEvent {
  KeyEventType type;
  KeyCode code;
} KeyEvent;

/**
 *
 */
int Keyboard_Install(J_VOID);

/**
 *
 */
void Keyboard_Uninstall(J_VOID);

/**
 *
 */
int Keyboard_GetEvent(KeyEvent* e);

#endif /* DOS2020_J_KEYBOARD_H */
