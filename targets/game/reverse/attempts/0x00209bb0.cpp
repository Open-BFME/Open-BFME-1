// ?beginSlowDeath@SlowDeathBehavior@@UAEXPBVDamageInfo@@@Z
// partial score=0.999131 date=2026-09-27
// Bank: one masked byte differs: EH static initialization state 0 versus retail 2.
// Retail EH map has two earlier null-cleanup states; their native lifetime source is unresolved.
// Callee relocation destinations have not yet passed add_match; preserve the existing lift.
// cl: /Igame/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
#define Coord3D ZHCoord3D
#define Coord2D ZHCoord2D
#include "Common/RandomValue.h"
#include "Common/GameCommon.h"
#include "matrix3d.h"
#include <math.h>
#include "GameLogic/LogicRandomValue.h"
#undef Coord3D
#undef Coord2D
#include "WWMath/coord3d.h"
inline Coord3D::Coord3D() {}
inline Coord3D::Coord3D(const Coord3D &that) {x=that.x; y=that.y; z=that.z;}
inline Coord3D::~Coord3D() {}

#line 310 "F:\\\\bfme\\\\Code\\\\gameengine\\\\Source\\\\GameLogic\\\\Object\\\\Behavior\\\\SlowDeathBehavior.cpp"
static void calcRandomForce(Real minMag, Real maxMag, Real minPitch, Real maxPitch, Coord3D& force)
{
	Real angle = GameLogicRandomValueReal(-PI, PI);
	Real pitch = GameLogicRandomValueReal(minPitch, maxPitch);
	Real mag = GameLogicRandomValueReal(minMag, maxMag);

	Matrix3D mtx(1);
	mtx.Scale(mag);
	mtx.Rotate_Z(angle);
	mtx.Rotate_Y(-pitch);

	Vector3 v = mtx.Get_X_Vector();

	force.x = v.X;
	force.y = v.Y;
	force.z = v.Z;
}

