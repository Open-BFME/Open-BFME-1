// ?evaluateContextCommand@CommandTranslator@@AAE?AW4CommandEvaluateType@@PAVDrawable@@PBVCoord3D@@W42@@Z
// partial score=0.8894457547169812 date=2026-09-23
// cl: /O2 /Ob2 /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/stringbaseunicode
// stlport
// Ported from GeneralsMD/Code/GameEngine/Source/GameClient/MessageStream/CommandXlat.cpp.
// Copyright 2025 Electronic Arts Inc.; GPL-3.0-or-later, as in the vendored source.
// BFME layout/call witnesses: build/gap_005ade0d/LAYOUTS.md and region_{a,b}.asm.
// Banked evaluator draft: RVA 005ADE90, retail 6784 B; NOT a matched claim.
// e295: ours 6776 B, 734 differing bytes; measured score 0.8894457547169812.
// Frame 0x68. See e295_shape.txt and EVALUATE_BEST_CALL_AUDIT.md for remaining work.
// The exact translateGameMessage body remains in the real Code/CommandXlat.cpp.
// Merge its implementation with this draft only when resuming the scoped gate.
#include <list>
#include "ascii_string.h"
#include "Common/UnicodeString.h"
inline AsciiString::~AsciiString() { ((StringBase<char>*)this)->releaseBuffer(); }
inline UnicodeString::~UnicodeString() { ((StringBase<wchar_t>*)this)->releaseBuffer(); }
class Coord3D { public: float x,y,z; void set(const Coord3D* p) { x=p->x;y=p->y;z=p->z; } };
struct ICoord2D { int x,y; };
struct IRegion2D { ICoord2D lo,hi; int width() const { return hi.x-lo.x; } int height() const { return hi.y-lo.y; } };
class Drawable; class Object; class Player; class ThingTemplate; class CommandButton;
class PickAndPlayInfo;
typedef _STL::list<Drawable*> DrawableList;
union GameMessageArgumentType { int integer; unsigned drawableID; ICoord2D pixel; IRegion2D pixelRegion; Coord3D location; };
enum DrawableID { DRAWABLEID_NONE };
enum ObjectID { INVALID_ID };
class Team;
enum Relationship { ENEMIES, NEUTRAL, ALLIES };
class KindOfMask { public: unsigned bits[6]; KindOfMask() { for(int i=0;i<6;++i) bits[i]=0; } void set(int i) { bits[i/32]|=1u<<(i%32); } };
class Overridable { public: void* opaque00; Overridable* m_override; const Overridable* getFinalOverride() const { if(m_override) return m_override->getFinalOverride(); return this; } Overridable* friend_getFinalOverride() { if(m_override) return m_override->friend_getFinalOverride(); return this; } const Overridable* friend_getFinalOverride() const { if(m_override) return m_override->friend_getFinalOverride(); return this; } };
template<class T> class OVERRIDE { public: const T* m_overridable;
 const T* operator*() const { if(!m_overridable) return 0; return (T*)m_overridable->getFinalOverride(); }
 operator const T*() const { return operator*(); }
};
class ThingTemplate : public Overridable { public: char pad08[0xc0]; unsigned m_kindOf[6]; };
enum SpecialPowerType { SPECIAL_INVALID };
class SpecialPowerTemplate : public Overridable { public: char pad08[8]; unsigned m_id; SpecialPowerType m_type;
 __forceinline unsigned getID() const { return getFO()->m_id; }
 SpecialPowerType getSpecialPowerType() const { return getFO()->m_type; }
 __forceinline SpecialPowerType getVoicePowerType() const { return getFO()->m_type; }
 __forceinline const SpecialPowerTemplate* getFO() const { return (const SpecialPowerTemplate*)friend_getFinalOverride(); }
};
class CommandSet { public: const CommandButton* getCommandButton(int) const; };
class PickAndPlayInfo { public: PickAndPlayInfo(); bool m_air; char pad01[3]; Drawable* m_drawTarget; int* m_weaponSlot; int m_specialPowerType; Coord3D m_position; unsigned field1c; };

class GameMessage { public:
 enum Type { MSG_INVALID=0, MSG_CREATE_SELECTED_GROUP=0x3e9 };
 char pad00[0x10]; Type m_type;
 Type getType() const { return m_type; }
 const GameMessageArgumentType* getArgument(int) const;
 void appendIntegerArgument(int); void appendLocationArgument(const Coord3D&);
 void appendBooleanArgument(bool); void appendObjectIDArgument(unsigned);
};
enum GameMessageDisposition { KEEP_MESSAGE, DESTROY_MESSAGE };
enum CanAttackResult { ATTACKRESULT_NONE, ATTACKRESULT_INVALID, ATTACKRESULT_MOVING, ATTACKRESULT_POSSIBLE };
enum CommandEvaluateType { DO_COMMAND, DO_HINT, DO_EVALUATE };
class AudioEventRTS { public: AudioEventRTS(const AsciiString&,int); ~AudioEventRTS(); void* m_vftable; char opaque04[0x6c]; };
class CommandButton { public: char pad00[0x10]; int m_command; int opaque14; unsigned m_options; char pad1c[0x18]; SpecialPowerTemplate* m_specialPower;
 unsigned getOptions() const { return m_options; }
 const SpecialPowerTemplate* getSpecialPowerTemplate() const { return m_specialPower; }

