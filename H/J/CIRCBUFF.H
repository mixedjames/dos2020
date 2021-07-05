/*
  CIRCBUFF.H
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

  Package: CIRCBUFF
*/

#ifndef DOS2020_J_CIRCBUFF_H
#define DOS2020_J_CIRCBUFF_H

#define DEFINE_VOLATILE_CIRCULAR_BUFFER_TYPE(typeName, dataType, bufferSize) \
  typedef struct typeName { \
    volatile dataType buffer[bufferSize]; \
    volatile dataType* volatile readPtr; \
    volatile dataType* volatile writePtr; \
  } typeName;

#define CB_IS_EMPTY(cb) ((cb).readPtr == NULL)
#define CB_IS_FULL(cb) ((cb).readPtr == (cb).writePtr)

#define CB_INIT(cb) do {\
    (cb).readPtr = NULL;\
    (cb).writePtr = (cb).buffer;\
  } while(0);

#define CB_ADD_ITEM(cb, item)\
  if (!CB_IS_FULL( (cb) )) {\
    *(cb).writePtr = (item);\
    \
    if (!(cb).readPtr) {\
      (cb).readPtr = (cb).writePtr;\
    }\
    \
    (cb).writePtr =\
      &(cb).buffer[\
        ((cb).writePtr - (cb).buffer + 1)\
        % ( sizeof( (cb).buffer )/sizeof( (cb).buffer[0] ) )\
      ];\
  }

#define CB_NEXT_ITEM(cb, defaultValue)\
  ( (cb).readPtr ? *(cb).readPtr : (defaultValue) )

#define CB_REMOVE_ITEM(cb)\
  if (!CB_IS_EMPTY( (cb) )) {\
    (cb).readPtr = &(cb).buffer[\
      ( (cb).readPtr - (cb).buffer + 1)\
      % ( sizeof( (cb).buffer )/sizeof( (cb).buffer[0] ) )\
    ];\
    \
    if ((cb).readPtr == (cb).writePtr) {\
      (cb).readPtr = NULL;\
    }\
  }

#endif /* DOS2020_J_CIRCBUFF_H */
