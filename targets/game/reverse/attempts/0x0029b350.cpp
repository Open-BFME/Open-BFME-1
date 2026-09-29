// ?rva0029B350@PhysicsBehavior@@QAEX_N@Z
// partial score=0.8127 date=2026-09-30
// ?rva0029B350@PhysicsBehavior@@QAEX_N@Z
// Residue: retail hoists the TheTerrainLogic vtable load above the pos stores; ours keeps it after them.
// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#define _OPERATOR_NEW_DEFINED_
#include "vector2.h"
struct Rva0029AB10Coord3D {
 float x,y,z;
 void set(const Rva0029AB10Coord3D* a) { x=a->x; y=a->y; z=a->z; }
 float length2D() const { return (float)sqrt(x*x+y*y); }
 void sub(const Rva0029AB10Coord3D* a) { x-=a->x; y-=a->y; z-=a->z; }
};
class Object { public: char pad00[0x38]; Rva0029AB10Coord3D position; };
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };
class UpdateModule { protected: void setWakeFrame(Object*,UpdateSleepTime); };
class TerrainLogic { public: virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c(); virtual void s10(); virtual void s14(); virtual float height(float x,float y,Rva0029AB10Coord3D* normal) const; };
extern TerrainLogic* TheTerrainLogic;
class PhysicsBehavior:public UpdateModule { public:
 void rva0029B350(bool);
 void rva0029B120(bool);
 void rva0029AB10(const Rva0029AB10Coord3D*,float,unsigned int);
 char pad00[8]; Object* object; char pad0c[0x14]; _STL::vector<Rva0029AB10Coord3D> points; Rva0029AB10Coord3D at2c,at38; float at44,at48; int at4c,at50,at54; char pad58[6]; bool at5e;
};
typedef void (PhysicsBehavior::*Rva0029AB10FloatWhen)(const Rva0029AB10Coord3D*,float,float);
void PhysicsBehavior::rva0029B350(bool skipWake) {
 Object* obj=object;
 if(!skipWake) setWakeFrame(obj,UPDATE_SLEEP_NONE);
 ++at54;
 int count=points.size();
 if(count<2) { rva0029B120(skipWake); return; }
 Vector2 direction(points[count-1].x-points[count-2].x,points[count-1].y-points[count-2].y);
 direction.Normalize();
 Rva0029AB10Coord3D delta;
 delta.set(&at38);
 delta.sub(&at2c);
 {
 Rva0029AB10Coord3D pos;
 pos.x=obj->position.x+direction.X*(delta.length2D()*0.5f);
 pos.y=obj->position.y+direction.Y*(delta.length2D()*0.5f);
 pos.z=TheTerrainLogic->height(pos.x,pos.y,0);
 (this->*(Rva0029AB10FloatWhen)&PhysicsBehavior::rva0029AB10)(&pos,at48*0.35f,at44*0.85f);
 }
 at5e=true;
}
