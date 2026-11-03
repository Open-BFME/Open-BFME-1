// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Include
// Retail RVA 0x002BD310, 525 bytes: GiantBirdGuardOuterState::onEnter, slot 4 of the
// state's vtable 0x010C7C28 installed by its constructor 0x002C04D0; ilt_oracle
// CONFIRMS the decorated name through ILT 0x00040142. Replaces the MASM dump
// game/masm_dumps/Rva002BD310GiantBirdGuardOuterOnEnter.asm.
//
// Port of the BFME 2 donor Code/GameEngine/Source/GameLogic/AI/AIGuardStates.cpp
// (open-bfme-2 45afcff3) with its quoted headers inlined and every other donor body
// left out. The donor's statement order is what fixes the AIAttackState constructor
// arguments (machine ECX, &m_exitConditions EDX) that 80+ Zero Hour spellings could not.
// BFME 1 layout deltas, read from the retail body:
//   - State::m_machine is at +0x1C, so the state's own members are 4 bytes higher.
//   - StateMachine::m_owner is at +0x10.
//   - The guard machine fields start at +0x44 (nemesis +0x6C, mode +0x70).
//   - TheAI's data pointer is at +0x14; TheGameLogic's frame is at +0x3C.
//   - The team-centre call is Team::getPosition through ILT 0x000241FE (pinned).
typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;
#include <stddef.h>
// ---- inlined inputs/reference/open-bfme-2/Code/GameEngine/Source/Common/GameLogicObjectLookupView.h

// BFME 2's native lookup at 0x00049DC5 uses the ObjectID enum and a map
// receiver at +0xB4. The provider's existing accessed prefix is shared here;
// complete GameLogic and map extents remain unreconstructed. Pointer-only
// callers do not construct these views or depend on their sizeof.
// Reference-backed consumers may already have the same ObjectID enum.
#ifndef _GAME_TYPE_H_
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};
#endif

class Xfer;
class GameMessage;
class BfmeThingEC;
class Object;
class Drawable;
class Rva00439E0C;
class AsciiString;
class CommandButton;
class WindowLayout;
class Rva0023E928;
class UnicodeString;
class TerrainResourceManager;
class LoadScreen;
class UpdateModule;
class GameInfo;
class ThingTemplate;
class Team;
struct CreateMask;
struct ObjectTOCEntry;
struct Rva0040D2FDVec;
struct Rva003F468DParticipant;
enum BuildableStatus;

struct ObjectIdNode
{
	char pad[8];
	Object *object;
};

class ObjectIdMap
{
public:
	ObjectIdNode *find(const ObjectID &id);
};

// The network code reads the command timestamp at +0x38 and Zero Hour's
// frame counter at +0x40 (ConnectionManager::update 0x004D342A, among others).
// StealthUpdate::disguiseAsObject (0x00373DF0) reads the manager at +0x178
// whose call 0x00439E0C takes the disguised object. The spell store's show
// (finishShowPurchaseScience 0x0043CB48) reads the end flag at +0x6D and
// the game mode at +0x110.
// InGameUI::addFloatingText (0x002A0D19) gates on the byte at +0x9A, Zero
// Hour's getDrawIconUI.
// The object list head is at +0xAC: getFirstObject (0x0023CAD2) returns it and
// prepareLogicForObjectLoad (0x00242C86) walks it inline.
// ScoreKeeper::addObjectLost (0x0039CF73) tests the scoring byte at +0x98
// first, as Zero Hour's isScoringEnabled does.
// GameClient::update (0x0023BEE8) reads the byte at +0x125, next to the pause
// byte isGamePaused (0x0023CD97) returns from +0x124, and skips the drawable,
// terrain and display updates while it is set.
// Object::initObject (0x002934E7) and setTriggerAreaFlagsForChangeInPosition
// (0x00291EB1) store the current frame at +0x180, as Zero Hour's
// updateObjectsChangedTriggerAreas stores m_frameObjectsChangedTriggerAreas.
// The script setters 0x003BB700 and 0x003BCA7B store their bool argument in
// the scoring byte (+0x98) and the icon-UI byte (+0x9A).
// PlaceEventTranslator::translateGameMessage (0x0043218A) swaps its
// pendingBuild/builderObj spill homes with the TU's declaration count, and
// not monotonically: before the +0x11C..+0x150 members joined, adding 1-8 or
// 13-15 declarations broke it and 9-12 or 16-19 kept it. Check it after
// adding members here; dead `extern int` lines in a scratch copy find the
// exact windows.
struct PlayerLeaveStatus;
class GameLogic
{
	char pad[0x38];
	unsigned int m_timestamp;

public:
	unsigned int m_frame; // +0x3C in BFME 1, the frame getFrame returns

private:
	char pad40[0x6D - 0x40];

public:
	bool m_6d; // +0x6D

private:
	char pad6E[0x98 - 0x6E];
	bool m_isScoringEnabled; // +0x98
	char pad99[0x9A - 0x99];
	bool m_drawIconUI; // +0x9A
	char pad9B[0xAC - 0x9B];
	Object *m_firstObject; // +0xAC, the head getFirstObject returns
	char padB0[0xB4 - 0xB0];
	ObjectIdMap m_map;
	char padB5[0x110 - 0xB5];

public:
	int m_110; // +0x110

