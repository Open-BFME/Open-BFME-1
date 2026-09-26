// ?canDoSpecialPowerAtLocation@ActionManager@@QAE_NPBVObject@@PBUCoord3D@@W4CommandSourceType@@PBVSpecialPowerTemplate@@0I_N@Z
// partial score=0.2804630969609262 date=2026-09-26
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
#include "basetype.h"
// Native reconstruction of RVA000C6930, complete 3447-byte retail extent.
// PARTIAL: control flow and direct-call ABI still require strict gate validation.
// Native dispatcher has 3094 code bytes, 2 alignment bytes, and 351 table bytes.
// Anonymous ABI views are address-qualified; no candidate-only pins were added.
// The original named lift remains intact until this reconstruction byte-matches.
// Identity: native InGameUI::canSelectedObjectsDoSpecialPower and
// Rva003273A0SpecialPowerAction::execute callers, plus the ZH ActionManager twin.
enum CommandSourceType { CMD_FROM_PLAYER=0 };
enum SpecialPowerType { Rva000C6930PowerNone=0 };
enum KindOfType { KINDOF_STRUCTURE=7 };
enum NameKeyType { NAMEKEY_INVALID=0 };
enum PathfindLayerEnum { LAYER_GROUND=0 };
enum ObjectID { INVALID_ID=0 };
enum IterOrderType { ITER_FASTEST=0, ITER_NEAR_TO_FAR=1 };
enum DistanceCalculationType { FROM_CENTER_2D=0 };
enum CellShroudStatus { CELLSHROUD_CLEAR=0, CELLSHROUD_SHROUDED=2 };
class Object;
class SpecialPowerTemplate;
class Module;
class Overridable {
public:
 const Overridable *friend_getFinalOverride() const;
 const Overridable *getFinalOverride() const;
 const Overridable *finalTemplate() const {
  const Overridable *p=m_nextOverride;
  if(p) { if(p->m_nextOverride) return p->m_nextOverride->friend_getFinalOverride(); return p; }
  return this;
 }
 void *m_vtable; const Overridable *m_nextOverride;
};
class SpecialPowerTemplate : public Overridable {
public:
 SpecialPowerType getSpecialPowerType() const { return ((const SpecialPowerTemplate*)finalTemplate())->m_type; }
 unsigned char m_08[12]; SpecialPowerType m_type;
};
class BfmeThingEOG { public: float bfmeGoEOG(); };
class BfmeThingEGF { public: bool bfmeGoEGFa(); };
class NameKeyGenerator { public: NameKeyType nameToKey(const char*); };
extern NameKeyGenerator *TheNameKeyGenerator;
class SpecialPowerModuleInterface {
public:
 virtual void slot00(); virtual void slot04(); virtual float getPercentReady();
 virtual void slot0c(); virtual void slot10(); virtual void slot14(); virtual void slot18();
 virtual void slot1c(); virtual void slot20(); virtual void slot24(); virtual void slot28();
 virtual void slot2c(); virtual void slot30(); virtual void slot34(); virtual void slot38();
 virtual void slot3c(); virtual void slot40(); virtual void slot44(); virtual void slot48();
 virtual void slot4c(); virtual void slot50(); virtual void slot54();
 virtual bool rva000C6930Slot58(const Coord3D*);
};
template<int N> class BitFlags {
public:
 enum BogusInitType { kInit=0 };
 BitFlags(BogusInitType,int);
 BitFlags(BogusInitType,int,int);
 BitFlags(BogusInitType,int,int,int,int);
 unsigned int words[6];
};
typedef BitFlags<192> KindOfMask192;
extern const KindOfMask192 KINDOFMASK_NONE;
class Thing {
public: bool isKindOf(KindOfType) const; bool isAnyKindOf(const BitFlags<116>&) const;
};
class Player { public: unsigned char m_00[0x24]; int m_playerIndex; };
class BfmeSub1CC_EC3 { public: float effectiveMaxSpeed(void*); };
class Rva001BDFF0 { public: int get(); };
class Rva0036CD30Owner { public: float value() const; unsigned char m_00[0x9c]; void *m_9c; };
class Object : public Thing {
public:
 bool hasSpecialPower(SpecialPowerType) const;
 SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate*) const;
 Player *getControllingPlayer() const;
 Module *findModule(NameKeyType) const;
 unsigned char m_00[4]; Overridable *m_template;
 unsigned char m_08[0x30]; Coord3D m_cachedPos;
 unsigned char m_44[0x1c0]; BfmeThingEGF *m_ai;
};
class Pathfinder {
public:
 int getLayer(const Coord3D*);
 bool slowDoesPathExist(Object*,const Coord3D*,const Coord3D*,ObjectID);
 int bfmeCellTypeFiveOrOutside(const Coord3D*,PathfindLayerEnum);
};
class AI { public: unsigned char m_00[12]; Pathfinder *m_pathfinder; };
extern AI *TheAI;
class TerrainLogic {
public:
 virtual void s00();virtual void s04();virtual void s08();virtual void s0c();virtual void s10();
 virtual void s14();virtual void s18();virtual void s1c();virtual void s20();virtual void s24();
 virtual void s28();virtual void s2c();virtual void s30();virtual void s34();virtual void s38();
 virtual void s3c();virtual void s40();virtual void s44();virtual void s48();
 virtual bool isUnderwater(float,float,float*,void**);
 virtual bool rva000C6930Slot50(float,float);
 virtual bool rva000C6930Slot54(float,float);
 PathfindLayerEnum getLayerForDestination(Object*,const Coord3D*);
 bool rva001A62D0(const Coord3D*,float,bool,bool);
};
extern TerrainLogic *TheTerrainLogic;
class PartitionFilter {
public:
 PartitionFilter():m_next(0){}
 virtual ~PartitionFilter(){}
 virtual bool allow(Object*)=0;
 virtual int getPlayerMask();
 PartitionFilter *link(PartitionFilter*);
 PartitionFilter *m_next;
};
class Rva0025ED50RootFilter : public PartitionFilter {
public: Rva0025ED50RootFilter(){} virtual ~Rva0025ED50RootFilter(){} virtual bool allow(Object*);
};
class Rva000C3DD0Filter : public PartitionFilter {
public:
 Rva000C3DD0Filter(const KindOfMask192&,const KindOfMask192&);
 virtual ~Rva000C3DD0Filter(){} virtual bool allow(Object*);
 KindOfMask192 m_yes,m_no;
};
struct Rva0025ED50Entry { Object *object; unsigned int unknown04; };
struct Rva0025ED50ResultData {
 Rva0025ED50Entry *begin,*end,*capacity,*current; int references;
};
struct Rva0025ED50WideResult {
 Rva0025ED50ResultData *value;
 Rva0025ED50WideResult();
 Rva0025ED50WideResult(const Rva0025ED50WideResult&);
 ~Rva0025ED50WideResult();
 Rva0025ED50WideResult& operator=(const Rva0025ED50WideResult&);
 Object *next() {
  Rva0025ED50ResultData *data=value;
  Rva0025ED50Entry *end=data->end;
  Rva0025ED50Entry *current=data->current;
  if(current==end) return 0;
  Object *result=current->object;
  data->current=current+1;
  return result;
 }
 Object *rva000C44D0Next();
};
class PartitionManager {
public:
 Rva0025ED50WideResult iterate(const Coord3D*,float,IterOrderType,PartitionFilter*,bool);
 Object *getClosestObject(const Coord3D*,float,DistanceCalculationType,PartitionFilter*);
 CellShroudStatus getShroudStatusForPlayer(int,const Coord3D*)const;
};
extern PartitionManager *ThePartitionManager;
extern PartitionManager *Rva000C6930TheShroudManager;
class Rva000B6CA0Coord { public: float length()const; float estimate2D()const; };
class ActionManager {
public:
 bool canDoSpecialPowerAtLocation(const Object*,const Coord3D*,CommandSourceType,
 const SpecialPowerTemplate*,const Object*,unsigned int,bool);
};

