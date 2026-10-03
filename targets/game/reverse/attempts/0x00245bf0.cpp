// ?d_00245bf0@@YAXXZ
// partial score=0.3797 date=2026-10-03
// cl: /I. /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include
// stlport
// BANK ONLY: unbound opaque ABI views; no production pin/identity claim.
// Retail RVA245BF0..2462D2: RET0C at2462CF and padding2462D2; frame3C.
// Secondary Horde receiver primary+E4; incoming Object*, int, bool. Native
// shared constructor vtables VA10AE230/10AED58/10B07E0 slot28 -> ILT41A67C.
// EH C0DE98/DFCBD4 has three states: AsciiString, list<Object*>, LatchRestore<bool>.
// Unbound view calls map from retail direct call operands (not guessed identities):
// Template::ask=87A80, Primary::find=238740, Primary::rva002459d0=2459D0,
// Primary::rva00245b20=245B20 (fourth bool forwarded to proven284810 bool).
// Factory::findTemplate=137E80, newObject=138520; Logic::findObjectByID=9A510,
// destroyObject=38B0C0; ObjectAPI::isKindOf=A2CF0, merge=FA140,
// setAndNotify=1BF2E0, rva00132200=132200; Mask::merge=F9F20;
// XP::gainExpForLevel=1B2A10; Pathfinder::rva003D57F0=3D57F0;
// Commands::rva001F1370=1F1370 (existing Oathbreakers dtor pin contradicts ABI).
// Native list calls CEB D0(dtor), CFFE0(push), F8740(erase), F87A0(find),
// allocator82E540; compare5FEB0, copy887B60, release887940.
// Native globals TheThingFactory=12EF1D8, TheGameLogic=12F0898, TheAI=12EF214.
// 1756B/1762,1081 nonreloc positional differences,shape.912; frame48 not3C.
// In particular compiler moves non-horde branch past early cleanup, retains
// a different zero register, and omits two native EH state-byte stores.
// /EHsc- matches /EHsc identically. Reordering data/XP/max worsens to1749B/1438diffs.
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_NEWALLOC 1
#include <list>
#include <algorithm>
#include "ascii_string.h"
#include "Common/LatchRestore.h"
class ProductionUpdateInterface;
#define OBJECT_TU_MEMBERS ProductionUpdateInterface *getProductionUpdateInterface(); void *unidentified_001BFE20() const; void setStatusBit(int,bool);
#include "game/GameEngine/Source/GameLogic/Object/object.h"

