// ?method@Rva0027C250@@QAEHXZ
// partial score=0.6092 date=2026-10-09
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Include/Lib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/GameLogic/Object
#include <math.h>
#include "Coord3D.h"
#include "matrix3d.h"
struct Rva0027C250CoordCopy : Coord3D {
 Rva0027C250CoordCopy() {}
 void set(float ax,float ay,float az) { x=ax; y=ay; z=az; }
 void scale(float value) { x*=value; y*=value; z*=value; }
 void add(const Coord3D *value) { x+=value->x; y+=value->y; z+=value->z; }
 void set(const Coord3D *value) { x=value->x; y=value->y; z=value->z; }
};
typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };
enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_GROUND = 1 };
enum KindOfType { KINDOF_FIRST = 0 };
enum CommandSourceType { CMD_FROM_AI = 2 };
#define BFME_HAVE_COORD3D
#define THING_TU_MEMBERS \
 void setPositionZ(Real); \
 void setOrientation(Real); \
 void rva00132200(const Matrix3D *); \
 Real bfmeRelativeAngleTo(const Coord3D *) const; \
 Bool isKindOf(KindOfType) const;
class Rva0027C250ContainView;
class Rva0027C250;
#define OBJECT_TU_MEMBERS void notifyModelConditionChanged(); \
 Rva0027C250ContainView *rva0027c250Contain() const { return (Rva0027C250ContainView *)m_contain; } \
 Rva0027C250 *rva0027c250AI() const { return (Rva0027C250 *)m_ai; }