 __forceinline bool rejectsRelationship(Relationship relationship) const {
  switch(relationship) {
  case ALLIES: if(!(getOptions()&4)) return true;break;
  case ENEMIES: if(!(getOptions()&1)) return true;break;
  case NEUTRAL: if(!(getOptions()&2)) return true;break;
  }
  return false;
 }
 bool isContextCommand() const; int getCommandType() const { return m_command; } };
enum KindOfType { KINDOF_PLACEHOLDER };
class Thing { public: bool isKindOf(KindOfType) const; bool rva00132AE0(const KindOfMask&) const; };

class SpawnBehaviorInterface {
public:
    virtual void slot00(); // vtable +0x0
    virtual void slot01(); // vtable +0x4
    virtual Object* getClosestSlave(const Coord3D*); // vtable +0x8

};

class BodyModuleInterface { public:
 virtual void slot00(); // +0x0
 virtual void slot01(); // +0x4
 virtual void slot02(); // +0x8
 virtual void slot03(); // +0xC
 virtual void slot04(); // +0x10
 virtual void slot05(); // +0x14
 virtual void slot06(); // +0x18
 virtual void slot07(); // +0x1C
 virtual int rvaSlot20() const; // +0x20

};
class AIUpdateInterface { public:
 virtual void slot00(); // +0x0
 virtual void slot01(); // +0x4
 virtual void slot02(); // +0x8
 virtual void slot03(); // +0xC
 virtual void slot04(); // +0x10
 virtual void slot05(); // +0x14
 virtual void slot06(); // +0x18
 virtual void slot07(); // +0x1C
 virtual void slot08(); // +0x20
 virtual void slot09(); // +0x24
 virtual void slot0A(); // +0x28
 virtual void slot0B(); // +0x2C
 virtual void slot0C(); // +0x30
 virtual void slot0D(); // +0x34
 virtual void slot0E(); // +0x38
 virtual void slot0F(); // +0x3C
 virtual void slot10(); // +0x40
 virtual void slot11(); // +0x44
 virtual void slot12(); // +0x48
 virtual void slot13(); // +0x4C
 virtual void slot14(); // +0x50
 virtual void slot15(); // +0x54
 virtual void slot16(); // +0x58
 virtual void slot17(); // +0x5C
 virtual void slot18(); // +0x60
 virtual void slot19(); // +0x64
 virtual void slot1A(); // +0x68
 virtual void slot1B(); // +0x6C
 virtual void slot1C(); // +0x70
 virtual void slot1D(); // +0x74
 virtual void slot1E(); // +0x78
 virtual void slot1F(); // +0x7C
 virtual void slot20(); // +0x80
 virtual void slot21(); // +0x84
 virtual void slot22(); // +0x88
 virtual void slot23(); // +0x8C
 virtual void slot24(); // +0x90
 virtual void slot25(); // +0x94
 virtual void slot26(); // +0x98
 virtual void slot27(); // +0x9C
 virtual void slot28(); // +0xA0
 virtual void slot29(); // +0xA4
 virtual void slot2A(); // +0xA8
 virtual void slot2B(); // +0xAC
 virtual void slot2C(); // +0xB0
 virtual void slot2D(); // +0xB4
 virtual void slot2E(); // +0xB8
 virtual void slot2F(); // +0xBC
 virtual void slot30(); // +0xC0
 virtual void slot31(); // +0xC4
 virtual void slot32(); // +0xC8
 virtual void slot33(); // +0xCC
 virtual void slot34(); // +0xD0
 virtual void slot35(); // +0xD4
 virtual void slot36(); // +0xD8
 virtual void slot37(); // +0xDC
 virtual void slot38(); // +0xE0
 virtual void slot39(); // +0xE4
 virtual void slot3A(); // +0xE8
 virtual void slot3B(); // +0xEC
 virtual void slot3C(); // +0xF0
 virtual void slot3D(); // +0xF4
 virtual void slot3E(); // +0xF8
 virtual void slot3F(); // +0xFC
 virtual void slot40(); // +0x100
 virtual void slot41(); // +0x104
 virtual void slot42(); // +0x108
 virtual void slot43(); // +0x10C
 virtual void slot44(); // +0x110
 virtual void slot45(); // +0x114
 virtual void slot46(); // +0x118
 virtual void slot47(); // +0x11C
 virtual void slot48(); // +0x120
 virtual void slot49(); // +0x124
 virtual void slot4A(); // +0x128
 virtual void slot4B(); // +0x12C
 virtual bool rvaSlot130() const; // +0x130
 bool isQuickPathAvailable(const Coord3D*) const;
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

 OVERRIDE<ThingTemplate> m_template; char pad08[0x30]; Coord3D m_position; char pad44[0x30]; ObjectID m_id;
 char pad78[0x188]; BodyModuleInterface* m_body; AIUpdateInterface* m_ai; char pad208[0xc]; Object* m_containedBy;
 char pad218[0xc]; char field224[0x18]; Team* m_team; char pad240[0x105]; bool m_masked;
 const ThingTemplate* getTemplate() const { return m_template; }
 bool isAnyKindOf(const KindOfMask& mask) const { return ((const Thing*)this)->rva00132AE0(mask); }
 BodyModuleInterface* getBodyModule() const { return m_body; } AIUpdateInterface* getAI() const { return m_ai; } Team* getTeam() const { return m_team; } bool isMasked() const { return m_masked; }
 bool isMobile() const; bool isSalvageCrate() const;
 const AsciiString& getCommandSetString() const;
 ObjectID getID() const { return m_id; }
 const Coord3D* getPosition() const { return &m_position; }
 bool isKindOf(int k) const { return ((const Thing*)this)->isKindOf((KindOfType)k); }
 bool isLocallyControlled() const;
 bool rva001C9C10() const;
 int rva001C77B0(int,const Object*,int) const;
 int rva001BE310(int,const Object*,const Coord3D*,int) const;
 SpawnBehaviorInterface* getSpawnBehaviorInterface() const;

};

