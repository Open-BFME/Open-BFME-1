// ?replaceModelConditionState@Rva0076B980View@@QAEXABV?$BitFlags@$0BDA@@@_NH@Z
// partial score=0.1595 date=2026-10-03
// cl: /D_STLP_USE_STATIC_LIB /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Complete draft of retail 0076B980..0076BD39 (RET12 at 76BD36).
// Owner/method evidence: identity_evidence/0076b980-scriptedmodel-condition.md.
// The named native implementation has the secondary receiver at owner+0x0C;
// this address-qualified view describes only that adjusted ABI, not a new owner.
// Native BitFlags<304>: ten words; flip clears the last high 16 bits at 76BA69.
// 2026-10-03: 960/953 bytes, 787 differing bytes, 11 relocation-layout drifts,
// measured quality 0.1595; normalized shape 0.964. Not an exact reconstruction.
// The first mask scan reserves EDX rather than EBX; the input is cached in EBX
// too early, changing the two copy/flip schedules. A nullable-mask accessor
// instead gives 967B/776 differences and shape0.989, leaving an extra null test
// and loop pad; assuming the reference nonnull restores this 960-byte result.
// Callee-visibility and a named mask reference do not change this draft.
// Lookup 765B70: incoming ECX receiver, one flags reference, RET4; scans 0x128
// records through data+18/+1C with fallback index+4C. Lookup765DC0 similarly
// scans data+24/+28 in 0xBC strides with mask+4 and RET4 at765F40.
// This avoids the historical false stdcall helper label. All calls use decoded
// thunk routes; no pin or production row has been changed. The native equality
// specialization remains unbound and must resolve to the independently checked
// ten-word comparator1C2870 (RET4); ctor specialization uses existing1ED160 pin.
// The set field is a read-only tree-layout/iterator view, not a recovered native
// container identity: header+80, count+84 and four-byte key at node+10.
// The particle handle is the witnessed intrusive triple; 5C2240 clears three
// words and relinks owner+98/+9C, while5C1FB0 marks the systems for destruction.
#include "PreRTS.h"
#include "Common/BitFlags.h"
#include <set>

typedef BitFlags<304> Rva0076B980Flags;
template <> BitFlags<304>::BitFlags(BogusInitType, Int, Int, Int, Int, Int);
template <> Bool BitFlags<304>::operator!=(const BitFlags<304>&) const;

struct Rva0076B980Call {
 void andFlags(const Rva0076B980Flags*);
 void drawableFlags(const Rva0076B980Flags&, const Rva0076B980Flags&);
 void *lookup(const Rva0076B980Flags&) const;
 void noArgs();
 bool select(const void*, bool, int);
};
extern void j_00047a73();
extern void j_0002ec35();
extern void j_00005024();
extern void j_0000ce5f();
extern void j_0000e525();
extern void j_00015640();
extern void j_000418e9();
extern void j_00001b18();

