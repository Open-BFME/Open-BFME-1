// ?updateInternal@AIAttackApproachTargetState@@AAE?AW4StateReturnType@@XZ
// partial score=0.9957081545 date=2026-09-27
// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath
#include "coord3d.h"
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
inline Coord3D::Coord3D(const Coord3D &v) { x=v.x; y=v.y; z=v.z; }
inline Coord3D &Coord3D::operator=(const Coord3D &v) { x=v.x; y=v.y; z=v.z; return *this; }
inline Coord3D &Coord3D::operator+=(const Coord3DBase &v) {x+=v.x; y+=v.y; z+=v.z; return *this;}
typedef bool Bool;
enum StateReturnType { STATE_CONTINUE=0, STATE_SUCCESS=-1, STATE_FAILURE=-2 };
enum WeaponSlotType {};
class Object; class Weapon; class Player;
class Rva001827C0Data { public: char pad00[0x24]; float rva24; bool rva28; };
class AIUpdateInterface { public:
 virtual void slot000();
 virtual void slot004();
 virtual void slot008();
 virtual void slot00C();
 virtual void slot010();
 virtual void slot014();
 virtual void slot018();
 virtual void slot01C();
 virtual void slot020();
 virtual void slot024();
 virtual void slot028();
 virtual void slot02C();
 virtual void slot030();
 virtual void slot034();
 virtual void slot038();
 virtual void slot03C();
 virtual void slot040();
 virtual void slot044();
 virtual void slot048();
 virtual void slot04C();
 virtual void slot050();
 virtual void slot054();
 virtual void slot058();
 virtual void slot05C();
 virtual void slot060();
 virtual void slot064();
 virtual void slot068();
 virtual void slot06C();
 virtual void slot070();
 virtual void slot074();
 virtual void slot078();
 virtual void slot07C();
 virtual void slot080();
 virtual void slot084();
 virtual void slot088();
 virtual void slot08C();
 virtual void slot090();
 virtual void slot094();
 virtual void slot098();
 virtual void slot09C();
 virtual void slot0A0();
 virtual void slot0A4();
 virtual void slot0A8();
 virtual void slot0AC();
 virtual void slot0B0();
 virtual void slot0B4();
 virtual void slot0B8();
 virtual void slot0BC();
 virtual void slot0C0();
 virtual void slot0C4();
 virtual void slot0C8();
 virtual void slot0CC();
 virtual void slot0D0();
 virtual void slot0D4();
 virtual void slot0D8();
 virtual void slot0DC();
 virtual void slot0E0();
 virtual void slot0E4();
 virtual void slot0E8();
 virtual void slot0EC();
 virtual void slot0F0();
 virtual void slot0F4();
 virtual void slot0F8();
 virtual void slot0FC();
 virtual void slot100();
 virtual void slot104();
 virtual void slot108();
 virtual void slot10C();
 virtual void slot110();
 virtual void slot114();
 virtual void slot118();
 virtual void slot11C();
 virtual void slot120();
 virtual void slot124();
 virtual void slot128();
 virtual void slot12C();
 virtual void slot130();
 virtual void slot134();
 virtual void slot138();
 virtual void slot13C();
 virtual void slot140();
 virtual void slot144();
 virtual void slot148();
 virtual void slot14C();
 virtual void slot150();
 virtual void slot154();
 virtual void slot158();
 virtual void slot15C();
 virtual void slot160();
 virtual void slot164();
 virtual void slot168();
 virtual void slot16C();
 virtual void slot170();
 virtual void slot174();
 virtual void slot178();
 virtual void slot17C();
 virtual void slot180();
 virtual void slot184();
 virtual void slot188();
 virtual void slot18C();
 virtual void slot190();
 virtual void slot194();
 virtual void slot198();
 virtual void slot19C();
 virtual void slot1A0();
 virtual void slot1A4();
 virtual void slot1A8();
 virtual void slot1AC();
 virtual void slot1B0();
 virtual void slot1B4();
 virtual void slot1B8();
 virtual void slot1BC();
 virtual void slot1C0();
 virtual void slot1C4();
 virtual void slot1C8();
 virtual void slot1CC();
 virtual void slot1D0();
 virtual void slot1D4();
 virtual void slot1D8();
 virtual void slot1DC();
 virtual void slot1E0();
 virtual void slot1E4();
 virtual void slot1E8();
 virtual bool isDoingGroundMovement();
 virtual void slot1F0();
 virtual void slot1F4();
 virtual void slot1F8();
 virtual void slot1FC();
 virtual void slot200();
 virtual void notifyVictimIsDead();
 Rva001827C0Data *rva04;
 char pad08[0x31f-8]; bool m_isAttackPath;
 char pad320[0x335-0x320]; bool rva335;
 void setCurrentVictim(const Object*);
 unsigned int getCurrentStateID() const;
 bool isQuickPathAvailable(const Coord3D*) const;
};
class Thing { public: const Coord3D *getUnitDirectionVector2D() const; };
class Team { public: char pad00[4]; void *rva04; Object *getTeamTargetObject(); };
class Object : public Thing { public:
 char pad00[0x38]; Coord3D m_position;
 char pad44[0x74-0x44]; unsigned int m_id;
 char pad78[0x94-0x78]; unsigned int rva94;
 char pad98[0x204-0x98]; AIUpdateInterface *m_ai;
 char pad208[0x23c-0x208]; Team *m_team;
 Weapon *getCurrentWeapon(WeaponSlotType *slot=0);
 Player *getControllingPlayer() const;
 float bfmeGetNonnegativePreferredLocomotorHeight() const;
 const Coord3D *getPosition() const {return &m_position;}
};
class Weapon { public:
 char pad00[4]; void *rva04;
 bool isWithinAttackRange(const Object*,const Object*,int) const;
 bool isWithinAttackRange(const Object*,const Coord3D*,int) const;
 bool isGoalPosWithinAttackRange(const Object*,const Coord3D*,const Object*,const Coord3D*,float) const;
};
class StateMachine { public:
 char pad00[0x10]; Object *m_owner;
 bool isGoalObjectDestroyed() const;
 Object *getGoalObject();
};
class Rva001827C0AiData { public: char pad00[0x4c]; float m_alertRangeModifier,m_aggressiveRangeModifier; };
class Pathfinder { public: bool isAttackViewBlockedByObstacle(const Object*,const Coord3D*,const Object*,const Coord3D*); };
class BfmePathfinderMethods { public: bool check(const Object*,const Coord3D*,const Weapon*,int); };
class Rva001827C0AI { public: char pad00[0xc]; Pathfinder *rva0c; Pathfinder *pathfinder() {return rva0c;} char pad10[4]; Rva001827C0AiData *rva14; };
class Rva001827C0GameLogic { public: char pad00[0x3c]; unsigned int m_frame; char pad40[0x1a0-0x40]; int rva1a0; };
extern Rva001827C0AI *rva001827C0_ai;
extern Rva001827C0GameLogic *rva001827C0_game;
class CRCParameterCheck;
extern CRCParameterCheck *TheCRCParameterCheck;
extern "C" void __cdecl bfmeRetailCritterDesyncLog(CRCParameterCheck*,const char*,...);
bool bfmeMeleeHordeTargetInvalid(Object*,Object*);
class ThiscallReceiverView {};
template<class T> __forceinline T member(void(*raw)()) { union { void(*raw)(); T ptr; } f; f.raw=raw; return f.ptr; }
#define CALL(T,obj,fn) (((ThiscallReceiverView*)(obj))->*member<T>(fn))
extern void j_00028f74();
extern void j_00003b1b();
extern void j_0000b8ac();
extern void j_00023042();
extern void j_00019ff1();
extern void j_0003a391();
extern void j_0001bb3f();
extern void j_00032b46();
typedef bool (ThiscallReceiverView::*BoolQuery)();
typedef bool (ThiscallReceiverView::*StealthQuery)(Player*);
typedef int (ThiscallReceiverView::*IntQuery)();
typedef unsigned int (ThiscallReceiverView::*FlagsQuery)();
typedef bool (ThiscallReceiverView::*ViewQuery)(Object*,const Coord3D&,Object*,const Coord3D&);
typedef bool (ThiscallReceiverView::*PathQuery)(Object*,const Coord3D*,Weapon*,bool);
class AIInternalMoveToState { public: StateReturnType update();
 virtual void slot00();
 virtual void slot04();
 virtual void slot08();
 virtual void slot0C();
 virtual void slot10();
 virtual void slot14();
 virtual void slot18();
 virtual void slot1C();
 virtual void slot20();
 virtual void slot24();
 virtual void slot28();
 virtual void slot2C();
 virtual void slot30();
 virtual void slot34();
 virtual void slot38();
 virtual void slot3C();
 virtual void slot40();
};
class AIAttackApproachTargetState : public AIInternalMoveToState { public:
 virtual bool computePath();
 char pad04[0x1c-4]; StateMachine *m_machine;
 char pad20[4]; Coord3D m_goalPosition;
 char pad30[0x50-0x30]; Coord3D m_prevVictimPos; Coord3D rva5c;
 unsigned int rva68, rva6c;
 bool m_follow,m_isAttackingObject,m_stopIfInRange,m_isInitialApproach,m_isForceAttacking,rva75;
private: StateReturnType updateInternal();
};
StateReturnType AIAttackApproachTargetState::updateInternal()
{
 AIUpdateInterface *ai=m_machine->m_owner->m_ai;
 if(m_machine->isGoalObjectDestroyed()) {
  ai->notifyVictimIsDead(); ai->setCurrentVictim(0); return STATE_FAILURE;
 }
 m_stopIfInRange=!ai->m_isAttackPath;
 if(rva75) m_stopIfInRange=true;
 StateReturnType code=STATE_FAILURE;
 Object *source=m_machine->m_owner;
 Weapon *weapon=source->getCurrentWeapon();
 Object *victim=m_machine->getGoalObject();
 if(weapon && CALL(BoolQuery,weapon->rva04,j_00028f74)()) m_stopIfInRange=false;
 if(victim) {
  if(victim->rva94 & 0x40000) return STATE_FAILURE;
  if(CALL(StealthQuery,victim,j_00003b1b)(source->getControllingPlayer())) return STATE_FAILURE;
  ai->setCurrentVictim(victim);
  bool melee=bfmeMeleeHordeTargetInvalid(source,victim);
  bool inRange=false;
  if(weapon) {
   if(melee) {
    Coord3D target=*victim->getPosition();
    Coord3D direction; const Coord3D *facing=victim->getUnitDirectionVector2D(); unsigned x=*(const unsigned*)&facing->x; unsigned y=*(const unsigned*)&facing->y; *(unsigned*)&direction.x=x; unsigned z=*(const unsigned*)&facing->z; *(unsigned*)&direction.y=y; *(unsigned*)&direction.z=z;
    direction.Scale(victim->bfmeGetNonnegativePreferredLocomotorHeight()*4.0f);
    target+=direction;
    inRange=weapon->isGoalPosWithinAttackRange(source,source->getPosition(),victim,&target,0.0f);
   } else inRange=weapon->isWithinAttackRange(source,victim,0);
  }
  bool viewBlocked=rva001827C0_ai->rva0c->isAttackViewBlockedByObstacle(source,source->getPosition(),victim,victim->getPosition());
  if(weapon && CALL(BoolQuery,weapon->rva04,j_0000b8ac)() && inRange) return STATE_SUCCESS;
  if(m_stopIfInRange && weapon && inRange) {
   if(ai->isDoingGroundMovement() && !CALL(BoolQuery,victim,j_00019ff1)() && !viewBlocked) return STATE_SUCCESS;
  }
  if(rva75) { if(rva001827C0_game->m_frame>rva6c) return STATE_FAILURE; return STATE_CONTINUE; }
  if(ai->rva04->rva28 && CALL(IntQuery,source,j_0003a391)()>=17 && !inRange && !ai->isQuickPathAvailable(victim->getPosition())) {
   rva75=true; rva6c=rva001827C0_game->m_frame+50; return STATE_CONTINUE;
  }
  bool checkRange=true;
  unsigned int state=ai->getCurrentStateID();
  if(state==17 || state==16 || state==35) checkRange=false;
  if(!ai->rva335) checkRange=false;
  if(source->m_team && *((bool*)source->m_team->rva04+0x1c2) && source->m_team->getTeamTargetObject()) checkRange=false;
  if(checkRange && bfmeMeleeHordeTargetInvalid(source,victim)) {
   float range=ai->rva04->rva24;
   if(range>0.0f) {
    Coord3D delta=*victim->getPosition();
    delta.x-=source->getPosition()->x; delta.y-=source->getPosition()->y; delta.z-=source->getPosition()->z;
    float dist=delta.length();
    unsigned int flags=CALL(FlagsQuery,ai,j_0001bb3f)();
    if(!(flags&1)) {
     switch(flags&0x1f00) {
      case 0x100: range=0.0f; break;
      case 0x800: range*=rva001827C0_ai->rva14->m_alertRangeModifier; break;
      case 0x1000: range*=rva001827C0_ai->rva14->m_aggressiveRangeModifier; break;
     }
    }
    if(dist>range) return STATE_FAILURE;
   }
  }
  if(!computePath()) {
   if(TheCRCParameterCheck) bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"%i AIAttackApproachTargetState success [3]",source->m_id);
   return STATE_SUCCESS;
  }
  if(!rva75) {
   code=AIInternalMoveToState::update();
   if(code!=STATE_CONTINUE) {
    Coord3D delta=rva5c;
    delta.x-=source->getPosition()->x; delta.y-=source->getPosition()->y; delta.z-=source->getPosition()->z;
    bool targetMoved=false;
    Coord3D moved=*victim->getPosition();
    moved.Sub(m_prevVictimPos);
    if(moved.lengthSqr()>100.0f) targetMoved=true;
    bool positionMoved=delta.lengthSqr()>100.0f;
    if((inRange && !viewBlocked) || targetMoved || positionMoved) return STATE_SUCCESS;
    if(((BfmePathfinderMethods*)rva001827C0_ai->pathfinder())->check(source,victim->getPosition(),weapon,0)) return STATE_SUCCESS;
    rva75=true; rva6c=rva001827C0_game->m_frame+50;
    code=STATE_CONTINUE;
   }
  } else code=STATE_CONTINUE;
 } else {
  if(rva001827C0_game->rva1a0>0 && m_stopIfInRange && weapon) {
   if(TheCRCParameterCheck) bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"masiwar called by AIAttackApproachTargetState::updateInternal [2]");
  }
  if(m_stopIfInRange && weapon && weapon->isWithinAttackRange(source,&m_goalPosition,0)) {
   bool viewBlocked=false;
   if(ai->isDoingGroundMovement()) {Pathfinder *const pf=rva001827C0_ai->pathfinder();const Coord3D &pos=*source->getPosition();viewBlocked=pf->isAttackViewBlockedByObstacle(source,&pos,0,&m_goalPosition);}
   if(!viewBlocked) return STATE_SUCCESS;
  }
  if(!computePath()) return STATE_FAILURE;
  code=AIInternalMoveToState::update();
 }
 return code;
}