class Drawable { public: char pad00[0xfc]; Object* m_object; Object* getObject() const { return m_object; } DrawableID getID() const; const Coord3D* getPosition() const; };
class PlayerTemplate { public: char pad00[0xe4]; AsciiString m_beaconTemplate; const AsciiString& getBeaconTemplate() const { return m_beaconTemplate; } };
class Player { public: char pad00[4]; PlayerTemplate* m_playerTemplate; char pad08[0x1c]; int m_playerIndex;
 const PlayerTemplate* getPlayerTemplate() const { return m_playerTemplate; }
 int getPlayerIndex() const { return m_playerIndex; } bool isPlayerActive() const; Relationship getRelationship(const Team*) const; Object* rva000D4400(); Object* rva000D4490();
 Object* rva000D4660(bool,Object**) const;
 int iterateObjects(int (*)(Object*,void*),void*) const;
 void countObjectsByThingTemplate(int,const ThingTemplate* const*,bool,int*,bool) const;
};
class PlayerList { public: char pad00[0xc]; Player* m_localPlayer; Player* getLocalPlayer() const { return m_localPlayer; } };
class ControlBar { public: const CommandButton* findCommandButton(const AsciiString&); void togglePurchaseScience(); const CommandSet* findCommandSet(const AsciiString&); };
class GameLogic { public: char pad00[0x91]; bool m_showBehindBuildingMarkers; char pad92[0x7a]; int m_mode;
 bool isInMultiplayerGame(); bool rva000652A0() const; bool isInReplayGame() const { return m_mode==3; }
};
class GlobalData { public:
 char pad00[0x38]; bool m_useCloudMap; char pad39[0xb]; bool m_useLightMap; char pad45[0x1b]; bool m_useAlternateMouse;
 char pad61[3]; bool m_useShadowVolumes; char pad65[0xaa7]; int m_netMinPlayers; char padb10[0x7c]; int m_maxParticleCount;
 char padb90[0xc9]; bool m_TiVOFastMode;
};
class Mouse { public:
 virtual void slot00(); // +0x0
 virtual void slot01(); // +0x4
 virtual void slot02(); // +0x8
 virtual void slot03(); // +0xC
 virtual void slot04(); // +0x10
 virtual void slot05(); // +0x14
 virtual void slot06(); // +0x18
 virtual void slot07(); // +0x1C
 virtual void slot08(); // +0x20
 virtual void slot09(); // +0x24
 virtual void slot0A(); // +0x28
 virtual void slot0B(); // +0x2C
 virtual void slot0C(); // +0x30
 virtual void getPosition(int*,int*); // +0x34
 char pad04[0x10e8]; unsigned m_dragTolerance; char pad10f0[4]; unsigned m_clickTime;
 bool rva005A49E0(const ICoord2D*,const ICoord2D*) const; int getCursorIndex(const AsciiString&);
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
 bool rva00447F10(Object*);
 bool canSelectedObjectsDoAction(int,const Object*,int,bool=false) const;
 bool canSelectedObjectsOverrideSpecialPowerDestination(const Coord3D*,int,int) const;
 bool canSelectedObjectsEffectivelyUseWeapon(const CommandButton*,const Object*,const Coord3D*,int) const;
 bool canSelectedObjectsDoSpecialPower(const CommandButton*,const Object*,const Coord3D*,int,unsigned,Object*) const;
 bool rva0043B790(const CommandButton*,const Object*,const Coord3D*,int,unsigned,Object*) const;
 CanAttackResult getCanSelectedObjectsAttack(int,const Object*,int,bool) const;
 bool isInWaypointMode() const { return m_waypointMode; }
 bool isInForceMoveToMode() const { return m_forceMoveMode; }
 bool isInPreferSelectionMode() const { return m_preferSelectionMode; }


};

class TerrainLogic { public: int getLayerForDestination(Object*,const Coord3D*); };
class PartitionManager { public: int getShroudStatusForPlayer(int,const Coord3D*) const; };
class Pathfinder { public: bool slowDoesPathExist(Object*,const Coord3D*,const Coord3D*,unsigned); };
class Keyboard { public: bool isShift(); };
class Rva0010B500 { public: class Rva0010B500Result* find(const int*); };
class Rva0010B500Result { public: char pad00[0x118]; AsciiString field118; };
class Rva000C4740 { public: int evaluate(const Object*); };
extern Rva000C4740* g_va012ED700;
extern Keyboard* TheKeyboard;
extern TerrainLogic* TheTerrainLogic;
extern PartitionManager* ThePartitionManager;
class AI { public: char pad00[0xc]; Pathfinder* m_pathfinder; Pathfinder* getPathfinder() const { return m_pathfinder; } };
extern AI* TheAI;
extern Rva0010B500* g_va012EF188;
bool rva001A40C0(Coord3D*);

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
    virtual bool screenToTerrain(const ICoord2D*,Coord3D*,bool); // vtable +0x164

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
 int issueMoveToLocationCommand(const Coord3D*,Drawable*,CommandEvaluateType);
 int issueAttackCommand(Drawable*,const Coord3D*,CommandEvaluateType,int=0);
 int issueSpecialPowerCommand(const CommandButton*,CommandEvaluateType,Drawable*,const Coord3D*,Object*);
 int rva005AD330(const CommandButton*,CommandEvaluateType,Drawable*,const Coord3D*);
 int rva005AD4C0(const CommandButton*,CommandEvaluateType,Drawable*,const Coord3D*);
 int rva005AD660(const CommandButton*,CommandEvaluateType,Drawable*,const Coord3D*);
 int createEnterMessage(Drawable*,CommandEvaluateType);
 int createEvacuateMessage(Drawable*,CommandEvaluateType);
 int createDockMessage(Drawable*,CommandEvaluateType);
 const CommandButton* rva005A7E20(unsigned) const;

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


