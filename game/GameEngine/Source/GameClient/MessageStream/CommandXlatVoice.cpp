// cl: /O2 /Ob2 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/stringbaseunicode
// stlport
// Ported from GeneralsMD/Code/GameEngine/Source/GameClient/MessageStream/CommandXlat.cpp.
// Copyright 2025 Electronic Arts Inc.; GPL-3.0-or-later, as in the vendored source.
// BFME voice ranges: 005A8A10..005A910E; 005A92D0..005A994D;
// dispatcher 005AA450..005AC3D0 including its switch tables.
// Layout and private ABI witnesses: build/unclaimed_map/astra_A/LAYOUTS.md.
// Existing direct-call bindings: build/unclaimed_map/astra_I/BINDINGS.md.
// Exact shared-TU reconstruction and verification: build/unclaimed_map/astra_L/REPORT.md.
// BFME returns bool: caller 0041EE1A tests AL after ILT 000196C8.
// Kept separate from CommandXlat.cpp because its narrower type declarations
// (including NameKeyGenerator and AudioEventRTS) conflict with these voice views.
#include <list>
#include <map>
#include <hash_map>
#include <climits>
#include <cstring>
#include "ascii_string.h"
#include "Common/UnicodeString.h"
inline AsciiString::~AsciiString() { ((StringBase<char>*)this)->releaseBuffer(); }
inline UnicodeString::~UnicodeString() { ((StringBase<wchar_t>*)this)->releaseBuffer(); }
class Coord3D { public: float x,y,z; };
struct ICoord2D { int x,y; };
struct IRegion2D { ICoord2D lo,hi; int width() const { return hi.x-lo.x; } int height() const { return hi.y-lo.y; } };

// Existing ledger declarations. These are symbol bindings, not new identity claims.
void d_00417060();
void d_00416fe0();
void dup_001cb020();
struct Q3IndexedItem;
struct Q3IndexedOwner { public:
 Q3IndexedItem* Rva0049B320();
 Q3IndexedItem* Rva0049B380();
 Q3IndexedItem* Rva0049B3E0();
 Q3IndexedItem* Rva0049B440();
 Q3IndexedItem* Rva0049B4A0();
 Q3IndexedItem* Rva0049B500();
 Q3IndexedItem* Rva0049B560();
 Q3IndexedItem* Rva0049B5C0();
 Q3IndexedItem* Rva0049B620();
 Q3IndexedItem* Rva0049B680();
 Q3IndexedItem* Rva0049B6E0();
 Q3IndexedItem* Rva0049B740();
};
class Q2FlagOwner { public: bool query(int); void Rva005A6D10(); void Rva005A6D40(); void Rva005A7030(); void Rva005A7060(); };
struct RvaC4390Interface;
struct RvaC4390First { public: RvaC4390Interface* getInterface(); };
struct RvaC4390Second { public: RvaC4390First* resolve(int); };
class AssistedTargetingObjectShim { public: void* find(int); };
void d_001cdbe0(); void d_00278830(); void d_002acd90(); void dup_000d2f40();
char bfmeGo1098B(int,int,int);
class BfmeThingDDE { public: int bfmeGoDDE(); };
struct BfmeFlagHolder; class BfmeFlagCandidate; struct BfmeThingEGA;
bool __stdcall bfmeMpSkirmishFlagGate(BfmeFlagHolder*, BfmeFlagCandidate*);
void* __stdcall bfmeGoEGAa(void*,BfmeThingEGA*);

class Rva00278830; class Rva002ACD90; class Rva001BE3F0; class Rva001BE270; class Drawable; class Object; class Player; class ThingTemplate; class CommandButton;
class Rva0049B320; class Rva001BFE20; class Rva001BFE40; class Rva001CF980; class Rva001C3920;
class PickAndPlayInfo { public: bool field00; char pad01[3]; Drawable* m_drawTarget; int* m_weaponSlot; int m_specialPowerType; Coord3D m_position; Rva0049B320* field1c; };
typedef _STL::list<Drawable*> DrawableList;
union GameMessageArgumentType { int integer; unsigned drawableID; ICoord2D pixel; IRegion2D pixelRegion; Coord3D location; };
class GameMessage { public:
 enum Type { MSG_INVALID=0, MSG_CREATE_SELECTED_GROUP=0x3e9 };
 char pad00[0x10]; Type m_type;
 Type getType() const { return m_type; }
 const GameMessageArgumentType* getArgument(int) const;
 void appendBooleanArgument(bool); void appendObjectIDArgument(unsigned);
};
enum GameMessageDisposition { KEEP_MESSAGE, DESTROY_MESSAGE };
enum CommandEvaluateType { DO_COMMAND, DO_HINT, DO_EVALUATE };
enum ObjectID { Rva005AA450ObjectID };
class AudioEventRTS { public:
 void setObjectID(ObjectID);
 AudioEventRTS(const AsciiString&,int); AudioEventRTS(const AudioEventRTS&); ~AudioEventRTS();
__forceinline void rva000B2250(unsigned a) {
 typedef void (AudioEventRTS::*Function)(unsigned);
 return (this->*reinterpret_cast<Function>(&AudioEventRTS::setObjectID))(a);
}int rva000B3BC0() {
 typedef int (AudioEventRTS::*Function)();
 return (this->*reinterpret_cast<Function>(&BfmeThingDDE::bfmeGoDDE))();
}
 void* m_vftable; char pad04[0x10]; AsciiString m_eventName; char pad18[0x40]; int field58; char pad5c[0x14];
};
class Overridable { public: void* field00; Overridable* m_override;
 const Overridable* getFinalOverride() const { if(m_override) return m_override->getFinalOverride();return this; }
};
template <class T> class OVERRIDE { public:
 const T* operator*() const { if(!m_overridable) return 0; return (T*)m_overridable->getFinalOverride(); }
 operator const T*() const { return **this; }
 T* m_overridable;
};
enum KindOfType { KINDOF_PLACEHOLDER };
enum NameKeyType { NAMEKEY_NONE };
class Module;
class ThingTemplate : public Overridable { public:
 bool isKindOf(KindOfType) const;
 char pad08[0x18]; AsciiString field20; char pad24[0xa4]; unsigned m_kindOf[6]; char pade0[0x354]; int field434;
__forceinline bool rva000A2CB0(int a) const {
 typedef bool (ThingTemplate::*Function)(int) const;
 return (this->*reinterpret_cast<Function>(&ThingTemplate::isKindOf))(a);
}
 const AudioEventRTS* getSound(int) const;
};
class CommandButton { public: char pad00[0x10]; int m_command; bool isContextCommand() const; int getCommandType() const { return m_command; } };

class Thing { public: bool isKindOf(KindOfType) const; const ThingTemplate* getTemplate() const; };

class SpawnBehaviorInterface {
public:
    virtual void slot00(); // vtable +0x0
    virtual void slot01(); // vtable +0x4
    virtual Object* getClosestSlave(const Coord3D*); // vtable +0x8

};

class Rva000D2F40 { public: char pad00[0x10]; unsigned field10;bool rva000D2F40(int a) const {
 typedef bool (Rva000D2F40::*Function)(int) const;
 union { void (*raw)(); Function member; } fn; fn.raw=dup_000d2f40;
 return (this->*fn.member)(a);
} };
enum CrushSquishTestType { Rva005AA450CrushTest };
enum Relationship { Rva005AA450Relationship };
enum SpecialPowerType { Rva005AA450SpecialPower };
class SpecialPowerModuleInterface;
class Rva001CF980Result;
class Object {
public:
protected:
 Module* findModule(NameKeyType) const;
public:
 Player* getControllingPlayer() const;
 void* unidentified_001BFE20() const;
 Rva001CF980Result* queryAt001CF980();
 SpecialPowerModuleInterface* findSpecialPowerModuleInterface(SpecialPowerType) const;
 void bfmeResetSafeOcclusionFrame();
    virtual void slot00(); // vtable +0x0
    virtual void slot01(); // vtable +0x4
    virtual void slot02(); // vtable +0x8
    virtual void slot03(); // vtable +0xC
    virtual void slot04(); // vtable +0x10
    virtual void slot05(); // vtable +0x14
    virtual void slot06(); // vtable +0x18
    virtual void slot07(); // vtable +0x1C
    virtual void slot08(); // vtable +0x20
    virtual void slot09(); // vtable +0x24
    virtual Drawable* getDrawable() const; // vtable +0x28

