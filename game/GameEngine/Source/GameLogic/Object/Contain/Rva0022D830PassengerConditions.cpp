// cl: /DNDEBUG /MD /EHsc
// stlport
#include <bitset>
// The empty kind-of mask is retail's global at 0x012ED8B8, which KindOf.cpp owns
// as `const BitFlags<192> KINDOFMASK_NONE`, so this TU names it with the
// canonical spelling (the template below mangles it as
// ?KINDOFMASK_NONE@@3V?$BitFlags@$0MA@@@B). The established Thing callee keeps
// BitFlags<116> in its ledger spelling, so the narrower reference below is the
// established cast.
template<int N> class BitFlags {
public:
 _STL::bitset<N> m_bits;
 bool any() const { return m_bits.any(); }
};
extern const BitFlags<192> KINDOFMASK_NONE;
class Thing { public: bool isKindOfMulti(const BitFlags<116>&, const BitFlags<116>&) const; };
class Object {
public:
 void notifyModelConditionChanged();
 char pad[0x110];
 struct Flags { unsigned bits[10]; unsigned test(int i) const { return bits[i>>5] & (1u<<(i&31)); } void set(int i) { bits[i>>5] |= (1u<<(i&31)); } } m_modelConditionFlags;
};
static __forceinline void setCondition(Object* o,int i) { if (!o->m_modelConditionFlags.test(i)) { o->m_modelConditionFlags.set(i); o->notifyModelConditionChanged(); } }
struct MaskData0022D830 { char pad[0x1b0]; BitFlags<192> mask1,mask2,mask3; };
// The receiver is the ContainModuleInterface subobject: retail loads module
// data at this-0x1c and owner at this-0x18 after virtual slot 55. The original
// BFME-only method name is unproved, so retain the RVA in the owner name.
// Data mask offsets 0x1b0/0x1c8/0x1e0 and six-word width come from retail.
// The established Thing callee uses BitFlags<116> in its ledger spelling;
// the reference casts preserve that ABI while storage is the BFME 192 bits.
// Object+0x110 is the witnessed 40-byte m_modelConditionFlags field.
class Rva0022D830 {
public:
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
 void applyPassengerConditions(Thing* passenger);
};
void Rva0022D830::applyPassengerConditions(Thing* passenger) {
 slot55();
 const MaskData0022D830* data=*(const MaskData0022D830**)((char*)this-0x1c);
 Object* owner=*(Object**)((char*)this-0x18);
 if (data->mask1.any() && passenger->isKindOfMulti((const BitFlags<116>&)data->mask1,(const BitFlags<116>&)KINDOFMASK_NONE)) setCondition(owner,18);
 else if (data->mask2.any() && passenger->isKindOfMulti((const BitFlags<116>&)data->mask2,(const BitFlags<116>&)KINDOFMASK_NONE)) setCondition(owner,19);
 else if (data->mask3.any() && passenger->isKindOfMulti((const BitFlags<116>&)data->mask3,(const BitFlags<116>&)KINDOFMASK_NONE)) setCondition(owner,20);
}
