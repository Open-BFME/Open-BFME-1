// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
// Retail 0x00293E50: update-state and model-condition cleanup with Lua notification.
template<int N> class BitFlags { public: enum Init { kInit }; BitFlags(Init,int bit) { bits.set(bit); } _STL::bitset<N> bits; };
class Drawable { friend class FlameCleanup00293E50; private: void applyPendingModelConditionFlags(bool); };
class Module;
enum NameKeyType { KEY_NONE=0 };
class NameKeyGenerator { public: NameKeyType nameToKey(const char*); };
extern NameKeyGenerator* TheNameKeyGenerator;
#define OBJECT_TU_MEMBERS void setStatus(const BitFlags<86>&,bool); void notifyModelConditionChanged(); Module* findModule(NameKeyType) const;
#include "../object.h"
class Rva001C1EA0Object { public: void rva001C1EA0(bool); };
class BfmeMarksYE { public: void bfmeSetYE(unsigned char,unsigned char); };
class Rva002918E0Object { public: void set(unsigned char); };
class BfmeDelayedLuaEvent { public: ~BfmeDelayedLuaEvent(); char data[0x18]; };
class BfmeDelayedLuaEventListBase { public: virtual ~BfmeDelayedLuaEventListBase() {} };
class __declspec(novtable) DelayedLuaEventList : public BfmeDelayedLuaEventListBase { public: DelayedLuaEventList(); __forceinline ~DelayedLuaEventList() {} BfmeDelayedLuaEvent events[3]; };
class BfmeOwnerBR { public: void bfmeGo939B(int,Object*,DelayedLuaEventList*); };
extern BfmeOwnerBR* g_script00293E50;
enum UpdateSleepTime { SLEEP1=1 };
class UpdateModule { protected: void setWakeFrame(Object*,UpdateSleepTime); };
struct Config00293E50 { char pad00[0x31]; bool at31; char at32; bool at33; };
class FlameCleanup00293E50 : public UpdateModule { public: void apply(); char pad00[4]; Config00293E50* at04; Object* at08; char pad0c[0x1c]; int at28; };
void FlameCleanup00293E50::apply() {
 Config00293E50* config=at04;
 Object* object=at08;
 at28=1;
 setWakeFrame(object,SLEEP1);
 object->setStatus(BitFlags<86>(BitFlags<86>::kInit,3),false);
 object->setStatus(BitFlags<86>(BitFlags<86>::kInit,5),false);
 object->setStatus(BitFlags<86>(BitFlags<86>::kInit,11),true);
 unsigned& flags=*(unsigned*)((char*)object+0x118);
 if(!(flags&0x8000)) { flags|=0x8000; object->notifyModelConditionChanged(); }
 ((Rva001C1EA0Object*)object)->rva001C1EA0(false);
 static NameKeyType key=TheNameKeyGenerator->nameToKey("EntEnragedUpdate");
 Module* enraged=object->findModule(key);
 if(enraged) { ((BfmeMarksYE*)enraged)->bfmeSetYE(0,0); ((Rva002918E0Object*)enraged)->set(0); }
 unsigned& other=*(unsigned*)((char*)object+0x124);
 if(config->at31 && (other&0x100000)) { other&=~0x100000; object->notifyModelConditionChanged(); }
 if(config->at33 && (other&0x200000)) { other&=~0x200000; object->notifyModelConditionChanged(); }
 if(config->at31 || config->at33) object->getDrawable()->applyPendingModelConditionFlags(true);
 DelayedLuaEventList events;
 g_script00293E50->bfmeGo939B(11,object,&events);
}


