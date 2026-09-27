// ?startNewGame@GameLogic@@QAEX_N@Z
// partial score=0.3205547559858694 date=2026-09-27
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/buddythread /Iinputs/reference/shims/sweep
// stlport
// BANKED RECONSTRUCTION, NOT VERIFIED FOR LANDING.
// Full 7643-byte extent ends at RVA 0039603B; legacy lift row is three bytes short.
// 370 calls in retail order after resolving ILT routes and comparing virtual slots.
// Frame 0x340. Local object homes, EH-state scheduling and register allocation differ.
// checkForDuplicateColors is compiled here for its private EBX ABI; its 104 bytes
// match modulo relocations. This helper is already landed elsewhere, not new progress.
// Still-unresolved data identities: G012ED5F4, G012F089C, G012F7090. No speculative pins.
// Address-derived views record disassembled offsets and call ABIs; they are not
// claims of recovered semantic type identities. Further ABI and DIR32 validation required.
// Retail direct-call and virtual-slot contracts are retained by address-derived adapters.
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <windows.h>
#include <stdio.h>
extern "C" __declspec(dllimport) void* __stdcall GetSystemMenu(void*,int);
extern "C" __declspec(dllimport) int __stdcall EnableMenuItem(void*,unsigned,unsigned);
#define SC_CLOSE 0xf060
#define MF_GRAYED 1
#define MF_ENABLED 0
#include <set>
#include <vector>
#include <string>
#include "ascii_string.h"
template<class T,int N> inline T &F(void *p) { return *(T*)((char*)p+N); }
class GameInfo;
class GameLogic { public: void startNewGame(bool); };
struct Coord00394260 { float x,y,z; };
struct Region00394260 { Coord00394260 lo,hi; };
struct Matrix00394260 {
 float m[3][4];
 Matrix00394260() {
  m[0][0]=1; m[0][1]=0; m[0][2]=0; m[0][3]=0;
  m[1][0]=0; m[1][1]=1; m[1][2]=0; m[1][3]=0;
  m[2][0]=0; m[2][1]=0; m[2][2]=1; m[2][3]=0;
 }
};
struct Encoded00394260 { unsigned uninitialised,value; Encoded00394260(bool b):value(b?0x637ab774:0x412a3267) {} Encoded00394260(const Encoded00394260 &b):value(b.value) {} ~Encoded00394260() {} };
struct ObjectMap00394260 { void *object,*mapObject; };
typedef _STL::vector<ObjectMap00394260> ObjectMapVector00394260;
struct Rva001408C0Target;
struct AssetList00394260 {
 _STL::set<Rva001408C0Target*> prototypes;
 unsigned field_c; bool changed;
 AssetList00394260():field_c(0),changed(true) {}
};
struct Flags00394260 { unsigned words[3]; Flags00394260() { words[0]=0;words[1]=0;words[2]=0; } };
typedef unsigned short WideChar; typedef bool Bool; typedef unsigned UnsignedInt;
#include "GameNetwork/GameSpy/BuddyThread.h"
typedef BuddyRequest Message00394260;
inline const char *str00394260(const AsciiString &s) { void *p=*(void* const*)&s; return p?(const char*)p+8:""; }
class Receiver00394260 {};
class StaticNameKey; extern const StaticNameKey TheKey_InitialCameraPosition;
#define G012A7A00 (*(int*)&TheKey_InitialCameraPosition)
extern void *ApplicationHWnd;
#define G012ED238 ApplicationHWnd
extern bool g012ED4E5;
#define G012ED4E5 g012ED4E5
extern bool g012ED4E6;
#define G012ED4E6 g012ED4E6
extern int BfmeSavedClientFrame;
#define G012ED508 BfmeSavedClientFrame
struct BfmeLinearGameEngine; extern BfmeLinearGameEngine *TheGameEngine;
#define G012ED524 (*(void**)&TheGameEngine)
extern unsigned fadeQueueKey;
#define G012ED588 fadeQueueKey
class BfmeWideForwardC; extern BfmeWideForwardC *ThePartitionManager;
#define G012ED5B8 (*(void**)&ThePartitionManager)
class PartitionManager; extern PartitionManager *TheShroudManager;
#define G012ED5BC (*(void**)&TheShroudManager)
class BfmeTaintManager; extern BfmeTaintManager *TheTaintManager;
#define G012ED5C0 (*(void**)&TheTaintManager)
extern void *Rva012ED5C8;
#define G012ED5C8 Rva012ED5C8
struct BfmeListEYE; extern BfmeListEYE *g_bfmeListEYE;
#define G012ED5DC (*(void**)&g_bfmeListEYE)
extern void *G012ED5F4;
class MultiplayerSettings; extern MultiplayerSettings *TheMultiplayerSettings;
#define G012ED5FC (*(void**)&TheMultiplayerSettings)
class BfmeGenAE; extern BfmeGenAE *TheBfmeGenAE;
#define G012ED600 (*(void**)&TheBfmeGenAE)
class RecorderClass; extern RecorderClass *TheRecorder;
#define G012ED62C (*(void**)&TheRecorder)
class StatsCollector; extern StatsCollector *TheStatsCollector;
#define G012ED63C (*(void**)&TheStatsCollector)
extern void *TheAudioClientUpdate;
#define G012ED668 TheAudioClientUpdate
class PlayerList; extern PlayerList *ThePlayers;
#define G012ED748 (*(void**)&ThePlayers)
class PlayerTemplateStore; extern PlayerTemplateStore *ThePlayerTemplateStore;
#define G012ED750 (*(void**)&ThePlayerTemplateStore)
class TeamFactory; extern TeamFactory *TheTeamFactory;
#define G012ED810 (*(void**)&TheTeamFactory)
class Radar; extern Radar *TheRadar;
#define G012EF0E4 (*(void**)&TheRadar)
class Watchdog; extern Watchdog *Watchdog0040F780;
#define G012EF18C (*(void**)&Watchdog0040F780)
struct Rva0075B660State; extern Rva0075B660State *TheGameState;
#define G012EF190 (*(void**)&TheGameState)
extern void *g_global12EF1D8;
#define G012EF1D8 g_global12EF1D8
extern bool Data00EEF1DC;
#define G012EF1DC Data00EEF1DC
extern void *TheAI;
#define G012EF214 TheAI
class BfmeSidesList; extern BfmeSidesList *TheSidesList;
#define G012EF428 (*(void**)&TheSidesList)
extern void *TheTerrainLogic;
#define G012EF4CC TheTerrainLogic
class BfmeGhostAH; extern BfmeGhostAH *TheBfmeGhostAH;
#define G012EF4FC (*(void**)&TheBfmeGhostAH)
class VictorySystem; extern VictorySystem *TheVictorySystem;
#define G012EF734 (*(void**)&TheVictorySystem)
class LuaScriptEngine; extern LuaScriptEngine *TheLuaScriptEngine;
#define G012F060C (*(void**)&TheLuaScriptEngine)
class BFMEScriptEngineFlagLookup; extern BFMEScriptEngineFlagLookup *TheScriptEngine;
#define G012F076C (*(void**)&TheScriptEngine)
class VictoryConditions; extern VictoryConditions *TheVictoryConditions;
#define G012F079C (*(void**)&TheVictoryConditions)
extern void *TheBfmeGameLogic;
#define G012F0898 TheBfmeGameLogic
extern float G012F089C;
extern bool Rva012F08A0;
#define G012F08A0 Rva012F08A0
class LargeGroupAudio; extern LargeGroupAudio *TheLargeGroupAudio;
#define G012F1044 (*(void**)&TheLargeGroupAudio)
extern void *TheDisplay;
#define G012F1270 TheDisplay
class BfmeMoveHintGameClient; extern BfmeMoveHintGameClient *TheGameClient;
#define G012F1464 (*(void**)&TheGameClient)
struct InGameUI; extern InGameUI *TheInGameUI;
#define G012F148C (*(void**)&TheInGameUI)
extern void *TheTacticalView;
#define G012F1600 TheTacticalView
extern void *g_rva00592D60NotifyOwner;
#define G012F19E8 g_rva00592D60NotifyOwner
class BfmeManagerZE; extern BfmeManagerZE *TheBfmeManagerZE;
#define G012F1B40 (*(void**)&TheBfmeManagerZE)
struct Rva005A00B0Transition; extern Rva005A00B0Transition *TheTransitionHandler;
#define G012F3330 (*(void**)&TheTransitionHandler)
struct Rva002AD380ControlBar; extern Rva002AD380ControlBar *TheControlBar;
#define G012F33F8 (*(void**)&TheControlBar)
class BfmeShell; extern BfmeShell *TheShell;
#define G012F4B58 (*(void**)&TheShell)
extern void *Screen005999B0;
#define G012F4B98 Screen005999B0
struct MouseState; extern MouseState *TheMouse;
#define G012F4C5C (*(void**)&TheMouse)
class ParticleSystemManager; extern ParticleSystemManager *TheParticleSystemManager;
#define G012F64BC (*(void**)&TheParticleSystemManager)
class Rva001A8820TerrainVisual; extern Rva001A8820TerrainVisual *TheTerrainVisual;
#define G012F7014 (*(void**)&TheTerrainVisual)
class BfmeGlobal012F706C; extern BfmeGlobal012F706C *TheBfmeGlobal012F706C;
#define G012F706C (*(void**)&TheBfmeGlobal012F706C)
class GameInfo; extern GameInfo *TheGameInfo;
#define G012F708C (*(void**)&TheGameInfo)
extern void *G012F7090;
extern void *g_bfmeCurrentCB;
#define G012F7094 g_bfmeCurrentCB
class BfmeEstablishGameSpyGame; extern BfmeEstablishGameSpyGame *TheGameSpyGame;
#define G012F7198 (*(void**)&TheGameSpyGame)
extern void *g_va012F71B4;
#define G012F71B4 g_va012F71B4
extern void *TheNetwork;
#define G012F7714 TheNetwork
extern void *g_rva004CAF70_g;
#define G012F7730 g_rva004CAF70_g
extern void *AssetSubsystem0059A3D0;
#define G0134FAA0 AssetSubsystem0059A3D0
#define VS(n) virtual void slot##n()=0;
struct Virtual00394260_178 {
VS(000) VS(001) VS(002) VS(003) VS(004) VS(005) VS(006) VS(007) VS(008) VS(009) VS(00A) VS(00B) VS(00C) VS(00D) VS(00E) VS(00F) VS(010) VS(011) VS(012) VS(013) VS(014) VS(015) VS(016) VS(017) VS(018) VS(019) VS(01A) VS(01B) VS(01C) VS(01D) VS(01E) VS(01F) VS(020) VS(021) VS(022) VS(023) VS(024) VS(025) VS(026) VS(027) VS(028) VS(029) VS(02A) VS(02B) VS(02C) VS(02D) VS(02E) VS(02F) VS(030) VS(031) VS(032) VS(033) VS(034) VS(035) VS(036) VS(037) VS(038) VS(039) VS(03A) VS(03B) VS(03C) VS(03D) VS(03E) VS(03F) VS(040) VS(041) VS(042) VS(043) VS(044) VS(045) VS(046) VS(047) VS(048) VS(049) VS(04A) VS(04B) VS(04C) VS(04D) VS(04E) VS(04F) VS(050) VS(051) VS(052) VS(053) VS(054) VS(055) VS(056) VS(057) VS(058) VS(059) VS(05A) VS(05B) VS(05C) VS(05D) virtual void invoke()=0;
};
static __forceinline void V178(void *self) { ((Virtual00394260_178*)self)->invoke(); }
struct Virtual00394260_014 {
VS(000) VS(001) VS(002) VS(003) VS(004) virtual void invoke()=0;
};
static __forceinline void V014(void *self) { ((Virtual00394260_014*)self)->invoke(); }
struct Virtual00394260_020 {
VS(000) VS(001) VS(002) VS(003) VS(004) VS(005) VS(006) VS(007) virtual void invoke()=0;
};
static __forceinline void V020(void *self) { ((Virtual00394260_020*)self)->invoke(); }
struct Virtual00394260_004i {
VS(000) virtual void invoke(int)=0;
};
static __forceinline void V004i(void *self, int a0) { ((Virtual00394260_004i*)self)->invoke(a0); }
struct Virtual00394260_010 {
VS(000) VS(001) VS(002) VS(003) virtual void invoke()=0;
};
static __forceinline void V010(void *self) { ((Virtual00394260_010*)self)->invoke(); }
struct Virtual00394260_0C0p {
VS(000) VS(001) VS(002) VS(003) VS(004) VS(005) VS(006) VS(007) VS(008) VS(009) VS(00A) VS(00B) VS(00C) VS(00D) VS(00E) VS(00F) VS(010) VS(011) VS(012) VS(013) VS(014) VS(015) VS(016) VS(017) VS(018) VS(019) VS(01A) VS(01B) VS(01C) VS(01D) VS(01E) VS(01F) VS(020) VS(021) VS(022) VS(023) VS(024) VS(025) VS(026) VS(027) VS(028) VS(029) VS(02A) VS(02B) VS(02C) VS(02D) VS(02E) VS(02F) virtual void* invoke()=0;
};
static __forceinline void* V0C0p(void *self) { return ((Virtual00394260_0C0p*)self)->invoke(); }
struct Virtual00394260_000i {
virtual void invoke(int)=0;
};
static __forceinline void V000i(void *self, int a0) { ((Virtual00394260_000i*)self)->invoke(a0); }
struct Virtual00394260_008p {
VS(000) VS(001) virtual void invoke(void*)=0;
};
static __forceinline void V008p(void *self, void* a0) { ((Virtual00394260_008p*)self)->invoke(a0); }
struct Virtual00394260_010map {
VS(000) VS(001) VS(002) VS(003) virtual void invoke(AsciiString, void*, bool, bool)=0;
};
static __forceinline void V010map(void *self, const AsciiString& a0, void* a1, bool a2, bool a3) { ((Virtual00394260_010map*)self)->invoke(a0, a1, a2, a3); }
struct Virtual00394260_03Cb {
VS(000) VS(001) VS(002) VS(003) VS(004) VS(005) VS(006) VS(007) VS(008) VS(009) VS(00A) VS(00B) VS(00C) VS(00D) VS(00E) virtual bool invoke()=0;
};
static __forceinline bool V03Cb(void *self) { return ((Virtual00394260_03Cb*)self)->invoke(); }
struct Virtual00394260_024 {
VS(000) VS(001) VS(002) VS(003) VS(004) VS(005) VS(006) VS(007) VS(008) virtual void invoke()=0;
};
static __forceinline void V024(void *self) { ((Virtual00394260_024*)self)->invoke(); }
struct Virtual00394260_018p {
VS(000) VS(001) VS(002) VS(003) VS(004) VS(005) virtual void invoke(void*)=0;
};
static __forceinline void V018p(void *self, void* a0) { ((Virtual00394260_018p*)self)->invoke(a0); }
struct Virtual00394260_030 {
VS(000) VS(001) VS(002) VS(003) VS(004) VS(005) VS(006) VS(007) VS(008) VS(009) VS(00A) VS(00B) virtual void invoke()=0;
};
static __forceinline void V030(void *self) { ((Virtual00394260_030*)self)->invoke(); }
struct Virtual00394260_020p {
VS(000) VS(001) VS(002) VS(003) VS(004) VS(005) VS(006) VS(007) virtual void invoke(void*)=0;
};
static __forceinline void V020p(void *self, void* a0) { ((Virtual00394260_020p*)self)->invoke(a0); }
struct Virtual00394260_158p {
VS(000) VS(001) VS(002) VS(003) VS(004) VS(005) VS(006) VS(007) VS(008) VS(009) VS(00A) VS(00B) VS(00C) VS(00D) VS(00E) VS(00F) VS(010) VS(011) VS(012) VS(013) VS(014) VS(015) VS(016) VS(017) VS(018) VS(019) VS(01A) VS(01B) VS(01C) VS(01D) VS(01E) VS(01F) VS(020) VS(021) VS(022) VS(023) VS(024) VS(025) VS(026) VS(027) VS(028) VS(029) VS(02A) VS(02B) VS(02C) VS(02D) VS(02E) VS(02F) VS(030) VS(031) VS(032) VS(033) VS(034) VS(035) VS(036) VS(037) VS(038) VS(039) VS(03A) VS(03B) VS(03C) VS(03D) VS(03E) VS(03F) VS(040) VS(041) VS(042) VS(043) VS(044) VS(045) VS(046) VS(047) VS(048) VS(049) VS(04A) VS(04B) VS(04C) VS(04D) VS(04E) VS(04F) VS(050) VS(051) VS(052) VS(053) VS(054) VS(055) virtual void invoke(void*)=0;
};
static __forceinline void V158p(void *self, void* a0) { ((Virtual00394260_158p*)self)->invoke(a0); }
struct Virtual00394260_014i {
VS(000) VS(001) VS(002) VS(003) VS(004) virtual void invoke(int)=0;
};
static __forceinline void V014i(void *self, int a0) { ((Virtual00394260_014i*)self)->invoke(a0); }
struct Virtual00394260_014b {
VS(000) VS(001) VS(002) VS(003) VS(004) virtual void invoke(bool)=0;
};
static __forceinline void V014b(void *self, bool a0) { ((Virtual00394260_014b*)self)->invoke(a0); }
struct Virtual00394260_010p {
VS(000) VS(001) VS(002) VS(003) virtual void invoke(void*)=0;
};
static __forceinline void V010p(void *self, void* a0) { ((Virtual00394260_010p*)self)->invoke(a0); }
struct Virtual00394260_038 {
VS(000) VS(001) VS(002) VS(003) VS(004) VS(005) VS(006) VS(007) VS(008) VS(009) VS(00A) VS(00B) VS(00C) VS(00D) virtual void invoke()=0;
};
static __forceinline void V038(void *self) { ((Virtual00394260_038*)self)->invoke(); }
struct Virtual00394260_018 {
VS(000) VS(001) VS(002) VS(003) VS(004) VS(005) virtual void invoke()=0;
};
static __forceinline void V018(void *self) { ((Virtual00394260_018*)self)->invoke(); }
struct Virtual00394260_110 {
VS(000) VS(001) VS(002) VS(003) VS(004) VS(005) VS(006) VS(007) VS(008) VS(009) VS(00A) VS(00B) VS(00C) VS(00D) VS(00E) VS(00F) VS(010) VS(011) VS(012) VS(013) VS(014) VS(015) VS(016) VS(017) VS(018) VS(019) VS(01A) VS(01B) VS(01C) VS(01D) VS(01E) VS(01F) VS(020) VS(021) VS(022) VS(023) VS(024) VS(025) VS(026) VS(027) VS(028) VS(029) VS(02A) VS(02B) VS(02C) VS(02D) VS(02E) VS(02F) VS(030) VS(031) VS(032) VS(033) VS(034) VS(035) VS(036) VS(037) VS(038) VS(039) VS(03A) VS(03B) VS(03C) VS(03D) VS(03E) VS(03F) VS(040) VS(041) VS(042) VS(043) virtual void invoke()=0;
};
static __forceinline void V110(void *self) { ((Virtual00394260_110*)self)->invoke(); }
struct Virtual00394260_138 {
VS(000) VS(001) VS(002) VS(003) VS(004) VS(005) VS(006) VS(007) VS(008) VS(009) VS(00A) VS(00B) VS(00C) VS(00D) VS(00E) VS(00F) VS(010) VS(011) VS(012) VS(013) VS(014) VS(015) VS(016) VS(017) VS(018) VS(019) VS(01A) VS(01B) VS(01C) VS(01D) VS(01E) VS(01F) VS(020) VS(021) VS(022) VS(023) VS(024) VS(025) VS(026) VS(027) VS(028) VS(029) VS(02A) VS(02B) VS(02C) VS(02D) VS(02E) VS(02F) VS(030) VS(031) VS(032) VS(033) VS(034) VS(035) VS(036) VS(037) VS(038) VS(039) VS(03A) VS(03B) VS(03C) VS(03D) VS(03E) VS(03F) VS(040) VS(041) VS(042) VS(043) VS(044) VS(045) VS(046) VS(047) VS(048) VS(049) VS(04A) VS(04B) VS(04C) VS(04D) virtual void invoke()=0;
};
static __forceinline void V138(void *self) { ((Virtual00394260_138*)self)->invoke(); }
struct Virtual00394260_058 {
VS(000) VS(001) VS(002) VS(003) VS(004) VS(005) VS(006) VS(007) VS(008) VS(009) VS(00A) VS(00B) VS(00C) VS(00D) VS(00E) VS(00F) VS(010) VS(011) VS(012) VS(013) VS(014) VS(015) virtual void invoke()=0;
};
static __forceinline void V058(void *self) { ((Virtual00394260_058*)self)->invoke(); }
struct Virtual00394260_0C4look {
VS(000) VS(001) VS(002) VS(003) VS(004) VS(005) VS(006) VS(007) VS(008) VS(009) VS(00A) VS(00B) VS(00C) VS(00D) VS(00E) VS(00F) VS(010) VS(011) VS(012) VS(013) VS(014) VS(015) VS(016) VS(017) VS(018) VS(019) VS(01A) VS(01B) VS(01C) VS(01D) VS(01E) VS(01F) VS(020) VS(021) VS(022) VS(023) VS(024) VS(025) VS(026) VS(027) VS(028) VS(029) VS(02A) VS(02B) VS(02C) VS(02D) VS(02E) VS(02F) VS(030) virtual void invoke(Coord00394260*, int, int, bool)=0;
};
static __forceinline void V0C4look(void *self, Coord00394260* a0, int a1, int a2, bool a3) { ((Virtual00394260_0C4look*)self)->invoke(a0, a1, a2, a3); }
struct Virtual00394260_028 {
VS(000) VS(001) VS(002) VS(003) VS(004) VS(005) VS(006) VS(007) VS(008) VS(009) virtual void invoke()=0;
};
static __forceinline void V028(void *self) { ((Virtual00394260_028*)self)->invoke(); }
struct Virtual00394260_074 {
VS(000) VS(001) VS(002) VS(003) VS(004) VS(005) VS(006) VS(007) VS(008) VS(009) VS(00A) VS(00B) VS(00C) VS(00D) VS(00E) VS(00F) VS(010) VS(011) VS(012) VS(013) VS(014) VS(015) VS(016) VS(017) VS(018) VS(019) VS(01A) VS(01B) VS(01C) virtual void invoke()=0;
};
static __forceinline void V074(void *self) { ((Virtual00394260_074*)self)->invoke(); }
struct Virtual00394260_024i {
VS(000) VS(001) VS(002) VS(003) VS(004) VS(005) VS(006) VS(007) VS(008) virtual void invoke(int)=0;
};
static __forceinline void V024i(void *self, int a0) { ((Virtual00394260_024i*)self)->invoke(a0); }
struct Virtual00394260_010i {
VS(000) VS(001) VS(002) VS(003) virtual void invoke(int)=0;
};
static __forceinline void V010i(void *self, int a0) { ((Virtual00394260_010i*)self)->invoke(a0); }
struct Virtual00394260_140b {
VS(000) VS(001) VS(002) VS(003) VS(004) VS(005) VS(006) VS(007) VS(008) VS(009) VS(00A) VS(00B) VS(00C) VS(00D) VS(00E) VS(00F) VS(010) VS(011) VS(012) VS(013) VS(014) VS(015) VS(016) VS(017) VS(018) VS(019) VS(01A) VS(01B) VS(01C) VS(01D) VS(01E) VS(01F) VS(020) VS(021) VS(022) VS(023) VS(024) VS(025) VS(026) VS(027) VS(028) VS(029) VS(02A) VS(02B) VS(02C) VS(02D) VS(02E) VS(02F) VS(030) VS(031) VS(032) VS(033) VS(034) VS(035) VS(036) VS(037) VS(038) VS(039) VS(03A) VS(03B) VS(03C) VS(03D) VS(03E) VS(03F) VS(040) VS(041) VS(042) VS(043) VS(044) VS(045) VS(046) VS(047) VS(048) VS(049) VS(04A) VS(04B) VS(04C) VS(04D) VS(04E) VS(04F) virtual void invoke(bool)=0;
};
static __forceinline void V140b(void *self, bool a0) { ((Virtual00394260_140b*)self)->invoke(a0); }
struct Virtual00394260_07Cp {
VS(000) VS(001) VS(002) VS(003) VS(004) VS(005) VS(006) VS(007) VS(008) VS(009) VS(00A) VS(00B) VS(00C) VS(00D) VS(00E) VS(00F) VS(010) VS(011) VS(012) VS(013) VS(014) VS(015) VS(016) VS(017) VS(018) VS(019) VS(01A) VS(01B) VS(01C) VS(01D) VS(01E) virtual void* invoke()=0;
};
static __forceinline void* V07Cp(void *self) { return ((Virtual00394260_07Cp*)self)->invoke(); }
struct Virtual00394260_040 {
VS(000) VS(001) VS(002) VS(003) VS(004) VS(005) VS(006) VS(007) VS(008) VS(009) VS(00A) VS(00B) VS(00C) VS(00D) VS(00E) VS(00F) virtual void invoke()=0;
};
static __forceinline void V040(void *self) { ((Virtual00394260_040*)self)->invoke(); }
struct Virtual00394260_1C8b {
VS(000) VS(001) VS(002) VS(003) VS(004) VS(005) VS(006) VS(007) VS(008) VS(009) VS(00A) VS(00B) VS(00C) VS(00D) VS(00E) VS(00F) VS(010) VS(011) VS(012) VS(013) VS(014) VS(015) VS(016) VS(017) VS(018) VS(019) VS(01A) VS(01B) VS(01C) VS(01D) VS(01E) VS(01F) VS(020) VS(021) VS(022) VS(023) VS(024) VS(025) VS(026) VS(027) VS(028) VS(029) VS(02A) VS(02B) VS(02C) VS(02D) VS(02E) VS(02F) VS(030) VS(031) VS(032) VS(033) VS(034) VS(035) VS(036) VS(037) VS(038) VS(039) VS(03A) VS(03B) VS(03C) VS(03D) VS(03E) VS(03F) VS(040) VS(041) VS(042) VS(043) VS(044) VS(045) VS(046) VS(047) VS(048) VS(049) VS(04A) VS(04B) VS(04C) VS(04D) VS(04E) VS(04F) VS(050) VS(051) VS(052) VS(053) VS(054) VS(055) VS(056) VS(057) VS(058) VS(059) VS(05A) VS(05B) VS(05C) VS(05D) VS(05E) VS(05F) VS(060) VS(061) VS(062) VS(063) VS(064) VS(065) VS(066) VS(067) VS(068) VS(069) VS(06A) VS(06B) VS(06C) VS(06D) VS(06E) VS(06F) VS(070) VS(071) virtual bool invoke()=0;
};
static __forceinline bool V1C8b(void *self) { return ((Virtual00394260_1C8b*)self)->invoke(); }
struct Virtual00394260_1CC {
VS(000) VS(001) VS(002) VS(003) VS(004) VS(005) VS(006) VS(007) VS(008) VS(009) VS(00A) VS(00B) VS(00C) VS(00D) VS(00E) VS(00F) VS(010) VS(011) VS(012) VS(013) VS(014) VS(015) VS(016) VS(017) VS(018) VS(019) VS(01A) VS(01B) VS(01C) VS(01D) VS(01E) VS(01F) VS(020) VS(021) VS(022) VS(023) VS(024) VS(025) VS(026) VS(027) VS(028) VS(029) VS(02A) VS(02B) VS(02C) VS(02D) VS(02E) VS(02F) VS(030) VS(031) VS(032) VS(033) VS(034) VS(035) VS(036) VS(037) VS(038) VS(039) VS(03A) VS(03B) VS(03C) VS(03D) VS(03E) VS(03F) VS(040) VS(041) VS(042) VS(043) VS(044) VS(045) VS(046) VS(047) VS(048) VS(049) VS(04A) VS(04B) VS(04C) VS(04D) VS(04E) VS(04F) VS(050) VS(051) VS(052) VS(053) VS(054) VS(055) VS(056) VS(057) VS(058) VS(059) VS(05A) VS(05B) VS(05C) VS(05D) VS(05E) VS(05F) VS(060) VS(061) VS(062) VS(063) VS(064) VS(065) VS(066) VS(067) VS(068) VS(069) VS(06A) VS(06B) VS(06C) VS(06D) VS(06E) VS(06F) VS(070) VS(071) VS(072) virtual void invoke(int, int, int, bool)=0;
};
static __forceinline void V1CC(void *self, int a0, int a1, int a2, bool a3) { ((Virtual00394260_1CC*)self)->invoke(a0, a1, a2, a3); }
struct Virtual00394260_0F0b {
VS(000) VS(001) VS(002) VS(003) VS(004) VS(005) VS(006) VS(007) VS(008) VS(009) VS(00A) VS(00B) VS(00C) VS(00D) VS(00E) VS(00F) VS(010) VS(011) VS(012) VS(013) VS(014) VS(015) VS(016) VS(017) VS(018) VS(019) VS(01A) VS(01B) VS(01C) VS(01D) VS(01E) VS(01F) VS(020) VS(021) VS(022) VS(023) VS(024) VS(025) VS(026) VS(027) VS(028) VS(029) VS(02A) VS(02B) VS(02C) VS(02D) VS(02E) VS(02F) VS(030) VS(031) VS(032) VS(033) VS(034) VS(035) VS(036) VS(037) VS(038) VS(039) VS(03A) VS(03B) virtual bool invoke()=0;
};
static __forceinline bool V0F0b(void *self) { return ((Virtual00394260_0F0b*)self)->invoke(); }
struct Virtual00394260_014bret {
VS(000) VS(001) VS(002) VS(003) VS(004) virtual bool invoke()=0;
};
static __forceinline bool V014bret(void *self) { return ((Virtual00394260_014bret*)self)->invoke(); }
struct Virtual00394260_0D8 {
VS(000) VS(001) VS(002) VS(003) VS(004) VS(005) VS(006) VS(007) VS(008) VS(009) VS(00A) VS(00B) VS(00C) VS(00D) VS(00E) VS(00F) VS(010) VS(011) VS(012) VS(013) VS(014) VS(015) VS(016) VS(017) VS(018) VS(019) VS(01A) VS(01B) VS(01C) VS(01D) VS(01E) VS(01F) VS(020) VS(021) VS(022) VS(023) VS(024) VS(025) VS(026) VS(027) VS(028) VS(029) VS(02A) VS(02B) VS(02C) VS(02D) VS(02E) VS(02F) VS(030) VS(031) VS(032) VS(033) VS(034) VS(035) virtual void invoke(int, bool)=0;
};
static __forceinline void V0D8(void *self, int a0, bool a1) { ((Virtual00394260_0D8*)self)->invoke(a0, a1); }
struct Virtual00394260_028p {
VS(000) VS(001) VS(002) VS(003) VS(004) VS(005) VS(006) VS(007) VS(008) VS(009) virtual void* invoke()=0;
};
static __forceinline void* V028p(void *self) { return ((Virtual00394260_028p*)self)->invoke(); }
#undef VS
extern void j_0003713C();
static __forceinline void D0003713C(void *self) {
union { void (*entry)(); void (Receiver00394260::*member)(); } call;
call.entry=j_0003713C; (((Receiver00394260*)self)->*call.member)();
}
extern void j_00001307();
static __forceinline void D00001307(void *self) {
union { void (*entry)(); void (Receiver00394260::*member)(); } call;
call.entry=j_00001307; (((Receiver00394260*)self)->*call.member)();
}
extern void j_0003e6da();
static __forceinline AsciiString* D0003E6DA(void *self, const AsciiString& a0) {
union { void (*entry)(); AsciiString* (Receiver00394260::*member)(const AsciiString&); } call;
call.entry=j_0003e6da; return (((Receiver00394260*)self)->*call.member)(a0);
}
extern void j_00030495();
static __forceinline bool D00030495(void *self) {
union { void (*entry)(); bool (Receiver00394260::*member)(); } call;
call.entry=j_00030495; return (((Receiver00394260*)self)->*call.member)();
}
extern void j_0003f7b5();
static __forceinline void D0003F7B5(void *self) {
union { void (*entry)(); void (Receiver00394260::*member)(); } call;
call.entry=j_0003f7b5; (((Receiver00394260*)self)->*call.member)();
}
extern void j_00030071();
static __forceinline void D00030071(void *self) {
union { void (*entry)(); void (Receiver00394260::*member)(); } call;
call.entry=j_00030071; (((Receiver00394260*)self)->*call.member)();
}
extern void j_0003d578();
static __forceinline void D0003D578(void *self, bool a0) {
union { void (*entry)(); void (Receiver00394260::*member)(bool); } call;
call.entry=j_0003d578; (((Receiver00394260*)self)->*call.member)(a0);
}
extern void j_0002518a();
static __forceinline void D0002518A(void *self) {
union { void (*entry)(); void (Receiver00394260::*member)(); } call;
call.entry=j_0002518a; (((Receiver00394260*)self)->*call.member)();
}
extern void j_0002a0db();
static __forceinline void D0002A0DB(void *self, const AsciiString& a0) {
union { void (*entry)(); void (Receiver00394260::*member)(AsciiString); } call;
call.entry=j_0002a0db; (((Receiver00394260*)self)->*call.member)(a0);
}
extern void j_00023f9c();
static __forceinline bool D00023F9C(void *self, const AsciiString& a0) {
union { void (*entry)(); bool (Receiver00394260::*member)(const AsciiString&); } call;
call.entry=j_00023f9c; return (((Receiver00394260*)self)->*call.member)(a0);
}
extern void j_00024893();
static __forceinline void D00024893(void *self, bool a0) {
union { void (*entry)(); void (Receiver00394260::*member)(bool); } call;
call.entry=j_00024893; (((Receiver00394260*)self)->*call.member)(a0);
}
extern void j_00043eeb();
static __forceinline int D00043EEB(void *self) {
union { void (*entry)(); int (Receiver00394260::*member)(); } call;
call.entry=j_00043eeb; return (((Receiver00394260*)self)->*call.member)();
}
extern void j_0001ec18();
static __forceinline void* D0001EC18(void *self, int a0) {
union { void (*entry)(); void* (Receiver00394260::*member)(int); } call;
call.entry=j_0001ec18; return (((Receiver00394260*)self)->*call.member)(a0);
}
extern void j_000324ca();
static __forceinline void D000324CA(void *self) {
union { void (*entry)(); void (Receiver00394260::*member)(); } call;
call.entry=j_000324ca; (((Receiver00394260*)self)->*call.member)();
}
extern void j_000422df();
static __forceinline bool D000422DF(void *self) {
union { void (*entry)(); bool (Receiver00394260::*member)(); } call;
call.entry=j_000422df; return (((Receiver00394260*)self)->*call.member)();
}
extern void j_00018d3b();
static __forceinline void* D00018D3B(void *self, bool a0) {
union { void (*entry)(); void* (Receiver00394260::*member)(bool); } call;
call.entry=j_00018d3b; return (((Receiver00394260*)self)->*call.member)(a0);
}
extern void j_00034644();
static __forceinline void D00034644(void *self, const AsciiString& a0) {
union { void (*entry)(); void (Receiver00394260::*member)(AsciiString); } call;
call.entry=j_00034644; (((Receiver00394260*)self)->*call.member)(a0);
}
extern void j_00022697();
static __forceinline void D00022697(void *self, const AsciiString* a0) {
union { void (*entry)(); void (Receiver00394260::*member)(const AsciiString*); } call;
call.entry=j_00022697; (((Receiver00394260*)self)->*call.member)(a0);
}
extern void j_0004b344();
static __forceinline void D0004B344(void *self) {
union { void (*entry)(); void (Receiver00394260::*member)(); } call;
call.entry=j_0004b344; (((Receiver00394260*)self)->*call.member)();
}
extern void j_0004aab1();
static __forceinline bool D0004AAB1(void *self, const AsciiString& a0) {
union { void (*entry)(); bool (Receiver00394260::*member)(AsciiString); } call;
call.entry=j_0004aab1; return (((Receiver00394260*)self)->*call.member)(a0);
}
extern void j_00049800();
static __forceinline void D00049800(void *self, int a0, int a1) {
union { void (*entry)(); void (Receiver00394260::*member)(int, int); } call;
call.entry=j_00049800; (((Receiver00394260*)self)->*call.member)(a0, a1);
}
extern void j_0001372d();
static __forceinline void D0001372D(void *self) {
union { void (*entry)(); void (Receiver00394260::*member)(); } call;
call.entry=j_0001372d; (((Receiver00394260*)self)->*call.member)();
}
extern void j_0000512d();
static __forceinline void D0000512D(void *self) {
union { void (*entry)(); void (Receiver00394260::*member)(); } call;
call.entry=j_0000512d; (((Receiver00394260*)self)->*call.member)();
}
extern void j_00003d5f();
static __forceinline void D00003D5F(void *self) {
union { void (*entry)(); void (Receiver00394260::*member)(); } call;
call.entry=j_00003d5f; (((Receiver00394260*)self)->*call.member)();
}
extern void j_000015f0();
static __forceinline void D000015F0(void *self, const AsciiString& a0) {
union { void (*entry)(); void (Receiver00394260::*member)(AsciiString); } call;
call.entry=j_000015f0; (((Receiver00394260*)self)->*call.member)(a0);
}
extern void j_0000fdf8();
static __forceinline void D0000FDF8(void *self, int a0) {
union { void (*entry)(); void (Receiver00394260::*member)(int); } call;
call.entry=j_0000fdf8; (((Receiver00394260*)self)->*call.member)(a0);
}
extern void j_00028155();
static __forceinline void D00028155(void *self) {
union { void (*entry)(); void (Receiver00394260::*member)(); } call;
call.entry=j_00028155; (((Receiver00394260*)self)->*call.member)();
}
extern void j_000298e3();
typedef void (Receiver00394260::*Member000298E3)(Encoded00394260, int);
static __forceinline Member000298E3 member000298E3() { union { void(*entry)();Member000298E3 member; } c; c.entry=j_000298e3;return c.member; }
#define D000298E3(self ,a0, a1) ((((Receiver00394260*)(self))->*member000298E3())(a0, a1))
extern void j_00046254();
static __forceinline void D00046254(void *self) {
union { void (*entry)(); void (Receiver00394260::*member)(); } call;
call.entry=j_00046254; (((Receiver00394260*)self)->*call.member)();
}
extern void j_00024b36();
static __forceinline void D00024B36(void *self) {
union { void (*entry)(); void (Receiver00394260::*member)(); } call;
call.entry=j_00024b36; (((Receiver00394260*)self)->*call.member)();
}
extern void j_00035c56();
static __forceinline void D00035C56(void *self) {
union { void (*entry)(); void (Receiver00394260::*member)(); } call;
call.entry=j_00035c56; (((Receiver00394260*)self)->*call.member)();
}
extern void j_0004ae4e();
static __forceinline void D0004AE4E(void *self) {
union { void (*entry)(); void (Receiver00394260::*member)(); } call;
call.entry=j_0004ae4e; (((Receiver00394260*)self)->*call.member)();
}
extern void j_0002835d();
static __forceinline void D0002835D(void *self, bool a0) {
union { void (*entry)(); void (Receiver00394260::*member)(bool); } call;
call.entry=j_0002835d; (((Receiver00394260*)self)->*call.member)(a0);
}
extern void j_0003add7();
static __forceinline int D0003ADD7(void *self, const char* a0) {
union { void (*entry)(); int (Receiver00394260::*member)(const char*); } call;
call.entry=j_0003add7; return (((Receiver00394260*)self)->*call.member)(a0);
}
extern void j_0002f586();
static __forceinline void* D0002F586(void *self, int a0) {
union { void (*entry)(); void* (Receiver00394260::*member)(int); } call;
call.entry=j_0002f586; return (((Receiver00394260*)self)->*call.member)(a0);
}
extern void j_00040593();
static __forceinline bool D00040593(void *self) {
union { void (*entry)(); bool (Receiver00394260::*member)(); } call;
call.entry=j_00040593; return (((Receiver00394260*)self)->*call.member)();
}
extern void j_00012814();
static __forceinline void* D00012814(void *self) {
union { void (*entry)(); void* (Receiver00394260::*member)(); } call;
call.entry=j_00012814; return (((Receiver00394260*)self)->*call.member)();
}
extern void j_0001325a();
static __forceinline Coord00394260* D0001325A(void *self) {
union { void (*entry)(); Coord00394260* (Receiver00394260::*member)(); } call;
call.entry=j_0001325a; return (((Receiver00394260*)self)->*call.member)();
}
extern void j_000364ad();
static __forceinline void D000364AD(void *self, void* a0, Coord00394260* a1, Matrix00394260* a2, float a3) {
union { void (*entry)(); void (Receiver00394260::*member)(void*, Coord00394260*, Matrix00394260*, float); } call;
call.entry=j_000364ad; (((Receiver00394260*)self)->*call.member)(a0, a1, a2, a3);
}
extern void j_000050c9();
static __forceinline void D000050C9(void *self, void* a0, Coord00394260* a1, Matrix00394260* a2, float a3) {
union { void (*entry)(); void (Receiver00394260::*member)(void*, Coord00394260*, Matrix00394260*, float); } call;
call.entry=j_000050c9; (((Receiver00394260*)self)->*call.member)(a0, a1, a2, a3);
}
extern void j_0001fd39();
static __forceinline void D0001FD39(void *self, ObjectMapVector00394260* a0, int* a1, bool a2, bool a3) {
union { void (*entry)(); void (Receiver00394260::*member)(ObjectMapVector00394260*, int*, bool, bool); } call;
call.entry=j_0001fd39; (((Receiver00394260*)self)->*call.member)(a0, a1, a2, a3);
}
extern void j_00028560();
static __forceinline void* D00028560(void *self, const AsciiString& a0) {
union { void (*entry)(); void* (Receiver00394260::*member)(const AsciiString&); } call;
call.entry=j_00028560; return (((Receiver00394260*)self)->*call.member)(a0);
}
extern void j_00017a12();
static __forceinline void D00017A12(void *self, AssetList00394260* a0, bool* a1) {
union { void (*entry)(); void (Receiver00394260::*member)(AssetList00394260*, bool*); } call;
call.entry=j_00017a12; (((Receiver00394260*)self)->*call.member)(a0, a1);
}
extern void j_0004494a();
static __forceinline void* D0004494A(void *self, void* a0, void* a1, const Flags00394260& a2, unsigned a3) {
union { void (*entry)(); void* (Receiver00394260::*member)(void*, void*, const Flags00394260&, unsigned); } call;
call.entry=j_0004494a; return (((Receiver00394260*)self)->*call.member)(a0, a1, a2, a3);
}
extern void j_00005a7e();
static __forceinline void D00005A7E(void *self, unsigned a0) {
union { void (*entry)(); void (Receiver00394260::*member)(unsigned); } call;
call.entry=j_00005a7e; (((Receiver00394260*)self)->*call.member)(a0);
}
extern void j_000017a8();
static __forceinline void D000017A8(void *self, void* a0) {
union { void (*entry)(); void (Receiver00394260::*member)(void*); } call;
call.entry=j_000017a8; (((Receiver00394260*)self)->*call.member)(a0);
}
extern void j_0002cd8b();
static __forceinline void* D0002CD8B(void *self, int a0) {
union { void (*entry)(); void* (Receiver00394260::*member)(int); } call;
call.entry=j_0002cd8b; return (((Receiver00394260*)self)->*call.member)(a0);
}
extern void j_00037bd2();
static __forceinline void* D00037BD2(void *self, int a0) {
union { void (*entry)(); void* (Receiver00394260::*member)(int); } call;
call.entry=j_00037bd2; return (((Receiver00394260*)self)->*call.member)(a0);
}
extern void j_00002914();
static __forceinline void D00002914(void *self) {
union { void (*entry)(); void (Receiver00394260::*member)(); } call;
call.entry=j_00002914; (((Receiver00394260*)self)->*call.member)();
}
extern void j_00038497();
static __forceinline void D00038497(void *self, bool a0) {
union { void (*entry)(); void (Receiver00394260::*member)(bool); } call;
call.entry=j_00038497; (((Receiver00394260*)self)->*call.member)(a0);
}
extern void j_00002a22();
static __forceinline void D00002A22(void *self) {
union { void (*entry)(); void (Receiver00394260::*member)(); } call;
call.entry=j_00002a22; (((Receiver00394260*)self)->*call.member)();
}
enum NameKeyType { NAMEKEY_INVALID=0 };
class NameKeyGenerator { public: AsciiString keyToName(NameKeyType); };
#define D0003EC7A(self,key) (((NameKeyGenerator*)(self))->keyToName((NameKeyType)(key)))
extern void j_00009304();
static __forceinline int D00009304(void *self) {
union { void (*entry)(); int (Receiver00394260::*member)(); } call;
call.entry=j_00009304; return (((Receiver00394260*)self)->*call.member)();
}
extern void j_00033127();
static __forceinline void D00033127(void *self, GameInfo* a0, int* a1) {
union { void (*entry)(); void (Receiver00394260::*member)(GameInfo*, int*); } call;
call.entry=j_00033127; (((Receiver00394260*)self)->*call.member)(a0, a1);
}
extern void j_000279cb();
static __forceinline bool D000279CB(void *self) {
union { void (*entry)(); bool (Receiver00394260::*member)(); } call;
call.entry=j_000279cb; return (((Receiver00394260*)self)->*call.member)();
}
extern void j_000380fa();
static __forceinline bool D000380FA(void *self, float a0, bool a1) {
union { void (*entry)(); bool (Receiver00394260::*member)(float, bool); } call;
call.entry=j_000380fa; return (((Receiver00394260*)self)->*call.member)(a0, a1);
}
extern void j_000259cd();
static __forceinline void D000259CD(void *self, int a0) {
union { void (*entry)(); void (Receiver00394260::*member)(int); } call;
call.entry=j_000259cd; (((Receiver00394260*)self)->*call.member)(a0);
}
extern void j_0004aabb();
static __forceinline void D0004AABB(void *self, void* a0, void* a1) {
union { void (*entry)(); void (Receiver00394260::*member)(void*, void*); } call;
call.entry=j_0004aabb; (((Receiver00394260*)self)->*call.member)(a0, a1);
}
extern void j_00008deb();
static __forceinline void D00008DEB(void *self) {
union { void (*entry)(); void (Receiver00394260::*member)(); } call;
call.entry=j_00008deb; (((Receiver00394260*)self)->*call.member)();
}
extern void j_000339a6();
typedef void (Receiver00394260::*Member000339A6)(AsciiString, bool);
static __forceinline Member000339A6 member000339A6() { union { void(*entry)();Member000339A6 member; } c; c.entry=j_000339a6;return c.member; }
#define D000339A6(self ,a0, a1) ((((Receiver00394260*)(self))->*member000339A6())(a0, a1))
extern void j_0004a336();
static __forceinline void* D0004A336(void *self) {
union { void (*entry)(); void* (Receiver00394260::*member)(); } call;
call.entry=j_0004a336; return (((Receiver00394260*)self)->*call.member)();
}
extern void j_0003d406();
static __forceinline void D0003D406(void *self) {
union { void (*entry)(); void (Receiver00394260::*member)(); } call;
call.entry=j_0003d406; (((Receiver00394260*)self)->*call.member)();
}
extern void j_00019f38();
static __forceinline void D00019F38(void *self) {
union { void (*entry)(); void (Receiver00394260::*member)(); } call;
call.entry=j_00019f38; (((Receiver00394260*)self)->*call.member)();
}
extern void j_000466e1();
static __forceinline void D000466E1(void *self, void* a0) {
union { void (*entry)(); void (Receiver00394260::*member)(void*); } call;
call.entry=j_000466e1; (((Receiver00394260*)self)->*call.member)(a0);
}
extern void j_00019b64();
static __forceinline void D00019B64(void *self, void* a0) {
union { void (*entry)(); void (Receiver00394260::*member)(void*); } call;
call.entry=j_00019b64; (((Receiver00394260*)self)->*call.member)(a0);
}
extern void j_00044f30();
static __forceinline void* D00044F30(void *self, int a0) {
union { void (*entry)(); void* (Receiver00394260::*member)(int); } call;
call.entry=j_00044f30; return (((Receiver00394260*)self)->*call.member)(a0);
}
extern void j_00014b14();
static __forceinline void D00014B14(void *self) {
union { void (*entry)(); void (Receiver00394260::*member)(); } call;
call.entry=j_00014b14; (((Receiver00394260*)self)->*call.member)();
}
extern void j_0004a7a5();
static __forceinline bool D0004A7A5(void *self) {
union { void (*entry)(); bool (Receiver00394260::*member)(); } call;
call.entry=j_0004a7a5; return (((Receiver00394260*)self)->*call.member)();
}
extern void j_000179bd();
static __forceinline bool D000179BD(void *self) {
union { void (*entry)(); bool (Receiver00394260::*member)(); } call;
call.entry=j_000179bd; return (((Receiver00394260*)self)->*call.member)();
}
extern void j_00031c05();
static __forceinline void D00031C05(void *self, void* a0) {
union { void (*entry)(); void (Receiver00394260::*member)(void*); } call;
call.entry=j_00031c05; (((Receiver00394260*)self)->*call.member)(a0);
}
extern void j_00032b14();
static __forceinline void D00032B14(void *self) {
union { void (*entry)(); void (Receiver00394260::*member)(); } call;
call.entry=j_00032b14; (((Receiver00394260*)self)->*call.member)();
}
extern void j_00045c28();
typedef void (Receiver00394260::*Member00045C28)(AsciiString, bool);
static __forceinline Member00045C28 member00045C28() { union { void(*entry)();Member00045C28 member; } c; c.entry=j_00045c28;return c.member; }
#define D00045C28(self ,a0, a1) ((((Receiver00394260*)(self))->*member00045C28())(a0, a1))
extern void j_000323e9();
static __forceinline void D000323E9(void *self) {
union { void (*entry)(); void (Receiver00394260::*member)(); } call;
call.entry=j_000323e9; (((Receiver00394260*)self)->*call.member)();
}
extern void j_00041ff1();
static __forceinline bool D00041FF1(void *self) {
union { void (*entry)(); bool (Receiver00394260::*member)(); } call;
call.entry=j_00041ff1; return (((Receiver00394260*)self)->*call.member)();
}
extern void j_00002e64();
static __forceinline void D00002E64(void *self) {
union { void (*entry)(); void (Receiver00394260::*member)(); } call;
call.entry=j_00002e64; (((Receiver00394260*)self)->*call.member)();
}
extern void j_0000324c();
static __forceinline void D0000324C(void *self) {
union { void (*entry)(); void (Receiver00394260::*member)(); } call;
call.entry=j_0000324c; (((Receiver00394260*)self)->*call.member)();
}
extern void j_00003486();
static __forceinline void D00003486(void *self) {
union { void (*entry)(); void (Receiver00394260::*member)(); } call;
call.entry=j_00003486; (((Receiver00394260*)self)->*call.member)();
}
extern void j_00021bc5();
static __forceinline bool D00021BC5(void *self, int a0, int a1) {
union { void (*entry)(); bool (Receiver00394260::*member)(int, int); } call;
call.entry=j_00021bc5; return (((Receiver00394260*)self)->*call.member)(a0, a1);
}

