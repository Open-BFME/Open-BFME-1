// ?method@Rva00373ED0@@QAEXXZ
// partial score=0.5107 date=2026-10-03
// ?method@Rva00373ED0@@QAEXXZ
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/sweep /Iinputs/reference/shims/stlp_nodealloc /Igame/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// Research bank only; no production row, callee pin, or vtable binding changed.
// Retail 00373ED0..00374305: complete 1077-byte body, RET at +434.
// Called by matched CastleBehavior update 00377740 through ILT00007969.
// Exact method identity remains unproved; keep the opaque address spelling.
// Ghidra plus raw retail decode: neutral name is PlyrCivilian; radius guard
// is <=0 (NaN continues); 32 scores; relationship test 2; capture argument 2.
// Probe: 1079 bytes, 523 differing non-relocation bytes, quality .5107;
// instruction-shape .951 is diagnostic only, not the bank's byte score.
// Progress: select vector size_type overload to inline 32 stores; visible
// noinline mask-copy constructors permit 24-byte temporary reuse (frame B0).
// Native aggregate Coord3D copy regresses to 753 differing bytes; keep the
// three scalar assignments. Const player and direct fill loop do not help.
// Remaining: filter temporary evaluation order, local stack slots and tree
// insertion aliasing; then independently validate all DIR32, vtables and EH.
// Current generated filter tables/root methods are UNBOUND research views,
// never approved replacements for the native tables 01083B80/01083B5C.
// Constructor copies follow VptrZeroPrefixBlockCtors.cpp; their complete
// emitted bodies and the existing opaque set contracts still need auditing.
// Retail EH has nine states: cleanup C1A9E0/Eb/F3/FB/C1AA06/11; the set
// exceptional cleanup routes through ILT10FFF to 00370720, whereas the normal
// cleanup uses ILT22F11 to 0036EA80. Do not accept masked parent bytes alone.
#define _STLP_NO_EXCEPTIONS 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include <set>
#include "Lib/BaseType.h"
#include "Common/BitFlags.h"
template<> __forceinline BitFlags<192>::BitFlags(BogusInitType,Int a,Int b,Int c,Int d) {m_bits.set(a);m_bits.set(b);m_bits.set(c);m_bits.set(d);}
template<> __forceinline std::vector<int>::vector(size_type n,const int &v,const allocator_type &a):_Vector_base<int,allocator_type>(n,a){int *p=this->_M_start; for(size_type i=n;i>0;--i,++p)*p=v;this->_M_finish=p;}
#define BFME_HAVE_COORD3D
#include "GameLogic/Object/object.h"
#include "Common/Overridable.h"
class Player;
class PlayerList;
class NameKeyGenerator;
class PartitionManager;
class GameLogic;
extern PlayerList *ThePlayerList;
extern NameKeyGenerator *TheNameKeyGenerator;
extern PartitionManager *ThePartitionManager;
extern GameLogic *TheGameLogic;
extern const BitFlags<192> KINDOFMASK_NONE;
extern void j_00019e34();
extern void j_0003add7();
extern void j_0002f586();
extern void j_0000fc45();
extern void j_00022f11();
extern void j_00045def();
extern void j_00020824();
extern void j_0003e77a();
extern void j_00044f30();
extern void j_000089f9();
extern void j_00025806();
extern void j_0002ae5f();
extern void j_0001909c();
extern void j_000022bb();
extern void d_009f2ae0();
class __single_inheritance Rva00373ED0Calls {};
template<class R> __forceinline R call0(void(*p)(),const void *self) {
 typedef R(Rva00373ED0Calls::*M)(); union{void(*p)();M m;} u;u.p=p;
 return (((Rva00373ED0Calls*)self)->*u.m)();
}
template<class R,class A> __forceinline R call1(void(*p)(),const void *self,A a) {
 typedef R(Rva00373ED0Calls::*M)(A); union{void(*p)();M m;} u;u.p=p;
 return (((Rva00373ED0Calls*)self)->*u.m)(a);
}
template<class R,class A,class B> __forceinline R call2(void(*p)(),const void *self,A a,B b) {
 typedef R(Rva00373ED0Calls::*M)(A,B); union{void(*p)();M m;} u;u.p=p;
 return (((Rva00373ED0Calls*)self)->*u.m)(a,b);
}
// BFME filter layout differs from the reference ZH interface: three slots,
// including destruction, plus a linked successor at +4. These are ABI views.
class Rva00373ED0Filter {
public:
 Rva00373ED0Filter():next(0){}
 virtual ~Rva00373ED0Filter(){}
 virtual bool allow(Object*)=0;
 virtual int playerMask();
 Rva00373ED0Filter *link(Rva00373ED0Filter *p) {return call1<Rva00373ED0Filter*>(d_009f2ae0,this,p);}
 Rva00373ED0Filter *next;
};
class Rva00373ED0RootFilter:public Rva00373ED0Filter {
public:
 virtual ~Rva00373ED0RootFilter(){}
 virtual bool allow(Object*);
};
struct VptrZeroBlock24 {unsigned w00,w04,w08,w0c,w10,w14;};
class Rva00251980VptrZeroBlockObject:public Rva00373ED0Filter {
public:
 __declspec(noinline) Rva00251980VptrZeroBlockObject(const VptrZeroBlock24 &p):words(p){}
 virtual ~Rva00251980VptrZeroBlockObject(){}
 virtual bool allow(Object*);
 VptrZeroBlock24 words;
};
class Rva00160BE0VptrZeroBlockObject:public Rva00373ED0Filter {
public:
 __declspec(noinline) Rva00160BE0VptrZeroBlockObject(const VptrZeroBlock24 &a,const VptrZeroBlock24 &b):first(a),second(b){}
 virtual ~Rva00160BE0VptrZeroBlockObject(){}
 virtual bool allow(Object*);
 VptrZeroBlock24 first,second;
};
struct Rva00373ED0Entry {Object *object; unsigned word;};
struct Rva00373ED0ResultData {
 std::vector<Rva00373ED0Entry> entries;
 Rva00373ED0Entry *current;
 int references;
};
struct BfmeWideResult {
 Rva00373ED0ResultData *value;
 BfmeWideResult();
 BfmeWideResult(const BfmeWideResult &);
 ~BfmeWideResult(){if(--value->references==0)delete value;}
 Object *nextObject(){if(value->current==value->entries.end())return 0;return (value->current++)->object;}
};
class BfmeWideForwardC {public:BfmeWideResult bfmeForwardWideC(int,int,int,int,int);};
// Out-of-line tree lifetime/insert follow the exact retail ILTs. Native
// iterator access uses the STLport representation; no guessed template pin.
struct Rva00373ED0Seen {
 typedef std::set<Player*> Set;
 typedef Set::iterator iterator;
 char storage[sizeof(Set)];
 Rva00373ED0Seen(){call0<void>(j_0000fc45,this);}
 ~Rva00373ED0Seen(){call0<void>(j_00022f11,this);}
 iterator begin(){return ((Set*)storage)->begin();}
 iterator end(){return ((Set*)storage)->end();}
 void insert(Player *const &p){call1<std::pair<iterator,bool>,Player *const &>(j_00045def,this,p);}
};
struct Rva00373ED0Data {char prefix[0x34];float radius34;};
struct Rva00373ED0 {
 void method();
 void *vptr;
 Rva00373ED0Data *data;
 Object *object;
};
static Team *rva00373ED0Team(Player *p){return *(Team**)((char*)p+0x230);}
static int rva00373ED0Index(Player *p){return *(int*)((char*)p+0x24);}
static int rva00373ED0Weight(Player *p){return (*(int*)((char*)p+0x2c)==0)+1;}
void Rva00373ED0::method(){
 if(!call1<bool>(j_00019e34,this,false))return;
 Object *owner=object;
 if(!owner)return;
 Player *neutral=call1<Player*>(j_0002f586,ThePlayerList,call1<int>(j_0003add7,TheNameKeyGenerator,(const char*)"PlyrCivilian"));
 Rva00373ED0Data *moduleData=data;
 if(moduleData->radius34<=0.0f)return;
 {
  Coord3D position;
  position.x=owner->m_cachedPos.x;
  position.y=owner->m_cachedPos.y;
  position.z=owner->m_cachedPos.z;
  BfmeWideResult objects=((BfmeWideForwardC*)ThePartitionManager)->bfmeForwardWideC((int)&position,*(int*)&moduleData->radius34,0,
   (int)Rva00160BE0VptrZeroBlockObject((const VptrZeroBlock24&)BitFlags<192>(BitFlags<192>::kInit,126),(const VptrZeroBlock24&)KINDOFMASK_NONE).link(
    Rva00251980VptrZeroBlockObject((const VptrZeroBlock24&)BitFlags<192>(BitFlags<192>::kInit,8,9,10,11)).link(&Rva00373ED0RootFilter())),0);
  std::vector<int> scores((std::vector<int>::size_type)32,-1);
  Rva00373ED0Seen seen;
  bool contested=false;
  Object *candidate;
  while((candidate=objects.nextObject())!=0){
   Player *player=call0<Player*>(j_00020824,candidate);
   if(player==neutral)continue;
   for(Rva00373ED0Seen::iterator it=seen.begin();it!=seen.end();++it){
    if(call1<int>(j_0003e77a,player,(const Team*)rva00373ED0Team(*it))!=2){contested=true;break;}
   }
   seen.insert(player);
   int index=rva00373ED0Index(player);
   int weight=rva00373ED0Weight(player);
   if(scores[index]<0)scores[index]=weight;
   scores[index]+=weight;
   const Overridable *t=(const Overridable*)candidate->m_template;
   if(t && t->getNextOverride())t=call0<const Overridable*>(j_000022bb,t->getNextOverride());
   scores[index]+=*(int*)((char*)t+0x4b4)*weight;
  }
  int bestScore=-1,bestIndex=-1;
  for(int i=0;i<32;++i)if(scores[i]>bestScore){bestScore=scores[i];bestIndex=i;}
  Player *winner;
  Team *team;
  if(bestIndex!=-1 && (winner=call1<Player*>(j_00044f30,ThePlayerList,bestIndex))!=0 && !contested){
   team=rva00373ED0Team(winner);
   if(team!=owner->m_team && call2<bool>(j_000089f9,this,winner,2))goto capture;
  }else if(*(unsigned*)((char*)TheGameLogic+0x3c)>5 && neutral && neutral!=call0<Player*>(j_00020824,owner) && (team=rva00373ED0Team(neutral))!=0){
   capture:
   owner->setTeam(team);
   call0<void>(j_00025806,owner);
   call0<void>(j_0002ae5f,owner);
   call0<void>(j_0001909c,owner);
  }
 }
}
