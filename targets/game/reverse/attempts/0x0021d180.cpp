// ?rva0021d180@Rva0021D180Owner@@QAEXXZ
// partial score=0.792 date=2026-09-30
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source/GameLogic/Object
// stlport
#include <list>
#include "ObjectStatusBits.h"
class Rva0021D180Owner;
class Rva0021D180Hold {
public:
#define S(n) virtual void slot##n();
 S(00) S(01) S(02) S(03) S(04) S(05) S(06) S(07) S(08) S(09)
 S(10) S(11) S(12) S(13) S(14) S(15) S(16) S(17) S(18) S(19)
 S(20) S(21) S(22) S(23) S(24) S(25) S(26) S(27) S(28) S(29)
 S(30) S(31) S(32) S(33) S(34) S(35) S(36) S(37) S(38) S(39)
 S(40) S(41) S(42) S(43) S(44) S(45) S(46) S(47) S(48) S(49)
 S(50) S(51) S(52) S(53) S(54) S(55) S(56) S(57) S(58) S(59)
 S(60) S(61) S(62)
 virtual void slot63(void (*callback)(int,Rva0021D180Owner*),Rva0021D180Owner*,int);
};
class Rva0021D180Object {
public:
 void setStatus(const ObjectStatusMaskType&,bool);
 void handle(int);
 void* unidentified_001BFE20() const;
 char pad00[0x94];
 unsigned char flags94;
 char pad95[0x1fc-0x95];
 Rva0021D180Hold* hold;
 char pad200[0x214-0x200];
 unsigned int word214;
};
class Rva0021D180Tree {
public:
 void erase(Rva0021D180Object* const&);
 char storage[12];
};
class Rva0021D180Secondary {
public:
 S(s00) S(s01) S(s02) S(s03) S(s04) S(s05) S(s06) S(s07) S(s08) S(s09)
 S(s10) S(s11) S(s12) S(s13) S(s14) S(s15)
 virtual void slot40();
};
class Rva0021D180Owner {
public:
 S(p00) S(p01) S(p02) S(p03) S(p04) S(p05) S(p06) S(p07) S(p08) S(p09)
 S(p10) S(p11) S(p12) S(p13) S(p14) S(p15) S(p16) S(p17) S(p18) S(p19)
 S(p20) S(p21) S(p22) S(p23) S(p24) S(p25) S(p26) S(p27) S(p28)
 virtual void slot74(Rva0021D180Object*);
 void rva0021d180();
 void updateCount();
 char pad04[4];
 Rva0021D180Object* owner;
 char pad0c[0x20-0xc];
 Rva0021D180Secondary secondary;
 char pad24[0x38-0x24];
 _STL::list<Rva0021D180Object*> members;
 unsigned int count;
 char pad40[0x9bc-0x40];
 _STL::list<Rva0021D180Object*> other;
 unsigned int word9c0;
 Rva0021D180Tree tree;
 char pad9d0[8];
 bool flag9d8;
};
#undef S
void Rva0003BE1C(int,Rva0021D180Owner*);
void Rva0001FEA6(int,Rva0021D180Owner*);
#pragma comment(linker, "/alternatename:?setStatus@Rva0021D180Object@@QAEXABV?$BitFlags@$0FG@@@_N@Z=?j_000307e7@@YAXXZ")
#pragma comment(linker, "/alternatename:?handle@Rva0021D180Object@@QAEXH@Z=?j_000122ab@@YAXXZ")
#pragma comment(linker, "/alternatename:?unidentified_001BFE20@Rva0021D180Object@@QBEPAXXZ=?j_0000d3b9@@YAXXZ")
#pragma comment(linker, "/alternatename:?updateCount@Rva0021D180Owner@@QAEXXZ=?j_0001e385@@YAXXZ")
#pragma comment(linker, "/alternatename:?erase@Rva0021D180Tree@@QAEXABQAVRva0021D180Object@@@Z=?j_00004719@@YAXXZ")
#pragma comment(linker, "/alternatename:?Rva0003BE1C@@YAXHPAVRva0021D180Owner@@@Z=?j_0003be1c@@YAXXZ")
#pragma comment(linker, "/alternatename:?Rva0001FEA6@@YAXHPAVRva0021D180Owner@@@Z=?j_0001fea6@@YAXXZ")
void Rva0021D180Owner::rva0021d180() {
 owner->setStatus(MAKE_OBJECT_STATUS_MASK(35),false);
 if (members.empty()) {
  flag9d8=true;
  for (_STL::list<Rva0021D180Object*>::iterator it=other.begin();it!=other.end();) {
   Rva0021D180Object* obj=*it;
   ++it;
   obj->word214=0;
   slot74(obj);
   Rva0021D180Hold* hold=obj->hold;
   if (hold) {
    hold->slot63(&Rva0003BE1C,this,1);
    hold->slot63(&Rva0003BE1C,this,0x10);
   }
  }
  other.clear();
  flag9d8=false;
  count=members.size();
  updateCount();
  secondary.slot40();
 }
 for (_STL::list<Rva0021D180Object*>::iterator it=members.begin();it!=members.end();++it) {
  Rva0021D180Object* obj=*it;
  Rva0021D180Object* key=obj;
  obj->setStatus(MAKE_OBJECT_STATUS_MASK(36),false);
  obj->handle(9);
  Rva0021D180Hold* hold=obj->hold;
  if (hold) {
   if (obj->unidentified_001BFE20()) {
    hold->slot63(&Rva0001FEA6,this,1);
    hold->slot63(&Rva0001FEA6,this,0x10);
   }
  } else if (obj->flags94&0x20) continue;
  tree.erase(key);
 }
}