	// Native AIUnitBuilder598052 and listener239457 compare this word.
	int m_114; // +0x114; precise mode meaning remains unresolved

private:
	char pad118[0x11C - 0x118];

public:
	// The script setter 0x003BD2A6 stores its flag here, calling
	// rva0023D68E first when the value changes.
	unsigned char m_field11C; // +0x11C

private:
	char pad11D[0x120 - 0x11D];
	// processProgress (0x0023D740) forwards to this screen's slot 0x10.
	LoadScreen *m_loadScreen; // +0x120
	char pad124[0x125 - 0x124];
	bool m_flag125;
	char pad126[0x128 - 0x126];
	// processProgressComplete (0x0023D76E) sets a player's byte here and
	// lastHeardFrom (0x0023CF1C) stamps its timeGetTime timeout; 8 slots.
	unsigned char m_heardFlags[8]; // +0x128
	unsigned long m_progressCompleteTimeout[8]; // +0x130
	char pad150[0x170 - 0x150];
	// Native handleBuildPlacements (0x002A21E1) enumerates resource claimants
	// through this manager; WorldBuilder's corresponding field is at +0x174.
	TerrainResourceManager *m_resourceManager;
	char pad174[0x178 - 0x174];
	Rva00439E0C *m_manager178;
	char pad17C[0x180 - 0x17C];
	unsigned int m_frameObjectsChangedTriggerAreas; // +0x180
	char pad184[0x1B8 - 0x184];
	// Window cleanup 0x00376D49 owns this layout and clears the pending byte.
	// BFME1's closeWindows supplies its purpose; offsets are native BFME2.
	WindowLayout *m_background; // +0x1B8
	bool m_backgroundPending; // +0x1BC

public:
	void logicMessageDispatcher(GameMessage *, void *); // Native 0x00377613
	void rva0023F8DA(); // Verified native 0x0023F8DA game-over details
	void rva0023DA49(); // Verified native 0x0023DA49 battle-complete wrapper
	void rva0023DA4E(); // Verified native 0x0023DA4E battle-complete gate
	void rva0023D68E(bool value); // 0x0023D68E, +0xAC object walk before the +0x11C store
	void selectObject(Object *, bool, unsigned int, bool); // Verified native 0x0023C924
	void ProcessCRC(unsigned int, int, unsigned int, GameMessage *, bool, BfmeThingEC *); // Verified native 0x00241529
	void rva0023D080(int); // Verified native 0x0023D080, forwards to the void ArmySummarySystem::CallArmyToEngageInBattleByID
	void CallPlayerGiveMoney(int, int, int); // Verified native 0x0023D793
	bool rva00085124();	// 0x00085124; verified mode 4-or-7 predicate
	bool isInMultiplayerGame();	// 0x00042235
	bool rva0042219();	// 0x00042219, mode gate rejecting 9, 4 and 7
	bool rva001DCD1C();	// 0x001DCD1C, mode 8 or mode 9 with +0x114 != 3
	void rva0023CD9E(bool paused, int pauseMode, bool affectMouse);	// 0x0023CD9E
	Object *findObjectByID(ObjectID id);
	void rva0023CFE4(Xfer *xfer); // 0x0023CFE4, Version1 plus native snapshot at +0x184
	void rva0023D033(); // 0x0023D033, native +0x184 cleanup forwarder
	const AsciiString *rva0023D05F(int value);	// 0x0023D05F, +0x184 army name by id
	const AsciiString *rva0023D06A(int value);	// 0x0023D06A, +0x184 army banner name by id
	int rva0023D08B(int value);	// 0x0023D08B, existing +0x184 forwarder
	void rva0023D0C2(Object *obj, int handle);	// 0x0023D0C2
	void TransitionFromLivingWorldTacticalBattle(); // 0x0023D0CD; timeline continue callback
	Object *getFirstObject();	// 0x0023CAD2
	int rva0023CAD9();	// 0x0023CAD9, next ObjectID for Object::Object 0x00298EA9
	void registerObject(Object *obj);	// 0x00242AE9, called by Object::Object 0x00298EA9
	void destroyObject(Object *obj);	// 0x00242C09
	void sendObjectDestroyed(Object *obj);	// 0x0023CD67, called by Object::~Object 0x00299CE4
	void rva0023CF8B();	// 0x0023CF8B, called by AptLoadScreen::init 0x0043A5F6
	void deselectObject(Object *obj, unsigned int playerMask, bool affectClient);	// 0x0023C9F8
	void bindObjectAndDrawable(Object *obj, Drawable *draw);	// 0x0023CD4A
	void clearGameData(bool first, bool second);	// 0x00376E92
	void rva00376D49();	// 0x00376D49, window cleanup, donor closeWindows
	void startNewGame(bool fromSave);	// 0x00248558, verified new-game/load pass
	unsigned char isGamePaused();	// 0x0023CD97
	bool rva002423E3();	// 0x002423E3
	void processDestroyList();	// 0x002413DF
	void prepareLogicForObjectLoad();	// 0x00242C86
	void processProgressComplete(int playerID);	// 0x0023D76E
	void CreateWOTRMPPlayers(); // 0x0023E99A; verified provider, campaign caller 0x0052C45E
	void setControlBarOverride(const AsciiString &commandSetName, int slot, const CommandButton *commandButton);	// 0x0024792F
	void ProcessSaveGameCommand(Rva0023E928 *msg, bool frozen);	// 0x00240866, multiplayer save request handler
	void rva0023D30F(int a, int b, UnicodeString *name);	// 0x0023D30F, thiscall spelling of the stdcall Rva0023D30FCall
	void enableScoring(bool score) { m_isScoringEnabled = score; }
	bool isScoringEnabled() const { return m_isScoringEnabled; }
	void setDrawIconUI(bool setting) { m_drawIconUI = setting; }
	void updateObjectsChangedTriggerAreas() { m_frameObjectsChangedTriggerAreas = m_frame; }
	bool getFlag125() const { return m_flag125; }
	unsigned int getTimestamp() const { return m_timestamp; }
	unsigned int getFrame() const { return m_frame; }
	bool getDrawIconUI() const { return m_drawIconUI; }
	Rva00439E0C *getManager178() const { return m_manager178; }
	TerrainResourceManager *getTerrainResourceManager() const { return m_resourceManager; }
	PlayerLeaveStatus *getPlayerLeaveStatus(int playerIndex); // 0x0023D1E3, verified eight-slot status accessor
	char rva0023C6FD();	// 0x0023C6FD
	void processCommandList();	// 0x0023CAA3
	unsigned int getCRC(int mode);	// 0x0023CB2C
	unsigned int getObjectCount();	// 0x0023CFCE
	void rva0023D007(int value);	// 0x0023D007, +0x184 forwarder
	int rva0023D0B7();	// 0x0023D0B7, +0x184 forwarder
	void DoExitMap(bool selfDestruct);	// 0x0023D0E3
	void rva0023D17D();	// 0x0023D17D
	void rva0023D201(int slotIndex, int status);	// 0x0023D201
	void processProgress(int playerId, int percentage);	// 0x0023D740
	void lastHeardFrom(int playerId);	// 0x0023CF1C
	void rva0023FABE(Object *obj);	// 0x0023FABE
	void friend_awakenUpdateModule(Object *obj, UpdateModule *updateModule, unsigned int when);	// 0x0024297F
	bool rva00245EDF(void *arg1, int *out);	// 0x00245EDF
	bool rva00246F8E(const AsciiString &setName, int slot, const CommandButton **button);	// 0x00246F8E
	bool rva0024877A();	// 0x0024877A
	void rva003BA5DD(int value);	// 0x003BA5DD
	void rva0023D028();	// 0x0023D028
	void rva0023D03E();	// 0x0023D03E
	void rva0023D054(int a, int b, Rva0040D2FDVec *out);	// 0x0023D054
	int rva0023D075(int value);	// 0x0023D075
	float rva0023D096(int value);	// 0x0023D096
	int rva0023D0A1(int value);	// 0x0023D0A1
	int rva0023D0AC(int value);	// 0x0023D0AC
	Object *friend_createObject(const ThingTemplate *thingTemplate, const CreateMask *mask, Team *team, ObjectID id);	// 0x0023CAE7
	ObjectTOCEntry *findTOCEntryByName(AsciiString name);	// 0x00240167
	void QueueForNotifyPathfindCellChanged(Object *obj);	// 0x00241C25
	void xferObjectTOC(Xfer *xfer);	// 0x00245F79
	void setBuildableStatusOverride(const ThingTemplate *thingTemplate, BuildableStatus status);	// 0x00246F71
	void bfmePopulateGameReport(GameInfo *game, int *localSlot);	// 0x00247378
	void formatPlayerStartWaypointName(AsciiString *out);	// 0x0024822B
	Rva003F468DParticipant *GetLivingWorldTacticalVictor();	// 0x0023D884
};
typedef UnsignedInt TeamID;
enum
{
	AI_VISIONFACTOR_OWNERTYPE = 0x01,
	AI_VISIONFACTOR_MOOD = 0x02,
	AI_VISIONFACTOR_GUARDINNER = 0x04
};
enum StateExitType
{
	EXIT_NORMAL = 0
};
enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};
#include "Lib/Coord3D.h"
class Object;
class AIUpdateInterface;
class Rva0030B719Shape
{
public:
	Real getRadius(void) const;
};
class PolygonTrigger
{
public:
	void getCenterPoint(Coord3D *pOutCenter) const;
	const Rva0030B719Shape *getShape() const { return &m_shape; }
private:
	unsigned char m_pad00[0x08];
	Rva0030B719Shape m_shape; // +0x08
};
extern int BfmeLogicFramesPerSecond;
#define LOGICFRAMES_PER_SECOND BfmeLogicFramesPerSecond
// ---- inlined inputs/reference/open-bfme-2/Code/GameEngine/Include/Common/TeamBFME2.h
// Team: canonical BFME2 header (hand-written; header_adopt_lane's generator
// emits no virtuals, and this class is polymorphic).
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
// Named TeamBFME2.h, like ScriptActionsBFME2.h: Zero Hour's Common/Player.h
// includes "Common/Team.h", so a Code/GameEngine/Include/Common/Team.h would
// shadow the Zero Hour header for every unit with that directory on its path.
//
// Target facts, read off game.dat:
//  - The ctor 0x003A39A7 stores the Snapshot base table 0x00BBB554 at +0,
//    constructs Rva0055B0CC (ctor 0x0055B048) at +4, then stores Team's own
//    tables 0x00C1AEFC at +0 and 0x00C1AEB8 at +4. So Team : Snapshot,
//    Rva0055B0CC (BFME2 drops Zero Hour's MemoryPoolObject base), and its own
//    members start at +0x30.
//  - 0x00C1AEFC has Snapshot's four slots: ??_G 0x003A38CD, loadPostProcess
//    0x003A2339, GetSnapshotName 0x003A3709, xfer 0x003A2072 (rows name all
//    four protected, M). 0x00C1AEB8 has Rva0055B0CC's seventeen: the ??_E
//    thunk 0x003A370F (sub ecx,4), slot 2 0x0039D840, slot 13 getLocation
//    0x0039D7DB, slots 14..16 0x0047A699 / 0x005CB9FA / 0x005DAA6C; the rest
//    are the base's.
//  - TeamFactory allocates 0x13C bytes before each ctor call (0x003A3C1E,
//    0x003A3D65, 0x003A3DE6): sizeof 0x13C.
//  - Member offsets from the ctor's stores (TeamCtor.cpp states each one).
//
// Members: every Team row of reverse/functions.csv with the access, constness
// and parameter types its decorated name states, minus two whose parameter
// types are templates units spell differently (countObjects' and
// transferKindOfUnitsTo's BitFlags; some units define a non-template BitFlags),
// plus the Zero Hour inline accessors the views inline.
// Data: the Zero Hour names for scalar members; the AsciiString, hash table,
// list and set members stay opaque until their types have shared headers.
// Data access is not modeled (all public); it has no codegen effect.
#ifndef CANONICAL_TEAM_H
#define CANONICAL_TEAM_H

