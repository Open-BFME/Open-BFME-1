// cl: /DNDEBUG /MD /EHsc
// WorkerAIUpdate::findGoodBuildOrRepairPositionAndTarget, retail RVA 0x002C9C40 (519 bytes).
struct Coord3D {float x,y,z;};
class Overridable {public: virtual ~Overridable(); const Overridable* getFinalOverride() const {if(next)return next->getFinalOverride();return this;} Overridable* next;};
template<class T>class OVERRIDE {const T*p;public:const T*operator*()const {if(!p)return 0;return(T*)p->getFinalOverride();}operator const T*()const{return operator*();}};
class AsciiString {public:char*data;const char*str()const{return data?data+8:"";}};
enum KindOfType {KINDOF_BRIDGE=22};
class ThingTemplate:public Overridable {public:char pad08[0x18];AsciiString name;char pad24[0xa4];unsigned kindOf[3];bool isKindOf(KindOfType i)const{return (kindOf[(unsigned)i>>5]&(1u<<((unsigned)i&31)))!=0;}const AsciiString&getName()const{return name;}};
enum CommandSourceType {CMD_FROM_AI=2}; class AICommandInterface {public:void aiIdle(CommandSourceType);};
class AIUpdateInterface {public:bool isPathAvailable(const Coord3D*)const;};
class Object {public:
 virtual ~Object(); OVERRIDE<ThingTemplate> m_template;char pad08[0x30];Coord3D position;char pad44[0x30];unsigned id;char pad78[0x18c];AIUpdateInterface*ai;
 const ThingTemplate*getTemplate()const{return m_template;} unsigned getID()const{return id;} const Coord3D*getPosition()const{return &position;}
 bool isKindOf(KindOfType i)const{return getTemplate()->isKindOf(i);} void setBuilder(const Object*);
};
class CRCParameterCheck;extern CRCParameterCheck*TheCRCParameterCheck;
extern bool g_bfmeDockingDesyncLog,g_bfmeDockingTraceActive;
extern "C" void bfmeRetailCritterDesyncLog(CRCParameterCheck*,const char*,...);
enum ObjectID {INVALID_ID=0}; class GameLogic {public:Object*findObjectByID(ObjectID);char pad[0x3c];unsigned frame;};extern GameLogic*TheGameLogic;
struct State {void*vtable;int id;};
class StateMachine {public:virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual void v5();virtual void resetToDefaultState();virtual void v7();virtual void setState(int);char pad04[0x18];State*current;int getCurrentStateID()const{return current?current->id:-1;}};
enum DozerTask {DOZER_TASK_BUILD,DOZER_TASK_REPAIR}; struct TaskInfo {unsigned targetObjectID,taskOrderFrame;}; struct DockPoint {bool valid;Coord3D location;};
enum BridgeTowerType {BRIDGE_TOWER_0,BRIDGE_TOWER_1,BRIDGE_TOWER_2,BRIDGE_TOWER_3};
class BridgeBehaviorInterface {public:virtual void slot0();virtual ObjectID getTowerID(BridgeTowerType);}; class BridgeBehavior {public:static BridgeBehaviorInterface*getBridgeBehaviorInterfaceFromObject(Object*);};
class WorkerAIUpdate {protected: bool findGoodBuildOrRepairPosition(const Object*,const Object*,Coord3D&); Object*findGoodBuildOrRepairPositionAndTarget(Object*,Object*,Coord3D&);};
inline float sqr(float x){return x*x;}
Object*WorkerAIUpdate::findGoodBuildOrRepairPositionAndTarget(Object*me,Object*target,Coord3D&positionOut){
 if(g_bfmeDockingTraceActive&&TheCRCParameterCheck)
  bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"  WorkerAIUpdate::findGoodBuildOrRepairPositionAndTarget() BEGIN: Object %s(%d) with target %s(%d)",me->getTemplate()->getName().str(),me->getID(),target?target->getTemplate()->getName().str():"NULL",target?target->getID():0);
 if(target->isKindOf(KINDOF_BRIDGE)){
  if(g_bfmeDockingTraceActive&&TheCRCParameterCheck)bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"  target is a bridge case");
  BridgeBehaviorInterface*bbi=BridgeBehavior::getBridgeBehaviorInterfaceFromObject(target);
  if(bbi){
   if(g_bfmeDockingTraceActive&&TheCRCParameterCheck)bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"  target has a bridge behavior");
   AIUpdateInterface*ai=me->ai;
   float bestDistSqr=1e10f;Object*bestTower=0;
   for(int i=0;i<4;++i){
    Object*tower=TheGameLogic->findObjectByID(bbi->getTowerID((BridgeTowerType)i));
    if(tower){Coord3D tmp;bool found=findGoodBuildOrRepairPosition(me,tower,tmp);
     if(found&&ai->isPathAvailable(&tmp)){
      float thisDistSqr=sqr(me->getPosition()->x-tmp.x)+sqr(me->getPosition()->y-tmp.y);
      if(thisDistSqr<bestDistSqr){positionOut=tmp;bestDistSqr=thisDistSqr;bestTower=tower;}
     }
    }
   }
   return bestTower;
  }
 }
 findGoodBuildOrRepairPosition(me,target,positionOut);return target;
}
