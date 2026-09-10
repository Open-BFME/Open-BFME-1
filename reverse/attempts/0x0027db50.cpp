// ?privateAttackPosition@AIUpdateInterface@@MAEXPBUCoord3D@@HW4CommandSourceType@@@Z
// partial score=0.53 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// BFME attack-position command at RVA 0x0027DB50, 562 bytes, ret 12.
// Source twin: AIUpdate.cpp privateAttackPosition. Retail adds weapon-set
// and object guards, linked partition filters and attack voice response.
extern "C" void *__cdecl memcpy(void *,const void *,unsigned int);
#pragma intrinsic(memcpy)
typedef bool Bool;
enum CommandSourceType { CMD_FROM_PLAYER, CMD_FROM_AI, CMD_FROM_INTERNAL };
enum WeaponSlotType { PRIMARY_WEAPON };
enum StateID { AI_ATTACK_POSITION = 9 };
struct Coord3D { float x,y,z; };
class Object;
class WeaponSetFlags { public: unsigned int word; };
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
class PartitionFilterPossibleToAttack:public PartitionFilter {
public:
 PartitionFilterPossibleToAttack(const Object *p,CommandSourceType c):source(p),command(c),attackType(0) {}
protected: virtual Bool allow(Object *);
private: const Object *source; CommandSourceType command; int attackType;
};
class PartitionManager {
public: Object *getClosestObject(const Coord3D *,float,int,PartitionFilter *);
};
extern PartitionManager *ThePartitionManager;
extern const float BfmeZeroRange;
struct FindPositionOptions {
 FindPositionOptions();
 unsigned int flags; float minRadius,maxRadius,startAngle,maxZDelta;
 const Object *ignoreObject,*sourceToPathToDest,*relationshipObject;
};
Bool findPositionAround(const Coord3D *,const FindPositionOptions *,Coord3D *);
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
 Bool isPathAvailable(const Coord3D *) const;
 void destroyPath();
 void setGoalPositionClipped(const Coord3D *,CommandSourceType);
protected:
 void playAttackVoiceResponse(const Coord3D *);
 virtual void privateAttackPosition(const Coord3D *,int,CommandSourceType);
private:
 unsigned char prefix[4]; Object *object;
 unsigned char gap0C[0x24]; StateMachine *machine;
 unsigned char gap34[0x14]; CommandSourceType lastCommand;
};
void AIUpdateInterface::privateAttackPosition(const Coord3D *pos,int maxShots,CommandSourceType command)
{
 if ((object->getWeaponSetFlags().word & 0x100) && command==CMD_FROM_PLAYER) return;
 if (object->flags & 8) return;
 Coord3D localPos=*pos;
 Weapon *weapon=object->getCurrentWeapon(0);
 if (weapon) {
  float range;
  memcpy(&range,&weapon->weaponTemplate->continueRange,sizeof(range));
  if (range>BfmeZeroRange) {
   object->setMode(27,1);
   Object *victim;
   {
    PartitionFilterSameMapStatus mapFilter(object);
    PartitionFilterPossibleToAttack attackFilter(object,command);
    victim=ThePartitionManager->getClosestObject(&localPos,range,0,attackFilter.link(&mapFilter));
   }
   object->setMode(27,0);
   if (victim) {
    reinterpret_cast<AICommandInterface *>(reinterpret_cast<char *>(this)+0x20)->aiAttackObject(victim,maxShots,command);
    return;
   }
   maxShots=1;
  }
  if (weapon->weaponTemplate->isContactWeapon() && !isPathAvailable(&localPos)) {
   FindPositionOptions options;
   options.minRadius=0; options.maxRadius=100;
   options.sourceToPathToDest=object;
   Coord3D tmp;
   if (findPositionAround(&localPos,&options,&tmp)) localPos=tmp;
  }
 }
 machine->clear(); destroyPath();
 setGoalPositionClipped(&localPos,command); lastCommand=command;
 machine->setState(AI_ATTACK_POSITION); machine->setGoalObject(0);
 weapon=object->getCurrentWeapon(0);
 if (weapon) { weapon->maxShots=maxShots; weapon->shotsFired=0; }
 if (command==CMD_FROM_PLAYER || command==CMD_FROM_AI) playAttackVoiceResponse(&localPos);
}
