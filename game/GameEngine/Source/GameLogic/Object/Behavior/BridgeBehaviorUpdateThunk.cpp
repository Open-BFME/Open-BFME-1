// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// readable body of ?update@BridgeBehavior@@UAE?AW4UpdateSleepTime@@XZ: game/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehavior.cpp
// BridgeBehavior::update at 0x001F38A0, 721 bytes.
//
// Identity: EA names BridgeBehavior::update (chain+direct, strong) in this
// file; the Zero Hour twin in
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehavior.cpp
// spells the same body, and the "ParentObject" string anchor is in this
// function. The readable-body TU above cannot hold it: its headers lay out
// BridgeBehavior with m_deathFrame at +0x410 (retail +0x474) and its OCL/FX
// calls follow the ZH API, so this standalone TU carries the BFME layout.
//
// Layout (retail-witnessed): getObject is this-8, getBridgeBehaviorModuleData
// is this-12, the random-surface helper takes the primary receiver at
// this-16, m_deathFrame is this+0x474, GameLogic::m_frame is +0x3c,
// Object::m_position is +0x38, Bridge::peekBridgeInfo reads this+12. The
// bridge template name comes from Bridge::getBridgeTemplateName at 0x001F22A0
// and is passed by value to TerrainRoadCollection::findBridge.
//
// Frame lever: retail shares one Coord3D scratch across the FX and OCL loops.
// Two per-loop locals pack to sub esp 0x2c with 27 displacement diffs; the
// single outer pos below packs to retail's sub esp 0x30 with zero diffs.
#include <list>
#include <string.h>
#include "string_base.h"
template<class T> inline bool StringBase<T>::isEmpty() const { return !m_data || !m_data->length; }
template<> inline int StringBase<char>::compare(const char *s) const {
 int n=s?(int)strlen(s):0;
 int len=m_data?m_data->length:0;
 const char *data=m_data?m_data->data:"";
 int c=memcmp(data,s,len<n?len:n);
 return c?c:len-n;
}
#include "ascii_string.h"
struct Coord3D { float x,y,z; };
class Matrix3D;
class Object { char pad00[0x38]; public: Coord3D m_position; bool getSingleLogicalBonePosition(const char*,Coord3D*,Matrix3D*) const; };
class BridgeInfo;
class TerrainRoadType;
class Bridge { public: AsciiString getBridgeTemplateName(); char pad00[0xc]; BridgeInfo *peekBridgeInfo() const { return (BridgeInfo*)((char*)this+12); } };
class TerrainLogic { public:
#define SLOT(n) virtual void slot##n();
 SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9)
 SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19)
 SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29)
 SLOT(30) SLOT(31) SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37)
