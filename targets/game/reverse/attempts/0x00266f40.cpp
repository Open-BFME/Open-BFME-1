// ?method@Rva00266F40@@QAEHXZ
// partial score=0.3239 date=2026-10-03
// cl: /DNDEBUG /MD /I.
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
class AICommandInterface {public: void aiMoveToPosition(const Coord3D*,CommandSourceType);void aiBfmeCommand39(const Coord3D*,CommandSourceType);};
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
extern void j_0002fc7a();extern void j_0003c740();extern void j_0003bff7();extern void j_0001336d();extern void j_00020455();
class Rva00266F40Action {public: void method();};
static __forceinline void *rva001F8AB0(Object *o) {union {void(*raw)();void*(__cdecl*fn)(Object*);}c;c.raw=j_0002fc7a;return c.fn(o);}
static __forceinline void rva001F84C0(void *o) {union {void(*raw)();void(Rva00266F40Action::*fn)();}c;c.raw=j_0003c740;(((Rva00266F40Action*)o)->*c.fn)();}
static __forceinline bool rva001F9180(void *o,int a) {union {void(*raw)();bool(Rva00266F40Action::*fn)(int);}c;c.raw=j_0003bff7;return (((Rva00266F40Action*)o)->*c.fn)(a);}
static __forceinline void rva001F1370(void *o,int a,int b) {union {void(*raw)();void(Rva00266F40Action::*fn)(int,int);}c;c.raw=j_0001336d;(((Rva00266F40Action*)o)->*c.fn)(a,b);}
static __forceinline Coord3D rva002666A0(void *o,Object *target,Coord3D *pos,bool *ok) {union {void(*raw)();Coord3D(Rva00266F40Action::*fn)(Object*,Coord3D*,bool*);}c;c.raw=j_00020455;return (((Rva00266F40Action*)o)->*c.fn)(target,pos,ok);}
class AIUpdateInterface {public: void ignoreObstacle(const Object*);};
struct Rva00266F40Data {char pad[0x1d0];unsigned count;};
class Rva00266F40 {public: int method(); char pad00[0x28];int state;unsigned counter;int target;char pad34[0x10];Coord3D pos;bool toggle;char pad51[3];Coord3D delta;bool pending;};
struct Rva00266F40Layout {char pad[4];Rva00266F40Data *data;Object *object;char pad0c[0x2c];int state;unsigned counter;int target;char pad44[0x10];Coord3D pos;bool toggle;char pad61[3];Coord3D delta;bool pending;};
int Rva00266F40::method()
{
 Rva00266F40 *self=this;
 Object *object=*(Object**)((char*)this-8);
 if(object->m_privateStatus&1) {void *m=rva001F8AB0(object);if(m)rva001F84C0(m);return 0x3fffffff;}
 if(!self->state)return 0x3fffffff;
 if(self->pending) {((Rva00266EB0SiegeDeployBase*)((char*)this-0x10))->transition(4);self->pending=false;return 1;}
 Rva00266F40AIView *ai=(Rva00266F40AIView*)object->m_ai;
 if(!ai) {((Rva00266EB0SiegeDeployBase*)((char*)this-0x10))->clearStatusBit63();return 0x3fffffff;}
 if(!object->getDrawable())return 0x3fffffff;
 if((!ai->slot96()&&ai->slot128()!=2)||(ai->slot96()&&ai->slot128()==0)) {((Rva00266EB0SiegeDeployBase*)((char*)this-0x10))->clearStatusBit63();return 0x3fffffff;}
 Object *target=0;
 if(self->target) {target=TheGameLogic->findObjectByID(self->target);if(!target||(target->m_privateStatus&1)) {target=0;self->target=0;if(self->state==3)((Rva00266EB0SiegeDeployBase*)((char*)this-0x10))->transition(4);}}
 if(!target)((Rva00266EB0SiegeDeployBase*)((char*)this-0x10))->transition(4);
 switch(self->state) {
 case 0:target->clearStatus(Rva00266F40Status63);return 0x3fffffff;
 case 1: {
 {Coord3D position=object->m_cachedPos;position+=self->delta;
 if(fabs(object->bfmeRelativeAngleTo(&position))<0.15f && (object->bfmeGeometryIntersects(target)||ai->slot96())) {
 void *module=rva001F8AB0(object);
 if(module&&rva001F9180(module,0)) {ai->slot122();rva001F1370((char*)ai+0x20,0,2);((Rva00266EB0SiegeDeployBase*)((char*)this-0x10))->transition(2);break;}
 }
 }
 if(ai->slot96()) {
 ((AIUpdateInterface*)ai)->ignoreObstacle(target);
 self->toggle=!self->toggle;
 if(self->toggle) {bool ok=false;union {void(*raw)();Coord3D(Rva00266F40Action::*fn)(Object*,Coord3D*,bool*);}c;c.raw=j_00020455;self->pos=(((Rva00266F40Action*)((char*)this-0x10))->*c.fn)(target,&self->delta,&ok);if(ok)((AICommandInterface*)((char*)ai+0x20))->aiMoveToPosition(&self->pos,CMD_FROM_AI);}
 else {Coord3D position=object->m_cachedPos;position+=self->delta;((AICommandInterface*)((char*)ai+0x20))->aiBfmeCommand39(&position,CMD_FROM_AI);}
 }
 break;}
 case 2:if(++self->counter>=(*(Rva00266F40Data**)((char*)this-12))->count)((Rva00266EB0SiegeDeployBase*)((char*)this-0x10))->transition(3);break;
 case 4:((Rva00266EB0SiegeDeployBase*)((char*)this-0x10))->transition(0);break;
 }
 return 1;
}
