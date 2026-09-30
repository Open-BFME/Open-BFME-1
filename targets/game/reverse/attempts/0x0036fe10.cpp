// ?find@NearestTemplate0036FE10@@QAEPAXABVAsciiString@@@Z
// partial score=0.9534 date=2026-09-30
// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath
#include "ascii_string.h"
#include "coord3d.h"
class Overridable { public: const Overridable *getFinalOverride() const; };
struct Rva00367E30Logic;
extern Rva00367E30Logic *TheBfmeGameLogic;
class Gen_00383090 { public: int m(); };
class NearestTemplate0036FE10 {
public:
 void *find(const AsciiString &name);
};
#pragma comment(linker, "/alternatename:?m@Gen_00383090@@QAEHXZ=?j_000358be@@YAXXZ")
#pragma comment(linker, "/alternatename:?getFinalOverride@Overridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ")
#pragma comment(linker, "/alternatename:?GetLengthEstimate@Coord3D@@QBEMXZ=?j_00036aa2@@YAXXZ")
void *NearestTemplate0036FE10::find(const AsciiString &name) {
 void *object=(void*)((Gen_00383090 *)TheBfmeGameLogic)->m();
 void *best=0;
 float distance=99999.0f;
 if(object) {
 const void *nameData=*(const void **)&name;
 for(;object;object=*(void**)((char*)object+0x88)) {
  const void *tmpl=*(void**)((char*)object+4);
  if(tmpl) {
   const Overridable *next=*(Overridable**)((char*)tmpl+4);
   if(next) tmpl=next->getFinalOverride();
  }
  if(((const AsciiString*)((const char*)tmpl+0x20))->compare(*(const AsciiString*)&nameData)==0) {
   const volatile float *src=(const volatile float*)((char*)object+0x38);
   const Coord3DBase *pos=(const Coord3DBase*)((char*)*(void**)((char*)this+8)+0x38);
   float sourceX=src[0];
   float sourceY=src[1];
   unsigned int sourceZ=*(const unsigned int *)&src[2];
   Coord3DBase delta;
   delta.z=*(const float *)&sourceZ;
   delta.x=sourceX-pos->x;
   delta.y=sourceY-pos->y;
   delta.z-=pos->z;
   float d=((const Coord3D*)&delta)->GetLengthEstimate();
   if(!best || d<distance) { distance=d; best=object; }
  }
 }
 }
 return best;
}