extern void Rva009EBBE0(int); extern void Rva009EBC00(int);
extern void Rva009EBA80(int); extern void Rva009EBAC0(int);
extern void Rva0090F050(); extern void setFPMode();
extern int Rva00389840(int,int);
extern int bfmeForward_009EBB60(); extern int bfmeForward_009EBB40();
extern void populateRandomStartPosition(GameInfo*);
extern void d_00390a50();
inline void randomSide00394260(GameInfo *g) { ((void(__cdecl*)(GameInfo*))d_00390a50)(g); }
extern void placeNetworkBuildingsForPlayer(int,const class GameSlot*,class Player*,const class PlayerTemplate*);
inline void placeNetwork00394260(int i,void*s,void*p,void*t) { placeNetworkBuildingsForPlayer(i,(GameSlot*)s,(Player*)p,(PlayerTemplate*)t); }
extern void preloadSpellTextures0059A3D0();
class Waypoint; extern Waypoint *Rva00388820_FindWaypointByName(AsciiString);
extern void HideControlBar(bool); extern void ShowControlBar(bool);
class Object;
extern int findAndSelectCommandCenter(Object*,void*);
#define callback0038AE10 findAndSelectCommandCenter
class PlayerIterateObjectsShim { public: void iterateObjects(void(__cdecl*)(Object*,void*),void*) const; };
inline void D0002F1CB(void *p,int(__cdecl*f)(Object*,void*),void *ctx) {
 ((PlayerIterateObjectsShim*)p)->iterateObjects((void(__cdecl*)(Object*,void*))f,ctx);
}
class Gen_008f7390 { public: void m(); };
static __forceinline void initShroud00394260(void *self, Region00394260* a0, float a1) {
union { void (Gen_008f7390::*entry)(); void (Receiver00394260::*member)(Region00394260*, float); } call;
call.entry=&Gen_008f7390::m; (((Receiver00394260*)self)->*call.member)(a0, a1);
}
class Gen_008f7420 { public: void m(); };
static __forceinline void notifyShroud00394260(void *self) {
union { void (Gen_008f7420::*entry)(); void (Receiver00394260::*member)(); } call;
call.entry=&Gen_008f7420::m; (((Receiver00394260*)self)->*call.member)();
}
class Gen_00880e20 { public: void m(); };
static __forceinline void initTaint00394260(void *self, Region00394260* a0, float a1) {
union { void (Gen_00880e20::*entry)(); void (Receiver00394260::*member)(Region00394260*, float); } call;
call.entry=&Gen_00880e20::m; (((Receiver00394260*)self)->*call.member)(a0, a1);
}
class Gen_00880e30 { public: void m(); };
static __forceinline void resetTaint00394260(void *self) {
union { void (Gen_00880e30::*entry)(); void (Receiver00394260::*member)(); } call;
call.entry=&Gen_00880e30::m; (((Receiver00394260*)self)->*call.member)();
}
class Gen_009f2640 { public: void m(); };
static __forceinline void initPartition00394260(void *self, Region00394260* a0) {
union { void (Gen_009f2640::*entry)(); void (Receiver00394260::*member)(Region00394260*); } call;
call.entry=&Gen_009f2640::m; (((Receiver00394260*)self)->*call.member)(a0);
}
class Gen_008f73e0 { public: void m(); };
static __forceinline void revealPermanently00394260(void *self, int a0) {
union { void (Gen_008f73e0::*entry)(); void (Receiver00394260::*member)(int); } call;
call.entry=&Gen_008f73e0::m; (((Receiver00394260*)self)->*call.member)(a0);
}

