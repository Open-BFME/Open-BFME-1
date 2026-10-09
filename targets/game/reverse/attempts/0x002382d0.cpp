// ?replace002382D0@ContainView002382D0@@UAEXPBVThingTemplate@@@Z
// partial score=0.7072 date=2026-10-09
// Retail secondary-interface slot 25; owner and method identities remain address-qualified.
// Pointer payloads and the boolean latch follow complete decoded helpers.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Igame/GameEngine/Source/GameLogic/Object
// stlport
#include <list>
#include <string.h>
#include <bitset>
#include <algorithm>
#include "Common/LatchRestore.h"
class Object;
class Team;
class ThingTemplate;
template<int N> class BitFlags { public: _STL::bitset<N> bits; };
class ThingFactory { public: Object *newObject(const ThingTemplate *,Team *,const BitFlags<86>&,unsigned int);
 // ?create002382D0@ThingFactory@@QAEPAVObject@@PBVThingTemplate@@PAVTeam@@@Z absent-from-retail
 Object *create002382D0(const ThingTemplate *t, Team *team) { return newObject(t,team,BitFlags<86>(),0); }
};
class GameLogic { public: void destroyObject(Object *); Object *findObjectByID(int); };
extern ThingFactory *TheThingFactory;
extern GameLogic *TheGameLogic;
typedef _STL::list<Object *> MemberList002382D0;
class ContainView002382D0;
struct Owner002382D0;
class ModuleView002382D0 {
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
 virtual ContainView002382D0 *slot26();
};
#define OBJECT_TU_MEMBERS void bfmeSwapContainModule(Object *);
#include "object.h"
class ContainView002382D0 { public:
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
 virtual void slot17(MemberList002382D0 *);
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void replace002382D0(const ThingTemplate *);
 virtual void slot26();
 virtual void slot27();
 virtual Object *slot28(Object *,Object *,bool);
 virtual void slot29(MemberList002382D0 *);
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
 virtual void slot81(int);
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
 virtual Owner002382D0 *slot122();
};
struct Owner002382D0 {
 char prefix[0xe4];
 ContainView002382D0 view;
 char gap[0x210-0xe8];
 bool flag210;
};
void ContainView002382D0::replace002382D0(const ThingTemplate *t)
{
 Object *created=TheThingFactory->newObject(t,(*(Object **)((char *)this-0xdc))->m_team,BitFlags<86>(),0);
 ContainView002382D0 *contain=0;
 if ((ModuleView002382D0 *)created->m_contain) contain=((ModuleView002382D0 *)created->m_contain)->slot26();
 if (!contain) { TheGameLogic->destroyObject(created); return; }
 Owner002382D0 *replacement=contain->slot122();
 slot112();
 MemberList002382D0 members;
 slot17(&members);
 Object *held=TheGameLogic->findObjectByID(*(int *)((char *)this+0xd8));
 if (held) {
  MemberList002382D0::iterator it=_STL::find(members.begin(),members.end(),held);
  if(it!=members.end()) members.erase(it);
 }
 bool enabled=((char *)(*(Object **)((char *)this-0xdc))->getDrawable())[0x3ac]!=0;
 (*(Object **)((char *)this-0xdc))->bfmeSwapContainModule(created);
 ContainView002382D0 *other=&replacement->view;
 other->slot81(*(int *)((char *)this+0xe8));
 other->slot29(&members);
 if(held) {
  if(members.size()>0) {
   LatchRestore<bool> restore(replacement->flag210,true);
   Object *first=members.front();
   if(first) { other->slot28(held,first,true); held=0; }
  }
  if(held) TheGameLogic->destroyObject(held);
 }
 other->slot111();
 TheGameLogic->destroyObject(created);
 if(enabled) other->slot52();
}

