// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/GameLogic/Object
// AIAttackState::onEnter: retail RVA 00184580, 970 bytes.
// Identity: constructor 0017C910 installs 0109A0C8; slot 4 routes through
// 0002CCCD to this body. The Zero Hour onEnter twin confirms its role.
// Layout follows the landed BFME ctor, destructor and attack-machine factory.
// The BFME extensions select an attack machine and adjust victim/model flags.
// Both native StringBase cleanup wrappers inline the same releaseBuffer call.
#include "string_base.h"
#include "ascii_string.h"
struct Coord3D { float x,y,z; };
#define BFME_HAVE_COORD3D 1
enum KindOfType {};
enum WeaponSlotType {};
enum Relationship {};
enum MoodMatrixAction {};
enum StateReturnType { CONTINUE=0, SUCCESS=-1, FAILURE=-2 };
class Weapon;
#define THING_TU_MEMBERS bool isKindOf(KindOfType) const;
#define OBJECT_TU_MEMBERS \
 Weapon* getCurrentWeapon(WeaponSlotType*); \
 bool bfmeIsGiantBird() const; \
 Object* bfmePostClosest(const Object*,bool); \
 Relationship getRelationship(const Object*) const; \
 void setStatusBit(int,bool); \
 void notifyModelConditionChanged(); \
 AIUpdateInterface* getAI()const {return m_ai;} \
 Team* getTeam()const{return m_team;} \
 int getID()const{return m_id;} \
 const Coord3D* getPosition()const{return &m_cachedPos;}