// ---- inlined inputs/reference/open-bfme-2/reference/shims/moduledata/Common/Snapshot.h
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: Snapshot.h ///////////////////////////////////////////////////////////////////////////////
// Desc:   Canonical BFME2 Snapshot base. Retail vtable 0x00BBB554 has a
//         deleting destructor followed by three pure virtual slots, in
//         retail order: loadPostProcess, GetSnapshotName, xfer.
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __SNAPSHOT_H_
#define __SNAPSHOT_H_

// FORWARD REFERENCES /////////////////////////////////////////////////////////////////////////////
class Xfer;

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// LivingWorldBattle (003F6A3A, 003F6F0D) and LivingWorldBuildPlot
// (004FC807) complete this base before calling their list-base constructor,
// without storing Snapshot's vptr. Their first unwind state still calls the
// shared destructor at 0049B47C, which restores table 00BBB554. Constructor
// units can select that novtable surface and bind the existing destructor;
// destructor units retain the inline body that emits the native vptr store.
#ifdef BFME_SNAPSHOT_CONSTRUCTOR_ONLY
class __declspec(novtable) Snapshot
#else
class Snapshot
#endif
{

friend class GameState;
// Xfer::operator==(Snapshot &) (0x0060B8C6) calls slot 3 itself.
friend class Xfer;
friend class XferLoad;
friend class XferSave;
friend class XferCRC;
// Xfer::operator&(Snapshot &) (export, 0x0060B8C6) is a member of the
// Xfer base itself and calls the protected slot-3 transfer directly.
friend class Xfer;

public:
	
#ifdef BFME_SNAPSHOT_CONSTRUCTOR_ONLY
	__declspec(dllimport) __forceinline Snapshot() {}
	virtual ~Snapshot( void );
#else
	Snapshot() {}
	virtual ~Snapshot( void ) {}
#endif
	Snapshot( const Snapshot &that ) {}

protected:

	// Retail order. Vtable 0x00BBB554 is the deleting destructor, then three
	// __purecall slots, and the overriders fix what each slot is:
	//  - the exports name every FXParticleSystem info's overriders
	//    LoadPostProcess, GetSnapshotName and DoXfer(Xfer &), and their
	//    vtables (e.g. 0x00BBB5C8) hold them in slots 1, 2 and 3;
	//  - Xfer::operator&(Snapshot &) (export, 0x0060B8C6) calls slot 3
	//    ([eax+0Ch]) with the Xfer;
	//  - Module and ModuleData vtables (0x00C59368, 0x00C52534, 0x00C594E0)
	//    hold loadPostProcess in slot 1, a getter returning the class-name
	//    literal in slot 2 and xfer in slot 3.
	// Retail has no crc. The Zero Hour classes still compiled against this
	// header override crc(Xfer *), so it stands in for GetSnapshotName in
	// slot 2 and keeps every derived table at four base slots; slots 1 and 3
	// keep the Zero Hour spellings the ledger's rows use.

	/** post process phase for loading save games.  All save systems have their xfer
	run using XferLoad mode, and then all systems each have their post process run */
// BFME2's named tracker table has the capitalized API. This selects the
	// spelling of the same three slots; the default ZH surface stays available.
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
	virtual void LoadPostProcess( void ) = 0;
#else
	virtual void loadPostProcess( void ) = 0;
#endif

	// Named BFME2 snapshot getters use the proven retail slot-2 signature.
	// Other imported units retain the Zero Hour crc spelling described above.
	// Both declarations occupy the same single slot, never an added fifth one.
#ifdef BFME_SNAPSHOT_NAME_SLOT
// FX info exports and retail vtable C1BBA0 use the non-const getter at
// 001F354A. Other consumers retain their established const signature.
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
	virtual const char *GetSnapshotName( void ) = 0;
#else
	virtual const char *GetSnapshotName( void ) const = 0;
#endif
#else
	virtual void crc( Xfer *xfer ) = 0;
#endif

	/** run save, load, or deep CRC check on this data structure, the type depends on the
	setup of the Xfer pointer */
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
// FX info DoXfer exports take Xfer& (e.g. 0047A69C); it occupies the same
// slot and has the same one-pointer ABI as the existing pointer surface.
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
	virtual void DoXfer( Xfer &xfer ) = 0;
#else
	virtual void DoXfer( Xfer *xfer ) = 0;
#endif
#else
	virtual void xfer( Xfer *xfer ) = 0;
#endif

};

#endif // __SNAPSHOT_H_
// ---- inlined inputs/reference/open-bfme-2/Code/GameEngine/Source/Common/Rva0055B0CC.h
// Rva0055B0CC: the 0x2C-byte polymorphic base Team (and the AI buildables)
// derive from. Its ctor 0x0055B048 and dtor 0x0055B0CC sit in AIBuildable.cpp
// and two of its slots carry AIBuildable rows (addNeed, registerWithBuilder),
// so WorldBuilder's AIBuildable is the likely original name; the ledger still
// spells it Rva0055B0CC and this header keeps that spelling.
//
// Target facts, read off game.dat:
//  - The ctor 0x0055B048 installs table 0x0086B900, 17 slots:
//     0 ??_G 0x0055B166           1 0x0055AFA3 (void())
//     2 0x0055B0B9 (float() const) 3 0x0055B146 (void(int), AIBuildable::addNeed)
//     4 0x0047A699 (bool() const, returns false)
//     5 0x0055B228 rva0055B228    6 0x0055AD91 (void(void *, bool), registerWithBuilder)
//     7 0x005F69CE (void(int))    8 0x003A36D3, 9 0x003A36F7, 10 0x003A3700 (float(int))
//    11 0x0047A699 (bool() const) 12 0x0055AED6 Rva0055AED6(Xfer *, void *)
//    13..16 __purecall: Team supplies 13 getLocation (0x0039D7DB) and 14..16.
//  - Slot signatures come from the bodies' own rows; vslotNN names are
//    placeholders for slots whose rows belong to other classes (ICF-shared
//    bodies or AIBuildable spellings), so callers through this class keep the
//    retail slot index.
//  - sizeof 0x2C: Team's ctor 0x003A39A7 constructs it at +4 and starts its own
//    members at +0x30.
#ifndef CANONICAL_RVA0055B0CC_H
#define CANONICAL_RVA0055B0CC_H

struct Coord3D;
class Xfer;

