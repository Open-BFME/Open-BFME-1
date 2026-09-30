// ?update@AIAttackState@@UAE?AW4StateReturnType@@XZ
// partial score=0.5948 date=2026-09-30
// cl: /DNDEBUG /MD /EHs-c- /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/GameLogic/Object
// ?update@AIAttackState@@UAE?AW4StateReturnType@@XZ
// partial 2026-09-30 opus-5.5: 1100/1108 B, 433 differing bytes (prior bank 1102 B / 447).
// Residue: retail spills weapon (reloads into ecx), keeps &m_lockedWeaponOnEnter and
// then the compare result in EBX, frame 0x14; ours keeps weapon in EBX, frame 0x10.
// AIAttackState::update: retail RVA 0017CAE0, 1108 bytes.
// Identity: constructor 0017C910 installs 0109A0C8; the Zero Hour update twin
// and the matched onEnter (00184580) / onExit (0017D050) siblings share the
// layout below. BFME adds the giant-bird/sleep guard, mood-matrix victim
// rejection, the related-container veto, the locked-weapon GondorTrebuchet
// exception and the melee-type re-entry.
#include "string_base.h"
template<> inline StringBase<char>::~StringBase() { releaseBuffer(); }
template<> inline bool StringBase<char>::isEmpty() const { return m_data == 0 || m_data->length == 0; }
#include "ascii_string.h"
struct Coord3D { float x,y,z; };
#define BFME_HAVE_COORD3D 1
enum KindOfType {};
enum WeaponSlotType {};
enum Relationship { ENEMIES = 0, NEUTRAL = 1 };
enum StateReturnType { CONTINUE=0, SUCCESS=-1, FAILURE=-2 };
enum StateExitType { EXIT_NORMAL = 0 };
class Weapon;
class Team;
#define THING_TU_MEMBERS bool isKindOf(KindOfType) const;
#define OBJECT_TU_MEMBERS \
 Weapon* getCurrentWeapon(WeaponSlotType*); \
 Relationship getRelationship(const Object*) const; \
 void notifyModelConditionChanged(); \
 AIUpdateInterface* getAI()const {return m_ai;} \
 Team* getTeam()const{return m_team;} \
 ContainModuleInterface* getContain()const{return m_contain;}
