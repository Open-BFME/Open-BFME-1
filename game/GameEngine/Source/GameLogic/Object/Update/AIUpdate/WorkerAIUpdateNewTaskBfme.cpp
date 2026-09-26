// cl: /DNDEBUG /MD /EHsc
// WorkerAIUpdate::newTask, retail RVA 0x002CA130 (791 bytes).
// Constructor 0x002C9ED0 installs DozerAIInterface vtable VA 0x010C9DE8
// at +0x340. Its slot 12 reaches this body through ILT 0x0002ECDF.
// The local view below is relative to that secondary interface.
// BFME retains docking diagnostics around the position-selection helper.
// Preserve OVERRIDE and individual getTemplate/getName/getID accessors:
// combining the name lookup changes register allocation across logging calls.
struct Coord3D {float x,y,z;};
class Overridable {
public:
 virtual ~Overridable();
 const Overridable* getFinalOverride() const {
  if(next) return next->getFinalOverride();
  return this;
 }
 Overridable* next;
};
template<class T>class OVERRIDE {const T*p;public:const T*operator*()const {if(!p)return 0;return(T*)p->getFinalOverride();}operator const T*()const{return operator*();}};
class AsciiString {public:char*data;const char*str()const{return data?data+8:"";}};
class ThingTemplate:public Overridable {public:char pad08[0x18];AsciiString name;const AsciiString&getName()const{return name;}};
enum CommandSourceType {CMD_FROM_AI=2};
class AICommandInterface {public:void aiIdle(CommandSourceType);};
class AIUpdateInterface {public:char pad[0x20];AICommandInterface command;};
class Object {public:
 virtual ~Object(); OVERRIDE<ThingTemplate> m_template;char pad08[0x30];Coord3D position;char pad44[0x30];unsigned id;char pad78[0x18c];AIUpdateInterface*ai;
 const ThingTemplate*getTemplate()const{return m_template;}
 unsigned getID()const{return id;}
 void setBuilder(const Object*);
};
class CRCParameterCheck;extern CRCParameterCheck*TheCRCParameterCheck;
extern bool g_bfmeDockingDesyncLog,g_bfmeDockingTraceActive;
extern "C" void bfmeRetailCritterDesyncLog(CRCParameterCheck*,const char*,...);
class GameLogic {public:char pad[0x3c];unsigned frame;};extern GameLogic*TheGameLogic;
struct State {void*vtable;int id;};
class StateMachine {public:virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual void v5();virtual void resetToDefaultState();virtual void v7();virtual void setState(int);char pad04[0x18];State*current;int getCurrentStateID()const{return current?current->id:-1;}};
enum DozerTask {DOZER_TASK_BUILD,DOZER_TASK_REPAIR};
struct TaskInfo {unsigned targetObjectID,taskOrderFrame;};
struct DockPoint {bool valid;Coord3D location;};
class WorkerAIUpdate {public:
 virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual void v5();virtual bool isTaskPending(DozerTask);virtual void v7();virtual void v8();virtual void v9();virtual void v10();virtual void v11();virtual void newTask(DozerTask,Object*);virtual void cancelTask(DozerTask);
 char pad04[8];
 TaskInfo m_task[2];
 char pad1c[0xc];
 DockPoint m_dockPoint[2][3];
 char pad88[0x38];
 unsigned m_preferredDock, fieldC4, fieldC8, fieldCC;
 bool fieldD0;
 char padD1[0xb];
 StateMachine *m_workerMachine, *m_dozerMachine;
 Object*getObject(){return *(Object**)((char*)this-0x338);}
protected:Object*findGoodBuildOrRepairPositionAndTarget(Object*,Object*,Coord3D&);
};
void WorkerAIUpdate::newTask(DozerTask task,Object*target){
 if(!target)return;
 // BFME clears the preferred supply dock and its additional selection state.
 m_preferredDock=0;
 fieldC4=0;
 fieldC8=0;
 fieldCC=0;
 fieldD0=false;
 if(task==DOZER_TASK_BUILD||task==DOZER_TASK_REPAIR){
  if(isTaskPending(task)==true)cancelTask(task);
  Object*me=getObject();Coord3D position;
  if(g_bfmeDockingDesyncLog){
   if(TheCRCParameterCheck)bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"DockingDesync(WORKER) BEGIN: Object %s(%d) with target %s(%d) at %g,%g,%g",me->getTemplate()->getName().str(),me->getID(),target->getTemplate()->getName().str(),target->getID(),me->position.x,me->position.y,me->position.z);
   g_bfmeDockingTraceActive=true;
  }
  target=((WorkerAIUpdate*)((char*)this-0x340))->findGoodBuildOrRepairPositionAndTarget(me,target,position);
  if(!target){
   if(g_bfmeDockingDesyncLog){
    if(TheCRCParameterCheck)bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"DockingDesync(WORKER) END: Object %s(%d) with no target found docking position %g,%g,%g",me->getTemplate()->getName().str(),me->getID(),position.x,position.y,position.z);
    g_bfmeDockingTraceActive=false;
   }
   return;
  }
  if(g_bfmeDockingDesyncLog){
   if(TheCRCParameterCheck)bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"DockingDesync(WORKER) END: Object %s(%d) with target %s(%d) found docking position %g,%g,%g",me->getTemplate()->getName().str(),me->getID(),target->getTemplate()->getName().str(),target->getID(),position.x,position.y,position.z);
   g_bfmeDockingTraceActive=false;
  }
  if(task==DOZER_TASK_BUILD)target->setBuilder(me);
  m_dockPoint[task][0].valid=true;m_dockPoint[task][0].location=position;
  m_dockPoint[task][1].valid=true;m_dockPoint[task][1].location=position;
  m_dockPoint[task][2].valid=true;m_dockPoint[task][2].location=position;
 }
 m_task[task].targetObjectID=target->getID();m_task[task].taskOrderFrame=TheGameLogic->frame;
 m_dozerMachine->resetToDefaultState();
 if(m_workerMachine->getCurrentStateID()==1){
  if(getObject()->ai) getObject()->ai->command.aiIdle(CMD_FROM_AI);
  m_workerMachine->setState(0);
 }
}
