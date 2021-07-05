/*
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
*/

#include <J/CIRCBUFF.H>
#include <stdio.h>

#define LENGTH 3
DEFINE_VOLATILE_CIRCULAR_BUFFER_TYPE(MyCBuffer, int, LENGTH);

MyCBuffer cb;

void Add(MyCBuffer* cb, int i);
int Remove(MyCBuffer* cb);

int main() {
  puts("Circular buffer test");

  CB_INIT(cb);

  CB_ADD_ITEM(cb, 1);
  CB_ADD_ITEM(cb, 2);
  CB_ADD_ITEM(cb, 3);

  printf("CB_NEXT_ITEM() = %d\n", CB_NEXT_ITEM(cb,-1)); CB_REMOVE_ITEM(cb);
  printf("CB_NEXT_ITEM() = %d\n", CB_NEXT_ITEM(cb,-1)); CB_REMOVE_ITEM(cb);

  CB_ADD_ITEM(cb, 4);
  CB_ADD_ITEM(cb, 5);

  printf("CB_NEXT_ITEM() = %d\n", CB_NEXT_ITEM(cb,-1)); CB_REMOVE_ITEM(cb);
  printf("CB_NEXT_ITEM() = %d\n", CB_NEXT_ITEM(cb,-1)); CB_REMOVE_ITEM(cb);
  printf("CB_NEXT_ITEM() = %d\n", CB_NEXT_ITEM(cb,-1)); CB_REMOVE_ITEM(cb);
  printf("CB_NEXT_ITEM() = %d\n", CB_NEXT_ITEM(cb,-1)); CB_REMOVE_ITEM(cb);

  return 0;
}

void Add(MyCBuffer* cb, int i) {

  printf("Add(%d);\n", i);

  if (!CB_IS_FULL(*cb)) {
    *cb->writePtr = i;

    if (!cb->readPtr) {
      cb->readPtr = cb->writePtr;
    }

    cb->writePtr = &cb->buffer[(cb->writePtr - cb->buffer + 1) % LENGTH];
  }
  else {
    puts("Buffer is full!!!");
  }

}

int Remove(MyCBuffer* cb) {

  int result = -1;

  if (!CB_IS_EMPTY(*cb)) {

    result = *cb->readPtr;
    cb->readPtr = &cb->buffer[(cb->readPtr - cb->buffer + 1) % LENGTH];

    if (cb->readPtr == cb->writePtr) {
      cb->readPtr = NULL;
    }

    printf("Removed %d\n", result);
  }
  else {
    puts("Buffer is empty!!!");
  }

  return result;
}