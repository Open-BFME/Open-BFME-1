// ?method@Rva001709E0@@QAEHXZ
// cl: /O2 /MD /EHsc /Igame/GameEngine/Source /Igame/Libraries/Source/WWVegas/WWMath
// stlport
// The matched callees at 0x001A7C20, 0x0009A510, and 0x000EF060 establish
// the class names and method signatures used below.
#include "coord3d.h"
#include "Common/Thing/GameLogicObjectLookup.h"
extern GameLogic *TheGameLogic;

enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_GROUND = 1 };
class TerrainLogic { public: PathfindLayerEnum getLayerForDestination(Object *, const Coord3D *); };
extern TerrainLogic *TheTerrainLogic;
class Team;
typedef unsigned int TeamID;
class TeamFactory { public: Team *findTeamByID(TeamID); };
extern TeamFactory *TheTeamFactory;
class Gen_001BF490 { public: void bfmeForward(void *); };
class Rva001709E0AI {
public:
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
 virtual void slot96();
 virtual void slot97();
 virtual void slot98();
 virtual void slot99();
 virtual void slot100();
 virtual void slot101();
 virtual void slot102();
 virtual void slot103();
 virtual const Coord3D *slot104();
 virtual int slot105();
 virtual unsigned slot106();
 virtual void *slot107();
 virtual void slot108();
 virtual int slot109();
 virtual void slot110();
 virtual int slot111();
};
struct Rva001709E0Words { unsigned x,y,z; };
class Rva001709E0Guard {
public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual int slot7();
 virtual int slot8(int);
 char pad4[0x14]; int word18;
 __forceinline void set44(Object *target) { *(unsigned *)((char *)this+0x44)=target?*(unsigned *)((char *)target+0x74):0; }
 __forceinline void set48(Team *team) { *(unsigned *)((char *)this+0x48)=team?*(unsigned *)((char *)team+8):0; }
 __forceinline void set5c(const Coord3D *p) { *(Rva001709E0Words *)((char *)this+0x5c)=*(const Rva001709E0Words *)p; *((char *)this+0x68)=1; }

};
class Rva001709E0Machine {
public:
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
 virtual Rva001709E0Guard *slot10();
};

class Rva001709E0 {
 char pad[0x1c];
 Rva001709E0Machine *machine;
 unsigned word20;
 Rva001709E0Guard *guard;
public: int method();
};
int Rva001709E0::method()
{
 Object *obj=*(Object **)((char *)machine+0x10);
 Rva001709E0AI *ai=*(Rva001709E0AI **)((char *)obj+0x204);
 guard=machine->slot10();
 switch(ai->slot109()) {
 case 0:
  *(Rva001709E0Words *)((char *)guard+0x50)=*(const Rva001709E0Words *)ai->slot104();
  if(TheTerrainLogic->getLayerForDestination(obj,ai->slot104())!=1)
   *((char *)ai+0x33b)=1;
  break;
 case 1: {
  Object *target=TheGameLogic->findObjectByID(ai->slot105());
  guard->set44(target);
  ((Gen_001BF490 *)obj)->bfmeForward(target);
  break;
 }
 case 2: {
  Team *team=TheTeamFactory->findTeamByID(ai->slot106());
  guard->set48(team);
  break;
 }
 case 3:
  *(void **)((char *)guard+0x4c)=ai->slot107();
  if(ai->slot104()->lengthEstimate()!=0.0f) {
   guard->set5c(ai->slot104());
  }
  break;
 }
 *(int *)((char *)guard+0x70)=ai->slot111();
 if(guard->slot7()==-2)return -2;
 int id=guard->word18;
 return guard->slot8(id);
}
