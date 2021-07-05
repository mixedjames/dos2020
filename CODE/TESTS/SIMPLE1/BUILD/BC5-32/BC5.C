/*
  This file is part of jcdep.

  Foobar is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Foobar is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with dos2020.  If not, see <https://www.gnu.org/licenses/>.

  James Heggie, Copyright (c) 2021
*/

/* This file exists to placate Borland C 5 DPMI. Should not be included in any other builds.
 */

#include <windows.h>
#include <stdio.h>

#define UNUSED(x) (void)(x)

/* winnls.h */
int WINAPI GetDateFormatA(
  LCID Locale, DWORD dwFlags, CONST SYSTEMTIME *lpDate, LPCSTR lpFormat,
  LPSTR lpDateStr, int cchDate
) {
  UNUSED(Locale);
  UNUSED(dwFlags);
  UNUSED(lpDate);
  UNUSED(lpFormat);
  UNUSED(lpDateStr);
  UNUSED(cchDate);

  return 0;
}

BOOL WINAPI GetStringTypeW(
  DWORD dwInfoType, LPCWSTR lpSrcStr, int cchSrc, LPWORD lpCharType
) {
  UNUSED(dwInfoType);
  UNUSED(lpSrcStr);
  UNUSED(cchSrc);
  UNUSED(lpCharType);

  return 0;
}

BOOL WINAPI GetCPInfo(UINT CodePage, LPCPINFO lpCPInfo) {

  puts("+++");

  if (CodePage == 437) {
    lpCPInfo->MaxCharSize = 1;
    memset(lpCPInfo->DefaultChar, '?', MAX_DEFAULTCHAR);
    memset(&lpCPInfo->LeadByte, 0, MAX_LEADBYTES);
    return 1;
  }

  return 0;
}

BOOL WINAPI GetVersionExA(LPOSVERSIONINFOA lpVersionInformation) {
  UNUSED(lpVersionInformation);

  return 0;
}