class PartitionManager { public: void revealMapForPlayer(int); };
inline void reveal00394260(void *p,int i) { ((PartitionManager*)p)->revealMapForPlayer(i); }
struct Preferences00394260 { char data[0x24]; Preferences00394260() { D0003713C(this); } ~Preferences00394260() { D00001307(this); } };
struct MenuGuard00394260 {
 MenuGuard00394260() { void *menu=GetSystemMenu((HWND)G012ED238,FALSE); EnableMenuItem(menu,SC_CLOSE,MF_GRAYED); }
 ~MenuGuard00394260() { void *menu=GetSystemMenu((HWND)G012ED238,FALSE); EnableMenuItem(menu,SC_CLOSE,MF_ENABLED); }
};
struct Stream00394260 { char bytes[0x10]; Stream00394260() {D0004B344(this);} ~Stream00394260() {D0000512D(this);} };
struct Context00394260 { char bytes[0x10]; Context00394260(int a,int b) {D00049800(this,a,b);} ~Context00394260() {D0001372D(this);} };
struct Stats00394260 { char bytes[0x68]; Stats00394260() {D0003D406(this);} };
static __forceinline void pump00394260() { V014(G0134FAA0); Rva0090F050(); }
static __forceinline void progress00394260(void *self,int n) { if(F<void*,0x118>(self)) V004i(F<void*,0x118>(self),n); }
static __forceinline int colorCount00394260(void *p) { int &n=F<int,0x3c>(p);if(!n)n=F<int,0x34>(p);return n; }
static __declspec(noinline) void checkForDuplicateColors(GameInfo *game) {
 if(!game) return;
 for(int i=7;i>=0;--i) {
  void *slot=D0001EC18(game,i);
  if(!slot || !D00040593(slot)) continue;
  int color=F<int,0xc>(slot);
  if(color<0 || color>=colorCount00394260(G012ED5FC)) continue;
  F<int,0xc>(slot)=-1;
  if(!D00021BC5(game,color,-1)) F<int,0xc>(slot)=color;
 }
}
struct HashNode00394260 { HashNode00394260 *next; unsigned id; void *object; };
template<int Offset> static __forceinline void ensureTree00394260(void *self,unsigned id,const char *name) {
 HashNode00394260 **first=F<HashNode00394260**,0xb4>(self);
 HashNode00394260 **last=F<HashNode00394260**,0xb8>(self);
 HashNode00394260 *p=first[id/(unsigned)1 % (unsigned)(last-first)];
 while(p && p->id!=id) p=p->next;
 F<void*,Offset>(self)=p?p->object:0;
 if(!F<void*,Offset>(self)) {
  void *type=D00028560(G012EF1D8,AsciiString(name));
  if(type) {
   if(!F<bool,0x11fc>(G012ED5C8)) {
    bool flag=false; AssetList00394260 assets;
    D00017A12(type,&assets,&flag); Rva009EBAC0((int)&assets);
   }
   F<void*,Offset>(self)=D0004494A(G012EF1D8,type,F<void*,0x230>(F<void*,0x14>(G012ED748)),Flags00394260(),id);
   if(F<void*,Offset>(self)) D00005A7E(V028p(F<void*,Offset>(self)),id);
  }
 }
}
inline int templateCount00394260() { return (F<char*,0xc>(G012ED750)-F<char*,8>(G012ED750))/0x124; }
// Native wide return: one pointer, nontrivial cleanup, hidden result pointer.
extern void b_008881d0();
struct Wide00394260 {
 void *p;
 ~Wide00394260() { union { void(*entry)();void(Receiver00394260::*member)(); } c; c.entry=b_008881d0; (((Receiver00394260*)this)->*c.member)(); }
 const unsigned short *str() const { return p?(const unsigned short*)((char*)p+8):(const unsigned short*)L""; }
};
extern void j_0002c7b4(); extern void j_00025c98();
typedef Wide00394260(Receiver00394260::*WideMember00394260)();
static __forceinline WideMember00394260 wideMember00394260() {
 union {void(*entry)();WideMember00394260 member;}c;c.entry=j_0002c7b4;return c.member;
}
#define D0002C7B4(self) ((((Receiver00394260*)(self))->*wideMember00394260())())
#define D00025C98(s) (((_STL::string(__cdecl*)(const unsigned short*))j_00025c98)(s))
// Witnessed 12-byte reference node, same vtable/layout as Bfme5NodeMakers.cpp.
extern void *g_bfme5RefVtable;
struct Bfme5RefNode { void *m_bfmeVptr; int m_bfmeRefCount; int m_bfmePad; };
class LoadGameFadeHolder {
public:
 Bfme5RefNode *p;
 __forceinline LoadGameFadeHolder() throw() {
  Bfme5RefNode *q=(Bfme5RefNode*)operator new(12);
  if(q) { q->m_bfmeRefCount=0; q->m_bfmeVptr=&g_bfme5RefVtable; }
  p=q;
  if(p) ++p->m_bfmeRefCount;
 }
 ~LoadGameFadeHolder() {}
};
extern bool postTimedOp(LoadGameFadeHolder,void*);
// Complete retail control-flow draft. Raw views keep unproved field identities opaque.
void GameLogic::startNewGame(bool loadingSaveGame)
{
    Rva009EBBE0(0);
    {
        Preferences00394260 prefs;
        if (F<bool,0x1278>(G012ED5C8)) {
            const AsciiString key("IsThreadedLoad");
            AsciiString *value=D0003E6DA(prefs.data+4,key);
            value->StringBase<char>::set("no",2);
        } else {
            const AsciiString key("IsThreadedLoad");
            AsciiString *value=D0003E6DA(prefs.data+4,key);
            value->StringBase<char>::set("yes",3);
        }
        D00030495(&prefs);
    }
    MenuGuard00394260 menuGuard;
    V178(G012ED668);
    F<bool,0x94>(this)=true;
    if(G012EF18C) D0003F7B5(G012EF18C);
    V014(G012F1B40);
    F<bool,0x114>(this)=F<bool,0xe60>(G012ED5C8);
    Rva009EBC00(2);
    F<bool,0x95>(this)=loadingSaveGame;
    if(F<int,0x10c>(this)==6 || F<int,0x10c>(this)==0 || F<int,0x10c>(this)==7)
        F<bool,0x1e>(G012ED5C8)=true;
    G012EF1DC=true;
    F<bool,0x69>(this)=true;
    D0003D578(G012F4C5C,false);
    if(F<bool,0x6d>(this)) D0002518A(G012F3330);
    if(!loadingSaveGame) {
        D0002A0DB(G012EF190,F<AsciiString,8>(G012ED5C8));
        D00023F9C(G012EF190,F<AsciiString,8>(G012ED5C8));
        if(!F<bool,0xa0>(this)) {
            if(F<int,0x10c>(this)==0 || F<int,0x10c>(this)==7) {
                if(F<void*,0xa4>(this)) {
                    V020(F<void*,0xa4>(this));
                    if(F<void*,0xa4>(this)) V004i(F<void*,0xa4>(this),1);
                    F<void*,0xa4>(this)=0;
                }
            }
            F<bool,0xa0>(this)=true;
        }
    }
    if(!F<bool,0x6d>(this)) V010(G012F3330);
    pump00394260();
    F<int,0x110>(this)=1000;
    D00024893(this,loadingSaveGame);
    F<bool,0xbb9>(G012ED5C8)=true;
    F<bool,0x91>(this)=true; F<bool,0x92>(this)=true; F<bool,0x93>(this)=true;
    F<int,0x98>(this)=-1;
    GameInfo *game=0;
    G012F708C=0;
    pump00394260();
    if(G012F7714) {
        pump00394260();
        if(G012F7730) G012F708C=game=(GameInfo*)V0C0p(G012F7730);
        else G012F708C=game=(GameInfo*)G012F7198;
        pump00394260();
    } else {
        pump00394260();
        if(G012ED62C && D00043EEB(G012ED62C)==1)
            G012F708C=game=(GameInfo*)((char*)G012ED62C+0x20);
        else if(F<int,0x10c>(this)==2) G012F708C=game=(GameInfo*)G012F7094;
        else if(F<int,0x10c>(this)==6) G012F708C=game=(GameInfo*)G012F7090;
        pump00394260();
    }
    pump00394260();
    checkForDuplicateColors(game);
    pump00394260();
    Encoded00394260 skirmish(false);
    if(game) {
        for(int i=0;i<8;++i) {
            pump00394260();
            void *slot=D0001EC18(game,i);
            if(!loadingSaveGame) D000324CA(slot);
            if(D000422DF(slot)) skirmish.value=0x637ab774;
        }
    } else if(F<int,0x10c>(this)==0 || F<int,0x10c>(this)==7) {
        if(G012F7094) { V000i((char*)G012F7094+0x58,1); G012F7094=0; }
    }
    pump00394260();
    populateRandomStartPosition(game);
    randomSide00394260(game);
    if(!F<void*,0x118>(this)) {
        F<void*,0x118>(this)=D00018D3B(this,loadingSaveGame);
        if(F<void*,0x118>(this)) V008p(F<void*,0x118>(this),game);
    }
    progress00394260(this,0);
    pump00394260();
    if(F<void*,0xa4>(this)) {
        V020(F<void*,0xa4>(this));
        if(F<void*,0xa4>(this)) V004i(F<void*,0xa4>(this),1);
        F<void*,0xa4>(this)=0;
    }
    setFPMode();
    F<bool,0xa0>(this)=false;
    progress00394260(this,1);
    F<int,0x3c>(this)=0;
    pump00394260();
    D00034644(this,F<AsciiString,8>(G012ED5C8));
    pump00394260();
    D00022697(G012F060C,&F<AsciiString,8>(G012ED5C8));
    { AssetList00394260 assets; Rva009EBA80((int)&assets); }
    {
        Stream00394260 stream;
        if(D0004AAB1(&stream,F<AsciiString,8>(G012ED5C8))) {
            Context00394260 context(1,2);
            V010map(G012EF4CC,F<AsciiString,8>(G012ED5C8),&stream,false,!loadingSaveGame);
        }
    }
    D00003D5F(G012EF428);
    D000015F0(this,F<AsciiString,8>(G012ED5C8));
    progress00394260(this,2);
    pump00394260(); pump00394260();
    if(game) {
        void *sides=G012EF428;
        short index=F<short,0>(F<void*,0x63c>(sides));
        while(index) {
            char *node=(char*)F<void*,0x63c>(sides)+index*16;
            short next=F<short,0>(node);
            if(F<short,6>(node)) { D0000FDF8((char*)sides+0x630,index); sides=G012EF428; }
            index=next;
        }
        if(V03Cb(G012ED524) || Rva00389840(skirmish.value,skirmish.value)) D00028155(G012EF428);
        D000298E3(this,skirmish,3);
        V010(G012F079C);
    }
    D00046254(this);
    if(G012EF428 && F<bool,0x668>(G012EF428)) D00024B36(G012EF428);
    progress00394260(this,12);
    V010(G012ED810);
    pump00394260();
    V024(G012ED748);
    progress00394260(this,13);
    if(!F<int,0x1a0>(this)) setFPMode();
    ++F<int,0x1a0>(this);
    V024(G012F076C);
    pump00394260();
    progress00394260(this,14);
    pump00394260();
    progress00394260(this,16);
    V018p(G012EF0E4,G012EF4CC);
    F<bool,0x12be>(G012F148C)=false;
    V030(G012F079C);
    progress00394260(this,17);
    Region00394260 extent;
    V020p(G012EF4CC,&extent);
    F<float,0x34>(G012F0898)=extent.hi.x-extent.lo.x;
    F<float,0x38>(G012F0898)=extent.hi.y-extent.lo.y;
    initShroud00394260(G012ED5BC,&extent,0.0f);
    notifyShroud00394260(G012ED5BC);
    initPartition00394260(G012ED5B8,&extent);
    if(G012ED5C0) { initTaint00394260(G012ED5C0,&extent,0.0f); resetTaint00394260(G012ED5C0); }
    V158p(G012F1270,&extent);
    V014i(G012EF4FC,F<int,0x24>(F<void*,0xc>(G012ED748)));
    V010(G012EF4FC);
    pump00394260(); progress00394260(this,18); pump00394260();
    V014b(G012EF4CC,loadingSaveGame);
    pump00394260(); progress00394260(this,19);
    D00035C56(G012F1044);
    progress00394260(this,20);
    D0004AE4E(F<void*,0xc>(G012EF214));
    pump00394260();
    D0002835D(this,loadingSaveGame);
    pump00394260(); progress00394260(this,30);
    V010p(G012EF0E4,G012EF4CC);
    void *observer=D0002F586(G012ED748,D0003ADD7(G012ED600,"ReplayObserver"));
    revealPermanently00394260(G012ED5BC,F<int,0x24>(observer));
    if(game) {
        for(int i=0;i<8;++i) {
            void *slot=D0001EC18(game,i);
            pump00394260();
            if(!slot || !D00040593(slot)) continue;
            void *player=D0002F586(G012ED748,D0003ADD7(G012ED600,str00394260(F<AsciiString,0x2c>(slot))));
            if(!player) continue;
            if(F<int,0x14>(slot)==-2) revealPermanently00394260(G012ED5BC,F<int,0x24>(player));
            else if(!F<bool,0x18>(G012ED5FC)) reveal00394260(G012ED5BC,F<int,0x24>(player));
        }
    }
    pump00394260();
    ObjectMapVector00394260 created;
    pump00394260();
    int progress=59;
    if(loadingSaveGame) {
        for(void *mapObject=F<void*,0>(G012ED5DC);mapObject;mapObject=F<void*,4>(mapObject)) {
            void *type=D00012814(mapObject);
            if(!type) continue;
            if(!(F<unsigned,0xd0>(type)&0x60000000)) continue;
            Coord00394260 pos=*D0001325A(mapObject);
            Matrix00394260 matrix;
            if(F<unsigned,0xd0>(type)&0x20000000) D000364AD(G012EF4CC,type,&pos,&matrix,1.0f);
            else if(F<unsigned,0xd0>(type)&0x40000000) D000050C9(G012EF4CC,type,&pos,&matrix,1.0f);
        }
        D0001FD39(this,&created,&progress,false,true);
    } else {
        D0001FD39(this,&created,&progress,false,false);
        ensureTree00394260<0x14c>(this,99999999,"TheOneTree");
        ensureTree00394260<0x150>(this,99999998,"TheNonInteractableTree");
        ensureTree00394260<0x154>(this,99999996,"TheGrabbableTree");
        ensureTree00394260<0x158>(this,99999997,"TheHarvestableTree");
        for(ObjectMapVector00394260::iterator i=created.begin();i!=created.end();++i) {
            pump00394260(); D000017A8(i->object,(char*)i->mapObject+0x24);
        }
    }
    progress00394260(this,40);
    progress=41;
    if(game && !loadingSaveGame) {
        for(int i=0;i<8;++i) {
            void *slot=D0001EC18(game,i);
            pump00394260();
            if(!slot || !D00040593(slot)) continue;
            void *player=D0002F586(G012ED748,D0003ADD7(G012ED600,str00394260(F<AsciiString,0x2c>(slot))));
            if(player) {
                if(F<int,0x14>(slot)==-2) {
                    F<int,0x14>(slot)=0;
                    void *pt=D0002CD8B(G012ED750,D0003ADD7(G012ED600,"FactionObserver"));
                    if(pt) for(int j=0;j<templateCount00394260();++j) {
                        pump00394260();
                        if(pt==D00037BD2(G012ED750,j)) {
                            F<int,0x14>(slot)=j;
                            if(j<=-2) F<int,0x10>(slot)=-1;
                            break;
                        }
                    }
                } else {
                    void *pt=D00037BD2(G012ED750,F<int,0x14>(slot));
                    placeNetwork00394260(i,slot,player,pt);
                }
            }
            progress00394260(this,progress++);
        }
    }
    pump00394260(); progress00394260(this,50);
    V038(G012F64BC); Sleep(1);
    D00002914(G012F33F8); D00038497(G012F33F8,false);
    preloadSpellTextures0059A3D0(); V018(G012F7014); Sleep(1);
    progress00394260(this,95); Sleep(1);
    V110(G012F1600); Sleep(1); V138(G012F1600); Sleep(1);
    if(G012ED62C) D00002A22(G012ED62C);
    AsciiString cameraName=D0003EC7A(G012ED600,D00009304(&G012A7A00));
    pump00394260();
    if(game) {
        int localSlot;
        D00033127(this,game,&localSlot);
        void *slot=D0001EC18(game,localSlot);
        if(D000279CB(slot)) cameraName.format(AsciiString("Player_%d_Start"),F<int,0x10>(slot)+1);
    }
    pump00394260(); progress00394260(this,96);
    V058(G012F1600); V110(G012F1600); V138(G012F1600);
    void *way=Rva00388820_FindWaypointByName(cameraName);
    if(way) { Coord00394260 pos=F<Coord00394260,0xc>(way); V0C4look(G012F1600,&pos,0,0,false); }
    else { Coord00394260 pos={50,50,0}; V0C4look(G012F1600,&pos,0,0,false); }
    progress00394260(this,97);
    V014(G012ED5B8); pump00394260();
    if(!loadingSaveGame) V028(G012ED748);
    V024(G012EF734);
    if(!loadingSaveGame && (F<int,0x10c>(this)==0 || F<int,0x10c>(this)==7 ||
        (G012ED62C && D00043EEB(G012ED62C)==1 && (F<int,0x2ac>(G012ED62C)==0 || F<int,0x2ac>(G012ED62C)==7)))) {
        pump00394260();
        for(int i=0;i<32;++i) {
            void *player=D00044F30(G012ED748,i);
            if(player && !F<int,0x2c>(player)) {
                D000380FA(player,(float)F<int,0x8c>(this),false);
                D000259CD(player,F<int,0x258>(player));
            }
        }
    }
    if(F<int,0x10c>(this)==1 || F<int,0x10c>(this)==5 || F<int,0x10c>(this)==2 ||
        (G012ED62C && D00043EEB(G012ED62C)==1 && (F<int,0x2ac>(G012ED62C)==2 || F<int,0x2ac>(G012ED62C)==1 || F<int,0x2ac>(G012ED62C)==5)))
        F<int,0x110>(this)=F<int,0xec0>(G012ED5C8);
    if((F<int,0x10c>(this)==1 || F<int,0x10c>(this)==5) && G012F7714) { V074(G012F7714); V024i(G012F7714,0); }
    if(!F<bool,0x11fc>(G012ED5C8)) {
        bool flag=false; AssetList00394260 assets;
        D0004AABB(G012F076C,&assets,&flag); Rva009EBAC0((int)&assets);
    }
    while((unsigned)bfmeForward_009EBB60()<100) { pump00394260(); D00008DEB(this); Sleep(100); }
    if(F<int,0x10c>(this)==4) {
        if(!F<int,0x48>(G012F4B58)) { D000339A6(G012F4B58,AsciiString("MainMenu.apt"),false); HideControlBar(true); }
        else {
            if(D0004A336(G012F4B58)) { V010i(D0004A336(G012F4B58),0); V014(D0004A336(G012F4B58)); }
            HideControlBar(true);
        }
    } else {
        if(G012ED63C) D00019F38(G012ED63C);
        else if(F<int,0xccc>(G012ED5C8)>0) { G012ED63C=new Stats00394260; D00019F38(G012ED63C); }
        if(F<int,0x10c>(this)==3) {
            D000466E1(G012ED748,D0002F586(G012ED748,D0003ADD7(G012ED600,"ReplayObserver")));
            F<void*,0x274>(G012F33F8)=D00044F30(G012ED748,F<int,0x2a4>(G012ED62C));
            F<bool,0xd>(G012EF0E4)=true;
            notifyShroud00394260(G012ED5BC);
            if(G012ED5C0) resetTaint00394260(G012ED5C0);
            D00019B64(G012F33F8,F<void*,0xc>(G012ED748));
        } else {
            void *player=F<void*,0xc>(G012ED748);
            D000466E1(G012ED748,F<void*,0x14>(G012ED748));
            D000466E1(G012ED748,player);
            D00019B64(G012F33F8,F<void*,0xc>(G012ED748));
            F<void*,0x274>(G012F33F8)=0;
        }
    }
    V140b(G012F1600,true); pump00394260();
    if(G012F08A0) D00014B14(&G012F08A0);
    if(D0004A7A5(G012ED62C)) {
        for(int i=0;i<32;++i) {
            void *player=D00044F30(G012ED748,i);
            pump00394260();
            if(player && D000179BD(player)) D0002F1CB(player,callback0038AE10,0);
        }
    }
    D00031C05(G012F33F8,F<void*,0xc>(G012ED748));
    if(!loadingSaveGame) D00032B14(G012F4B98);
    if(F<int,0x10c>(this)==4) HideControlBar(true); else ShowControlBar(false);
    if(!F<bool,0x6d>(this) && !F<bool,0x74>(this) && !F<int,0x1b8>(G012F19E8)) {
        D00045C28(G012F3330,AsciiString("FadeWholeScreen"),false); D0002518A(G012F3330);
    }
    F<bool,0xbb9>(G012ED5C8)=false;
    if(G012F71B4 && G012F7198 && F<int,0x10c>(this)==5) {
        Message00394260 message;
        message.buddyRequestType=BuddyRequest::BUDDYREQUEST_SETSTATUS; message.arg.status.status=GP_PLAYING; strcpy(message.arg.status.statusString,"Playing");
        sprintf(message.arg.status.locationString,"%s",D00025C98(D0002C7B4(G012F7198).str()).c_str());
        V018p(G012F71B4,&message);
    }
    if(!loadingSaveGame) {
        for(void *draw=V07Cp(G012F1464);draw;draw=F<void*,0x104>(draw)) { pump00394260(); D000323E9(draw); }
    }
    F<bool,0x69>(this)=false; Sleep(0); if(G012ED524) V040(G012ED524);
    if(G012F1600 && V1C8b(G012F1600)) {
        V1CC(G012F1600,0,0,0,true); Sleep(0); if(G012ED524) V040(G012ED524);
    }
    if(F<void*,0x118>(this)) {
        Sleep(0); if(G012ED524) V040(G012ED524);
        while((unsigned)bfmeForward_009EBB40()<100) { pump00394260(); Sleep(1); }
    } else { while((unsigned)bfmeForward_009EBB40()<100) { pump00394260(); Sleep(1); } }
    F<bool,0x6d>(this)=false; G012EF1DC=false; F<bool,0x40>(this)=true;
    if(D00041FF1(G012F706C) && !loadingSaveGame) D00002E64((char*)this+0x170);
    V010(G012ED5F4); D0000324C(this); F<bool,0x6c>(this)=false; D00003486(this);
    --F<int,0x1a0>(this);
    if(V0F0b(G012F1270) && F<void*,0x118>(this))
        while(!V014bret(F<void*,0x118>(this))) Sleep(5);
    int mode=F<int,0x10c>(this);
    if(mode==2 || mode==6 || mode==1 || mode==5) {
        postTimedOp(LoadGameFadeHolder(),&G012ED588);
        if(F<void*,0x118>(this)) F<bool,0xc>(F<void*,0x118>(this))=false;
        G012F089C=98.0f;
        if(F<int,0x10c>(this)==6) F<bool,0x111>(G012F1270)=true;
        V0D8(G012ED668,0,true);
    }
    if(G012ED4E5) F<int,0xcb4>(G012ED5C8)=2;
    else if(G012ED4E6) F<int,0xcb4>(G012ED5C8)=5;
    G012ED508=0; Rva009EBC00(0);
    if(G012EF18C) D00030071(G012EF18C);
}
