// Retail 00594D60: selection-table action with one index argument (ret 4).
// The old Gen00594D60::handle() pin declares no argument and is not the ABI.
// Address-derived identity; 17 slots of 24 bytes start at +8, sentinel at +4.
// Object+74 is witnessed m_id; Drawable+FC is witnessed m_object.
// Object+214 and InGameUI+12B3 are observed here but remain unnamed by the oracle.
// The conditional pointer update and direct UI-global expressions preserve
// VC7.1 saved-register allocation. Native STLport list::size is the retail helper.
// stlport
#include <list>
// Address-derived selection-table method. Retail ends in ret 4.
struct Coord3D;
class Object;
class Drawable;
struct Node00594D60 { Node00594D60 *next,*prev; unsigned value; };
typedef std::list<Drawable *> List00594D60;
class GameMessage { public: void appendBooleanArgument(bool); void appendObjectIDArgument(unsigned); };
class GameLogic { public: Object *findObjectByID(int); };
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
virtual const List00594D60 *getSelected();
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
class BfmeThingAIA { public: bool bfmeAskAIA(int); };
class BFMERopeDrawable { public: const Coord3D *getPosition() const; };
inline Object *link00594D60(Object *p) { return *(Object **)((char*)p+0x214); }
inline unsigned id00594D60(Object *p) { return *(unsigned *)((char*)p+0x74); }
struct Entry00594D60 { Node00594D60 *node; char rest[20]; };
class SelectionTable00594D60 { public:
 void invoke(int index);
 unsigned field_0; Node00594D60 *field_4; Entry00594D60 entries[17];
};
void SelectionTable00594D60::invoke(int index)
{
 if(index<0 || index>=17) return;
 Node00594D60 *node=entries[index].node;
 if(node==field_4) return;
 Object *object=TheGameLogic->findObjectByID((int)node->value);
 if(!object) return;
 if(((BfmeThingAIA*)object)->bfmeAskAIA(89)) object=link00594D60(object)?link00594D60(object):object;
 if(!object || !object->isMassSelectable()) return;
 Drawable *drawable=object->getDrawable();
 if(!drawable) return;
 Object *owner=*(Object **)((char*)drawable+0xfc);
 if(owner) {
  Object *other=link00594D60(owner);
  if(other && ((BfmeThingAIA*)other)->bfmeAskAIA(108)) {
   object=other; drawable=other->getDrawable();
  }
 }
 const List00594D60 *list=TheInGameUI->getSelected();

 if(*((bool*)TheInGameUI+0x12b3) && list->size()!=0 &&
    (list->size()!=1 || list->front()!=drawable)) {
  bool found=false;
  for(List00594D60::const_iterator it=list->begin(); it!=list->end() && !found;) {
   if(*it==drawable) found=true; else ++it;
  }
  if(found) {
   GameMessage *msg=TheMessageStream->append(1004);
   msg->appendObjectIDArgument(id00594D60(object));
   TheInGameUI->deselect(drawable);
  } else {
   GameMessage *msg=TheMessageStream->append(1001);
   msg->appendBooleanArgument(false);
   msg->appendObjectIDArgument(id00594D60(object));
   TheInGameUI->select(drawable);
  }
 } else if(list->size()==1 && list->front()==drawable) {
  TheTacticalView->lookAt(((BFMERopeDrawable*)drawable)->getPosition());
 } else {
  TheInGameUI->clear();
  GameMessage *msg=TheMessageStream->append(1001);
  msg->appendBooleanArgument(true);
  msg->appendObjectIDArgument(id00594D60(object));
  TheInGameUI->select(drawable);
 }
}
