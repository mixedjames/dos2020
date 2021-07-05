/*
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

*/

#include <stdio.h>
#include "J/KEYBOARD.H"

const char* TypeToString(KeyEventType t);

int main() {

  KeyEvent e;

  puts(__FILE__);

  Keyboard_Install();

  while (1) {

    if (Keyboard_GetEvent(&e)) {
      switch (e.code) {
      case KC_ESCAPE:
        goto quit;

      default:
        printf("%u %s\n", e.code, TypeToString(e.type));
      }
    }

  }
quit:

  Keyboard_Uninstall();
  return 0;
}

const char* TypeToString(KeyEventType t) {
  switch(t) {
    case KEY_PRESSED: return "pressed";
    case KEY_RELEASED: return "released";
    case KEY_REPEATED: return "repeated";
    default: return "unknown";
  }
}