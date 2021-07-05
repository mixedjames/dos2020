#include <stdio.h>
#include "J/TEST.H"

#ifndef __DJGPP__
#define C_NEAR_CALL near cdecl
#else
#define C_NEAR_CALL
#endif

int add2(int a, int b);

int main() {

  printf("sizeof(int) = %u, sizeof(void*) = %u\n",
    sizeof(int), sizeof(void*));
#if 1
  printf("add(2,3) = %d\n", add2(2,3));
#endif
  return 0;
}
