// cl: /O2 /GR- /DNDEBUG /DWIN32 /MD /EHsc-
// Retail RVA 0x001BB0D0, 890 bytes. Identity: matched dispatcher 0x001BC820.
// The appearance-1/8 branches pass Object*, Coord3D*, distance and speed.
// Template names at +0x40 and +0xd4 follow name_oracle field witnesses;
// the unsigned conversion at +0x238 independently proves the +0x40 load type.
// Unwitnessed mover/template fields retain their offsets. Coord3D is the
// SAGE plain three-float type; WWMath coord3d.h describes a different type.
// See docs/header_adoption.md on the conflicting Coord3D headers.
#include <math.h>
#pragma intrinsic(atan2, fabs)
typedef float Real;
struct Coord3D { Real x,y,z; };
class Overridable {
public:
 const Overridable *getFinalOverride() const;
 void *m_vtable;
 const Overridable *m_nextOverride;
};
class LocomotorTemplate : public Overridable {
public:
 char pad008[0x40-8]; unsigned m_acceleration;
 char pad044[0xd4-0x44]; int m_canMoveBackward;
 char pad0d8[0x130-0xd8]; bool field130;
 char pad131[3]; Real field134,field138,field13c;
};
enum CommandSourceType { COMMANDSOURCE_AI = 2 };
class AICommandInterface { public: void aiIdle(CommandSourceType); };
struct Rva001BB0D0AI { char pad000[0x20]; AICommandInterface command; };
struct ModelConditionFlags {
 unsigned test(int i) const { return bits[i>>5] & (1u<<(i&31)); }
 void set(int i) { bits[i>>5] |= (1u<<(i&31)); }
 void clear(int i) { bits[i>>5] &= ~(1u<<(i&31)); }
 unsigned bits[10];
};
#define BFME_HAVE_COORD3D
#define BFME_HAVE_MODELCONDITIONFLAGS
#define OBJECT_TU_MEMBERS \
 void notifyModelConditionChanged(); \
 void setModelConditionState(int bit) { \
  if (!m_modelConditionFlags.test(bit)) { m_modelConditionFlags.set(bit); notifyModelConditionChanged(); } \
 } \
 void clearModelConditionState(int bit) { \
  if (m_modelConditionFlags.test(bit)) { m_modelConditionFlags.clear(bit); notifyModelConditionChanged(); } \
 }
#include "object.h"
#undef OBJECT_TU_MEMBERS
struct Mat12;
class BfmeSub1CC_EC3 { public:
 Real effectiveMaxSpeed(void *objectArgument);
 void copyMatrixAndGo(Mat12 *m,int a,int b);
};
class BfmeQ1282;
class BfmeA1282 { public: void bfmeFinish1282(BfmeQ1282*,const Coord3D*,Real,Real); };
Real normalizeAngle(Real);
Real Cos(Real);
Real Sin(Real);
class Rva001BB0D0Mover {
public:
 void move(Object *obj,const Coord3D *goalPos,Real onPathDistToGoal,Real desiredSpeed);
 void *m_vtable; const LocomotorTemplate *m_template;
 char pad008[0x14-8]; Real field014,field018;
 char pad01c[0x2c-0x1c]; Real field02c;
 char pad030[0x3c-0x30]; Real field03c; unsigned m_flags;
 const LocomotorTemplate *getTemplate() const {
  const LocomotorTemplate *p=m_template;
  if(p && p->m_nextOverride) p=static_cast<const LocomotorTemplate *>(p->m_nextOverride->getFinalOverride());
  return p;
 }
 bool getFlag(int i) const { return (m_flags>>i)&1; }
 void setFlag(int i,bool value) { if(value) m_flags|=1u<<i; else m_flags&=~(1u<<i); }
};
void Rva001BB0D0Mover::move(Object *obj,const Coord3D *goalPos,Real onPathDistToGoal,Real desiredSpeed)
{
 Real maxSpeed=((BfmeSub1CC_EC3*)this)->effectiveMaxSpeed(obj);
 if(desiredSpeed>maxSpeed) desiredSpeed=maxSpeed;
 Real angle=obj->m_cachedAngle;
 Real desiredAngle=(Real)atan2(goalPos->y-obj->m_cachedPos.y,goalPos->x-obj->m_cachedPos.x);
 Real relAngle=normalizeAngle(desiredAngle-angle);
 bool moveBackwards=getTemplate()->m_canMoveBackward!=0;
 if(moveBackwards) {
  Coord3D delta;
  delta.x=field014; delta.y=field018;
  delta.x-=obj->m_cachedPos.x; delta.y-=obj->m_cachedPos.y;
  Real ax=(Real)fabs(delta.x), ay=(Real)fabs(delta.y);
  Real dist;
  if(ax>ay) dist=ax+ay*0.25f; else dist=ay+ax*0.25f;
  if(dist>getTemplate()->field134 && onPathDistToGoal>getTemplate()->field138) moveBackwards=false;
 }
 Real actualSpeed=field03c;
 if(moveBackwards && fabs(relAngle)>getTemplate()->field13c*3.1415927f) {
  obj->setModelConditionState(146);
  setFlag(7,true);
 } else {
  obj->clearModelConditionState(146);
  setFlag(7,false);
 }
 if(getFlag(7)) desiredAngle=normalizeAngle(desiredAngle-3.1415927f);
 // Sibling block lifetimes let this coordinate reuse the earlier delta slot.
 {
 Coord3D desiredPos=obj->m_cachedPos;
 desiredPos.x+=Cos(desiredAngle)*1000.0f;
 desiredPos.y+=Sin(desiredAngle)*1000.0f;
 // Established 0x001B9C50 ABI: object transform prefix and position pointer
 // carried in its historical int slot, as in the matched wings sibling.
 ((BfmeSub1CC_EC3*)this)->copyMatrixAndGo((Mat12*)obj,(int)&desiredPos,0);
 }
 Real cap=((BfmeSub1CC_EC3*)this)->effectiveMaxSpeed(obj);
 cap/=getTemplate()->m_acceleration;
 if(cap>field02c) cap=field02c;
 if(actualSpeed<=cap) relAngle*=2.0f;
 else if(actualSpeed>maxSpeed*0.25f) relAngle=0.0f;
 if(maxSpeed>0.0f) {
  Real angleCoeff=(Real)fabs(relAngle)/(3.1415927f/4.0f);
  if(angleCoeff>1.0f) angleCoeff=1.0f;
  Real goalSpeed;
  if(getTemplate()->field130 && getFlag(7))
   if((obj->m_modelConditionFlags.bits[3]&0x60000000u)==0) goalSpeed=desiredSpeed; else goalSpeed=0.0f;
  else goalSpeed=getFlag(7) ? desiredSpeed : (1.0f-angleCoeff)*desiredSpeed;
  ((BfmeA1282*)this)->bfmeFinish1282((BfmeQ1282*)obj,goalPos,onPathDistToGoal,goalSpeed);
 } else if(fabs(relAngle)<0.01f) ((Rva001BB0D0AI*)obj->m_ai)->command.aiIdle(COMMANDSOURCE_AI);
}