class Rva0055B0CC
{
public:
	Rva0055B0CC();									// 0x0055B048
	virtual ~Rva0055B0CC();							// 0x0055B0CC (slot 0: ??_G 0x0055B166)
	virtual void vslot01();							// slot 1, 0x0055AFA3
	virtual float vslot02() const;					// slot 2, 0x0055B0B9
	virtual void vslot03(int);						// slot 3, 0x0055B146
	virtual bool vslot04() const;					// slot 4, 0x0047A699
	virtual void rva0055B228();						// slot 5, 0x0055B228
	virtual void vslot06(void *, bool);				// slot 6, 0x0055AD91
	virtual void vslot07(int);						// slot 7, 0x005F69CE
	virtual float vslot08(int);						// slot 8, 0x003A36D3
	virtual float vslot09(int);						// slot 9, 0x003A36F7
	virtual float vslot10(int);						// slot 10, 0x003A3700
	virtual bool vslot11() const;					// slot 11, 0x0047A699
	virtual void Rva0055AED6(Xfer *, void *);		// slot 12, 0x0055AED6
	virtual Coord3D getLocation() const = 0;		// slot 13, pure here
	virtual bool vslot14() const = 0;				// slot 14, pure here
	virtual bool vslot15(int) = 0;					// slot 15, pure here
	virtual int vslot16(void *) = 0;				// slot 16, pure here

	void rva0055B01F();								// 0x0055B01F

private:
	unsigned char m_opaque04[0x2C - 0x04];			// +0x04; AIBuildable.cpp names the fields
};
typedef char CanonicalRva0055B0CCSizeCheck[sizeof(Rva0055B0CC) == 0x2C ? 1 : -1];

#endif // CANONICAL_RVA0055B0CC_H

class AIGroup;
class AsciiString;
class BfmeFixedStorage0004543D;
class BfmeTab1026;
struct Coord3D;
class Object;
class ObjectTypes;
class Player;
class PlayerRelationMap;
class PolygonTrigger;
class Rva00376A62;
class Team;
class TeamPrototype;
class TeamRelationMap;
class ThingTemplate;
class Waypoint;
class Xfer;
enum Relationship;
// Units define the iterator template themselves (86 views declare the
// out-of-line iterate_TeamMemberList below against their own definition).
template <class OBJECT> class DLINK_ITERATOR;

class Team : public Snapshot, public Rva0055B0CC
{
public:
	Team(TeamPrototype *proto, int id);				// 0x003A39A7

	// Zero Hour inline accessors.
	TeamPrototype *getPrototype() const { return m_proto; }
	unsigned int getID() const { return m_id; }
	void setActive() { if (!m_active) { m_created = true; m_active = true; } }
	bool isActive() const { return m_active; }
	bool isCreated() const { return m_created; }
	bool didEnterOrExit() const { return m_enteredOrExited; }
	const Waypoint *getCurrentWaypoint() { return m_currentWaypoint; }
	void setCurrentWaypoint(const Waypoint *way) { m_currentWaypoint = way; }
	Object *getFirstItemIn_TeamMemberList() const { return m_dlinkhead_TeamMemberList; }

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;	// 0x00263864
	bool isInList_TeamMemberList(Object *) const;	// 0x0028A74F
	void prependTo_TeamMemberList(Object *);		// 0x0028A75F
	void removeFrom_TeamMemberList(Object *);		// 0x0028A77F
	bool dlink_isInList_TeamInstanceList(Team *const *pListHead) const;	// 0x0039D40F
	void dlink_prependTo_TeamInstanceList(Team **pListHead);	// 0x0039D429
	void dlink_removeFrom_TeamInstanceList(Team **pListHead);	// 0x0039D440
	Player *getControllingPlayer() const;			// 0x0039D7CF
	virtual Coord3D getLocation() const;			// 0x0039D7DB, Rva0055B0CC slot 13
	void setTeamTargetObject(Object *);				// 0x0039D84A
	void rva0039D889(bool);							// 0x0039D889
	void rva0039D8BA(Object *);						// 0x0039D8BA
	void rva0039D8D3(unsigned int);					// 0x0039D8D3
	void setControllingPlayer(Player *newController);	// 0x0039D97E
	int getTargetableCount() const;					// 0x0039D9E3
	Coord3D *rva0039DA2A(Coord3D *) const;			// 0x0039DA2A
	bool rva0039DAF4() const;						// 0x0039DAF4
	void rva0039DB31(const void *);					// 0x0039DB31
	void countObjectsByThingTemplate(int numThings, const ThingTemplate *const *things, bool ignoreDead, int *counts, bool ignoreUnderConstruction) const;	// 0x0039DB89
	int rva0039DC05(int, bool, bool) const;			// 0x0039DC05
	int countBuildings() const;						// 0x0039DC63
	void healAllObjects();							// 0x0039DCE9
	int rva0039DD12(int (*func)(Object *, void *), void *userData) const;	// 0x0039DD12
	bool rva0039DD4B(bool);							// 0x0039DD4B
	bool rva0039DDC2(BfmeFixedStorage0004543D, bool);	// 0x0039DDC2
	bool rva0039DE46(BfmeTab1026 *, bool);			// 0x0039DE46
	bool hasAnyUnits();								// 0x0039DEC4
	bool hasAnyBuildings(BfmeFixedStorage0004543D, BfmeFixedStorage0004543D);	// 0x0039DF1C
	bool rva0039DF87(BfmeTab1026 *);				// 0x0039DF87
	bool isIdle() const;							// 0x0039DFF8
	bool hasAnyObjects(bool);						// 0x0039E042
	bool rva0039E0D0();								// 0x0039E0D0
	bool didAllEnter(PolygonTrigger *pTrigger, unsigned int whichToConsider);	// 0x0039E15D
	bool didPartialEnter(PolygonTrigger *pTrigger, unsigned int whichToConsider);	// 0x0039E20D
	bool didPartialExit(PolygonTrigger *pTrigger, unsigned int whichToConsider);	// 0x0039E288
	bool didAllExit(PolygonTrigger *pTrigger, unsigned int whichToConsider);	// 0x0039E303
	bool allInside(PolygonTrigger *pTrigger, unsigned int whichToConsider);	// 0x0039E3C8
	bool noneInside(PolygonTrigger *pTrigger, unsigned int whichToConsider);	// 0x0039E474
	bool someInsideSomeOutside(PolygonTrigger *pTrigger, unsigned int whichToConsider);	// 0x0039E50D
	void getPosition(Coord3D *);					// BFME 1 ILT 0x000241FE (pinned)
	void transferUnitsTo(Team *newTeam);			// 0x0039E660
	bool damageTeamMembers(float amount);			// 0x0039E76C
	void moveTeamTo(Coord3D destination);			// 0x0039E7F2
	bool hasAnyBuildFacility();						// 0x0039E815
	float rva0039E84B(Object *);					// 0x0039E84B
	Object *rva0039E8EB();							// 0x0039E8EB
	bool rva0039E8FF(int);							// 0x0039E8FF
	Object *rva0039E968(int);						// 0x0039E968
	Coord3D *rva0039E9A1(Coord3D *) const;			// 0x0039E9A1
	void disband();									// 0x0039E9E0
	void setAttackPriorityName(AsciiString name);	// 0x0039F094
	bool rva0039F0D2();								// 0x0039F0D2
	void updateState();								// 0x0039F0E3
	bool rva0039F824();								// 0x0039F824
	void notifyTeamOfObjectDeath(Object *goneObj);	// 0x0039F835
	void updateGenericScripts();					// 0x0039F8F7
	void getTeamAsAIGroup(AIGroup *pAIGroup);		// 0x003A0F62
	Relationship getRelationship(const Team *that) const;	// 0x003A0FD2
	Object *getTeamTargetObject();					// 0x003A105B
	bool rva003A10C0(int) const;					// 0x003A10C0
	bool rva003A10DF(int) const;					// 0x003A10DF
	void deleteTeam(bool ignoreDead);				// 0x003A10FE
	bool recruitUnit(Object **, float *, Object *, const ThingTemplate *, const Coord3D *);	// 0x003A123C
	Object *tryToRecruit(const ThingTemplate *, const Coord3D *, float, int, int, int);	// 0x003A135B
	bool rva003A1542(const ThingTemplate *, int);	// 0x003A1542
	int rva003A1626(const ThingTemplate *, Rva00376A62 *, int, Team *);	// 0x003A1626
	int rva003A178D(ObjectTypes *, int, Team *);	// 0x003A178D
	int rva003A1AA3(const ThingTemplate *, ObjectTypes *, int, float);	// 0x003A1AA3
	void evacuateTeam(bool);						// 0x003A1C3A
	void killTeam();								// 0x003A1D1A
	bool enableGenericScript(const AsciiString &, const AsciiString &, bool);	// 0x003A1F65
	void rva003A23A5(int id, bool add);				// 0x003A23A5
	void rva003A2CEB(int, Object *);				// 0x003A2CEB
	void rva003A2D53(int, Object *);				// 0x003A2D53
	void rva003A2DBB(float);						// 0x003A2DBB
	bool rva003A3717(const AsciiString &);			// 0x003A3717
	float rva003A3736(float);						// 0x003A3736
	void rva003A38E9(const AsciiString &, unsigned char);	// 0x003A38E9
	void setRecruitable(bool recruitable);			// 0x003BA5F9
	Team *dlink_next_TeamInstanceList() const;		// 0x005C4AF5