__forceinline bool queueRallyPoint(const Drawable* target)
{
 return TheKeyboard->isShift() && !target;
}







// RVA 005A8850: ZH canSelectionSalvage; private ECX target convention.
static bool canSelectionSalvage(const Object* targetObj)
{
 if(!targetObj) return false;
 if(!targetObj->isSalvageCrate()) return false;
 const DrawableList* drawList=TheInGameUI->getAllSelectedDrawables();
 for(DrawableList::const_iterator cit=drawList->begin();cit!=drawList->end();++cit) {
  Drawable* draw=*cit;if(!draw) continue;
  Object* obj=draw->getObject();if(!obj) continue;
  if(obj->getTemplate()->m_kindOf[0]&0x80000) return true;
 }
 return false;
}


CommandEvaluateType CommandTranslator::evaluateContextCommand(Drawable* draw,const Coord3D* pos,CommandEvaluateType type)
{
 Object* obj=draw?draw->getObject():0;
 Drawable* drawableInWay=draw;
 Coord3D screenPosition;
 if(draw) {
  DrawableID id=draw->getID();
  if(id==99999999 || id==99999996 || id==99999997 || id==99999998) {
   ICoord2D mousePosition;
   TheMouse->getPosition(&mousePosition.x,&mousePosition.y);
   if(TheTacticalView->screenToTerrain(&mousePosition,&screenPosition,false)) pos=&screenPosition;
  }
 }
 if(!obj || obj->isMasked() && !obj->isKindOf(6) && !obj->isKindOf(0x60) && !obj->isKindOf(0x87) && !obj->isKindOf(0x43)) { draw=0;obj=0; }
 Object* singleSelected=0;
 if(TheInGameUI->getSelectCount()==1) {
  Drawable* first=*TheInGameUI->getAllSelectedDrawables()->begin();
  singleSelected=first?first->getObject():0;
 }
 bool onlyKind85=false,onlyMask=false,hasKind85=false,hasMask=false,hasOtherKind=false,hasOtherMask=false;
 {
 const DrawableList* selection=TheInGameUI->getAllSelectedDrawables();
 for(DrawableList::const_iterator it=selection->begin();it!=selection->end();++it) {
   Object* selected=*it?(*it)->getObject():0;
   if(selected) {
    if(selected->getTemplate()->m_kindOf[4]&0x20) hasKind85=true; else hasOtherKind=true;
    KindOfMask mask;mask.set(54);mask.set(146);
    if(selected->isAnyKindOf(mask)) hasMask=true;else hasOtherMask=true;
   }
  }
  if(hasKind85 && !hasOtherKind) onlyKind85=true;
  if(hasMask && !hasOtherMask) onlyMask=true;
  if(onlyKind85) { draw=0;obj=0; }
 }
 Object* originalObject=obj;
 // Disjoint phases witnessed at ESP+0x20; this draft is not byte exact.
 union { Drawable* originalDraw; CanAttackResult result; } targetState;
 targetState.originalDraw=draw;
 if(obj && (obj->getTemplate()->m_kindOf[1]&0x08000000) && !(obj->getTemplate()->m_kindOf[4]&0x200000) &&
    obj->getBodyModule()->rvaSlot20()!=3 && TheTerrainLogic->getLayerForDestination(0,pos)!=1 && !onlyMask) { draw=0;obj=0; }
 if(TheInGameUI->isInForceMoveToMode()) { draw=0;targetState.originalDraw=0;obj=0;originalObject=0; }
 else if(TheInGameUI->isInForceAttackMode()) drawableInWay=draw;
 GameMessage::Type msgType=(GameMessage::Type)0;
 if(obj && obj->isLocallyControlled() && TheInGameUI->isInPreferSelectionMode()) return (CommandEvaluateType)msgType;
 const CommandButton* command=TheInGameUI->getGUICommand();
 if(TheInGameUI->rva0043EC00() || command && (command->getCommandType()==0x1f || command->getCommandType()==0x24 || command->getCommandType()==0x1e)) {
  GameMessage* hintMessage;
  if(TheInGameUI->isInWaypointMode()) {
   if(type==DO_COMMAND || type==DO_EVALUATE) {
    if(TheTerrainLogic) msgType=(GameMessage::Type)(issueMoveToLocationCommand(pos,draw,type));
   } else {
    msgType=(GameMessage::Type)(0xa7);hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendLocationArgument(*pos);
   }
   return (CommandEvaluateType)msgType;
  }
  if(command && (command->isContextCommand() || command->getCommandType()==0x17 || command->getCommandType()==0x1f || command->getCommandType()==0x24 || command->getCommandType()==0xa || command->getCommandType()==0x1e)) {
   if(originalObject && (originalObject->getTemplate()->m_kindOf[0]&0x40) && !(command->getOptions()&0x10)) { draw=0;targetState.originalDraw=0;obj=0;originalObject=0; }
   if(originalObject && ((originalObject->getTemplate()->m_kindOf[3]&1) || originalObject->isKindOf(0x87)) && !(command->getOptions()&0x200000)) { draw=0;targetState.originalDraw=0;obj=0;originalObject=0; }
   if(originalObject && (command->getOptions()&7)) {
    Relationship relationship=ThePlayerList->getLocalPlayer()->getRelationship(originalObject->getTeam());
    if(command->rejectsRelationship(relationship)) { draw=0;targetState.originalDraw=0;obj=0;originalObject=0; }
   }
   bool currentlyValid=false;
   ObjectID objectID=obj?obj->getID():INVALID_ID;
   switch(command->getCommandType()) {
   case 0x1d: currentlyValid=TheInGameUI->canSelectedObjectsDoAction(0xb,obj,0);break;
   case 0x1c: currentlyValid=TheInGameUI->canSelectedObjectsDoAction(0xa,obj,0);break;
   case 0x1f: { Object* unit=ThePlayerList->getLocalPlayer()->rva000D4400(); if(unit) currentlyValid=TheInGameUI->canSelectedObjectsDoSpecialPower(command,obj,pos,0,command->getOptions(),unit);break; }
   case 0x24: { Object* unit=ThePlayerList->getLocalPlayer()->rva000D4490(); if(unit) currentlyValid=TheInGameUI->canSelectedObjectsDoSpecialPower(command,obj,pos,0,command->getOptions(),unit);break; }
   case 0x17:
    currentlyValid=TheInGameUI->canSelectedObjectsDoSpecialPower(command,originalObject,pos,0,command->getOptions(),0);
    if(currentlyValid) { objectID=originalObject?originalObject->getID():INVALID_ID;draw=targetState.originalDraw; }
    break;
   case 0x16: currentlyValid=TheInGameUI->canSelectedObjectsEffectivelyUseWeapon(command,obj,pos,0);break;
   case 0x19: currentlyValid=!obj?true:TheInGameUI->canSelectedObjectsDoAction(0xf,obj,0);break;
   case 0xa: currentlyValid=TheInGameUI->rva0043B790(command,obj,pos,0,command->getOptions(),0);break;
   case 0x27: currentlyValid=TheInGameUI->canSelectedObjectsDoAction(0x13,obj,0);break;
   case 0x2d: currentlyValid=TheInGameUI->canSelectedObjectsDoAction(0x14,obj,0);break;
   case 0x1e: { Coord3D beaconPosition;beaconPosition.set(pos);currentlyValid=rva001A40C0(&beaconPosition);break; }
   }
   if(currentlyValid) {
    if(type==DO_COMMAND || type==DO_EVALUATE) {
     Object* shortcutUnit;
     switch(command->getCommandType()) {
     case 0x1c: case 0x1d: msgType=(GameMessage::Type)(createEnterMessage(draw,type));break;
     case 0x27: msgType=(GameMessage::Type)(createEvacuateMessage(draw,type));break;
     case 0x2d: msgType=(GameMessage::Type)(createDockMessage(draw,type));break;
     case 0x1f: { shortcutUnit=ThePlayerList->getLocalPlayer()->rva000D4400();if(shortcutUnit) msgType=(GameMessage::Type)(issueSpecialPowerCommand(command,type,draw,pos,shortcutUnit));break; }
     case 0x24: { shortcutUnit=ThePlayerList->getLocalPlayer()->rva000D4490();if(shortcutUnit) msgType=(GameMessage::Type)(issueSpecialPowerCommand(command,type,draw,pos,shortcutUnit));break; }
     case 0x17: msgType=(GameMessage::Type)(issueSpecialPowerCommand(command,type,targetState.originalDraw,pos,0));break;
     case 0x16: msgType=(GameMessage::Type)(rva005AD660(command,type,draw,pos));break;
     case 0x19: msgType=(GameMessage::Type)(rva005AD330(command,type,draw,pos));break;
     case 0xa: msgType=(GameMessage::Type)(rva005AD4C0(command,type,draw,pos));break;
     }
     if(type==DO_COMMAND) TheInGameUI->setGUICommand(0);
    } else { msgType=(GameMessage::Type)(0x96);hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendObjectIDArgument(objectID); }
   } else { msgType=(GameMessage::Type)(0x97);hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendObjectIDArgument(objectID); }
  }
  else if(TheInGameUI->rva00447F10(originalObject)) {
   if(type==DO_COMMAND || type==DO_EVALUATE) {
    msgType=(GameMessage::Type)(0x411);
    if(type==DO_COMMAND) {
     const CommandButton* deploy=TheControlBar->findCommandButton(AsciiString("Command_SpecialAbilitySiegeDeploy"));
     if(deploy) {
      GameMessage* message=TheMessageStream->appendMessage((GameMessage::Type)msgType);
      message->appendIntegerArgument(deploy->getSpecialPowerTemplate()->getID());
      message->appendObjectIDArgument(originalObject->getID());
      message->appendIntegerArgument(deploy->getOptions());
      message->appendObjectIDArgument(0);
      message->appendLocationArgument(*originalObject->getPosition());
      PickAndPlayInfo info;info.m_drawTarget=originalObject->getDrawable();info.m_specialPowerType=deploy->getSpecialPowerTemplate()->getVoicePowerType();info.m_position.set(pos);
      pickAndPlayUnitVoiceResponse(TheInGameUI->getAllSelectedDrawables(),(GameMessage::Type)msgType,&info);
     }
    }
   } else { msgType=(GameMessage::Type)(0x99);hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendObjectIDArgument(originalObject->getID()); }
  }
  else if(TheInGameUI->canSelectedObjectsOverrideSpecialPowerDestination(pos,0,0)) {
   if(type==DO_COMMAND || type==DO_EVALUATE) {
    msgType=(GameMessage::Type)(0x440);
    if(type==DO_COMMAND) { GameMessage* message=TheMessageStream->appendMessage((GameMessage::Type)msgType);message->appendLocationArgument(*pos);message->appendIntegerArgument(0);message->appendObjectIDArgument(0); }
   } else { msgType=(GameMessage::Type)(0xaf);hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType); }
  }
  else if(draw && !TheInGameUI->isInForceAttackMode() && TheInGameUI->canSelectedObjectsDoAction(7,obj,0,false)) {
   if(type==DO_COMMAND || type==DO_EVALUATE) {
    msgType=(GameMessage::Type)(0x42a);
    if(type==DO_COMMAND) {
     GameMessage* message=TheMessageStream->appendMessage((GameMessage::Type)msgType);message->appendObjectIDArgument(obj->getID());
     PickAndPlayInfo info;info.m_drawTarget=draw;
     pickAndPlayUnitVoiceResponse(TheInGameUI->getAllSelectedDrawables(),(GameMessage::Type)msgType,&info);
    }
   } else { msgType=(GameMessage::Type)(0xa0);hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendObjectIDArgument(obj->getID()); }
  }
  else if(draw && !TheInGameUI->isInForceAttackMode() && TheInGameUI->canSelectedObjectsDoAction(3,obj,0,false)) {
   if(type==DO_COMMAND || type==DO_EVALUATE) {
    msgType=(GameMessage::Type)(0x42c);
    if(type==DO_COMMAND) {
     GameMessage* message=TheMessageStream->appendMessage((GameMessage::Type)msgType);message->appendObjectIDArgument(obj->getID());
     PickAndPlayInfo info;info.m_drawTarget=draw;
     pickAndPlayUnitVoiceResponse(TheInGameUI->getAllSelectedDrawables(),(GameMessage::Type)msgType,&info);
    }
   } else { msgType=(GameMessage::Type)(0xa3);hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendObjectIDArgument(obj->getID()); }
  }
  else if(draw && !TheInGameUI->isInForceAttackMode() && TheInGameUI->canSelectedObjectsDoAction(4,obj,1,false)) {
   if(type==DO_COMMAND || type==DO_EVALUATE) {
    msgType=(GameMessage::Type)(0x42d);
    if(type==DO_COMMAND) {
     GameMessage* message=TheMessageStream->appendMessage((GameMessage::Type)msgType);message->appendLocationArgument(*pos);
     PickAndPlayInfo info;info.m_position.set(pos);
     pickAndPlayUnitVoiceResponse(TheInGameUI->getAllSelectedDrawables(),(GameMessage::Type)msgType,&info);
    }
   } else { msgType=(GameMessage::Type)(0xa4);hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendObjectIDArgument(obj->getID()); }
  }
  else if((draw || targetState.originalDraw) && !TheInGameUI->isInForceAttackMode() && TheInGameUI->canSelectedObjectsDoAction(8,originalObject?originalObject:obj,0,true)) {
   if(type==DO_COMMAND || type==DO_EVALUATE) msgType=(GameMessage::Type)(createEnterMessage(targetState.originalDraw?targetState.originalDraw:draw,type));
   else {
    if(originalObject) obj=originalObject;
    msgType=(GameMessage::Type)(g_va012ED700->evaluate(obj));hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendObjectIDArgument(obj->getID());
   }
  }
  else if(targetState.originalDraw && !TheInGameUI->isInForceAttackMode() && TheInGameUI->canSelectedObjectsDoAction(6,originalObject,0,false)) {
   if(type==DO_COMMAND || type==DO_EVALUATE) {
    msgType=(GameMessage::Type)(0x429);
    if(type==DO_COMMAND) {
     GameMessage* message=TheMessageStream->appendMessage((GameMessage::Type)msgType);message->appendObjectIDArgument(originalObject->getID());
     PickAndPlayInfo info;info.m_drawTarget=targetState.originalDraw;
     pickAndPlayUnitVoiceResponse(TheInGameUI->getAllSelectedDrawables(),(GameMessage::Type)msgType,&info);
    }
   } else { msgType=(GameMessage::Type)(0x9f);hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendObjectIDArgument(originalObject->getID()); }
  }
  else if(draw && !TheInGameUI->isInForceAttackMode() && TheInGameUI->canSelectedObjectsDoAction(2,obj,0,false)) {
   if(type==DO_COMMAND || type==DO_EVALUATE) {
    msgType=(GameMessage::Type)(0x427);
    if(type==DO_COMMAND) {
     GameMessage* message=TheMessageStream->appendMessage((GameMessage::Type)msgType);message->appendObjectIDArgument(obj->getID());
     PickAndPlayInfo info;info.m_drawTarget=draw;
     pickAndPlayUnitVoiceResponse(TheInGameUI->getAllSelectedDrawables(),(GameMessage::Type)msgType,&info);
    }
   } else { msgType=(GameMessage::Type)(0x9d);hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendObjectIDArgument(obj->getID()); }
  }
  else if(draw && !TheInGameUI->isInForceAttackMode() && TheInGameUI->canSelectedObjectsDoAction(5,obj,0,false)) {
   if(type==DO_COMMAND || type==DO_EVALUATE) {
    msgType=(GameMessage::Type)(0x428);
    if(type==DO_COMMAND) {
     GameMessage* message=TheMessageStream->appendMessage((GameMessage::Type)msgType);message->appendObjectIDArgument(obj->getID());
     PickAndPlayInfo info;info.m_drawTarget=draw;
     pickAndPlayUnitVoiceResponse(TheInGameUI->getAllSelectedDrawables(),(GameMessage::Type)msgType,&info);
    }
   } else { msgType=(GameMessage::Type)(0x9e);hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendObjectIDArgument(obj->getID()); }
  }
  else if(draw && draw->getObject() && !TheInGameUI->isInForceAttackMode() && TheInGameUI->canSelectedObjectsDoAction(10,draw->getObject(),0,false)) {
   if(type==DO_COMMAND || type==DO_EVALUATE) msgType=(GameMessage::Type)(createEnterMessage(draw,type));
   else { msgType=(GameMessage::Type)(0xa8);hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendObjectIDArgument(draw->getObject()->getID()); }
  }
  else if(draw && !TheInGameUI->isInForceAttackMode() && TheInGameUI->canSelectedObjectsDoAction(11,obj,0,false)) {
   if(type==DO_COMMAND || type==DO_EVALUATE) msgType=(GameMessage::Type)(createEnterMessage(draw,type));
   else { msgType=(GameMessage::Type)(0xaa);hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendObjectIDArgument(obj->getID()); }
  }
  else if(draw && !TheInGameUI->isInForceAttackMode() && canSelectionSalvage(obj)) {
   if(type==DO_COMMAND || type==DO_EVALUATE) {
    msgType=(GameMessage::Type)(0x441);
    if(type==DO_COMMAND) {
     GameMessage* message=TheMessageStream->appendMessage((GameMessage::Type)msgType);message->appendLocationArgument(*obj->getPosition());
     PickAndPlayInfo info;info.m_drawTarget=draw;
     pickAndPlayUnitVoiceResponse(TheInGameUI->getAllSelectedDrawables(),(GameMessage::Type)msgType,&info);
    }
   } else { msgType=(GameMessage::Type)(0xb0);hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendLocationArgument(*obj->getPosition()); }
  }
  else if(draw && !TheInGameUI->isInForceAttackMode() && TheInGameUI->canSelectedObjectsDoAction(9,obj,0,true)) {
   if(type==DO_COMMAND || type==DO_EVALUATE) msgType=(GameMessage::Type)(createEnterMessage(draw,type));
   else { msgType=(GameMessage::Type)(0xa2);hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendObjectIDArgument(obj->getID()); }
  }
  else {
   if(draw) {
    if((targetState.result=TheInGameUI->getCanSelectedObjectsAttack(1,obj,0,TheInGameUI->isInForceAttackMode()))==3) {

   if(type==DO_COMMAND || type==DO_EVALUATE) msgType=(GameMessage::Type)(issueAttackCommand(draw,pos,type));
   else { msgType=(GameMessage::Type)(0x99);hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendObjectIDArgument(obj->getID()); }
  
    goto evaluateDone;
    }
    else if(targetState.result==2) {

   if(type==DO_COMMAND || type==DO_EVALUATE) msgType=(GameMessage::Type)(issueAttackCommand(draw,pos,type));
   else { msgType=(GameMessage::Type)(0xb2);hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendObjectIDArgument(obj->getID()); }
  
    goto evaluateDone;
    }
   }

  if(draw && TheInGameUI->canSelectedObjectsDoAction(0xc,obj,0)) {
   Object* source=TheInGameUI->getFirstSelectedDrawable()->getObject();
   const CommandSet* set=TheControlBar->findCommandSet(source->getCommandSetString());
   if(set) for(int i=0;i<20;++i) {
    const CommandButton* button=set->getCommandButton(i);
    if(button && button->getCommandType()==0x17) {
     int power=button->getSpecialPowerTemplate()->getSpecialPowerType();
     if(type==DO_COMMAND || type==DO_EVALUATE) {
      if(power==0x1a || power==0x1d) { msgType=(GameMessage::Type)(issueSpecialPowerCommand(button,type,draw,pos,0));break; }
     }
    }
   }
  }
  else if(draw && TheInGameUI->canSelectedObjectsDoAction(0x12,obj,0)) {
   if(type==DO_COMMAND) {
    CommandTranslator* translator=this;
    const CommandButton* button=translator->rva005A7E20(0x34);
    if(button) msgType=(GameMessage::Type)(translator->issueSpecialPowerCommand(button,type,draw,pos,0));
   } else {
    msgType=(GameMessage::Type)(0x7d6);hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendObjectIDArgument(obj->getID());
    Object* selected=TheInGameUI->getFirstSelectedDrawable()->getObject();
    Rva0010B500Result* entry=g_va012EF188->find((const int*)&selected->field224);
    if(entry) hintMessage->appendIntegerArgument(TheMouse->getCursorIndex(entry->field118));else hintMessage->appendIntegerArgument(1);
   }
  }
  else if(draw && TheInGameUI->canSelectedObjectsDoAction(0x11,obj,1)) {
   if(type==DO_COMMAND || type==DO_EVALUATE) {
    Object* source=TheInGameUI->getFirstSelectedDrawable()->getObject();
    const CommandSet* set=TheControlBar->findCommandSet(source->getCommandSetString());
    if(set) for(int i=0;i<20;++i) {
     const CommandButton* button=set->getCommandButton(i);
     if(button && button->getCommandType()==0x17) {
      int power=button->getSpecialPowerTemplate()->getSpecialPowerType();
      if(power==0x27) { msgType=(GameMessage::Type)(issueSpecialPowerCommand(button,type,draw,pos,0));break; }
     }
    }
   } else {
    bool valid=true;
    if(obj && pos && obj->isKindOf(0x5d)) {
     Object* source=TheInGameUI->getFirstSelectedDrawable()->getObject();
     if(source && !TheAI->getPathfinder()->slowDoesPathExist(source,source->getPosition(),pos,0)) valid=false;
    }
    if(valid) { msgType=(GameMessage::Type)0x7d8;hintMessage=TheMessageStream->appendMessage(msgType);hintMessage->appendObjectIDArgument(obj->getID()); }
    else { msgType=(GameMessage::Type)0xb1;hintMessage=TheMessageStream->appendMessage(msgType);hintMessage->appendObjectIDArgument(obj->getID()); }
   }
  }
  else if(draw && TheInGameUI->getSelectCount()==1 && TheInGameUI->canSelectedObjectsDoAction(0x10,draw->getObject(),1)) {
   if(type==DO_COMMAND || type==DO_EVALUATE) {
    msgType=(GameMessage::Type)(0x422);
    if(type==DO_COMMAND) {
     GameMessage* message=TheMessageStream->appendMessage((GameMessage::Type)msgType);
     Object* target=draw->getObject();message->appendObjectIDArgument(!target?0:target->getID());
     PickAndPlayInfo info;
     if(target) { info.m_drawTarget=target->getDrawable();info.m_position=*target->getPosition(); }
     pickAndPlayUnitVoiceResponse(TheInGameUI->getAllSelectedDrawables(),(GameMessage::Type)msgType,&info);
    }
   } else { msgType=(GameMessage::Type)(0x7d7);hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendObjectIDArgument(obj->getID()); }
  }
  else if(pos && !draw && TheInGameUI->canSelectedObjectsDoAction(0xe,0,1,false) || draw && obj && TheInGameUI->canSelectedObjectsDoAction(0xe,obj,0,false)) {
   msgType=(GameMessage::Type)(0x412);
   if(type==DO_COMMAND) {
    const DrawableList* allSelected=TheInGameUI->getAllSelectedDrawables();
    for(DrawableList::const_iterator it=allSelected->begin();it!=allSelected->end();++it) {
     Drawable* selected=*it;
     if(selected && selected->getObject()) {
      GameMessage* message=TheMessageStream->appendMessage((GameMessage::Type)msgType);
      message->appendObjectIDArgument(selected->getObject()->getID());message->appendLocationArgument(*pos);
      bool queue=queueRallyPoint(draw);
      message->appendBooleanArgument(queue);
      message->appendObjectIDArgument(obj?obj->getID():0);
     }
    }
   } else if(type==DO_HINT) { msgType=(GameMessage::Type)(0xae);hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendLocationArgument(*pos); }
  }
  else if(draw && targetState.result==1) { msgType=(GameMessage::Type)(0x9a);hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendLocationArgument(*pos); }
  else {
   bool validQuickPath=false;
   if(ThePartitionManager->getShroudStatusForPlayer(ThePlayerList->getLocalPlayer()->getPlayerIndex(),pos)!=0) validQuickPath=true;
   else {
    const DrawableList* allSelected=TheInGameUI->getAllSelectedDrawables();
    for(DrawableList::const_iterator it=allSelected->begin();it!=allSelected->end();++it) {
     Object* selected=*it?(*it)->getObject():0;
     AIUpdateInterface* ai=selected?selected->getAI():0;
     if(selected) { if(selected->isMobile()) { if(selected->isKindOf(0x96) || (ai && ai->isQuickPathAvailable(pos))) { validQuickPath=true;break; } } }
    }
   }
   if(type==DO_COMMAND || type==DO_EVALUATE) {
    if(obj && obj->isKindOf(0x67)) issueMoveToLocationCommand(pos,0,type);
    else {
     msgType=(GameMessage::Type)(issueMoveToLocationCommand(pos,drawableInWay,type));
     if(!(obj && onlyMask && targetState.result==ATTACKRESULT_NONE && obj->isKindOf(0x3b)) && draw) msgType=(GameMessage::Type)0;
    }
   } else {
    bool aiAllows=singleSelected && singleSelected->getAI() && singleSelected->getAI()->rvaSlot130();
    if(!validQuickPath && !(singleSelected && singleSelected->isKindOf(0x85)) && !aiAllows) msgType=(GameMessage::Type)(0xb1);
    else if(TheInGameUI->isInWaypointMode()) msgType=(GameMessage::Type)(0xa7);
    else msgType=(GameMessage::Type)(0xa5);
    hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendLocationArgument(*pos);
   }
  }
  }
 }
 else if(type==DO_HINT && TheInGameUI->getSelectCount()>0 && !TheInGameUI->rva0043EC00()) {
  msgType=(GameMessage::Type)(0xb1);GameMessage* hintMessage=TheMessageStream->appendMessage((GameMessage::Type)msgType);hintMessage->appendLocationArgument(*pos);
 }
evaluateDone:
 return (CommandEvaluateType)msgType;
}
