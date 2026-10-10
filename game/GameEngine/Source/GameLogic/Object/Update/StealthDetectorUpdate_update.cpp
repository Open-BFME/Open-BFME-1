// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// readable body of ?update@StealthDetectorUpdate@@: game/GameEngine/Source/GameLogic/Object/Update/StealthDetectorUpdate.cpp
//
// ?update@StealthDetectorUpdate@@UAE?AW4UpdateSleepTime@@XZ -- retail RVA 0x002AB690, 1954 bytes.
//
// Identity: the StealthDetectorUpdate vtable 0x00CC3B2C slots name this class
// (its deleting destructor 0x002AB620 is matched); the retail body is the
// ZH StealthDetectorUpdate::update reshaped by BFME, called from the update
// dispatch through vtable slot 2's ILT.  The ZH twin (readable copy in
// StealthDetectorUpdate.cpp) differs in layout and callee set; the shape
// below was reconstructed from the complete retail body:
//  - a ref-counted vector query result (BfmeWideResult) replaces the ZH
//    SimpleObjectIterator;
//  - temporary filters are linked through PartitionFilter::link
//    (0x009F2AE0, matched) instead of the ZH filters array;
//  - the module NameKey is a shared function-local static;
//  - static discovered/neutralized AudioEventRTS sounds copy-construct from
//    TheAudio->getMiscAudio() +0x460/+0x4D0;
//  - the extra 002AD250 state update (matched
//    ?update002AD250@StealthUpdate@@QAEXXZ) fires when module-data field
//    0x13A is set and StealthUpdate+0x2D is set;
//  - particle systems come back as tracked 12-byte ParticleSystemHandle
//    values (create through 0x005C3A30, matched ?make@Rva005C3A30);
//  - the 8-byte WWLib AsciiString header (stringbaseascii shim) reproduces
//    the inline StringBase<char>::str() empty-string shape at +0x5CB.
//
// Native while(next()) and a shared function-local key are essential: a for
// epilogue duplicated the iterator advance and separate inline key sites
// added a second static guard.  All module-data fields are witnessed by
// field_names.csv except field13a, which is named by its offset only.
// Object/player/drawable views use explicit retail offsets because the
// retail Object layout (dead flag +0x344, status +0x90) differs from the
// ZH reference headers.

#define _STLP_USE_STATIC_LIB 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include <list>
#include "Common/AsciiString.h"
#include "Common/BitFlags.h"


template<class T> __forceinline T &sdField(void *p,int o){return *(T*)((char*)p+o);}

// Common/BitFlags.h (below) transitively provides the reference Coord3D,
// UnicodeString, Relationship and ObjectShroudStatus declarations.

// The key-generator callee is the matched ?nameToKey@NameKeyGenerator@@QAE?AW4NameKeyType@@PBD@Z.
enum NameKeyType { FORCE_NAMEKEYTYPE_LONG = 0x7fffffff };
class NameKeyGenerator { public: NameKeyType nameToKey(const char*); };
extern NameKeyGenerator *TheNameKeyGenerator;

class Module;
class ParticleSystemZA;
class Matrix3D;

enum ObjectID {};
enum RadarEventType {};

// ?bfmeNullSystemZA@@YAPAVParticleSystemZA@@XZ (matched, 0x005CFF50)
ParticleSystemZA *bfmeNullSystemZA();

// ?setPlayerIndex@AudioEventRTS@@QAEXH@Z, ??0AudioEventRTS@@QAE@ABVAsciiString@@H@Z,
// ?setObjectID@AudioEventRTS@@QAEXW4ObjectID@@@Z, ?assign@AudioEventRTS@@QAEAAV1@ABV1@@Z,
// ??1AudioEventRTS@@QAE@XZ and ??0AudioEventRTS@@QAE@ABV0@@Z are all matched
// retail bodies; the view below spells the calls at those names.
class AudioEventRTS {
public:
 char bytes[0x70];
 AudioEventRTS(const AsciiString&,int);
 AudioEventRTS(const AudioEventRTS&);
 ~AudioEventRTS();
 AudioEventRTS& operator=(const AudioEventRTS&);
 AudioEventRTS& assign(const AudioEventRTS&);
 void setPlayerIndex(int);
 void setObjectID(ObjectID);
};

