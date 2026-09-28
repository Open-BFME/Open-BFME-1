// ?finish@BfmeRvaB7E0Owner@@QAEXPAVBfmeRvaB7E0Object@@_N@Z
// partial score=0.37 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include <map>
#include "ascii_string.h"
class Drawable0022ED10 {
public:
 unsigned getID() const;
 void add(unsigned); void remove(unsigned); void show(unsigned,AsciiString); void flag(bool);
};
#pragma comment(linker, "/alternatename:?getID@Drawable0022ED10@@QBEIXZ=?j_00009b01@@YAXXZ")
#pragma comment(linker, "/alternatename:?add@Drawable0022ED10@@QAEXI@Z=?j_00030d37@@YAXXZ")
#pragma comment(linker, "/alternatename:?remove@Drawable0022ED10@@QAEXI@Z=?j_00011cfc@@YAXXZ")
#pragma comment(linker, "/alternatename:?show@Drawable0022ED10@@QAEXIVAsciiString@@@Z=?j_000418e4@@YAXXZ")
#pragma comment(linker, "/alternatename:?flag@Drawable0022ED10@@QAEX_N@Z=?j_00008337@@YAXXZ")
typedef std::map<int,AsciiString> Map0022ED10;
class BfmeRvaB7E0Object { public:
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
virtual Drawable0022ED10* drawable();
 char pad004[0x70]; int m_id; char pad078[0x1c]; unsigned flags094;
};
class BfmeRvaB7E0Owner { public: void finish(BfmeRvaB7E0Object* object,bool flag); };
void BfmeRvaB7E0Owner::finish(BfmeRvaB7E0Object* object,bool flag) {
 if(!object) return;
 Drawable0022ED10* rider=object->drawable();
 if(!rider) return;
 Drawable0022ED10* owner=(*(BfmeRvaB7E0Object**)((char*)this-0x18))->drawable();
 if(!owner) return;
 if(!(object->flags094 & 0x10000000)) {
  if(flag) owner->add(rider->getID()); else owner->remove(rider->getID());
  unsigned id=object->m_id;
  Map0022ED10* map=(Map0022ED10*)((char*)this+0x20);
  Map0022ED10::iterator it=map->find(id);
  if(it != map->end()) rider->show(owner->getID(),(*map)[id]);
  else rider->show(owner->getID(),AsciiString("FIREPOINT01"));
 }
 rider->flag(flag);
}