template<class T> static __forceinline T rva0076B980Member(void (*p)()) {
 union { void (*raw)(); T member; } u;
 typedef char Check[sizeof(T)==sizeof(p)?1:-1];
 u.raw=p; return u.member;
}
static __forceinline void rva0076B980And(Rva0076B980Flags& f, const Rva0076B980Flags& g) {
 typedef void(Rva0076B980Call::*M)(const Rva0076B980Flags*);
 ((Rva0076B980Call*)&f->*rva0076B980Member<M>(j_00047a73))(&g);
}
static __forceinline void rva0076B980InlineAnd(Rva0076B980Flags& f,const Rva0076B980Flags& g) {
 *(std::bitset<304>*)&f &= *(const std::bitset<304>*)&g;
}
struct Rva0076B980Data {
 unsigned char pad0[0xb4];
 Rva0076B980Flags flags;
 unsigned char padDC[0x10b-0xdc];
 bool field10B;
 unsigned char pad10C[0x133-0x10c];
 bool field133;
 void *lookup(const Rva0076B980Flags& c, void(*target)()) const {
  typedef void*(Rva0076B980Call::*M)(const Rva0076B980Flags&) const;
  return ((const Rva0076B980Call*)this->*rva0076B980Member<M>(target))(c);
 }
};
struct Rva0076B980Handle {
 void* pointer;
 void* next;
 void* prev;
 void* get() const {
  typedef void*(__cdecl *F)();
  return pointer ? pointer : ((F)j_00001b18)();
 }
 void unlink() {
  typedef void(Rva0076B980Call::*M)();
  ((Rva0076B980Call*)this->*rva0076B980Member<M>(j_00015640))();
 }
};
template<int N> class Rva0076B980Slots: public Rva0076B980Slots<N-1> {public: virtual void slot(char (*)[N])=0;};
template<> class Rva0076B980Slots<0> {};
struct Rva0076B980Client: Rva0076B980Slots<11> {virtual void* lookup(unsigned)=0;};
class GameClient;
extern GameClient *TheGameClient;
struct Rva0076B980Primary: Rva0076B980Slots<61> {virtual void slotF4(void*,bool,void*)=0;};
class Rva0076B980View {
public:
 void replaceModelConditionState(const Rva0076B980Flags&,bool,int);
 unsigned char pad0[8];
 void *field08;
 Rva0076B980Handle field0C;
 unsigned char pad18[0x58-0x18];
 bool field58;
 unsigned char pad59[0x80-0x59];
 std::set<unsigned> field7C;
 unsigned char pad8C[0x94-0x8c];
 void *field94;
 unsigned char pad98[0x13c-0x98];
 Rva0076B980Flags field13C;
 unsigned char pad164[3];
 bool field167;
 void *field168;
 unsigned char pad16C[0x224-0x16c];
 bool field224;
 Rva0076B980Data* data() const {return *(Rva0076B980Data**)((char*)this-8);}
 Rva0076B980Primary* primary() {return (Rva0076B980Primary*)((char*)this-12);}
};

static __forceinline bool rva0076B980Any(const Rva0076B980Flags& flags) {
 const unsigned *words=(const unsigned*)&flags;
 for(unsigned i=0;i<10;++i) if(words[i]) return true;
 return false;
}
void Rva0076B980View::replaceModelConditionState(const Rva0076B980Flags& c,bool force,int arg3)
{
 const Rva0076B980Data *module=data();
 if(module->field133 && field94) return;
 if(rva0076B980Any(module->flags) && !field7C.empty()) {
  Rva0076B980Flags set=c;
  rva0076B980And(set,module->flags);
  Rva0076B980Flags clear=c;
  clear.flip();
  rva0076B980And(clear,module->flags);
  for(std::set<unsigned>::iterator it=field7C.begin(); it!=field7C.end(); ++it) {
   void* drawable=((Rva0076B980Client*)TheGameClient)->lookup(*it);
   if(drawable) {
    typedef void(Rva0076B980Call::*M)(const Rva0076B980Flags&,const Rva0076B980Flags&);
    ((Rva0076B980Call*)drawable->*rva0076B980Member<M>(j_0002ec35))(clear,set);
   }
  }
 }
 void *effect=data()->lookup(c,j_00005024);
 bool changed=force;
 if(!changed && module->field10B) {
  Rva0076B980Flags mask(Rva0076B980Flags::kInit,3,4,5,7,8);
  Rva0076B980Flags old=field13C;
  rva0076B980InlineAnd(old,mask);
  Rva0076B980Flags current=c;
  rva0076B980InlineAnd(current,mask);
  if(current!=old) changed=true;
 }
 field13C=c;
 field58=!c.test(7);
 void *info=data()->lookup(c,j_0000ce5f);
 if(field167 && field08 && info==field168) info=field08;
 else {field167=false; field168=0;}
 if(!c.test(228) && field0C.pointer) {
  typedef void(Rva0076B980Call::*M)();
  ((Rva0076B980Call*)field0C.get()->*rva0076B980Member<M>(j_0000e525))();
  field0C.unlink();
 }
 if(effect) primary()->slotF4(effect,changed,info);
 if(info) {
  field224=false;
  typedef bool(Rva0076B980Call::*M)(const void*,bool,int);
  ((Rva0076B980Call*)primary()->*rva0076B980Member<M>(j_000418e9))(info,force,arg3);
 }
}