#include "object.h"
template<int N> class BfmeVirtualSlots: public BfmeVirtualSlots<N-1> { public: virtual void unused(char(*)[N])=0; };
template<> class BfmeVirtualSlots<0> {};
class AIUpdateInterface:public BfmeVirtualSlots<129> { public: virtual void notifyVictimIsDead()=0; unsigned getMoodMatrixActionAdjustment(MoodMatrixAction)const; void setCurrentVictim(const Object*); };
class StateMachine {public:
 virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6();
 virtual StateReturnType initDefaultState(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void setGoalObject(const Object*);
 char pad04[12]; Object* m_owner; char pad14[16]; Coord3D m_goalPosition;
 Object* getGoalObject(); unsigned getCurrentStateID()const; void setGoalPosition(const Coord3D*);
};
class AttackExitConditionsInterface {public:virtual bool shouldExit(StateMachine*)=0;};
class BfmeUnit1001 {public: char bfmeReady1001();};
class BFMEActionObject {public:bool testStatus(int)const;};
class Rva001BEF30 {public:bool has();};
class Rva001E1770ByteField {public:bool get()const;};
// Retail consumes 001E1770 as a boolean without integer normalization.
// The existing unsigned-byte getter name describes the same AL-only ABI.
void j_00028f74();
inline bool Rva001E1770ByteField::get()const {
 union {void(*f)(); bool(Rva001E1770ByteField::*m)()const;} u;
 u.f=j_00028f74; return (this->*u.m)();
}
class Gen_001e1790 {public:char m();};
// +510 is witnessed m_continueAttackRange. Unwitnessed fields retain offsets.
class WeaponTemplate {
public:
 char pad00[0x71];
 bool m_field71;
 char pad72[0x49e];
 float m_continueAttackRange;
};
class Weapon {
public:
 char pad00[4];
 WeaponTemplate* m_field04;
 char pad08[0x2c];
 unsigned m_field34;
};
// 0016F740 forwards the hidden AsciiString result via its +4 receiver.
// Its existing opaque identity does not establish a semantic accessor name.
void j_00027a48();
typedef AsciiString(Weapon::*Rva0016F740ValueMethod)();
static __forceinline Rva0016F740ValueMethod valueMethod0016F740() {
 union {void(*f)(); Rva0016F740ValueMethod m;} u;
 u.f=j_00027a48; return u.m;
}
void j_00003765();
static __forceinline void assignString(AsciiString& dst,const AsciiString& src) {
 union {void(*f)(); AsciiString&(AsciiString::*m)(const AsciiString&);} u;
 u.f=j_00003765; (dst.*u.m)(src);
}
class AIAttackState {public:
 virtual StateReturnType onEnter();
 StateMachine* getMachine()const {return m_machine;}
 char pad04[0x18]; StateMachine* m_machine; char pad20[8]; StateMachine* m_attackMachine;
 AttackExitConditionsInterface* m_attackParameters; Team* m_victimTeam; Coord3D m_originalVictimPos; AsciiString m_lockedWeaponOnEnter;
 bool m_follow,m_isAttackingObject,m_isForceAttacking; char pad47;
 unsigned m_bfmeAttackState48; bool m_bfmeAttackState4C,m_bfmeAttackState4D; char pad4e[2]; unsigned m_attackMachineType;
 protected: void createAttackMachine(Object*);
 private: bool chooseWeapon();
};
StateReturnType AIAttackState::onEnter() {
 Object* source=m_machine->m_owner;
 Object* victim=m_machine->getGoalObject();
 AIUpdateInterface* ai=source->m_ai;
 if(!(ai->getMoodMatrixActionAdjustment((MoodMatrixAction)2)&1)) return SUCCESS;
 if(m_attackParameters && m_attackParameters->shouldExit(getMachine())) return SUCCESS;
 if(((BfmeUnit1001*)source)->bfmeReady1001() && !source->isKindOf((KindOfType)25)) return FAILURE;
 if(!chooseWeapon()) return FAILURE;
 Weapon* weapon=source->getCurrentWeapon(0);
 if(!weapon) return FAILURE;
 m_bfmeAttackState4C=((Rva001E1770ByteField*)weapon->m_field04)->get();
 bool melee=false;
 if(m_isAttackingObject && victim) {
  melee=((Rva001E1770ByteField*)weapon->m_field04)->get();
  if(victim->isKindOf((KindOfType)108)) {
   victim=victim->bfmePostClosest(source,true);
   source->getAI()->setCurrentVictim(victim);
  }
 }
 if(source->isKindOf((KindOfType)2)) melee=false;
 if(source->bfmeIsGiantBird()) m_attackMachineType=0;
 else if(((BFMEActionObject*)source)->testStatus(36)) m_attackMachineType=4;
 else if(source->isKindOf((KindOfType)108)) m_attackMachineType=5;
 else if(weapon->m_field04->m_field71) m_attackMachineType=6;
 else if(melee) m_attackMachineType=((Gen_001e1790*)weapon->m_field04)->m()?1:2;
 else m_attackMachineType=3;
 createAttackMachine(source);
 StateMachine* machine=m_attackMachine;
 if(!machine) return FAILURE;
 m_bfmeAttackState4D=false;
 if(m_isAttackingObject) {
  if(!victim || (victim->m_privateStatus&1) || ((BFMEActionObject*)victim)->testStatus(49)) {
   ai->notifyVictimIsDead(); return FAILURE;
  }
  m_bfmeAttackState48=victim->getID();
  m_victimTeam=victim->getTeam();
  machine->setGoalObject(victim);
  m_originalVictimPos=victim->m_cachedPos;
  m_bfmeAttackState4D=source->getRelationship(victim)==0;
 }else {
  machine->setGoalPosition(&m_machine->m_goalPosition);
  m_originalVictimPos=m_machine->m_goalPosition;
 }
 source->setStatusBit(22,true);
 weapon->m_field34=0x7fffffff;
 if(weapon->m_field04->m_continueAttackRange>0) source->setStatusBit(27,true);
 if(((Rva001BEF30*)source)->has() && source->getCurrentWeapon(0)) {
  assignString(m_lockedWeaponOnEnter, (source->getCurrentWeapon(0)->*valueMethod0016F740())());
 }else m_lockedWeaponOnEnter.clear();
 StateReturnType ret=m_attackMachine->initDefaultState();
 if(ret==CONTINUE) {
  if(m_attackMachine->getCurrentStateID()==0xe4) {
   if(((unsigned char*)source->m_modelConditionFlags)[4]&0x20) {source->m_modelConditionFlags[1]&=~0x20; source->notifyModelConditionChanged();}
   if(((unsigned char*)source->m_modelConditionFlags)[4]&0x40) {source->m_modelConditionFlags[1]&=~0x40; source->notifyModelConditionChanged();}
  }else {
   if(!(((unsigned char*)source->m_modelConditionFlags)[4]&0x20)) {source->m_modelConditionFlags[1]|=0x20; source->notifyModelConditionChanged();}
   if(victim && victim->isKindOf((KindOfType)7)) {
    if(!(((unsigned char*)source->m_modelConditionFlags)[4]&0x40)) {source->m_modelConditionFlags[1]|=0x40; source->notifyModelConditionChanged();}
   }
  }
 }else source->setStatusBit(22,false);
 return ret;
}
