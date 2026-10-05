// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/Common/System
// stlport
// GameLogic::reset RVA0038F4B0. Layout reused from the landed constructor
// RVA003928E0 and cross-checked against this body and the retail destructor.
// The map identities are independently witnessed by BuildableStatusHashMap.cpp,
// GameLogicOverridesAndTimeouts.cpp and GameLogicObjectLookupTable.cpp. Each of
// their three bucket initializers is a 106-byte native STLport match, reached
// through ILTs 0002233B / 00047C99 / 0001DCEB at +0C / +20 / +B0 respectively.
// GameLogicAwakenUpdate.cpp and GameLogicProcessDestroyList.cpp establish the
// four UpdateModule-pointer phase vectors, sleeping vector and Object-pointer
// destruction list. +4C is the captured CRC stream list (GameLogicCRC.cpp).
// Constructor also initializes the final word at +290: complete extent is 294 bytes.
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <list>
#include <vector>
#include "ascii_string.h"
typedef bool Bool;
#include "subsystem_interface.h"
#include "snapshot.h"
enum BuildableStatus {};
class CommandButton;
namespace rts {
 template<class T> struct hash;
 template<class T> struct equal_to;
 template<> struct hash<AsciiString> {unsigned operator()(AsciiString)const;};
 template<> struct equal_to<AsciiString> {int operator()(const AsciiString&,const AsciiString&)const;};
}
class Object;
class UpdateModule;
class BfmeByteStream;
extern void j_0000b5cd();
typedef std::hash_map<AsciiString,BuildableStatus,rts::hash<AsciiString>,rts::equal_to<AsciiString> > CtorBuildableMap;
typedef std::hash_map<AsciiString,const CommandButton*,rts::hash<AsciiString>,rts::equal_to<AsciiString> > CtorControlMap;
typedef std::hash_map<int,Object*> CtorObjectMap;
class Gen_00366B90 {
public: Gen_00366B90();
 ~Gen_00366B90() {typedef void(Gen_00366B90::*P)();union{void(*raw)();P member;}r={j_0000b5cd};(this->*r.member)();}
private: unsigned at000[12];
};
class Rva00386070 {
public:
 Rva00386070(); ~Rva00386070() {}
 unsigned at000,at004,at008,at00c; bool at010; char pad011[3];unsigned at014;AsciiString at018;
};
class GameLogic : public SubsystemInterface, public Snapshot {
public: GameLogic();virtual ~GameLogic(); virtual void reset(); void setDefaults(bool); void closeWindows();
private:
 CtorBuildableMap at00c;
 CtorControlMap m_controlBarOverrides;
 unsigned at034,at038,at03c; bool at040;char pad041[3];unsigned at044,at048;
 std::list<BfmeByteStream*> at04c;
 AsciiString at050;
 std::vector<AsciiString> at054;
 AsciiString at060,at064;
 bool at068,at069,at06a,at06b,at06c,at06d; char pad06e[2];
 AsciiString at070;
 bool at074; char pad075[3];
 AsciiString at078,at07c,at080,at084,at088;
 unsigned at08c;
 bool at090,at091,at092,at093,at094,at095,at096;char pad097;
 unsigned at098,at09c;bool at0a0;char pad0a1[3];unsigned at0a4,at0a8,at0ac;
 CtorObjectMap at0b0;
 std::vector<UpdateModule*> at0c4[4];
 std::vector<UpdateModule*> at0f4;
 unsigned at100;
 std::list<Object*> at104;
 unsigned at108,m_gameMode,at110;bool at114;char pad115[3];
 void *m_loadScreen;
 bool at11c,at11d,at11e,at11f;
 bool at120[8];unsigned at128[8];
 bool m_forceGameStartByTimeOut;char pad149[3];unsigned at14c,at150,at154,at158;
 std::vector<unsigned> at15c;unsigned at168,at16c;
 Gen_00366B90 at170;
 unsigned at1a0,at1a4;bool at1a8;char pad1a9[3];
 struct ObjectTOCEntry {AsciiString name;unsigned short id;};
 std::list<ObjectTOCEntry> at1ac;
 Rva00386070 at1b0[8];
 unsigned at290;
};

