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

#ifndef DOS2020_MIDIFILE_BSWAP_H
#define DOS2020_MIDIFILE_BSWAP_H

#define BSWAP16(x)\
  (\
    (( (x) >> 8) & 0xff) | (( (x) & 0xff) << 8)\
  )

#define BSWAP32(x)\
  (\
    (( (x) & 0xff000000) >> 24) | (( (x) & 0x00ff0000) >>  8) |\
    (( (x) & 0x0000ff00) <<  8) | (( (x) & 0x000000ff) << 24)\
  )

#endif /* DOS2020_MIDIFILE_BSWAP_H */
