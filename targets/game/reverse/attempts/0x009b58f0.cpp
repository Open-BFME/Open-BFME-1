// ?Rva009B58F0@@YAXPAEHIH@Z
// partial score=0.6125 date=2026-09-30
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
#include <string.h>
struct Rva009B4880State;
struct Rva009B4880Neighbor;
struct Rva009B5830State;
extern void Rva009B4880PredictValue(Rva009B4880State *,int,short *,const Rva009B4880Neighbor *,const Rva009B4880Neighbor *);
extern void Rva009B5830ReconstructBlock(Rva009B5830State *,int);
extern void d_009b4a10();
extern void d_009ab9d0();
typedef unsigned char (__cdecl *Rva009B4A10Fn)(void *,short *,int);
typedef unsigned char (__cdecl *Rva009AB9D0Fn)(void *,short *,int,void *,void *);
typedef void (__cdecl *Rva009B58F0Callback)(short *,void *,int);
extern Rva009B58F0Callback g_01356B64,g_01356B84,g_01356C5C;
extern unsigned char g_Rva01142608[];
extern const unsigned short Rva01142BA0Table[];
#define F(T,N) (*(T *)(ctx+N))
void __cdecl Rva009B58F0(unsigned char *ctx,int row,unsigned column,int block) {
 int byteOffset=block<<7;
 int decoded;
 if(F(int,0x4520)) decoded=((Rva009B4A10Fn)d_009b4a10)(ctx,(short*)(F(unsigned char*,4)+byteOffset),F(int,0x78)!=0);
 else decoded=((Rva009AB9D0Fn)d_009ab9d0)(ctx,(short*)(F(unsigned char*,4)+byteOffset),F(int,0x78)!=0,F(void*,0xbc),F(void*,0xc0));
 Rva009B4880PredictValue((Rva009B4880State*)ctx,block,F(short*,0xc4),F(Rva009B4880Neighbor*,0xbc),F(Rva009B4880Neighbor*,0xc0));
 *(int*)(F(unsigned char*,0xc0)+4)=F(int,0xc+block*4);
 *(int*)(F(unsigned char*,0xbc)+4)=*(int*)(F(unsigned char*,0xc0)+4);
 *(short*)(F(unsigned char*,0xc0)+0xa)=*(short*)(F(unsigned char*,4)+byteOffset);
 *(short*)(F(unsigned char*,0xbc)+0xa)=*(short*)(F(unsigned char*,0xc0)+0xa);
 *(short*)(F(unsigned char*,0xc0)+8)=Rva01142BA0Table[F(int,8)*2];
 *(short*)(F(unsigned char*,0xbc)+8)=*(short*)(F(unsigned char*,0xc0)+8);
 if(decoded<=1) {
  g_01356B64((short*)(F(unsigned char*,4)+byteOffset),*(void**)(F(unsigned char*,0x13c)+0x180+g_Rva01142608[block]*4),F(int,0x270));
  *(short*)(F(unsigned char*,4)+byteOffset)=0;
  Rva009B5830ReconstructBlock((Rva009B5830State*)ctx,block);
  return;
 } else if(decoded<=10) {
  g_01356B84((short*)(F(unsigned char*,4)+byteOffset),*(void**)(F(unsigned char*,0x13c)+0x180+g_Rva01142608[block]*4),F(int,0x270));
  memset((char*)F(unsigned char*,4)+byteOffset,0,16);
  memset((char*)F(unsigned char*,4)+byteOffset+16,0,8);
  memset((char*)F(unsigned char*,4)+byteOffset+32,0,8);
  memset((char*)F(unsigned char*,4)+byteOffset+48,0,8);
  *(short*)(F(unsigned char*,4)+byteOffset+64)=0;
  Rva009B5830ReconstructBlock((Rva009B5830State*)ctx,block);
  return;
 } else {
  g_01356C5C((short*)(F(unsigned char*,4)+byteOffset),*(void**)(F(unsigned char*,0x13c)+0x180+g_Rva01142608[block]*4),F(int,0x270));
  memset((char*)F(unsigned char*,4)+byteOffset,0,128);
  Rva009B5830ReconstructBlock((Rva009B5830State*)ctx,block);
 }
}