	// Rva0055B0CC slots Team fills with ICF-shared bodies.
	virtual float vslot02() const;					// slot 2, 0x0039D840
	virtual bool vslot14() const;					// slot 14, 0x0047A699
	virtual bool vslot15(int);						// slot 15, 0x005CB9FA
	virtual int vslot16(void *);					// slot 16, 0x005DAA6C

protected:
	virtual ~Team();								// 0x003A354F (??_G 0x003A38CD, ??_E 0x003A370F)

	// Snapshot slots, spelled the way the unit selected Snapshot.h's; Team's
	// rows are loadPostProcess, GetSnapshotName() const and xfer.
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
	virtual void LoadPostProcess();
#else
	virtual void loadPostProcess();					// 0x003A2339
#endif
#ifdef BFME_SNAPSHOT_NAME_SLOT
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
	virtual const char *GetSnapshotName();
#else
	virtual const char *GetSnapshotName() const;	// 0x003A3709
#endif
#else
	virtual void crc(Xfer *xfer);
#endif
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
	virtual void DoXfer(Xfer &xfer);
#else
	virtual void DoXfer(Xfer *xfer);
#endif
#else
	virtual void xfer(Xfer *xfer);					// 0x003A2072
#endif

public:
	TeamPrototype *m_proto;							// +0x30
	unsigned int m_id;								// +0x34
	Object *m_dlinkhead_TeamMemberList;				// +0x38
	Team *m_dlink_TeamInstanceList_prev;			// +0x3C
	Team *m_dlink_TeamInstanceList_next;			// +0x40
	unsigned char m_opaque44[4];					// +0x44 AsciiString m_state
	unsigned char m_opaque48[0x14];					// +0x48 hash table (ctor 0x003A393A)
	bool m_enteredOrExited;							// +0x5C
	bool m_active;									// +0x5D
	bool m_created;									// +0x5E
	bool m_5F;										// +0x5F
	bool m_checkEnemySighted;						// +0x60
	bool m_seeEnemy;								// +0x61
	bool m_prevSeeEnemy;							// +0x62
	bool m_wasIdle;									// +0x63
	int m_destroyThreshold;							// +0x64
	int m_curUnits;									// +0x68
	const Waypoint *m_currentWaypoint;				// +0x6C
	bool m_shouldAttemptGenericScript[32];			// +0x70
	int m_90[32];									// +0x90
	bool m_isRecruitablitySet;						// +0x110
	bool m_isRecruitable;							// +0x111
	bool m_112;										// +0x112
	bool m_113;										// +0x113
	int m_commonAttackTarget;						// +0x114
	TeamRelationMap *m_teamRelations;				// +0x118
	PlayerRelationMap *m_playerRelations;			// +0x11C
	float m_120;									// +0x120
	int m_124;										// +0x124
	bool m_128;										// +0x128
	unsigned char m_pad129[3];						// +0x129
	unsigned char m_opaque12C[4];					// +0x12C list<int>
	unsigned char m_opaque130[0xC];					// +0x130 set<AsciiString>
};													// sizeof 0x13C
typedef char CanonicalTeamSizeCheck[sizeof(Team) == 0x13C ? 1 : -1];

#endif // CANONICAL_TEAM_H
class TeamFactory
{
public:
	Team *findTeamByID(TeamID id);
};
extern TeamFactory *TheTeamFactory;
struct DamageInfoInput
{
	unsigned char m_pad00[0x08];
	ObjectID m_sourceID; // +0x08
};
struct DamageInfo
{
	DamageInfoInput in;
};
template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};
class BodyModuleInterface : public VSlots<15>
{
public:
	virtual const DamageInfo *getLastDamageInfo() const = 0;
};
class ThingTemplate
{
public:
	Bool isKindOfBfme108Bit7() const { return (m_kindOf[0] & 0x80) != 0; }
	Bool testBfme115Bit5() const { return (m_bfme115 & 0x20) != 0; }
private:
	unsigned char m_pad00[0x108];
	unsigned char m_kindOf[4]; // +0x108
	unsigned char m_pad10C[0x115 - 0x10C];
	unsigned char m_bfme115; // +0x115
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_BFME_26 = 0x26
};
enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};
enum WeaponStatus
{
	WEAPON_STATUS_BFME_4 = 4
};
// ---- inlined inputs/reference/open-bfme-2/Code/GameEngine/Include/GameLogic/Weapon.h
// Weapon: canonical BFME2 header (hand-written; the contract leaves vslots
// 1-3 undecided and reads sizeof 8, because most private views stop at
// m_template). upstream layout:
// reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
//
// Target facts, read off game.dat:
//  - WeaponStore::allocateNewWeapon (0x0028AA81) news 0x60 bytes and calls the
//    protected ctor 0x002CC23D, so sizeof is 0x60.
//  - The ctors 0x002CC23D and 0x002CC2FC and the dtor 0x002CC39E install
//    vftable 0x00C0214C; the dtor ends on Snapshot's table 0x00BBB554. So
//    Weapon : Snapshot, one vptr at +0 (no MemoryPoolObject table as in ZH).
//  - Table 0x00C0214C has four slots, Snapshot's: 0 ??_G 0x002CCE37, 1
//    loadPostProcess (the folded empty body 0x000B3FD0), 2 the name slot
//    (0x002CC2F6 returns the string "Weapon"; its row is the free
//    Rva002CC2F6Get), 3 xfer 0x002CDD47.
//  - Data offsets are the matched ctor's (WeaponCtor.cpp); names follow ZH
//    where ZH has the field. The scatter-target vector at +0x40 is opaque:
//    the views spell its element five ways (BfmeE16, int, Coord2D, ...).
//
// Members: every Weapon row of reverse/functions.csv, with the access,
// constness and parameter types its decorated name states. Addresses are
// target RVAs. Data is public so units outside the class's own rows can
// adopt the header; ZH keeps it private, which does not change the layout.
#ifndef CANONICAL_WEAPON_H
#define CANONICAL_WEAPON_H


class AsciiString;
class Matrix3D;
class Object;
class WeaponBonus;
class WeaponTemplate;
class Xfer;
struct Coord3D;
struct SavedWeaponState;
enum WeaponSlotType;
enum WeaponStatus;

class Weapon : public Snapshot
{
	friend class WeaponStore;

protected:
	Weapon(const WeaponTemplate *tmpl, WeaponSlotType wslot);	// 0x002CC23D
	Weapon(const Weapon &that);									// 0x002CC2FC
	virtual ~Weapon();											// 0x002CC39E (slot 0: ??_G 0x002CCE37)

	// Snapshot slots, spelled the way the unit selected Snapshot.h's.
	virtual void loadPostProcess();								// slot 1, 0x000B3FD0
#ifdef BFME_SNAPSHOT_NAME_SLOT
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
	virtual const char *GetSnapshotName();						// slot 2, 0x002CC2F6
#else
	virtual const char *GetSnapshotName() const;				// slot 2, 0x002CC2F6
#endif
#else
	virtual void crc(Xfer *xfer);
#endif

public:
	virtual void xfer(Xfer *xfer);								// slot 3, 0x002CDD47

