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

#include "J/PACK.H"
struct PackMe
{
  char a;
  void* b;
  char c;
};
#include "J/UNPACK.H"

struct Unpacked
{
  char a;
  void* b;
  char c;
};

int main() {

  struct PackMe p;
  struct Unpacked u;

  printf("sizeof(struct PackMe) = %u\n", sizeof(p));
  printf("sizeof(struct Unpacked) = %u\n", sizeof(u));

  return 0;
}
