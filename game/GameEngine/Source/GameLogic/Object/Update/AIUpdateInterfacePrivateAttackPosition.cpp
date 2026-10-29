// ?privateAttackPosition@AIUpdateInterface@@MAEXPBUCoord3D@@HW4CommandSourceType@@@Z
// cl: /DNDEBUG /MD /EHsc
// readable body of ?privateAttackPosition@AIUpdateInterface@@: game/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
// BFME attack-position command at RVA 0x0027DB50, 562 bytes through ret 12.
// Source twin: Zero Hour AIUpdate.cpp privateAttackPosition. Retail adds the
// weapon-set bit 8 player gate, the Object+0x344 bit 3 early-out, linked
// partition filters and the attack voice response.
// The continue range is a volatile local: retail copies the template float
// through EAX into the dead cmdSource argument home, loads it from there for
// the compare and reloads it into EDX for the getClosestObject push after
// PartitionFilter::link; a plain local keeps the bits in EBX across the call.
// The weapon-set word is captured in an unsigned local, which makes MSVC load
// it into EAX (retail) rather than ECX (the inline test(8) spelling).
// The attack filter installs vtable 0x010956C4, not PartitionFilterPossibleToAttack's
// 0x010FD964, so it keeps an address-derived name and stores the recorded
// table g_010956C4 itself (novtable), as AIMeleeReAcquireState_update.cpp does.
typedef bool Bool;
#include "../../command_source_type.h"
enum WeaponSlotType { PRIMARY_WEAPON };
enum StateID { AI_ATTACK_POSITION = 9 };
// class-gate: allow Coord3D ilt_oracle confirms the row's PBVCoord3D (class-keyed) decoration; Lib/Coord3D.h is struct-keyed
class Coord3D { public: float x,y,z; };
class Object;
class WeaponSetFlags { public: Bool test(int type) const { return (word & (1U << type)) != 0; } unsigned int word; };
class BfmeOutOfWeaponRangeTemplate {
public:
 Bool isContactWeapon() const;
 unsigned char prefix[0x510]; float continueRange;
};
class Weapon {
public:
 void *vtable; BfmeOutOfWeaponRangeTemplate *weaponTemplate;
 unsigned char gap[0x18]; int shotsFired;
 unsigned char gap24[0x10]; int maxShots;
};
class Object {
public:
 const WeaponSetFlags &getWeaponSetFlags() const;
 Weapon *getCurrentWeapon(WeaponSlotType *slot);
 void setMode(int bit,int value);
 unsigned char prefix[0x344]; unsigned char flags;
};
class PartitionFilter {
public:
 PartitionFilter():next(0) {}
 virtual ~PartitionFilter() {}
 virtual Bool allow(Object *)=0;
 PartitionFilter *link(PartitionFilter *);
 PartitionFilter *next;
};
class PartitionFilterSameMapStatus:public PartitionFilter {
public:
 PartitionFilterSameMapStatus(const Object *p):source(p) {}
protected: virtual Bool allow(Object *);
private: const Object *source;
};
extern const void *g_010956C4[];
class __declspec(novtable) Rva010956C4AttackFilter:public PartitionFilter {
public:
 Rva010956C4AttackFilter(const Object *p,CommandSourceType c)
 {
  *reinterpret_cast<unsigned int *>(this)=(unsigned int)g_010956C4;
  source=p; command=c; attackType=0;
 }
protected: virtual Bool allow(Object *);
private: const Object *source; CommandSourceType command; int attackType;
};
class PartitionManager {
public: Object *getClosestObject(const Coord3D *,float,int,PartitionFilter *);
};
extern PartitionManager *ThePartitionManager;
// Retail 0x01075350 is ?g_rva01075350@@3MB (data_rows.csv,
// Common/BfmeAngleWrap0079D0.cpp); BfmeBoundaryZero3D was only a pin.
extern const float g_rva01075350;
#define BfmeBoundaryZero3D g_rva01075350
struct FindPositionOptions {
 FindPositionOptions();
 unsigned int flags; float minRadius,maxRadius,startAngle,maxZDelta;
 const Object *ignoreObject,*sourceToPathToDest,*relationshipObject;
};
// Retail reaches the four Coord3D-taking callees through their ILT thunks.
// BFME's Coord3D is class-keyed (ilt_oracle confirms
// ?privateAttackPosition@AIUpdateInterface@@MAEXPBVCoord3D@@...), while the
// existing pins for these callees spell it as a struct, so they are called
// through the thunk rows by address:
//   j_0001f9b5 -> 0x0026F200 AIUpdateInterface::isPathAvailable
//   j_00026c4c -> 0x001AF610 findPositionAround (cdecl, three arguments)
//   j_000284b1 -> 0x00273DE0 AIUpdateInterface::setGoalPositionClipped
//   j_0001060e -> 0x00273200 AIUpdateInterface::playAttackVoiceResponse(position)
extern void j_0001f9b5();
extern void j_00026c4c();
extern void j_000284b1();
extern void j_0001060e();
class AICommandInterface {
public: void aiAttackObject(Object *,int,CommandSourceType);
};
class StateMachine {
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08();
 virtual void slot0C(); virtual void slot10(); virtual void clear();
 virtual void slot18(); virtual void slot1C(); virtual void setState(StateID);
 virtual void slot24(); virtual void slot28(); virtual void slot2C();
 virtual void slot30(); virtual void slot34(); virtual void setGoalObject(const Object *);
};
class AIUpdateInterface {
public:
 void destroyPath();
protected:
 Bool callIsPathAvailable(const Coord3D *p) const
 {
  typedef Bool (AIUpdateInterface::*Fn)(const Coord3D *) const;
  union { void (*fn)(); Fn call; } u = { j_0001f9b5 };
  return (this->*u.call)(p);
 }
 void callSetGoalPositionClipped(const Coord3D *p,CommandSourceType c)
 {
  typedef void (AIUpdateInterface::*Fn)(const Coord3D *,CommandSourceType);
  union { void (*fn)(); Fn call; } u = { j_000284b1 };
  (this->*u.call)(p,c);
 }
 void callPlayAttackVoiceResponse(const Coord3D *p)
 {
  typedef void (AIUpdateInterface::*Fn)(const Coord3D *);
  union { void (*fn)(); Fn call; } u = { j_0001060e };
  (this->*u.call)(p);
 }
 virtual void privateAttackPosition(const Coord3D *,int,CommandSourceType);
private:
 unsigned char prefix[4]; Object *object;
 unsigned char gap0C[0x24]; StateMachine *machine;
 unsigned char gap34[0x14]; CommandSourceType lastCommand;
};
void AIUpdateInterface::privateAttackPosition(const Coord3D *pos,int maxShots,CommandSourceType command)
{
 unsigned int w=object->getWeaponSetFlags().word;
 if ((w & 0x100) && command==CMD_FROM_PLAYER) return;
 if (object->flags & 8) return;
 Coord3D localPos=*pos;
 Weapon *weapon=object->getCurrentWeapon(0);
 if (weapon) {
  volatile float range=weapon->weaponTemplate->continueRange;
  if (range>BfmeBoundaryZero3D) {
   object->setMode(27,1);
   Object *victim;
   {
    PartitionFilterSameMapStatus mapFilter(object);
    Rva010956C4AttackFilter attackFilter(object,command);
    victim=ThePartitionManager->getClosestObject(&localPos,*(float *)&range,0,attackFilter.link(&mapFilter));
   }
   object->setMode(27,0);
   if (victim) {
    reinterpret_cast<AICommandInterface *>(reinterpret_cast<char *>(this)+0x20)->aiAttackObject(victim,maxShots,command);
    return;
   }
   maxShots=1;
  }
  if (weapon->weaponTemplate->isContactWeapon() && !callIsPathAvailable(&localPos)) {
   FindPositionOptions options;
   options.minRadius=0; options.maxRadius=100;
   options.sourceToPathToDest=object;
   Coord3D tmp;
   typedef Bool (*FindPositionAround)(const Coord3D *,const FindPositionOptions *,Coord3D *);
   if (((FindPositionAround)j_00026c4c)(&localPos,&options,&tmp)) localPos=tmp;
  }
 }
 machine->clear(); destroyPath();
 callSetGoalPositionClipped(&localPos,command); lastCommand=command;
 machine->setState(AI_ATTACK_POSITION); machine->setGoalObject(0);
 weapon=object->getCurrentWeapon(0);
 if (weapon) { weapon->maxShots=maxShots; weapon->shotsFired=0; }
 if (command==CMD_FROM_PLAYER || command==CMD_FROM_SCRIPT) callPlayAttackVoiceResponse(&localPos);
}
