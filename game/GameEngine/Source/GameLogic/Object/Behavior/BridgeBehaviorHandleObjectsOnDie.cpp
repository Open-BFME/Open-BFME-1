// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWMath
// stlport
// RVA 0x001F4F40 +712. The named BridgeBehavior::onDie in
// landed BridgeBehaviorOnHealing.cpp calls this method; ZH twin supplies
// the bridge polygon and height-filter algorithm. BFME has an owning
// partition-result handle and always kills qualifying objects: retail has
// no PhysicsBehavior branch. Names from the prior body are preserved.
// Layout: module object +8; Object position +0x38 and template +4;
// Bridge info +0xc / layer +0x88. BridgeInfo is 108 bytes, copied as
// nine three-word blocks (retail rep movsd 27). Coord3D contains only XYZ;
// byte-copy assignment preserves its native non-arithmetic copy semantics.
// Wide-result vector/refcount ABI is independently shared with the landed
// TerrainLogicSetWaterHeight.cpp; the int-word radius is the existing
// BfmeWideForwardA ABI. No new callee pins.
#include <vector>
#include <math.h>
#include <string.h>
#include "coord3d.h"
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
inline Coord3D &Coord3D::operator=(const Coord3D &v) { memcpy(this,&v,12); return *this; }
enum PathfindLayerEnum { LAYER_GROUND=1 };
enum DamageType { DAMAGE_UNRESISTABLE=8 };
enum DeathType { DEATH_NORMAL=0 };
class BridgeInfo {
public:
 BridgeInfo();
 Coord3D from,to;
 float bridgeWidth;
 Coord3D fromLeft,fromRight,toLeft,toRight;
 int bridgeIndex,curDamageState,bridgeObjectID,towerObjectID[4];
 bool damageStateChanged;
};
class Bridge { char pad00[12]; public: BridgeInfo m_bridgeInfo; char bounds[16]; PathfindLayerEnum m_layer; };
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
class Overridable { public: const Overridable *getFinalOverride() const; void *vtable; Overridable *m_nextOverride; };
class ThingTemplate : public Overridable { public: char pad08[0xc0]; unsigned m_kindOf; };
class Thing { public: float getHeightAboveTerrain() const; };
class Object : public Thing { public:
 void *vtable; ThingTemplate *m_template; char pad08[0x30]; Coord3D m_position;
 unsigned isKindOf(unsigned bit) const { const ThingTemplate *t=m_template; if(t && t->m_nextOverride) t=(const ThingTemplate*)t->m_nextOverride->getFinalOverride(); return t->m_kindOf&bit; }
 void setLayer(PathfindLayerEnum);
 void kill(DamageType,DeathType);
};
struct BfmeIterEntry { Object *m_obj; void *m_extra; };
struct BfmeObjectIterator { std::vector<BfmeIterEntry> m_entries; BfmeIterEntry *m_cur; int m_refCount; };
struct BfmeWideResult {
 BfmeObjectIterator *m_value;
 BfmeWideResult(); BfmeWideResult(const BfmeWideResult&);
 ~BfmeWideResult() { if(--m_value->m_refCount==0) delete m_value; }
 Object *next() { if(m_value->m_cur==m_value->m_entries.end()) return 0; return (m_value->m_cur++)->m_obj; }
};
class BfmeWideForwardA { public: BfmeWideResult bfmeForwardWideA(int,int,int,int); };
class PartitionManager;
extern PartitionManager *ThePartitionManager;
extern const float g_rva01075350;
void j_000015e1();
void j_0003a391();
struct Rva001BEC20View { int call() const; };
inline int getLayer(const Object *o) { union { void (*f)(); int (Rva001BEC20View::*m)() const; } u;u.f=j_0003a391;return (((const Rva001BEC20View*)o)->*u.m)(); }
inline Coord2D::Coord2D() {}
inline Coord2D::~Coord2D() {}
inline float Coord2D::length() const { return (float)sqrt(x*x+y*y); }
class BridgeBehavior { char pad00[8]; Object *m_object; protected: void handleObjectsOnBridgeOnDie(); };
void BridgeBehavior::handleObjectsOnBridgeOnDie() {
 const Object *bridge=m_object;
 const Coord3D *bridgePos=&bridge->m_position;
 Bridge *terrainBridge=TheTerrainLogic->findBridgeAt(&m_object->m_position);
 if(terrainBridge) {
  PathfindLayerEnum bridgeLayer=terrainBridge->m_layer;
  BridgeInfo bridgeInfo;
  memcpy(&bridgeInfo,&terrainBridge->m_bridgeInfo,sizeof(bridgeInfo));
  Coord3D bridgePolygon[4];
  bridgePolygon[0]=bridgeInfo.fromLeft;
  bridgePolygon[1]=bridgeInfo.fromRight;
  bridgePolygon[2]=bridgeInfo.toRight;
  bridgePolygon[3]=bridgeInfo.toLeft;
  float lowBridgeZ=bridgePolygon[0].z;
  for(int i=0;i<4;++i) if(bridgePolygon[i].z<lowBridgeZ) lowBridgeZ=bridgePolygon[i].z;
  Coord2D v;
  v.x=bridgeInfo.toLeft.x-bridgePos->x;
  v.y=bridgeInfo.toLeft.y-bridgePos->y;
  float radius=v.length();
  BfmeWideResult iter=((BfmeWideForwardA*)ThePartitionManager)->bfmeForwardWideA((int)bridgePos,*(int*)&radius,0,0);
  Object *other;
  while((other=iter.next())!=0) {
   if(other->isKindOf(0x400000)||other->isKindOf(0x1000000)) continue;
   if(other->getHeightAboveTerrain()>g_rva01075350) continue;
   if(other->m_position.z<lowBridgeZ) continue;
   if(!((bool (__cdecl*)(const Coord3D*,const Coord3D*,int))j_000015e1)(&other->m_position,bridgePolygon,4)) continue;
   if(bridgeLayer!=getLayer(other)) continue;
   if(getLayer(other)==bridgeLayer) other->setLayer(LAYER_GROUND);
   other->kill(DAMAGE_UNRESISTABLE,DEATH_NORMAL);
  }
 }
}
