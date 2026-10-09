// cl: /O2 /G6 /DNDEBUG /MD
extern int g_012D7818[8][2];
void __cdecl Rva009A7FE0Vp6Filter(const unsigned char *,unsigned short *,int,const int *,const int *);

// ?Rva009A8110BilinearByteBlock@@YAXPBEPAEIIIIPBH@Z absent-from-retail
// Ported from Open BFME 2 Code/Libraries/Source/VP6/FilterBlockBil8.cpp.
static void Rva009A8110BilinearByteBlock(const unsigned char *source,unsigned char *destination,
 unsigned int pitch,unsigned int step,unsigned int rows,unsigned int columns,const int *weights)
{
 for(unsigned int row=0;row<rows;++row) {
  for(unsigned int column=0;column<columns;++column) {
   destination[column]=(unsigned char)((source[step]*weights[1]+source[0]*weights[0]+64)>>7);
   ++source;
  }
  source+=pitch-columns;
  destination+=columns;
 }
}
// ?Rva009A8110Filter@@YAXPBE0PAEHHH@Z
// Ported from Open BFME 2 Code/Libraries/Source/VP6/FilterBlockBil8.cpp.
void Rva009A8110Filter(const unsigned char *first,const unsigned char *second,
 unsigned char *destination,int pitch,int horizontal,int vertical)
{
 int distance=second-first;
 if(distance<0) {
  const unsigned char *temporary=first;
  first=second;
  second=temporary;
  distance=second-first;
 }
 if(distance==1) Rva009A8110BilinearByteBlock(first,destination,pitch,1,8,8,g_012D7818[horizontal]);
 else if(distance==(int)pitch) Rva009A8110BilinearByteBlock(first,destination,pitch,pitch,8,8,g_012D7818[vertical]);
 else if(distance==(int)(pitch-1)) Rva009A7FE0Vp6Filter(first-1,(unsigned short *)destination,pitch,g_012D7818[horizontal],g_012D7818[vertical]);
 else if(distance==(int)(pitch+1)) Rva009A7FE0Vp6Filter(first,(unsigned short *)destination,pitch,g_012D7818[horizontal],g_012D7818[vertical]);
}