 OVERRIDE<ThingTemplate> m_template; char pad08[0x30]; Coord3D m_position; char pad44[0x30]; unsigned m_id;
 char pad78[0x18]; unsigned field90; unsigned field94; char pad98[0x78]; Rva000D2F40 field110; char pad124[0xe0]; Rva00278830* field204; char pad208[0xc]; Object* m_containedBy;
 public:
 __forceinline const ThingTemplate* getTemplate() const { return m_template; }
__forceinline Rva001BFE20* rva001BFE20() const {
 typedef Rva001BFE20* (Object::*Function)() const;
 return (this->*reinterpret_cast<Function>(&Object::unidentified_001BFE20))();
}Rva001BFE40* rva001BFE40() {
 typedef Rva001BFE40* (Object::*Function)();
 return (this->*reinterpret_cast<Function>(&RvaC4390First::getInterface))();
}Rva001CF980* rva001CF980() {
 typedef Rva001CF980* (Object::*Function)();
 return (this->*reinterpret_cast<Function>(&Object::queryAt001CF980))();
}
__forceinline Rva001C3920* rva001C3920(int a) const {
 typedef Rva001C3920* (Object::*Function)(int) const;
 return (this->*reinterpret_cast<Function>(&Object::findSpecialPowerModuleInterface))(a);
}Object* rva001CB020(int a) {
 typedef Object* (Object::*Function)(int);
 union { void (*raw)(); Function member; } fn; fn.raw=dup_001cb020;
 return (this->*fn.member)(a);
} Relationship getRelationship(const Object*) const;
__forceinline Rva002ACD90* rva001BEE60(int a) {
 typedef Rva002ACD90* (Object::*Function)(int);
 return (this->*reinterpret_cast<Function>(&Object::findModule))(a);
}Object* rva001CB0C0(int a) {
 typedef Object* (Object::*Function)(int);
 return (this->*reinterpret_cast<Function>(&RvaC4390Second::resolve))(a);
}Rva001BE3F0* rva001BE3F0() const {
 typedef Rva001BE3F0* (Object::*Function)() const;
 return (this->*reinterpret_cast<Function>(&Object::getControllingPlayer))();
}
__forceinline bool rva001CC790(Object* a,int b) const {
 typedef bool (Object::*Function)(Object*,int) const;
 return (this->*reinterpret_cast<Function>(&Object::crushPolicy))(a,b);
}
 bool crushPolicy(Object*,enum CrushSquishTestType) const;
__forceinline void rva001C3020() {
 typedef void (Object::*Function)();
 return (this->*reinterpret_cast<Function>(&Object::bfmeResetSafeOcclusionFrame))();
}bool rva001CDBE0() const {
 typedef bool (Object::*Function)() const;
 union { void (*raw)(); Function member; } fn; fn.raw=d_001cdbe0;
 return (this->*fn.member)();
}Rva001BE270* rva001BE270(int a) const {
 typedef Rva001BE270* (Object::*Function)(int) const;
 return (this->*reinterpret_cast<Function>(&AssistedTargetingObjectShim::find))(a);
}
 unsigned getID() const { return m_id; }
 const Coord3D* getPosition() const { return &m_position; }
 bool isKindOf(int k) const { return ((const Thing*)this)->isKindOf((KindOfType)k); }
 bool isLocallyControlled() const;
 bool rva001C9C10() const;
 int rva001C77B0(int,const Object*,int) const;
 int rva001BE310(int,const Object*,const Coord3D*,int) const;
 SpawnBehaviorInterface* getSpawnBehaviorInterface() const;

};

class Drawable { public: void* field00; ThingTemplate* field04; char pad08[0xf4]; Object* m_object;
 const ThingTemplate* rvaTemplate() const { if(!field04) return 0;return (const ThingTemplate*)field04->getFinalOverride(); }
__forceinline bool rva00416FC0(int a) const {
 typedef bool (Drawable::*Function)(int) const;
 return (this->*reinterpret_cast<Function>(&Q2FlagOwner::query))(a);
}
 Object* getObject() const { return m_object; } const Coord3D* getPosition() const;
__forceinline const AudioEventRTS* rva00416FA0(int a) const {
 typedef const AudioEventRTS* (Drawable::*Function)(int) const;
 return (this->*reinterpret_cast<Function>(&ThingTemplate::getSound))(a);
}const AudioEventRTS* rva00416FE0(const AsciiString& a) const {
 typedef const AudioEventRTS* (Drawable::*Function)(const AsciiString&) const;
 union { void (*raw)(); Function member; } fn; fn.raw=d_00416fe0;
 return (this->*fn.member)(a);
}
__forceinline int rva00417060() const {
 typedef int (Drawable::*Function)() const;
 union { void (*raw)(); Function member; } fn; fn.raw=d_00417060;
 return (this->*fn.member)();
}
__forceinline const AudioEventRTS* rva005A6D10() {
 typedef const AudioEventRTS* (Drawable::*Function)();
 return (this->*reinterpret_cast<Function>(&Q2FlagOwner::Rva005A6D10))();
}const AudioEventRTS* rva005A6D40() {
 typedef const AudioEventRTS* (Drawable::*Function)();
 return (this->*reinterpret_cast<Function>(&Q2FlagOwner::Rva005A6D40))();
}
__forceinline const AudioEventRTS* rva005A7030() {
 typedef const AudioEventRTS* (Drawable::*Function)();
 return (this->*reinterpret_cast<Function>(&Q2FlagOwner::Rva005A7030))();
}const AudioEventRTS* rva005A7060() {
 typedef const AudioEventRTS* (Drawable::*Function)();
 return (this->*reinterpret_cast<Function>(&Q2FlagOwner::Rva005A7060))();
}
};
class PlayerTemplate { public: char pad00[0xe4]; AsciiString m_beaconTemplate; const AsciiString& getBeaconTemplate() const { return m_beaconTemplate; } };
class Player { public: char pad00[4]; PlayerTemplate* m_playerTemplate;
 const PlayerTemplate* getPlayerTemplate() const { return m_playerTemplate; }
 bool isPlayerActive() const;
 Object* rva000D4660(bool,Object**) const;
 int iterateObjects(int (*)(Object*,void*),void*) const;
 void countObjectsByThingTemplate(int,const ThingTemplate* const*,bool,int*,bool) const;
};
class PlayerList { public: char pad00[0xc]; Player* m_localPlayer; Player* getLocalPlayer() const { return m_localPlayer; } };
class ControlBar { public: const CommandButton* findCommandButton(const AsciiString&); void togglePurchaseScience(); };
class GameLogic { public: char pad00[0x91]; bool m_showBehindBuildingMarkers; char pad92[0x7a]; int m_mode;
 bool isInMultiplayerGame(); bool rva000652A0() const; bool isInReplayGame() const { return m_mode==3; }
};
class GlobalData { public:
 char pad00[0x38]; bool m_useCloudMap; char pad39[0xb]; bool m_useLightMap; char pad45[0x1b]; bool m_useAlternateMouse;
 char pad61[3]; bool m_useShadowVolumes; char pad65[0xaa7]; int m_netMinPlayers; char padb10[0x7c]; int m_maxParticleCount;
 char padb90[0xc9]; bool m_TiVOFastMode;
};
class Mouse { public: char pad00[0x10ec]; unsigned m_dragTolerance; char pad10f0[4]; unsigned m_clickTime;
 bool rva005A49E0(const ICoord2D*,const ICoord2D*) const;
};
class Radar { public: bool rva00107140(Coord3D*); };
class Rva004891C0 { public: char pad00[0x4d]; bool field4d; bool test() const; };
class Rva003968A0 { public: bool test(); };
enum RecorderModeType { RECORDER_NONE };
class RecorderClass { public: RecorderModeType getMode(); };

class NameKeyGenerator { public: __forceinline int rva0008FFC0(const char* a) {
 return nameToKey(a);
} NameKeyType nameToKey(const char*); NameKeyType nameToKey(const AsciiString&); };
class GameWindow { public: bool winIsHidden(); };
class ThingFactory { public: const ThingTemplate* findTemplate(const AsciiString&); };
class MultiplayerSettings { public: char pad00[0x14]; int m_maxBeaconsPerPlayer; int getMaxBeaconsPerPlayer() { return m_maxBeaconsPerPlayer; } };

