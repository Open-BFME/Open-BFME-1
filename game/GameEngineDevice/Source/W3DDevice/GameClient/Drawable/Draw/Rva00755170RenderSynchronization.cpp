// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x00755170: 943 bytes, thiscall, two pointer-range arguments (ret 8).
// The owner has no proven semantic class identity. The address-bearing names
// below describe only the observed selection and render-sharing operation.
// Caller: 0x00755A70 through its ILT; independently matched handle 0x00754850
// witnesses the list at +0x0c and retained-pointer vectors at +0x10/+0x1c.
// The two 28-byte records copy only their +4/+8 words, not their whole storage.
//
// Container names Object and Gen_t_00715d40_p4pod preserve EXISTING callee ABIs:
// these are storage/transport views, not claims that render objects are game
// Object instances. Object stays incomplete and is never dereferenced.
// 0x00037D21 -> 0x00754260: vector<Object*>::_M_fill_insert.
// 0x000486BC -> 0x00754110: vector<Object*>::_M_insert_overflow.
// 0x00012625 -> 0x00715770: vector<Gen_t_00715d40_p4pod> overflow.
//
// List00754E70::insertDefault is independently decoded at 0x00754E70:
// allocate 20 bytes; copy a zeroed 12-byte vector into node+8; link before
// the iterator argument; write the new node through the hidden result pointer;
// ret 8. Its ILT at 0x0002385D is an E9 to that body.
// Iter00754E70's explicit copy constructor preserves by-value construction.
//
// Exact-shape lever: reject nonzero slot3 results with release+continue in
// BOTH child loops. Nesting the first predicate under ==0 changes MSVC 7.1's
// register allocation. No volatile casts, custom compiler switches, or asm.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
class Gen_00410BA0 { public: int bfmeBusy() const; };
class Rva0092D660 { public: int test(); };
class Render00755170 {
public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual int slot3();
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
virtual int slot28();
virtual Render00755170 *slot29(int);
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
virtual void slot58(Render00755170 *);
int refs;
char pad008[0x314-8];
void **field314;
void release() { if (--refs == 0) slot0(); }
void retain() { ++refs; }
};
struct Flags00755170 { char pad[0x3b0]; bool field3b0, field3b1; };
struct Pair00755170 { int field0; int field4, field8; char tail[16];
 void copy(const Pair00755170 &p) { field4=p.field4; field8=p.field8; }
};
class Module00755170 {
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
virtual Render00755170 *slot46();
int field004;
Flags00755170 *field008;
char pad00c[8];
int field014;
char pad018[0xdc-0x18];
Pair00755170 field0dc;
Pair00755170 field0f8;
char pad114[0x280-0x114];
int field280, field284;
};
struct Entry00755170 { int field0; Module00755170 *module; };
class ClientRoot4120 {
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
virtual int slot26();
};
class GameClient;
extern GameClient *TheGameClient;
class Object;
struct Gen_t_00715d40_p4pod { int a[1]; };
struct Node00754E70 { Node00754E70 *next,*prev; _STL::vector<Object *> data; };
struct Iter00754E70 { Node00754E70 *node; Iter00754E70(Node00754E70 *p):node(p) {} Iter00754E70(const Iter00754E70 &p):node(p.node) {} };
struct List00754E70 { Node00754E70 *node; Iter00754E70 insertDefault(Iter00754E70 pos); };
class Synchronize00755170 {
public:
 void apply(Entry00755170 **first, Entry00755170 **last);
 char pad000[12];
 List00754E70 list;
 _STL::vector<Object *> children;
 _STL::vector<Gen_t_00715d40_p4pod> models;
};
void Synchronize00755170::apply(Entry00755170 **first, Entry00755170 **last)
{
 Entry00755170 *selected=0;
 Render00755170 *selectedModel=0;
 Entry00755170 *fallback=0;
 Render00755170 *fallbackModel=0;

 for (Entry00755170 **it=first; it!=last; ++it) {
  Module00755170 *module=(*it)->module;
  Flags00755170 *flags=module->field008;
  if (!flags->field3b1 || (char)((Gen_00410BA0*)flags)->bfmeBusy() || flags->field3b0) continue;
  Render00755170 *model=module->slot46();
  if (!model) continue;
  if (!selected) { selected=*it; selectedModel=model; }
  if (module->field284==module->field014) {
   int frame=((ClientRoot4120 *)TheGameClient)->slot26();
   int stamp=module->field280;
   bool positive=true;
   if (stamp<0) { positive=false; stamp=-stamp; }
   if (stamp>=frame-1) {
    if (positive) { Entry00755170 *preferred=*it; if (preferred) { selected=preferred; selectedModel=model; goto selected_ready; } break; }
    if (!fallback) { fallback=*it; fallbackModel=model; }
   }
  }
 }
 if (fallback) { selected=fallback; selectedModel=fallbackModel; }
selected_ready:
 if (!selected) return;
 unsigned count=0;
 for (int n=selectedModel->slot28(); n>0;) {
  Render00755170 *child=selectedModel->slot29(--n);
  if (!child) continue;
  if (child->slot3()!=0) { child->release(); continue; }
  if (!(char)((Rva0092D660*)child)->test()) { child->release(); continue; }
  ++count;
  child->release();
 }
 list.insertDefault(Iter00754E70(list.node));
 _STL::vector<Object *> &slots=list.node->prev->data;
 slots.resize(count, (Object*)0);
 void **base=(void**)slots.begin();
 for (Entry00755170 **it=first; it!=last; ++it) {
  Module00755170 *module=(*it)->module;
  Flags00755170 *flags=module->field008;
  if (!flags->field3b1 || (char)((Gen_00410BA0*)flags)->bfmeBusy() || flags->field3b0) continue;
  Gen_t_00715d40_p4pod trackedModel = { (int)module->slot46() };
  Render00755170 *model=(Render00755170*)trackedModel.a[0];
  if (!model) continue;
  module->field284=module->field014;
  if (model!=selectedModel) {
   model->retain();
   models.push_back(trackedModel); model->slot58(selectedModel);
   module->field280=-((ClientRoot4120 *)TheGameClient)->slot26();
  } else module->field280=((ClientRoot4120 *)TheGameClient)->slot26();
  void **slot=base;
  for (int n=model->slot28(); n>0;) {
   Render00755170 *child=model->slot29(--n);
   if (!child) continue;
   if (child->slot3()!=0) { child->release(); continue; }
   Object *mesh=(Object*)child;
   if (!(char)((Rva0092D660*)mesh)->test()) { child->release(); continue; }
   ((Render00755170*)mesh)->retain(); child->release();
   children.push_back(mesh);
   ((Render00755170*)mesh)->field314=slot;
   *slot=0;
   ++slot;
  }
  module->field0dc.copy(selected->module->field0dc);
  module->field0f8.copy(selected->module->field0f8);
 }
}

// Layout checks for the fields decoded from this body and its matched sibling.
#include <stddef.h>
typedef char CheckPair00755170[(sizeof(Pair00755170)==28)?1:-1];
typedef char CheckFlags00755170[(offsetof(Flags00755170,field3b1)==0x3b1)?1:-1];
typedef char CheckModule00755170[(offsetof(Module00755170,field280)==0x280)?1:-1];
typedef char CheckChild00755170[(offsetof(Render00755170,field314)==0x314)?1:-1];
typedef char CheckList00754E70[(sizeof(Node00754E70)==20)?1:-1];
typedef char CheckModels00755170[(offsetof(Synchronize00755170,models)==0x1c)?1:-1];
