#include <stdio.h>

void in_section2(void);

extern unsigned long int startOfLockedData;
extern unsigned long int endOfLockedData;
extern unsigned long int startOfLockedCode;
extern unsigned long int endOfLockedCode;

int main() {

  puts("WCMAP.EXE");
  printf("in_section2 = %p\n", in_section2);
  in_section2();


  return 0;
}
