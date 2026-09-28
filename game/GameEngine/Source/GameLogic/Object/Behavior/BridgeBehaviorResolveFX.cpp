// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include <list>
// BFME RVA 0x001F2AF0 +723. Identity and algorithm: ZH BridgeBehavior
// resolveFX plus the original named lift. Retail initializes four damage
// states, three OCL/FX entries each, then two 0x70-byte audio arrays.
// Witnessed fields: object +8, damage OCL +0x3c, damage FX +0x6c,
// damage audio +0x9c, repair OCL +0x25c, repair FX +0x28c,
// repair audio +0x2bc, resolved byte +0x47c. Object ID is +0x74.
// Getter ILTs 0001dafc / 0002fc39 / 0003fef9 return AsciiString via
// a hidden out pointer; their old opaque ledger names are preserved by
// typed member-call views. setEventName consumes a by-value string.
#include <string.h>
#include "string_base.h"
template<class T> inline bool StringBase<T>::isEmpty() const { return !m_data || !m_data->length; }
template<class T> inline const T *StringBase<T>::str() const { return m_data ? m_data->data : (const T*)""; }
template<> inline int StringBase<char>::compare(const char *s) const {
 int n=(int)strlen(s);
 int len=m_data?m_data->length:0;
 const char *data=m_data?m_data->data:"";
 int c=memcmp(data,s,len<n?len:n);
 if(c) return c;
 return len-n;
}
#include "ascii_string.h"
struct Coord3D { float x,y,z; };
class Matrix3D;
enum ObjectID {};
class Object { char pad00[0x38]; public: Coord3D m_position; char pad44[0x30]; ObjectID m_id; ObjectID getID() const { return m_id; } bool getSingleLogicalBonePosition(const char*,Coord3D*,Matrix3D*) const; };
class Rva000EE6D0StringAccessor { public: AsciiString getString(); };
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
class FXList;
class ObjectCreationList;
class ObjectCreationListStore { public: const ObjectCreationList *findObjectCreationList(const char*) const; };
class FXListStore { public: const FXList *findFXList(const char*) const; };
extern ObjectCreationListStore *TheObjectCreationListStore;
extern FXListStore *TheFXListStore;
enum BodyDamageType { BODY_PRISTINE=0, BODYDAMAGETYPE_COUNT=4 };
class AudioEventRTS { char m_data[0x70]; public: void setEventName(AsciiString); void setObjectID(ObjectID); };
class TerrainRoadType { public:
 AsciiString getDamageToOCLString(BodyDamageType,int);
 AsciiString getDamageToSoundString(BodyDamageType);
 AsciiString getRepairedToSoundString(BodyDamageType);
};
void j_0004a83b();
void j_0001dafc(); void j_0002fc39(); void j_0003fef9();
class BridgeBehavior {
 char pad00[8]; Object *m_object; char pad0c[0x30];
 const ObjectCreationList *m_damageToOCL[4][3];
 const FXList *m_damageToFX[4][3];
 AudioEventRTS m_damageToSound[4];
 const ObjectCreationList *m_repairToOCL[4][3];
 const FXList *m_repairToFX[4][3];
 AudioEventRTS m_repairToSound[4];
 bool m_fxResolved;
protected: void resolveFX();
};
void BridgeBehavior::resolveFX() {
 Object *us=m_object;
 Bridge *bridge=TheTerrainLogic->findBridgeAt(&us->m_position);
 if(!bridge) return;
 AsciiString bridgeTemplateName=bridge->getBridgeTemplateName();
 TerrainRoadType *bridgeTemplate=TheTerrainRoads->findBridge(bridgeTemplateName);
 if(!bridgeTemplate) return;
 AsciiString name;
 union { void (*f)(); AsciiString(TerrainRoadType::*m)(BodyDamageType,int); } damageFX,repairOCL,repairFX;
 damageFX.f=j_0001dafc; repairOCL.f=j_0003fef9; repairFX.f=j_0002fc39;
 for(int bodyState=0;bodyState<4;++bodyState) {
  for(int i=0;i<3;++i) {
   name=bridgeTemplate->getDamageToOCLString((BodyDamageType)bodyState,i);
   m_damageToOCL[bodyState][i]=TheObjectCreationListStore->findObjectCreationList(name.str());
   name=(bridgeTemplate->*damageFX.m)((BodyDamageType)bodyState,i);
   m_damageToFX[bodyState][i]=TheFXListStore->findFXList(name.str());
   name=(bridgeTemplate->*repairOCL.m)((BodyDamageType)bodyState,i);
   m_repairToOCL[bodyState][i]=TheObjectCreationListStore->findObjectCreationList(name.str());
   name=(bridgeTemplate->*repairFX.m)((BodyDamageType)bodyState,i);
   m_repairToFX[bodyState][i]=TheFXListStore->findFXList(name.str());
  }
  name=bridgeTemplate->getDamageToSoundString((BodyDamageType)bodyState);
  m_damageToSound[bodyState].setEventName(name);
  m_damageToSound[bodyState].setObjectID(us->getID());
  name=bridgeTemplate->getRepairedToSoundString((BodyDamageType)bodyState);
  m_repairToSound[bodyState].setEventName(name);
  m_repairToSound[bodyState].setObjectID(us->getID());
 }
 m_fxResolved=true;
}
