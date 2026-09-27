// Retail 0x00299250: stealth state cleanup and conditional audio notification.
// Address-derived module owner; offsets read directly from retail.
struct AudioEventInfoRef { void* ptr; };
enum ObjectID { INVALID_ID=0 };
class AudioEventRTS {
public:
 AudioEventRTS(const AudioEventInfoRef&,ObjectID);
 ~AudioEventRTS();
 void* vtable; char data[108];
};
enum NameKeyType { INVALID_NAME=0 };
class NameKeyGenerator { public: NameKeyType nameToKey(const char*); };
extern NameKeyGenerator* TheNameKeyGenerator;
class StealthUpdate { public: void update002AD250(); char pad00[0x2d]; bool at2d; };
class Module;
enum ObjectStatusTypes { STATUS18=18 };
enum DamageType { DAMAGE8=8 }; enum DeathType { DEATH0=0 };
#define BFME_HAVE_OBJECTID
#define OBJECT_TU_MEMBERS Module* findModule(NameKeyType) const; void clearStatus(ObjectStatusTypes); void bfmeApplySpecialModelCondition(int,const void*,int); void kill(DamageType,DeathType);
#include "../object.h"
class GameLogic { public: Object* findObjectByID(int); char pad00[0x3c]; unsigned at3c; };
extern GameLogic* TheBfmeGameLogic;
class AudioDispatch00299250 { public: virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c(); virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c(); virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c(); virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3c(); virtual void s40(); virtual void add(AudioEventRTS*); };
extern AudioDispatch00299250* g_audio00299250;
struct Config00299250 { char pad00[0x20]; AudioEventInfoRef at20; };
class StealthCleanup00299250 { public: void apply(); char pad00[4]; Config00299250* at04; Object* at08; char pad0c[0x18]; int at24; int at28; int at2c; unsigned at30; };
void StealthCleanup00299250::apply() {
 unsigned frame=TheBfmeGameLogic->at3c;
 Config00299250* config=at04;
 at30=frame;
 Object* object=at08;
 at28=0;
 static NameKeyType key=TheNameKeyGenerator->nameToKey("StealthUpdate");
 StealthUpdate* stealth=(StealthUpdate*)object->findModule(key);
 if(stealth && stealth->at2d) {
  stealth->update002AD250();
  object->clearStatus(STATUS18);
  object->bfmeApplySpecialModelCondition(5,0,1);
  if(config->at20.ptr) {
   ObjectID id=object->m_id;
   AudioEventRTS audio(config->at20,id);
   g_audio00299250->add(&audio);
  }
 }
 Object* previous=TheBfmeGameLogic->findObjectByID(at24);
 if(previous) { previous->kill(DAMAGE8,DEATH0); at24=0; }
}