class InGameUI {
public:
    virtual void slot00(); // vtable +0x0
    virtual void slot01(); // vtable +0x4
    virtual void slot02(); // vtable +0x8
    virtual void slot03(); // vtable +0xC
    virtual void slot04(); // vtable +0x10
    virtual void slot05(); // vtable +0x14
    virtual void slot06(); // vtable +0x18
    virtual void slot07(); // vtable +0x1C
    virtual void slot08(); // vtable +0x20
    virtual void slot09(); // vtable +0x24
    virtual void slot0A(); // vtable +0x28
    virtual void slot0B(); // vtable +0x2C
    virtual void __cdecl message(UnicodeString,...); // MSVC overloaded slot +0x34
    virtual void __cdecl message(AsciiString,...); // MSVC overloaded slot +0x30
    virtual void slot0E(); // vtable +0x38
    virtual void slot0F(); // vtable +0x3C
    virtual void slot10(); // vtable +0x40
    virtual void slot11(); // vtable +0x44
    virtual void slot12(); // vtable +0x48
    virtual void slot13(); // vtable +0x4C
    virtual void slot14(); // vtable +0x50
    virtual void slot15(); // vtable +0x54
    virtual void slot16(); // vtable +0x58
    virtual void slot17(); // vtable +0x5C
    virtual void slot18(); // vtable +0x60
    virtual void slot19(); // vtable +0x64
    virtual void slot1A(); // vtable +0x68
    virtual void slot1B(); // vtable +0x6C
    virtual void slot1C(); // vtable +0x70
    virtual void slot1D(); // vtable +0x74
    virtual void slot1E(); // vtable +0x78
    virtual void slot1F(); // vtable +0x7C
    virtual void slot20(); // vtable +0x80
    virtual void slot21(); // vtable +0x84
    virtual void slot22(); // vtable +0x88
    virtual void slot23(); // vtable +0x8C
    virtual void slot24(); // vtable +0x90
    virtual void slot25(); // vtable +0x94
    virtual void slot26(); // vtable +0x98
    virtual void slot27(); // vtable +0x9C
    virtual void slot28(); // vtable +0xA0
    virtual void slot29(); // vtable +0xA4
    virtual void slot2A(); // vtable +0xA8
    virtual void slot2B(); // vtable +0xAC
    virtual void slot2C(); // vtable +0xB0
    virtual void slot2D(); // vtable +0xB4
    virtual void setGUICommand(const CommandButton*); // vtable +0xB8
    virtual const CommandButton* getGUICommand(); // vtable +0xBC
    virtual void slot30(); // vtable +0xC0
    virtual void slot31(); // vtable +0xC4
    virtual void slot32(); // vtable +0xC8
    virtual void slot33(); // vtable +0xCC
    virtual void slot34(); // vtable +0xD0
    virtual void slot35(); // vtable +0xD4
    virtual void slot36(); // vtable +0xD8
    virtual void slot37(); // vtable +0xDC
    virtual void selectDrawable(Drawable*); // vtable +0xE0
    virtual void slot39(); // vtable +0xE4
    virtual void deselectAllDrawables(); // vtable +0xE8
    virtual void selectAllUnitsByType(int,Player*); // vtable +0xEC
    virtual int getSelectCount(); // vtable +0xF0
    virtual void slot3D(); // vtable +0xF4
    virtual void slot3E(); // vtable +0xF8
    virtual const DrawableList* getAllSelectedDrawables() const; // vtable +0xFC
    virtual void slot40(); // vtable +0x100
    virtual Drawable* getFirstSelectedDrawable(); // vtable +0x104
    virtual void slot42(); // vtable +0x108
    virtual void slot43(); // vtable +0x10C
    virtual void slot44(); // vtable +0x110
    virtual void slot45(); // vtable +0x114
    virtual void slot46(); // vtable +0x118
    virtual void slot47(); // vtable +0x11C
    virtual void slot48(); // vtable +0x120
    virtual void slot49(); // vtable +0x124
    virtual void slot4A(); // vtable +0x128
    virtual void slot4B(); // vtable +0x12C
    virtual void slot4C(); // vtable +0x130
    virtual void slot4D(); // vtable +0x134
    virtual void slot4E(); // vtable +0x138
    virtual void slot4F(); // vtable +0x13C
    virtual void slot50(); // vtable +0x140
    virtual void slot51(); // vtable +0x144
    virtual void slot52(); // vtable +0x148
    virtual void slot53(); // vtable +0x14C
    virtual void slot54(); // vtable +0x150
    virtual void slot55(); // vtable +0x154
    virtual void slot56(); // vtable +0x158
    virtual void selectUnitsMatchingCurrentSelection(); // vtable +0x15C

 char pad04[0x12ac]; bool m_waypointMode; bool m_forceAttackMode; bool m_forceMoveMode; bool m_preferSelectionMode;
 bool m_cameraRotateLeft; bool m_cameraRotateRight; bool m_cameraZoomIn; bool m_cameraZoomOut;
 bool field12b8; bool field12b9; bool field12ba; bool field12bb;
 bool isInForceAttackMode() const { return m_forceAttackMode; }
 bool getInputEnabled() const;
 bool rva0043EC00() const;
 void rva0043CEC0();

};

class MessageStream;

class GameClient;

class View;

class WindowLayout;

class Shell { public: char pad00[0x58]; bool m_active; WindowLayout* top(); };
class GameWindowManager;

class GameInfo;

class AudioManager {
public:
    virtual void slot00(); // vtable +0x0
    virtual void slot01(); // vtable +0x4
    virtual void slot02(); // vtable +0x8
    virtual void slot03(); // vtable +0xC
    virtual void slot04(); // vtable +0x10
    virtual void slot05(); // vtable +0x14
    virtual void slot06(); // vtable +0x18
    virtual void slot07(); // vtable +0x1C
    virtual void slot08(); // vtable +0x20
    virtual void slot09(); // vtable +0x24
    virtual void slot0A(); // vtable +0x28
    virtual void slot0B(); // vtable +0x2C
    virtual void slot0C(); // vtable +0x30
    virtual void slot0D(); // vtable +0x34
    virtual void slot0E(); // vtable +0x38
    virtual void slot0F(); // vtable +0x3C
    virtual void slot10(); // vtable +0x40
    virtual unsigned addAudioEvent(const AudioEventRTS*); // vtable +0x44
    virtual void slot12(); // vtable +0x48
    virtual void slot13(); // vtable +0x4C
    virtual void slot14(); // vtable +0x50
    virtual void slot15(); // vtable +0x54
    virtual void slot16(); // vtable +0x58
    virtual bool rvaSlot5c(const AudioEventRTS*); // vtable +0x5C
    virtual void slot18(); // vtable +0x60
    virtual void slot19(); // vtable +0x64
    virtual void slot1A(); // vtable +0x68
    virtual void slot1B(); // vtable +0x6C
    virtual void slot1C(); // vtable +0x70
    virtual void slot1D(); // vtable +0x74
    virtual void slot1E(); // vtable +0x78
    virtual void slot1F(); // vtable +0x7C
    virtual void slot20(); // vtable +0x80
    virtual void slot21(); // vtable +0x84
    virtual void slot22(); // vtable +0x88
    virtual void slot23(); // vtable +0x8C
    virtual void slot24(); // vtable +0x90
    virtual void slot25(); // vtable +0x94
    virtual void slot26(); // vtable +0x98
    virtual void slot27(); // vtable +0x9C
    virtual void slot28(); // vtable +0xA0
    virtual void slot29(); // vtable +0xA4
    virtual void slot2A(); // vtable +0xA8
    virtual void slot2B(); // vtable +0xAC
    virtual void slot2C(); // vtable +0xB0
    virtual void slot2D(); // vtable +0xB4
    virtual void slot2E(); // vtable +0xB8
    virtual void slot2F(); // vtable +0xBC
    virtual void slot30(); // vtable +0xC0
    virtual void slot31(); // vtable +0xC4
    virtual void slot32(); // vtable +0xC8
    virtual void slot33(); // vtable +0xCC
    virtual void slot34(); // vtable +0xD0
    virtual void slot35(); // vtable +0xD4
    virtual void slot36(); // vtable +0xD8
    virtual void slot37(); // vtable +0xDC
    virtual void slot38(); // vtable +0xE0
    virtual void slot39(); // vtable +0xE4
    virtual void slot3A(); // vtable +0xE8
    virtual void slot3B(); // vtable +0xEC
    virtual void slot3C(); // vtable +0xF0
    virtual void slot3D(); // vtable +0xF4
    virtual void slot3E(); // vtable +0xF8
    virtual void slot3F(); // vtable +0xFC
    virtual void slot40(); // vtable +0x100
    virtual void slot41(); // vtable +0x104
    virtual void slot42(); // vtable +0x108
    virtual void slot43(); // vtable +0x10C
    virtual void slot44(); // vtable +0x110
    virtual void slot45(); // vtable +0x114
    virtual void slot46(); // vtable +0x118
    virtual void slot47(); // vtable +0x11C
    virtual void slot48(); // vtable +0x120
    virtual const char* getMiscAudio() const; // vtable +0x124

};

class Display;

extern InGameUI* TheInGameUI;
extern GameClient* TheGameClient;
extern MessageStream* TheMessageStream;
extern PlayerList* ThePlayerList;
extern View* TheTacticalView;
extern GameLogic* TheGameLogic;
extern GlobalData* TheGlobalData;
extern Mouse* TheMouse;
extern Radar* TheRadar;
extern ControlBar* TheControlBar;
extern Shell* TheShell;
extern RecorderClass* TheRecorder;
extern GameWindowManager* TheWindowManager;
extern NameKeyGenerator* TheNameKeyGenerator;
extern ThingFactory* TheThingFactory;
extern MultiplayerSettings* TheMultiplayerSettings;
extern GameInfo* TheGameInfo;
extern AudioManager* TheAudio;
extern Display* TheDisplay;
extern Rva004891C0* g_va012F3330;
extern Rva003968A0* g_va012F1028;
extern void* g_va012F71B4;
extern void* g_va012F4988;
void rva00511CC0(int);
void HideInGameChat();
void rva0052B2A0();
void rva00569D80();
void Rva004C1040(int);
int Rva00459060(bool);
int rva005A9B00(Object*,void*);
bool pickAndPlayUnitVoiceResponse(const DrawableList*,GameMessage::Type,PickAndPlayInfo* = 0);

