// ?update@StealthDetectorUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=1.0 date=2026-09-27
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// StealthDetectorUpdate::update, retail RVA 002AB690 / 1954 bytes.
// Exact non-relocation bytes with MSVC 7.1; NOT a landed conversion.
// Retail vtable identity and ZH StealthDetectorUpdate::update establish identity.
// BFME layout/ABI differences reconstructed from the complete retail body:
// ref-counted vector query result; temporary filters; cached module NameKey;
// static discovered/neutralized sounds; two-argument markAsDetected; extra
// 002AD250 state update; tracked 12-byte particle handles; 8-byte string header.
// Native while(next()) and a shared function-local key are essential: a for
// epilogue duplicated the iterator advance and separate inline key sites added
// a second static guard. These two structural fixes removed 1162 differences.
// All module-data named fields are witnessed by field_names.csv. field13a has
// no current witness. Object/player/drawable views use explicit retail offsets.
// Relocation bindings are intentionally unlanded: 22 typed REL32 spellings lack
// existing pins. See build/astra_seat/stealth_missing_pins.json and the complete
// relocation audit. Do not infer callee identity from the exact masked bytes.

#define _STLP_USE_STATIC_LIB 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include <list>
#include "PreRTS.h"
#include "Common/NameKeyGenerator.h"
#include "Common/BitFlags.h"


template<class T> __forceinline T &sdField(void *p,int o){return *(T*)((char*)p+o);}
class Rva002AB690Object; class Rva002AB690Drawable; class Rva002AB690Stealth;
class Rva002AB690Particle;
struct Rva002AB690AudioEvent { char bytes[0x70]; Rva002AB690AudioEvent(const AsciiString&,int); Rva002AB690AudioEvent(const Rva002AB690AudioEvent&); ~Rva002AB690AudioEvent(); Rva002AB690AudioEvent& operator=(const Rva002AB690AudioEvent&); void setPlayerIndex(int);void setObjectID(int);};
struct Rva002AB690Data {
 char pad00[8]; unsigned m_updateRate; float m_detectionRange; bool m_initiallyDisabled; char pad11[3];
 Rva002AB690AudioEvent m_pingSound,m_loudPingSound;
 void *m_IRBeaconParticleSysTmpl,*m_IRParticleSysTmpl,*m_IRBrightParticleSysTmpl,*m_IRGridParticleSysTmpl;
 AsciiString m_IRParticleSysBone;
 BitFlags<192> m_extraDetectKindof,m_extraDetectKindofNot;
 bool m_canDetectWhileGarrisoned,m_canDetectWhileTransported,field13a;
};
typedef std::list<Rva002AB690Object*> Rva002AB690Contained;
class Rva002AB690Contain {public:
virtual void slot00();
virtual void slot01();
virtual bool isGarrisonable();
virtual void slot03();
virtual void slot04();
virtual void slot05();
virtual void slot06();
virtual void slot07();
virtual void slot08();
virtual void slot09();
virtual void slot0a();
virtual void slot0b();
virtual void slot0c();
virtual void slot0d();
virtual void slot0e();
virtual void slot0f();
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
virtual void slot1a();
virtual void slot1b();
virtual void slot1c();
virtual void slot1d();
virtual void slot1e();
virtual void slot1f();
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
virtual void slot2a();
virtual void slot2b();
virtual void slot2c();
virtual void slot2d();
virtual void slot2e();
virtual void slot2f();
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
virtual void slot3a();
virtual void slot3b();
virtual void slot3c();
virtual void slot3d();
virtual void slot3e();
virtual void slot3f();
virtual void slot40();
virtual const Rva002AB690Contained *getItems();
virtual void slot42();
virtual void slot43();
virtual int getStealthUnitsContained();

};
class Rva002AB690Player {public: int index(){return sdField<int>(this,0x24);} };
class Rva002AB690Drawable {public:
virtual void slot00();
void getPristineBonePositions(const char*,int,Coord3D*,void*,int,int);
};
class Rva002AB690Stealth {public:void markAsDetected(unsigned,bool);void update002AD250();bool field2d(){return sdField<bool>(this,0x2d);}};
class Rva002AB690Object {public:
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
virtual Rva002AB690Drawable *getDrawable();

