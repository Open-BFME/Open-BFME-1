// ?rva0029B350@PhysicsBehavior@@QAEX_N@Z
// partial score=0.634921 date=2026-09-28
// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#define _OPERATOR_NEW_DEFINED_
#include "vector2.h"
struct Rva0029AB10Coord3D { float x,y,z; };
struct Object { char pad00[0x38]; Rva0029AB10Coord3D position; };
class UpdateModule { public: void setWakeFrame(Object*,int); };
class Terrain0029B350 { public: virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c(); virtual void s10(); virtual void s14(); virtual float height(float,float,void*); };
extern Terrain0029B350* g_terrain0029B350;
// Retail passes float bits in the third stack slot to 0x0029AB10.
// Existing unsigned third-argument declaration needs separate ABI review; no pin added.
class PhysicsBehavior:public UpdateModule { public:
 void rva0029B350(bool);
 void rva0029B120(bool);
 void rva0029AB10(const Rva0029AB10Coord3D*,float,float);
 char pad00[8]; Object* object; char pad0c[0x14]; _STL::vector<Rva0029AB10Coord3D> points; Rva0029AB10Coord3D at2c,at38; float at44,at48; int at4c,at50,at54; char pad58[6]; bool at5e;
};
inline float distance2d(float x,float y) { return (float)sqrt(x*x+y*y); }
void PhysicsBehavior::rva0029B350(bool skipWake) {
 Object* obj=object;
 if(!skipWake) setWakeFrame(obj,1);
 ++at54;
 int count=points.size();
 if(count<2) { rva0029B120(skipWake); return; }
 Rva0029AB10Coord3D pos;
 {
 Vector2 direction(points[count-1].x-points[count-2].x,points[count-1].y-points[count-2].y);
 direction.Normalize();
 float distance=distance2d(at38.x-at2c.x,at38.y-at2c.y)*0.5f;
 pos.x=obj->position.x+direction.X*distance;
 pos.y=obj->position.y+direction.Y*distance;
 }
 pos.z=g_terrain0029B350->height(pos.x,pos.y,0);
 rva0029AB10(&pos,at48*0.35f,at44*0.85f);
 at5e=true;
}