	inline const WeaponTemplate *getTemplate() const { return m_template; }
	inline WeaponSlotType getWeaponSlot() const { return m_wslot; }
	inline unsigned int getLastShotFrame() const { return m_lastFireFrame; }
	inline unsigned int getPossibleNextShotFrame() const { return m_whenWeCanFireAgain; }
	inline bool isPitchLimited() const { return m_pitchLimited; }
	inline int getMaxShotCount() const { return m_maxShotCount; }
	inline unsigned int getSuspendFXFrame() const { return m_suspendFXFrame; }

	AsciiString getName() const;	// 0x0028F95C
	void cacheStatus(WeaponStatus) const;	// 0x002C94F5
	float rva002C957E() const;	// 0x002C957E
	bool rva002C9586();	// 0x002C9586
	void rva002C959E();	// 0x002C959E
	void rva002C95DE(int);	// 0x002C95DE
	bool rva002C95F0() const;	// 0x002C95F0
	bool isClearFiringLineOfSightTerrain(const Object *, const Coord3D &) const;	// 0x002C961F
	bool isClearGoalFiringLineOfSightTerrain(const Object *, const Coord3D &, const Coord3D &) const;	// 0x002C9655
	bool rva002C969D(const void *, int);	// 0x002C969D
	bool rva002C96D8();	// 0x002C96D8
	int getClipReloadTime(const Object *) const;	// 0x002C9AC5
	bool isTooClose(const Object *, const Object *) const;	// 0x002C9AFE
	bool isTooClose(const Object *, const Coord3D *) const;	// 0x002C9B3D
	float getAttackRange(const Object *, const Object *) const;	// 0x002C9BE4
	float getAttackRange(const Object *) const;	// 0x002C9BF8
	float getAttackDistance(const Object *, const Object *, const Coord3D *) const;	// 0x002C9C37
	bool isWithinTargetPitch(const Object *, const Object *) const;	// 0x002C9C82
	int rva002C9D3B(const Object *, unsigned int) const;	// 0x002C9D3B
	static void calcProjectileLaunchPosition(const Object *, WeaponSlotType, int, Matrix3D &, Coord3D &);	// 0x002C9E48
	static void positionProjectileForLaunch(Object *, const Object *, WeaponSlotType, int);	// 0x002CA753
	bool computeApproachTarget(const Object *, const Object *, const Coord3D *, float, Coord3D &) const;	// 0x002CAEA3
	bool isSourceObjectWithGoalPositionWithinAttackRange(const Object *, const Coord3D *, const Object *, const Coord3D *) const;	// 0x002CB2D1
	bool isWithinAttackRange(Object *, const Coord3D *, Object *, const Coord3D *, float, bool);	// 0x002CB35C
	Coord3D bfmeGetLOSVictimPos(const Object *, const Object *, int) const;	// 0x002CB65B
	bool isWithinAttackRange(const Object *, const Object *, float, int) const;	// 0x002CB933
	char isWithinAttackRange(Object *, void *, float, int) const;	// 0x002CB902
	void rva002CB967(const Object *, const Object *);	// 0x002CB967
	int isClearGoalFiringLineOfSightTerrain(const Object *, const Coord3D *, const Object *);	// 0x002CB9BD
	bool isAmmoReady() const;	// 0x002CC3FF
	WeaponStatus computeStatus(bool *) const;	// 0x002CC422
	void prepareProjectileStreamForFiring();	// 0x002CC4DD
	unsigned int getRemainingAmmo(bool) const;	// 0x002CC578
	float getPercentReadyToFire() const;	// 0x002CCE53
	bool rva002CCED3(const Object *, const Object *);	// 0x002CCED3
	WeaponStatus getStatus() const;	// 0x002CCFC7
	int getPreAttackDelay(const Object *, const Object *, const Coord3D *) const;	// 0x002CCFF0
	void preFireWeapon(const Object *, const Object *, const Coord3D *);	// 0x002CDC3D
	void loadAmmoNow(const Object *);	// 0x002CE1AC
	void reloadAmmo(const Object *);	// 0x002CE1E9
	void rva002CE226(const Object *, const SavedWeaponState *);	// 0x002CE226
	void setClipPercentFull(float, bool);	// 0x002CE280
	bool privateFireWeapon(const Object *, const Coord3D *, const Object *, int, const Coord3D *, bool, bool, unsigned int, int *);	// 0x002CE30A
	bool rva002CE6C5(const Object *, int, const Object *, int *);	// 0x002CE6C5
	bool fireWeapon(const Object *, const Coord3D *, int *);	// 0x002CE6E8
	bool bfmeFireYC(const Object *, const Coord3D *, const Object *, int);	// 0x002CE708
	bool fireProjectileDetonationWeapon(const Object *, const Coord3D *, const Coord3D *, int);	// 0x002CE72B
	bool rva002CE74B(const Object *, const Object *);	// 0x002CE74B
	Object * forceFireWeapon(const Object *, const Coord3D *);	// 0x002CE76F
	Object * forceFireWeapon(const Object *, const Object *);	// 0x002CE7A4
	void setLeechRangeActive(bool);	// 0x002D95FE
	void setMaxShotCount(int);	// 0x00661D50

protected:
	void getFiringLineOfSightOrigin(const Object *, Coord3D &) const;	// 0x002C9601
	void computeBonus(const Object *, unsigned int, WeaponBonus &) const;	// 0x002C9A6F
	void processRequestAssistance(const Object *, Object *);	// 0x002C9DF5
	void rebuildScatterTargets();	// 0x002CDB53
	void reloadWithBonus(const Object *, const WeaponBonus &, bool);	// 0x002CDB99

public:
	const WeaponTemplate *m_template;			// +0x04
	unsigned int m_ownerID;						// +0x08
	WeaponSlotType m_wslot;						// +0x0C
	mutable WeaponStatus m_status;				// +0x10
	unsigned int m_ammoInClip;					// +0x14
	unsigned int m_whenWeCanFireAgain;			// +0x18
	unsigned int m_whenPreAttackFinished;		// +0x1C
	unsigned int m_whenLastReloadStarted;		// +0x20
	unsigned int m_lastFireFrame;				// +0x24
	unsigned int m_projectileStreamID;			// +0x28
	unsigned int m_unknown2C;					// +0x2C
	unsigned int m_suspendFXFrame;				// +0x30
	int m_maxShotCount;							// +0x34
	int m_curBarrel;							// +0x38
	int m_numShotsForCurBarrel;					// +0x3C
	void *m_scatterTargets[3];					// +0x40 vector: begin, end, capacity
	bool m_pitchLimited;						// +0x4C
	char m_pad4D[3];
	unsigned int m_leechWeaponRangeActive;		// +0x50
	unsigned int m_unknown54;					// +0x54
	unsigned int m_tailState;					// +0x58
	unsigned int m_extra5C;						// +0x5C
};

