// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x002A9420, 856 bytes: SpecialAbilityUpdate::startPreparation.
// Identity: ZH startPreparation twin, preparationFrames +0x20c,
// prepSoundLoop +0xe8, and preparation/laser/EVA phase transitions.
// Receiver locals preserve evaluation before external flag constructors;
// a mutable current-data pointer preserves the final EAX/EDX allocation.
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
#include <list>
template<int N> class BitFlags { _STL::bitset<N> bits; public:
 enum Init { kInit }; BitFlags(Init,int n) { bits.set(n); }
 BitFlags(Init,int a,int b) {bits.set(a);bits.set(b);}
 __forceinline bool test(int n) const { return bits.test(n); }
 __forceinline void set(int n) { bits._Unchecked_set(n); }
};
class Object; class Module; class Drawable;
enum ObjectID { INVALID_ID };
class AudioEventRTS { public: AudioEventRTS(const AudioEventRTS&); ~AudioEventRTS(); void setObjectID(ObjectID); AudioEventRTS& operator=(const AudioEventRTS&); void setPlayingHandle(unsigned); void* vptr; char payload[0x6c]; };
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
enum SpecialPowerType { DummyPower002A9420 };
class SpecialPowerTemplate:public Overridable { public:
 char pad008[0xc]; int powerType;
 SpecialPowerType getSpecialPowerType() const;
 int getType() const { const SpecialPowerTemplate* self;
 Overridable* p=next; if(p) {if(p->next)p=p->next->friend_getFinalOverride();self=(const SpecialPowerTemplate*)p;}else self=this;
 return self->powerType; }

};
class BfmeArg1158;
class BfmeOwner1158 { public: void bfmeSubEAll1158(BfmeArg1158*); };
class BfmeInnerCPB { public: void bfmeOneCPB(int,int); };
class Rva00267D00 { public: void m00267D00(char); };
class Thing { public: bool isKindOf(KindOfType) const; };
struct Coord3D; enum Relationship { DummyRelation002A9420 }; enum EvaMessage { DummyEva002A9420 };
class Eva {public:bool setShouldPlay(EvaMessage,const Coord3D*);}; extern Eva* TheEva;
class Rva00170C70BitSet:public BitFlags<320> {public:Rva00170C70BitSet(void*,unsigned);};
class Rva002A7D20 {public:unsigned getConditionalPreparationFrames()const;};
enum CommandSourceType { DummyCommand002A9420 }; class AICommandInterface {public:void aiIdle(CommandSourceType);};
class Contain002A9420 {public:
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
virtual void useTarget(Object*);};
class SpecialPowerModuleInterface {public:
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
virtual void mark(void*);};
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
 SpecialPowerModuleInterface* getSpecialPowerModule(const SpecialPowerTemplate*)const;
 Relationship getRelationship(const Object*)const; bool isLocallyControlled()const;
 char pad004[0x70]; ObjectID id; char pad078[0x98]; BitFlags<320> conditions;
 char pad138[0xc4]; Contain002A9420* contain; char pad200[4]; void* ai; char pad208[0x34]; void* team;
 __forceinline void setCondition(int n) { if(!conditions.test(n)) { conditions.set(n); notifyModelConditionChanged(); } }
};

class SpecialAbilityUpdateModuleData { public:
 char pad000[0xe8]; AudioEventRTS m_prepSoundLoop; char pad158[0x80]; SpecialPowerTemplate* m_specialPowerTemplate;
 char pad1dc[0x2c]; int field208; unsigned m_preparationFrames;
};
class SpecialAbilityUpdate {public:
 void startPreparation(); Object* createSpecialObject(); bool initLaser(Object*,Object*);
 void* vptr; SpecialAbilityUpdateModuleData* data; Object* object;
 char pad00c[0x28]; AudioEventRTS prepSoundLoop; unsigned prepHandle; unsigned prepFrames; int targetID;
};
void SpecialAbilityUpdate::startPreparation() {
 const SpecialAbilityUpdateModuleData* d=data;
 SpecialPowerTemplate* power=d->m_specialPowerTemplate;
 prepFrames=((Rva002A7D20*)this)->getConditionalPreparationFrames();
 if(prepFrames) {
 Object* target=TheGameLogic->findObjectByID(targetID);
 Contain002A9420* contain=object->contain;
 if(contain&&target) contain->useTarget(target);
 object->clearAndSetModelConditionFlags(BitFlags<320>(BitFlags<320>::kInit,95,111),BitFlags<320>(BitFlags<320>::kInit,94));
 if(d->field208) {if(d->field208==1)object->setCondition(96);else if(d->field208==2)object->setCondition(97);else if(d->field208==3)object->setCondition(98);}
 }
 switch(power->getType()) {
 case 29: {
 Object* target=TheGameLogic->findObjectByID(targetID);
 if(target && target->team==object->team)return;
 Object* self=object; self->clearAndSetModelConditionFlags(Rva00170C70BitSet(0,95),Rva00170C70BitSet(0,111));
 Drawable* draw=object->getDrawable();
 if(draw)((BfmeOwner1158*)draw)->bfmeSubEAll1158((BfmeArg1158*)d->m_preparationFrames);
 if(target&&target->isLocallyControlled())TheEva->setShouldPlay((EvaMessage)15,0);
 break; }
 case 26: {
 Object* target=TheGameLogic->findObjectByID(targetID);
 if(target) {
 if(object->getRelationship(target)==2)return;
 Object* special=createSpecialObject();
 if(special) {if(!initLaser(special,target))return;
 Object* self=object; self->clearAndSetModelConditionFlags(Rva00170C70BitSet(0,95),Rva00170C70BitSet(0,40));}
 if(power->getSpecialPowerType()==26&&target->isLocallyControlled())TheEva->setShouldPlay((EvaMessage)15,0);
 }break;}
 case 21: {
 Object* target=TheGameLogic->findObjectByID(targetID);
 if(target){Object* special=createSpecialObject();if(special&&!initLaser(special,target))return;}break;}
 }
 SpecialAbilityUpdateModuleData* current=data; SpecialPowerModuleInterface* module=object->getSpecialPowerModule(current->m_specialPowerTemplate);
 if(module)module->mark(0);
 void* ai=object->ai;
 if(ai)((AICommandInterface*)((char*)ai+0x20))->aiIdle((CommandSourceType)2);
 object->setStatus(BitFlags<86>(BitFlags<86>::kInit,24,69),true);
 prepSoundLoop=d->m_prepSoundLoop;
 prepSoundLoop.setObjectID(object->id);
 unsigned handle=TheAudio->addAudioEvent(&prepSoundLoop);
 prepSoundLoop.setPlayingHandle(handle);
}