 bool dead(){return (sdField<unsigned char>(this,0x344)&1)!=0;}
 unsigned status(unsigned mask){return sdField<unsigned>(this,0x90)&mask;}
 Rva002AB690Object *containedBy(){return sdField<Rva002AB690Object*>(this,0x214);}
 Rva002AB690Contain *contain(){return sdField<Rva002AB690Contain*>(this,0x1fc);}
 Coord3D* position(){return &sdField<Coord3D>(this,0x38);}
 float getVisionRange()const;
 Rva002AB690Player* getControllingPlayer()const;
 int getRelationship(const Rva002AB690Object*)const;
 int getShroudedStatus(int)const;
 Rva002AB690Stealth *findModule(NameKeyType)const;
 __forceinline Rva002AB690Stealth *getStealth(){static NameKeyType key=TheNameKeyGenerator->nameToKey("StealthUpdate");return findModule(key);}
 int id(){return sdField<int>(this,0x74);}

};

class PartitionFilter {public:PartitionFilter():next(0){} virtual ~PartitionFilter(){} virtual bool allow(Rva002AB690Object*)=0;virtual int getPlayerMask();PartitionFilter *link(PartitionFilter*);PartitionFilter *next;};
class PartitionFilterSameMapStatus:public PartitionFilter {public:PartitionFilterSameMapStatus(Rva002AB690Object*o):obj(o){} virtual ~PartitionFilterSameMapStatus(){} virtual bool allow(Rva002AB690Object*);Rva002AB690Object*obj;};
class PartitionFilterAcceptByKindOf:public PartitionFilter {public:PartitionFilterAcceptByKindOf(const BitFlags<192>&,const BitFlags<192>&);virtual ~PartitionFilterAcceptByKindOf(){}virtual bool allow(Rva002AB690Object*);BitFlags<192> yes,no;};
class PartitionFilterRelationship:public PartitionFilter {public:PartitionFilterRelationship(Rva002AB690Object*o,int f,bool b):obj(o),flags(f),flag(b){}virtual ~PartitionFilterRelationship(){}virtual bool allow(Rva002AB690Object*);virtual int getPlayerMask();Rva002AB690Object*obj;int flags;bool flag;};
struct Rva002AB690Entry{Rva002AB690Object *obj;unsigned value;};
struct Rva002AB690ResultData{std::vector<Rva002AB690Entry> entries;Rva002AB690Entry* current;int references;};
struct BfmeWideResult{Rva002AB690ResultData *value;BfmeWideResult();BfmeWideResult(const BfmeWideResult&);~BfmeWideResult(){if(--value->references==0)delete value;}Rva002AB690Object *next(){if(value->current==value->entries.end())return 0;return (value->current++)->obj;}};
class BfmeWideForwardC{public:BfmeWideResult bfmeForwardWideC(const Coord3D*,float,int,PartitionFilter*,bool);};
extern BfmeWideForwardC *ThePartitionManager;
class Rva002AB690Radar{public:void createEvent(const Coord3D*,int,float);};extern Rva002AB690Radar *Rva012EF0E4;
class Rva002AB690Players {public:Rva002AB690Player *local(){return sdField<Rva002AB690Player*>(this,0xc);}};extern Rva002AB690Players *Rva012ED748;
class Rva002AB690Audio {public:
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
virtual void slot0a();
virtual void slot0b();
virtual void slot0c();
virtual void slot0d();
virtual void slot0e();
virtual void slot0f();
virtual void slot10();
virtual void addAudioEvent(Rva002AB690AudioEvent*);
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot1a();
virtual void slot1b();
virtual void slot1c();
virtual void slot1d();
virtual void slot1e();
virtual void slot1f();
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
virtual void slot2a();
virtual void slot2b();
virtual void slot2c();
virtual void slot2d();
virtual void slot2e();
virtual void slot2f();
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
virtual void slot3a();
virtual void slot3b();
virtual void slot3c();
virtual void slot3d();
virtual void slot3e();
virtual void slot3f();
virtual void slot40();
virtual void slot41();
virtual void slot42();
virtual void slot43();
virtual void slot44();
virtual void slot45();
virtual void slot46();
virtual void slot47();
virtual void slot48();
virtual void *getMiscAudio();

};
extern Rva002AB690Audio *Rva012ED668;
class Rva002AB690Text {public:
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
virtual UnicodeString fetch(const char*,bool*);

};
class Rva002AB690UI {public:
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
virtual void slot0a();
virtual void slot0b();
virtual void slot0c();
virtual void __cdecl message(UnicodeString,...);

};
extern Rva002AB690Text *Rva012F147C;extern Rva002AB690UI *Rva012F148C;