#endif // CANONICAL_WEAPON_H
class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	Bool testBfme438Bit0() const { return (m_bfme438 & 1) != 0; }
	const Weapon *getCurrentWeapon(WeaponSlotType *wslot = NULL) const;
	int rva0028B511() const;
	Bool testStatus(ObjectStatusTypes bit) const;
	Real rva002C97E8(const Coord3D *a, const Coord3D *b) const;
	Object *getBfme274() const { return m_bfme274; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	const Coord3D *getPosition() const { return &m_position; }
	// The callers inline +0x304; do not emit a competing accessor COMDAT.
	__declspec(dllimport) __forceinline Team *getTeam() { return m_team; }
	AIUpdateInterface *getAI() { return m_ai; }
private:
	unsigned char m_pad00[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_position; // +0x38
	unsigned char m_pad44[0x254 - 0x44];
	BodyModuleInterface *m_body; // +0x254
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x274 - 0x25C];
	Object *m_bfme274; // +0x274
	unsigned char m_pad278[0x304 - 0x278];
	Team *m_team; // +0x304
	unsigned char m_pad308[0x438 - 0x308];
	unsigned char m_bfme438; // +0x438
};
class AIUpdateInterface
{
public:
	Real getLocomotorDistanceToGoal();
	ObjectID getCrateID() const { return m_crateCreated; }
private:
	unsigned char m_pad00[0x238];
	ObjectID m_crateCreated; // +0x238
};
struct TAiData
{
	unsigned char m_pad00[0x3C];
	UnsignedInt m_guardChaseUnitFrames; // +0x3C
	UnsignedInt m_guardEnemyScanRate; // +0x40
	UnsignedInt m_guardEnemyReturnScanRate; // +0x44
};
class AI
{
public:
	const TAiData *getAiData() const { return m_aiData; }
	static Real getAdjustedVisionRangeForObject(const Object *object, int factorsToConsider);
	static Bool rva002FE193(Object *obj, Object *nemesis);
private:
	unsigned char m_pad00[0x14];
	TAiData *m_aiData; // +0x14
};
extern AI *TheAI;
extern GameLogic *TheGameLogic;
typedef UnsignedInt StateID;
class StateMachine
{
public:
	virtual ~StateMachine();
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual void slot07();
	virtual StateReturnType setState(StateID newStateID);
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13();
	virtual void setGoalObject(const Object *obj);
	Object *getOwner() const { return m_owner; }
	Object *getGoalObject();
private:
	unsigned char m_pad04[0x10 - 0x04];
	Object *m_owner; // +0x10
};
class AIGuardMachine : public StateMachine
{
public:
	Object *findTargetToGuardByID() { return TheGameLogic->findObjectByID(m_targetToGuard); }
	Team *findTeamToGuardByID() { return TheTeamFactory->findTeamByID(m_teamToGuard); }
	Bool lookForInnerTarget(void);
	static Real getStdGuardRange(const Object *obj);
	void setNemesisID(ObjectID id) { m_nemesisToAttack = id; }
	ObjectID getNemesisID() const { return m_nemesisToAttack; }
	const PolygonTrigger *getAreaToGuard(void) const { return m_areaToGuard; }
	const Coord3D *getPositionToGuard(void) const { return &m_positionToGuard; }
	int getGuardMode() const { return m_guardMode; }
	Bool hasBfmeAreaCenter() const { return m_bfmeAreaCenterValid; }
	const Coord3D *getBfmeAreaCenter() const { return &m_bfmeAreaCenter; }
private:
	unsigned char m_pad14[0x44 - 0x14];
	ObjectID m_targetToGuard; // +0x44
	TeamID m_teamToGuard; // +0x48
	const PolygonTrigger *m_areaToGuard; // +0x4C
	Coord3D m_positionToGuard; // +0x50
	Coord3D m_bfmeAreaCenter; // +0x5C
	Bool m_bfmeAreaCenterValid; // +0x68
	unsigned char m_pad69[0x6C - 0x69];
	ObjectID m_nemesisToAttack; // +0x6C
	int m_guardMode; // +0x70
};
enum
{
	GUARDMODE_NORMAL = 0,
	GUARDMODE_GUARD_WITHOUT_PURSUIT = 1
};
class State
{
public:
	State(StateMachine *machine, unsigned int hash);
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
	StateMachine *getMachine() const { return m_machine; }
 Object *getMachineGoalObject()const{return m_machine->getGoalObject();}
protected:
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	unsigned char m_pad04[0x1C - 0x04];
	StateMachine *m_machine; // +0x1C
};
class AttackExitConditionsInterface
{
public:
	virtual Bool shouldExit(const StateMachine *machine) const = 0;
};
class ExitConditions : public AttackExitConditionsInterface
{
public:
	enum ExitConditionsEnum
	{
		ATTACK_ExitIfOutsideRadius = 0x01,
		ATTACK_ExitIfExpiredDuration = 0x02,
		ATTACK_ExitIfNoUnitFound = 0x04
	};
	ExitConditions();
	virtual Bool shouldExit(const StateMachine *machine) const;
	int m_conditionsToConsider; // +0x04 (state +0x24)
	Coord3D m_center; // +0x08 (state +0x28)
	Real m_radiusSqr; // +0x14
	UnsignedInt m_attackGiveUpFrame; // +0x18 (state +0x38)
};
// (definition of ExitConditions::ExitConditions omitted)

class AIAttackState : public State
{
public:
	AIAttackState(StateMachine *machine, Bool follow, Bool attackingObject, Bool forceAttacking, AttackExitConditionsInterface *attackParameters);
private:
	unsigned char m_pad1C[0x50 - 0x1C]; // sizeof(AIAttackState) 0x50 (the operator new size)
};
class AIGuardAttackAggressorState : public State
{
public:
	AIGuardAttackAggressorState(StateMachine *machine);
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
private:
	AIGuardMachine *getGuardMachine() { return (AIGuardMachine *)getMachine(); }
	unsigned char m_pad20[0x24 - 0x20];
	ExitConditions m_exitConditions; // +0x20
	AIAttackState *m_attackState; // +0x3C
	Bool m_bfmeRestart; // +0x40
};
class AIGuardInnerState : public State
{
public:
	AIGuardInnerState(StateMachine *machine);
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
private:
	AIGuardMachine *getGuardMachine() { return (AIGuardMachine *)getMachine(); }
	unsigned char m_pad20[0x24 - 0x20];
	ExitConditions m_exitConditions; // +0x20
	AIAttackState *m_attackState; // +0x3C
	Bool m_bfmeRestart; // +0x40
	unsigned char m_pad41[0x44 - 0x41];
	UnsignedInt m_bfmeDeadline; // +0x44
};
class AIInternalMoveToState : public State
{
public:
	AIInternalMoveToState(StateMachine *machine, unsigned int hash);
	virtual StateReturnType update();
protected:
	unsigned char m_pad1C[0x4C - 0x1C];
};
class AIGuardReturnState : public AIInternalMoveToState
{
public:
	AIGuardReturnState(StateMachine *machine);
	virtual StateReturnType update();
private:
	AIGuardMachine *getGuardMachine() { return (AIGuardMachine *)getMachine(); }
	UnsignedInt m_nextReturnScanTime; // +0x4C
};
enum
{
	AI_GUARD_GET_CRATE = 5004
};
#define PATHFIND_CELL_SIZE_F 10.0f
#define STATE_SLEEP(n) ((StateReturnType)(n))
int GetGameLogicRandomValue(int low, int high, char *file, int line);
#define AIGUARD_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\AI\\AIGuard.cpp"
class AIGuardIdleState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
private:
	AIGuardMachine *getGuardMachine() { return (AIGuardMachine *)getMachine(); }
	unsigned char m_pad20[0x24 - 0x20];
	UnsignedInt m_nextEnemyScanTime; // +0x20
	Coord3D m_guardeePos; // +0x24
};
class AIGuardOuterState : public State
{
public:
	AIGuardOuterState(StateMachine *machine);
 virtual StateReturnType update();
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
private:
	AIGuardMachine *getGuardMachine() { return (AIGuardMachine *)getMachine(); }
	unsigned char m_pad20[0x24 - 0x20];
	ExitConditions m_exitConditions; // +0x20
	AIAttackState *m_attackState; // +0x3C
	Bool m_bfme40; // +0x40
};
// A second BFME 2 guard machine keeps AIGuardMachine's layout but its own inner
// scan (0x00369FDF, called where AIGuardIdleState::update calls 0x005433FA).
class Rva00369FDFGuardMachine : public AIGuardMachine
{
public:
	Bool lookForInnerTarget(void);
};
// Its idle state: vtable VA 0x00C17648 (slot 4 onEnter 0x0036803F, slot 6 update).
class Rva0036A979GuardIdleState : public State
{
public:
	virtual StateReturnType update();
private:
	Rva00369FDFGuardMachine *getGuardMachine() { return (Rva00369FDFGuardMachine *)getMachine(); }
	unsigned char m_pad20[0x24 - 0x20];
	UnsignedInt m_nextEnemyScanTime; // +0x20
	Coord3D m_guardeePos; // +0x24
};
// Second-system inner state onEnter (dump range 16 head, 0x36A3E9/315): same
// centre/area/radius/new-attack pattern as AIGuardInnerState::onEnter 0x54379B
// on the second guard machine layout (target +0x3C, team +0x40, area +0x44,
// pos +0x48, nemesis +0x68). Address-derived owner; retry from reference body.
class Rva0036A3E9GuardInnerState : public State
{
public:
	virtual StateReturnType onEnter();
private:
	Rva00369FDFGuardMachine *getGuardMachine() { return (Rva00369FDFGuardMachine *)getMachine(); }
	unsigned char m_pad20[0x24 - 0x20];
	ExitConditions m_exitConditions; // +0x20
	AIAttackState *m_attackState; // +0x3C
	Bool m_bfmeRestart; // +0x40
	unsigned char m_pad41[0x44 - 0x41];
	UnsignedInt m_bfmeDeadline; // +0x44
};

