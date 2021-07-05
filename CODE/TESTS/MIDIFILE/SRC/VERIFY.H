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

#ifndef DOS2020_MIDIFILE_VERIFY_H
#define DOS2020_MIDIFILE_VERIFY_H

#include <stdlib.h>
#include <stdio.h>

/* Macros needed to convert __LINE__ from an integer into a string.
   Not intended for public consumption.
 */
#define TRY_STRING_ME1(x) #x
#define TRY_STRING_ME(x) TRY_STRING_ME1(x)

/* Evaluates f and if false/zero reports a localising error message and
   calls abort.

   Similar to assert but appears in both debug and release builds.
 */
#define VERIFY(f) \
  if (!(f)) { \
    fputs( \
      "ERROR: VERIFY(" #f ") failed @ " \
      __FILE__ \
      ", line " \
      TRY_STRING_ME(__LINE__) \
      "\n", \
      stderr); \
    exit(1); \
  }

/* Checks feof(f) and ferror(f); if either is non-zero reports a localising
   error message and calls abort.
 */
#define VERIFY_STDIO(f)\
  if (feof( (f) )) {\
    fputs( \
      "ERROR: unexpected eof @ " \
      __FILE__ \
      ", line " \
      TRY_STRING_ME(__LINE__) \
      "\n", \
      stderr); \
    abort(); \
  }\
  else if (ferror( (f) )) {\
    fputs( \
      "ERROR: io error @ " \
      __FILE__ \
      ", line " \
      TRY_STRING_ME(__LINE__) \
      "\n", \
      stderr); \
    exit(1); \
  }\

#endif /* DOS2020_MIDIFILE_VERIFY_H */