// TheAudio at retail 0x012ED668; virtual slots position addAudioEvent
// (0x11) and getMiscAudio (0x49).
class Rva0041D290Audio {public:
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
virtual void addAudioEvent(AudioEventRTS*);
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
extern Rva0041D290Audio *Rva012ed668;

struct Rva002AB690Data {
 char pad00[8]; unsigned m_updateRate; float m_detectionRange; bool m_initiallyDisabled; char pad11[3];
 AudioEventRTS m_pingSound,m_loudPingSound;
 void *m_IRBeaconParticleSysTmpl,*m_IRParticleSysTmpl,*m_IRBrightParticleSysTmpl,*m_IRGridParticleSysTmpl;
 AsciiString m_IRParticleSysBone;
 BitFlags<192> m_extraDetectKindof,m_extraDetectKindofNot;
 bool m_canDetectWhileGarrisoned,m_canDetectWhileTransported,field13a;
};

class Player {public: int index(){return sdField<int>(this,0x24);} };

class Object; class Drawable;

// ?getPristineBonePositions@BFMEDrawableBoneQuery@@QBEHPBDHPAUCoord3D@@PAVMatrix3D@@HH@Z (matched, 0x00413850)
class BFMEDrawableBoneQuery {public:
int getPristineBonePositions(const char*,int,Coord3D*,Matrix3D*,int,int) const;
};

class Drawable {public:
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
};

class StealthUpdate {public:
 void markAsDetected(unsigned,bool); // ?markAsDetected@StealthUpdate@@QAEXI_N@Z (matched)
 void update002AD250();               // ?update002AD250@StealthUpdate@@QAEXXZ (matched)
 bool field2d(){return sdField<bool>(this,0x2d);}
};

typedef std::list<Object*> Rva002AB690Contained;
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

class Object {public:
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
virtual Drawable *getDrawable();

