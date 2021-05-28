#include <stdio.h>

int main() {

  puts("*** COMPILER IDENTIFICATION ***");

#ifdef __DJGPP__
  printf("  __DJGPP__ = %u\n", (unsigned int)__DJGPP__);
#else
  puts("  __DJGPP__ undefined.");
#endif

#ifdef __BORLANDC__
  printf("  __BORLANDC__ = %u\n", (unsigned int)__BORLANDC__);
#else
  puts("  __BORLANDC__ undefined.");
#endif

#ifdef __WATCOMC__
  printf("  __WATCOMC__ = %u\n", (unsigned int)__WATCOMC__);
#else
  puts("  __WATCOMC__ undefined.");
#endif

#ifdef _MSC_VER
  printf("  _MSC_VER = %u\n", (unsigned int)_MSC_VER);
#else
  puts("  _MSC_VER undefined.");
#endif

  puts("*** SYSTEM IDENTIFICATION ***");

#ifdef __MSDOS__
  printf("  __MSDOS__ = %u\n", (unsigned int)__MSDOS__);
#else
  puts("  __MSDOS__ undefined.");
#endif

#ifdef __DOS__
  printf("  __DOS__ = %u\n", (unsigned int)__DOS__);
#else
  puts("  __DOS__ undefined.");
#endif

#ifdef _DOS
  printf("  _DOS = %u\n", (unsigned int)_DOS);
#else
  puts("  _DOS undefined.");
#endif

#ifdef _MSDOS
  printf("  _MSDOS = %u\n", (unsigned int)_MSDOS);
#else
  puts("  _MSDOS undefined.");
#endif

#ifdef MSDOS
  printf("  MSDOS = %u\n", (unsigned int)MSDOS);
#else
  puts("  MSDOS undefined.");
#endif

#ifdef __GO32__
  printf("  __GO32__ = %u\n", (unsigned int)__GO32__);
#else
  puts("  __GO32__ undefined.");
#endif

#ifdef __FLAT__
  printf("  __FLAT__ = %u\n", (unsigned int)__FLAT__);
#else
  puts("  __FLAT__ undefined.");
#endif

#ifdef __X86__ 
  printf("  __X86__ = %u\n", (unsigned int)__X86__);
#else
  puts("  __X86__ undefined.");
#endif

#ifdef __I86__
  printf("  __I86__ = %u\n", (unsigned int)__I86__);
#else
  puts("  __I86__ undefined.");
#endif

#ifdef M_I86
  printf("  M_I86 = %u\n", (unsigned int)M_I86);
#else
  puts("  M_I86 undefined.");
#endif

#ifdef _M_IX86
  printf("  _M_IX86 = %u\n", (unsigned int)_M_IX86);
#else
  puts("  _M_IX86 undefined.");
#endif

#ifdef __i386__
  printf("  __i386__ = %u\n", (unsigned int)__i386__);
#else
  puts("  __i386__ undefined.");
#endif

  puts("*** MEMORY MODEL ***");

#if __TINY__
  printf("  __TINY__ = %u\n", __TINY__);
#elif __SMALL__
  printf("  __SMALL__ = %u\n", __SMALL__);
#elif __MEDIUM__
  printf("  __MEDIUM__ = %u\n", __MEDIUM__);
#elif __COMPACT__
  printf("  __COMPACT__ = %u\n", __COMPACT__);
#elif __LARGE__
  printf("  __LARGE__ = %u\n", __LARGE__);
#elif __HUGE__
  printf("  __HUGE__ = %u\n", __HUGE__);
#else
  puts("  No __XXX__ memory model macros detected.");
#endif

#if M_I86SM
  printf("  M_I86SM = %u\n", M_I86SM);
#elif M_I86MM
  printf("  M_I86MM = %u\n", M_I86MM);
#elif M_I86CM
  printf("  M_I86CM = %u\n", M_I86CM);
#elif M_I86LM
  printf("  M_I86LM = %u\n", M_I86LM);
#elif M_I86HM
  printf("  M_I86HM = %u\n", M_I86HM);
#else
  puts("  No M_I86xM memory model macros detected.");
#endif

#if __DPMI32__
  printf("  __DPMI32__ = %u\n", __DPMI32__);
#else
  puts("  __DPMI32__ undefined.");
#endif

  return 0;
}
