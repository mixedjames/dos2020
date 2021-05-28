#include <stdio.h>
#include <windows.h>
#include "J/TEST.H"

#ifndef __DJGPP__
#define C_NEAR_CALL near cdecl
#else
#define C_NEAR_CALL
#endif

int C_NEAR_CALL add2(int a, int b);

int main() {

  j_test();
  printf("add(2,3) = %d\n", add2(2,3));

  return 0;
}
