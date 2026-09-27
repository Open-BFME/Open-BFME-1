// cl: /DNDEBUG /MD /EHsc-
#include "../../object.h"
extern void j_00015d02();
extern void j_0004a12e();
extern void j_0000efa2();
class Route0023FDB0 {};
template<int N> class Slots0023FDB0 : public Slots0023FDB0<N-1> { public: virtual void unused(char (*)[N])=0; };
template<> class Slots0023FDB0<0> {};
class Primary0023FDB0 : public Slots0023FDB0<30> { public: virtual void slot078(int)=0; };
class AIView0023FDB0 : public Slots0023FDB0<127> { public: virtual void slot1fc(int)=0; };
struct AIHub0023FDB0 { char at000[12]; Route0023FDB0 *at00c; };
extern AIHub0023FDB0 *g0023FDB0Va012EF214;
struct Node0023FDB0 { Node0023FDB0 *next,*prev; Object *object; };
struct List0023FDB0 { Node0023FDB0 *head; };
class MemberSync0023FDB0 {
public:
 void run(List0023FDB0 *list);
 virtual void s00()=0; virtual void s04()=0; virtual void s08()=0; virtual void s0c()=0;
 virtual void slot010(int)=0;
 virtual void s14()=0; virtual void s18()=0; virtual void s1c()=0; virtual void s20()=0; virtual void s24()=0; virtual void s28()=0;
 virtual void slot02c(Object *)=0;
 virtual void unused12()=0;
 virtual void unused13()=0;
 virtual void unused14()=0;
 virtual void unused15()=0;
 virtual void unused16()=0;
 virtual void unused17()=0;
 virtual void unused18()=0;
 virtual void unused19()=0;
 virtual void unused20()=0;
 virtual void unused21()=0;
 virtual void unused22()=0;
 virtual void unused23()=0;
 virtual void unused24()=0;
 virtual void unused25()=0;
 virtual void unused26()=0;
 virtual void unused27()=0;
 virtual void unused28()=0;
 virtual void unused29()=0;
 virtual void unused30()=0;
 virtual void unused31()=0;
 virtual void unused32()=0;
 virtual void unused33()=0;
 virtual void unused34()=0;
 virtual void unused35()=0;
 virtual void unused36()=0;
 virtual void unused37()=0;
 virtual void unused38()=0;
 virtual void unused39()=0;
 virtual void unused40()=0;
 virtual void unused41()=0;
 virtual void unused42()=0;
 virtual void unused43()=0;
 virtual void unused44()=0;
 virtual void unused45()=0;
 virtual void unused46()=0;
 virtual void unused47()=0;
 virtual void unused48()=0;
 virtual void unused49()=0;
 virtual void unused50()=0;
 virtual void unused51()=0;
 virtual void unused52()=0;
 virtual void unused53()=0;
 virtual void unused54()=0;
 virtual void unused55()=0;
 virtual void unused56()=0;
 virtual void unused57()=0;
 virtual void unused58()=0;
 virtual void unused59()=0;
 virtual void unused60()=0;
 virtual void unused61()=0;
 virtual void unused62()=0;
 virtual void unused63()=0;
 virtual void unused64()=0;
 virtual void unused65()=0;
 virtual void unused66()=0;
 virtual void unused67()=0;
 virtual void unused68()=0;
 virtual void unused69()=0;
 virtual void unused70()=0;
 virtual void unused71()=0;
 virtual void unused72()=0;
 virtual void unused73()=0;
 virtual void unused74()=0;
 virtual void unused75()=0;
 virtual void unused76()=0;
 virtual void unused77()=0;
 virtual void unused78()=0;
 virtual void unused79()=0;
 virtual void unused80()=0;
 virtual void unused81()=0;
 virtual void unused82()=0;
 virtual void unused83()=0;
 virtual void unused84()=0;
 virtual void unused85()=0;
 virtual void unused86()=0;
 virtual void unused87()=0;
 virtual void unused88()=0;
 virtual void unused89()=0;
 virtual void unused90()=0;
 virtual void unused91()=0;
 virtual void unused92()=0;
 virtual void unused93()=0;
 virtual void unused94()=0;
 virtual void unused95()=0;
 virtual void unused96()=0;
 virtual void unused97()=0;
 virtual void unused98()=0;
 virtual void unused99()=0;
 virtual void unused100()=0;
 virtual void unused101()=0;
 virtual void unused102()=0;
 virtual void unused103()=0;
 virtual void unused104()=0;
 virtual void unused105()=0;
 virtual void unused106()=0;
 virtual void unused107()=0;
 virtual void unused108()=0;
 virtual void unused109()=0;
 virtual void unused110()=0;
 virtual void slot1bc()=0;
};
// Retail 0x0023FDB0: 225 bytes, ret 4. Original method identity is unproved.
// Receiver is an interior interface, 0xe4 bytes after the primary view.
// Calls retain ILT routes 15D02 -> Pathfinder removeGoal, 4A12E ->
// ExperienceTracker gainExpForLevel and EFA2 -> member formation state.
// Object fields use the shared retail layout. Virtual slots follow the call sites.
void MemberSync0023FDB0::run(List0023FDB0 *list) {
 if (!*((char*)this+0x58)) ((Primary0023FDB0*)((char*)this-0xe4))->slot078(1);
 Object *owner=*(Object **)((char*)this-0xdc);
 int level=*(int*)((char*)owner->m_experienceTracker+0x28);
 char *data=*(char **)((char*)this-0xe0);
 Node0023FDB0 *node=list->head->next;
 while(node!=list->head) {
  Object *obj=node->object;
  AIView0023FDB0 *ai=(AIView0023FDB0*)obj->m_ai;
  if(ai) {
   typedef void (Route0023FDB0::*Remove)(Object*);
   union { void (*fn)(); Remove call; } remove={j_00015d02};
   (g0023FDB0Va012EF214->at00c->*remove.call)(obj);
   slot02c(obj);
   typedef bool (Route0023FDB0::*Gain)(int,bool,bool);
   union { void (*fn)(); Gain call; } gain={j_0004a12e};
   (((Route0023FDB0*)obj->m_experienceTracker)->*gain.call)(level-*(int*)((char*)obj->m_experienceTracker+0x28),true,false);
   union { void (*fn)(); Remove call; } apply={j_0000efa2};
   (((Route0023FDB0*)((char*)this-0xe4))->*apply.call)(obj);
   if(data) { int value=*(int*)(data+0x2cc); if(value!=-1) ai->slot1fc(value); }
   node=node->next;
  }
 }

 slot1bc();
 slot010(0);
}
