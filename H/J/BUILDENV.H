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

#ifndef DOS2020_J_BUILDENV_H
#define DOS2020_J_BUILDENV_H

/* 
 */
#if __cplusplus
#  define J_VOID
#else
#  define J_VOID void
#endif

/*
 */
#if defined(M_I86SM) || defined(__SMALL__) \
 || defined(M_I86MM) || defined(__MEDIUM__) \
 || defined(M_I86CM) || defined(__COMPACT__) \
 || defined(M_I86LM) || defined(__LARGE__) \
 || defined(M_I86HM) || defined(__HUGE__)
#  define J_BITS16
#  define J_BITNESS "16 bit"
#else
#  define J_BITS32
#  define J_BITNESS "32 bit"
#  define J_MEMORY_MODEL "flat"
#endif

/* Small memory model */
#if defined(M_I86SM) && !defined(__SMALL__)
#  define __SMALL__
#endif

#if defined(__SMALL__) && !defined(M_I86SM)
#  define M_I86SM
#endif

#if defined(__SMALL__)
#  define J_MEMORY_MODEL "small"
#endif

/* Medium memory model */
#if defined(M_I86MM) && !defined(__MEDIUM__)
#  define __MEDIUM__
#endif

#if defined(__MEDIUM__) && !defined(M_I86MM)
#  define M_I86MM
#endif

#if defined(__MEDIUM__)
#  define J_MEMORY_MODEL "medium"
#endif

/* Compact memory model */
#if defined(M_I86CM) && !defined(__COMPACT__)
#  define __COMPACT__
#endif

#if defined(__COMPACT__) && !defined(M_I86CM)
#  define M_I86CM
#endif

#if defined(__COMPACT__)
#  define J_MEMORY_MODEL "compact"
#endif

/* Large memory model */
#if defined(M_I86LM) && !defined(__LARGE__)
#  define __LARGE__
#endif

#if defined(__LARGE__) && !defined(M_I86LM)
#  define M_I86LM
#endif

#if defined(__LARGE__)
#  define J_MEMORY_MODEL "large"
#endif

/* Huge memory model */
#if defined(M_I86HM) && !defined(__HUGE__)
#  define __HUGE__
#endif

#if defined(__HUGE__) && !defined(M_I86HM)
#  define M_I86HM
#endif

#if defined(__HUGE__)
#  define J_MEMORY_MODEL "huge"
#endif

#if defined(_MSC_VER)
#  if _MSC_VER == 800
#    define J_COMPILER_NAME "Microsoft 8.00 (Microsoft Visual C 1.0)"
#  else
#    error Unsupported Microsoft compiler version
#  endif
#endif

#if defined(__DJGPP__)
#  define J_COMPILER_NAME "DJGPP GCC" __VERSION__
#endif

#ifndef J_STRINGME
#  define J_STRINGME1(x) #x
#  define J_STRINGME(x) J_STRINGME1(x)
#endif

#if defined(__BORLANDC__)
#  if __BORLANDC__ >= 0x0500 && __BORLANDC__ < 0x0600
#    define J_COMPILER_NAME "Borland C 5 (" J_STRINGME(__BORLANDC__) ")"
#  else
#    error Unsupported Borland compiler version
#  endif
#endif

#if defined(__WATCOMC__)
#  if __WATCOMC__ >= 1200 && __WATCOMC__ < 1300
#    define J_COMPILER_NAME "Watcom C 12 (" J_STRINGME(__WATCOMC__) ")"
#  else
#    error Unsupported Watcom compiler version
#  endif
#endif

#ifndef J_COMPILER_NAME
#  error Unsupported compiler.
#endif

#endif /* DOS2020_J_BUILDENV_H */
