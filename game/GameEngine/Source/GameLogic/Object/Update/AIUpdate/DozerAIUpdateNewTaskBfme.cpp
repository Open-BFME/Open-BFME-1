// cl: /DNDEBUG /MD /EHsc
// DozerAIUpdate::newTask, retail RVA 0x002B8A00 (826 bytes).
// Constructor 0x002B8680 installs DozerAIInterface vtable VA 0x010C6920;
// its slot 12 (+0x30) reaches this body through ILT 0x000072B1, the same slot
// WorkerAIUpdate::newTask (0x002CA130) occupies. The format strings at VA
// 0x010C7128/0x010C70C0/0x010C7050 read "DockingDesync(DOZER) ...".
// The local view below is relative to that secondary interface, like the
// landed WorkerAIUpdateNewTaskBfme.cpp; m_task +0x04 and m_dockPoint +0x98
// match DozerAIUpdate_internalTaskComplete.cpp / DozerAIUpdate_getDockPoint.cpp.
// Body follows the Zero Hour twin DozerAIUpdate::newTask plus BFME's docking
// diagnostics around the position helper (now a thiscall on the primary base:
// retail passes ECX=this-0x340 and the helper returns with ret 0xC).
// Shape: the START/ACTION locations are stored before their valid flags, and
// the end-point offset lives in its own block; without the block MSVC 7.1
// spills every scaled component instead of forwarding x and y through the FPU.
struct Coord3D {
 float x,y,z;
 void normalize();
 void scale(float s){x*=s;y*=s;z*=s;}
 void add(const Coord3D*a){x+=a->x;y+=a->y;z+=a->z;}
};
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
class Object {public:
 virtual ~Object(); OVERRIDE<ThingTemplate> m_template;char pad08[0x30];Coord3D position;char pad44[0x30];unsigned id;
 const ThingTemplate*getTemplate()const{return m_template;}
 const Coord3D*getPosition()const{return &position;}
 unsigned getID()const{return id;}
 void setBuilder(const Object*);
};
class CRCParameterCheck;extern CRCParameterCheck*TheCRCParameterCheck;
extern bool g_bfmeDockingDesyncLog,g_bfmeDockingTraceActive;
extern "C" void bfmeRetailCritterDesyncLog(CRCParameterCheck*,const char*,...);
class GameLogic {public:char pad[0x3c];unsigned frame;unsigned getFrame()const{return frame;}};extern GameLogic*TheGameLogic;
class StateMachine {public:virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual void v5();virtual void resetToDefaultState();};
enum DozerTask {DOZER_TASK_BUILD,DOZER_TASK_REPAIR,DOZER_TASK_FORTIFY,DOZER_NUM_TASKS};
enum {DOZER_DOCK_POINT_START,DOZER_DOCK_POINT_ACTION,DOZER_DOCK_POINT_END,DOZER_NUM_DOCK_POINTS};
struct DozerTaskInfo {unsigned m_targetObjectID,m_taskOrderFrame;};
struct DozerDockPointInfo {bool valid;Coord3D location;};
class DozerAIUpdate {public:
 virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual void v5();virtual bool isTaskPending(DozerTask);virtual void v7();virtual void v8();virtual void v9();virtual void v10();virtual void v11();virtual void newTask(DozerTask,Object*);virtual void cancelTask(DozerTask);
 DozerTaskInfo m_task[DOZER_NUM_TASKS];
 StateMachine *m_dozerMachine;
 char pad20[0x78];
 DozerDockPointInfo m_dockPoint[DOZER_NUM_TASKS][DOZER_NUM_DOCK_POINTS];
 Object*getObject(){return *(Object**)((char*)this-0x338);}
};
// Address-derived view of the 0x002B8890 helper (its ledger row's object-symbol):
// retail calls it through ILT 0x00004C4B as a thiscall on the primary base.
class Rva002B8890DozerAIUpdate {public:Object*findGoodBuildOrRepairPositionAndTarget(Object*,Object*,Coord3D&);};
void DozerAIUpdate::newTask(DozerTask task,Object*target){
 if(target==0)return;
 if(task==DOZER_TASK_BUILD||task==DOZER_TASK_REPAIR){
  if(isTaskPending(task)==true)cancelTask(task);
  Object*me=getObject();
  Coord3D position;
  if(g_bfmeDockingDesyncLog){
   if(TheCRCParameterCheck)bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"DockingDesync(DOZER) BEGIN: Object %s(%d) with target %s(%d) at %g,%g,%g",me->getTemplate()->getName().str(),me->getID(),target->getTemplate()->getName().str(),target->getID(),me->position.x,me->position.y,me->position.z);
   g_bfmeDockingTraceActive=true;
  }
  target=((Rva002B8890DozerAIUpdate*)((char*)this-0x340))->findGoodBuildOrRepairPositionAndTarget(me,target,position);
  if(target==0){
   if(g_bfmeDockingDesyncLog){
    if(TheCRCParameterCheck)bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"DockingDesync(DOZER) END: Object %s(%d) with no target found docking position %g,%g,%g",me->getTemplate()->getName().str(),me->getID(),position.x,position.y,position.z);
    g_bfmeDockingTraceActive=false;
   }
   return;
  }
  if(g_bfmeDockingDesyncLog){
   if(TheCRCParameterCheck)bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"DockingDesync(DOZER) END: Object %s(%d) with target %s(%d) found docking position %g,%g,%g",me->getTemplate()->getName().str(),me->getID(),target->getTemplate()->getName().str(),target->getID(),position.x,position.y,position.z);
   g_bfmeDockingTraceActive=false;
  }
  if(task==DOZER_TASK_BUILD)target->setBuilder(me);
  m_dockPoint[task][DOZER_DOCK_POINT_START].location=position;
  m_dockPoint[task][DOZER_DOCK_POINT_ACTION].location=position;
  m_dockPoint[task][DOZER_DOCK_POINT_START].valid=true;
  m_dockPoint[task][DOZER_DOCK_POINT_ACTION].valid=true;
  {
  Coord3D offset;
  offset.x=position.x-target->getPosition()->x;
  offset.y=position.y-target->getPosition()->y;
  offset.z=0;
  offset.normalize();
  offset.scale(5*10.0f);
  position.add(&offset);
  }
  m_dockPoint[task][DOZER_DOCK_POINT_END].valid=true;
  m_dockPoint[task][DOZER_DOCK_POINT_END].location=position;
 }
 m_task[task].m_targetObjectID=target->getID();
 m_task[task].m_taskOrderFrame=TheGameLogic->getFrame();
 m_dozerMachine->resetToDefaultState();
}
