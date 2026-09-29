// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include <bitset>
#include "string_base.h"
template<> inline bool StringBase<char>::isEmpty() const { return !m_data || !m_data->length; }
#include "ascii_string.h"
extern "C" __declspec(dllimport) int __cdecl sprintf(char*,const char*,...);
// RVA 0x0022BA20 / 441 bytes. SiegeEngineContain constructor 0x0022BC50
// installs primary table VA 0x010AD088; slot 27 reaches this body via 0x0001E191.
// The same slot in TransportContain is createPayload; this body finishes with
// the qualified base call via 0x0003A355. The first payload name/count live at
// module-data +0x22c/+0x230. Their original member spellings are unproved.
// Object name storage +0x84 is a StringBase<char>: retail tests its 16-bit
// length, formats "%s%d", then invokes the char string assignment body.
// The inherited frame receiver is the primary module (data +4; object +8).
// Canonical string types above retain the witnessed native inline operations.
class Team;
class Player { public: char pad[0x230]; Team* team230; };
class Object;
extern void j_0002852e();
class PayloadApply0022BA20 { public: void apply(int,int); };
class PayloadContain0022BA20 { public:
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
 virtual bool isValidContainerFor(Object*,bool);
 virtual void addToContain(Object*);
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
 virtual void slot56();
 virtual void slot57();
 virtual void slot58();
 virtual void slot59();
 virtual void slot60();
 virtual void slot61();
 virtual void slot62();
 virtual void slot63();
 virtual void slot64();
 virtual void slot65();
 virtual void slot66();
 virtual void slot67();
 virtual void slot68();
 virtual void slot69();
 virtual void slot70();
 virtual void slot71();
 virtual void slot72();
 virtual void slot73();
 virtual void slot74();
 virtual void slot75();
 virtual void slot76();
 virtual void slot77();
 virtual void enableLoadSounds(bool);
};
class Object { public:
 Player* getControllingPlayer() const;
 void apply(int first,int second) {
  typedef void (PayloadApply0022BA20::*Call)(int,int);
  union { void (*raw)(); Call member; } call;
  call.raw=j_0002852e;
  (((PayloadApply0022BA20*)this)->*call.member)(first,second);
 }
 char pad000[0x84]; AsciiString m_name; char pad088[0x174]; PayloadContain0022BA20* m_contain;
};
#pragma comment(linker,"/alternatename:?apply@Object@@QAEXHH@Z=?j_0002852e@@YAXXZ")
class ThingTemplate { public: char pad[0x2f4]; float field2f4; };
template<int N> class BitFlags { public: _STL::bitset<N> words; };
class ThingFactory { public:
 const ThingTemplate* findTemplate(const AsciiString&);
 Object* newObject(const ThingTemplate*,Team*,const BitFlags<86>&,unsigned);
};
extern ThingFactory* TheThingFactory;
#pragma comment(linker,"/alternatename:?findTemplate@ThingFactory@@QAEPBVThingTemplate@@ABVAsciiString@@@Z=?j_00028560@@YAXXZ")
struct PayloadData0022BA20 { char pad[0x22c]; AsciiString field22c; int field230; };
class TransportContain { protected: virtual void createPayload(); };
class SiegeEngineContain : public TransportContain { protected:
 virtual void createPayload();
 PayloadData0022BA20* data; Object* object;
};
#pragma comment(linker,"/alternatename:?createPayload@TransportContain@@MAEXXZ=?j_0003a355@@YAXXZ")
void SiegeEngineContain::createPayload() {
 PayloadData0022BA20* self=data;
 int count=self->field230;
 const ThingTemplate* payloadTemplate=self->field22c.isEmpty() ? 0 : TheThingFactory->findTemplate(self->field22c);
 Object* owner=object;
 PayloadContain0022BA20* contain=owner->m_contain;
 if(contain && payloadTemplate) {
  contain->enableLoadSounds(false);
  for(int i=0;i<count;++i) {
   BitFlags<86> status;
   Team* team=owner->getControllingPlayer()->team230;
   Object* payload=TheThingFactory->newObject(payloadTemplate,team,status,0);
   if(contain->isValidContainerFor(payload,true)) {
    int value=(int)(payloadTemplate->field2f4*5.0f);
    if(value>0) payload->apply(207,value);
    if(!owner->m_name.isEmpty()) {
     char name[256]; sprintf(name,"%s%d",owner->m_name.str(),i);
     payload->m_name=AsciiString(name);
    }
    contain->addToContain(payload);
   }
  }
  contain->enableLoadSounds(true);
 }
 TransportContain::createPayload();
}
