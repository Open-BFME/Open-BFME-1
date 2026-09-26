// cl: /O2 /Ob2 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/stringbaseunicode
// stlport
// Ported from GeneralsMD/Code/GameEngine/Source/GameClient/MessageStream/CommandXlat.cpp.
// Copyright 2025 Electronic Arts Inc.; GPL-3.0-or-later, as in the vendored source.
// BFME layout/call witnesses: build/gap_005ade0d/LAYOUTS.md and region_{a,b}.asm.
#include <list>
#include "ascii_string.h"
#include "Common/UnicodeString.h"
inline AsciiString::~AsciiString() { ((StringBase<char>*)this)->releaseBuffer(); }
inline UnicodeString::~UnicodeString() { ((StringBase<wchar_t>*)this)->releaseBuffer(); }
class Coord3D { public: float x,y,z; };
struct ICoord2D { int x,y; };
struct IRegion2D { ICoord2D lo,hi; int width() const { return hi.x-lo.x; } int height() const { return hi.y-lo.y; } };
class Drawable; class Object; class Player; class ThingTemplate; class CommandButton;
class PickAndPlayInfo;
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
class AudioEventRTS { public: AudioEventRTS(const AsciiString&,int); ~AudioEventRTS(); void* m_vftable; char opaque04[0x6c]; };
class CommandButton { public: char pad00[0x10]; int m_command; bool isContextCommand() const; int getCommandType() const { return m_command; } };
enum KindOfType { KINDOF_PLACEHOLDER };
class Thing { public: bool isKindOf(KindOfType) const; };

class SpawnBehaviorInterface {
public:
    virtual void slot00(); // vtable +0x0
    virtual void slot01(); // vtable +0x4
    virtual Object* getClosestSlave(const Coord3D*); // vtable +0x8

};

class Object {
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
    virtual Drawable* getDrawable() const; // vtable +0x28

 char pad04[0x34]; Coord3D m_position; char pad44[0x30]; unsigned m_id;
 char pad78[0x19c]; Object* m_containedBy;
 unsigned getID() const { return m_id; }
 const Coord3D* getPosition() const { return &m_position; }
 bool isKindOf(int k) const { return ((const Thing*)this)->isKindOf((KindOfType)k); }
 bool isLocallyControlled() const;
 bool rva001C9C10() const;
 int rva001C77B0(int,const Object*,int) const;
 int rva001BE310(int,const Object*,const Coord3D*,int) const;
 SpawnBehaviorInterface* getSpawnBehaviorInterface() const;

};

class Drawable { public: char pad00[0xfc]; Object* m_object; Object* getObject() const { return m_object; } const Coord3D* getPosition() const; };
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
enum NameKeyType { NAMEKEY_NONE };
class NameKeyGenerator { public: NameKeyType nameToKey(const AsciiString&); };
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

class MessageStream {
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
    virtual GameMessage* appendMessage(GameMessage::Type); // vtable +0x34

};

class GameClient {
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
    virtual Drawable* findDrawableByID(unsigned); // vtable +0x2C
    virtual Drawable* firstDrawable(); // vtable +0x30

};

class View {
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
    virtual Drawable* pickDrawable(const ICoord2D*,bool,int); // vtable +0x24
    virtual void slot0A(); // vtable +0x28
    virtual void slot0B(); // vtable +0x2C
    virtual void slot0C(); // vtable +0x30
    virtual void slot0D(); // vtable +0x34
    virtual void slot0E(); // vtable +0x38
    virtual void slot0F(); // vtable +0x3C
    virtual void slot10(); // vtable +0x40
    virtual void slot11(); // vtable +0x44
    virtual void slot12(); // vtable +0x48
    virtual void slot13(); // vtable +0x4C
    virtual void slot14(); // vtable +0x50
    virtual void lookAt(const Coord3D*); // vtable +0x54
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
    virtual void slot57(); // vtable +0x15C
    virtual void slot58(); // vtable +0x160
    virtual void screenToTerrain(const ICoord2D*,Coord3D*,bool); // vtable +0x164

};