#undef SLOT
 virtual Bridge *findBridgeAt(const Coord3D*);
};
extern TerrainLogic *TheTerrainLogic;
class TerrainRoadCollection { public: TerrainRoadType *findBridge(AsciiString); };
extern TerrainRoadCollection *TheTerrainRoads;
class GameLogic { char pad00[0x3c]; public: unsigned m_frame; unsigned getFrame() const { return m_frame; } };
extern GameLogic *TheGameLogic;
class FXList { public: bool bfmeIsBlocked(); void doFXPos(const Coord3D*,const Matrix3D*,float,const Coord3D*) const; };
class ObjectCreationList { public: void createInternal(const Object*,const Object*,unsigned) const; };
void j_00002a59();
struct Rva001D67C0View { void call(const Object*,const Coord3D*,const void*,unsigned) const; };
inline void createAt(const ObjectCreationList *p,const Object *o,const Coord3D *v) {
 if(p) { union { void (*f)(); void (Rva001D67C0View::*m)(const Object*,const Coord3D*,const void*,unsigned) const; } u;
 u.f=j_00002a59; (((const Rva001D67C0View*)p)->*u.m)(o,v,0,0); }
}
struct BridgeFX { FXList *fx; unsigned delay; AsciiString boneName; };
typedef std::list<BridgeFX> BridgeFXList;
struct BridgeOCL { const ObjectCreationList *ocl; unsigned delay; AsciiString boneName; };
typedef std::list<BridgeOCL> BridgeOCLList;
class BridgeBehaviorModuleData { char pad00[0x10]; public: BridgeFXList m_fx; BridgeOCLList m_ocl; };
enum UpdateSleepTime { UPDATE_SLEEP_NONE=1 };
class BridgeBehavior {
 char pad04[0x470]; unsigned m_deathFrame;
 Object *getObject() const { return *(Object**)((char*)this-8); }
 const BridgeBehaviorModuleData *getBridgeBehaviorModuleData() const { return *(const BridgeBehaviorModuleData**)((char*)this-12); }
protected:
 void getRandomSurfacePosition(TerrainRoadType*,const BridgeInfo*,Coord3D*);
public:
 virtual UpdateSleepTime update();
};
// Secondary UpdateModule receiver is full BridgeBehavior +0x10.
// Random-surface helper expects the primary receiver, so use its existing ILT.
void j_000406fb();
struct Rva001F1FD0View { void call(TerrainRoadType*,const BridgeInfo*,Coord3D*); };
inline void randomSurface(BridgeBehavior *b,TerrainRoadType *t,const BridgeInfo *i,Coord3D *p) {
 union { void(*f)(); void(Rva001F1FD0View::*m)(TerrainRoadType*,const BridgeInfo*,Coord3D*); }u;u.f=j_000406fb;
 (((Rva001F1FD0View*)((char*)b-16))->*u.m)(t,i,p);
}
UpdateSleepTime BridgeBehavior::update() {
 if(m_deathFrame) {
  AsciiString boneName;
  Object *us=getObject();
  const BridgeBehaviorModuleData *modData=getBridgeBehaviorModuleData();
  Bridge *bridge=TheTerrainLogic->findBridgeAt(&us->m_position);
  const BridgeInfo *bridgeInfo=0;
  TerrainRoadType *bridgeTemplate=0;
  if(bridge) {
   bridgeInfo=bridge->peekBridgeInfo();
   AsciiString bridgeTemplateName=bridge->getBridgeTemplateName();
   bridgeTemplate=TheTerrainRoads->findBridge(bridgeTemplateName);
  }
  unsigned deathTime;
  deathTime=TheGameLogic->getFrame()-m_deathFrame;
  Coord3D pos;
  BridgeFXList::const_iterator fxIt;
  for(fxIt=modData->m_fx.begin();fxIt!=modData->m_fx.end();++fxIt) {
   if(deathTime==fxIt->delay) {
    boneName=fxIt->boneName;
    if(!boneName.isEmpty()) us->getSingleLogicalBonePosition(boneName.str(),&pos,0);
    else if(bridge&&bridgeTemplate&&bridgeInfo) randomSurface(this,bridgeTemplate,bridgeInfo,&pos);
    else { pos.x=getObject()->m_position.x; pos.y=getObject()->m_position.y; pos.z=getObject()->m_position.z; }
    FXList *fx=fxIt->fx;
    if(fx && !fx->bfmeIsBlocked()) fx->doFXPos(&pos,0,0,0);
   }
  }
  BridgeOCLList::const_iterator it;
  for(it=modData->m_ocl.begin();it!=modData->m_ocl.end();++it) {
   if(deathTime==it->delay) {
    boneName=it->boneName;
    if(!boneName.isEmpty()) {
     if(boneName.compare("ParentObject")==0) { if(it->ocl) it->ocl->createInternal(us,0,0); }
     else { us->getSingleLogicalBonePosition(boneName.str(),&pos,0); createAt(it->ocl,us,&pos); }
    } else {
     if(bridge&&bridgeTemplate&&bridgeInfo) randomSurface(this,bridgeTemplate,bridgeInfo,&pos);
     else { pos.x=getObject()->m_position.x; pos.y=getObject()->m_position.y; pos.z=getObject()->m_position.z; }
     createAt(it->ocl,us,&pos);
    }
   }
  }
 }
 return UPDATE_SLEEP_NONE;
}
