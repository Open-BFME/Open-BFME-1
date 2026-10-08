// ?method@Rva002DBD20@@UAE_NPAVRva002DBD20Weapon@@PAVObject@@@Z
// partial score=0.6341 date=2026-10-08
// cl: /O2 /Ob2 /DNDEBUG /DWIN32 /MD /EHs-c- /Igame/GameEngine/Source/GameLogic/Object /Igame/GameEngine/Source/Common/Thing

// stlport
// Retail table 0x010CE9CC slot 1 reaches this 399-byte Boolean query.
#include <algorithm>
#undef min
struct Rva002DB3F0Vec6 { int v[6]; bool notEquals(const Rva002DB3F0Vec6*) const; };
extern "C" const Rva002DB3F0Vec6 __identifier("?KINDOFMASK_NONE@@3V?$BitFlags@$0MA@@@B");
#define NONE __identifier("?KINDOFMASK_NONE@@3V?$BitFlags@$0MA@@@B")
struct Rva002DBD20DamageInput {
 void* m_vptr; int m_04; unsigned short m_08; unsigned short m_pad0a;
 int m_0c, m_10, m_14; float m_18; unsigned char m_1c, m_1d, m_pad1e[2];
 float m_20; int m_24; unsigned int m_unread28[8];
};
struct Rva002DBD20DamageOutput { void* m_vptr; float m_04, m_08; bool m_0c; };
class DamageInfo { public: DamageInfo(); void* m_vptr; Rva002DBD20DamageInput in; Rva002DBD20DamageOutput out; };
typedef char Rva002DBD20DamageSize[sizeof(DamageInfo)==0x5c?1:-1];


class Object;
#define BFME_GAMELOGIC_LOOKUP_VISIBLE
#include "GameLogicObjectLookup.h"
extern GameLogic* TheGameLogic;
class Rva002DF120 { public: unsigned char test(void*,void*); };
class Rva003679D0FrameDeadline { public: unsigned char isPending(int) const; };
class Rva002DBD20Calls {};
class Rva002DBD20Weapon;
extern void j_000384f6();
extern void j_0003dccb();
extern void j_00043fae();
extern void j_0000c176();
template<class F> __forceinline F route(void (*raw)()) { union { void (*raw)(); F member; } f; f.raw=raw; return f.member; }
class ContainModuleInterface { public:
 virtual void slot0()=0;
 virtual void slot1()=0;
 virtual void slot2()=0;
 virtual void slot3()=0;
 virtual void slot4()=0;
 virtual void slot5()=0;
 virtual void slot6()=0;
 virtual void slot7()=0;
 virtual void slot8()=0;
 virtual void slot9()=0;
 virtual void slot10()=0;
 virtual void slot11()=0;
 virtual void slot12()=0;
 virtual void slot13()=0;
 virtual void slot14()=0;
 virtual void slot15()=0;
 virtual void slot16()=0;
 virtual void slot17()=0;
 virtual void slot18()=0;
 virtual void slot19()=0;
 virtual void slot20()=0;
 virtual void slot21()=0;
 virtual void slot22()=0;
 virtual void slot23()=0;
 virtual void slot24()=0;
 virtual void slot25()=0;
 virtual void slot26()=0;
 virtual void slot27()=0;
 virtual void slot28()=0;
 virtual void slot29()=0;
 virtual void slot30()=0;
 virtual void slot31()=0;
 virtual void slot32()=0;
 virtual void slot33()=0;
 virtual void slot34()=0;
 virtual void slot35()=0;
 virtual void slot36()=0;
 virtual void slot37()=0;
 virtual void slot38()=0;
 virtual void slot39()=0;
 virtual void slot40()=0;
 virtual void slot41()=0;
 virtual void slot42()=0;
 virtual void slot43()=0;
 virtual void slot44()=0;
 virtual void slot45()=0;
 virtual void slot46()=0;
 virtual void slot47()=0;
 virtual void slot48()=0;
 virtual void slot49()=0;
 virtual void slot50()=0;
 virtual void slot51()=0;
 virtual void slot52()=0;
 virtual void slot53()=0;
 virtual void slot54()=0;
 virtual void slot55()=0;
 virtual void slot56()=0;
 virtual void slot57()=0;
 virtual void slot58()=0;
 virtual void slot59()=0;
 virtual void slot60()=0;
 virtual void slot61()=0;
 virtual void slot62()=0;
 virtual void slot63()=0;
 virtual void slot64()=0;
 virtual void slot65()=0;
 virtual const Rva002DBD20Calls* members()=0;
};
class AttributeModifierPoolUpdate;
class Rva002DBD20;
#define OBJECT_TU_MEMBERS public: __forceinline ContainModuleInterface* getContain() const { return m_contain; } private: AttributeModifierPoolUpdate* findAttributeModifierPoolUpdate() const; friend class Rva002DBD20;
#include "object.h"
class Rva002DBD20WeaponTemplate { public: char m_pad00[0x508]; bool m_508; unsigned char m_509; };
class Rva002DBD20Weapon { public: void* m_vptr; Rva002DBD20WeaponTemplate* m_template; int m_sourceID; };
class Rva002DBD20 { public:
 virtual void slot0()=0;
 virtual bool method(Rva002DBD20Weapon*,Object*);
 char m_pad04[0x88]; Rva002DB3F0Vec6 m_8c;
 // ?mask@Rva002DBD20@@QBE?AURva002DB3F0Vec6@@XZ absent-from-retail
 __forceinline Rva002DB3F0Vec6 mask() const { return m_8c; }
};
// ?method@Rva002DBD20@@UAE_NPAVRva002DBD20Weapon@@PAVObject@@@Z
bool Rva002DBD20::method(Rva002DBD20Weapon* weapon,Object* target) {
 if(!((Rva002DF120*)this)->test(weapon,target)) return 0;
 DamageInfo damage;
 (((Rva002DBD20Calls*)this)->*route<bool (Rva002DBD20Calls::*)(Rva002DBD20Weapon*,Object*,DamageInfo*)>(&j_000384f6))(weapon,target,&damage);
 if(!target) return 0;
 Object* source=TheGameLogic->findObjectByID(weapon->m_sourceID);
 if(!source) return 0;
 if(m_8c.notEquals(&NONE) && (((const Rva002DBD20Calls*)target)->*route<bool (Rva002DBD20Calls::*)(const Rva002DB3F0Vec6&,const Rva002DB3F0Vec6&) const>(&j_0003dccb))(mask(),NONE)) {
  AttributeModifierPoolUpdate* pool=source->findAttributeModifierPoolUpdate();
  if(pool && ((const Rva003679D0FrameDeadline*)pool)->isPending(1)) return 0;
 }
 float amount=(((const Rva002DBD20Calls*)target)->*route<float (Rva002DBD20Calls::*)(Rva002DBD20DamageInput&) const>(&j_00043fae))(damage.in);
 if(weapon->m_template->m_508 && source->getContain()) {
  unsigned count=(source->m_contain->members()->*route<unsigned (Rva002DBD20Calls::*)() const>(&j_0000c176))();
  int maximum=weapon->m_template->m_509;
  if(maximum>0) { float ratio=(float)count/maximum; const float& capped=std::min(ratio,1.0f); amount*=capped; }
 }
 if(amount<=0.0f) return 0;
 return 1;
}
