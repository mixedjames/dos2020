/*
  KEYCODES.H
  Copyright (C) 2020  James Heggie

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

#ifndef DOS202_J_KEYCODES_H
#define DOS202_J_KEYCODES_H

typedef enum KeyCode {

  KC_UNKNOWN = 0,

  KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_I, KC_J, KC_K, KC_L,
  KC_M, KC_N, KC_O, KC_P, KC_Q, KC_R, KC_S, KC_T, KC_U, KC_V, KC_W, KC_X,
  KC_Y, KC_Z,

  KC_0, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9,

  KC_ESCAPE,

  KC_SPACE, KC_TAB, KC_RETURN, KC_BACKSPACE,

  KC_PLUS, KC_MINUS, KC_MULTIPLY, KC_EQUALS,

  KC_UP, KC_DOWN, KC_LEFT, KC_RIGHT,

  KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,
  KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12

} KeyCode;

#endif /* DOS202_J_KEYCODES_H */
