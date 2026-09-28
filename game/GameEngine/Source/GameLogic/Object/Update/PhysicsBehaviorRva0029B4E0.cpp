// PhysicsBehavior completion transition at retail RVA 0x0029B4E0 (512 bytes).
// Filename literal identifies PhysicsUpdate.cpp. Same primary this flows to
// matched PhysicsBehavior::rva0029B120 and through rva0029B350 to that method.
// Constructor/destructor establish module data +4, Object +8 and vector +0x20.
// Private method and module-data field identities remain address-derived.
// Native bitset accessors preserve the retail mask materialization and tests.
// cl: /DNDEBUG /MD /Igame/GameEngine/Source/GameLogic/Object
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
#include <vector>
struct Coord3D { float x,y,z; };
#define BFME_HAVE_COORD3D
class ModelConditionFlags { public: bool test(int n) const { return bits.test(n); } void reset(int n) { bits.reset(n); } void set(int n) { bits.set(n); } _STL::bitset<320> bits; };
#define BFME_HAVE_MODELCONDITIONFLAGS
#define OBJECT_TU_MEMBERS void notifyModelConditionChanged();
#include "object.h"
class Matrix3D;
class FXList { public: bool bfmeIsBlocked(); void doFXPos(const Coord3D*,const Matrix3D*,float,const Coord3D*) const; };
class Drawable { friend class PhysicsBehavior; private: void applyPendingModelConditionFlags(bool); };
extern int GetGameLogicRandomValue(int,int,char*,int);
struct Config0029B4E0 { char pad00[0x18]; int at18,at1c,at20,at24; char pad28[0x28]; FXList* at50; char pad54[4]; bool at58; };
class PhysicsBehavior { public:
 void rva0029B4E0(); void rva0029B350(bool); void rva0029B120(bool);
 char pad00[4]; Config0029B4E0* at04; Object* at08; char pad0c[0x14]; _STL::vector<Coord3D> at20; char pad2c[0x28]; int at54,at58; bool at5c,at5d;
};
inline void set0029B4E0(Object* o,int n) { if(!o->m_modelConditionFlags.test(n)) { o->m_modelConditionFlags.set(n); o->notifyModelConditionChanged(); } }
inline void reset0029B4E0(Object* o,int n) { if(o->m_modelConditionFlags.test(n)) { o->m_modelConditionFlags.reset(n); o->notifyModelConditionChanged(); } }
void PhysicsBehavior::rva0029B4E0() {
 if(at20.size()==0) return;
 Config0029B4E0* data=at04;
 Object* obj=at08;
 FXList* fx=data->at50;
 if(fx && !fx->bfmeIsBlocked()) fx->doFXPos((const Coord3D*)&obj->m_cachedPos,0,0.0f,0);
 bool changed=false;
 if(obj->m_modelConditionFlags.test(71)) {
  set0029B4E0(obj,115); reset0029B4E0(obj,71); reset0029B4E0(obj,120); changed=true;
 }
 if(at5c && (at58<=0 || (obj->m_privateStatus&1))) {
  reset0029B4E0(obj,120); reset0029B4E0(obj,71);
  if(obj->m_privateStatus&1) { set0029B4E0(obj,61); set0029B4E0(obj,115); }
  else { set0029B4E0(obj,121); at58=GetGameLogicRandomValue(data->at18,data->at1c,"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\PhysicsUpdate.cpp",711); changed=true; }
 }
 if(changed && obj->getDrawable()) obj->getDrawable()->applyPendingModelConditionFlags(false);
 if((at5d || data->at58) && at54<data->at24) { rva0029B350(false); return; }
 rva0029B120(true);
}
