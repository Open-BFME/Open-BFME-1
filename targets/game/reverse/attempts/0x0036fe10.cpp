// ?find@NearestTemplate0036FE10@@QAEPAXABVAsciiString@@@Z
// partial score=0.9857 date=2026-10-03
// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath
#include "ascii_string.h"
#include "coord3d.h"
#include <math.h>
static const float length_estimate_factor = 0.25f;
static __forceinline float estimateLength2D(float a, float b)
{
    if (a > b)
        return a + length_estimate_factor * b;
    return b + length_estimate_factor * a;
}

static __forceinline float estimateLength3D(const Coord3D &coord)
{
    float ax = fabs(coord.x);
    float ay = fabs(coord.y);
    float xy = estimateLength2D(ax, ay);
    float az = fabs(coord.z);
    if (xy > az)
        return estimateLength2D(ax, ay) + length_estimate_factor * az;
    return az + length_estimate_factor * estimateLength2D(ax, ay);
}

__declspec(noinline) float Coord3D::GetLengthEstimate() const
{
    return estimateLength3D(*this);
}


inline Coord3D::Coord3D(const Coord3DBase &that) { x=that.x; y=that.y; z=that.z; }
inline Coord3D::~Coord3D() {}
inline Coord3D &Coord3D::operator-=(const Coord3DBase &that) { x-=that.x; y-=that.y; z-=that.z; return *this; }
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
   const Coord3DBase *src=(const Coord3DBase*)((char*)object+0x38);
   const Coord3DBase *pos=(const Coord3DBase*)((char*)*(void**)((char*)this+8)+0x38);
   Coord3D delta(*src);
   delta -= *pos;
   float d=((const Coord3D*)&delta)->GetLengthEstimate();
   if(!best || d<distance) { distance=d; best=object; }
  }
 }
 }
 return best;
}
