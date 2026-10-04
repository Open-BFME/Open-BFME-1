// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// Retail 0x00215930 is a two-argument completion callback entered on a
// secondary interface at owner+0x10. The semantic owner is not established.
// Owner-0x10 uses the existing BfmeOwnFCB receiver; -8 holds Object and -0xC
// holds the data block whose +0x48 field supplies the optional FXList.
// The inline clear-flags wrapper passes two ten-word masks to Object.
// stlport
#include <bitset>
template<int N> class BitFlags { _STL::bitset<N> bits; public:
 enum BogusInitType { kInit=0 };
 BitFlags() {}
 BitFlags(BogusInitType,int,int,int);
 BitFlags(BogusInitType,int i) { bits.set(i); }
};
class Object { public:
 void setStatus(const BitFlags<86>&,bool);
 void clearAndSetModelConditionFlags(const BitFlags<320>&,const BitFlags<320>&);
 void clear(const BitFlags<304>& flags) {
  clearAndSetModelConditionFlags((const BitFlags<320>&)flags,(const BitFlags<320>&)BitFlags<304>());
 }
};
class FXList { public: bool bfmeIsBlocked(); void doFXObj(const Object *,const Object *) const; };
class BfmeOwnFCB { public:
 void bfmeAfterFCB();
 virtual void pad00();
 virtual void pad04();
 virtual void pad08();
 virtual void pad0C();
 virtual void pad10();
 virtual void pad14();
 virtual void pad18();
 virtual void pad1C();
 virtual void pad20();
 virtual void pad24();
 virtual void pad28();
 virtual void pad2C();
 virtual void pad30();
 virtual void pad34();
 virtual void pad38();
 virtual void pad3C();
 virtual void pad40();
 virtual void pad44();
 virtual void pad48();
 virtual void pad4C();
 virtual void pad50();
 virtual float value54();
};
extern void j_00032c54();
typedef void (BfmeOwnFCB::*Refresh215650)();
struct FxData215930 { char bytes[0x48]; FXList *fx; };
class Completion215930 { public:
 virtual void pad00();
 virtual void pad04();
 virtual void pad08();
 virtual void pad0C();
 virtual void pad10();
 virtual void pad14();
 virtual float value18();

 void complete(int unused,bool play);
 Object *object() { return *(Object **)((char *)this-8); }
};
void Completion215930::complete(int unused,bool play)
{
 BfmeOwnFCB *base=(BfmeOwnFCB *)((char *)this-0x10);
 base->bfmeAfterFCB();
 union { void (*fn)(); Refresh215650 call; } refresh={j_00032c54};
 (base->*refresh.call)();
 float value=base->value54();
 if (value == value18()) {
  object()->clear(BitFlags<304>(BitFlags<304>::kInit,0x42,0x43,0x44));
  object()->setStatus(BitFlags<86>(BitFlags<86>::kInit,2),false);
  object()->setStatus(BitFlags<86>(BitFlags<86>::kInit,21),false);
 }
 if (play) {
  FXList *fx=(*(FxData215930 **)((char *)this-0xc))->fx;
  if (fx) {
   Object *obj=object();
   if (!fx->bfmeIsBlocked()) fx->doFXObj(obj,0);
  }
 }
}
