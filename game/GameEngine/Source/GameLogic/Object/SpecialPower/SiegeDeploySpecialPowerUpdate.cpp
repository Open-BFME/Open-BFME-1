// cl: /DNDEBUG /MD /I.
//
// Open-BFME: SiegeDeploySpecialPower::update at retail RVA 0x00266F40
// (704 bytes including its five-entry switch table).
// BFME 1 target evidence: the matched constructor 0x00266240 installs vtable
// VA 0x010B7494 at +0x10, whose slot 0 is ILT 0x00007DBA -> this body, and
// ilt_oracle CONFIRMS ?update@SiegeDeploySpecialPower@@UAE?AW4UpdateSleepTime@@XZ
// (ZH UpdateModuleInterface::update is that interface's first virtual).
// `this` is the +0x10 subobject: module data at +4, Object at +8, the phase
// at +0x38 drives transition 0x00266B50, +0x3C counts frames against module
// data +0x1D0, +0x40 is the target ObjectID, +0x54 takes the approach point
// 0x002666A0 for direction +0x64, +0x60 alternates moving/facing, +0x70 is
// the stop request.
// Donor (open-bfme-2 20a0cb6173, Code/GameEngine/Source/GameLogic/Object/
// SpecialPower/SiegeDeploySpecialPowerUpdate.cpp, retail 0x004C5E80 there)
// supplies the control flow; its `ok` flag queried once per branch is what
// gives retail's Object-in-EBP/target-in-EBX allocation (the older && || form
// swapped them), and field reads go through a `self` copy of `this`
// (direct member access reallocates every register). Field, slot and
// helper names stay address-derived.
#include <math.h>
#include "game/Libraries/Source/WWVegas/WWMath/coord3d.h"
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
inline Coord3D::Coord3D(const Coord3D&o) {x=o.x;y=o.y;z=o.z;}
__forceinline Coord3D& Coord3D::operator=(const Coord3D&o) {struct Words{int x,y,z;};*(Words*)this=*(const Words*)&o;return *this;}
enum ObjectStatusTypes { Rva00266F40Status63=63 };
#define BFME_HAVE_COORD3D
#define THING_TU_MEMBERS float bfmeRelativeAngleTo(const Coord3D*) const;
#define OBJECT_TU_MEMBERS void clearStatus(ObjectStatusTypes); bool bfmeGeometryIntersects(const Object*) const;
#include "game/GameEngine/Source/GameLogic/Object/object.h"
#include "game/GameEngine/Source/GameLogic/command_source_type.h"
class Rva00266EB0SiegeDeployBase {public: void transition(int);void clearStatusBit63();};
class GameLogic {public: Object *findObjectByID(int);};
extern GameLogic *TheGameLogic;
class AICommandInterface {public: void aiMoveToPosition(const Coord3D*,CommandSourceType);};
class Rva00266F40AIView { public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual void slot28();
virtual void slot29();
virtual void slot30();
virtual void slot31();
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual void slot36();
virtual void slot37();
virtual void slot38();
virtual void slot39();
virtual void slot40();
virtual void slot41();
virtual void slot42();
virtual void slot43();
virtual void slot44();
virtual void slot45();
virtual void slot46();
virtual void slot47();
virtual void slot48();
virtual void slot49();
virtual void slot50();
virtual void slot51();
virtual void slot52();
virtual void slot53();
virtual void slot54();
virtual void slot55();
virtual void slot56();
virtual void slot57();
virtual void slot58();
virtual void slot59();
virtual void slot60();
virtual void slot61();
virtual void slot62();
virtual void slot63();
virtual void slot64();
virtual void slot65();
virtual void slot66();
virtual void slot67();
virtual void slot68();
virtual void slot69();
virtual void slot70();
virtual void slot71();
virtual void slot72();
virtual void slot73();
virtual void slot74();
virtual void slot75();
virtual void slot76();
virtual void slot77();
virtual void slot78();
virtual void slot79();
virtual void slot80();
virtual void slot81();
virtual void slot82();
virtual void slot83();
virtual void slot84();
virtual void slot85();
virtual void slot86();
virtual void slot87();
virtual void slot88();
virtual void slot89();
virtual void slot90();
virtual void slot91();
virtual void slot92();
virtual void slot93();
virtual void slot94();
virtual void slot95();
virtual bool slot96();
virtual void slot97();
virtual void slot98();
virtual void slot99();
virtual void slot100();
virtual void slot101();
virtual void slot102();
virtual void slot103();
virtual void slot104();
virtual void slot105();
virtual void slot106();
virtual void slot107();
virtual void slot108();
virtual void slot109();
virtual void slot110();
virtual void slot111();
virtual void slot112();
virtual void slot113();
virtual void slot114();
virtual void slot115();
virtual void slot116();
virtual void slot117();
virtual void slot118();
virtual void slot119();
virtual void slot120();
virtual void slot121();
virtual void slot122();
virtual void slot123();
virtual void slot124();
virtual void slot125();
virtual void slot126();
virtual void slot127();
virtual int slot128();
};
extern void j_0002fc7a();extern void j_0003c740();extern void j_0003bff7();extern void j_0001336d();extern void j_00020455();extern void j_00040732();
class Rva00266F40Action {public: void method();};
static __forceinline void *rva001F8AB0(Object *o) {union {void(*raw)();void*(__cdecl*fn)(Object*);}c;c.raw=j_0002fc7a;return c.fn(o);}
static __forceinline void rva001F84C0(void *o) {union {void(*raw)();void(Rva00266F40Action::*fn)();}c;c.raw=j_0003c740;(((Rva00266F40Action*)o)->*c.fn)();}
static __forceinline bool rva001F9180(void *o,int a) {union {void(*raw)();bool(Rva00266F40Action::*fn)(int);}c;c.raw=j_0003bff7;return (((Rva00266F40Action*)o)->*c.fn)(a);}
static __forceinline void rva001F1370(void *o,int a,int b) {union {void(*raw)();void(Rva00266F40Action::*fn)(int,int);}c;c.raw=j_0001336d;(((Rva00266F40Action*)o)->*c.fn)(a,b);}
// aiBfmeCommand39 (0x00266A30) is ledgered with the struct-keyed Coord3D spelling.
static __forceinline void rva00266A30(void *o,const Coord3D *pos,CommandSourceType src) {union {void(*raw)();void(Rva00266F40Action::*fn)(const Coord3D*,CommandSourceType);}c;c.raw=j_00040732;(((Rva00266F40Action*)o)->*c.fn)(pos,src);}
class AIUpdateInterface {public: void ignoreObstacle(const Object*);};
struct Rva00266F40ModuleData {char pad[0x1d0];unsigned count;};
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1, UPDATE_SLEEP_FOREVER = 0x3fffffff };
// Private view of the +0x10 update-interface subobject (the vptr of vtable
// VA 0x010B7494 at +0); the primary base and its module data and Object
// pointers sit at -0x10, -0xC and -8.
class SiegeDeploySpecialPower
{
public:
 virtual UpdateSleepTime update();
private:
 char pad00[0x28 - 4];
 int m_phase;
 unsigned m_frame;
 int m_targetID;
 char pad34[0x10];
 Coord3D m_approach;
 bool m_turn;
 char pad51[3];
 Coord3D m_direction;
 bool m_stop;
};
UpdateSleepTime SiegeDeploySpecialPower::update()
{
 SiegeDeploySpecialPower *self=this;
 Object *object=*(Object**)((char*)this-8);
 if(object->m_privateStatus&1) {void *m=rva001F8AB0(object);if(m)rva001F84C0(m);return UPDATE_SLEEP_FOREVER;}
 if(!self->m_phase)return UPDATE_SLEEP_FOREVER;
 if(self->m_stop) {((Rva00266EB0SiegeDeployBase*)((char*)this-0x10))->transition(4);self->m_stop=false;return UPDATE_SLEEP_NONE;}
 Rva00266F40AIView *ai=(Rva00266F40AIView*)object->m_ai;
 if(!ai) {((Rva00266EB0SiegeDeployBase*)((char*)this-0x10))->clearStatusBit63();return UPDATE_SLEEP_FOREVER;}
 if(!object->getDrawable())return UPDATE_SLEEP_FOREVER;
 if((!ai->slot96()&&ai->slot128()!=2)||(ai->slot96()&&ai->slot128()==0)) {((Rva00266EB0SiegeDeployBase*)((char*)this-0x10))->clearStatusBit63();return UPDATE_SLEEP_FOREVER;}
 Object *target=0;
 if(self->m_targetID) {target=TheGameLogic->findObjectByID(self->m_targetID);if(!target||(target->m_privateStatus&1)) {target=0;self->m_targetID=0;if(self->m_phase==3)((Rva00266EB0SiegeDeployBase*)((char*)this-0x10))->transition(4);}}
 if(!target)((Rva00266EB0SiegeDeployBase*)((char*)this-0x10))->transition(4);
 switch(self->m_phase) {
 case 0:target->clearStatus(Rva00266F40Status63);return UPDATE_SLEEP_FOREVER;
 case 1: {
 bool ok;
 {Coord3D position=object->m_cachedPos;position+=self->m_direction;
 ok=fabs(object->bfmeRelativeAngleTo(&position))<0.15f;
 if(ok) {ok=false;
 if(object->bfmeGeometryIntersects(target)) {void *module=rva001F8AB0(object);if(module&&rva001F9180(module,0))ok=true;}
 else if(ai->slot96()) {void *module=rva001F8AB0(object);if(module&&rva001F9180(module,0))ok=true;}
 }
 }
 if(ok) {ai->slot122();rva001F1370((char*)ai+0x20,0,2);((Rva00266EB0SiegeDeployBase*)((char*)this-0x10))->transition(2);break;}
 if(ai->slot96()) {
 ((AIUpdateInterface*)ai)->ignoreObstacle(target);
 self->m_turn=!self->m_turn;
 if(self->m_turn) {bool docked=false;union {void(*raw)();Coord3D(Rva00266F40Action::*fn)(Object*,Coord3D*,bool*);}c;c.raw=j_00020455;self->m_approach=(((Rva00266F40Action*)((char*)this-0x10))->*c.fn)(target,&self->m_direction,&docked);if(docked)((AICommandInterface*)((char*)ai+0x20))->aiMoveToPosition(&self->m_approach,CMD_FROM_AI);}
 else {Coord3D position=object->m_cachedPos;position+=self->m_direction;rva00266A30((char*)ai+0x20,&position,CMD_FROM_AI);}
 }
 break;}
 case 2:if(++self->m_frame>=(*(Rva00266F40ModuleData**)((char*)this-12))->count)((Rva00266EB0SiegeDeployBase*)((char*)this-0x10))->transition(3);break;
 case 4:((Rva00266EB0SiegeDeployBase*)((char*)this-0x10))->transition(0);break;
 }
 return UPDATE_SLEEP_NONE;
}
