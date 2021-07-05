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

#ifdef DOS2020_J_PACK_H
#  undef DOS2020_J_PACK_H
#else
#  error UNPACK.H must be included after PACK.H
#endif

#ifdef DOS2020_J_UNPACK_H
#  error UNPACK.H must be paired with a preceeding call to PACK.H
#else
#  define DOS2020_J_UNPACK_H

#  ifdef __BORLANDC__

#    pragma nopackwarning
#    pragma option -a.

#  elif __WATCOMC__ || __DJGPP__

#    pragma pack (pop)

#  elif _MSC_VER

#    pragma pack ()

#  else

#    error Unsupported compiler

#  endif

#endif /* DOS2020_J_UNPACK_H */
