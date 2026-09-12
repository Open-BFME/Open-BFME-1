// ?computePath@AIUpdateInterface@@QAE_NPAVPathfindServicesInterface@@PAUCoord3D@@@Z
// partial score=0.56 date=2026-09-12
// cl: /DNDEBUG /MD /EHsc
struct Coord3D { Coord3D(){} Coord3D(const Coord3D& c):x(c.x),y(c.y),z(c.z){} Coord3D&operator=(const Coord3D&c){x=c.x;y=c.y;z=c.z;return *this;} float x,y,z; };
struct Region3D{Coord3D lo,hi; __forceinline bool isInRegionNoZ(const Coord3D*p)const{return p->x>=lo.x&&p->x<=hi.x&&p->y>=lo.y&&p->y<=hi.y;}};
enum PathfindLayerEnum{LAYER_GROUND=1};enum CommandSourceType{CMD_FROM_AI=2};enum UpdateSleepTime{SLEEP5=5};enum KindOfType{NO_COLLIDE=30,BFME108=108,BFME124=124,BFME138=138};
class AsciiString {public: const char*str()const{return data?data+8:"";} char*data;};
class Overridable {public:const Overridable*getFinalOverride()const;char prefix[4];const Overridable*next;};
class ThingTemplate:public Overridable {public:char pad08[0x20-8];AsciiString name;char pad24[0x4b1-0x24];bool moveAllies;};
class Thing{public:
 const ThingTemplate*getTemplate()const{const ThingTemplate*t=templ;if(t&&t->next)t=(const ThingTemplate*)t->next->getFinalOverride();return t;}
 const Coord3D*getPosition()const{return &position;}
 bool isKindOf(KindOfType)const;
 char prefix[4];ThingTemplate*templ;char pad08[0x38-8];Coord3D position;
};
class Object:public Thing{public:
 int getLayer()const;unsigned char getCrushableLevel()const;bool testStatus(int)const;bool test(unsigned)const;
 char pad44[0x74-0x44];int id;char pad78[0x94-0x78];unsigned flags94;
};
class Locomotor{public:bool isUltraAccurate()const{return(flags>>6)&1;}char prefix[0x40];unsigned flags;};
struct LocomotorSet {char prefix[16];unsigned surfaces;char pad14[4];AsciiString name;};
struct PathInfo {float distance;Coord3D position;PathfindLayerEnum layer;int pad14[3];int portal;};
class Path{public:void computePoint(Object*,Locomotor*,PathInfo*,bool);void updateLastNode(const Coord3D*);char prefix[0xd];bool blockedByAlly;};
class PathfindServicesInterface{public:
 virtual Path*findPath(Object*,LocomotorSet&,const Coord3D*,const Coord3D*);
 virtual Path*findClosestPath(Object*,LocomotorSet&,const Coord3D*,const Coord3D*,bool,float,bool);
 virtual void slot08();
 virtual Path*patchPath(Object*,LocomotorSet&,Path*,bool);
};
class Pathfinder{public:
 int isLinePassable(Object*,int,PathfindLayerEnum,const Coord3D*,const Coord3D*,int,int,int);
 bool validMovementPosition(const Coord3D*,PathfindLayerEnum,unsigned,Object*);
 void snapPosition(Object*,Coord3D*);
 bool moveAllies(Object*,Path*,bool);
};
struct TAiData{char prefix[0xb5];bool fieldB5;};
class AI{public:char prefix[12];Pathfinder*finder;char gap[4];TAiData*data;Pathfinder*pathfinder()const{return finder;}};extern AI*TheAI;
class TerrainLogic{public:
 virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0c();virtual void slot10();virtual void slot14();virtual void slot18();virtual void slot1c();virtual void slot20();virtual void slot24();virtual void slot28();virtual void slot2c();
 virtual void getMaximumPathfindExtent(Region3D*);
 PathfindLayerEnum getLayerForDestination(Object*,const Coord3D*);
};extern TerrainLogic*TheTerrainLogic;
struct GameLogic {char prefix[0x3c];unsigned frame;};extern GameLogic*TheBfmeGameLogic;
extern unsigned char g_012F0239;extern void*g_012ED4FC;extern void j_0003a17a();
typedef void(__cdecl*DebugLog)(void*,const char*,...);
#define LOG(s) ((DebugLog)j_0003a17a)(g_012ED4FC,s)
#define TRACE(s) if(g_012F0239&&g_012ED4FC){LOG(s);}
#define DETAIL() if(g_012ED4FC){((DebugLog)j_0003a17a)(g_012ED4FC,"m_path=%s, m_locomotorSet=%s, destination=%g,%g,%g",path?"VALID":"NULL",locomotorSet.name.str(),destination->x,destination->y,destination->z);}
#define NEWDETAIL() if(g_012ED4FC){((DebugLog)j_0003a17a)(g_012ED4FC,"m_path=%s, theNewPath=%s, m_locomotorSet=%s, destination=%g,%g,%g",path?"VALID":"NULL",theNewPath?"VALID":"NULL",locomotorSet.name.str(),destination->x,destination->y,destination->z);}
#define TRACEDETAIL(s) if(g_012F0239&&g_012ED4FC){LOG(s);DETAIL();}
#define TRACENEW(s) if(g_012F0239&&g_012ED4FC){LOG(s);NEWDETAIL();}
struct State{char pad[4];int id;};struct AIStateMachine{char prefix[0x1c];State*fallback;};
class UpdateModule{public:virtual void slot00();protected:UpdateSleepTime getWakeFrame()const;void setWakeFrame(Object*,UpdateSleepTime);};
class AIUpdateInterface:public UpdateModule{public:
 bool computePath(PathfindServicesInterface*,Coord3D*);
 void destroyPath();bool computeQuickPath(const Coord3D*);void setGoalPositionClipped(const Coord3D*,CommandSourceType);void setFinalPosition(const Coord3D*);
virtual void slot004();
virtual void slot008();
virtual void slot00c();
virtual void slot010();
virtual void slot014();
virtual void slot018();
virtual void slot01c();
virtual void slot020();
virtual void slot024();
virtual void slot028();
virtual void slot02c();
virtual void slot030();
virtual void slot034();
virtual void slot038();
virtual void slot03c();
virtual void slot040();
virtual void slot044();
virtual void slot048();
virtual void slot04c();
virtual void slot050();
virtual void slot054();
virtual void slot058();
virtual void slot05c();
virtual void slot060();
virtual void slot064();
virtual void slot068();
virtual void slot06c();
virtual void slot070();
virtual void slot074();
virtual void slot078();
virtual void slot07c();
virtual void slot080();
virtual void slot084();
virtual void slot088();
virtual void slot08c();
virtual void slot090();
virtual void slot094();
virtual void slot098();
virtual void slot09c();
virtual void slot0a0();
virtual void slot0a4();
virtual void slot0a8();
virtual void slot0ac();
virtual void slot0b0();
virtual void slot0b4();
virtual void slot0b8();
virtual void slot0bc();
virtual void slot0c0();
virtual void slot0c4();
virtual void slot0c8();
virtual void slot0cc();
virtual void slot0d0();
virtual void slot0d4();
virtual void slot0d8();
virtual void slot0dc();
virtual void slot0e0();
virtual void slot0e4();
virtual void slot0e8();
virtual void slot0ec();
virtual void slot0f0();
virtual void slot0f4();
virtual void slot0f8();
virtual void slot0fc();
virtual void slot100();
virtual void slot104();
virtual void slot108();
virtual void slot10c();
virtual void slot110();
virtual void slot114();
virtual void slot118();
virtual void slot11c();
virtual void slot120();
virtual void slot124();
virtual void slot128();
virtual void slot12c();
virtual void slot130();
virtual void slot134();
virtual void slot138();
virtual void slot13c();
virtual void slot140();
virtual void slot144();
virtual void slot148();
virtual void slot14c();
virtual void slot150();
virtual void slot154();
virtual void slot158();
virtual void slot15c();
virtual void slot160();
virtual void slot164();
virtual void slot168();
virtual void slot16c();
virtual void slot170();
virtual void slot174();
virtual void slot178();
virtual void slot17c();
virtual void slot180();
virtual void slot184();
virtual void slot188();
virtual void slot18c();
virtual void slot190();
virtual void slot194();
virtual void slot198();
virtual void slot19c();
virtual void slot1a0();
virtual void slot1a4();
virtual void slot1a8();
virtual void slot1ac();
virtual void slot1b0();
virtual void slot1b4();
virtual void slot1b8();
virtual void slot1bc();
virtual void slot1c0();
virtual void slot1c4();
virtual void slot1c8();
virtual void slot1cc();
virtual void slot1d0();
virtual void setLocomotorGoalPositionOnPath();
virtual void slot1d8();
virtual void slot1dc();
virtual void slot1e0();
virtual void slot1e4();
virtual void setLocomotorGoalNone();
virtual bool isDoingGroundMovement()const;

