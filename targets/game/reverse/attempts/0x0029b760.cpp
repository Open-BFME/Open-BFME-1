// ?d_0029b760@@YAXXZ
// partial score=0.711806 date=2026-09-27
// cl: /DNDEBUG /MD /Igame/GameEngine/Source/GameLogic/Object /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWLib

// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
#define _OPERATOR_NEW_DEFINED_
#include "matrix3d.h"
class ModelConditionFlags { public: bool test(int n) const { return bits.test(n); } void reset(int n) { bits.reset(n); } void set(int n) { bits.set(n); } _STL::bitset<320> bits; };
#define BFME_HAVE_MODELCONDITIONFLAGS
struct Coord3D { float x,y,z; };
#define BFME_HAVE_COORD3D
#define THING_TU_MEMBERS void setPosition(const Coord3D*); void rva00132200(const Matrix3D*);
#define OBJECT_TU_MEMBERS void notifyModelConditionChanged();
#include "object.h"
class Drawable { friend class PhysicsPathStep0029B760; private: void applyPendingModelConditionFlags(bool); };
class PhysicsBehavior { public: void rva0029A6A0(bool); void rva0029B4E0(); };
struct PhysicsSleep0029B760 { char pad00[0x20]; Coord3D* begin; Coord3D* end; char pad28[0x30]; int at58; bool at5c; int sleep() { if((unsigned)(end-begin)) return 1; if(at5c && at58>0) return 1; return 0x3fffffff; } };
class ModelFlagTest000D2F40 { public: bool test(unsigned) const; };
class Pathfinder { public: void Rva003E4190(Object*); };
struct PathSystem0029B760 { char pad00[12]; Pathfinder* at0c; };
extern PathSystem0029B760* g_path0029B760;
struct Globals0029B760 { char pad00[0x1ac]; float at1ac; };
extern Globals0029B760* g_globals0029B760;
struct Config0029B760 { char pad00[0x20]; int at20; char pad24[0x1c]; bool at40,at41; char pad42[10]; float at4c; };
class PhysicsPathStep0029B760 {
public: int step();
 Config0029B760* config() { return *(Config0029B760**)((char*)this-12); }
 Object* object() { return *(Object**)((char*)this-8); }
 PhysicsBehavior* physics() { return (PhysicsBehavior*)((char*)this-16); }
 unsigned size() { return end-begin; }
 char pad00[0x10]; Coord3D* begin; Coord3D* end; char pad18[0x28]; int at40,at44,at48; bool at4c,at4d,at4e;
};
inline void setVectorHint0029B760(Object* obj,const Vector3& p) { *(bool*)((char*)obj+0x186)=true; *(Vector3*)((char*)obj+0x178)=p; }
inline void setHint0029B760(Object* obj,const Coord3D* p) { *(bool*)((char*)obj+0x186)=true; *(Coord3D*)((char*)obj+0x178)=*p; }
int PhysicsPathStep0029B760::step() {
 Config0029B760* data=config();
 at4e=false;
 bool changed=false;
 Object* obj=object();
 if(at4c && at48>0 && !(obj->m_privateStatus&1) && --at48<=0) {

  if(obj->m_modelConditionFlags.test(121)) {
   obj->m_modelConditionFlags.reset(121); obj->notifyModelConditionChanged();
   if(!(obj->m_modelConditionFlags.test(153))) { obj->m_modelConditionFlags.set(153); obj->notifyModelConditionChanged(); }
   at48=data->at20; changed=true;
  } else {
   if(((ModelFlagTest000D2F40*)((char*)obj+0x110))->test(153) && (obj->m_modelConditionFlags.test(153))) { obj->m_modelConditionFlags.reset(153); obj->notifyModelConditionChanged(); }
   physics()->rva0029A6A0(false);
  }
 }
 if((unsigned)at40>=size()) {
  physics()->rva0029B4E0();
  return ((PhysicsSleep0029B760*)physics())->sleep();
 }
 if(changed && obj->getDrawable()) obj->getDrawable()->applyPendingModelConditionFlags(false);
 const Coord3D& pos=begin[at40];
 if(data->at41 && !data->at40 && at40>0) {
  const Coord3D& previous=begin[at40-1];
  Vector3 direction(pos.x-previous.x,pos.y-previous.y,pos.z-previous.z);
  if(at44>0) direction.Z=g_globals0029B760->at1ac*data->at4c*100.0f;
  direction.Normalize();
  Vector3 position(pos.x,pos.y,pos.z);
  Matrix3D transform;
  transform.buildTransformMatrix(position,direction);
  object()->rva00132200(&transform);
 } else object()->setPosition(&pos);
 if((unsigned)at40<size()-1) {
  setHint0029B760(obj,&begin[at40+1]);
 } else {
  Vector3 next=2.0f*Vector3(pos.x,pos.y,pos.z)-Vector3(obj->m_cachedPos.x,obj->m_cachedPos.y,obj->m_cachedPos.z);
  setHint0029B760(obj,(const Coord3D*)&next);
 }
 g_path0029B760->at0c->Rva003E4190(object());
 ++at40;

 return ((PhysicsSleep0029B760*)physics())->sleep();
}



