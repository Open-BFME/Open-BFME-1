// ?d_009a6ba0@@YAXXZ
// partial score=0.916 date=2026-09-27
#include <string.h>
// Table offsets agree with Rva009A6780BuildQuantizers.cpp. No codec
// identity is asserted; retail selects a 64-entry bank and zigzag order.
extern unsigned char g_Rva01142608[];
extern int g_rva01142308[];
struct Rva009A6780State {
 int index,at0004;
 short at0008[8],at0018[8],at0028[8];
 unsigned char pad0038[0x158];
 int at0190[2][64],at0390[2][64],at0590[2][64],at0790[2][64];
};
void Rva009A6BA0QuantizeBlock(Rva009A6780State *s,const short *src,short *dst,unsigned char mode) {
 unsigned char run=0;
 int bank=g_Rva01142608[mode];
 int *multipliers=s->at0190[bank];
 int *offsets=s->at0390[bank];
 volatile int *thresholds=s->at0590[bank];
 volatile int *runs=s->at0790[bank];
 memset(dst,0,128);
 int value=src[0];
 int threshold=thresholds[0];
 if(value>=threshold) dst[0]=(short)(((value+offsets[0])*multipliers[0])>>16);
 else if(value<=-threshold) dst[0]=(short)(((value-offsets[0])*multipliers[0]+65535)>>16);
 else run=1;
 for(unsigned int i=1;i<64;i+=3) {
 {

  int pos=g_rva01142308[i+0];
  threshold=thresholds[pos]+runs[run];
  value=src[pos];
  if(value>=threshold) {
   dst[i+0]=(short)(((value+offsets[pos])*multipliers[pos])>>16);
   run=0;
  } else if(value<=-threshold) {
   dst[i+0]=(short)(((value-offsets[pos])*multipliers[pos]+65535)>>16);
   run=0;
  } else ++run;
 }
 {

  int pos=g_rva01142308[i+1];
  threshold=thresholds[pos]+runs[run];
  value=src[pos];
  if(value>=threshold) {
   dst[i+1]=(short)(((value+offsets[pos])*multipliers[pos])>>16);
   run=0;
  } else if(value<=-threshold) {
   dst[i+1]=(short)(((value-offsets[pos])*multipliers[pos]+65535)>>16);
   run=0;
  } else ++run;
 }
 {

  int pos=g_rva01142308[i+2];
  threshold=thresholds[pos]+runs[run];
  value=src[pos];
  if(value>=threshold) {
   dst[i+2]=(short)(((value+offsets[pos])*multipliers[pos])>>16);
   run=0;
  } else if(value<=-threshold) {
   dst[i+2]=(short)(((value-offsets[pos])*multipliers[pos]+65535)>>16);
   run=0;
  } else ++run;
 }
 }
}