Rva002AB690Particle *bfmeNullSystemZA();
class Rva002AB690Particle {public:void attachToDrawable(Rva002AB690Drawable*);void attachToObject(Rva002AB690Object*);void setPosition(const Coord3D*);};
struct Rva002AB690Handle{Rva002AB690Particle *value;void *previous,*next;~Rva002AB690Handle();Rva002AB690Particle *operator->()const{return value?value:bfmeNullSystemZA();}};
class Rva002AB690ParticleManager{public:Rva002AB690Handle createParticleSystem(void*,bool);};extern Rva002AB690ParticleManager *Rva012F64BC;
extern AsciiString Rva01336E50;
enum UpdateSleepTime{SD_SLEEP_NONE=1,SD_SLEEP_FOREVER=0x3fffffff};
class StealthDetectorUpdate{public:virtual UpdateSleepTime update();};

UpdateSleepTime StealthDetectorUpdate::update()
{
 Rva002AB690Data *data=sdField<Rva002AB690Data*>(this,-12);
 Rva002AB690Object *self=sdField<Rva002AB690Object*>(this,-8);
 if(self->dead())return SD_SLEEP_FOREVER;
 if(self->status(4))return SD_SLEEP_NONE;
 if(self->status(0x80000))return SD_SLEEP_FOREVER;
 Rva002AB690Object *containedBy=self->containedBy();
 if(containedBy){Rva002AB690Contain *contain=containedBy->contain();if(contain){if(contain->isGarrisonable()){if(!data->m_canDetectWhileGarrisoned)return (UpdateSleepTime)data->m_updateRate;}else if(!data->m_canDetectWhileTransported)return (UpdateSleepTime)data->m_updateRate;}}
 float visionRange=self->getVisionRange();
 if(data->m_detectionRange>0.0f)visionRange=data->m_detectionRange;
 bool foundSomeone=false;
 BfmeWideResult iter=ThePartitionManager->bfmeForwardWideC(self->position(),visionRange,0,
  PartitionFilterRelationship(self,3,false).link(PartitionFilterAcceptByKindOf(data->m_extraDetectKindof,data->m_extraDetectKindofNot).link(&PartitionFilterSameMapStatus(sdField<Rva002AB690Object*>(this,-8)))),false);
 while(Rva002AB690Object *them=iter.next()){
  if(them->dead())continue;
  static NameKeyType key=TheNameKeyGenerator->nameToKey("StealthUpdate");
  Rva002AB690Stealth *stealth=them->findModule(key);
  if(stealth && them->status(0x40000)){
   foundSomeone=true;
   if(!them->status(0x20000)){
    if(Rva012ED748->local()==self->getControllingPlayer() && self->getRelationship(them)!=2){
     Rva012EF0E4->createEvent(them->position(),8,4.0f);
     static Rva002AB690AudioEvent discoveredSound=sdField<Rva002AB690AudioEvent>(Rva012ED668->getMiscAudio(),0x460);
     discoveredSound.setPlayerIndex(self->getControllingPlayer()->index());Rva012ED668->addAudioEvent(&discoveredSound);
     Rva012F148C->message(Rva012F147C->fetch("MESSAGE:StealthDiscovered",0));
    }
    if(Rva012ED748->local()==them->getControllingPlayer() && self->getRelationship(them)!=2){
     Rva012EF0E4->createEvent(them->position(),9,4.0f);
     static Rva002AB690AudioEvent neutralizedSound=sdField<Rva002AB690AudioEvent>(Rva012ED668->getMiscAudio(),0x4d0);
     neutralizedSound.setPlayerIndex(them->getControllingPlayer()->index());Rva012ED668->addAudioEvent(&neutralizedSound);
     Rva012F148C->message(Rva012F147C->fetch("MESSAGE:StealthNeutralized",0));
    }
    Rva002AB690Drawable *theirDraw=them->getDrawable();if(theirDraw)sdField<float>(theirDraw,0x2e4)=1.0f;
   }
   stealth->markAsDetected(data->m_updateRate+1,true);
   if(data->field13a && stealth->field2d())stealth->update002AD250();
   if(data->m_IRGridParticleSysTmpl){
    Rva002AB690Handle sys=Rva012F64BC->createParticleSystem(data->m_IRGridParticleSysTmpl,true);
    if(sys.value){Coord3D gridPosition;gridPosition.x=them->position()->x;gridPosition.y=them->position()->y;gridPosition.z=self->position()->z+17;gridPosition.x-=((int)gridPosition.x)%12;gridPosition.y-=((int)gridPosition.y)%12;sys.value->setPosition(&gridPosition);}
   }
  } else {
   Rva002AB690Contain *contain=them->contain();if(contain && contain->isGarrisonable() && contain->getStealthUnitsContained()){
    for(Rva002AB690Contained::const_iterator it=contain->getItems()->begin();it!=contain->getItems()->end();++it){
     Rva002AB690Object *rider=*it;Rva002AB690Stealth *stealth=rider->findModule(key);if(stealth){foundSomeone=true;if(self->getControllingPlayer()!=rider->getControllingPlayer() && self->getRelationship(rider)!=2)stealth->markAsDetected(data->m_updateRate+2,true);}
    }
   }
  }
 }
 if(data->m_IRGridParticleSysTmpl && self->getShroudedStatus(Rva012ED748->local()->index())<=2){
  Rva002AB690Drawable *myDraw=self->getDrawable();Coord3D bonePosition={-1.66f,5.5f,15};
  if(myDraw)myDraw->getPristineBonePositions(data->m_IRParticleSysBone.str(),0,&bonePosition,0,1,0);
  void *pingTemplate=foundSomeone?data->m_IRBrightParticleSysTmpl:data->m_IRParticleSysTmpl;
  if(pingTemplate){Rva002AB690Handle sys=Rva012F64BC->createParticleSystem(pingTemplate,true);if(sys.value){if(myDraw)sys->attachToDrawable(myDraw);else sys->attachToObject(self);sys->setPosition(&bonePosition);}}
  void *beaconTemplate=data->m_IRBeaconParticleSysTmpl;
  if(beaconTemplate){Rva002AB690Handle sys=Rva012F64BC->createParticleSystem(beaconTemplate,true);if(sys.value){if(myDraw)sys->attachToDrawable(myDraw);else sys->attachToObject(self);sys->setPosition(&bonePosition);}}
  Rva002AB690AudioEvent IRPingSound(Rva01336E50,0);
  if(foundSomeone)IRPingSound=data->m_loudPingSound;else IRPingSound=data->m_pingSound;
  IRPingSound.setObjectID(self->id());Rva012ED668->addAudioEvent(&IRPingSound);
 }
 return (UpdateSleepTime)data->m_updateRate;
}