class WindowLayout {
public:
    virtual void slot00(); // vtable +0x0
    virtual void slot01(); // vtable +0x4
    virtual void slot02(); // vtable +0x8
    virtual void slot03(); // vtable +0xC
    virtual void hide(bool); // vtable +0x10
 char pad04[0x10]; bool m_hidden;
};

class Shell { public: char pad00[0x58]; bool m_active; WindowLayout* top(); };
class GameWindowManager {
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
    virtual void slot2E(); // vtable +0xB8
    virtual void slot2F(); // vtable +0xBC
    virtual void slot30(); // vtable +0xC0
    virtual void slot31(); // vtable +0xC4
    virtual void slot32(); // vtable +0xC8
    virtual void slot33(); // vtable +0xCC
    virtual void slot34(); // vtable +0xD0
    virtual void slot35(); // vtable +0xD4
    virtual void slot36(); // vtable +0xD8
    virtual GameWindow* winGetWindowFromId(GameWindow*,int); // vtable +0xDC

};

class GameInfo {
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
    virtual bool isMultiPlayer() const; // vtable +0x2C

};

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

class Display {
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
    virtual void takeScreenShot(); // vtable +0x124

};

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
void pickAndPlayUnitVoiceResponse(const DrawableList*,GameMessage::Type,PickAndPlayInfo* = 0);

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

struct HeroHolder { Object* hero; Object* previous; };
static Object* iNeedAHero(Object* previous)
{
 Player* localPlayer=ThePlayerList->getLocalPlayer();
 if(!localPlayer) return 0;
 HeroHolder holder; holder.hero=0; holder.previous=previous;
 localPlayer->iterateObjects(rva005A9B00,&holder);
 if(!holder.hero && previous) { holder.previous=0; localPlayer->iterateObjects(rva005A9B00,&holder); }
 return holder.hero;
}

static __declspec(noinline) int canObjectForceAttack(Object* obj,const Object* victim,const Coord3D* pos)
{
 if(!obj->rva001C9C10()) return 0;
 if(victim) {
  int result=obj->rva001C77B0(1,victim,0);
  if(result!=3 && result!=2 && obj->isKindOf(0x53)) {
   SpawnBehaviorInterface* spawn=obj->getSpawnBehaviorInterface();
   if(spawn) { Object* slave=spawn->getClosestSlave(victim->getPosition()); if(slave) result=slave->rva001C77B0(1,victim,0); }
  }
  return result;
 }
 if(pos) {
  if(obj->isKindOf(2) || obj->isKindOf(0x53)) {
   SpawnBehaviorInterface* spawn=obj->getSpawnBehaviorInterface();
   if(spawn) spawn->getClosestSlave(pos);
  }
  return obj->rva001BE310(0,0,pos,0);
 }
 return 0;
}
static __declspec(noinline) int canAnyForceAttack(const DrawableList* allSelected,const Object* victim,const Coord3D* pos)
{
 for(DrawableList::const_iterator it=allSelected->begin();it!=allSelected->end();++it) {
  Drawable* draw=*it; if(!draw) continue;
  Object* obj=draw->getObject(); if(!obj) continue;
  return canObjectForceAttack(obj,victim,pos);
 }
 return 0;
}

