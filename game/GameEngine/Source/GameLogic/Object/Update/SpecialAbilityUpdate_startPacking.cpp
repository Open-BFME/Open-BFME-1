// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x002A8940, 741 bytes: SpecialAbilityUpdate::startPacking(bool).
// ZH twin, state 1, packTime +0x21C and packSound +0x08 establish identity.
// Reuses the verified BFME condition-selector and override shapes from
// startUnpacking. BFME stops prep audio and dispatches completion voices
// through a native STLport one-Drawable list. Native AudioEventRTS is 0x70 B.
// Copying ObjectID before the sound call preserves the retail EAX temporary.
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
#include <list>
template<int N> class BitFlags { _STL::bitset<N> bits; public:
 enum Init { kInit }; BitFlags(Init,int n) { bits.set(n); }
 BitFlags(Init,int a,int b) {bits.set(a);bits.set(b);}
 bool test(int n) const { return bits.test(n); }
 void set(int n) { bits._Unchecked_set(n); }
};
class Object; class Module; class Drawable;
enum ObjectID { INVALID_ID };
class AudioEventRTS { public: AudioEventRTS(const AudioEventRTS&); ~AudioEventRTS(); void setObjectID(ObjectID); void* vptr; char payload[0x6c]; };
class AudioManager { public:
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
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual unsigned addAudioEvent(const AudioEventRTS*);
 virtual void slot48(); virtual void removeAudioEvent(unsigned);
};
extern AudioManager* TheAudio;
namespace _STL { template<> _List_base<Drawable*,allocator<Drawable*> >::~_List_base(); }
class GameMessage { public: enum Type { DummyMessage002A8940 }; };
class PickAndPlayInfo;
void pickAndPlayUnitVoiceResponse(const _STL::list<Drawable*>*,GameMessage::Type,PickAndPlayInfo*);

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
 virtual Drawable* getDrawable();

 void clearAndSetModelConditionFlags(const BitFlags<320>&,const BitFlags<320>&);
 void setStatus(const BitFlags<86>&,bool);
 void notifyModelConditionChanged();
 Module* findModule(NameKeyType) const;
 char pad004[0x70]; ObjectID id; char pad078[0x98]; BitFlags<320> conditions;
 char pad138[0xcc]; void* ai;
 void setCondition(int n) { if(!conditions.test(n)) { conditions.set(n); notifyModelConditionChanged(); } }
};
class SpecialAbilityUpdateModuleData { public:
 char pad000[8]; AudioEventRTS m_packSound; char pad078[0x160]; SpecialPowerTemplate* m_specialPowerTemplate;
 char pad1dc[0x18]; float m_packUnpackVariationFactor;
 char pad1f8[0x10]; int field208;
 char pad20c[0x10]; unsigned m_packTime; unsigned m_unpackTime;
};
class SpecialAbilityUpdate { public:
 void startPacking(bool success);
 void* vptr; SpecialAbilityUpdateModuleData* data; Object* object;
 char pad00c[0x1c]; unsigned animFrames; unsigned field02c; int packingState;
 char pad034[0x70]; unsigned prepHandle; char pad0a8[4]; int targetID;
};
void SpecialAbilityUpdate::startPacking(bool success) {
 const SpecialAbilityUpdateModuleData* d=data;
 Object* self=object;
 packingState=1;
 float variation=GetGameLogicRandomValueReal(1.0f-d->m_packUnpackVariationFactor,1.0f+d->m_packUnpackVariationFactor,
 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\SpecialAbilityUpdate.cpp",1107);
 animFrames=(unsigned)(d->m_packTime*variation);
 self->clearAndSetModelConditionFlags(BitFlags<320>(BitFlags<320>::kInit,95,111),BitFlags<320>(BitFlags<320>::kInit,93));
 self->setStatus(BitFlags<86>(BitFlags<86>::kInit,69),true);
 if(d->field208) {
  if(d->field208==1) self->setCondition(96);
  else if(d->field208==2) self->setCondition(97);
  else if(d->field208==3) self->setCondition(98);
 }
 AudioEventRTS sound=d->m_packSound;
 ObjectID id=self->id;
 sound.setObjectID(id);
 TheAudio->addAudioEvent(&sound);
 TheAudio->removeAudioEvent(prepHandle);
 prepHandle=1;
 Drawable* draw=self->getDrawable();
 if(draw) ((BfmeOwner1158*)draw)->bfmeSubEAll1158((BfmeArg1158*)animFrames);
 if(d->m_specialPowerTemplate->getType()!=43) {
  void* ai=self->ai;
  if(ai) ((BfmeInnerCPB*)((char*)ai+0x20))->bfmeOneCPB(0,2);
 }
 if(success) {
  _STL::list<Drawable*> objects;
  objects.push_back(draw);
  if(d->m_specialPowerTemplate->getType()==26) pickAndPlayUnitVoiceResponse(&objects,(GameMessage::Type)2013,0);
  else pickAndPlayUnitVoiceResponse(&objects,(GameMessage::Type)2014,0);
 }
}