#include "object.h"
#undef THING_TU_MEMBERS
#undef OBJECT_TU_MEMBERS
class AICommandInterface { public: void aiIdle(CommandSourceType); };
class AIUpdateInterface { public: void rva00273000(Object *, UpdateSleepTime *); };
class Locomotor { public: Real getMaxTurnRate(Object *) const; };
class BfmeSub1CC_EC3 { public: Real effectiveMaxSpeed(void *); void queryClamp(Real,void *); };
class BfmeHostYL { public: Real bfmeRateYL(Object *); };
class Rva001B3FE0 { public: Bool test() const; };
class Gen_001BEC20 { public: int bfmeScale() const; };
class Rva001BEC40DwordSlot { public: void set(int); };
class StateMachine { public: Object *getGoalObject(); };
class Pathfinder { public:
 Bool validMovementPosition(const Coord3D *,PathfindLayerEnum,UnsignedInt,Object *);
 unsigned char rva003e7b90(Object *,const Coord3D *,const Coord3D *,const Coord3D *);
 void Rva003E4190(Object *);
};
class TerrainLogic { public: PathfindLayerEnum getLayerForDestination(Object *,const Coord3D *); };
extern void *TheTerrainLogic;
extern void *TheWritableGlobalData;
extern void *TheAI;
extern Real stdAngleDiff(Real,Real);
class Rva0027C250Route {};
extern void j_0000faa6();
extern void j_0002bd82();
extern void j_00003922();
extern void j_00008a9e();
extern void j_0001e6fa();
extern void j_0000ca68();
extern void j_00044774();
#define CALL_ROUTE(RESULT,RECEIVER,THUNK,PARAMS,ARGS) \
 (((Rva0027C250Route *)(RECEIVER))->*route_##THUNK.member)ARGS
#define ROUTE(RESULT,THUNK,PARAMS) \
 typedef RESULT (Rva0027C250Route::*Call_##THUNK)PARAMS; \
 union { void (*address)(); Call_##THUNK member; } route_##THUNK = {j_##THUNK}
struct Rva0027C250PathPoint {
 Real m_real00;
 Coord3D m_coord04;
 Real m_real10[3];
 PathfindLayerEnum m_layer;
 int m_int20;
};
struct Rva0027C250PathNode { char m_pad000[0xc]; Coord3D m_position; };
struct Rva0027C250PathView { char m_pad000[8]; Rva0027C250PathNode *m_last; };
class Rva0027C250HordeView {
public:
 virtual void slot000() = 0;
 virtual void slot001() = 0;
 virtual void slot002() = 0;
 virtual void slot003() = 0;
 virtual void slot004() = 0;
 virtual void slot005() = 0;
 virtual void slot006() = 0;
 virtual void slot007() = 0;
 virtual void slot008() = 0;
 virtual void slot009() = 0;
 virtual void slot010() = 0;
 virtual void slot011() = 0;
 virtual void slot012() = 0;
 virtual void slot013() = 0;
 virtual void slot014() = 0;
 virtual void slot015() = 0;
 virtual void slot016() = 0;
 virtual void slot017() = 0;
 virtual void slot018() = 0;
 virtual void slot019() = 0;
 virtual void slot020() = 0;
 virtual void slot021() = 0;
 virtual void slot022() = 0;
 virtual void slot023() = 0;
 virtual void slot024() = 0;
 virtual void slot025() = 0;
 virtual void slot026() = 0;
 virtual void slot027() = 0;
 virtual void slot028() = 0;
 virtual void slot029() = 0;
 virtual void slot030() = 0;
 virtual void slot031() = 0;
 virtual void slot032() = 0;
 virtual void slot033() = 0;
 virtual void slot034() = 0;
 virtual void slot035() = 0;
 virtual void slot036() = 0;
 virtual void slot037() = 0;
 virtual void slot038() = 0;
 virtual void slot039() = 0;
 virtual void slot040() = 0;
 virtual void slot041() = 0;
 virtual void slot042() = 0;
 virtual void slot043() = 0;
 virtual void slot044() = 0;
 virtual void slot045() = 0;
 virtual void slot046() = 0;
 virtual void slot047() = 0;
 virtual void slot048() = 0;
 virtual void slot049() = 0;
 virtual void slot050() = 0;
 virtual void slot051() = 0;
 virtual void slot052() = 0;
 virtual void slot053() = 0;
 virtual void slot054() = 0;
 virtual void slot055() = 0;
 virtual void slot056() = 0;
 virtual void slot057() = 0;
 virtual void slot058() = 0;
 virtual void slot059() = 0;
 virtual void slot060() = 0;
 virtual void slot061() = 0;
 virtual void slot062() = 0;
 virtual void slot063() = 0;
 virtual void slot064() = 0;
 virtual void slot065() = 0;
 virtual void slot066() = 0;
 virtual void slot067() = 0;
 virtual void slot068() = 0;
 virtual void slot069() = 0;
 virtual void slot070() = 0;
 virtual void slot071() = 0;
 virtual void slot072() = 0;
 virtual void slot073() = 0;
 virtual void slot074() = 0;
 virtual void slot075() = 0;
 virtual void slot076() = 0;
 virtual void slot077() = 0;
 virtual void slot078() = 0;
 virtual void slot079() = 0;
 virtual void slot080() = 0;
 virtual void slot081() = 0;
 virtual void slot082() = 0;
 virtual void slot083() = 0;
 virtual void slot084() = 0;
 virtual void slot085() = 0;
 virtual void slot086() = 0;
 virtual void slot087() = 0;
 virtual void slot088() = 0;
 virtual void slot089() = 0;
 virtual void slot090() = 0;
 virtual void slot091() = 0;
 virtual void slot092() = 0;
 virtual Bool slot174() = 0;
};
class Rva0027C250ContainView {
public:
 virtual void slot000() = 0;
 virtual void slot001() = 0;
 virtual void slot002() = 0;
 virtual void slot003() = 0;
 virtual void slot004() = 0;
 virtual void slot005() = 0;
 virtual void slot006() = 0;
 virtual void slot007() = 0;
 virtual void slot008() = 0;
 virtual void slot009() = 0;
 virtual void slot010() = 0;
 virtual void slot011() = 0;
 virtual void slot012() = 0;
 virtual void slot013() = 0;
 virtual void slot014() = 0;
 virtual void slot015() = 0;
 virtual void slot016() = 0;
 virtual void slot017() = 0;
 virtual void slot018() = 0;
 virtual void slot019() = 0;
 virtual void slot020() = 0;
 virtual void slot021() = 0;
 virtual void slot022() = 0;
 virtual void slot023() = 0;
 virtual void slot024() = 0;
 virtual void slot025() = 0;
 virtual Rva0027C250HordeView *slot68() = 0;
};
class Rva0027C250;
struct Rva0027C250PhysicsView { char m_pad000[0x5c]; Bool m_byte5c; };
typedef Object Rva0027C250ObjectView;
static __forceinline void resetFlag(Object *obj,int bit) {
 UnsignedInt mask=1u<<(bit&31);
 if (obj->m_modelConditionFlags[bit>>5]&mask) {
  obj->m_modelConditionFlags[bit>>5]&=~mask;
  obj->notifyModelConditionChanged();
 }
}
static __forceinline void setFlag(Object *obj,int bit) {
 UnsignedInt mask=1u<<(bit&31);
 if (!(obj->m_modelConditionFlags[bit>>5]&mask)) {
  obj->m_modelConditionFlags[bit>>5]|=mask;
  obj->notifyModelConditionChanged();
 }
}
static __forceinline int layer(const Object *obj) { return ((Gen_001BEC20 *)obj)->bfmeScale(); }
class Rva0027C250TerrainView {
public:
 virtual void slot0() = 0;
 virtual void slot1() = 0;
 virtual void slot2() = 0;
 virtual void slot3() = 0;
 virtual void slot4() = 0;
 virtual void slot5() = 0;
 virtual void slot6() = 0;
 virtual Real slot1c(Real,Real,PathfindLayerEnum,Coord3D *,Bool) const = 0;
};
class Rva0027C250 {
public:
 virtual void slot000() = 0;
 virtual void slot004() = 0;
 virtual void slot008() = 0;
 virtual void slot00c() = 0;
 virtual void slot010() = 0;
 virtual void slot014() = 0;
 virtual void slot018() = 0;
 virtual void slot01c() = 0;
 virtual void slot020() = 0;
 virtual void slot024() = 0;
 virtual void slot028() = 0;
 virtual void slot02c() = 0;
 virtual void slot030() = 0;
 virtual void slot034() = 0;
 virtual void slot038() = 0;
 virtual void slot03c() = 0;
 virtual void slot040() = 0;
 virtual void slot044() = 0;
 virtual void slot048() = 0;
 virtual void slot04c() = 0;
 virtual void slot050() = 0;
 virtual void slot054() = 0;
 virtual void slot058() = 0;
 virtual void slot05c() = 0;
 virtual void slot060() = 0;
 virtual void slot064() = 0;
 virtual void slot068() = 0;
 virtual void slot06c() = 0;
 virtual void slot070() = 0;
 virtual void slot074() = 0;
 virtual void slot078() = 0;
 virtual void slot07c() = 0;
 virtual void slot080() = 0;
 virtual void slot084() = 0;
 virtual void slot088() = 0;
 virtual void slot08c() = 0;
 virtual void slot090() = 0;
 virtual void slot094() = 0;
 virtual void slot098() = 0;
 virtual void slot09c() = 0;
 virtual void slot0a0() = 0;
 virtual void slot0a4() = 0;
 virtual void slot0a8() = 0;
 virtual void slot0ac() = 0;
 virtual void slot0b0() = 0;
 virtual void slot0b4() = 0;
 virtual void slot0b8() = 0;
 virtual void slot0bc() = 0;
 virtual void slot0c0() = 0;
 virtual void slot0c4() = 0;
 virtual void slot0c8() = 0;
 virtual void slot0cc() = 0;
 virtual void slot0d0() = 0;
 virtual void slot0d4() = 0;
 virtual void slot0d8() = 0;
 virtual void slot0dc() = 0;
 virtual void slot0e0() = 0;
 virtual void slot0e4() = 0;
 virtual void slot0e8() = 0;
 virtual void slot0ec() = 0;
 virtual void slot0f0() = 0;
 virtual void slot0f4() = 0;
 virtual void slot0f8() = 0;
 virtual void slot0fc() = 0;
 virtual void slot100() = 0;
 virtual void slot104() = 0;
 virtual void slot108() = 0;
 virtual void slot10c() = 0;
 virtual void slot110() = 0;
 virtual void slot114() = 0;
 virtual void slot118() = 0;
 virtual void slot11c() = 0;
 virtual void slot120() = 0;
 virtual void slot124() = 0;
 virtual void slot128() = 0;
 virtual void slot12c() = 0;
 virtual void slot130() = 0;
 virtual void slot134() = 0;
 virtual void slot138() = 0;
 virtual void slot13c() = 0;
 virtual void slot140() = 0;
 virtual void slot144() = 0;
 virtual void slot148() = 0;
 virtual void slot14c() = 0;
 virtual void slot150() = 0;
 virtual void slot154() = 0;
 virtual void slot158() = 0;
 virtual void slot15c() = 0;
 virtual void slot160() = 0;
 virtual void slot164() = 0;
 virtual void slot168() = 0;
 virtual void slot16c() = 0;
 virtual void slot170() = 0;
 virtual void slot174() = 0;
 virtual void slot178() = 0;
 virtual void slot17c() = 0;
 virtual Bool slot180() = 0;
 virtual Bool slot184() = 0;
 virtual void slot188() = 0;
 virtual Bool slot18c() = 0;
 virtual void slot190() = 0;
 virtual void slot194() = 0;
 virtual void slot198() = 0;
 virtual void slot19c() = 0;
 virtual void slot1a0() = 0;
 virtual void slot1a4() = 0;
 virtual void slot1a8() = 0;
 virtual void slot1ac() = 0;
 virtual void slot1b0() = 0;
 virtual void slot1b4() = 0;
 virtual void slot1b8() = 0;
 virtual void slot1bc() = 0;
 virtual void slot1c0() = 0;
 virtual void slot1c4() = 0;
 virtual void slot1c8() = 0;
 virtual void slot1cc() = 0;
 virtual void slot1d0() = 0;
 virtual void slot1d4() = 0;
 virtual void slot1d8() = 0;
 virtual void slot1dc() = 0;
 virtual void slot1e0() = 0;
 virtual void slot1e4() = 0;
 virtual void slot1e8() = 0;
 virtual void slot1ec() = 0;
 virtual void slot1f0() = 0;
 virtual void slot1f4() = 0;
 virtual void slot1f8() = 0;
 virtual void slot1fc() = 0;
 virtual void slot200() = 0;
 virtual void slot204() = 0;
 virtual void slot208() = 0;
 virtual void slot20c() = 0;
 virtual void slot210() = 0;
 virtual void slot214() = 0;
 int method();
 char m_pad004[4];
 Rva0027C250ObjectView *m_object;
 char m_pad00c[0x30-0xc];
 void *m_stateMachine;
 char m_pad034[0x140-0x34];
 Rva0027C250PathView *m_path;
 char m_pad144[0x168-0x144];
 Real m_pathExtraDistance;
 char m_pad16c[0x1b8-0x16c];
 UnsignedInt m_validLocomotorSurfaces;
 char m_pad1bc[0x1cc-0x1bc];
 void *m_curLocomotor;
 char m_pad1d0[8];
 int m_locomotorGoalType;
 Coord3D m_locomotorGoalData;
};
class Rva0027C250MachineView {
public:
 virtual void slot00() = 0;
 virtual void slot04() = 0;
 virtual void slot08() = 0;
 virtual void slot0c() = 0;
 virtual void slot10() = 0;
};
static __forceinline Pathfinder *pathfinder() { return *(Pathfinder **)((char *)TheAI+0xc); }
static __forceinline Thing *thing(Rva0027C250ObjectView *obj) { return (Thing *)obj; }
static __forceinline Real terrainHeight(Rva0027C250ObjectView *obj,const Coord3D &pos) {
 return ((Rva0027C250TerrainView *)TheTerrainLogic)->slot1c(pos.x,pos.y,(PathfindLayerEnum)layer(obj),0,true);
}
static __forceinline void copyCoord(Coord3D &out,const Coord3D &in) { out.x=in.x; out.y=in.y; out.z=in.z; }
typedef char Rva0027C250CoordCopy_size[(sizeof(Rva0027C250CoordCopy)==12)?1:-1];
typedef char Rva0027C250PathPoint_size[(sizeof(Rva0027C250PathPoint)==36)?1:-1];
typedef char Rva0027C250PathPoint_layer[(offsetof(Rva0027C250PathPoint,m_layer)==0x1c)?1:-1];
typedef char Rva0027C250PathPoint_int20[(offsetof(Rva0027C250PathPoint,m_int20)==0x20)?1:-1];
typedef char Rva0027C250_object_offset[(offsetof(Rva0027C250,m_object)==8)?1:-1];
typedef char Rva0027C250_state_offset[(offsetof(Rva0027C250,m_stateMachine)==0x30)?1:-1];
typedef char Rva0027C250_path_offset[(offsetof(Rva0027C250,m_path)==0x140)?1:-1];
typedef char Rva0027C250_extra_offset[(offsetof(Rva0027C250,m_pathExtraDistance)==0x168)?1:-1];
typedef char Rva0027C250_surfaces_offset[(offsetof(Rva0027C250,m_validLocomotorSurfaces)==0x1b8)?1:-1];
typedef char Rva0027C250_locomotor_offset[(offsetof(Rva0027C250,m_curLocomotor)==0x1cc)?1:-1];
typedef char Rva0027C250_goal_type_offset[(offsetof(Rva0027C250,m_locomotorGoalType)==0x1d8)?1:-1];
typedef char Rva0027C250_goal_data_offset[(offsetof(Rva0027C250,m_locomotorGoalData)==0x1dc)?1:-1];
// ?method@Rva0027C250@@QAEHXZ
int Rva0027C250::method() {
 ROUTE(void *,0000faa6,(Bool));
 ROUTE(void,0002bd82,());
 ROUTE(void,00003922,(Object *,const Coord3D &,Real,Real,Bool *));
 ROUTE(void,00008a9e,(Object *,void *,Rva0027C250PathPoint *,Bool));
 ROUTE(Rva0027C250PathView *,0001e6fa,(Object *,const Coord3D *));
 ROUTE(void,0000ca68,());
 ROUTE(Bool,00044774,());
 Rva0027C250ObjectView *obj=m_object;
 resetFlag(obj,102); resetFlag(obj,125); resetFlag(obj,126); resetFlag(obj,129); resetFlag(obj,130);
 if (slot18c() && !obj->m_containedBy && !CALL_ROUTE(void *,obj,0000faa6,(Bool),(false))) {
  ((AICommandInterface *)((char *)this+0x20))->aiIdle(CMD_FROM_AI);
  return 1;
 }
 UpdateSleepTime sleep;
 ((AIUpdateInterface *)this)->rva00273000((Object *)obj,&sleep);
 if (!m_locomotorGoalType) return 5;
 if (obj->m_privateStatus & 1) {
  resetFlag(obj,146);
  Rva0027C250CoordCopy pos; pos.set(&obj->m_cachedPos);
  Real height=terrainHeight(obj,pos);
  if (height<pos.z) {
   pos.z += *(Real *)((char *)TheWritableGlobalData+0x1ac)*5.0f;
   if (pos.z<height) pos.z=height;
   thing(obj)->setPositionZ(pos.z);
   return 1;
  }
  return 5;
 }
 if (obj->m_physics && ((Rva0027C250PhysicsView *)obj->m_physics)->m_byte5c) { resetFlag(obj,146); return 5; }
 if (slot184()) ((Rva0027C250MachineView *)m_stateMachine)->slot10();
 resetFlag(obj,146);
 Rva0027C250ObjectView *container=obj->m_containedBy;
 if (m_locomotorGoalType!=2 && m_locomotorGoalType!=4) {
 if (m_locomotorGoalType==3) {
  Real currentAngle=obj->m_cachedAngle;
  Real diff=stdAngleDiff(currentAngle,m_locomotorGoalData.x);
  if (diff>-0.00000011920928955078125f && diff<0.00000011920928955078125f) {
   resetFlag(obj,60); resetFlag(obj,126); resetFlag(obj,125);
   m_locomotorGoalType=0;
   return 1;
  }
  setFlag(obj,60);
  if (m_curLocomotor) {
   Real rate=((Locomotor *)m_curLocomotor)->getMaxTurnRate((Object *)obj);
   if (diff>0.5f*rate) setFlag(obj,126);
   else if (diff<-0.5f*rate) setFlag(obj,125);
  }
  thing(obj)->setOrientation(m_locomotorGoalData.x);
  return 1;
 }
 return 5;
 }
 Real speed=99999.0f;
 if (container && container->m_contain && container->rva0027c250Contain()->slot68() && container->rva0027c250Contain()->slot68()->slot174()) setFlag(obj,146);
 if (m_curLocomotor) {
  if (obj->m_modelConditionFlags[4]&0x40000) speed=((BfmeHostYL *)m_curLocomotor)->bfmeRateYL((Object *)obj);
  else speed=((BfmeSub1CC_EC3 *)m_curLocomotor)->effectiveMaxSpeed(obj);
 }
 Rva0027C250CoordCopy pos; pos.set(&obj->m_cachedPos);
 Coord3D oldPos=pos;
 if (m_locomotorGoalType!=4 || !m_path) {
  Rva0027C250CoordCopy delta;
  delta.set(m_locomotorGoalData.x-pos.x,m_locomotorGoalData.y-pos.y,0);
  Real dist=(Real)sqrt(delta.x*delta.x+delta.y*delta.y);
  if (4.0f*speed<dist && container && container->m_ai && container->rva0027c250AI()->slot184() && CALL_ROUTE(Bool,container->m_ai,00044774,(),())) speed*=1.5f;
  if (dist>speed) {
   CALL_ROUTE(void,&delta,0002bd82,(),());
   delta.scale(speed);
   pos.add(&delta);
   setFlag(obj,60);
  } else copyCoord(pos,m_locomotorGoalData);
  if (pathfinder()->validMovementPosition(&obj->m_cachedPos,(PathfindLayerEnum)layer(obj),m_validLocomotorSurfaces,(Object *)obj) && !pathfinder()->rva003e7b90((Object *)obj,&obj->m_cachedPos,&pos,&m_locomotorGoalData)) {
   pathfinder()->Rva003E4190((Object *)obj);
   m_path=CALL_ROUTE(Rva0027C250PathView *,pathfinder(),0001e6fa,(Object *,const Coord3D *),((Object *)obj,&m_locomotorGoalData));
   if (!m_path) copyCoord(pos,m_locomotorGoalData);
  }
 }
 if (m_locomotorGoalType==4 && m_path) {
  Rva0027C250PathPoint point;
  CALL_ROUTE(void,m_path,00008a9e,(Object *,void *,Rva0027C250PathPoint *,Bool),((Object *)obj,m_curLocomotor,&point,false));
  if (((Rva001B3FE0 *)m_path)->test()) {
   m_locomotorGoalType=1; slot214(); m_locomotorGoalType=4;
   ((Rva001BEC40DwordSlot *)obj)->set((int)((TerrainLogic *)TheTerrainLogic)->getLayerForDestination((Object *)obj,&m_path->m_last->m_position));
  } else {
   pathfinder()->Rva003E4190((Object *)obj);
   Bool blocked;
   CALL_ROUTE(void,m_curLocomotor,00003922,(Object *,const Coord3D &,Real,Real,Bool *),((Object *)obj,point.m_coord04,point.m_real00+m_pathExtraDistance,speed*1.5f,&blocked));
  }
  setFlag(obj,60);
  if (point.m_real00<5.0f) {
   if (m_path) {
    Rva0027C250PathView *old=m_path;
    CALL_ROUTE(void,old,0000ca68,(),());
    ::operator delete(old);
   }
   m_path=0;
   return 1;
  }
 } else {
  Matrix3D matrix(true);
  Real angle=obj->m_cachedAngle+thing(obj)->bfmeRelativeAngleTo(&m_locomotorGoalData);
  if (thing(obj)->isKindOf((KindOfType)9)) {
   Real relative=thing(obj)->bfmeRelativeAngleTo(&m_locomotorGoalData);
   Real dx=obj->m_cachedPos.x-m_locomotorGoalData.x;
   Real dy=obj->m_cachedPos.y-m_locomotorGoalData.y;
   Real factor=(Real)sqrt(dx*dx+dy*dy)*0.05f;
   if (factor<1.0f) angle=obj->m_cachedAngle+factor*relative;
  }
  if (obj->m_modelConditionFlags[4]&0x40000) {
   Object *goal=((StateMachine *)((Rva0027C250 *)obj->m_containedBy->m_ai)->m_stateMachine)->getGoalObject();
   if (goal) angle=obj->m_cachedAngle+thing(obj)->bfmeRelativeAngleTo(&((Rva0027C250ObjectView *)goal)->m_cachedPos);
   else angle+=3.1415927410125732421875f;
  }
  matrix.Rotate_Z(angle);
  ((Rva001BEC40DwordSlot *)obj)->set((int)((TerrainLogic *)TheTerrainLogic)->getLayerForDestination((Object *)obj,&pos));
  if ((m_locomotorGoalType!=4 || !m_path) && pathfinder()->validMovementPosition(&pos,(PathfindLayerEnum)layer(obj),m_validLocomotorSurfaces,(Object *)m_object)) {
   Real height=terrainHeight(obj,pos);
   if (pos.z<height) pos.z=height;
   else if (layer(obj)==16 && pos.z-height<20.0f) {
    Real adjusted=pos.z-0.066666670143604278564453125f;
    pos.z=adjusted<height ? height:adjusted;
   }
   if (layer(obj)==1 && container && layer(container)==1) pos.z=height;
  }
  matrix.Set_Translation(Vector3(pos.x,pos.y,pos.z));
  thing(obj)->rva00132200(&matrix);
  Real dx=pos.x-oldPos.x,dy=pos.y-oldPos.y,dz=pos.z-oldPos.z;
  Real distance=(Real)sqrt(dx*dx+dy*dy+dz*dz);
  if (distance>speed) distance=speed;
  ((BfmeSub1CC_EC3 *)m_curLocomotor)->queryClamp(distance,obj);
 }
 return 1;
}
