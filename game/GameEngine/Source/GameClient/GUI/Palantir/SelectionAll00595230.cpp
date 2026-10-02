// stlport
#include <list>
#include <hash_map>
#include "../../../Common/Thing/GameLogicObjectLookup.h"
// Retail RVA 0x00595230. The dump claimed 524 bytes but cuts add esp,0x14
// at +0x20B; that instruction ends at +0x20E and the ret makes 527 bytes.
// Address-derived owner: receiver+4 is the list sentinel and +8 the first
// 24-byte selection entry. Seventeen entries are examined. Object m_id +0x74,
// m_privateStatus +0x344 and Drawable m_object +0xFC are name-oracle witnesses.
// The shared GameLogic ABI fixes the hash buckets at this+0xB4/+0xB8.
// VC7.1 outlines the first lookup and inlines the second, exactly as retail.
// This TU owns the byte-verified 82-byte lookup at RVA 0x0009A510.
struct Coord3D;
class Object;
class Drawable;
struct Node00595230 { Node00595230 *next,*prev; Drawable *value; };
typedef std::list<Drawable *> List00595230;
class GameMessage { public: void appendBooleanArgument(bool); void appendObjectIDArgument(unsigned); };
// Zero Hour GameLogic.h preserves this older BFME hash-map body in a comment.
// Inline linkage lets identical caller-visible copies coalesce at link time.
inline Object *GameLogic::findObjectByID(int id) {
 if(id==0) return 0;
 ObjectPtrHash::iterator it=m_objHash.find(id);
 if(it==m_objHash.end()) return 0;
 return (*it).second;
}
extern GameLogic *TheGameLogic;
class Object { public:
bool isMassSelectable() const;
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
virtual Drawable *getDrawable();
};
class InGameUI { public:
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
virtual void select(Drawable *);
virtual void deselect(Drawable *);
virtual void clear();
virtual void slot59();
virtual void slot60();
virtual void slot61();
virtual void slot62();
virtual const List00595230 *getSelected();
};
class MessageStream { public:
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
virtual GameMessage *append(int);
};
class View { public:
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
virtual void lookAt(const Coord3D *);
};
extern InGameUI *TheInGameUI;
extern MessageStream *TheMessageStream;
extern View *TheTacticalView;
enum KindOfType;
class Thing { public: bool isKindOf(KindOfType) const; };
void j_00001c03();
void j_00014c6d();
class BFMERopeDrawable { public: const Coord3D *getPosition() const; };
typedef bool (__fastcall *Predicate00595230)(Object *);
typedef bool (__fastcall *Kind00595230)(Object *,int);
typedef unsigned (__fastcall *Size00595230)(const List00595230 *);
typedef const Coord3D *(__fastcall *Position00595230)(Drawable *);
inline Object *link00595230(Object *p) { return *(Object **)((char*)p+0x214); }
inline unsigned id00595230(Object *p) { return *(unsigned *)((char*)p+0x74); }
struct Entry00595230 { Node00595230 *node; char rest[20]; };
class SelectionTable00595230 { public:
 void invoke();
 unsigned field_0; Node00595230 *field_4; Entry00595230 entries[17];
};

void SelectionTable00595230::invoke()
{
 bool clear=!*((bool*)TheInGameUI+0x12b3);
 int last=0;
 for(int index=0;index<17;++index) {
  Node00595230 *node=entries[index].node;
  if(node!=field_4) {
   Object *object=TheGameLogic->findObjectByID((int)node->value);
   if(object && object->isMassSelectable() && !(*((unsigned char*)object+0x344)&1) && object->getDrawable()) {
    if(clear || !*((bool*)object->getDrawable()+0x3ac)) last=index;
   }
  }
 }
 for(int index=0;index<last+1;++index) {
  Node00595230 *node=entries[index].node;
  if(node==field_4) continue;
  Object *object=TheGameLogic->findObjectByID((int)node->value);
  if(!object || !object->isMassSelectable() || (*((unsigned char*)object+0x344)&1)) continue;
  Drawable *drawable=object->getDrawable();
  if(!drawable || (!clear && *((bool*)drawable+0x3ac))) continue;
  Object *owner=*(Object**)((char*)drawable+0xfc);
  if(owner) {
   Object *other=link00595230(owner);
   if(other && ((Thing*)other)->isKindOf((KindOfType)108)) {
    object=other;drawable=other->getDrawable();
   }
  }
  if(clear) TheInGameUI->clear();
  GameMessage *message=TheMessageStream->append(index!=last ? 1002 : 1001);
  message->appendBooleanArgument(clear);
  message->appendObjectIDArgument(id00595230(object));
  TheInGameUI->select(drawable);
  clear=false;
 }
}