GameMessageDisposition CommandTranslator::translateGameMessage(const GameMessage* msg)
{
 InGameUI* initialUI=TheInGameUI;
 GameMessage::Type t=msg->getType();
 GameMessageDisposition disp=KEEP_MESSAGE;
 if(t!=0x6d && t!=0x1d && t!=0x7d9 && t!=0x7ea && t!=0x45e &&
    !initialUI->getInputEnabled()) {
  bool system=false;
  switch(t) { case 0x3eb: case 0x446: case 0x449: system=true; break; }
  if(!system) return DESTROY_MESSAGE;
 }
 switch(t) {
 case 0x59:
  initialUI->selectUnitsMatchingCurrentSelection(); disp=DESTROY_MESSAGE; break;
 case 0x60: {
  if(!TheGameClient->firstDrawable()) break;
  Object* previous=0;
  if(TheInGameUI->getSelectCount()>0) {
   Drawable* selected=TheInGameUI->getFirstSelectedDrawable();
   if(selected) {
    Object* object=selected->getObject();
    if(object && object->isKindOf(0x59)) previous=object;
   }
  }
  Object* hero=iNeedAHero(previous);
  if(!hero) break;
  if(hero->m_containedBy) hero=hero->m_containedBy;
  Drawable* heroDraw=hero->getDrawable();
  if(!heroDraw) break;
  TheInGameUI->deselectAllDrawables();
  GameMessage* teamMsg=TheMessageStream->appendMessage(GameMessage::MSG_CREATE_SELECTED_GROUP);
  teamMsg->appendBooleanArgument(true);
  teamMsg->appendObjectIDArgument(hero->getID());
  TheInGameUI->selectDrawable(heroDraw);
  TheTacticalView->lookAt(heroDraw->getPosition());
  disp=DESTROY_MESSAGE;
  break;
 }
 case 0x5e: {
  Player* localPlayer=ThePlayerList->getLocalPlayer();
  if(localPlayer) {
   Object* obj=localPlayer->rva000D4660(true,0);
   if(obj) TheTacticalView->lookAt(obj->getPosition());
  }
  disp=DESTROY_MESSAGE; break;
 }
 case 0x5f: {
  Coord3D lastEvent;
  if(TheRadar->rva00107140(&lastEvent)) TheTacticalView->lookAt(&lastEvent);
  disp=DESTROY_MESSAGE; break;
 }
 case 0x61:
  initialUI->selectAllUnitsByType(0,ThePlayerList->getLocalPlayer()); disp=DESTROY_MESSAGE; break;
 case 0x62:
  TheMessageStream->appendMessage((GameMessage::Type)0x435); disp=DESTROY_MESSAGE; break;
 case 0x63:
  TheMessageStream->appendMessage((GameMessage::Type)0x434); disp=DESTROY_MESSAGE; break;
 case 0x65:
  TheMessageStream->appendMessage((GameMessage::Type)0x448); disp=DESTROY_MESSAGE; break;
 case 0x64: disp=DESTROY_MESSAGE; break;
 case 0x66: disp=DESTROY_MESSAGE; break;
 case 0x67: disp=DESTROY_MESSAGE; break;
 case 0x6a: {
  GameLogic* logic=TheGameLogic;
  if(logic->isInMultiplayerGame() && !logic->isInReplayGame()) {
   Player* localPlayer=ThePlayerList->getLocalPlayer();
   if(localPlayer && localPlayer->isPlayerActive() || !TheGlobalData->m_netMinPlayers) rva00511CC0(0);
  }
  disp=DESTROY_MESSAGE; break;
 }
 case 0x6b: {
  GameLogic* logic=TheGameLogic;
  if(logic->isInMultiplayerGame() && !logic->isInReplayGame()) {
   Player* localPlayer=ThePlayerList->getLocalPlayer();
   if(localPlayer && localPlayer->isPlayerActive() || !TheGlobalData->m_netMinPlayers) rva00511CC0(1);
  }
  disp=DESTROY_MESSAGE; break;
 }
 case 0x69:
  if(g_va012F71B4) { if(!g_va012F4988) rva00511CC0(3); else HideInGameChat(); }
  disp=DESTROY_MESSAGE; break;
 case 0x6c:
  if(TheGameLogic->rva000652A0() && g_va012F3330->test()) rva0052B2A0();
  disp=DESTROY_MESSAGE; break;
 case 0x8e: {
  GameLogic* logic=TheGameLogic;
  if(logic->isInMultiplayerGame() && !logic->isInReplayGame() &&
    ThePlayerList->getLocalPlayer()->isPlayerActive() &&
    (TheGlobalData->m_netMinPlayers==0 || TheGameInfo->isMultiPlayer())) {
   int count;
   const ThingTemplate* thing=TheThingFactory->findTemplate(ThePlayerList->getLocalPlayer()->getPlayerTemplate()->getBeaconTemplate());
   ThePlayerList->getLocalPlayer()->countObjectsByThingTemplate(1,&thing,false,&count,true);
   if(count<TheMultiplayerSettings->getMaxBeaconsPerPlayer()) {
    const CommandButton* commandButton=TheControlBar->findCommandButton("Command_PlaceBeacon");
    TheInGameUI->setGUICommand(commandButton);
   }
  }
  disp=DESTROY_MESSAGE; break;
 }
 case 0x8f: {
  GameLogic* logic=TheGameLogic;
  if(logic->isInMultiplayerGame() && !logic->isInReplayGame())
   TheMessageStream->appendMessage((GameMessage::Type)0x444);
  disp=DESTROY_MESSAGE; break;
 }
 case 0x6d: {
  Rva004891C0* current=g_va012F3330;
  if(current && !current->test()) current->field4d=true;
  else rva00569D80();
  disp=DESTROY_MESSAGE; break;
 }
 case 0x6e: {
  if(TheGlobalData) {
   static bool isLowDetails=false;
   static bool oldShadowVolumesValue=true,oldLightMapValue=true,oldCloudMap=true,oldBehindBuildingMarkers=true;
   static int oldMaxParticleCount=0;
   if(isLowDetails) {
    TheGlobalData->m_useShadowVolumes=oldShadowVolumesValue;
    TheGlobalData->m_useLightMap=oldLightMapValue;
    TheGlobalData->m_useCloudMap=oldCloudMap;
    TheGlobalData->m_maxParticleCount=oldMaxParticleCount;
    TheGameLogic->m_showBehindBuildingMarkers=oldBehindBuildingMarkers;
    if(TheInGameUI) TheInGameUI->message("GUI:ReturnGraphicsToPreviousSettings");
   } else {
    oldShadowVolumesValue=TheGlobalData->m_useShadowVolumes;
    TheGlobalData->m_useShadowVolumes=false;
    oldLightMapValue=TheGlobalData->m_useLightMap;
    TheGlobalData->m_useLightMap=false;
    oldCloudMap=TheGlobalData->m_useCloudMap;
    TheGlobalData->m_useCloudMap=false;
    oldBehindBuildingMarkers=TheGameLogic->m_showBehindBuildingMarkers;
    TheGameLogic->m_showBehindBuildingMarkers=false;
    oldMaxParticleCount=TheGlobalData->m_maxParticleCount;
    TheGlobalData->m_maxParticleCount=1000;
    if(TheInGameUI) TheInGameUI->message("GUI:DetailsSetToLowest");
   }
  }
  disp=DESTROY_MESSAGE; break;
 }
 case 0x6f: {
  if(TheShell->m_active) {
   WindowLayout* win=TheShell->top();
   if(win) win->hide(!win->m_hidden);
  } else if(!(TheRecorder && TheRecorder->getMode()==1)) {
   bool hide=false;
   if(TheWindowManager) {
    int id=TheNameKeyGenerator->nameToKey(AsciiString("ControlBar.wnd:ControlBarParent"));
    GameWindow* window=TheWindowManager->winGetWindowFromId(0,id);
    if(window) hide=!window->winIsHidden();
   }
   Rva004C1040(1);
  }
  disp=DESTROY_MESSAGE; break;
 }
 case 0x74: initialUI->m_forceMoveMode=true; break;
 case 0x75: initialUI->m_forceMoveMode=false; break;
 case 0x76: initialUI->m_waypointMode=true; break;
 case 0x78: initialUI->m_preferSelectionMode=true; break;
 case 0x79: initialUI->m_preferSelectionMode=false; break;
 case 0x77: initialUI->m_waypointMode=false; break;
 case 0x7d: initialUI->m_cameraRotateLeft=true; break;
 case 0x7e: initialUI->m_cameraRotateLeft=false; break;
 case 0x7f: initialUI->m_cameraRotateRight=true; break;
 case 0x80: initialUI->m_cameraRotateRight=false; break;
 case 0x81: initialUI->m_cameraZoomIn=true; break;
 case 0x82: initialUI->m_cameraZoomIn=false; break;
 case 0x83: initialUI->m_cameraZoomOut=true; break;
 case 0x84: initialUI->m_cameraZoomOut=false; break;
 case 0x85: initialUI->rva0043CEC0(); break;
 case 0x86: initialUI->field12b8=true; break;
 case 0x87: initialUI->field12b8=false; break;
 case 0x88: initialUI->field12b9=true; break;
 case 0x89: initialUI->field12b9=false; break;
 case 0x8a: initialUI->field12ba=true; break;
 case 0x8b: initialUI->field12ba=false; break;
 case 0x8c: initialUI->field12bb=true; break;
 case 0x8d: initialUI->field12bb=false; break;
 case 0x7b:
  if(TheGameLogic->isInMultiplayerGame()) {
   TheAudio->addAudioEvent((const AudioEventRTS*)(TheAudio->getMiscAudio()+0x310));
   disp=DESTROY_MESSAGE;
   TheMessageStream->appendMessage((GameMessage::Type)0x437);
  }
  break;
 case 0x7a:
  if(TheDisplay) TheDisplay->takeScreenShot();
  disp=DESTROY_MESSAGE; break;
 case 0x3e9: case 0x3f7: case 0x3f8: case 0x3f9: case 0x3fa: case 0x3fb:
 case 0x3fc: case 0x3fd: case 0x3fe: case 0x3ff: case 0x400: case 0x460: {
  DrawableList listOfUnits=*initialUI->getAllSelectedDrawables();
  for(DrawableList::iterator it=listOfUnits.begin();it!=listOfUnits.end();) {
   Drawable* draw=*it;
   if(draw->getObject() && draw->getObject()->isLocallyControlled()) { ++it; continue; }
   else it=listOfUnits.erase(it);
  }
  if(!listOfUnits.empty()) pickAndPlayUnitVoiceResponse(&listOfUnits,GameMessage::MSG_CREATE_SELECTED_GROUP);
  m_teamExists=true;
  break;
 }
 case 0x3ea: case 0x401: case 0x402: case 0x403: case 0x404: case 0x405:
 case 0x406: case 0x407: case 0x408: case 0x409: case 0x40a:
  m_teamExists=true; break;
 case 0x3eb: m_teamExists=false; break;
 case 0x94: {
  bool selected=initialUI->getSelectCount()>0;
  if(!selected) {
   const CommandButton* command=TheInGameUI->getGUICommand();
   if(command) {
    int commandType=command->getCommandType();
    if(commandType==0x1f || commandType==0x24) selected=true;
   }
  }
  if(selected) {
  Drawable* draw=TheGameClient->findDrawableByID(msg->getArgument(0)->drawableID);
  if(draw) {
   if(TheInGameUI->isInForceAttackMode()) evaluateForceAttack(draw,draw->getPosition(),DO_HINT);
   else evaluateContextCommand(draw,draw->getPosition(),DO_HINT);
  }
  }
  break;
 }
 case 0x95: {
  Coord3D position=msg->getArgument(0)->location;
  if(TheInGameUI->isInForceAttackMode()) {
   const DrawableList* selected=TheInGameUI->getAllSelectedDrawables();
   int attack=canAnyForceAttack(selected,0,&position);
   if(attack==3 || attack==2) TheMessageStream->appendMessage((GameMessage::Type)0x9c);
   else if(attack==1) TheMessageStream->appendMessage((GameMessage::Type)0x9a);
  } else evaluateContextCommand(0,&position,DO_HINT);
  break;
 }
 case 0xe:
  m_mouseRightDragAnchor=msg->getArgument(0)->pixel;
  m_mouseRightDown=msg->getArgument(2)->integer;
  field2c=false;
  break;
 case 3: {
  ICoord2D current=msg->getArgument(0)->pixel;
  if(TheMouse->rva005A49E0(&m_mouseRightDragAnchor,&current)) field2c=true;
  break;
 }
 case 0x10:
  m_mouseRightDragLift=msg->getArgument(0)->pixel;
  m_mouseRightUp=msg->getArgument(2)->integer;
  break;
 case 6: field28=msg->getArgument(2)->integer; break;
 case 4: field24=msg->getArgument(2)->integer; break;
 case 0x1b: case 0x1c: {
  bool isPoint=!field2c;
  if(m_mouseRightUp-m_mouseRightDown<TheMouse->m_clickTime) isPoint=true;
  if(TheGlobalData->m_useAlternateMouse && isPoint) {
   if(!TheTacticalView) break;
   Coord3D pos;
   TheTacticalView->screenToTerrain(&msg->getArgument(0)->pixel,&pos,false);
   const CommandButton* command=TheInGameUI->getGUICommand();
   int commandType=command?command->getCommandType():0;
   bool controllable=TheInGameUI->rva0043EC00();
   if(!controllable && command && (commandType==0x1f || commandType==0x24)) controllable=true;
   if(controllable) {
    int pickType=Rva00459060(TheInGameUI->isInForceAttackMode());
    Drawable* draw=TheTacticalView->pickDrawable(&msg->getArgument(0)->pixelRegion.lo,TheInGameUI->isInForceAttackMode(),pickType);
    if(TheInGameUI->isInForceAttackMode()) evaluateForceAttack(draw,&pos,DO_COMMAND);
    else {
     int result=evaluateContextCommand(draw,&pos,DO_COMMAND);
     if(commandType==0x17 && result==0x97) TheInGameUI->setGUICommand(0);
    }
    disp=DESTROY_MESSAGE;
   }
  }
  break;
 }
 case 0x17: {
  bool isPoint=((unsigned)msg->getArgument(0)->pixelRegion.height()<=TheMouse->m_dragTolerance &&
                (unsigned)msg->getArgument(0)->pixelRegion.width()<=TheMouse->m_dragTolerance);
  if(field28-field24<TheMouse->m_clickTime) isPoint=true;
  if(!TheTacticalView) break;
  if(TheGlobalData->m_useAlternateMouse) break;
  Coord3D pos;
  TheTacticalView->screenToTerrain(&msg->getArgument(0)->pixel,&pos,false);
  const CommandButton* command=TheInGameUI->getGUICommand();
  int commandType=command?command->getCommandType():0;
  bool isFiringGUICommand=command && command->isContextCommand();
  if(TheGlobalData->m_useAlternateMouse && !isFiringGUICommand) break;
  bool controllable=TheInGameUI->rva0043EC00();
   if(!controllable && command && (commandType==0x1f || commandType==0x24)) controllable=true;
  if(isPoint && controllable) {
   int pickType=Rva00459060(TheInGameUI->isInForceAttackMode());
   Drawable* draw=TheTacticalView->pickDrawable(&msg->getArgument(0)->pixelRegion.lo,TheInGameUI->isInForceAttackMode(),pickType);
   if(TheInGameUI->isInForceAttackMode()) evaluateForceAttack(draw,&pos,DO_COMMAND);
   else {
    int result=evaluateContextCommand(draw,&pos,DO_COMMAND);
    if(commandType==0x17 && result==0x97) TheInGameUI->setGUICommand(0);
   }
   disp=DESTROY_MESSAGE;
  }
  break;
 }
 case 0x18: rva005A9C90(msg); break;
 case 0x92:
  if(TheGameLogic->isInReplayGame()) {
   if(TheGlobalData) {
    TheGlobalData->m_TiVOFastMode=1-TheGlobalData->m_TiVOFastMode;
    TheInGameUI->message(UnicodeString(L">> %s"),TheGlobalData->m_TiVOFastMode?L"ON":L"OFF");
    if(TheGlobalData->m_TiVOFastMode) {
     AudioEventRTS event("UIBaboop",0);
     TheAudio->addAudioEvent(&event);
    } else {
     AudioEventRTS event("UIBomp",0);
     TheAudio->addAudioEvent(&event);
    }
   }
   disp=DESTROY_MESSAGE;
  }
  break;
 case 0x90:
  if(!g_va012F1028 || !g_va012F1028->test()) if(TheControlBar) TheControlBar->togglePurchaseScience();
  disp=DESTROY_MESSAGE; break;
 }
 return disp;
}