 bool dead(){return (sdField<unsigned char>(this,0x344)&1)!=0;}
 unsigned status(unsigned mask){return sdField<unsigned>(this,0x90)&mask;}
 Object *containedBy(){return sdField<Object*>(this,0x214);}
 Rva002AB690Contain *contain(){return sdField<Rva002AB690Contain*>(this,0x1fc);}
 Coord3D* position(){return &sdField<Coord3D>(this,0x38);}
 float getVisionRange()const;                    // ?getVisionRange@Object@@QBEMXZ (matched)
 Player* getControllingPlayer()const;            // ?getControllingPlayer@Object@@QBEPAVPlayer@@XZ (matched)
 Relationship getRelationship(const Object*)const; // ?getRelationship@Object@@QBE?AW4Relationship@@PBV1@@Z (matched)
 ObjectShroudStatus getShroudedStatus(int)const; // ?getShroudedStatus@Object@@QBE?AW4ObjectShroudStatus@@H@Z (matched)
 int id(){return sdField<int>(this,0x74);}

friend class StealthDetectorUpdate;
protected:
 Module* findModule(NameKeyType)const;           // ?findModule@Object@@IBEPAVModule@@W4NameKeyType@@@Z (matched)

};

class PartitionFilter {public:PartitionFilter():next(0){} virtual ~PartitionFilter(){} virtual bool allow(Object*)=0;virtual int getPlayerMask();PartitionFilter *link(PartitionFilter*);PartitionFilter *next;};
class PartitionFilterSameMapStatus:public PartitionFilter {public:PartitionFilterSameMapStatus(Object*o):obj(o){} virtual ~PartitionFilterSameMapStatus(){} virtual bool allow(Object*);Object*obj;};
class PartitionFilterAcceptByKindOf:public PartitionFilter {public:PartitionFilterAcceptByKindOf(const BitFlags<192>&,const BitFlags<192>&);virtual ~PartitionFilterAcceptByKindOf(){}virtual bool allow(Object*);BitFlags<192> yes,no;};
class PartitionFilterRelationship:public PartitionFilter {public:PartitionFilterRelationship(Object*o,int f,bool b):obj(o),flags(f),flag(b){}virtual ~PartitionFilterRelationship(){}virtual bool allow(Object*);virtual int getPlayerMask();Object*obj;int flags;bool flag;};

struct Rva002AB690Entry{Object *obj;unsigned value;};
struct Rva002AB690ResultData{std::vector<Rva002AB690Entry> entries;Rva002AB690Entry* current;int references;};
struct BfmeWideResult{Rva002AB690ResultData *value;BfmeWideResult();BfmeWideResult(const BfmeWideResult&);~BfmeWideResult(){if(--value->references==0)delete value;}Object *next(){if(value->current==value->entries.end())return 0;return (value->current++)->obj;}};

// Retail ThePartitionManager at 0x012ED5B8; the BFME wide query entry is the
// matched ?bfmeForwardWideC@BfmeWideForwardC@@QAE?AUBfmeWideResult@@HMHHH@Z
// (0x009F2960), called with raw integer spellings of the pointer/bool arguments.
class PartitionManager;
class BfmeWideForwardC {public:BfmeWideResult bfmeForwardWideC(int,float,int,int,int);};
extern PartitionManager *ThePartitionManager;

// Retail TheRadar at 0x012EF0E4 (proven by the engine-init tag block);
// ?createEvent@Radar@@QAEXPBUCoord3D@@W4RadarEventType@@M@Z is matched at 0x00108140.
class Radar {public: void createEvent(const Coord3D*,RadarEventType,float); };
extern Radar *TheRadar;

struct Rva002EE330PlayerList {Player *local(){return sdField<Player*>(this,0xc);}};
extern Rva002EE330PlayerList *Rva002EE330ThePlayers;

class GameTextInterface {public:
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
extern GameTextInterface *TheGameText;

struct InGameUI {public:
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
extern InGameUI *TheInGameUI;

// ?setPosition@ParticleSystem@@QAEXPBUCoord3D@@@Z, ?attachToDrawable@ParticleSystem@@QAEXPBVDrawable@@@Z
// and ?attachToObject@ParticleSystem@@QAEXPBVObject@@@Z are matched retail bodies.
class ParticleSystem {public:
 void attachToDrawable(const Drawable*);
 void attachToObject(const Object*);
 void setPosition(const Coord3D*);
};

// ??1ParticleSystemHandle@@QAE@XZ (matched, 0x001DA440) is the tracked handle's
// destructor; the null system fallback goes through the matched
// ?bfmeNullSystemZA@@YAPAVParticleSystemZA@@XZ.
class ParticleSystemHandle {public:
 ParticleSystem *value;void *previous,*next;
 ~ParticleSystemHandle();
 ParticleSystem *operator->()const{return value?value:(ParticleSystem*)bfmeNullSystemZA();}
};

// The particle-system factory callee is matched as
// ?make@Rva005C3A30@@QAE?AUBfmeVec3@@PAX0@Z (0x005C3A30); its by-value return
// is the 12-byte tracked handle.
struct BfmeVec3:ParticleSystemHandle {};
class Rva005C3A30 {public:BfmeVec3 make(void*,void*);};
class ParticleSystemManager;
extern ParticleSystemManager *TheParticleSystemManager;

extern const AsciiString Rva01336E50EmptyAscii;
enum UpdateSleepTime{SD_SLEEP_NONE=1,SD_SLEEP_FOREVER=0x3fffffff};
class StealthDetectorUpdate{public:virtual UpdateSleepTime update();};

UpdateSleepTime StealthDetectorUpdate::update()
{
 Rva002AB690Data *data=sdField<Rva002AB690Data*>(this,-12);
 Object *self=sdField<Object*>(this,-8);
 if(self->dead())return SD_SLEEP_FOREVER;
 if(self->status(4))return SD_SLEEP_NONE;
 if(self->status(0x80000))return SD_SLEEP_FOREVER;
 Object *containedBy=self->containedBy();
 if(containedBy){Rva002AB690Contain *contain=containedBy->contain();if(contain){if(contain->isGarrisonable()){if(!data->m_canDetectWhileGarrisoned)return (UpdateSleepTime)data->m_updateRate;}else if(!data->m_canDetectWhileTransported)return (UpdateSleepTime)data->m_updateRate;}}
 float visionRange=self->getVisionRange();
 if(data->m_detectionRange>0.0f)visionRange=data->m_detectionRange;
 bool foundSomeone=false;
 BfmeWideResult iter=((BfmeWideForwardC*)ThePartitionManager)->bfmeForwardWideC((int)self->position(),visionRange,0,
  (int)PartitionFilterRelationship(self,3,false).link(PartitionFilterAcceptByKindOf(data->m_extraDetectKindof,data->m_extraDetectKindofNot).link(&PartitionFilterSameMapStatus(sdField<Object*>(this,-8)))),0);
 while(Object *them=iter.next()){
  if(them->dead())continue;
  static NameKeyType key=TheNameKeyGenerator->nameToKey("StealthUpdate");
  StealthUpdate *stealth=(StealthUpdate*)them->findModule(key);
  if(stealth && them->status(0x40000)){
   foundSomeone=true;
   if(!them->status(0x20000)){
    if(Rva002EE330ThePlayers->local()==self->getControllingPlayer() && self->getRelationship(them)!=2){
     TheRadar->createEvent(them->position(),(RadarEventType)8,4.0f);
     static AudioEventRTS discoveredSound=sdField<AudioEventRTS>(Rva012ed668->getMiscAudio(),0x460);
     discoveredSound.setPlayerIndex(self->getControllingPlayer()->index());Rva012ed668->addAudioEvent(&discoveredSound);
     TheInGameUI->message(TheGameText->fetch("MESSAGE:StealthDiscovered",0));
    }
    if(Rva002EE330ThePlayers->local()==them->getControllingPlayer() && self->getRelationship(them)!=2){
     TheRadar->createEvent(them->position(),(RadarEventType)9,4.0f);
     static AudioEventRTS neutralizedSound=sdField<AudioEventRTS>(Rva012ed668->getMiscAudio(),0x4d0);
     neutralizedSound.setPlayerIndex(them->getControllingPlayer()->index());Rva012ed668->addAudioEvent(&neutralizedSound);
     TheInGameUI->message(TheGameText->fetch("MESSAGE:StealthNeutralized",0));
    }
    Drawable *theirDraw=them->getDrawable();if(theirDraw)sdField<float>(theirDraw,0x2e4)=1.0f;
   }
   stealth->markAsDetected(data->m_updateRate+1,true);
   if(data->field13a && stealth->field2d())stealth->update002AD250();
   if(data->m_IRGridParticleSysTmpl){
    BfmeVec3 sys=((Rva005C3A30*)TheParticleSystemManager)->make(data->m_IRGridParticleSysTmpl,(void*)1);
    if(sys.value){Coord3D gridPosition;gridPosition.x=them->position()->x;gridPosition.y=them->position()->y;gridPosition.z=self->position()->z+17;gridPosition.x-=((int)gridPosition.x)%12;gridPosition.y-=((int)gridPosition.y)%12;sys.value->setPosition(&gridPosition);}
   }
  } else {
   Rva002AB690Contain *contain=them->contain();if(contain && contain->isGarrisonable() && contain->getStealthUnitsContained()){
    for(Rva002AB690Contained::const_iterator it=contain->getItems()->begin();it!=contain->getItems()->end();++it){
     Object *rider=*it;StealthUpdate *stealth=(StealthUpdate*)rider->findModule(key);if(stealth){foundSomeone=true;if(self->getControllingPlayer()!=rider->getControllingPlayer() && self->getRelationship(rider)!=2)stealth->markAsDetected(data->m_updateRate+2,true);}
    }
   }
  }
 }
 if(data->m_IRGridParticleSysTmpl && self->getShroudedStatus(Rva002EE330ThePlayers->local()->index())<=2){
  Drawable *myDraw=self->getDrawable();Coord3D bonePosition={-1.66f,5.5f,15};
  if(myDraw)((const BFMEDrawableBoneQuery*)myDraw)->getPristineBonePositions(data->m_IRParticleSysBone.str(),0,&bonePosition,0,1,0);
  void *pingTemplate=foundSomeone?data->m_IRBrightParticleSysTmpl:data->m_IRParticleSysTmpl;
  if(pingTemplate){BfmeVec3 sys=((Rva005C3A30*)TheParticleSystemManager)->make(pingTemplate,(void*)1);if(sys.value){if(myDraw)sys->attachToDrawable(myDraw);else sys->attachToObject(self);sys->setPosition(&bonePosition);}}
  void *beaconTemplate=data->m_IRBeaconParticleSysTmpl;
  if(beaconTemplate){BfmeVec3 sys=((Rva005C3A30*)TheParticleSystemManager)->make(beaconTemplate,(void*)1);if(sys.value){if(myDraw)sys->attachToDrawable(myDraw);else sys->attachToObject(self);sys->setPosition(&bonePosition);}}
  AudioEventRTS IRPingSound(Rva01336E50EmptyAscii,0);
  if(foundSomeone)IRPingSound.assign(data->m_loudPingSound);else IRPingSound.assign(data->m_pingSound);
  IRPingSound.setObjectID((ObjectID)self->id());Rva012ed668->addAudioEvent(&IRPingSound);
 }
 return (UpdateSleepTime)data->m_updateRate;
}