template<class T> static T &field(void*p,int n) {return *(T*)((char*)p+n);}
template<class T> static const T &field(const void*p,int n) {return *(const T*)((const char*)p+n);}
class Rva00245BF0Dispatch;
struct Rva00245BF0Mask {unsigned w[6];void merge(const Rva00245BF0Mask&);};
struct Rva00245BF0ObjectAPI {
 bool isKindOf(int) const;
 void merge(const Rva00245BF0Mask&);
 void setAndNotify(int);
 void rva00132200(const Matrix3D*);
};
struct Rva00245BF0XP {
 bool gainExpForLevel(int,bool,bool);
 int level() const {return field<int>(this,0x28);}
};
struct Rva00245BF0Template {
 Rva00245BF0Template *ask();
 Rva00245BF0Template *getFinal() {
  if(!this) return 0;
  if(field<Rva00245BF0Template*>(this,4)) return field<Rva00245BF0Template*>(this,4)->ask();
  return this;
 }
 const AsciiString &name() const {return field<AsciiString>(this,0x20);}
 unsigned flag108() const {return field<unsigned>(this,0xd4)&0x1000;}
};
static Rva00245BF0Template *templ(Object*o) {return ((Rva00245BF0Template*)o->m_template)->getFinal();}
struct Rva00245BF0Entry {AsciiString key,value;};
struct Rva00245BF0Primary {
 void rva002459d0(Object*,int*,int);
 void rva00245b20(Object*,int,bool,bool);
 Rva00245BF0Entry *find(AsciiString);
};
struct Rva00245BF0Status {unsigned w[3];Rva00245BF0Status(){w[0]=w[1]=w[2]=0;}};
struct Rva00245BF0Factory {
 const ThingTemplate *findTemplate(const AsciiString&);
 Object *newObject(const ThingTemplate*,Team*,const Rva00245BF0Status&,unsigned);
};
extern Rva00245BF0Factory *TheThingFactory;
struct Rva00245BF0Logic {Object*findObjectByID(unsigned);void destroyObject(Object*);};
extern Rva00245BF0Logic *TheGameLogic;
struct Rva00245BF0Pathfinder {void rva003D57F0(Object*);};
struct Rva00245BF0AI {char pad[12];Rva00245BF0Pathfinder *pathfinder;};
extern Rva00245BF0AI *TheAI;
struct Rva00245BF0Commands {void rva001F1370(Object*,int);};
class Rva00245BF0Dispatch { public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual void slot0A();
 virtual void slot0B();
 virtual void slot0C();
 virtual void production34();
 virtual void slot0E();
 virtual void slot0F();
 virtual void slot10();
 virtual void members(std::list<Object*>*);
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual Rva00245BF0Dispatch *contain68();
 virtual void slot1B();
 virtual void add(Object*,Object*,bool);
 virtual void take(std::list<Object*>*);
 virtual void primary78(bool);
 virtual void slot1F();
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
 virtual void slot2A();
 virtual void slot2B();
 virtual void apply(const Rva00245BF0Mask*,bool);
 virtual void slot2D();
 virtual void slot2E();
 virtual void slot2F();
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
 virtual void slot3A();
 virtual void slot3B();
 virtual void slot3C();
 virtual void slot3D();
 virtual void slot3E();
 virtual void slot3F();
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
 virtual void slot4A();
 virtual void slot4B();
 virtual void slot4C();
 virtual void slot4D();
 virtual void slot4E();
 virtual void slot4F();
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
 virtual void slot5A();
 virtual void slot5B();
 virtual void slot5C();
 virtual void slot5D();
 virtual void slot5E();
 virtual void slot5F();
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
 virtual void slot6A();
 virtual void slot6B();
 virtual void slot6C();
 virtual void slot6D();
 virtual void slot6E();
 virtual void slot6F();
 virtual void prepare();
 virtual void slot71();
 virtual void slot72();
 virtual void slot73();
 virtual void slot74();
 virtual void slot75();
 virtual void slot76();
 virtual void slot77();
 virtual void slot78();
 virtual void slot79();
 virtual Rva00245BF0Dispatch *owner1E8();
};
class Rva00245BF0Secondary {public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual void slot0A();
 virtual void slot0B();
 virtual void slot0C();
 virtual void slot0D();
 virtual void slot0E();
 virtual void slot0F();
 virtual void slot10();
 virtual void members(std::list<Object*>*);
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual bool accepts(Object*,int,const void*,bool);
 virtual void slot1B();
 virtual void slot1C();
 virtual void slot1D();
 virtual void slot1E();
 virtual void slot1F();
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
 virtual void slot2A();
 virtual void slot2B();
 virtual void slot2C();
 virtual void slot2D();
 virtual void slot2E();
 virtual void slot2F();
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
 virtual void slot3A();
 virtual void slot3B();
 virtual void slot3C();
 virtual void slot3D();
 virtual void slot3E();
 virtual void slot3F();
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
 virtual void slot4A();
 virtual void slot4B();
 virtual void slot4C();
 virtual void slot4D();
 virtual void slot4E();
 virtual void slot4F();
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
 virtual void slot5A();
 virtual void slot5B();
 virtual void slot5C();
 virtual void slot5D();
 virtual void slot5E();
 virtual void slot5F();
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
 virtual void slot6A();
 virtual void slot6B();
 virtual void slot6C();
 virtual void slot6D();
 virtual void slot6E();
 virtual void slot6F();
 virtual void prepare();
 Object *method(Object*,int,bool);
 Object *object() {return field<Object*>(this,-0xdc);}
 Rva00245BF0Primary *primary() {return (Rva00245BF0Primary*)((char*)this-0xe4);}
};