// (definition of ExitConditions::shouldExit omitted)


// (definition of AIGuardInnerState::AIGuardInnerState omitted)


// (definition of AIGuardOuterState::AIGuardOuterState omitted)


// (definition of AIGuardReturnState::AIGuardReturnState omitted)


// (definition of AIGuardAttackAggressorState::AIGuardAttackAggressorState omitted)


// The giant bird's guard states repeat the AIGuard layout with their own exit
// conditions class: vtable VA 0x00C17640, whose only slot is the shouldExit
// below. Its name is not known; it keeps Zero Hour's ExitConditions body
// (no rider redirect, planar distance from the goal's position).
class Rva00367F19ExitConditions : public AttackExitConditionsInterface
{
public:
	enum ExitConditionsEnum
	{
		ATTACK_ExitIfOutsideRadius = 0x01,
		ATTACK_ExitIfExpiredDuration = 0x02,
		ATTACK_ExitIfNoUnitFound = 0x04
	};
	Rva00367F19ExitConditions() : m_attackGiveUpFrame(0), m_conditionsToConsider(0), m_radiusSqr(0.0f)
	{
		m_center.x = 0.0f;
		m_center.y = 0.0f;
		m_center.z = 0.0f;
	}
	virtual Bool shouldExit(const StateMachine *machine) const;
	int m_conditionsToConsider; // +0x04
	Coord3D m_center; // +0x08
	Real m_radiusSqr; // +0x14
	UnsignedInt m_attackGiveUpFrame; // +0x18
};
class GiantBirdGuardOuterState : public State
{
public:
	GiantBirdGuardOuterState(StateMachine *machine);
	virtual StateReturnType onEnter();
	Rva00369FDFGuardMachine *getGuardMachine() { return (Rva00369FDFGuardMachine *)getMachine(); }
private:
	unsigned char m_pad20[0x24 - 0x20];
	Rva00367F19ExitConditions m_exitConditions; // +0x20
	AIAttackState *m_attackState; // +0x3C
	Bool m_bfme40; // +0x40
};
class GiantBirdGuardAttackAggressorState : public State
{
public:
	GiantBirdGuardAttackAggressorState(StateMachine *machine);
	virtual StateReturnType onEnter();
	Rva00369FDFGuardMachine *getGuardMachine() { return (Rva00369FDFGuardMachine *)getMachine(); }
private:
	unsigned char m_pad20[0x24 - 0x20];
	Rva00367F19ExitConditions m_exitConditions; // +0x20
	AIAttackState *m_attackState; // +0x3C
	Bool m_bfmeRestart; // +0x40
};
// Vtable VA 0x00C17978, the class whose onEnter is rowed above as
// Rva0036A3E9GuardInnerState::onEnter.
class GiantBirdGuardInnerState : public State
{
public:
	GiantBirdGuardInnerState(StateMachine *machine);
private:
	unsigned char m_pad20[0x24 - 0x20];
	Rva00367F19ExitConditions m_exitConditions; // +0x20
	AIAttackState *m_attackState; // +0x3C
	Bool m_bfmeRestart; // +0x40
};

// (definition of Rva00367F19ExitConditions::shouldExit omitted)


// (definition of GiantBirdGuardOuterState::GiantBirdGuardOuterState omitted)


// (definition of GiantBirdGuardAttackAggressorState::GiantBirdGuardAttackAggressorState omitted)


// (definition of GiantBirdGuardInnerState::GiantBirdGuardInnerState omitted)


// (definition of AIGuardAttackAggressorState::onEnter omitted)


// (definition of AIGuardInnerState::onEnter omitted)


// (definition of AIGuardInnerState::update omitted)


// (definition of AIGuardOuterState::onEnter omitted)


// (definition of AIGuardAttackAggressorState::update omitted)


// (definition of AIGuardAttackAggressorState::onExit omitted)


// Retail C69780 slot 5 shares 542C87 with the attack-aggressor state.
// The ZH inner-state exit drops its enter-state branch in BFME 2; the
// remaining attack lifetime and team-target reset are identical.
// (definition of AIGuardInnerState::onExit omitted)



// (definition of AIGuardOuterState::onExit omitted)


// (definition of AIGuardMachine::getStdGuardRange omitted)


// (definition of AIGuardReturnState::update omitted)


// (definition of AIGuardIdleState::onEnter omitted)


// (definition of AIGuardIdleState::update omitted)


// (definition of Rva0036A979GuardIdleState::update omitted)

// (definition of Rva0036A3E9GuardInnerState::onEnter omitted)


// BF1 f98983a7d AIGuardOuterState_update_Bfme is the semantic guide;
// full target543B5A..543CC4 proves all layout offsets and float evaluation.
// (definition of AIGuardOuterState::update omitted)


// BF1 f98983a7d guard attack-aggressor onEnter guide; target GiantBird
// name slot C177C8 and entry C177D0; native minimum chase duration is 8.0.
// (definition of GiantBirdGuardAttackAggressorState::onEnter omitted)


// Native C176A8 slot4 is GiantBirdGuardOuterState::onEnter; same guide
// as named guard sibling, with native 8.0 minimum chase duration.
StateReturnType GiantBirdGuardOuterState::onEnter( void )
{
	if (getGuardMachine()->getGuardMode() == GUARDMODE_GUARD_WITHOUT_PURSUIT)
	{
		// "patrol" mode does not follow targets outside the guard area.
		return STATE_SUCCESS;
	}

	Rva00369FDFGuardMachine *guard = getGuardMachine();
	Object* targetToGuard = guard->findTargetToGuardByID();
	Team* teamToGuard = guard->findTeamToGuardByID();
	Coord3D pos;
	if (targetToGuard)
		pos = *targetToGuard->getPosition();
	else if (teamToGuard)
		teamToGuard->getPosition(&pos);
	else
		pos = *getGuardMachine()->getPositionToGuard();

	Rva00369FDFGuardMachine *machine = getGuardMachine();
	Object* nemesis = TheGameLogic->findObjectByID(machine->getNemesisID()) ;
	if (nemesis == NULL) 
	{
		return STATE_SUCCESS;
	}
	Object *obj = machine->getOwner();

	Real range = TheAI->getAdjustedVisionRangeForObject(obj, AI_VISIONFACTOR_OWNERTYPE | AI_VISIONFACTOR_MOOD);

	const PolygonTrigger *area = getGuardMachine()->getAreaToGuard();
	if (area) 
	{
		if (getGuardMachine()->hasBfmeAreaCenter())
			pos = *getGuardMachine()->getBfmeAreaCenter();
		else
			area->getCenterPoint(&pos);
	}
	m_exitConditions.m_center = pos;
	m_exitConditions.m_radiusSqr = range * range;
	m_exitConditions.m_attackGiveUpFrame = (UnsignedInt)(TheGameLogic->getFrame() + ((8.0f > (Real)TheAI->getAiData()->m_guardChaseUnitFrames) ? 8.0f : (Real)TheAI->getAiData()->m_guardChaseUnitFrames));
	m_exitConditions.m_conditionsToConsider = (ExitConditions::ATTACK_ExitIfExpiredDuration | 
																								ExitConditions::ATTACK_ExitIfOutsideRadius | 
																								ExitConditions::ATTACK_ExitIfNoUnitFound);

	m_attackState = new AIAttackState(getMachine(), false, true, false, &m_exitConditions);

	m_attackState->getMachine()->setGoalObject(nemesis);

	StateReturnType returnVal = m_attackState->onEnter();
	if (returnVal == STATE_CONTINUE) {
		return STATE_CONTINUE;
	}

	// if we had no one to attack, we were successful, so go to the next state.
	return STATE_SUCCESS;
}
