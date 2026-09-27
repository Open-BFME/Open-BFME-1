// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/Common/System
// stlport
// GameLogic ctor RVA003928E0. Layout cross-checked against the retail destructor.
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
template<> inline StringBase<char>::~StringBase() {releaseBuffer();}
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
public: GameLogic();virtual ~GameLogic();
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
 unsigned at108,at10c,at110;bool at114;char pad115[3];
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
GameLogic::GameLogic()
 : at034(0),at038(0),at03c(0),at040(false),at044(0),
 at068(false),at069(false),at06a(false),at06b(false),at06c(false),at06d(false),at074(false),
 at078("LoadingRing"),at07c("TitleScreen"),at08c(0),
 at090(false),at091(false),at092(false),at093(false),at094(false),at095(false),at096(false),
 at098(0),at09c(1),at0a0(false),at0a4(0),at0a8(0),at0ac(0),at100(0),
 at108(0),at10c(8),at110(1000),at114(false),m_loadScreen(0),at11c(false),at11d(false),at11e(true),at11f(true),
 m_forceGameStartByTimeOut(false),at14c(0),at150(0),at154(0),at158(0),at168(0),at16c(0),at1a0(0),at1a4(0),at1a8(false)
{
 for(int i=0;i<8;++i) {at120[i]=false;at128[i]=0;}
 at04c.clear();
 for(int j=0;j<8;++j) {
  at1b0[j].at010=true;
  at1b0[j].at004=0;
  at1b0[j].at008=0;
  at1b0[j].at00c=0;
  at1b0[j].at000=0;
  at1b0[j].at014=255;
 }
 at290=2;
}
typedef char GameLogicSize294[sizeof(GameLogic)==0x294?1:-1];