 Object*getObject()const{return object;}
 char pad04[4];Object*object;char pad0c[0x30-12];AIStateMachine*state;
 char pad34[0x140-0x34];Path*path;char pad144[0x160-0x144];unsigned timestamp;
 char pad164[8];int blockedFrames;char pad170[12];unsigned queueFrame;
 char pad180[0x1a8-0x180];LocomotorSet locomotorSet;char pad1c4[8];Locomotor*locomotor;
 char pad1d0[0x320-0x1d0];bool finalGoal;char pad321[4];bool blocked,stuck;char pad327[1];bool canThrough;
 char pad329[5];bool retry;char pad32f[1];bool inUpdate;
};
bool AIUpdateInterface::computePath(PathfindServicesInterface*pathServices,Coord3D*destination)
{
 TRACE("CritterDesync: ComputePath43");
 if(g_012F0239&&g_012ED4FC){
 ((DebugLog)j_0003a17a)(g_012ED4FC,"CritterDesync:  Object %s(%d) called AIUpdateInterface::computePath()",getObject()->getTemplate()->name.str(),getObject()->id);DETAIL();
 }
 if(path){PathInfo info;path->computePoint(getObject(),locomotor,&info,false);if(info.portal!=0x7fffffff){timestamp=TheBfmeGameLogic->frame;blockedFrames=0;stuck=false;TRACEDETAIL("CritterDesync:  return true because of portal.");return true;}}
 if(!stuck){TRACEDETAIL("CritterDesync:  path destroyed.");destroyPath();}
 if((locomotorSet.surfaces&8)&&!isDoingGroundMovement()){
 if(computeQuickPath(destination)){TRACEDETAIL("CritterDesync:  computeQuickPath1 returned TRUE.");return true;}
 else{TRACEDETAIL("CritterDesync:  computeQuickPath1 returned FALSE.");return false;}}
 TRACEDETAIL("CritterDesync:  m_retryPath cleared.");retry=false;
 Region3D extent;TheTerrainLogic->getMaximumPathfindExtent(&extent);
 if(!extent.isInRegionNoZ(destination)){Coord3D pos=*getObject()->getPosition();if(!extent.isInRegionNoZ(&pos)){
 if(computeQuickPath(destination)){TRACEDETAIL("CritterDesync:  computeQuickPath2 returned TRUE.");return true;}
 else{TRACEDETAIL("CritterDesync:  computeQuickPath2 returned FALSE.");return false;}}}
 if(state->fallback&&state->fallback->id==7&&canThrough){bool ok=computeQuickPath(destination);if(ok){canThrough=false;setGoalPositionClipped(destination,CMD_FROM_AI);TRACEDETAIL("CritterDesync:  computeQuickPath3 returned TRUE.");return ok;}}
 Path*theNewPath=0;NEWDETAIL();
 Coord3D originalDestination=*destination;
 unsigned surfaces=locomotorSet.surfaces;
 int layer=getObject()->getLayer();bool specialLayer=layer>=2&&layer<=15;
 if(!finalGoal&&!specialLayer&&TheAI->pathfinder()->isLinePassable(getObject(),surfaces,(PathfindLayerEnum)getObject()->getLayer(),getObject()->getPosition(),&originalDestination,0,1,0)){
 if(computeQuickPath(destination)){TRACENEW("CritterDesync:  computeQuickPath4 returned TRUE.");return true;}
 else{TRACENEW("CritterDesync:  computeQuickPath4 returned FALSE.");return false;}}
 PathfindLayerEnum destinationLayer=TheTerrainLogic->getLayerForDestination(getObject(),destination);
 if(!TheAI->pathfinder()->validMovementPosition(destination,destinationLayer,locomotorSet.surfaces,getObject())){
 theNewPath=0;TRACE("CritterDesync:  theNewPath = NULL;");if(g_012F0239){NEWDETAIL();}
 }else if(stuck){theNewPath=pathServices->patchPath(getObject(),locomotorSet,path,stuck);TRACENEW("CritterDesync:  m_isBlockedAndStuck check.");}
 else{theNewPath=pathServices->findPath(getObject(),locomotorSet,getObject()->getPosition(),destination);TRACENEW("CritterDesync:  m_isBlockedAndStuck failed check.");}
 if(!theNewPath&&!path){theNewPath=pathServices->findClosestPath(getObject(),locomotorSet,getObject()->getPosition(),destination,stuck,0.0f,false);TRACENEW("CritterDesync:  m_retryPath set.");retry=true;}
 if(theNewPath){
 TRACE("CritterDesync:  There is a theNewPath");destroyPath();path=theNewPath;
 if(locomotor&&locomotor->isUltraAccurate()){theNewPath->updateLastNode(&originalDestination);TRACE("CritterDesync:  bblah1");}
 setLocomotorGoalPositionOnPath();
 bool move=path->blockedByAlly&&!getObject()->isKindOf(NO_COLLIDE);
 if(getObject()->isKindOf(BFME108)){TRACE("CritterDesync:  bblah2");if(!TheAI->data->fieldB5){TRACE("CritterDesync:  bblah3");move=false;}}
 if(getObject()->getTemplate()->moveAllies||getObject()->isKindOf(BFME124)){TRACE("CritterDesync:  bblah4");move=true;}
 if(getObject()->isKindOf(BFME138)){TRACE("CritterDesync:  bblah5");move=false;}
 Object*obj=getObject();
 if(!(obj->flags94&0x1000000)&&!obj->testStatus(49)&&!obj->test(124)&&move){TRACE("CritterDesync:  bblah6");TheAI->pathfinder()->moveAllies(getObject(),path,(signed char)getObject()->getCrushableLevel()>=4);}
 }else{
 TRACE("CritterDesync:  There isn't a theNewPath");
 if(path&&stuck){TRACE("CritterDesync:  bblah7");destroyPath();
 if(getWakeFrame()>SLEEP5&&!inUpdate)setWakeFrame(getObject(),SLEEP5);
 queueFrame=TheBfmeGameLogic->frame+5;
 Coord3D goalPos;Object*obj=getObject();goalPos=*obj->getPosition();TheAI->pathfinder()->snapPosition(obj,&goalPos);setFinalPosition(&goalPos);setLocomotorGoalNone();blockedFrames=0;blocked=false;stuck=false;}
 }
 timestamp=TheBfmeGameLogic->frame;blockedFrames=0;stuck=false;
 if(path){TRACE("CritterDesync:  Returning true because m_path");return true;}
 TRACE("CritterDesync:  Returning false because !m_path");return false;
}
