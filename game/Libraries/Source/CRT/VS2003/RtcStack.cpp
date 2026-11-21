// cl: /O1 /G6 /Oi /Ob1 /MD /GX-
// Independent reconstruction of native stack.obj's ordinary fastcall guard
// checker, from retail, COFF identity/relocations and CodeView types. The
// descriptor layouts are the public rtcapi.h definitions (8 and 12 bytes).
// Its flag-dependent sibling remains assembly in RTC_CheckEsp.asm; no naked
// C++ or compiler-generated import aliases are used here.
#include <rtcapi.h>
#pragma intrinsic(_ReturnAddress)
void _RTC_StackFailure(void *,const char *);

extern "C" void __fastcall _RTC_CheckStackVars(void *frame,_RTC_framedesc *v) {
 unsigned int byteOffset=0;
 for(int i=0;i<v->varCount;++i,byteOffset+=sizeof(_RTC_vardesc)) {
  int pos=(*(_RTC_vardesc *)((char *)v->variables+byteOffset)).addr;
  int size=(*(_RTC_vardesc *)((char *)v->variables+byteOffset)).size;
  if(*(int *)((unsigned long)frame+pos-4)!=0xCCCCCCCC ||
     *(int *)((unsigned long)frame+pos+size)!=0xCCCCCCCC)
   _RTC_StackFailure(_ReturnAddress(),(*(_RTC_vardesc *)((char *)v->variables+byteOffset)).name);
 }
}