// Retail receiver is the SlowDeathBehaviorInterface at complete-object +0x24.
// The compact base reserves the witnessed ObjectModule and UpdateModule prefix.
class DamageInfo;
class Module;
class Drawable {
public:
 void setShadowsEnabled(bool);
 void setTerrainDecalFadeTarget(float,float);
};
template<int N> class BitFlags {
public:
 unsigned int bits[(N+31)/32];
 bool any() const { for (unsigned i=0;i<(N+31)/32;++i) if(bits[i]) return true; return false; }
};
class ModelConditionFlags {};
enum NameKeyType { NAMEKEY_INVALID=0 };
enum KindOfType { KINDOF_RVA00209BB0_HULK=0x51 };
enum UpdateSleepTime { UPDATE_SLEEP_NONE=1 };
enum SlowDeathPhaseType { SDPHASE_INITIAL=0 };
class PhysicsBehavior { public: void applyMotiveForce(const Coord3D *); };
class Thing {
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
 virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
 virtual void slot20(); virtual void slot24(); virtual Drawable *getDrawable() const;
 char pad04[0x34];
 Coord3D m_cachedPos;
 const Coord3D *getPosition() const {return &m_cachedPos;}
 bool isKindOf(KindOfType) const;
 float getHeightAboveTerrain() const;
 void setPosition(const Coord3D *);
 void setOrientation(float);
};
class Object : public Thing {
public:
 void notifyModelConditionChanged();
 int bfmeGetLastDamagePlayerIndex() const;
 void setStatus(const BitFlags<86> &,bool);
 void bfmeClearYG(const BitFlags<320> &);
 Module *findModule(NameKeyType) const;
};
template<class T> inline T &at(void *p, unsigned off) { return *(T *)((char *)p+off); }
template<class T> inline const T &at(const void *p, unsigned off) { return *(const T *)((const char *)p+off); }
inline unsigned testFlag(Object *o,unsigned n) { return at<unsigned>(o,0x110+4*(n>>5)) & (1u<<(n&31)); }
__forceinline void setFlag(Object *o,unsigned n) { if(!testFlag(o,n)) { at<unsigned>(o,0x110+4*(n>>5)) |= 1u<<(n&31); o->notifyModelConditionChanged(); } }
inline void clearFlag(Object *o,unsigned n) { if(testFlag(o,n)) { at<unsigned>(o,0x110+4*(n>>5)) &= ~(1u<<(n&31)); o->notifyModelConditionChanged(); } }
class GameLODManager {};
class GameLogic { public: void destroyObject(Object *); };
class NameKeyGenerator { public: NameKeyType nameToKey(const char *); };
extern GameLODManager *TheGameLODManager;
extern GameLogic *TheGameLogic;
extern NameKeyGenerator *TheNameKeyGenerator;
class Rva00209BB0SlavedInterface { public: virtual void slot0(); virtual void slot4(); virtual void onSlaverDie(Object *); };
struct SlowDeathBehaviorModuleData {
 char pad00[0x34];
 float m_sinkRate;
 int m_probabilityModifier;
 float m_modifierBonusPerOverkillPercent;
 unsigned m_sinkDelay, m_sinkDelayVariance;
 float m_destructionAltitude;
 unsigned m_destructionDelay,m_destructionDelayVariance;
 unsigned field54;
 char pad58[0xc0];
 float m_flingForce,m_flingForceVariance,m_flingPitch,m_flingPitchVariance;
 BitFlags<320> field128;
 BitFlags<86> field150;
 char pad15c[0x44];
 unsigned field1a0;
 unsigned char field1a4;
 bool field1a5,field1a6;
};
class UpdateModule {
public:
 virtual void slot00();
protected:
 const SlowDeathBehaviorModuleData *m_moduleData;
 Object *m_object;
 char pad0c[0x18];
 void setWakeFrame(Object *,UpdateSleepTime);
};
class SlowDeathBehaviorInterface { public: virtual void beginSlowDeath(const DamageInfo *)=0; };
class SlowDeathBehavior : public UpdateModule, public SlowDeathBehaviorInterface {
public:
 virtual void beginSlowDeath(const DamageInfo *);
protected:
 void doPhaseStuff(SlowDeathPhaseType);
private:
 unsigned m_sinkFrame,m_midpointFrame,m_destructionFrame;
 unsigned field34;
 float m_acceleratedTimeScale;
 unsigned m_flags;
 bool field40;
 char pad41[3];
 int field44;
 unsigned field48;
 unsigned field4c;
};
void SlowDeathBehavior::beginSlowDeath(const DamageInfo *) {
 if (!(m_flags & 1)) {
  const SlowDeathBehaviorModuleData *d=m_moduleData;
  Object *obj=m_object;
  if (!obj) return;
  clearFlag(obj,37);
  field44=obj->bfmeGetLastDamagePlayerIndex();
  if(d->field150.any()) obj->setStatus(d->field150,true);
  Drawable *draw=obj->getDrawable();
  if(d->field128.any()) { obj->bfmeClearYG(d->field128); unsigned flags=at<unsigned>(obj,0x114); if (!(flags&0x20000000)) {at<unsigned>(obj,0x114)=flags|0x20000000; obj->notifyModelConditionChanged();} }
  if(draw) {
   if(!d->field1a5) obj->getDrawable()->setShadowsEnabled(false);
   draw->setTerrainDecalFadeTarget(0.0f,-0.2f);
  }
  float timeScale=at<float>(TheGameLODManager,0x16e0);
  m_acceleratedTimeScale=1.0f;
  if(timeScale==0.0f && !(d->field1a4 & 6)) { TheGameLogic->destroyObject(obj); return; }
  if(m_object->isKindOf(KINDOF_RVA00209BB0_HULK) && at<int>(TheGameLogic,0x98)!=-1) {
   m_sinkFrame=1; m_midpointFrame=3; m_destructionFrame=6; m_acceleratedTimeScale=1.0f;
  } else {
   m_sinkFrame=timeScale*(d->m_sinkDelay+GetGameLogicRandomValue(0,d->m_sinkDelayVariance,"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Behavior\\SlowDeathBehavior.cpp",424));
   m_destructionFrame=timeScale*(d->m_destructionDelay+GetGameLogicRandomValue(0,d->m_destructionDelayVariance,"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Behavior\\SlowDeathBehavior.cpp",425));
   field34=timeScale*d->field54;
   m_midpointFrame=GetGameLogicRandomValue(0.35f*m_destructionFrame,0.65f*m_destructionFrame,"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Behavior\\SlowDeathBehavior.cpp",427);
   m_acceleratedTimeScale=timeScale;
  }
  if(d->field1a0!=0xfacade00) field4c=timeScale*d->field1a0;
  unsigned now=at<unsigned>(TheGameLogic,0x3c);
  unsigned when;
  if(d->m_flingForce>0) {
   if(at<unsigned>(obj,0x1a4)&8) {
    static NameKeyType key_SlavedUpdate=TheNameKeyGenerator->nameToKey("SlavedUpdate");
    Module *slave=obj->findModule(key_SlavedUpdate);
    if(slave) ((Rva00209BB0SlavedInterface *)((char *)slave+0x20))->onSlaverDie(0);
   }
   PhysicsBehavior *physics=at<PhysicsBehavior *>(obj,0x208);
   if(physics) {
    if(obj->getHeightAboveTerrain()<1.0f) { Coord3D pos=*obj->getPosition(); pos.z+=1.0f; obj->setPosition(&pos); }
    Coord3D force;
    calcRandomForce(d->m_flingForce,d->m_flingForce+d->m_flingForceVariance,d->m_flingPitch,d->m_flingPitch+d->m_flingPitchVariance,force);
    physics->applyMotiveForce(&force);
    float orientation=atan2(force.y,force.x);
    obj->setOrientation(orientation);
    setFlag(obj,113);
    m_flags|=4;
   }
   setWakeFrame(obj,UPDATE_SLEEP_NONE);
  } else if(field40) setWakeFrame(obj,UPDATE_SLEEP_NONE);
  else {
   when=m_sinkFrame;
   if(when>m_destructionFrame) when=m_destructionFrame;
   if(when>m_midpointFrame) when=m_midpointFrame;
   if(field34 && when>field34) when=field34;
   setWakeFrame(obj,(UpdateSleepTime)when);
  }
  m_sinkFrame+=now; m_destructionFrame+=now; m_midpointFrame+=now;
  if(field34) field34+=now;
  field4c+=now;
  m_flags|=1;
  doPhaseStuff(SDPHASE_INITIAL);
  if(d->field1a6) draw->setShadowsEnabled(false);
 }
}