class CommandTranslator { public:
 virtual GameMessageDisposition translateGameMessage(const GameMessage*);
 virtual ~CommandTranslator();
private:
 int opaque04; bool m_teamExists; char pad09[3];
 ICoord2D m_mouseRightDragAnchor, m_mouseRightDragLift;
 unsigned m_mouseRightDown, m_mouseRightUp, field24, field28; bool field2c;
 CommandEvaluateType evaluateContextCommand(Drawable*,const Coord3D*,CommandEvaluateType);
 int evaluateForceAttack(Drawable*,const Coord3D*,CommandEvaluateType);
 void rva005A9C90(const GameMessage*);
};


// Body-local opaque interfaces; offsets are witnessed in LAYOUTS.md.
namespace _STL { template<> _List_base<Object*,allocator<Object*> >::~_List_base(); }
class Rva001BFE20 { public:
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
 virtual void fieldF0(_STL::list<Object*>*);
};
class Rva001BFE40 { public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual const AudioEventRTS* field24();
 virtual const AudioEventRTS* field28();
};
class Rva001CF980 { public:
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
 virtual void slot41();
 virtual void slot42();
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual void slot46();
 virtual void slot47();
 virtual void slot48();
 virtual void slot49();
 virtual void slot4a();
 virtual void slot4b();
 virtual void slot4c();
 virtual void slot4d();
 virtual void slot4e();
 virtual void slot4f();
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
 virtual void slot5a();
 virtual void slot5b();
 virtual void slot5c();
 virtual void slot5d();
 virtual void slot5e();
 virtual void slot5f();
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
 virtual void slot6a();
 virtual void slot6b();
 virtual void slot6c();
 virtual void slot6d();
 virtual void slot6e();
 virtual void slot6f();
 virtual void slot70();
 virtual void slot71();
 virtual void slot72();
 virtual void slot73();
 virtual void slot74();
 virtual void slot75();
 virtual void slot76();
 virtual void slot77();
 virtual void slot78();
 virtual void slot79();
 virtual void slot7a();
 virtual void slot7b();
 virtual void slot7c();
 virtual const AudioEventRTS* field1f4(Object*);
 virtual const AudioEventRTS* field1f8(Object*);
};
class Rva001C3920 { public:
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
 virtual const AudioEventRTS* field44();
 virtual const AudioEventRTS* field48();
 virtual const AudioEventRTS* field4c();
 virtual const AudioEventRTS* field50();
};
class Rva0049B320 { public:
__forceinline const AudioEventRTS* rva0049B320() {
 typedef const AudioEventRTS* (Rva0049B320::*Function)();
 return (this->*reinterpret_cast<Function>(&Q3IndexedOwner::Rva0049B320))();
}
__forceinline const AudioEventRTS* rva0049B380() {
 typedef const AudioEventRTS* (Rva0049B320::*Function)();
 return (this->*reinterpret_cast<Function>(&Q3IndexedOwner::Rva0049B380))();
}
__forceinline const AudioEventRTS* rva0049B3E0() {
 typedef const AudioEventRTS* (Rva0049B320::*Function)();
 return (this->*reinterpret_cast<Function>(&Q3IndexedOwner::Rva0049B3E0))();
}
__forceinline const AudioEventRTS* rva0049B440() {
 typedef const AudioEventRTS* (Rva0049B320::*Function)();
 return (this->*reinterpret_cast<Function>(&Q3IndexedOwner::Rva0049B440))();
}
__forceinline const AudioEventRTS* rva0049B4A0() {
 typedef const AudioEventRTS* (Rva0049B320::*Function)();
 return (this->*reinterpret_cast<Function>(&Q3IndexedOwner::Rva0049B4A0))();
}
__forceinline const AudioEventRTS* rva0049B500() {
 typedef const AudioEventRTS* (Rva0049B320::*Function)();
 return (this->*reinterpret_cast<Function>(&Q3IndexedOwner::Rva0049B500))();
}
__forceinline const AudioEventRTS* rva0049B560() {
 typedef const AudioEventRTS* (Rva0049B320::*Function)();
 return (this->*reinterpret_cast<Function>(&Q3IndexedOwner::Rva0049B560))();
}
__forceinline const AudioEventRTS* rva0049B5C0() {
 typedef const AudioEventRTS* (Rva0049B320::*Function)();
 return (this->*reinterpret_cast<Function>(&Q3IndexedOwner::Rva0049B5C0))();
}
__forceinline const AudioEventRTS* rva0049B620() {
 typedef const AudioEventRTS* (Rva0049B320::*Function)();
 return (this->*reinterpret_cast<Function>(&Q3IndexedOwner::Rva0049B620))();
}
__forceinline const AudioEventRTS* rva0049B680() {
 typedef const AudioEventRTS* (Rva0049B320::*Function)();
 return (this->*reinterpret_cast<Function>(&Q3IndexedOwner::Rva0049B680))();
}
__forceinline const AudioEventRTS* rva0049B6E0() {
 typedef const AudioEventRTS* (Rva0049B320::*Function)();
 return (this->*reinterpret_cast<Function>(&Q3IndexedOwner::Rva0049B6E0))();
}
__forceinline const AudioEventRTS* rva0049B740() {
 typedef const AudioEventRTS* (Rva0049B320::*Function)();
 return (this->*reinterpret_cast<Function>(&Q3IndexedOwner::Rva0049B740))();
}
};

struct Rva0037F190Result { void* field00; void* field04;
 Rva0037F190Result() {}
 Rva0037F190Result(const Rva0037F190Result& b):field00(b.field00),field04(b.field04) {}
};
class ExperienceLevelSystem { public:
 void rva0037F190(Rva0037F190Result*,Object*);
 bool rva0037E810(Rva0037F190Result); int rva0037D810(Rva0037F190Result);
};
extern ExperienceLevelSystem* g_va012F0888;
class Rva00098E50 { public: __forceinline const ThingTemplate* getTemplate() const {
 typedef const ThingTemplate* (Rva00098E50::*Function)() const;
 return (this->*reinterpret_cast<Function>(&Thing::getTemplate))();
} };
typedef bool (ExperienceLevelSystem::*Rva0037E810Function)(Rva0037F190Result);
__forceinline Rva0037E810Function Rva0037E810Binding() {
 union { bool (__stdcall *raw)(BfmeFlagHolder*,BfmeFlagCandidate*); Rva0037E810Function member; } fn;
 fn.raw=bfmeMpSkirmishFlagGate; return fn.member;
}

typedef int (ExperienceLevelSystem::*Rva0037D810Function)(Rva0037F190Result);
__forceinline Rva0037D810Function Rva0037D810Binding() {
 union { void* (__stdcall *raw)(void*,BfmeThingEGA*); Rva0037D810Function member; } fn;
 fn.raw=bfmeGoEGAa; return fn.member;
}

// 005A8A10: nine stack inputs; 005A92D0: ECX drawable, seven stack inputs.
class Rva00278830 { public: char pad00[0x31e]; bool field31e;bool rva00278830() const {
 typedef bool (Rva00278830::*Function)() const;
 union { void (*raw)(); Function member; } fn; fn.raw=d_00278830;
 return (this->*fn.member)();
} };
class Rva002ACD90Data { public: char pad00[0x70]; AudioEventRTS field70,fielde0,field150,field1c0,field230,field2a0; };
class Rva002ACD90 {
public:
 void* field00;
 Rva002ACD90Data* field04;
__forceinline bool rva002ACD90(const Coord3D* a,const Coord3D* b) const {
 typedef bool (Rva002ACD90::*Function)(const Coord3D*,const Coord3D*) const;
 union { void (*raw)(); Function member; } fn; fn.raw=d_002acd90;
 return (this->*fn.member)(a,b);
}
 // Retail 005A8D0D/005A8D20/005A8D40: repeated module-data pointer loads.
 // Keep the natural inline accessor and branch-local output assignments.
 __forceinline const Rva002ACD90Data* rvaField04() const { return field04; }
};
class Rva001BE3F0 { public: char pad00[0x24]; int field24; };
bool Rva003723A0(int,const Coord3D*,const Coord3D*);
extern Coord3D g_va012B87AC;
__forceinline bool Rva003723A0(int a,const Coord3D* b,const Coord3D* c) {
 typedef bool (__cdecl *Function)(int,const Coord3D*,const Coord3D*);
 return reinterpret_cast<Function>(bfmeGo1098B)(a,b,c);
}