// reset identity: GameLogic vtable VA 010EB574 slot 4 -> ILT 0000128F -> 0038F4B0.
// Complete retail extent is 614 bytes through RET at 0038F715.
extern void setFPMode();
extern void j_0002c327(); extern void j_0002775a(); extern void j_00044b16();
extern void j_00040cf0(); extern void j_00041641(); extern void j_00016f09();
extern void j_0004a133(); extern void j_0000324c();
struct CallReceiver0038F4B0 {};
inline void call0_0038F4B0(void* p, void (*f)()) {
 typedef void(CallReceiver0038F4B0::*M)(); union { void(*f)(); M m; } u={f};
 (((CallReceiver0038F4B0*)p)->*u.m)();
}
inline void call1_0038F4B0(void* p, void (*f)(), unsigned n) {
 typedef void(CallReceiver0038F4B0::*M)(unsigned); union { void(*f)(); M m; } u={f};
 (((CallReceiver0038F4B0*)p)->*u.m)(n);
}
class ResetSlot0038F4B0 {public: virtual ~ResetSlot0038F4B0(); virtual void slot1();virtual void slot2();virtual void slot3();virtual void reset();};
#define GLOBAL(C,N) class C; extern C* N;
GLOBAL(GhostObjectManager,TheGhostObjectManager)
GLOBAL(PartitionManager,ThePartitionManager)
GLOBAL(ShroudManager,TheShroudManager)
GLOBAL(CollisionManager,TheCollisionManager)
GLOBAL(TaintManager,TheTaintManager)
GLOBAL(TerrainLogic,TheTerrainLogic)
GLOBAL(AI,TheAI)
GLOBAL(ScriptEngine,TheScriptEngine)
GLOBAL(LargeGroupAudio,TheLargeGroupAudio)
GLOBAL(Manager012EF4F0,g_012EF4F0)
class StatsCollector { public: ~StatsCollector() {call0_0038F4B0(this,j_00016f09);} }; extern StatsCollector* TheStatsCollector;
class Overridable {public:virtual ~Overridable(); Overridable* at004; bool at008;
 Overridable* deleteOverrides();
};
template<class T> class OVERRIDE {public: T* ptr;};
class WaterTransparencySetting; extern OVERRIDE<WaterTransparencySetting> TheWaterTransparency;
class WeatherSetting; extern OVERRIDE<WeatherSetting> TheWeatherSetting;
struct TocNode0038F4B0 {TocNode0038F4B0 *next,*prev;unsigned name;unsigned short id;};
void GameLogic::reset() {
 if(!at1a0) setFPMode(); ++at1a0;
 call0_0038F4B0(&at00c,j_0002c327);
 call0_0038F4B0(&m_controlBarOverrides,j_0002775a);
 call0_0038F4B0(&at0b0,j_00044b16);
 call1_0038F4B0(&at0b0,j_00040cf0,8192);
 at11c=false;at11d=false;at11e=true;at11f=true;at096=true;
 setFPMode();at14c=0;at150=0;at154=0;at158=0;
 call0_0038F4B0(this,j_00041641);
 at108=1;at16c=0;
 ((ResetSlot0038F4B0*)TheGhostObjectManager)->reset();
 ((ResetSlot0038F4B0*)ThePartitionManager)->reset();
 ((ResetSlot0038F4B0*)TheShroudManager)->reset();
 ((ResetSlot0038F4B0*)TheCollisionManager)->reset();
 ((ResetSlot0038F4B0*)TheTaintManager)->reset();
 ((ResetSlot0038F4B0*)((char*)TheTerrainLogic+4))->reset();
 ((ResetSlot0038F4B0*)TheAI)->reset();
 ((ResetSlot0038F4B0*)TheScriptEngine)->reset();
 ((ResetSlot0038F4B0*)TheLargeGroupAudio)->reset();
 ((ResetSlot0038F4B0*)((char*)g_012EF4F0+4))->reset();
 for(int i=0;i<8;++i) {at120[i]=false;at128[i]=0;}
 m_forceGameStartByTimeOut=false;
 if(TheStatsCollector) {delete TheStatsCollector;TheStatsCollector=0;}
 TocNode0038F4B0*& head=*(TocNode0038F4B0**)&at1ac;
 TocNode0038F4B0* cur=head->next;
 while(cur!=head) {TocNode0038F4B0* old=cur;cur=cur->next;call0_0038F4B0(&old->name,j_0004a133);std::__node_alloc<true,0>::deallocate(old,16);}
 head->next=head;head->prev=head;
 setDefaults(false);
 at090=true;at091=true;at092=true;at093=true;at098=-1;at09c=1;
 {Overridable* p=(Overridable*)TheWaterTransparency.ptr;
 if(p->at008) {delete p;p=0;}
 else if(p->at004) {p->at004=p->at004->deleteOverrides();}
 TheWaterTransparency.ptr=(WaterTransparencySetting*)p;}
 {Overridable* p=(Overridable*)TheWeatherSetting.ptr;
 if(p->at008) {delete p;p=0;}
 else if(p->at004) {p->at004=p->at004->deleteOverrides();}
 TheWeatherSetting.ptr=(WeatherSetting*)p;}
 at08c=0;at168=0;call0_0038F4B0(this,j_0000324c);at06c=false;closeWindows();
 at040=false;at03c=0;at290=2;--at1a0;
}

typedef char GameLogicResetSize294[sizeof(GameLogic)==0x294?1:-1];