bool ActionManager::canDoSpecialPowerAtLocation(const Object *obj,const Coord3D *loc,
 CommandSourceType commandSource,const SpecialPowerTemplate *spTemplate,const Object *objectInWay,
 unsigned int commandOptions,bool checkSourceRequirements)
{
 if(!spTemplate) return false;
 if(checkSourceRequirements && !obj->hasSpecialPower(spTemplate->getSpecialPowerType())) return false;
 if(obj && obj->m_ai && obj->m_ai->bfmeGoEGFa()) {
  Coord3D pos; pos.x=obj->m_cachedPos.x; pos.y=obj->m_cachedPos.y; pos.z=obj->m_cachedPos.z+500.0f;
  if(TheAI && TheAI->m_pathfinder->getLayer(&pos)>=17) return false;
 }
 static NameKeyType castleKey=TheNameKeyGenerator->nameToKey("CastleBehavior");
 SpecialPowerModuleInterface *mod=obj->getSpecialPowerModule(spTemplate);
 if(mod) {
  if(checkSourceRequirements) {
   if(mod->getPercentReady()<1.0f) return false;
   if(!mod->rva000C6930Slot58(0)) return false;
  }
  switch(spTemplate->getSpecialPowerType()) {
  case 2:case 17:case 66:case 114:
   if(TheTerrainLogic->isUnderwater(loc->x,loc->y,0,0)) return false;
   if(TheTerrainLogic->rva000C6930Slot50(loc->x,loc->y)) return false;
  }
  switch(spTemplate->getSpecialPowerType()) {
  case 78:case 94:case 97:case 100: {
   float radius=((BfmeThingEOG*)spTemplate)->bfmeGoEOG();
   Rva0025ED50RootFilter root;
   Rva000C3DD0Filter filter(KINDOFMASK_NONE,KindOfMask192(KindOfMask192::kInit,88,30,47,135));
   Rva0025ED50WideResult iter=ThePartitionManager->iterate(loc,radius,ITER_NEAR_TO_FAR,root.link(&filter),false);
   Object *other;
   while((other=iter.next())!=0) {
    KindOfMask192 reject(KindOfMask192::kInit,2,7);
    if(other->isAnyKindOf(reinterpret_cast<const BitFlags<116>&>(reject)) && !other->isKindOf((KindOfType)119)) return false;
    const Overridable *t=other->m_template;
    if(t) t=t->getFinalOverride();
    if(*(const bool*)((const char*)t+0x4b0)) return false;
   }
   iter=ThePartitionManager->iterate(loc,575.0f,ITER_FASTEST,&Rva000C3DD0Filter(KindOfMask192(KindOfMask192::kInit,119),KINDOFMASK_NONE),false);
   while((other=iter.next())!=0) {
    Rva0036CD30Owner *castle=(Rva0036CD30Owner*)other->findModule(castleKey);
    if(castle && castle->m_9c) {
     float radius=castle->value(); Coord3D otherPos=other->m_cachedPos; Coord3D diff=*loc; diff.sub(&otherPos);
     if(((Rva000B6CA0Coord*)&diff)->length()<radius+75.0f) return false;
    }
   }
   break;
  }
  case 66: {
   if(!mod->rva000C6930Slot58(loc)) return false;
   Rva000C3DD0Filter filter(KindOfMask192(KindOfMask192::kInit,7),KINDOFMASK_NONE);
   if(ThePartitionManager->getClosestObject(loc,1.0f,FROM_CENTER_2D,&filter)) return false;
   if(TheTerrainLogic->getLayerForDestination(0,loc)!=1) return false;
   BfmeSub1CC_EC3 *speed=(BfmeSub1CC_EC3*)((Rva001BDFF0*)obj)->get();
   if(speed && speed->effectiveMaxSpeed((void*)obj)==0.0f) return false;
   break;
  } case 114: {
   Rva000C3DD0Filter filter(KindOfMask192(KindOfMask192::kInit,7),KINDOFMASK_NONE);
   if(ThePartitionManager->getClosestObject(loc,1.0f,FROM_CENTER_2D,&filter)) return false;
   if(!TheAI->m_pathfinder->slowDoesPathExist((Object*)obj,&obj->m_cachedPos,loc,INVALID_ID)) return false;
   if(TheAI->m_pathfinder->bfmeCellTypeFiveOrOutside(loc,TheTerrainLogic->getLayerForDestination(0,loc))) return false;
   BfmeSub1CC_EC3 *speed=(BfmeSub1CC_EC3*)((Rva001BDFF0*)obj)->get();
   if(speed && speed->effectiveMaxSpeed((void*)obj)==0.0f) return false;
   break;
  }}
  switch(spTemplate->getSpecialPowerType()) {
  case 85: {
   Object *closest=ThePartitionManager->getClosestObject(loc,200.0f,FROM_CENTER_2D,Rva0025ED50RootFilter().link(&Rva000C3DD0Filter(KindOfMask192(KindOfMask192::kInit,165),KINDOFMASK_NONE)));
   if(!closest) return false;
  }
  case 1:case 2:case 3:case 4:case 8:case 11:case 12:case 13:case 14:case 15:case 16:case 17:case 18:case 20:case 28:case 33:case 34:case 35:case 38:case 43:case 48:case 51:case 64:case 66:case 68:case 81:case 89:case 93:case 99:case 114:
   return Rva000C6930TheShroudManager->getShroudStatusForPlayer(obj->getControllingPlayer()->m_playerIndex,loc)==CELLSHROUD_CLEAR;
  case 78:case 94:case 97:case 100: {
   Coord3D pos; pos.x=loc->x; pos.y=loc->y; pos.z=loc->z;
   int xmin=(int)(pos.x-75.0f),xmax=(int)(pos.x+75.0f),ymax=(int)(pos.y+75.0f),ymin=(int)(pos.y-75.0f);
   for(int y=ymin;y<=ymax;y+=15) for(int x=xmin;x<=xmax;x+=15) {
    if(TheTerrainLogic->rva000C6930Slot54((float)x,(float)y)) return false;
    if(TheTerrainLogic->rva000C6930Slot50((float)x,(float)y)) return false;
    if(TheTerrainLogic->isUnderwater((float)x,(float)y,0,0)) return false;
   }
   return Rva000C6930TheShroudManager->getShroudStatusForPlayer(obj->getControllingPlayer()->m_playerIndex,loc)==CELLSHROUD_CLEAR;
  }
  case 88:case 96: {
   Rva0025ED50WideResult iter=ThePartitionManager->iterate(loc,675.0f,ITER_FASTEST,&Rva000C3DD0Filter(KindOfMask192(KindOfMask192::kInit,119),KINDOFMASK_NONE),false);
   for(Object *other=iter.rva000C44D0Next();other;other=iter.rva000C44D0Next()) {
    Rva0036CD30Owner *castle=(Rva0036CD30Owner*)other->findModule(castleKey);
    if(castle && castle->m_9c) {
     float radius=castle->value(); Coord3D otherPos=other->m_cachedPos; Coord3D diff=*loc; diff.sub(&otherPos);
     if(((Rva000B6CA0Coord*)&diff)->length()<radius+175.0f) return false;
    }
   }
   Coord3D pos; pos.x=loc->x; pos.y=loc->y; pos.z=loc->z;
   int xmin=(int)(pos.x-175.0f),xmax=(int)(pos.x+175.0f),ymin=(int)(pos.y-175.0f),ymax=(int)(pos.y+175.0f);
   for(int y=ymin;y<=ymax;y+=35) for(int x=xmin;x<=xmax;x+=35)
    if(TheTerrainLogic->rva000C6930Slot54((float)x,(float)y)) return false;
   return Rva000C6930TheShroudManager->getShroudStatusForPlayer(obj->getControllingPlayer()->m_playerIndex,loc)!=CELLSHROUD_SHROUDED;
  }
  case 91: {
   Object *closest=ThePartitionManager->getClosestObject(loc,200.0f,FROM_CENTER_2D,&Rva000C3DD0Filter(KindOfMask192(KindOfMask192::kInit,59),KINDOFMASK_NONE));
   if(closest) return false;
   Coord3D pos; pos.x=loc->x; pos.y=loc->y; pos.z=loc->z;
   int xmin=(int)(pos.x-200.0f),xmax=(int)(pos.x+200.0f),ymax=(int)(pos.y+200.0f),ymin=(int)(pos.y-200.0f);
   for(int y=ymin;y<=ymax;y+=40) for(int x=xmin;x<=xmax;x+=40)
    if(TheTerrainLogic->rva000C6930Slot54((float)x,(float)y)) return false;
   return Rva000C6930TheShroudManager->getShroudStatusForPlayer(obj->getControllingPlayer()->m_playerIndex,loc)==CELLSHROUD_CLEAR;
  }
  case 72: {
   if(obj) { Coord3D diff; diff.x=obj->m_cachedPos.x; diff.y=obj->m_cachedPos.y; diff.z=obj->m_cachedPos.z; diff.sub(loc);if(((Rva000B6CA0Coord*)&diff)->estimate2D()>200.0f) return false; }
   Coord3D pos; pos.x=loc->x; pos.y=loc->y; pos.z=loc->z;
   int xmin=(int)(pos.x-125.0f),xmax=(int)(pos.x+125.0f),ymin=(int)(pos.y-125.0f),ymax=(int)(pos.y+125.0f);
   for(int y=ymin;y<=ymax;y+=25) for(int x=xmin;x<=xmax;x+=25)
    if(TheTerrainLogic->rva000C6930Slot54((float)x,(float)y)) return false;
   Object *closest=ThePartitionManager->getClosestObject(loc,125.0f,FROM_CENTER_2D,&Rva000C3DD0Filter(KindOfMask192(KindOfMask192::kInit,59),KINDOFMASK_NONE));
   if(closest) return false;
   return Rva000C6930TheShroudManager->getShroudStatusForPlayer(obj->getControllingPlayer()->m_playerIndex,loc)==CELLSHROUD_CLEAR;
  }
  case 30:case 31:case 53:case 54:case 55:case 61:case 62:case 63:case 67:case 70:case 73:case 75:case 77:case 79:case 80:case 82:case 83:case 84:case 86:case 87:case 90:case 92:case 95:case 98:case 101:case 102:case 107:return true;
  case 74:case 108:return Rva000C6930TheShroudManager->getShroudStatusForPlayer(obj->getControllingPlayer()->m_playerIndex,loc)!=CELLSHROUD_SHROUDED;
  case 115:return false;
  case 39:return TheTerrainLogic->rva001A62D0(loc,5.0f,true,true);
  }
 }
 return false;
}
