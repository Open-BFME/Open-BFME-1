// _rva009B1ED0
// partial score=0.7161 date=2026-10-03
// cl: /O2
// Bank only: full 701-byte retail extent, 699-byte draft; not a byte match.
// Seven stack arguments and info+8 are witnessed at DB1ED0.
extern "C" int Vp6FilterEdgeTagTable[];
struct Rva009B1ED0Info { int opaque[2]; int field08; };
extern "C" void __cdecl rva009B1ED0(const Rva009B1ED0Info *info, const void *sourceArgument, void *destinationArgument, int stride, int selector, const int *thresholds, unsigned variance)
{
 const unsigned char *source=(const unsigned char *)sourceArgument;
 unsigned char *dest=(unsigned char *)destinationArgument;
 int strength=thresholds[selector];
 int edgeTag=Vp6FilterEdgeTagTable[selector];
 int slope=4;
 if(info->field08>100) strength=info->field08-100;
 if(variance>32768) slope=4;
 else if(variance>2048) slope=8;
 int cap=3*strength;
 if(cap>32)cap=32;
 unsigned pixels[8];
 for(unsigned row=0;row<8;++row) {
  for(unsigned col=0;col<8;++col) {
   pixels[0]=source[col-stride-1];
   pixels[1]=source[col-stride];
   pixels[2]=source[col-stride+1];
   pixels[3]=source[col-1];
   pixels[4]=source[col+1];
   pixels[5]=source[col+stride-1];
   pixels[6]=source[col+stride];
   pixels[7]=source[col+stride+1];
   unsigned center=source[col];
   int remaining=256,sum=128;
   for(unsigned i=0;i<8;++i) {
    unsigned sample=pixels[i];
    int difference=center-sample;
    if(difference<=0)difference=sample-center;
    int weight=strength-((difference*slope)>>2)+32;
    if(weight < -64) weight=edgeTag;
    else if(weight<0)weight=0;
    else if(weight>cap)weight=cap;
    remaining-=weight;
    sum+=weight*pixels[i];
   }
   int value=(int)(remaining*center+sum)>>8;
   dest[col]=(unsigned char)(value<0 ? 0 : value>255 ? 255 : value);
  }
  source+=stride;
  dest+=stride;
 }
}