// 005A8A10 consumes Drawable in ESI plus nine stack arguments; its caller
// cleans 0x24 bytes at 005ABB72. The same-TU definition lets VC7.1 derive this
// private convention naturally. Full 1790-byte body verified against retail.
static __declspec(noinline) void Rva005A8A10(Drawable* draw,GameMessage::Type msg,Object* obj,PickAndPlayInfo* info,const AudioEventRTS*& sound,const AudioEventRTS*& group,const AudioEventRTS*& sound2,const AudioEventRTS*& group2,int* rank0,int* rank10)
{
 const AudioEventRTS* choices[4][4];memset(choices,0,sizeof(choices));
 if(msg==0x7e8) {
  choices[0][0]=draw->rva00416FA0(38);
  choices[0][1]=draw->rva00416FA0(39);
  choices[0][2]=draw->rva00416FA0(40);
  choices[0][3]=draw->rva00416FA0(41);
  choices[2][0]=draw->rva00416FA0(79);
  choices[2][1]=draw->rva00416FA0(80);
  choices[2][2]=draw->rva00416FA0(81);
  choices[2][3]=draw->rva00416FA0(82);
 } else {
  choices[0][0]=draw->rva00416FA0(5);
  choices[0][1]=draw->rva00416FA0(21);
  choices[0][2]=draw->rva00416FA0(23);
  choices[0][3]=draw->rva00416FA0(29);
  choices[1][0]=draw->rva00416FA0(6);
  choices[1][1]=draw->rva00416FA0(22);
  choices[1][2]=draw->rva00416FA0(24);
  choices[1][3]=draw->rva00416FA0(30);
  choices[2][0]=draw->rva00416FA0(46);
  choices[2][1]=draw->rva00416FA0(62);
  choices[2][2]=draw->rva00416FA0(64);
  choices[2][3]=draw->rva00416FA0(70);
  choices[3][0]=draw->rva00416FA0(47);
  choices[3][1]=draw->rva00416FA0(63);
  choices[3][2]=draw->rva00416FA0(65);
  choices[3][3]=draw->rva00416FA0(71);
 }
 bool hasPosition=info && !(info->m_position.x==g_va012B87AC.x && info->m_position.y==g_va012B87AC.y && info->m_position.z==g_va012B87AC.z);
 Rva00278830* ai=obj->field204;
 if(!ai) return;
 bool flag=ai->rva00278830() || ai->field31e;
 if(TheInGameUI->m_waypointMode && flag) return;
 if(*rank10<=0) {
  if(hasPosition) {
   static int key=TheNameKeyGenerator->rva0008FFC0("StealthUpdate");
   Rva002ACD90* q=obj->rva001BEE60(key);
   if(q && info) {
    Object* parent=obj->rva001CB0C0(0);
    Coord3D position;
    if(parent) position=*parent->getPosition(); else position=*obj->getPosition();
    if(!q->rva002ACD90(obj->getPosition(),&position) && q->rva002ACD90(&info->m_position,&info->m_position)) {
     if(msg==0x7e8) {
      sound=&q->rvaField04()->field230;group=0;sound2=&q->rvaField04()->field2a0;group2=0;
     } else {
      sound=&q->rvaField04()->field70;group=&q->rvaField04()->fielde0;sound2=&q->rvaField04()->field150;group2=&q->rvaField04()->field1c0;
     }
     if(TheAudio->rvaSlot5c(sound)) goto specialCases;
    }
   }
   if(TheAudio->rvaSlot5c(choices[0][2]) || TheAudio->rvaSlot5c(choices[0][1])) {
    Rva001BE3F0* q=obj->rva001BE3F0();
    if(q && Rva003723A0(q->field24,obj->getPosition(),&info->m_position)) {
     
if(obj->field110.rva000D2F40(0x93)) {
      sound=choices[0][1];group=choices[1][1];sound2=choices[2][1];group2=choices[3][1];
     } else {
      sound=choices[0][2];group=choices[1][2];sound2=choices[2][2];group2=choices[3][2];
     }

     if(TheAudio->rvaSlot5c(sound)) goto specialCases;
    }
   }
  }
  
if(obj->field110.field10&0x80000) {
   sound=choices[0][3];group=choices[1][3];sound2=choices[2][3];group2=choices[3][3];
  } else {
   sound=choices[0][0];group=choices[1][0];sound2=choices[2][0];group2=choices[3][0];
  }

 }
specialCases:
 if(msg!=0x7e8 && TheInGameUI->m_forceMoveMode && info && info->m_drawTarget) {
  Object* target=info->m_drawTarget->getObject();
  if(target && obj->rva001CC790(target,2)) {
   const AudioEventRTS* custom=draw->rva00416FE0(AsciiString("VoiceCrush"));
   if(TheAudio->rvaSlot5c(custom)) {
    sound=custom;
    group=draw->rva00416FE0(AsciiString("VoiceCrushGroup"));
    sound2=draw->rva00416FE0(AsciiString("VoiceCrush2"));
    group2=draw->rva00416FE0(AsciiString("VoiceCrushGroup2"));
    *rank0=1;
   }
  }
 }
 if(msg==0x441) {
  const AudioEventRTS* custom=draw->rva00416FE0(AsciiString("VoiceSalvage"));
  if(TheAudio->rvaSlot5c(custom)) {
   sound=custom;
   group=draw->rva00416FE0(AsciiString("VoiceSalvageGroup"));
   sound2=draw->rva00416FE0(AsciiString("VoiceSalvage2"));
   group2=draw->rva00416FE0(AsciiString("VoiceSalvageGroup2"));
   *rank0=2;
  }
 }
}

class Rva001BE270Template { public:
 char pad00[0x128]; AudioEventRTS field128,field198,field208,field278,field2e8,field358,field3c8,field438;
};
class Rva001BE270 { public: void* field00; Rva001BE270Template* field04; };
// 005A92D0 consumes Drawable in ECX plus seven stack arguments; caller cleanup
// is 0x1C at 005ABBB6. Full 1661-byte body verified with resolved direct calls.
static __declspec(noinline) void Rva005A92D0(Drawable* draw,GameMessage::Type msg,Object* obj,PickAndPlayInfo* info,const AudioEventRTS*& sound,const AudioEventRTS*& group,const AudioEventRTS*& sound2,const AudioEventRTS*& group2)
{
 const AudioEventRTS* choices[4][5];memset(choices,0,sizeof(choices));
 if(msg==0x7e7) {
  choices[0][0]=draw->rva00416FA0(33);
  if(draw->rva00416FC0(34)) choices[0][1]=draw->rva00416FA0(34);else choices[0][1]=draw->rva00416FA0(33);
  choices[0][2]=draw->rva00416FA0(35);
  choices[0][3]=draw->rva00416FA0(36);
  choices[0][4]=draw->rva00416FA0(37);
  choices[2][0]=draw->rva00416FA0(74);
  if(draw->rva00416FC0(75)) choices[2][1]=draw->rva00416FA0(75);else choices[2][1]=draw->rva00416FA0(74);
  choices[2][2]=draw->rva00416FA0(76);
  choices[2][3]=draw->rva00416FA0(77);
  choices[2][4]=draw->rva00416FA0(78);
 } else {
  choices[0][0]=draw->rva00416FA0(7);
  if(draw->rva00416FC0(9)) choices[0][1]=draw->rva00416FA0(9);else choices[0][1]=draw->rva00416FA0(7);
  choices[0][2]=draw->rva00416FA0(15);
  choices[0][3]=draw->rva00416FA0(25);
  choices[0][4]=draw->rva00416FA0(27);
  choices[1][0]=draw->rva00416FA0(8);
  if(draw->rva00416FC0(10)) choices[1][1]=draw->rva00416FA0(10);else choices[1][1]=draw->rva00416FA0(8);
  choices[1][2]=draw->rva00416FA0(16);
  choices[1][3]=draw->rva00416FA0(26);
  choices[1][4]=draw->rva00416FA0(28);
  choices[2][0]=draw->rva00416FA0(48);
  if(draw->rva00416FC0(50)) choices[2][1]=draw->rva00416FA0(50);else choices[2][1]=draw->rva00416FA0(48);
  choices[2][2]=draw->rva00416FA0(56);
  choices[2][3]=draw->rva00416FA0(66);
  choices[2][4]=draw->rva00416FA0(68);
  choices[3][0]=draw->rva00416FA0(49);
  if(draw->rva00416FC0(51)) choices[3][1]=draw->rva00416FA0(51);else choices[3][1]=draw->rva00416FA0(49);
  choices[3][2]=draw->rva00416FA0(57);
  choices[3][3]=draw->rva00416FA0(67);
  choices[3][4]=draw->rva00416FA0(69);
  if(msg==0x426) {
   sound=draw->rva00416FE0(AsciiString("VoiceBombard"));
   group=draw->rva00416FE0(AsciiString("VoiceBombardGroup"));
   sound2=draw->rva00416FE0(AsciiString("VoiceBombard2"));
   group2=draw->rva00416FE0(AsciiString("VoiceBombardGroup2"));
  }
 }
 if(!TheAudio->rvaSlot5c(sound) && info && info->m_drawTarget) {
  const ThingTemplate* targetTemplate=info->m_drawTarget->rvaTemplate();
  if(targetTemplate) {
   const AsciiString& targetName=targetTemplate->field20;
   AsciiString name(msg==0x7e7?"VoiceEnterStateAttackUnit":"VoiceAttackUnit");
   name+=targetName;
   sound=draw->rva00416FE0(name);
   group=draw->rva00416FE0(name+"Group");
   sound2=draw->rva00416FE0(name+"2");
   group2=draw->rva00416FE0(name+"Group2");
   if(!TheAudio->rvaSlot5c(sound)) {
    if(targetTemplate->rva000A2CB0(7)) {
     sound=choices[0][3];group=choices[1][3];sound2=choices[2][3];group2=choices[3][3];
    } else if(targetTemplate->rva000A2CB0(11)) {
     sound=choices[0][4];group=choices[1][4];sound2=choices[2][4];group2=choices[3][4];
    }
   }
  }
 }
 if(!TheAudio->rvaSlot5c(sound)) {
  Rva001BE270* weapon=obj->rva001BE270(0);
  if(weapon) {
   const Rva001BE270Template* data=weapon->field04;
   if(data) {
    if(msg==0x7e7) {
     sound=&data->field2e8;group=&data->field358;sound2=&data->field3c8;group2=&data->field438;
    } else {
     sound=&data->field128;group=&data->field198;sound2=&data->field208;group2=&data->field278;
    }
   }
  }
 }
 if(!TheAudio->rvaSlot5c(sound)) {
  if(obj->rva001CDBE0()) {
   sound=choices[0][1];group=choices[1][1];sound2=choices[2][1];group2=choices[3][1];
  } else if(info && info->field00) {
   sound=choices[0][2];group=choices[1][2];sound2=choices[2][2];group2=choices[3][2];
  } else {
   sound=choices[0][0];group=choices[1][0];sound2=choices[2][0];group2=choices[3][0];
  }
 }
}
class Rva005A7CF0FourStringRecord { public:
 AsciiString field00,field04,field08,field0c;
 Rva005A7CF0FourStringRecord(const AsciiString& a,const AsciiString& b,const AsciiString& c,const AsciiString& d):field00(a),field04(b),field08(c),field0c(d) {}
 Rva005A7CF0FourStringRecord(const Rva005A7CF0FourStringRecord&);
};
struct Rva005AA450Less { bool operator()(const Rva005A7CF0FourStringRecord& a,const Rva005A7CF0FourStringRecord& b) const {
 int n=a.field00.compareNoCase(b.field00);if(n) return n<0;
 n=a.field08.compareNoCase(b.field08);if(n) return n<0;
 n=a.field04.compareNoCase(b.field04);if(n) return n<0;
 return a.field0c.compareNoCase(b.field0c)<0;
} };
struct Rva005AA450Value { const AudioEventRTS* field00; const AudioEventRTS* field04; const AudioEventRTS* field08; const AudioEventRTS* field0c; Object* field10; int field14; };
struct Rva005AA450Hash { unsigned operator()(Object* obj) const { return (unsigned)obj; } };
struct Gen_t_005aa3f0_p12cd { int a[3]; };
struct Gen_t_005a8580_p12cd { int a[3]; };
struct Gen_t_005a8560_m12pod { int field00; };
typedef _STL::hash_map<int,Gen_t_005aa3f0_p12cd> Rva005AA3F0Hash;
typedef _STL::pair<const int,Gen_t_005a8580_p12cd> Rva005A8580Pair;
typedef _STL::hashtable<Rva005A8580Pair,int,_STL::hash<int>,_STL::_Select1st<Rva005A8580Pair>,_STL::equal_to<int>,_STL::allocator<Rva005A8580Pair> > Rva005A8580Table;
typedef _STL::pair<const int,Gen_t_005a8560_m12pod> Rva005A8280Pair;
typedef _STL::hashtable<Rva005A8280Pair,int,_STL::hash<int>,_STL::_Select1st<Rva005A8280Pair>,_STL::equal_to<int>,_STL::allocator<Rva005A8280Pair> > Rva005A8280Table;
namespace _STL {
 template<> Rva005AA3F0Hash::hash_map();
 template<> Rva005A8580Table::~hashtable();

}
struct Rva005A8690Value { unsigned m_key; };
struct Rva005A8690ExtractKey { const unsigned& operator()(const Rva005A8690Value& x) const { return x.m_key; } };
typedef _STL::hashtable<Rva005A8690Value,unsigned,_STL::hash<unsigned>,Rva005A8690ExtractKey,_STL::equal_to<unsigned>,_STL::allocator<Rva005A8690Value> > Rva005A8690Table;