#include "object.h"
template<int N> class BfmeVirtualSlots: public BfmeVirtualSlots<N-1> { public: virtual void unused(char(*)[N])=0; };
template<> class BfmeVirtualSlots<0> {};
class AIUpdateInterface:public BfmeVirtualSlots<128> {
public:
 virtual unsigned getMoodMatrixAction()=0;
 virtual void notifyVictimIsDead()=0;
 virtual void s130()=0; virtual void s131()=0; virtual void s132()=0; virtual void s133()=0;
 virtual void s134()=0; virtual void s135()=0;
 virtual bool isSleeping()=0;
 void setCurrentVictim(const Object*);
 void friend_setGoalObject(Object*);
};
class ContainModuleInterface:public BfmeVirtualSlots<2> {
public:
 virtual bool isGarrisonable()const=0;
 virtual void c03()=0; virtual void c04()=0; virtual void c05()=0; virtual void c06()=0; virtual void c07()=0;
 virtual void c08()=0; virtual void c09()=0; virtual void c10()=0; virtual void c11()=0; virtual void c12()=0;
 virtual void c13()=0; virtual void c14()=0; virtual void c15()=0; virtual void c16()=0; virtual void c17()=0;
 virtual void c18()=0; virtual void c19()=0; virtual void c20()=0; virtual void c21()=0; virtual void c22()=0;
 virtual void c23()=0; virtual void c24()=0; virtual void c25()=0; virtual void c26()=0; virtual void c27()=0;
 virtual void c28()=0; virtual void c29()=0; virtual void c30()=0; virtual void c31()=0; virtual void c32()=0;
 virtual void c33()=0; virtual void c34()=0; virtual void c35()=0; virtual void c36()=0; virtual void c37()=0;
 virtual void c38()=0; virtual void c39()=0; virtual void c40()=0; virtual void c41()=0; virtual void c42()=0;
 virtual bool vetoesAttack(Object *source, Object *victim)const=0;
 virtual void c44()=0; virtual void c45()=0; virtual void c46()=0; virtual void c47()=0; virtual void c48()=0;
 virtual void c49()=0; virtual void c50()=0; virtual void c51()=0; virtual void c52()=0; virtual void c53()=0;
 virtual void c54()=0; virtual void c55()=0; virtual void c56()=0; virtual void c57()=0; virtual void c58()=0;
 virtual void c59()=0; virtual void c60()=0; virtual void c61()=0; virtual void c62()=0; virtual void c63()=0;
 virtual unsigned getContainCount(int)const=0;
};
class Team { public: Object *getTeamTargetObject(); void setTeamTargetObject(const Object*); };
class StateMachine {public:
 virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
 virtual StateReturnType updateStateMachine(); virtual void s5(); virtual void s6(); virtual void s7();
 virtual StateReturnType setState(unsigned); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13();
 virtual void setGoalObject(const Object*);
 char pad04[12]; Object* m_owner; char pad14[4]; unsigned m_currentStateID;
 Object* getGoalObject(); unsigned getCurrentStateID()const;
};
class AttackExitConditionsInterface {public:virtual bool shouldExit(StateMachine*)=0;};
class BfmeUnit1001 {public: char bfmeReady1001();};
class BFMEActionObject {public:bool testStatus(int)const;};
class Gen_0016A1B0 {public: bool bfmeQuery()const;};
class Overridable {public: const Overridable *getFinalOverride()const; char pad00[4]; Overridable *m_nextOverride;};
class ThingTemplate : public Overridable {public: char pad08[0x18]; AsciiString m_name;};
class Rva001E1770ByteField {public:bool get()const;};
void j_00028f74();
inline bool Rva001E1770ByteField::get()const {
 union {void(*f)(); bool(Rva001E1770ByteField::*m)()const;} u;
 u.f=j_00028f74; return (this->*u.m)();
}
class Weapon {
public:
 char pad00[4];
 Rva001E1770ByteField* m_field04;
 char pad08[0x2c];
 int m_field34;
};
class State {public:
 virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
 virtual StateReturnType onEnter(); virtual void onExit(StateExitType); virtual StateReturnType update();
};
class AIAttackState : public State {public:
 virtual StateReturnType update();
 StateMachine* getMachine()const {return m_machine;}
 char pad04[0x18]; StateMachine* m_machine; char pad20[8]; StateMachine* m_attackMachine;
 AttackExitConditionsInterface* m_attackParameters; Team* m_victimTeam; Coord3D m_originalVictimPos; AsciiString m_lockedWeaponOnEnter;
 bool m_follow,m_isAttackingObject,m_isForceAttacking; char pad47;
 unsigned m_bfmeAttackState48; bool m_bfmeAttackState4C,m_bfmeAttackState4D; char pad4e[2]; unsigned m_attackMachineType;
 private: bool chooseWeapon();
};
class Rva0016F9E0WeaponNameShim {public: AsciiString getName() const;};
#define CONVERT_SLEEP_TO_CONTINUE(s) ((s) > 0 ? CONTINUE : (s))
// ?update@AIAttackState@@UAE?AW4StateReturnType@@XZ
StateReturnType AIAttackState::update() {
 Object* source=m_machine->m_owner;
 Object* victim=m_machine->getGoalObject();
 if(m_attackParameters && m_attackParameters->shouldExit(getMachine())) return SUCCESS;
 AIUpdateInterface* ai=source->getAI();
 if(ai && ai->isSleeping()) return CONTINUE;
 if(((BfmeUnit1001*)source)->bfmeReady1001() && !source->isKindOf((KindOfType)25)) return FAILURE;
 if(m_isAttackingObject) {
  if(!victim || (victim->m_privateStatus&1) || ((BFMEActionObject*)victim)->testStatus(49)) {
   source->getAI()->notifyVictimIsDead();
   if(source->isKindOf((KindOfType)150)) return SUCCESS;
   StateReturnType status=m_attackMachine->updateStateMachine();
   return CONVERT_SLEEP_TO_CONTINUE(status);
  }
  AIUpdateInterface* activeAI=source->getAI();
  unsigned action=activeAI->getMoodMatrixAction();
  bool sourceFlag=((BFMEActionObject*)source)->testStatus(28);
  const bool &enemy=source->getRelationship(victim)==ENEMIES;
  if(!enemy && m_bfmeAttackState4D && (action&2) && !sourceFlag && !victim->isKindOf((KindOfType)93)) {
   activeAI->friend_setGoalObject(0);
   if(victim==source->getTeam()->getTeamTargetObject()) source->getTeam()->setTeamTargetObject(0);
   activeAI->notifyVictimIsDead();
   return FAILURE;
  }
  source->getAI()->setCurrentVictim(victim);
  if(victim->getTeam()!=m_victimTeam) {
   if(ai && !((BFMEActionObject*)victim)->testStatus(1) && victim->getContain() &&
      victim->getContain()->isGarrisonable() && victim->getContain()->getContainCount(0)==0 &&
      source->getRelationship(victim)==NEUTRAL) {
    ai->friend_setGoalObject(0);
    if(victim==source->getTeam()->getTeamTargetObject()) source->getTeam()->setTeamTargetObject(0);
    ai->notifyVictimIsDead();
    return FAILURE;
   }
   if(source->getRelationship(victim)!=ENEMIES) {
    ai->friend_setGoalObject(0);
    if(victim==source->getTeam()->getTeamTargetObject()) source->getTeam()->setTeamTargetObject(0);
    ai->notifyVictimIsDead();
    return FAILURE;
   }
  }
  if(victim!=m_attackMachine->getGoalObject()) m_attackMachine->setGoalObject(victim);
 }
 Object* related=source->m_containedBy;
 if(related && related->getContain() && related->getContain()->vetoesAttack(source,victim)) return FAILURE;
 if(!chooseWeapon()) return FAILURE;
 Weapon* weapon=source->getCurrentWeapon(0);
 if(!m_lockedWeaponOnEnter.isEmpty() && weapon && m_lockedWeaponOnEnter.compare(((const Rva0016F9E0WeaponNameShim*)weapon)->getName().str())) {
  const ThingTemplate *tmpl=*(const ThingTemplate**)((char*)source+4);
  if(tmpl && tmpl->m_nextOverride) tmpl=(const ThingTemplate*)tmpl->m_nextOverride->getFinalOverride();
  if(tmpl->m_name.compare("GondorTrebuchet")) return FAILURE;
 }
 if(!weapon || weapon->m_field34<=0) return FAILURE;
 if(weapon->m_field04->get()!=m_bfmeAttackState4C) {
  onExit(EXIT_NORMAL);
  if(ai) {
   ai->setCurrentVictim(victim);
   ai->friend_setGoalObject(victim);
   m_machine->setGoalObject(victim);
  }
  return onEnter();
 }
 if(m_attackMachine->getCurrentStateID()==0xe4) {
  if(((unsigned char*)source->m_modelConditionFlags)[4]&0x20) {source->m_modelConditionFlags[1]&=~0x20; source->notifyModelConditionChanged();}
  if(((unsigned char*)source->m_modelConditionFlags)[4]&0x40) {source->m_modelConditionFlags[1]&=~0x40; source->notifyModelConditionChanged();}
 }else {
  if(!(((unsigned char*)source->m_modelConditionFlags)[4]&0x20)) {source->m_modelConditionFlags[1]|=0x20; source->notifyModelConditionChanged();}
  if(victim && victim->isKindOf((KindOfType)7)) {
   if(!(((unsigned char*)source->m_modelConditionFlags)[4]&0x40)) {source->m_modelConditionFlags[1]|=0x40; source->notifyModelConditionChanged();}
  }
 }
 if(((Gen_0016A1B0*)m_attackMachine)->bfmeQuery()) {
  if(m_attackMachine->setState(m_attackMachine->m_currentStateID)==FAILURE) return FAILURE;
 }
 StateReturnType status=m_attackMachine->updateStateMachine();
 return CONVERT_SLEEP_TO_CONTINUE(status);
}
