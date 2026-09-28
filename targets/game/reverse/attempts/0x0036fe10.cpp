// ?find@NearestTemplate0036FE10@@QAEPAXABVAsciiString@@@Z
// partial score=0.616487 date=2026-09-28
// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath
#include "ascii_string.h"
#include "coord3d.h"
class Overridable { public: const Overridable *getFinalOverride() const; };
class Gen_00383090 { public: int m(); };
extern Gen_00383090 *TheBfmeGameLogic;
class NearestTemplate0036FE10 {
public:
 void *find(const AsciiString &name);
};
void *NearestTemplate0036FE10::find(const AsciiString &name) {
 void *object=(void*)TheBfmeGameLogic->m();
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
   const Coord3DBase *src=(const Coord3DBase*)((char*)object+0x38);
   const Coord3DBase *pos=(const Coord3DBase*)((char*)*(void**)((char*)this+8)+0x38);
   Coord3DBase delta;
   delta.z=src->z; delta.x=src->x-pos->x; delta.y=src->y-pos->y; delta.z-=pos->z;
   float d=((const Coord3D*)&delta)->GetLengthEstimate();
   if(!best || d<distance) { distance=d; best=object; }
  }
 }
 }
 return best;
}