void *bfmeAllocNode(unsigned int bytes);

struct BfmeHashValue
{
	unsigned int m_bfmeKey;
	int m_bfmeSecond;
};

void bfmeConstructB(BfmeHashValue *slot, const BfmeHashValue *source);

struct BfmeHashNode
{
	BfmeHashNode *m_bfmeNext;
	BfmeHashValue m_bfmeValue;
};

struct BfmeBucketVector
{
	unsigned int size() const
	{
		return (unsigned int)(m_finish - m_start);
	}

	BfmeHashNode *&operator[](unsigned int index)
	{
		return m_start[index];
	}

	BfmeHashNode **m_start;
	BfmeHashNode **m_finish;
	BfmeHashNode **m_endOfStorage;
};

class Gen_005A82F0;

struct BfmeInsertResultB
{
	BfmeInsertResultB(BfmeHashNode *node, Gen_005A82F0 *table, bool inserted)
	{
		m_bfmeNode = node;
		m_bfmeTable = table;
		m_bfmeInserted = inserted;
	}

	BfmeHashNode *m_bfmeNode;
	Gen_005A82F0 *m_bfmeTable;
	bool m_bfmeInserted;
};

class Gen_005A82F0
{
public:
	BfmeInsertResultB bfmeInsertUnique(const BfmeHashValue *value);

private:
	char m_bfmeHead[4];
	BfmeBucketVector m_bfmeBuckets;
	int m_bfmeCount;
};

BfmeInsertResultB Gen_005A82F0::bfmeInsertUnique(const BfmeHashValue *value)
{
	unsigned int key = value->m_bfmeKey;
	unsigned int index = key % m_bfmeBuckets.size();
	BfmeHashNode *first = m_bfmeBuckets[index];

	for (BfmeHashNode *node = first; node; node = node->m_bfmeNext)
	{
		if (node->m_bfmeValue.m_bfmeKey == key)
			return BfmeInsertResultB(node, this, false);
	}

	BfmeHashNode *created = (BfmeHashNode *)bfmeAllocNode(sizeof(BfmeHashNode));

	created->m_bfmeNext = 0;
	bfmeConstructB(&created->m_bfmeValue, value);
	created->m_bfmeNext = first;
	m_bfmeBuckets[index] = created;
	++m_bfmeCount;

	return BfmeInsertResultB(created, this, true);
}


typedef _STL::hash_map<Object*,int,Rva005AA450Hash> Rva005AA450NativeObjects;
typedef _STL::pair<Object* const,int> Rva005AA450ObjectPair;
typedef _STL::hashtable<Rva005AA450ObjectPair,Object*,Rva005AA450Hash,_STL::_Select1st<Rva005AA450ObjectPair>,_STL::equal_to<Object*>,_STL::allocator<Rva005AA450ObjectPair> > Rva005AA450ObjectTable;

namespace _STL {

}
// Storage has the native container's alignment and extent. Only lifecycle calls
// cross the existing ledger's anonymous template spelling; iteration is native.
class Rva005AA450Objects {
 unsigned field00[sizeof(Rva005AA450NativeObjects)/sizeof(unsigned)];
 Rva005AA450NativeObjects* native() { return reinterpret_cast<Rva005AA450NativeObjects*>(this); }
public:
 typedef Rva005A8280Table::iterator iterator;
 __forceinline Rva005AA450Objects() { reinterpret_cast<Rva005AA3F0Hash*>(this)->Rva005AA3F0Hash::hash_map(); }
 __forceinline ~Rva005AA450Objects() { reinterpret_cast<Rva005A8580Table*>(this)->~Rva005A8580Table(); }
 __forceinline void insert(const Rva005AA450ObjectPair& x) {
 reinterpret_cast<Rva005A8690Table*>(this)->resize(native()->size()+1);
 reinterpret_cast<Gen_005A82F0*>(this)->bfmeInsertUnique(reinterpret_cast<const BfmeHashValue*>(&x));
 }
 __forceinline iterator begin() { return reinterpret_cast<Rva005A8280Table*>(this)->begin(); }
 __forceinline iterator end() { return iterator(0,reinterpret_cast<Rva005A8280Table*>(this)); }
};


typedef _STL::map<Rva005A7CF0FourStringRecord,Rva005AA450Value,Rva005AA450Less> Rva005AA450NativeSounds;
void b_005a9f90(); // Existing symbols.csv body binding for Gen_setmd_005a9f90.
struct Gen_t_005a8640_m40cd { int a[10]; ~Gen_t_005a8640_m40cd(); };
typedef _STL::_Rb_tree<Gen_t_005a8640_m40cd,Gen_t_005a8640_m40cd,_STL::_Identity<Gen_t_005a8640_m40cd>,_STL::less<Gen_t_005a8640_m40cd>,_STL::allocator<Gen_t_005a8640_m40cd> > Rva005A8640Tree;

// The existing insertion identity spells a four-string key as AsciiString.
// Its member pointer addresses the first slot of the witnessed 16-byte key.
struct upgradePairWide {
 typedef AsciiString first_type;
 typedef Rva005AA450Value second_type;
 AsciiString first,field04,field08,field0c;
 Rva005AA450Value second;
};
namespace _STL {
 template<> struct equal_to<AsciiString> {
  bool operator()(const AsciiString& a,const AsciiString& b) const {
   return Rva005AA450Less()(reinterpret_cast<const Rva005A7CF0FourStringRecord&>(a),reinterpret_cast<const Rva005A7CF0FourStringRecord&>(b));
  }
 };
 template<> void _Construct(upgradePairWide*,const upgradePairWide&);
}
typedef _STL::_Rb_tree<AsciiString,upgradePairWide,_STL::_Select1st<upgradePairWide>,_STL::equal_to<AsciiString>,_STL::allocator<upgradePairWide> > Rva005AA0F0Tree;

