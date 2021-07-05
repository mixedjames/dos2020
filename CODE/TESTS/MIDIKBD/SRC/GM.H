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

#ifndef DOS2020_MIDIKBD_GM_H
#define DOS2020_MIDIKBD_GM_H

#include "MUSIC.H"
#include <J/BUILDENV.H>

j_uint16 DetectGeneralMIDIDevice(J_VOID);

int CreateGeneralMIDIDevice(MusicOutputDevice** out, j_uint16 port);

#endif /* DOS2020_MIDIKBD_GM_H */
