// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// Retail 0x00215930 is a two-argument completion callback entered on a
// secondary interface at owner+0x10. The semantic owner is not established.
// Owner-0x10 uses the existing BfmeOwnFCB receiver; -8 holds Object and -0xC
// holds the data block whose +0x48 field supplies the optional FXList.
// Keep the clear-flags wrapper inline: retail constructs its three-bit mask
// before constructing the empty set mask. The raw BfmeThingVKP signature is
// retained from the existing callee claim; its two ints carry mask addresses.
// stlport
#include <bitset>
template<int N> class BitFlags { _STL::bitset<N> bits; public:
 enum BogusInitType { kInit=0 };
 BitFlags() {}
 BitFlags(BogusInitType,int,int,int);
 BitFlags(BogusInitType,int i) { bits.set(i); }
};
class Object { public: void setStatus(const BitFlags<86>&,bool); };
class BfmeThingVKP { public: void bfmeSetVKP(int,int);
 void clear(const BitFlags<304>& flags) { bfmeSetVKP((int)&flags,(int)&BitFlags<304>()); } };
class FXList { public: bool bfmeIsBlocked(); void doFXObj(const Object *,const Object *) const; };
class BfmeOwnFCB { public:
 void bfmeAfterFCB();
 void refreshRva00215650();
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
 base->refreshRva00215650();
 float value=base->value54();
 if (value == value18()) {
  ((BfmeThingVKP *)object())->clear(BitFlags<304>(BitFlags<304>::kInit,0x42,0x43,0x44));
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