class Rva005AA450Sounds {
 unsigned field00[sizeof(Rva005AA450NativeSounds)/sizeof(unsigned)];
 Rva005AA450NativeSounds* native() { return reinterpret_cast<Rva005AA450NativeSounds*>(this); }
public:
 typedef Rva005AA0F0Tree::iterator iterator;
 typedef Rva005AA450NativeSounds::value_type value_type;
 __forceinline Rva005AA450Sounds() { native()->Rva005AA450NativeSounds::map(); }
 __forceinline ~Rva005AA450Sounds() {
  typedef void (Rva005AA450Sounds::*Function)();
  union { void (*raw)(); Function member; } fn; fn.raw=b_005a9f90;
  (this->*fn.member)();
 }
 __forceinline bool empty() { return native()->empty(); }
 __forceinline iterator begin() { return reinterpret_cast<Rva005AA0F0Tree*>(this)->begin(); }
 __forceinline iterator end() { return reinterpret_cast<Rva005AA0F0Tree*>(this)->end(); }
 __forceinline void clear() { reinterpret_cast<Rva005A8640Tree*>(this)->clear(); }
 __forceinline _STL::pair<iterator,bool> insert(const value_type& x) { return reinterpret_cast<Rva005AA0F0Tree*>(this)->insert_unique(reinterpret_cast<const upgradePairWide&>(x)); }
};

struct Rva005AA450Rank {
 int field00; bool field04; int field08,field0c,field10;

 bool operator<(const Rva005AA450Rank& b) const {
  if(field00<b.field00) return true;
  if(field00>b.field00) return false;
  if(field04) {
   if(!b.field04) return false;
   if(field08<b.field08) return true;
   if(field08>b.field08) return false;
   if(field0c<=b.field0c) return false;
   return true;
  }
  if(b.field04) return true;
  if(field10<b.field10) return true;
  return false;
 }
 bool operator==(const Rva005AA450Rank& b) const { return !(*this<b) && !(b<*this); }
};

