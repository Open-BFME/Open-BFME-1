// cl: /O2 /GS /MD /GR- /EHsc-
void __cdecl ji_008793a0();
int __cdecl Rva008793B0(int);
int __cdecl d_008790b0(int);
int __cdecl bfmeRandom(int);

static inline unsigned long StartStopwatch() { return ((unsigned long (__cdecl *)())ji_008793a0)(); }
static inline unsigned long StopStopwatch(unsigned long elapsed) { return (unsigned long)Rva008793B0((int)elapsed); }
static inline long randnum(long value) { return (long)d_008790b0((int)value); }
static inline long randwc(long value) { return (long)bfmeRandom((int)value); }

#include "emfloat.c"
