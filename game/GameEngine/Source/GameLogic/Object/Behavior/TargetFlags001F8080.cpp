// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <bitset>
#include "../../../../../Libraries/Source/WWVegas/WWMath/coord3d.h"
// Retail 0x001F8080, 542 bytes. Owner remains address-derived: this is
// the update interface; module data is at this-0x0C and Object at this-8.
// Calls use existing matched identities and verified ILT routes. The native
// condition accessors retain the register-held mask at Object+0x120.
// _WriteBarrier emits no instruction; it preserves the retail shared-block
// placement for the forced-enable path without adding an assembly body.
extern "C" void _WriteBarrier();
#pragma intrinsic(_WriteBarrier)
extern "C" double fabs(double);
#pragma intrinsic(fabs)
class Condition001F8080 { public: bool test(int bit) const {return bits.test(bit);} void set(int bit) {bits.set(bit);} void reset(int bit) {bits.reset(bit);} private: _STL::bitset<320> bits; };
class Object;
class AIUpdateInterface { public: Object *getCurrentVictim() const; };
class BFMEWeaponSetFlags { public: unsigned int word; };
class BFMEWeaponSetOwner { public: const BFMEWeaponSetFlags &getWeaponSetFlags() const; };
class Gen001C9A10 { public: void handle(int); };
class Gen001C9AC0 { public: void handle(int); };
class BFMESelectionStatusBits { public: bool test(unsigned int) const; };
enum KindOfType { KIND_001F8080 = 0x6c };
class Thing { public: bool isKindOf(KindOfType) const; };
class Object { public:
char pad000[0x38]; Coord3DBase position; char pad044[0x110-0x44]; Condition001F8080 flags;
char pad138[0x204-0x138]; AIUpdateInterface *field204; char pad208[0x214-0x208]; Object *field214;
char pad218[0x344-0x218]; unsigned char m_privateStatus;
void notifyModelConditionChanged();
__forceinline const BFMEWeaponSetFlags &weaponFlags() const { return ((const BFMEWeaponSetOwner *)this)->getWeaponSetFlags(); }

};
static __forceinline void setFlag(Object *o) { if(!o->flags.test(150)) {o->flags.set(150);o->notifyModelConditionChanged();} }
static __forceinline void clearFlag(Object *o) { if(o->flags.test(150)) {o->flags.reset(150);o->notifyModelConditionChanged();} }
class AI { public: Object *findEnemyNear(Object *,float,int,int,int); }; extern AI *TheAI;
class GameLogic { public: char pad00[0x3c]; unsigned int field3c; }; extern GameLogic *TheGameLogic;
struct Data001F8080 { char pad00[8]; float field08; bool field0c; char pad0d[3]; unsigned int field10; bool field14,field15; };
class TargetFlags001F8080 { public:
char pad00[0x10]; bool field10; unsigned int field14;
int update();
};

__forceinline void enable001F8080(Object *object) {
 if(!(object->weaponFlags().word&0x80)) {
 ((Gen001C9A10 *)object)->handle(7); setFlag(object);
 }
}
__forceinline void disable001F8080(Object *object) {
 if(object->weaponFlags().word&0x80) {
 ((Gen001C9AC0 *)object)->handle(7); clearFlag(object);
 }
}
int TargetFlags001F8080::update()
{
 Data001F8080 *data=*(Data001F8080 **)((char *)this-0xc);
 Object *object=*(Object **)((char *)this-8);
 AIUpdateInterface *ai=object->field204;
 if(!ai) return 0x3fffffff; if(object->m_privateStatus&1) return 0x3fffffff;
 if(object->weaponFlags().word&0x100) return 5;
 Object *container=object->field214;
 if(container && !((Thing *)container)->isKindOf(KIND_001F8080)) return 5;
 if(data->field14 && container && ((Thing *)container)->isKindOf(KIND_001F8080)) {
  if(container->weaponFlags().word&0x80) {
   ((Gen001C9A10 *)object)->handle(7); setFlag(object);
  } else {
   ((Gen001C9AC0 *)object)->handle(7); clearFlag(object);
  }
  return 5;
 }
 if(object->flags.test(196)) return 5;
 if(field10) { _WriteBarrier(); enable001F8080(object); return 5; }
 float range=data->field08;
 Object *target;
 if(data->field15 && ai->getCurrentVictim()) {
  target=ai->getCurrentVictim();
  Coord3DBase delta;
  delta.x=object->position.x; delta.y=object->position.y; delta.z=object->position.z;
  *(Coord3D *)&delta -= target->position;
  if(((Coord3D *)&delta)->lengthSqr()>range*range) target=0;
 } else {
  target=TheAI->findEnemyNear(object,range,0x62,0,0);
 }
 if(target && (float)fabs(target->position.z-object->position.z)>range*0.5f) target=0;
 if(data->field0c && ((BFMESelectionStatusBits *)object)->test(0xcb)) {
  enable001F8080(object); return 5;
 }
 unsigned int now=TheGameLogic->field3c;
 int delay=data->field10-now+field14;
 if(delay>0) return delay;
 field14=now;
 if(target && !(target->m_privateStatus&1)) enable001F8080(object);
 else disable001F8080(object);
 return 5;
}
