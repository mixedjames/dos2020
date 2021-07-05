#include <stdio.h>
#include <string.h>

#ifdef __WATCOMC__
#  pragma data_seg (LOCKDATA)
#  pragma code_seg (LOCKCODE)
#  define LOCKED_DATA
#  define LOCKED_CODE
#elif __DJGPP__
#  define LOCKED_DATA __attribute__ ((section ("LOCKDATA")))
#  define LOCKED_CODE __attribute__ ((section ("LOCKCODE")))
#elif __BORLANDC__
#  pragma codeseg LOCKCODE
#  define LOCKED_DATA
#  define LOCKED_CODE
#else
#  error Unsupported compiler
#endif

extern unsigned long int startOfLockedData;
extern unsigned long int endOfLockedData;
extern unsigned long int startOfLockedCode;
extern unsigned long int endOfLockedCode;

char LOCKED_DATA theStart = 0;
char LOCKED_DATA a[] = { "Locked Data!" };
char LOCKED_DATA theEnd = 0;

#define IS_LOCKED_DATA(x)\
  (\
    ((x) > &startOfLockedData)\
      && ((x) < &endOfLockedData)\
  )

LOCKED_CODE
void in_section2()
{

  printf("theStart = %u\n", IS_LOCKED_DATA(&theStart));
  printf("a = %u\n", IS_LOCKED_DATA(&a));
  printf("theEnd = %u\n", IS_LOCKED_DATA(&theEnd));

}
