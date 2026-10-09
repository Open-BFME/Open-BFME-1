// stlport
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x00208A50: SlowDeathBehavior constructor 0x00207B60 installs
// update-interface table 0x010A65E4; slot 0 routes through ILT 0x000030B2.
// This view starts at the full object +0x10. Control flow agrees with the
// Zero Hour SlowDeathBehavior::update twin; BFME-specific fields retain offsets.
// Complete extent is 1067 bytes: ret at +0x42A followed by int3 at +0x42B.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <bitset>
#include "ascii_string.h"
struct Coord3D;
struct Position208A50 { float x,y,z; };
class Rva00170C70BitSet { public: Rva00170C70BitSet(void*,unsigned); unsigned words[10]; };
template<int N> class BitFlags;
class S4Sink004135C0 { public: void invoke(const AsciiString&,int,int,int,int); };
class BfmeHostEX { public: void bfmeSetEX(float); };
class Thing { public: virtual void slot0(); float getHeightAboveTerrain() const; void setPosition(const Coord3D*); };
// Retail ILT19FF1/3F288 reach these existing matched native providers.
class BfmeOwnerRW { public: int bfmeCheckRW(); };
class BfmeInit962 { public: void bfmeInit962(int); };
class Drawable { public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot20(void*);
 char pad04[0xe0]; bool flagE4; char padE5[0x13]; float fieldF8;
 void setShadowsEnabled(bool);
};
class Module208A50 { public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot20();
};
enum DisabledType { DisabledHeld208A50=3 };
class Object : public Thing { public:
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
 virtual Drawable* drawable28();
 char pad04[0x34]; Position208A50 position38; char pad44[0xcc]; unsigned words110[10];
 char pad138[0x6c]; unsigned status1A4; char pad1A8[0x54]; Module208A50* module1FC;
 void notifyModelConditionChanged(); void setDisabled(DisabledType); void setStatusBit(int,bool); int getLayer() const;
 void clearAndSetModelConditionFlags(const BitFlags<320>&,const BitFlags<320>&);
 __forceinline void clear5() { if(*(unsigned char*)words110 & 32) { words110[0]&=~32u;notifyModelConditionChanged(); } }
 __forceinline void set5() { if(!(*(unsigned char*)words110 & 32)) { words110[0]|=32;notifyModelConditionChanged(); } }
};
struct Conditions208A50 { _STL::bitset<320> bits; bool test(int bit)const{return bits.test(bit);} void set(int bit){bits.set(bit);} };
static __forceinline void setCondition208A50(Object* object,int bit) {
 Conditions208A50* flags=(Conditions208A50*)object->words110;
 if(!flags->test(bit)) {flags->set(bit);object->notifyModelConditionChanged();}
}
class GameLogic { public: char pad00[0x3c]; unsigned frame3C; void destroyObject(Object*); };
extern GameLogic* TheGameLogic;
class GameLODManager { public: char pad00[0x16e0]; float scale16E0; };
extern GameLODManager* TheGameLODManager;
class Terrain208A50 { public:
 virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4();virtual void slot5();virtual void slot6();
 virtual float height1C(float,float,int,void*,bool);
};
// retail singleton: TerrainLogic *TheTerrainLogic (mangled ?TheTerrainLogic@@3PAVTerrainLogic@@A),
// defined in GameLogic/Map/TerrainLogic.cpp. Uses go through this TU's Terrain208A50 view.
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;
struct SlowDeathData208A50 {
 char pad00[0x34]; float sinkRate34; char pad38[0x128]; _STL::vector<AsciiString> names160;
 char shadow16C[0x30]; int delay19C; unsigned sentinel1A0; unsigned char mask1A4; char pad1A5; bool flag1A6;
};
enum UpdateSleepTime { UPDATE_SLEEP_NONE=1,UPDATE_SLEEP_FOREVER=0x3fffffff };
enum SlowDeathPhaseType { SDPHASE_INITIAL,SDPHASE_MIDPOINT,SDPHASE_FINAL,SDPHASE_LANDED208A50 };
class SlowDeathBehavior { public:
 virtual UpdateSleepTime update();
 char pad04[0x14]; unsigned m_sinkFrame,m_midpointFrame,m_destructionFrame,frame24; float m_acceleratedTimeScale; unsigned m_flags;
 bool flag30; char pad31[7]; bool flag38; char pad39[3]; unsigned frame3C;
 Object* getObject() {return *(Object**)((char*)this-8);}
 SlowDeathData208A50* getData() {return *(SlowDeathData208A50**)((char*)this-12);}
protected: void doPhaseStuff(SlowDeathPhaseType);
};
UpdateSleepTime SlowDeathBehavior::update() {
 SlowDeathData208A50* d=getData();
 Object* obj=getObject();
 if(!obj) return UPDATE_SLEEP_FOREVER;
 float timeScale=TheGameLODManager->scale16E0;
 if(timeScale!=1.0f && m_acceleratedTimeScale==1.0f && !(d->mask1A4&6)) {
  if(timeScale==0) { TheGameLogic->destroyObject(obj);return UPDATE_SLEEP_NONE; }
  m_sinkFrame=(float)m_sinkFrame*timeScale;
  m_midpointFrame=(float)m_midpointFrame*timeScale;
  m_destructionFrame=(float)m_destructionFrame*timeScale;
  frame24=(float)frame24*timeScale;
  m_acceleratedTimeScale=timeScale;
  frame3C=(float)frame3C*timeScale;
 }
 unsigned now=TheGameLogic->frame3C;
 if((m_flags&4) && !(m_flags&8)) {
  ++m_sinkFrame; ++m_midpointFrame; ++m_destructionFrame; ++frame3C;
  if(frame24) ++frame24;
  if(!(obj->getHeightAboveTerrain()>0.0f)) {
   obj->clearAndSetModelConditionFlags((const BitFlags<320>&)Rva00170C70BitSet(0,113),(const BitFlags<320>&)Rva00170C70BitSet(0,114));
   m_flags|=8;
  }
 }
 if(flag30) {
  obj->clear5();
  if(obj->getHeightAboveTerrain()<1.0f) {
   flag30=false;
   ((SlowDeathBehavior*)((char*)this-16))->doPhaseStuff(SDPHASE_LANDED208A50);
   obj->set5();
   Module208A50* module=getObject()->module1FC;
   if(module) module->slot20();
   Drawable* drawable=getObject()->drawable28();
   if(drawable) {
    for(unsigned i=0;i<d->names160.size();++i)
     ((S4Sink004135C0*)drawable)->invoke(d->names160[i],0,0,0,0);
   }
  }
 }
 Drawable* drawable=obj->drawable28();
 if(drawable && now>=frame3C && d->sentinel1A0!=0xfacade00 && !flag38) {flag38=true;((BfmeInit962*)drawable)->bfmeInit962(d->delay19C);}
 if(now>=m_sinkFrame && d->sinkRate34>0.0f) {
  if(!(obj->status1A4&8) && !(unsigned char)((BfmeOwnerRW*)obj)->bfmeCheckRW()) obj->setDisabled(DisabledHeld208A50);
  obj->setStatusBit(55,true);
  Position208A50 pos; pos.x=obj->position38.x; pos.y=obj->position38.y; pos.z=obj->position38.z;
  pos.z-=d->sinkRate34/m_acceleratedTimeScale;
  if(((Terrain208A50*)TheTerrainLogic)->height1C(pos.x,pos.y,obj->getLayer(),0,true)<pos.z) pos.z-=5.7f;
  obj->setPosition((const Coord3D*)&pos);
  if(drawable && d->flag1A6 && !drawable->flagE4) {
   drawable->setShadowsEnabled(false);
   drawable->slot20(&d->shadow16C);
   drawable->flagE4=true;
   ((BfmeHostEX*)drawable)->bfmeSetEX(0.0f);
   drawable->fieldF8=0.003f;
  }
 }
 if(now>=m_midpointFrame && !(m_flags&2)) {((SlowDeathBehavior*)((char*)this-16))->doPhaseStuff(SDPHASE_MIDPOINT);m_flags|=2;}
 if(now>=m_destructionFrame) {((SlowDeathBehavior*)((char*)this-16))->doPhaseStuff(SDPHASE_FINAL);TheGameLogic->destroyObject(obj);}
 if(frame24 && now>=frame24) setCondition208A50(obj,143);
 return UPDATE_SLEEP_NONE;
}