// BFME returns bool: caller 0041EE12 tests AL at 0041EE1A. The ZH void
// signature on ILT 000196C8 is not the BFME return contract.
bool pickAndPlayUnitVoiceResponse(const DrawableList* list,GameMessage::Type msgType,PickAndPlayInfo* info)
{
 if(!list) return false;
 Object* target=0;
 if(info && info->m_drawTarget) target=info->m_drawTarget->getObject();
 Rva005AA450Sounds sounds;
 Rva005AA450Rank best={0,false,INT_MIN,INT_MAX,INT_MIN};
 Rva005AA450Objects candidates;
 int ordinal=0;
 for(DrawableList::const_iterator it=list->begin();it!=list->end();++it) {
  ++ordinal;Object* obj=(*it)->getObject();
  if(!obj) continue;
  if(obj->getTemplate()->m_kindOf[1]&0x8000) continue;
  Rva001BFE20* group=obj->rva001BFE20();
  if(group) {
   _STL::list<Object*> objects;
   group->fieldF0(&objects);
   for(_STL::list<Object*>::const_iterator j=objects.begin(),end=objects.end();j!=end;++j) {
    Object* member=*j;
    if(member && !(member->getTemplate()->m_kindOf[1]&0x8000)) candidates.insert(_STL::make_pair(member,ordinal));
   }
  } else {
   if((msgType==0x7e7 || msgType==0x7e8) && (obj->field94&0x20)) continue;
   candidates.insert(_STL::make_pair(obj,ordinal));
  }
 }
 for(Rva005AA450Objects::iterator it=candidates.begin();it!=candidates.end();) {
  Object* obj=reinterpret_cast<Object*>(it->first); int ordinal=it->second.field00; ++it;
  Drawable* draw=obj->getDrawable();
  if(!draw) continue;
  const AudioEventRTS *sound=0,*groupSound=0,*sound2=0,*groupSound2=0;
  
  Rva005AA450Rank rank; rank.field08=INT_MIN; rank.field00=0; rank.field0c=ordinal; rank.field10=draw->rva00417060();
  rank.field04=(obj->getTemplate()->m_kindOf[2]&0x02000000)!=0;
  if(rank.field04) {
   Rva0037F190Result level;g_va012F0888->rva0037F190(&level,obj);
   if((g_va012F0888->*Rva0037E810Binding())(level)) rank.field08=(g_va012F0888->*Rva0037D810Binding())(level);
  }
  switch(msgType) {
  case 0x42c: case 0x42d:
   sound=draw->rva00416FE0(AsciiString("VoiceSupply"));
   groupSound=draw->rva00416FE0(AsciiString("VoiceSupplyGroup"));
   sound2=draw->rva00416FE0(AsciiString("VoiceSupply2"));
   groupSound2=draw->rva00416FE0(AsciiString("VoiceSupplyGroup2"));
   break;
  case 0x422:
   if(info->m_drawTarget) {
    Rva001CF980* q=obj->rva001CF980();
    if(q) { sound=q->field1f4(info->m_drawTarget->getObject());sound2=q->field1f8(info->m_drawTarget->getObject()); }
    else { sound=draw->rva00416FA0(0x20);sound2=draw->rva00416FA0(0x49); }
   } break;
  case 0x3e9: case 0x3f7: case 0x3f8: case 0x3f9: case 0x3fa: case 0x3fb: case 0x3fc: case 0x3fd: case 0x3fe: case 0x3ff: case 0x400:
   if(obj->field110.field10&0x80000) { sound=draw->rva005A6D10();groupSound=draw->rva005A6D40();sound2=draw->rva005A7030();groupSound2=draw->rva005A7060(); }
   else { if(obj->field90&4) sound=draw->rva00416FA0(1);else sound=draw->rva00416FA0(0);groupSound=draw->rva00416FA0(2);sound2=draw->rva00416FA0(0x2a);groupSound2=draw->rva00416FA0(0x2b); }
   break;
  case 0x41d: case 0x41e:
   sound=draw->rva00416FE0(AsciiString("VoiceUnload"));
   groupSound=draw->rva00416FE0(AsciiString("VoiceUnloadGroup"));
   sound2=draw->rva00416FE0(AsciiString("VoiceUnload2"));
   groupSound2=draw->rva00416FE0(AsciiString("VoiceUnloadGroup2"));
   break;
  case 0x429:
   sound=draw->rva00416FE0(AsciiString("VoiceRepair"));
   groupSound=draw->rva00416FE0(AsciiString("VoiceRepairGroup"));
   sound2=draw->rva00416FE0(AsciiString("VoiceRepair2"));
   groupSound2=draw->rva00416FE0(AsciiString("VoiceRepairGroup2"));
   break;
  case 0x420: case 0x421:
   sound=draw->rva00416FE0(AsciiString("VoiceCombatDrop"));
   groupSound=draw->rva00416FE0(AsciiString("VoiceCombatDropGroup"));
   sound2=draw->rva00416FE0(AsciiString("VoiceCombatDrop2"));
   groupSound2=draw->rva00416FE0(AsciiString("VoiceCombatDropGroup2"));
   break;
  case 0x42b: {
   bool custom=false;
   if(!target) goto ordinaryEnter;
   {
    if(((Rva00098E50*)target)->getTemplate()) {
     const AsciiString& targetName=((Rva00098E50*)target)->getTemplate()->field20;
     AsciiString name("VoiceEnterUnit");name+=targetName;
     sound=draw->rva00416FE0(name);groupSound=draw->rva00416FE0(name+"Group");
     sound2=draw->rva00416FE0(name+"2");groupSound2=draw->rva00416FE0(name+"Group2");
     custom=TheAudio->rvaSlot5c(sound);
    }
    if(custom) break;
    if(target->isKindOf(0x20)) {
   sound=draw->rva00416FE0(AsciiString("VoiceGetHealed"));
   groupSound=draw->rva00416FE0(AsciiString("VoiceGetHealedGroup"));
   sound2=draw->rva00416FE0(AsciiString("VoiceGetHealed2"));
   groupSound2=draw->rva00416FE0(AsciiString("VoiceGetHealedGroup2"));
    } else if(target->isKindOf(7)) {
   sound=draw->rva00416FE0(AsciiString("VoiceGarrison"));
   groupSound=draw->rva00416FE0(AsciiString("VoiceGarrisonGroup"));
   sound2=draw->rva00416FE0(AsciiString("VoiceGarrison2"));
   groupSound2=draw->rva00416FE0(AsciiString("VoiceGarrisonGroup2"));
    } else if(obj->getRelationship(target)!=2) {
   sound=draw->rva00416FE0(AsciiString("VoiceEnterHostile"));
   groupSound=draw->rva00416FE0(AsciiString("VoiceEnterHostileGroup"));
   sound2=draw->rva00416FE0(AsciiString("VoiceEnterHostile2"));
   groupSound2=draw->rva00416FE0(AsciiString("VoiceEnterHostileGroup2"));
    } else {
     goto ordinaryEnter;
    }
   }
   break;
ordinaryEnter:
   sound=draw->rva00416FE0(AsciiString("VoiceEnter"));
   groupSound=draw->rva00416FE0(AsciiString("VoiceEnterGroup"));
   sound2=draw->rva00416FE0(AsciiString("VoiceEnter2"));
   groupSound2=draw->rva00416FE0(AsciiString("VoiceEnterGroup2"));
   break;
  }
  case 0x418: case 0x42a:
   sound=draw->rva00416FE0(AsciiString("VoiceBuildResponse"));
   groupSound=draw->rva00416FE0(AsciiString("VoiceBuildResponseGroup"));
   sound2=draw->rva00416FE0(AsciiString("VoiceBuildResponse2"));
   groupSound2=draw->rva00416FE0(AsciiString("VoiceBuildResponseGroup2"));
   break;
  case 0x439:
   if(info && info->m_weaponSlot) {
    switch(*info->m_weaponSlot) {
    case 0:
   sound=draw->rva00416FE0(AsciiString("VoicePrimaryWeaponMode"));
   groupSound=draw->rva00416FE0(AsciiString("VoicePrimaryWeaponModeGroup"));
   sound2=draw->rva00416FE0(AsciiString("VoicePrimaryWeaponMode2"));
   groupSound2=draw->rva00416FE0(AsciiString("VoicePrimaryWeaponModeGroup2"));
     break;
    case 1:
   sound=draw->rva00416FE0(AsciiString("VoiceSecondaryWeaponMode"));
   groupSound=draw->rva00416FE0(AsciiString("VoiceSecondaryWeaponModeGroup"));
   sound2=draw->rva00416FE0(AsciiString("VoiceSecondaryWeaponMode2"));
   groupSound2=draw->rva00416FE0(AsciiString("VoiceSecondaryWeaponModeGroup2"));
     break;
    case 2:
   sound=draw->rva00416FE0(AsciiString("VoiceTertiaryWeaponMode"));
   groupSound=draw->rva00416FE0(AsciiString("VoiceTertiaryWeaponModeGroup"));
   sound2=draw->rva00416FE0(AsciiString("VoiceTertiaryWeaponMode2"));
   groupSound2=draw->rva00416FE0(AsciiString("VoiceTertiaryWeaponModeGroup2"));
     break;
   } } break;
  case 0x432: case 0x433:
   sound=draw->rva00416FA0(0x11);groupSound=draw->rva00416FA0(0x12);sound2=draw->rva00416FA0(0x3a);groupSound2=draw->rva00416FA0(0x3b);break;
  case 0x40f: case 0x410: case 0x411: case 0x455:
   if(info && info->m_specialPowerType) {
    Rva001C3920* q=obj->rva001C3920(info->m_specialPowerType);
    if(q) { sound=q->field44();groupSound=q->field48();sound2=q->field4c();groupSound2=q->field50(); }
   } break;
  case 0x7da: sound=draw->rva00416FA0(0xc);sound2=draw->rva00416FA0(0x35);break;
  case 0x7de: sound=draw->rva00416FA0(0xd);sound2=draw->rva00416FA0(0x36);break;
  case 0x7df: sound=draw->rva00416FA0(0xe);sound2=draw->rva00416FA0(0x37);break;
  case 0x7e0: sound=draw->rva00416FA0(0xb);sound2=draw->rva00416FA0(0x34);break;
  case 0x7e1: sound=draw->rva00416FA0(0x13);sound2=draw->rva00416FA0(0x3c);break;
  case 0x7db:
   sound=draw->rva00416FE0(AsciiString("VoiceDesperateAttack"));
   groupSound=draw->rva00416FE0(AsciiString("VoiceDesperateAttackGroup"));
   sound2=draw->rva00416FE0(AsciiString("VoiceDesperateAttack2"));
   groupSound2=draw->rva00416FE0(AsciiString("VoiceDesperateAttackGroup2"));
   break;
  case 0x7dc:
   sound=draw->rva00416FE0(AsciiString("VoiceRapidFire"));
   groupSound=draw->rva00416FE0(AsciiString("VoiceRapidFireGroup"));
   sound2=draw->rva00416FE0(AsciiString("VoiceRapidFire2"));
   groupSound2=draw->rva00416FE0(AsciiString("VoiceRapidFireGroup2"));
   break;
  case 0x7dd:
   sound=draw->rva00416FE0(AsciiString("VoiceCaptureBuildingComplete"));
   groupSound=draw->rva00416FE0(AsciiString("VoiceCaptureBuildingCompleteGroup"));
   sound2=draw->rva00416FE0(AsciiString("VoiceCaptureBuildingComplete2"));
   groupSound2=draw->rva00416FE0(AsciiString("VoiceCaptureBuildingCompleteGroup2"));
   break;
  case 0x427: case 0x428: case 0x42e: case 0x42f: case 0x441: case 0x7e8:
   Rva005A8A10(draw,msgType,obj,info,sound,groupSound,sound2,groupSound2,&rank.field00,&best.field00);break;
  case 0x40d: case 0x40e: case 0x424: case 0x425: case 0x426: case 0x7e7:
   Rva005A92D0(draw,msgType,obj,info,sound,groupSound,sound2,groupSound2);break;
  case 0x7e2: sound=draw->rva00416FA0(0x14);sound2=draw->rva00416FA0(0x3d);break;
  case 0x7e3: sound=draw->rva00416FA0(0x1f);sound2=draw->rva00416FA0(0x48);break;
  case 0x7e9: {
   Rva001BFE40* q=obj->rva001BFE40();
   if(!q) { Object* other=obj->rva001CB020(0);if(other) q=other->rva001BFE40(); }
   if(q) { sound=q->field24();sound2=q->field28(); }
   break;
  }
  case 0x7e4: if(info && info->field1c) {
   sound=info->field1c->rva0049B320();
   groupSound=info->field1c->rva0049B3E0();
   sound2=info->field1c->rva0049B380();
   groupSound2=info->field1c->rva0049B440();
   } break;
  case 0x7e5: if(info && info->field1c) {
   sound=info->field1c->rva0049B4A0();
   groupSound=info->field1c->rva0049B560();
   sound2=info->field1c->rva0049B500();
   groupSound2=info->field1c->rva0049B5C0();
   } break;
  case 0x7e6: if(info && info->field1c) {
   sound=info->field1c->rva0049B620();
   groupSound=info->field1c->rva0049B6E0();
   sound2=info->field1c->rva0049B680();
   groupSound2=info->field1c->rva0049B740();
   } break;

  }
  if(TheAudio->rvaSlot5c(sound) || TheAudio->rvaSlot5c(groupSound) || TheAudio->rvaSlot5c(sound2) || TheAudio->rvaSlot5c(groupSound2)) {
   if(!TheAudio->rvaSlot5c(groupSound) && TheAudio->rvaSlot5c(sound)) groupSound=sound;
   if(!TheAudio->rvaSlot5c(groupSound2) && TheAudio->rvaSlot5c(sound2)) groupSound2=sound2;
   if(best<rank) { sounds.clear();best=rank; }
   if(best==rank) {
    AsciiString name,nameGroup,name2,nameGroup2;
    if(TheAudio->rvaSlot5c(sound)) name=sound->m_eventName;
    if(TheAudio->rvaSlot5c(groupSound)) nameGroup=groupSound->m_eventName;
    if(TheAudio->rvaSlot5c(sound2)) name2=sound2->m_eventName;
    if(TheAudio->rvaSlot5c(groupSound2)) nameGroup2=groupSound2->m_eventName;
    Rva005A7CF0FourStringRecord key(name,nameGroup,name2,nameGroup2);
    Rva005AA450Value value={sound,groupSound,sound2,groupSound2,obj,0};
    ++sounds.insert(Rva005AA450Sounds::value_type(key,value)).first->second.field14;
   }
  }
 }
 if(sounds.empty()) return false;
 Rva005AA450Sounds::iterator bestSound=sounds.begin();
 for(Rva005AA450Sounds::iterator it=++sounds.begin();it!=sounds.end();++it) {
  if(it->second.field14>bestSound->second.field14) bestSound=it;
 }
 Rva005AA450Value& value=bestSound->second;
 int threshold=value.field10->getTemplate()->field434;
 const AudioEventRTS* play[2];
 if(value.field14>=threshold && threshold>0) { play[0]=value.field04;play[1]=value.field0c; }
 else { play[0]=value.field00;play[1]=value.field08; }
 bool played=false;
 for(unsigned i=0;i<2;++i) {
  const AudioEventRTS* sound=play[i];
  if(TheAudio->rvaSlot5c(sound)) {
   AudioEventRTS event(*sound);
   if(value.field10) {
    event.rva000B2250(value.field10->getID());
    if(msgType==0x426 || msgType==0x425 || msgType==0x424 || msgType==0x40e || msgType==0x40d || msgType==0x7e7) value.field10->rva001C3020();
   }
   TheAudio->addAudioEvent(&event);
   const_cast<AudioEventRTS*>(sound)->field58=event.rva000B3BC0();
   played=true;
  }
 }
 return played;
}
