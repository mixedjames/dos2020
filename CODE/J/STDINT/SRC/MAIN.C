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
#include "J/STDINT.H"

int main() {

  puts("--- SIGNED TYPES ---");
  printf("  sizeof(j_int8)  = %u\n", sizeof(j_int8));
  printf("  sizeof(j_int16) = %u\n", sizeof(j_int16));
  printf("  sizeof(j_int32) = %u\n", sizeof(j_int32));

  puts("--- UNSIGNED TYPES ---");
  printf("  sizeof(j_uint8)  = %u\n", sizeof(j_uint8));
  printf("  sizeof(j_uint16) = %u\n", sizeof(j_uint16));
  printf("  sizeof(j_uint32) = %u\n", sizeof(j_uint32));

  return 0;
}
