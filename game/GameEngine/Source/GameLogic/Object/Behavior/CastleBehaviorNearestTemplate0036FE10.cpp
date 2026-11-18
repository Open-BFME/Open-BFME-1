// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath
// ?find@NearestTemplate0036FE10@@QAEPAXABVAsciiString@@@Z
// Retail 0x0036FE10, 279 bytes (tu_map: CastleBehavior range 0x0036FD20..0x0036FF70).
// Walks TheBfmeGameLogic's object list (next at +0x88) and returns the object whose
// final-override template name (+0x20) equals the argument and which is nearest, by
// Coord3D::GetLengthEstimate, to the owner at this+8. The identity is unproven, so
// the class name keeps the address.
// Reading the owner position inline in the subtraction, instead of through a named
// pointer, gives retail's register choice (this in EDX, copied z in ECX).
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

inline __declspec(noinline) float Coord3D::GetLengthEstimate() const
{
    return estimateLength3D(*this);
}


inline Coord3D::Coord3D(const Coord3DBase &that) { x=that.x; y=that.y; z=that.z; }
inline Coord3D::~Coord3D() {}
inline Coord3D &Coord3D::operator-=(const Coord3DBase &that) { x-=that.x; y-=that.y; z-=that.z; return *this; }
class Overridable { public: const Overridable *getFinalOverride() const; };
// Retail 0x012f0898: use the existing data owner; retain the local pointee view.
class GameLogic { public: class Object *getFirstObject(); };
extern GameLogic *TheGameLogic;
class NearestTemplate0036FE10 {
public:
 void *find(const AsciiString &name);
};
void *NearestTemplate0036FE10::find(const AsciiString &name) {
 void *object=(void*)TheGameLogic->getFirstObject();
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
   Coord3D delta(*src);
   delta -= *(const Coord3DBase*)((char*)*(void**)((char*)this+8)+0x38);
   float d=((const Coord3D*)&delta)->GetLengthEstimate();
   if(!best || d<distance) { distance=d; best=object; }
  }
 }
 }
 return best;
}
