// ?check@MemberTarget002439F0@@QAE_NPAVMember002439F0@@@Z
// partial score=0.6373 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <list>
// Retail 002439F0. Adjusted receiver and member/object offsets witnessed in retail.
extern void j_00043ced(); extern void j_0000faa6(); extern void j_0001f253();
extern void j_000261a2(); extern void j_000016a4(); extern void j_00006dcf();
extern void j_00024d70(); extern void j_0000e4a8();
class Member002439F0;
class BfmeSrcBT {public: float bfmeCalcBT(void *);};
class BfmeObjAS {public: BfmeObjAS *bfmeParentAS(int);};
class Object;
class AIUpdateInterface {public: Object *getCurrentVictim() const;};
class BFMEActionObject {public: bool testStatus(int) const;};
class Rva001B3FE0 {public: bool test() const;};
class BfmeOwnedD {public: void *bfmeDeleteSelf(unsigned);};

class Predicate002439F0 { public: bool test() const {
 union {void (*p)(); bool (Predicate002439F0::*m)() const;} c; c.p=j_00006dcf; return (this->*c.m)();
}};
template<int N> class Slots002439F0: public Slots002439F0<N-1> {public: virtual void unused(char (*)[N])=0;};
template<> class Slots002439F0<0> {};
class AI002439F0 { public:
 virtual void unused0()=0;
 virtual void unused1()=0;
 virtual void unused2()=0;
 virtual void unused3()=0;
 virtual void unused4()=0;
 virtual void unused5()=0;
 virtual void unused6()=0;
 virtual void unused7()=0;
 virtual void unused8()=0;
 virtual void unused9()=0;
 virtual void unused10()=0;
 virtual void unused11()=0;
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

 virtual bool slot184() const=0; virtual void slot188()=0; virtual bool slot18C() const=0;
 char pad004[0x140-4]; Predicate002439F0 *field140;
 Member002439F0 *victim() const {return (Member002439F0 *)((const AIUpdateInterface *)this)->getCurrentVictim();}
};
class Commands002439F0 { public: void idle(int source) {union {void (*p)();void (Commands002439F0::*m)(int);} c;c.p=j_00024d70;(this->*c.m)(source);} };
class Member002439F0 {public:
 char pad000[0x74]; int field074; int field078; char pad07C[0x94-0x7c]; unsigned field094;
 char pad098[0x204-0x98]; AI002439F0 *field204; char pad208[12]; Member002439F0 *field214;
 float distance(Member002439F0 *o) {return ((BfmeSrcBT *)this)->bfmeCalcBT(o);}
 Member002439F0 *parent(bool b) {return (Member002439F0 *)((BfmeObjAS *)this)->bfmeParentAS(b);}
 bool status(int i) const {return ((const BFMEActionObject *)this)->testStatus(i);}
 void action(bool b) {union {void (*p)();void (Member002439F0::*m)(bool);} c;c.p=j_0000e4a8;(this->*c.m)(b);}
};
class GameLogic {public: char pad000[0x3c]; unsigned frame;
 Member002439F0 *lookup(int id) {union {void (*p)();Member002439F0 *(GameLogic::*m)(int);} c;c.p=j_0001f253;return (this->*c.m)(id);}
};
extern GameLogic *TheGameLogic;
class MemberTarget002439F0 {public:
 virtual void unused0()=0;
 virtual void unused1()=0;
 virtual void unused2()=0;
 virtual void unused3()=0;
 virtual void unused4()=0;
 virtual void unused5()=0;
 virtual void unused6()=0;
 virtual void unused7()=0;
 virtual void unused8()=0;
 virtual void unused9()=0;
 virtual void unused10()=0;
 virtual void unused11()=0;
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

 virtual void slot134(Member002439F0 *)=0;
 char pad004[0x100-4]; int field100; unsigned field104;
 bool check(Member002439F0 *target);
};
bool MemberTarget002439F0::check(Member002439F0 *arg) {
 Member002439F0 *target=arg;
 if (!target) return false;
 bool close=target->distance(*(Member002439F0 **)((char *)this-0xdc))<10000.0f;
 int id=target->field074;
 Member002439F0 *parent=target->parent(false);
 if(parent) id=parent->field074;
 if ((target->field074==field100 || id==field100) && TheGameLogic->frame<field104) return true;
 Member002439F0 *container=target->field214;
 if(!container && (target->field094&0x20)) container=TheGameLogic->lookup(target->field078);
 _STL::list<Member002439F0 *> &members=*(_STL::list<Member002439F0 *> *)((char *)this-0xac);
 bool found=false;
 for(_STL::list<Member002439F0 *>::iterator it=members.begin();it!=members.end();++it) {
  Member002439F0 *member=*it;
  if(found) break;
  AI002439F0 *ai=member->field204;
  if(!ai) continue;
  if(ai->slot184()) {
   if(close) found=true;
   Member002439F0 *victim=ai->victim();
   if(victim) {
    if(victim==arg) found=true;
    Member002439F0 *victimContainer=victim->field214;
    if(victimContainer==arg) found=true;
    if(container) {
     if(!victimContainer && victim->status(37)) {
      victimContainer=TheGameLogic->lookup(victim->field078);
      if(victimContainer==container) found=true;
     }
     if(victimContainer==container) found=true;
    }
   }
  } else if(close) {
   if(ai->field140 && ai->field140->test()) continue;
   if(ai->slot18C()) ((Commands002439F0 *)((char *)ai+0x20))->idle(2);
   member->action(false);
   if(ai->slot184()) found=true;
  }
 }
 if(found) {slot134(arg);return true;}
 return false;
}
