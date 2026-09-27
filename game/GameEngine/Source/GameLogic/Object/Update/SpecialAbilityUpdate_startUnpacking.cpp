// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x002A8CE0, 637 bytes: SpecialAbilityUpdate::startUnpacking.
// ZH twin plus BFME unpack state 2, module-data unpackTime +0x220,
// animation frames +0x28 and condition bits 93/95 prove the identity.
// ModuleData named fields are verified by name_oracle. field208 is unaligned.
// BFME-specific paths notify condition bits 96..98 and 166, and clear disguise.
// BfmeOwner1158 is the existing ABI spelling for Drawable animation duration;
// its pointer-width argument carries the unsigned frame count unchanged.
// Initializing the override view before the branch avoids an extra join jump.
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
template<int N> class BitFlags { _STL::bitset<N> bits; public:
 enum Init { kInit }; BitFlags(Init,int n) { bits.set(n); }
 bool test(int n) const { return bits.test(n); }
 void set(int n) { bits._Unchecked_set(n); }
};
class Object; class Module;
enum KindOfType { DummyKind002A8CE0 };
enum NameKeyType { NAMEKEY_NONE };
class NameKeyGenerator { public: NameKeyType nameToKey(const char*); };
extern NameKeyGenerator* TheNameKeyGenerator;
class GameLogic { public: Object* findObjectByID(int); };
extern GameLogic* TheGameLogic;
float GetGameLogicRandomValueReal(float,float,char*,int);
class Overridable { public: virtual ~Overridable(); Overridable* friend_getFinalOverride(); Overridable* next; };
class SpecialPowerTemplate:public Overridable { public:
 char pad008[0xc]; int powerType;
 int getType() const { const SpecialPowerTemplate* self=this; Overridable* p=next;
  if(p) { if(p->next) p=p->next->friend_getFinalOverride(); self=(const SpecialPowerTemplate*)p; }
  return self->powerType;
 }
};
class BfmeArg1158;
class BfmeOwner1158 { public: void bfmeSubEAll1158(BfmeArg1158*); };
class BfmeInnerCPB { public: void bfmeOneCPB(int,int); };
class Rva00267D00 { public: void m00267D00(char); };
class Thing { public: bool isKindOf(KindOfType) const; };
class Object { public:
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
 virtual BfmeOwner1158* getDrawable();

 void clearAndSetModelConditionFlags(const BitFlags<320>&,const BitFlags<320>&);
 void setStatus(const BitFlags<86>&,bool);
 void notifyModelConditionChanged();
 Module* findModule(NameKeyType) const;
 char pad004[0x10c]; BitFlags<320> conditions;
 char pad138[0xcc]; void* ai;
 void setCondition(int n) { if(!conditions.test(n)) { conditions.set(n); notifyModelConditionChanged(); } }
};
class SpecialAbilityUpdateModuleData { public:
 char pad000[0x1d8]; SpecialPowerTemplate* m_specialPowerTemplate;
 char pad1dc[0x18]; float m_packUnpackVariationFactor;
 char pad1f8[0x10]; int field208;
 char pad20c[0x14]; unsigned m_unpackTime;
};
class SpecialAbilityUpdate { public:
 void startUnpacking();
 void* vptr; SpecialAbilityUpdateModuleData* data; Object* object;
 char pad00c[0x1c]; unsigned animFrames; unsigned field02c; int packingState;
 char pad034[0x78]; int targetID;
};
void SpecialAbilityUpdate::startUnpacking() {
 Object* self=object;
 const SpecialAbilityUpdateModuleData* d=data;
 packingState=2;
 float variation=GetGameLogicRandomValueReal(1.0f-d->m_packUnpackVariationFactor,1.0f+d->m_packUnpackVariationFactor,
 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\SpecialAbilityUpdate.cpp",1170);
 animFrames=(unsigned)(d->m_unpackTime*variation);
 self->clearAndSetModelConditionFlags(BitFlags<320>(BitFlags<320>::kInit,93),BitFlags<320>(BitFlags<320>::kInit,95));
 self->setStatus(BitFlags<86>(BitFlags<86>::kInit,69),true);
 if(d->field208) {
  if(d->field208==1) self->setCondition(96);
  else if(d->field208==2) self->setCondition(97);
  else if(d->field208==3) self->setCondition(98);
 }
 Object* target=TheGameLogic->findObjectByID(targetID);
 int type=d->m_specialPowerTemplate->getType();
 switch(type) {
 case 106:
  if(self->conditions.test(267)) {
   static NameKeyType key=TheNameKeyGenerator->nameToKey("SpecialDisguiseUpdate");
   Rva00267D00* disguise=(Rva00267D00*)self->findModule(key);
   if(disguise) disguise->m00267D00(0);
  }
  break;
 case 40:
  if(target && ((Thing*)target)->isKindOf((KindOfType)131)) self->setCondition(166);
  break;
 }
 BfmeOwner1158* draw=self->getDrawable();
 if(draw) draw->bfmeSubEAll1158((BfmeArg1158*)animFrames);
 void* ai=self->ai;
 if(ai) ((BfmeInnerCPB*)((char*)ai+0x20))->bfmeOneCPB(0,2);
}
