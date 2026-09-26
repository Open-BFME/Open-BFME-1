// ??0BfmeCheckMovementInfo@@QAE@PAVPathfinder@@PAVObject@@HHHHH@Z
// partial score=0.379947 date=2026-09-25
// Retain inherited field spellings for navigation; layout and accesses below
// are established from retail offsets, not from those spellings.
// Retail RVA 003E5640 /379. Corrected bank: template reads are not Player reads;
// native 12-byte query copy is 48 -> 28; AI getter is null guarded.
// cl: /DNDEBUG /MD /ICode/GameEngine/Source/GameLogic/Object /ICode/GameEngine/Source/Common/Thing
class AIUpdateInterface { public: int getIgnoredObstacleID(); };
#define OBJECT_TU_MEMBERS bool bfmeIsComputerControlled() const; const ThingTemplate *getTemplate() const;
#include "object.h"
class Overridable {
public: virtual ~Overridable();
 const Overridable *getFinalOverride() const;
 Overridable *m_nextOverride;
};
class ThingTemplate:public Overridable {
public:
 const ThingTemplate *getFinalTemplate() const { if(m_nextOverride) return (const ThingTemplate*)m_nextOverride->getFinalOverride(); return this; }
 unsigned char m_at008[0xC8-8];
 unsigned m_at0C8;
 unsigned char m_at0CC[8];
 unsigned m_at0D4;
 unsigned char m_at0D8[0x444-0xD8];
 int m_at444;
 unsigned char m_at448[0x4CC-0x448];
 unsigned char m_at4CC;
};
inline const ThingTemplate *Object::getTemplate() const {
 return m_template ? m_template->getFinalTemplate() : 0;
}
class BfmeCheckMovementInfo;
class Pathfinder {
 friend class BfmeCheckMovementInfo;
protected: void getRadiusAndCenter(const Object*,int&,bool&);
};
struct Rva003E5640Query {
 int at00;
 bool at04,at05;
 unsigned char at06[2];
 int at08;
};
class BfmeCheckMovementInfo {
public:
 BfmeCheckMovementInfo(Pathfinder*,Object*,int,int,int,int,int);
 Pathfinder *m_pathfinder; Object *m_object;
 unsigned char m_isCrusher; char m_at09[3];
 int m_scratch0c,m_scratch10,m_scratch14,m_radius;
 bool m_center;
 unsigned char m_coordinateSamePlayer; char m_at1E[2];
 int m_mode,m_scratch24;
 Rva003E5640Query m_coordinateZone;
 int m_scratch34;
 unsigned char m_at38,m_playerIsComputer,m_at3A,m_at3B;
 int m_scratch3c;
 char m_at40[8];
 Rva003E5640Query m_zone;
 unsigned char m_allowPinched,m_coordinatePlayerIndex;
};
BfmeCheckMovementInfo::BfmeCheckMovementInfo(
 Pathfinder *pathfinder,Object *object,int parameter3,int parameter4,
 int parameter5,int parameter6,int parameter7)
{
 m_pathfinder=pathfinder;
 m_isCrusher=(unsigned char)parameter5;
 m_object=object;
 m_scratch0c=0;m_scratch10=0;m_scratch14=0;m_radius=0;m_center=0;m_coordinateSamePlayer=0;
 m_mode=0;m_scratch24=0;m_coordinateZone.at00=0;m_coordinateZone.at04=0;m_coordinateZone.at05=0;
 m_coordinateZone.at08=-1;m_scratch34=0;m_playerIsComputer=0;m_at3A=0;m_at38=0;m_scratch3c=0;
 int index=object->getTemplate()->m_at444;
 unsigned char flag=object->getTemplate()->m_at4CC;
 bool computer=object->bfmeIsComputerControlled();
 m_zone.at00=parameter3;
 m_zone.at05=computer;
 m_zone.at04=(flag==0);
 m_zone.at08=index-1;
 m_allowPinched=(unsigned char)parameter7;
 m_coordinateZone=m_zone;
 m_coordinateSamePlayer=(unsigned char)parameter4;
 m_coordinatePlayerIndex=0;
 m_mode=13;
 if (!parameter6 || !(object->getTemplate()->m_at0C8&0x800))
  m_mode=15;
 AIUpdateInterface *ai=m_object->m_ai;
 m_scratch24=ai?ai->getIgnoredObstacleID():0;
 Object *current=m_object;
 if (current->getTemplate()->m_at0D4&0x1000) {
  m_radius=1;m_center=true;
 } else m_pathfinder->getRadiusAndCenter(current,m_radius,m_center);
}