Object *Rva00245BF0Secondary::method(Object *other,int which,bool force)
{
 void *data;
 if(!other)return 0;
 data=field<void*>(this,-0xe0);
 if(other->m_containedBy)other=other->m_containedBy;
 if(!field<bool>(this,0x58)) ((Rva00245BF0Dispatch*)((Rva00245BF0Primary*)((char*)this-0xe4)))->primary78(true);
 field<bool>(this,5)=true;
 if(!other->m_containedBy && !templ(other)->flag108()) {
  if(accepts(other,field<int>(this,0xd0),(char*)data+0x28c,false)) {
   ((Rva00245BF0Primary*)((char*)this-0xe4))->rva002459d0(other,&field<int>(this,0xd0),field<int>(this,0xd4));return 0;
  }
  if(accepts(other,field<int>(this,0xd8),(char*)data+0x2b0,force) &&
      (force || ((Rva00245BF0XP*)object()->m_experienceTracker)->level()<=1)) {
   ((Rva00245BF0Primary*)((char*)this-0xe4))->rva00245b20(other,which,force,!field<bool>(this,0x12c));return 0;
  }
  if(!field<bool>(data,0x2d0))return 0;
 }
 Object *second=0;
 if(!other->unidentified_001BFE20()) {
  if(!field<bool>(data,0x2d0))return 0;
  if(((const StringBase<char>&)field<AsciiString>(data,0x2d4)).compare(templ(other)->name())!=0)return 0;
 }
 Rva00245BF0Entry *entry=((Rva00245BF0Primary*)((char*)this-0xe4))->find(templ(other)->name());
 if(!entry)return 0;
 AsciiString name=entry->value;
 const ThingTemplate *newTemplate=TheThingFactory->findTemplate(name);
 if(!newTemplate)return 0;
 ProductionUpdateInterface *prod=object()->getProductionUpdateInterface();
 if(prod)((Rva00245BF0Dispatch*)prod)->production34();
 prod=other->getProductionUpdateInterface();
 if(prod)((Rva00245BF0Dispatch*)prod)->production34();
 prepare();
 std::list<Object*> list;
 members(&list);
 Object *first=TheGameLogic->findObjectByID(field<unsigned>(this,0xd8));
 Object *firstPlace=0;
 if(first) {
  std::list<Object*>::iterator it=std::find(list.begin(),list.end(),first);
  if(it!=list.end())list.erase(it);
  if(!list.empty())firstPlace=list.front();
 }
 Object *secondPlace=0;
 if(((Rva00245BF0ObjectAPI*)other)->isKindOf(108)) {
  Rva00245BF0Dispatch *h=((Rva00245BF0Dispatch*)other->m_contain)->contain68()->owner1E8();
  Rva00245BF0Dispatch *hsecondary=(Rva00245BF0Dispatch*)((char*)h+0xe4);
  hsecondary->prepare();hsecondary->members(&list);
  second=TheGameLogic->findObjectByID(field<unsigned>(h,0x1bc));
  if(second) {
   std::list<Object*>::iterator it=std::find(list.begin(),list.end(),second);
   if(it!=list.end())list.erase(it);
   if(!list.empty())secondPlace=list.back();
  }
 } else {
  if(other->m_ai)((Rva00245BF0Commands*)((char*)other->m_ai+0x20))->rva001F1370(0,2);
  list.push_back(other);
 }
 Rva00245BF0Status status;
 Object *created=TheThingFactory->newObject(newTemplate,object()->m_team,status,0);
 ((Rva00245BF0ObjectAPI*)created)->rva00132200((const Matrix3D*)&other->m_transform);
 TheAI->pathfinder->rva003D57F0(created);
 Rva00245BF0Mask mask=*(const Rva00245BF0Mask*)object()->m_objectUpgradesCompleted;
 mask.merge(*(const Rva00245BF0Mask*)other->m_objectUpgradesCompleted);
 ((Rva00245BF0ObjectAPI*)created)->merge(mask);
 if((object()->m_status[2]&0x100)!=0)created->setStatusBit(0x48,true);
 Rva00245BF0Dispatch *newH=0;
 if(created->m_contain)newH=((Rva00245BF0Dispatch*)created->m_contain)->contain68();
 if(!newH) {TheGameLogic->destroyObject(created);return 0;}
 Rva00245BF0Dispatch *newOwner=newH->owner1E8();
 Object *chosen=0;Object *place=0;
 if(first) {
  if(second) {
   if(((Rva00245BF0XP*)first->m_experienceTracker)->level() < ((Rva00245BF0XP*)second->m_experienceTracker)->level()) {
    place=secondPlace;TheGameLogic->destroyObject(first);chosen=second;
   } else {chosen=first;place=firstPlace;TheGameLogic->destroyObject(second);}
  } else {chosen=first;place=firstPlace;}
 } else if(second) {chosen=second;place=secondPlace;}
 int one=((Rva00245BF0XP*)object()->m_experienceTracker)->level();
 int two=((Rva00245BF0XP*)other->m_experienceTracker)->level();
 bool saved=field<bool>(TheGameLogic,0x90);
 field<bool>(TheGameLogic,0x90)=false;
 ((Rva00245BF0XP*)created->m_experienceTracker)->gainExpForLevel(std::max(one,two)-1,true,false);
 ((Rva00245BF0ObjectAPI*)created)->setAndNotify(field<int>(object(),0x370));
 if(chosen) {
  if(place) {
   LatchRestore<bool> latch(field<bool>(newOwner,0x210),true);
   ((Rva00245BF0Dispatch*)((char*)newOwner+0xe4))->add(chosen,place,true);
  } else TheGameLogic->destroyObject(chosen);
 }
 Rva00245BF0Dispatch *newSecondary=(Rva00245BF0Dispatch*)((char*)newOwner+0xe4);
 newSecondary->take(&list);
 field<bool>(TheGameLogic,0x90)=saved;
 if(((Rva00245BF0ObjectAPI*)other)->isKindOf(108))TheGameLogic->destroyObject(other);
 TheGameLogic->destroyObject(object());
 newSecondary->apply((const Rva00245BF0Mask*)created->m_objectUpgradesCompleted,false);
 return created;
}
