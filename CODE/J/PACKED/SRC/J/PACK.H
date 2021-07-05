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

#ifdef DOS2020_J_UNPACK_H
#  undef DOS2020_J_UNPACK_H
#endif

#ifdef DOS2020_J_PACK_H
#  error PACK.H has already been included without a coresponding UNPACK.H
#else

#  define DOS2020_J_PACK_H

#  ifdef __BORLANDC__

#    pragma nopackwarning
#    pragma option -a1

#  elif __WATCOMC__ || __DJGPP__

#    pragma pack (push, 1)

#  elif _MSC_VER

#    pragma warning( disable : 4103 )
#    pragma pack (1)

#  else

#    error Unsupported compiler

#  endif

#endif /* DOS2020_J_PACK_H */
