// Rva00597FC0Client::update at RVA 0x00598950 (1119 bytes).
// Retains the established vtable-slot identity from symbols.csv. The receiver
// offsets and bit fields are witnessed by this body; unknown names stay numeric.
// The zero-stack-argument dump callees use ECX; a one-argument fastcall cast
// expresses that same machine ABI without asserting a semantic method identity.
// SubRefresh and Handle keep the inlined receiver lifetimes present in retail.
// The four-byte eligibility scratch preserves VC7.1's stack-slot allocation;
// only byte zero is written/read, as in retail's byte result and map<bool> store.
// stlport
// cl: /Igame/Libraries/Source/WWVegas/WWLib /D_STLP_USE_STATIC_LIB
#include <map>
#include "ascii_string.h"
class GenString;
class GameLogic { public: bool _bfme_isInMultiplayerGame(); };
class GameLogicPortraitShim { public: bool isInMultiplayerOrSkirmishGame(); };
extern GameLogic *TheGameLogic;
class BfmeThingAOA { public: void bfmeGoAOA(); };
extern BfmeThingAOA *Radar00598950;
class Rva000DF7F0 { public: int inactive() const; };
class BfmeMemberRV;
class BfmeThingRV { public: BfmeMemberRV *bfmePickRV(); };
extern BfmeThingRV *Players00598950;
class Rva003BDF70Owner { public: int combinedSpanCount(); };
class CampaignManager { public: unsigned char isMissionObjectiveEligible(int); };
extern CampaignManager *TheLivingWorldLogic;
extern void *Campaign00598950;
extern void *g_obj12F49E4;
class AptPalantirStore { public: void rva00591b60(); };
class BfmeThingCDA { public: void bfmeStepCDA(); };
class Rva00593E60State { public: void update(); };
class Rva00592570ResourceImageSlot { public: void cacheResourceImage(const AsciiString&); };
class Rva00592A90ResourceImageSlot { public: void cacheResourceImage(const AsciiString&); };
class Rva00494410RatioOwner { public: float getRatio(); };
class BfmeThingECHb { public: void bfmeGoECHb(); };
class Rva00564940 { public: static void go(); };
void bfmeGo993B();
int bfmeQuiet();
int Rva00589320();
void bfmeGo1021G(int);
void Rva00564E40();void Rva00564EA0();void Rva00564E70();void Rva00564ED0();void Rva00564F00();void Rva00564F30();
void Rva00564F60(bool);void Rva00564B00(bool);void bfmePowerCapZB(int);void SetPlayerFaction(const GenString*);
void j_0003f198();void j_00034a86();void j_0001bc70();void j_00035431();void j_0002f51d();
typedef void (__fastcall *Call00598950)(void*);
template<class T> inline T &at00598950(void *p,int offset) { return *(T*)((char*)p+offset); }
struct SubState00598950 { char pad0[0x1f4];int field1f4; };
struct Transition00598950 {
 virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4();virtual void slot5();
 char pad4[0x1c]; unsigned char flags20;char pad21[3];unsigned value24;
};
struct Bits00598950 { unsigned char b0:1,b1:1,b2:1,b3:1,b4:1,b5:1,b6:1,b7:1; };
struct SubRefresh00598950 { bool byte0,byte1;char pad2[2];int field4;
 void refresh() {int old=field4;field4=0;byte0=false;((BfmeThingCDA*)this)->bfmeStepCDA();field4=old;byte0=true;}
};
struct Counter00598950 { int remaining,value; int tick() { return --remaining; } int getValue() const { return value; } };
struct Handle00598950 { Counter00598950 *p; Counter00598950 *get() const {return p;}
 __forceinline int adjust(int n) {
  if(p) {
   int count=p->tick();
   if(count<=0) {((BfmeThingECHb*)this)->bfmeGoECHb();Rva00564940::go();}
   else n-=get()->value;
  }
  return n;
 }
};
class Rva00597FC0Client { public:
 virtual void update();
 SubState00598950 *stateAt0c() const { return field_c; }
 char pad4[8];SubState00598950 *field_c;Transition00598950 *field_10;char pad14[0x28-0x14];unsigned field_28;char pad2c[0x4c-0x2c];
 bool byte_4c;char pad4d[0x58-0x4d];Bits00598950 bits58;char pad59[3];int field_5c;int field_60;int field_64;
 char field_68[0x154-0x68];char field_154[0x17c-0x154];char field_17c[0x2b8-0x17c];char field_2b8[0x460-0x2b8];char field_460[0x488-0x460];char field_488[0x4c5-0x488];
 bool byte_4c5;char pad4c6[2];int field_4c8;Counter00598950 *field_4cc;int field_4d0;bool byte_4d4;char pad4d5[3];AsciiString field_4d8;char pad4dc[0x4fc-0x4dc];std::map<int,bool> field_4fc;
};
void Rva00597FC0Client::update()
{
 ((AptPalantirStore*)field_154)->rva00591b60();
 ((Call00598950)j_0003f198)(field_17c);
 ((Call00598950)j_00034a86)(field_2b8);
 if(!(unsigned char)bfmeQuiet()) return;
 int mode=Rva00589320();
 if(mode!=field_4c8) {
  bfmeGo1021G(mode);field_4c8=mode;field_64=1;field_5c=-1;
  *(unsigned char*)&bits58 &= 0xc4;
  if(field_68[1]) {
   ((SubRefresh00598950*)field_68)->refresh();
  }
  return;
 }
 ((Call00598950)j_0001bc70)(field_68);
 Rva00592570ResourceImageSlot *resourceSlot=(Rva00592570ResourceImageSlot*)field_460;
 ((Call00598950)j_00035431)(resourceSlot);
 Rva00592A90ResourceImageSlot *helpSlot=(Rva00592A90ResourceImageSlot*)field_488;
 ((Rva00593E60State*)helpSlot)->update();
 if(byte_4c) { if(Radar00598950) Radar00598950->bfmeGoAOA(); bfmeGo993B();byte_4c=false; }
 bool active=false;
 if(field_10->flags20 & 1) {
  if((field_10->flags20&4) && !(field_10->value24&0xff000000)) field_10->slot4();
  else { field_10->slot5();active=!(field_10->flags20&4) && ((Rva00494410RatioOwner*)field_10)->getRatio()>0.5f; }
 }
 if(bits58.b6!=active) {
  if(active) {Rva00564E40();Rva00564EA0();stateAt0c()->field1f4=1;}
  else {Rva00564E70();Rva00564ED0();stateAt0c()->field1f4=0;}
  bits58.b6=active;
 }
 bool inactive=TheGameLogic && TheGameLogic->_bfme_isInMultiplayerGame() && (unsigned char)((Rva000DF7F0*)Players00598950)->inactive();
 if(inactive!=bits58.b7) {if(inactive) Rva00564F00();else Rva00564F30();bits58.b7=inactive;}
 if(!byte_4c5) {
  if(TheLivingWorldLogic && (!at00598950<bool>(TheLivingWorldLogic,0x2c) || !at00598950<bool>(TheLivingWorldLogic,0x2d)) &&
    !((GameLogicPortraitShim*)TheGameLogic)->isInMultiplayerOrSkirmishGame()) {
   int count=((Rva003BDF70Owner*)TheLivingWorldLogic)->combinedSpanCount();
   for(int i=0;i<count;++i) {
    bool old=false;
    std::map<int,bool>::iterator it=field_4fc.find(i);
    if(it!=field_4fc.end()) old=it->second;
    bool value[4]; *(unsigned char*)&value[0]=TheLivingWorldLogic->isMissionObjectiveEligible(i);
    if(value[0]!=old) { if(!old && value[0]) byte_4c5=true;field_4fc[i]=value[0]; }
   }
  }
 } else if(g_obj12F49E4) byte_4c5=false;
 if(bits58.b5!=byte_4c5) {Rva00564F60(byte_4c5);bits58.b5=byte_4c5;}
 AsciiString side;
 if(TheLivingWorldLogic && at00598950<bool>(TheLivingWorldLogic,0x2c) && at00598950<bool>(TheLivingWorldLogic,0x2d)) {
  bool value=at00598950<bool>(Campaign00598950,0x1c);
  if(value!=byte_4d4) {Rva00564B00(value);byte_4d4=value;}
  int n=at00598950<int>(TheLivingWorldLogic,0xa0);
  n=((Handle00598950*)&field_4cc)->adjust(n);
  if(n!=field_4d0) {bfmePowerCapZB(n);field_4d0=n;}
 } else {
  delete field_4cc;field_4cc=0;
  ((Call00598950)j_0002f51d)(this);
  BfmeMemberRV *player=Players00598950->bfmePickRV();
  AsciiString &overrideSide=at00598950<AsciiString>(player,0x698);
  const char *p=*(const char *const*)&overrideSide;
  if(p && *(const unsigned short*)(p+4)) side=overrideSide;
  else {
   void *playerTemplate=at00598950<void*>(player,4);
   if(playerTemplate && at00598950<bool>(playerTemplate,0xbd)) side=at00598950<AsciiString>(playerTemplate,8);
  }
 }
 if(((StringBase<char>*)&side)->compare(*(StringBase<char>*)&field_4d8)!=0) {
  resourceSlot->cacheResourceImage(side);
  helpSlot->cacheResourceImage(side);
  SetPlayerFaction((const GenString*)&side);
  field_4d8=side;
 }
}
