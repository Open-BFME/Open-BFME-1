// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Include
// stlport
// Retail RVA 0x002B9B80, 330 bytes: DozerAIUpdate::aiDoCommand (the identity the MASM
// row game/masm_dumps/Rva002B9B80DozerAIDoCommand.asm carried). Replaces that dump.
//
// Port of the BFME 2 donor Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/
// DozerAIUpdateCtor.cpp (open-bfme-2 45afcff3; Zero Hour's DozerAIUpdate::aiDoCommand
// as BFME 2 kept it), its quoted headers inlined with BFME 1's string headers. The
// other donor bodies are left out. BFME 1 deltas, read from the retail body:
//   - MODELCONDITION_ACTIVELY_CONSTRUCTING is +0x118 bit 8 (bit 104).
//   - AIUpdateInterface is 0x340 bytes, so the DozerAIInterface base is at +0x340 in
//     the dozer.
//   - Primary vtable: privateRepair/ResumeConstruction at +0xA0/+0xA4 and
//     isAllowedToRespondToAiCommands at +0x210 (slots renumbered with bfme1Slot fillers).
//   - The kind-of test is the out-of-line Thing::isKindOf (ILT 0x0003251F) and the
//     model-condition notifier is Object::notifyModelConditionChanged (ILT 0x0002191D).
// Comments below this header are carried over from the donor views; addresses they
// quote are BFME 2 addresses.
#include <list>

// list<Drawable *> takes its nodes from the 12-byte pool at VA 0x00DBA5E0.
// The base constructor (0x00239BB0) and node creator (0x00239BD8) are spelled
// as stlport_list_drawable_base_ctor.cpp and InGameUISelectDrawable.cpp spell
// them, and the destructor (0x00239AF4) is defined once elsewhere, so this
// unit emits no stock allocator copy of them for the link to reject.
class Drawable;
class FreelistPool { public: void *pop(); };
extern FreelistPool g_freelistPool00DBA5E0;
namespace _STL {
template <> __declspec(noinline)
_List_base<Drawable *, allocator<Drawable *> >::_List_base(const allocator<Drawable *> &__a)
	: _M_node(__a, (_List_node<Drawable *> *)0)
{
	_List_node<Drawable *> *node = (_List_node<Drawable *> *)g_freelistPool00DBA5E0.pop();
	node->_M_next = node;
	node->_M_prev = node;
	_M_node._M_data = node;
}
template <> _List_base<Drawable *, allocator<Drawable *> >::~_List_base() throw(); // no EH state store before retail's calls
template <> __declspec(noinline) _List_node<Drawable *> *
list<Drawable *>::_M_create_node(Drawable *const &value)
{
	_List_node<Drawable *> *node = (_List_node<Drawable *> *)g_freelistPool00DBA5E0.pop();
	_Construct(&node->_M_data, value);
	return node;
}
}
#include "ascii_string.h"
#include "unicode_string.h"
// The speed-built 22-byte wide isEmpty body is owned by string_base_inline.cpp.
// The inline import view retains the caller's test and suppresses a local copy.
template<> __declspec(dllimport) inline bool StringBase<unsigned short>::isEmpty() const { return !m_data || m_data->length == 0; }

// Coord3D: shared header/view; no private copy.
#define COORD3D_VIEW_INLINE
#define COORD3D_VIEW_INLINE_ONLY
#include "Lib/Coord3D.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#define FALSE false
#define TRUE true

struct _iobuf;
typedef struct _iobuf FILE;

extern "C" int __cdecl fprintf(FILE *stream, const char *format, ...);

// BFME's logic random log file (data ledger 0x00DFEFF0).
extern "C" FILE *theLogicRandomLogFile;

// BFME 1's docking diagnostics switches (0x00DCBF44 and 0x00E03CA8).
// The first is defined here: retail .data holds 1 at RVA 0x009CBF44, right
// after this unit's header string tables; DozerAIUpdate::newTask (0x00489A07)
// and WorkerAIUpdate::newTask (0x004AADB1) test it.
bool g_bfmeDockingDesyncLog = true;
extern bool g_bfmeDockingTraceActive;

// Logic random log switch (data ledger 0x00A03745).
extern unsigned char g_00E03745;

#include "Lib/Coord2D.h"

enum ObjectID
{
	INVALID_ID = 0
};

extern "C" void *memset(void *dst, int val, unsigned size);

namespace _STL
{
template<unsigned N> struct _Base_bitset;
template<> struct _Base_bitset<4>
{
	void _M_do_or(const _Base_bitset<4> &other);
	unsigned long _M_w[4];
};
}

class Thing;
class ModuleData;
class BodyModuleInterface;
class Object;
class Drawable;
class Player;
class ThingTemplate;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

typedef UnsignedInt StateID;
enum { INVALID_STATE_ID = 999999 };

class State;
struct StateConditionInfo
{
	Bool (*test)(State *thisState, void *userData);
	StateID toStateID;
	void *userData;
};

// ---- inlined inputs/reference/open-bfme-2/reference/shims/bfme2_statemachine/StateMachineView.h
// Retail StateMachine table at VA 0x00C60740 and its 0x3C-byte object layout.
// Slots 9 and 10 share the zero-return body; their original names are unknown.

class Object;
class Xfer;
struct State;
struct StateConditionInfo;

class StateMachine
{
public:
    StateMachine(Object *owner, unsigned int nameKey, bool flag);
    virtual ~StateMachine();
protected:
    virtual void loadPostProcess() {}
    virtual const char *GetSnapshotName() const;
    virtual void xfer(Xfer *xfer);
public:
    virtual StateReturnType updateStateMachine();
    virtual void clear();
    virtual StateReturnType resetToDefaultState();
    virtual StateReturnType initDefaultState();
    virtual StateReturnType setState(int stateID);
    virtual int slot09() { return 0; }
    virtual int slot10() { return 0; }
    virtual bool isInAttackState() const;
    virtual bool isInBusyState() const;
    virtual void rva004D7395();
    virtual void setGoalObject(const Object *object);
    virtual void halt();

    void defineState(unsigned int id, State *state, unsigned int successID, unsigned int failureID, const StateConditionInfo *conditions = 0);
    Object *getOwner() const { return m_owner; }
    Object *getGoalObject();
    const Coord3D *locomotorGoalPosition() const { return &m_goalPosition; }
    void setGoalPosition(const Coord3D *position, float range);
    __declspec(dllimport) __forceinline unsigned int getCurrentStateID() const;
protected:
    State *m_currentState;
    unsigned char m_pad08[0x10 - 0x08];
    Object *m_owner;	// +0x10 in BFME 1
    unsigned int m_sleepTill;	// +0x14
    unsigned char m_pad18[0x24 - 0x18];
    Coord3D m_goalPosition;
    unsigned char m_pad30[0x3C - 0x30];
};

// BFME 2's StateMachine constructor (owner, name key, flag), rowed by
// address as ??0StateMachine@@QAE@PAVObject@@I_N@Z. Every
// caller passes the name as one dword, and only a scalar parameter gives
// retail's push of the immediate key, so this view takes the key as one.

struct State
{
public:
	virtual ~State();
	StateMachine *getMachine() const { return m_machine; }
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	Object *getMachineGoalObject() const { return m_machine->getGoalObject(); }
protected:
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
	unsigned char m_pad1C[0x20 - 0x1C];
};

// ZH's DozerPrimaryIdleState (rowed ctor 0x004886C7).
class Rva004886C7 : public State
{
public:
	Rva004886C7(StateMachine *machine);
private:
	unsigned char m_pad20[0x2C - 0x20];
};

// ZH's DozerActionState (machine, task) (rowed ctor 0x00488883).
class DozerActionState : public State
{
public:
	DozerActionState(StateMachine *machine, Int task);
private:
	unsigned char m_pad20[0x28 - 0x20];
};

// ZH's DozerPrimaryGoingHomeState (rowed ctor 0x0048896B).
class Rva0048896B : public State
{
public:
	Rva0048896B(StateMachine *machine);
};

enum DozerTask
{
	DOZER_TASK_INVALID = -1,
	DOZER_TASK_FIRST = 0,
	DOZER_TASK_BUILD = DOZER_TASK_FIRST,
	DOZER_TASK_REPAIR,
	DOZER_TASK_FORTIFY
};

enum DozerDockPoint
{
	DOZER_DOCK_POINT_START = 0,
	DOZER_DOCK_POINT_ACTION = 1,
	DOZER_DOCK_POINT_END = 2,
	DOZER_NUM_DOCK_POINTS
};

enum
{
	DOZER_PRIMARY_IDLE = 0,
	DOZER_PRIMARY_BUILD,
	DOZER_PRIMARY_REPAIR,
	DOZER_PRIMARY_FORTIFY,
	DOZER_PRIMARY_GO_HOME
};

class DozerPrimaryStateMachine : public StateMachine
{
public:
	DozerPrimaryStateMachine(Object *owner);
	virtual ~DozerPrimaryStateMachine();
protected:
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
public:

	static Bool isBuildMostImportant(State *thisState, void *userData);
	static Bool isRepairMostImportant(State *thisState, void *userData);
	static Bool isFortifyMostImportant(State *thisState, void *userData);
};

class ObjectModule
{
public:
	virtual ~ObjectModule();
protected:
	Object *getObject() const { return m_object; }
private:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void getBody();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
private:
	UnsignedInt m_nextCallFrameAndPhase; // +0x14
	Int m_indexInLogic; // +0x18
	Int m_reserved1C; // +0x1C
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT,
	CMD_FROM_AI
};

// BFME 2's command ids (aiDoCommand 0x002673F6's jump table); ZH's order
// up to AICMD_RESUME_CONSTRUCTION, BFME 2 inserts four before
// AICMD_MOVE_AWAY_FROM_UNIT.
enum AICommandType
{
	AICMD_REPAIR = 0x13,
	AICMD_RESUME_CONSTRUCTION = 0x14,
	AICMD_MOVE_AWAY_FROM_UNIT = 0x34
};

struct AICommandParms
{
	AICommandType m_cmd; // +0x00
	CommandSourceType m_cmdSource; // +0x04
	Coord3D m_pos; // +0x08
	Object *m_obj; // +0x14
};

class AICommandInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms) = 0;
	void aiIdle(CommandSourceType cmdSource);
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource);
	void aiFaceObject(Object *obj, CommandSourceType cmdSource);
};

class AIUpdateInterface24
{
public:
	virtual void onCollide(Object *obj, const Coord3D *loc, const Coord3D *normal) = 0;
};

// ZH's build sub-tasks; BFME 2 turns to face the site (2) before building.
enum DozerBuildSubTask
{
	DOZER_SELECT_BUILD_DOCK_LOCATION = 0,
	DOZER_MOVING_TO_BUILD_DOCK_LOCATION = 1,
	DOZER_FACING_BUILD_TARGET = 2,
	DOZER_DO_BUILD_AT_DOCK = 3
};

class Rva002390CB;

class DozerAIInterface
{
public:
	virtual void onDelete() = 0; // vslot 0
	virtual Real getRepairHealthPerSecond() const = 0; // vslot 1
	virtual Real getBoredTime() const = 0;
	virtual Real getBoredRange() const = 0;
	virtual Object *construct(const ThingTemplate *what, const Coord3D *pos, Real angle, Player *owningPlayer, Bool isRebuild, Int flags) = 0; // vslot 4
	virtual DozerTask getMostRecentCommand() = 0; // vslot 5
	virtual Bool isTaskPending(DozerTask task) = 0; // vslot 6
	virtual ObjectID getTaskTarget(DozerTask task) = 0; // vslot 7
	virtual Bool isAnyTaskPending() = 0; // vslot 8
	virtual DozerTask getCurrentTask() const = 0; // vslot 9
	virtual void setCurrentTask(DozerTask task) = 0;
	virtual Bool getIsRebuild() = 0; // vslot 11
	virtual void newTask(DozerTask task, Object *target) = 0; // vslot 12
	virtual void cancelTask(DozerTask task) = 0; // vslot 13
	virtual void internalTaskComplete(DozerTask task) = 0; // vslot 14
	virtual void internalCancelTask(DozerTask task) = 0; // vslot 15
	virtual void internalTaskCompleteOrCancelled(DozerTask task) = 0; // vslot 16
	virtual const Coord3D *getDockPoint(DozerTask task, DozerDockPoint point) = 0; // vslot 17
	virtual void setBuildSubTask(DozerBuildSubTask subTask) = 0; // vslot 18
	virtual DozerBuildSubTask getBuildSubTask() = 0; // vslot 19
	virtual Bool canAcceptNewRepair(Object *obj) = 0;
	virtual void createBridgeScaffolding(Object *bridgeTower) = 0; // vslot 21
	virtual void removeBridgeScaffolding(Object *bridgeTower) = 0;
	// BFME 2 hands over the drawable's sound record (by reference).
	virtual void startBuildingSound(const Rva002390CB &sound, ObjectID constructionSiteID) = 0; // vslot 23
	virtual void finishBuildingSound() = 0; // vslot 24
	// BFME 2's own slots. 26 (0x0048A15A) and 29 (0x00489DD1, which slot 28
	// shares) both work on the object whose id is at DozerAIUpdate +0x4A4.
	// Slot names 25, 26 and 31 are WorldBuilder's (DozerAIUpdate.cpp asserts).
	virtual void createPhantomStructure(const ThingTemplate *what, Player *owningPlayer, const Coord3D *pos, Real angle) = 0; // vslot 25
	virtual void makePhantomStructureReal() = 0; // vslot 26
	virtual void destroyPhantomStructure() = 0; // vslot 27
	virtual Object *slot28() = 0;
	virtual Object *rva00489DD1() = 0; // vslot 29
	virtual void slot30() = 0;
	virtual void notifyConstructionComplete() = 0; // vslot 31
};

class Waypoint;
class Rva0035149F;
class Team;
class DamageInfo;
struct Rva00264D81Arg;
class PolygonTrigger;
class CommandButton;
class Rva00263404Source;
class PathfindServicesInterface;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
// ---- inlined inputs/reference/open-bfme-2/Code/GameEngine/Include/Common/BfmeXfer.h
// Xfer: the shared BFME2 Xfer interface view, adopted by tools/header_adopt_lane.py.
// The declaration is the private view 354 ledger units carried verbatim
// (class_views layout fb2837e782): retail-dispatched virtual slots in vtable
// order, the out-of-line Version1 (0x000053EE), SkipBadBlock (0x0050B238),
// XferRawBytes (0x0060B886) and XferEnum (0x0060BBD5) spellings the ledger rows use.
// reverse/class_contracts/Xfer.json leaves slots 4-38 undecided (their names
// differ across views); this header keeps the majority spelling. Slot names
// are not identity claims beyond the rows above and the notes below.
//
// Slots 5-7 are _purecall in Xfer's own table (RVA 0x007BB910). XferLoad's table
// (RVA 0x0087AF18) fills them with 0x0060C629 int(const char *), 0x0060C469
// void() and 0x0060C6F6 void(const char *) (ledger rows in xfer_load.cpp);
// WorldBuilder names the overriders XferLoad::BeginBlock, ::EndBlock and
// ::SkipBlock (XferSave and XferSaveAsText: EndBlock, SkipBlock), so the
// base slots carry those names and signatures.
// Slot 11 is _purecall too and sits inside the operator== run (MSVC keeps
// overloads together), so it is one more operator== overload. Its operand
// is the container type name callers pass as a string literal ("std::list",
// "std::vector", ...): the 59 private views that call it agree on
// `const char *const &`, and XferSave's slot-11 body (0x0060CE41) reads the
// interned string pointer through the reference.
//
// The operand types (Snapshot, AsciiString, the Coord/Region value types,
// RealRange, the RGBA colors, PooledString) are deliberately
// not forward-declared here: units declare them with their own class-keys
// before including this header; a forward declaration here could disagree
// with the class-key a unit already uses.
#ifndef BFME_XFER_H
#define BFME_XFER_H

class Xfer
{
public:
	class Version;

	// XferSaveAsText inlines base construction without emitting another
	// external constructor; System/Xfer.cpp owns the out-of-line body.
#ifdef BFME_XFER_INLINE_CTOR
	__declspec(dllimport) __forceinline Xfer() {}
#else
	Xfer();
#endif
	// Retail's scalar deleting destructor (Xfer.cpp) calls ~Xfer instead of
	// inlining its vtable restore; only the defining TU sees the body.
	// XferVectorDeletingDtor.cpp defines BFME_XFER_INLINE_DTOR: retail's
	// vector deleting destructor inlines the vptr store.
#ifdef BFME_XFER_INLINE_DTOR
	virtual ~Xfer();
#else
	__declspec(noinline) virtual ~Xfer();
#endif

	void Version1();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual int BeginBlock(const char *name) = 0;
	virtual void EndBlock() = 0;
	virtual void SkipBlock(const char *name) = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(const char *const &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

#endif // BFME_XFER_H
enum GuardMode;
enum NameKeyType;
namespace _STL { template<class T, class A> class vector; }

class AIUpdateInterface : public UpdateModule, public AICommandInterface, public AIUpdateInterface24
{
public:
	AIUpdateInterface(Thing *thing, const ModuleData *moduleData);
	virtual void onCollide(Object *obj, const Coord3D *loc, const Coord3D *normal);
	// Primary vtable slots 1-92 (slot 0 is the destructor).
protected:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
public:
	virtual void xfer(Xfer *xfer);
	virtual NameKeyType getModuleNameKey() const;
	virtual void onObjectCreated();
	virtual void v06() {}
	virtual void v07() {}
	virtual void onDelete();
	virtual void v09(int, int) {}
	virtual int v10() { return 0; }
	virtual int v11() { return 0; }
	virtual int v12() { return 0; }
protected:
	virtual void privateMoveToPosition(Coord3D const *, Real, CommandSourceType);
	virtual void privateAttackMoveToPositionAndOrientation(Coord3D const *, Real, Int, CommandSourceType);
	virtual void bfmePrivateCommand01(Object *, CommandSourceType);
	virtual void privateMoveToPositionSA(Coord3D const *, CommandSourceType);
	virtual void privateMoveToPositionAmphibious(Coord3D const *, Int, CommandSourceType);
	virtual void bfmePrivateCommand48(Object *, CommandSourceType);
	virtual void privateMoveToAndEvacuate(Coord3D const *, CommandSourceType);
	virtual void privateMoveToAndEvacuateAndExit(Coord3D const *, CommandSourceType);
	virtual void bfmePrivateCommand38(Coord3D const *, CommandSourceType);
	virtual void bfmePrivateCommand41(Coord3D const *, CommandSourceType);
	virtual void bfmePrivateCommand42(Object *, CommandSourceType);
	virtual void privateIdle(CommandSourceType);
	virtual void privateTightenToPosition(Coord3D const *, CommandSourceType);
	virtual void privateFollowWaypointPath(Waypoint const *, CommandSourceType);
	virtual void privateFollowWaypointPathAsTeam(Waypoint const *, CommandSourceType);
	virtual void privateFollowWaypointPathExact(Waypoint const *, CommandSourceType);
	virtual void privateFollowWaypointPathAsTeamExact(Waypoint const *, CommandSourceType);
	virtual void privateFollowPath(Rva0035149F const *, Object *, CommandSourceType, Bool);
	virtual void privateFollowPathAppend(Coord3D const *, CommandSourceType);
	virtual void privateAttackObject(Object *, Int, CommandSourceType);
	virtual void bfmePrivateCommand39(Object *, CommandSourceType);
public:
protected:
	virtual void privateForceAttackObject(Object *, Int, CommandSourceType);
	virtual void privateAttackTeam(Team const *, Int, CommandSourceType);
	virtual void privateAttackPosition(Coord3D const *, Int, CommandSourceType);
	virtual void bfmePrivateCommand49(Object *, CommandSourceType);
	virtual void privateAttackFollowWaypointPath(Waypoint const *, Int, Bool, CommandSourceType);
	virtual void privateHunt(CommandSourceType);
public:
	virtual void privateRepair(Object *obj, CommandSourceType cmdSource); // vslot 44 (+0xB0)

protected:
	virtual void privateResumeConstruction(Object *obj, CommandSourceType cmdSource); // vslot 45 (+0xB4)
public:
protected:
	virtual void privateGetHealed(Object *, CommandSourceType);
	virtual void privateGetRepaired(Object *, CommandSourceType);
	virtual void privateEnter(Object *, CommandSourceType);
	virtual void bfmePrivateCommand3D(Object *, CommandSourceType);
	virtual void privateMoveToObject(Object *, CommandSourceType);
	virtual void privateDock(Object *, CommandSourceType);
	virtual void privateHarvest(Coord3D const *, CommandSourceType);
	virtual void privateExitInstantly(Object *, CommandSourceType);
	virtual void bfmePrivateCommand4B(Object *, Coord3D const *, CommandSourceType);
	virtual void bfmePrivateCommand4D(Object *, Rva0035149F const *, CommandSourceType);
	virtual void bfmePrivateCommand3E(Object *, CommandSourceType);
	virtual void bfmePrivateCommand4A(Object *, Coord3D const *, CommandSourceType);
	virtual void bfmePrivateCommand4C(Object *, Rva0035149F const *, CommandSourceType);
	virtual void bfmePrivateCommand54(Object *, Coord3D const *, CommandSourceType);
public:
	virtual void rva0026DDED(int cond, CommandSourceType cmd);
protected:
	virtual void privateGoProne(DamageInfo const *, CommandSourceType);
	virtual void privateGuardTunnelNetwork(Int, CommandSourceType);
	virtual void privateGuardPosition(Coord3D const *, GuardMode, CommandSourceType);
	virtual void privateGuardObject(Object *, GuardMode, CommandSourceType);
	virtual void bfmePrivateCommand20(Rva00264D81Arg const *, GuardMode, CommandSourceType);
	virtual void privateGuardRetaliate(Object *, Coord3D const *, Int, CommandSourceType);
	virtual void privateGuardAreaFromPosition(PolygonTrigger const *, GuardMode, CommandSourceType, Coord3D const *);
	virtual void privateAttackArea(PolygonTrigger const *, CommandSourceType);
	virtual void privateFaceObject(Object *, CommandSourceType);
	virtual void privateFacePosition(Coord3D const *, CommandSourceType);
public:
	virtual void rva00262EFF(void *, void *, void *);
protected:
	virtual void privateCommandButton(CommandButton const *, CommandSourceType);
	virtual void privateCommandButtonPosition(CommandButton const *, Coord3D const *, CommandSourceType);
public:
	virtual void v74(int, int, int) {}
	virtual void bfmeGoCSG(void *, void *);
	virtual void bfmeGoCSA(void *);
protected:
	virtual void bfmePrivateCommand53(CommandSourceType);
public:
	virtual void bfmeGoCSH(void *, void *);
	virtual void bfmeGoCSD(void *, void *);
protected:
	virtual void bfmePrivateCommand31(Int, CommandSourceType);
	virtual void privateMoveAwayFromUnit(Object *, Coord3D const *, CommandSourceType);
	virtual void bfmePrivateCommand3C(Object *, CommandSourceType);
public:
	virtual void bfmeGoCSE(void *, void *);
protected:
	virtual void rva002630FD(Int);
public:
	virtual void bfmeGoCSF(void *, void *);
protected:
	virtual void rva0026316B(void *, Int);
	virtual void rva002631A6(Real, Int);
public:
	virtual void v88() {}
	virtual void v89() {}
	virtual Bool v90() const { return false; }
	virtual Bool isBusy() const;
	virtual DozerAIInterface *getDozerAIInterface(); // vslot 93 (+0x174)
	virtual const DozerAIInterface *getDozerAIInterface() const { return 0; } // vslot 92 (+0x170): MSVC orders overloads in reverse
	virtual void *v94() { return 0; }
	virtual void *v95() { return 0; }
	virtual void *v96() { return 0; }
	virtual void *v97() { return 0; }
	virtual void *v98() { return 0; }
	virtual void *v99() { return 0; }
	virtual void *v100() { return 0; }
	virtual void *v101() { return 0; }
	virtual void *v102() { return 0; }
	virtual void joinTeam();
	virtual Int rva0026E988();
	virtual Int rva0026E999();
	virtual int v106(const Object *) const { return 0; }
	virtual Bool v107() const { return true; }
	virtual Bool v108() const { return true; }
	virtual unsigned int v109() const { return 0; }
	virtual Bool isIdle() const; // vslot 110 (+0x1B8)
	virtual Bool rva00262D8F() const;
	virtual Bool isClearingMines() const;
	virtual Bool rva00262DA3() const;
	virtual Bool rva00262DAB() const;
	virtual Bool rva00262DBF() const;
	virtual Bool rva00262D7B() const;
	virtual void doQuickExit(_STL::vector<Coord3D, _STL::allocator<Coord3D> > const *);
	virtual const Coord3D *v118() const { return &m_guardLocation; }
	virtual unsigned int v119() const { return m_guardObject; }
	virtual const PolygonTrigger *v120() const { return m_guardArea; }
	virtual int v121() const { return m_guardTarget; }
	virtual void v122(int target) { m_guardTarget = target; }
	virtual int v123() const { return m_previousGuardTarget; }
	virtual void clearGuardTargetType();
	virtual int v125() const { return m_guardMode; }
	virtual Object *construct(const ThingTemplate *what, const Coord3D *pos, Real angle, Player *owningPlayer, Bool isRebuild, Int flags); // vslot 126 (+0x1F8)
	virtual Object *getEnterTarget();
	virtual void v144() {}
	virtual void rva00267E46();
	virtual Bool v146() const { return true; }
	virtual void rva00488CF0(); // vslot 147 (+0x24C), empty in the base (0x000B3FD0)
	virtual void bfme1Slot128(); virtual void bfme1Slot129(); virtual void bfme1Slot130(); virtual void bfme1Slot131();
	virtual Bool isAllowedToRespondToAiCommands(const AICommandParms *parms) const; // BFME 1 vslot 132 (+0x210)
	virtual void aiDoCommand(const AICommandParms *parms);
	Bool isPathAvailable(const Coord3D *destination) const;
	void ignoreObstacle(const Object *obj);
	Bool findNearestLabeledContactPointOnTarget(Object *target, Coord3D *result, const Coord3D *workingPosition, Bool skipCollideTest);
protected:
	virtual ~AIUpdateInterface();
private:
	unsigned char m_pad28[0x48 - 0x28];
	CommandSourceType m_lastCommandSource;
	int m_guardMode;
	int m_currentGuardTarget;
	int m_previousGuardTarget;
	Coord3D m_guardLocation;
	unsigned int m_guardObject;
	const PolygonTrigger *m_guardArea;
	int m_guardTarget;
	unsigned char m_pad70[0x1FC - 0x70];
	int m_locomotorGoalType;
	unsigned char m_pad200[0x340 - 0x200];	// BFME 1 AIUpdateInterface is 0x340 bytes
};

enum ModelConditionFlagType
{
	MODELCONDITION_AWAITING_CONSTRUCTION = 67,
	MODELCONDITION_PARTIALLY_CONSTRUCTED = 68,
	MODELCONDITION_ACTIVELY_BEING_CONSTRUCTED = 69, // +0x114 bit 5
	MODELCONDITION_ACTIVELY_CONSTRUCTING = 104, // BFME 1: +0x118 bit 8
	MODELCONDITION_PHANTOM_STRUCTURE = 109 // +0x118 bit 13
};

class ModelConditionFlags
{
public:
	unsigned int test(unsigned int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(unsigned int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
	void clear(unsigned int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};

// The two model condition mask builders (19 dwords each).
class Rva001E4912
{
public:
	Rva001E4912 *rva001E4912(int unused, unsigned int bit1, unsigned int bit2);
private:
	unsigned int m_words[19];
};

class Rva0028F59A
{
public:
	Rva0028F59A(int unused, int bit);
private:
	unsigned int m_words[19];
};

// The four-bit status mask Rva00489256Do sets.
class Rva00346BC0
{
public:
	Rva00346BC0(unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4, unsigned int a5);
private:
	unsigned int m_bits[4];
};

class GeometryInfo
{
public:
	Real getMajorRadius() const { return m_majorRadius; }
	__declspec(dllimport) Real getBoundingSphereRadius() const { return m_boundingSphereRadius; }
private:
	unsigned char m_pad00[0x10];
	Real m_majorRadius; // +0x10
	Real m_boundingSphereRadius; // +0x14 (calcBoundingStuff 0x006BE700)
	unsigned char m_pad18[0x5C - 0x18];
};

// BFME 2's kind-of bit names (the name table at .rdata 0x009BBE18).
enum KindOfType
{
	KINDOF_DOZER = 14,
	KINDOF_SWARM_DOZER = 15,
	KINDOF_BRIDGE = 22,
	KINDOF_BRIDGE_TOWER = 24,
	KINDOF_NO_COLLIDE = 30,
	KINDOF_DO_NOT_CLASSIFY = 149
};

class ThingTemplate
{
public:
	const AsciiString &getName() const { return m_name; }
	__forceinline UnsignedInt isKindOf(KindOfType t) const { return m_kindOf[t >> 5] & (1U << (t & 31)); }
	Int rva0033A69A(const Player *player, Int builder, Int a3) const;
	Int calcTimeToBuild(const Player *player, Int builder, Int a3) const;
private:
	unsigned char m_pad000[0x64];
	AsciiString m_name; // +0x64
	unsigned char m_pad068[0x108 - 0x68];
	UnsignedInt m_kindOf[7]; // +0x108 (218 kind-of bits)
};

class Thing
{
public:
	virtual ~Thing();
	Bool isKindOf(KindOfType t) const;	// rowed 0x000A2CF0, called through ILT 0x0003251F
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_cachedPos; }
	Real getOrientation() const { return m_cachedAngle; }
	Drawable *getDrawable() const;
	void setPosition(const Coord3D *pos);
	void setOrientation(Real angle);
private:
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_cachedPos; // +0x38
	Real m_cachedAngle; // +0x44
};

// BFME 2's object status bit names (the name table at .rdata 0x009A5F30).
enum ObjectStatusTypes
{
	OBJECT_STATUS_UNDER_CONSTRUCTION = 2,
	OBJECT_STATUS_RECONSTRUCTING = 21,
	OBJECT_STATUS_PENDING_CONSTRUCTION = 87,
	OBJECT_STATUS_PHANTOM_STRUCTURE = 88
};

// ZH's disabled types, in its order.
enum DisabledType
{
	DISABLED_UNMANNED = 5
};

class Module;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum DamageType { DAMAGE_08 = 8 };
enum DeathType { DEATH_NORMAL = 0 };

class Object : public Thing
{
public:
	void kill(DamageType damageType, DeathType deathType); // 0x002984D4
	void rva0028BAC0(); // 0x0028BAC0
	ObjectID getID() const { return m_id; }
	void setBuilder(const Object *builder);
	const GeometryInfo &getGeometryInfo() const { return m_geometryInfo; }
	Bool isUsingAirborneLocomotor() const;
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	ObjectID getSoleHealingBenefactor() const;
	Real rva002C97E8(const Coord3D *a, const Coord3D *b) const;
	void rva0028AB4E() const;
	void rva0028CFB2(const int *clear, const int *set);
	void rva0028CDEB(const Rva00346BC0 &mask, bool set);
	Bool get454() const { return m_454; }
	Player *getControllingPlayer() const;
	void rva0028DCC4();
	void notifyModelConditionChanged();
	__forceinline void clearModelConditionState(ModelConditionFlagType mc)
	{
		if (m_modelConditionFlags.test(mc) != 0)
		{
			m_modelConditionFlags.clear(mc);
			notifyModelConditionChanged();
		}
	}
	__forceinline void setModelConditionState(ModelConditionFlagType mc)
	{
		if (m_modelConditionFlags.test(mc) == 0)
		{
			m_modelConditionFlags.set(mc);
			notifyModelConditionChanged();
		}
	}
	void setProducer(Object *obj);
	ObjectID getProducerID() const { return m_producerID; }
	ObjectID getBuilderID() const { return m_builderID; }
	__forceinline UnsignedInt isDisabledByType(DisabledType type) const { return m_disabledMask & (1U << type); }
	Bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
	// LINK: TU-unique helper (see Rva004E669APoint/getPosition pattern).
	// The generic Object::getConstructionPercent copy in this TU compiles
	// x87 (TU flags) while the three /arch:SSE siblings emit movss; the
	// mismatch loses link order. Rebinding in-TU uses to this unique copy
	// (inlined at all use sites) drops the loser symbol. No flags touched.
	Real bfme_construction_percent() const { return m_constructionPercent; }
	__declspec(dllimport) void setConstructionPercent(Real percent) { m_constructionPercent = percent; }
	void setStatus(ObjectStatusTypes status, Bool set);
protected:
	friend class DozerActionDoActionState;
	Module *findModule(NameKeyType key) const;
public:
	void rva001E42F2(const int *clear);
	void setSpecialModelConditionState(ModelConditionFlagType mc, UnsignedInt frames);
	Bool isLocallyControlled() const;
	void *getDisplayName();
	// ZH's attemptHealingFromSoleBenefactor (amount, source, duration).
	Bool attemptHealingFromSoleBenefactor(Real amount, const Object *source, UnsignedInt duration);
	Int get45C() const { return m_45C; }
private:
	unsigned char m_pad048[0x74 - 0x48];
	ObjectID m_id; // +0x74
	ObjectID m_producerID; // +0x78
	ObjectID m_builderID; // +0x7C
	unsigned char m_pad080[0xA8 - 0x80];
	GeometryInfo m_geometryInfo; // +0xA8
	unsigned char m_pad104[0x10C - 0x104];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
	unsigned char m_pad158[0x1C8 - 0x158];
	UnsignedInt m_disabledMask; // +0x1C8
	unsigned char m_pad1CC[0x254 - 0x1CC];
	BodyModuleInterface *m_body; // +0x254
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x280 - 0x25C];
	Real m_constructionPercent; // +0x280
	unsigned char m_pad284[0x324 - 0x284];
public:
	Real m_buildCost; // +0x324
private:
	unsigned char m_pad328[0x438 - 0x328];
	unsigned char m_privateStatus; // +0x438, bit 0 effectively dead
	unsigned char m_pad439[0x454 - 0x439];
	Bool m_454; // +0x454
	unsigned char m_pad455[0x45C - 0x455];
	Int m_45C; // +0x45C
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	void destroyObject(Object *obj);
	UnsignedInt getFrame() const { return m_frame; }
	void rva0023D0C2(Object *obj, Int handle);
private:
	unsigned char m_pad00[0x40];
	UnsignedInt m_frame; // +0x40
};

extern GameLogic *TheGameLogic;

class WWMath
{
public:
	static float __fastcall Inv_Sqrt(float val);
};

// WWMath's Vector3 (its inline members, WWINLINE as __forceinline).
class Vector3
{
public:
	float X;
	float Y;
	float Z;

	__forceinline Vector3(void) {}
	__forceinline Vector3(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; }
	__forceinline Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }
	__forceinline Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
	__forceinline float Length2(void) const { return X*X + Y*Y + Z*Z; }
	__forceinline void Normalize(void)
	{
		float len2 = Length2();
		if (len2 != 0.0f)
		{
			float oolen = WWMath::Inv_Sqrt(len2);
			X *= oolen;
			Y *= oolen;
			Z *= oolen;
		}
	}
	__forceinline friend Vector3 operator*(const Vector3 &a, float k) { return Vector3((a.X * k), (a.Y * k), (a.Z * k)); }
};

struct FindPositionOptions
{
	FindPositionOptions() : flags(0), minRadius(0.0f), maxRadius(0.0f), startAngle(-99999.9f),
		maxZDelta(1e10f), ignoreObject(0), sourceToPathToDest(0), relationshipObject(0) {}
	UnsignedInt flags;
	Real minRadius;
	Real maxRadius;
	Real startAngle;
	Real maxZDelta;
	const Object *ignoreObject;
	const Object *sourceToPathToDest;
	const Object *relationshipObject;
};

class PartitionManager
{
public:
	static Bool findPositionAround(const Coord3D *center, const FindPositionOptions *options, Coord3D *result);
};

enum BridgeTowerType
{
	BRIDGE_TOWER_FROM_LEFT = 0,
	BRIDGE_MAX_TOWERS = 4
};

class BridgeBehaviorInterface
{
public:
	virtual void slot0();
	virtual ObjectID getTowerID(BridgeTowerType type); // vslot 1
	virtual void createScaffolding();
	virtual void removeScaffolding();
	virtual Bool isScaffoldInMotion(); // vslot 4
};

class BridgeBehavior
{
public:
	static BridgeBehaviorInterface *getBridgeBehaviorInterfaceFromObject(Object *obj);
};

inline Real sqr(Real x)
{
	return x * x;
}

inline void zeroCoord(Coord3D &c)
{
	c.x = 0.0f;
	c.y = 0.0f;
	c.z = 0.0f;
}

// The dock point element: an out-of-line empty ctor and dtor (retail's
// __ehvec_ctor arguments, the ICF-folded 0x0047A6A9 and 0x000B3FD0).
struct Rva004894F5DockPoint
{
	Rva004894F5DockPoint() {}
	~Rva004894F5DockPoint() {}
	Bool valid;
	Coord3D location;
};

class DozerAIUpdate : public AIUpdateInterface, public DozerAIInterface
{
public:
	virtual UpdateSleepTime update(); // UpdateModuleInterface slot 0, the rowed override
	DozerAIUpdate(Thing *thing, const ModuleData *moduleData);
	virtual NameKeyType getModuleNameKey() const;
	virtual void onDelete();
	virtual Object *construct(const ThingTemplate *what, const Coord3D *pos, Real angle, Player *owningPlayer, Bool isRebuild, Int flags);
	virtual void finishBuildingSound();
	virtual void createPhantomStructure(const ThingTemplate *what, Player *owningPlayer, const Coord3D *pos, Real angle);
	virtual void makePhantomStructureReal();
	virtual void destroyPhantomStructure();
	virtual Object *rva00489DD1();
	virtual void notifyConstructionComplete();
	virtual void rva00488CF0();
	virtual void newTask(DozerTask task, Object *target);
	virtual void cancelTask(DozerTask task);
	virtual void internalTaskCompleteOrCancelled(DozerTask task);
	virtual const Coord3D *getDockPoint(DozerTask task, DozerDockPoint point);
	virtual void aiDoCommand(const AICommandParms *parms);
	void makePhantomStructureInert();
	void makePhantomStructureNotInert();
private:
	enum { DOZER_NUM_TASKS = 3 };

	struct DozerTaskInfo
	{
		ObjectID m_targetObjectID;
		UnsignedInt m_taskOrderFrame;
	};

	void createMachines();

protected:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
	virtual void privateRepair(Object *obj, CommandSourceType cmdSource);
	virtual void privateResumeConstruction(Object *obj, CommandSourceType cmdSource);
	Bool findGoodBuildOrRepairPosition(const Object *me, const Object *target, Coord3D &positionOut);
	Object *findGoodBuildOrRepairPositionAndTarget(Object *me, Object *target, Coord3D &positionOut);
	virtual ~DozerAIUpdate();

private:
	DozerTaskInfo m_task[DOZER_NUM_TASKS]; // +0x3E8
	DozerPrimaryStateMachine *m_dozerMachine; // +0x400
	Int m_currentTask; // +0x404
	Int m_408; // +0x408
	Bool m_isRebuild; // +0x40C
	Rva004894F5DockPoint m_dockPoint[DOZER_NUM_TASKS][DOZER_NUM_DOCK_POINTS]; // +0x410
	Int m_buildSubTask; // +0x4A0
	Int m_4A4; // +0x4A4
};

// (definition of DozerAIUpdate::DozerAIUpdate omitted)


// Retail 0x0048898C: stores the vtable 0x0084B668 this constructor installs
// (slot 0 is the deleting destructor 0x00488EE0, slot 2 the class-name getter
// 0x00488997) and tail-calls ~StateMachine.
// (definition of DozerPrimaryStateMachine::~DozerPrimaryStateMachine omitted)


// Retail slot 3 of vtable 0x0084B668 is 0x0033FB0B, the identical-code fold of
// this override with the other StateMachine xfers rowed as Rva0033FB0B.
// (definition of DozerPrimaryStateMachine::xfer omitted)


// (definition of DozerPrimaryStateMachine::DozerPrimaryStateMachine omitted)


// (definition of DozerPrimaryStateMachine::isBuildMostImportant omitted)


// (definition of DozerPrimaryStateMachine::isRepairMostImportant omitted)


// (definition of DozerPrimaryStateMachine::isFortifyMostImportant omitted)


// (definition of DozerAIUpdate::createMachines omitted)


// (definition of DozerAIUpdate::onDelete omitted)


// (definition of DozerAIUpdate::findGoodBuildOrRepairPositionAndTarget omitted)


// (definition of DozerAIUpdate::newTask omitted)


// (definition of DozerAIUpdate::findGoodBuildOrRepairPosition omitted)


//-------------------------------------------------------------------------------------------------
void DozerAIUpdate::aiDoCommand(const AICommandParms *parms)
{
	//
	// anytime we get a command, just remove any model condition that has us actively building
	// if we need to show that, that bit will be set anyway again during the build process
	//
	getObject()->clearModelConditionState(MODELCONDITION_ACTIVELY_CONSTRUCTING);

	if (!isAllowedToRespondToAiCommands(parms))
		return;

	// if we haven't made the dozer machine yet, do so now
	createMachines();

	switch (parms->m_cmd)
	{
		case AICMD_MOVE_AWAY_FROM_UNIT:
		{
			Object *otherObj = parms->m_obj;
			Bool otherIsDozer = false;
			if (otherObj)
			{
				otherIsDozer = otherObj->isKindOf(KINDOF_DOZER);
			}
			// We only want to do this if we aren't busy doing dozer things. jba.
			// Or if the other guy is a dozer too.
			if (!otherIsDozer && getCurrentTask() != DOZER_TASK_INVALID)
			{
				return; // just ignore it.  jba.
			}
			// issue the command
			AIUpdateInterface::aiDoCommand(parms);
			break;
		}

		// --------------------------------------------------------------------------------------------
		case AICMD_REPAIR:
		{
			// if we have no task right now, go idle so we can immediately respond to this
			if (getCurrentTask() == DOZER_TASK_INVALID)
				aiIdle(CMD_FROM_AI);

			// do the repair
			privateRepair(parms->m_obj, parms->m_cmdSource);
			break;
		}

		// --------------------------------------------------------------------------------------------
		case AICMD_RESUME_CONSTRUCTION:
		{
			// if we have no task right now, go idle so we can immediately respond to this
			if (getCurrentTask() == DOZER_TASK_INVALID)
				aiIdle(CMD_FROM_AI);

			// do the command
			privateResumeConstruction(parms->m_obj, parms->m_cmdSource);
			break;
		}

		// --------------------------------------------------------------------------------------------
		default:
		{
			// if this is from the player, cancel our current task
			if (parms->m_cmdSource == CMD_FROM_PLAYER && getCurrentTask() != DOZER_TASK_INVALID)
				cancelTask(getCurrentTask());

			// issue the command
			AIUpdateInterface::aiDoCommand(parms);

			// when a player issues commands, this will cause the dozer to re-evaluate what it's doing
			if (parms->m_cmdSource == CMD_FROM_PLAYER)
				m_dozerMachine->resetToDefaultState();
			break;
		}
	}
}

class Drawable
{
public:
	void rva00274176(Bool flag);
	void fadeIn(UnsignedInt frames);
	void fadeOut(UnsignedInt frames);
	Rva002390CB rva00274CD8(const AsciiString &name);
	Bool rva002765D4(UnicodeString *name);
	void setDrawableHidden(Bool hide);
	void setDrawableOpacity(Real value) { m_explicitOpacity = value; }
private:
	unsigned char m_pad00[0xB0];
	Real m_explicitOpacity; // +0xB0
};

class InGameUI
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
	// cl 7.1 lays overloaded virtuals out in reverse declaration order:
	// message(AsciiString) is vslot 15 (+0x3C), message(UnicodeString) 16.
	virtual void message(UnicodeString format, ...);
	virtual void message(AsciiString stringManagerLabel, ...);
	virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
	virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49();
	virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55(); virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63(); virtual void v64(); virtual void v65(); virtual void v66();
	virtual void deselectDrawable(Drawable *draw); // vslot 67 (+0x10C)
};

extern InGameUI *TheInGameUI;

class AiOrdersManager
{
public:
	void clearOrders(Int a, Int b);
};

extern AiOrdersManager *TheAiOrdersManager;

bool __cdecl rva004884B7(Object *obj);

// ZH's DozerActionMoveToActionPosState (rowed ctor 0x0048851B, vtable
// 0x0084B448).
class DozerActionMoveToActionPosState : public State
{
public:
	virtual StateReturnType update();
private:
	DozerTask m_task; // +0x20
};

template <class T>
inline const T &bfmeMax(const T &a, const T &b)
{
	return (a > b) ? a : b;
}

static const Real MIN_ACTION_TOLERANCE = 70.0f;

// (definition of Rva00489256Do omitted)


// (definition of DozerActionMoveToActionPosState::update omitted)


class DozerActionPickActionPosState : public State
{
public:
	virtual StateReturnType update();
private:
	DozerTask m_task; // +0x20
};

// (definition of DozerActionPickActionPosState::update omitted)


// ZH's dozer action states (rowed ctors 0x004884ED, 0x0048851B, 0x00488545).
class Rva004884ED : public State
{
public:
	Rva004884ED(StateMachine *machine, Int task);
private:
	unsigned char m_pad20[0x28 - 0x20];
};

class Rva0048851B : public State
{
public:
	Rva0048851B(StateMachine *machine, Int task);
private:
	unsigned char m_pad20[0x24 - 0x20];
};

class Rva00488545 : public State
{
public:
	Rva00488545(StateMachine *machine, Int task);
private:
	unsigned char m_pad20[0x28 - 0x20];
};

enum
{
	DOZER_ACTION_PICK_ACTION_POS = 0,
	DOZER_ACTION_MOVE_TO_ACTION_POS,
	DOZER_ACTION_DO_ACTION
};

enum
{
	EXIT_MACHINE_WITH_SUCCESS = 9998,
	EXIT_MACHINE_WITH_FAILURE = 9999
};

// ZH's DozerActionStateMachine.
class Rva004885DE : public StateMachine
{
public:
	Rva004885DE(Object *owner, Int task);
protected:
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
protected:
	Int m_task; // +0x3C
};

// (definition of Rva004885DE::Rva004885DE omitted)


typedef UnsignedInt AudioHandle;

class AudioManager
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26();
	virtual void removeAudioEvent(AudioHandle handle); // vslot 27 (+0x6C)
};

extern AudioManager *TheAudio;

// Folded into FoundationAIUpdate's identical body at 0x004550DE.
// (definition of DozerAIUpdate::finishBuildingSound omitted)


// (definition of DozerAIUpdate::~DozerAIUpdate omitted)


// (definition of DozerAIUpdate::internalTaskCompleteOrCancelled omitted)


// (definition of DozerAIUpdate::getDockPoint omitted)


// (definition of DozerAIUpdate::rva00489DD1 omitted)


// TheSkirmishAIManager's per-player record (0x002A8AB1), and the AI builder
// call (0x004EC2D4) that takes this dozer's id.
struct Rva002A8AB1Record;

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *owner);
};

extern Rva002A8F24 *TheSkirmishAIManager;

class AIBuilder
{
public:
	void rva004EC2D4(int value);
};

// (definition of DozerAIUpdate::notifyConstructionComplete omitted)


// Primary vslot 147 (+0x24C of vtable 0x0084B848; the AIUpdateInterface
// base slot is the empty 0x000B3FD0), retail 0x00488CF0..0x00488D1F, 47
// bytes, unnamed. With a phantom structure id at +0x4A4 it tail-calls dozer
// interface vslot 27 (rowed 0x00489D09, WorldBuilder's
// destroyPhantomStructure); otherwise it kills the goal object of the
// machine at +0x400 (pinned StateMachine::getGoalObject 0x004D7726, rowed
// Object::kill 0x002984D4 with damage type 8, death type 0).
// (definition of DozerAIUpdate::rva00488CF0 omitted)


class GlobalData
{
public:
	unsigned char m_pad0000[0x11DC];
	UnsignedInt m_builderFadeOutTime; // +0x11DC, the frames a dozer takes to fade out into a site
	UnsignedInt m_builderFadeInTime; // +0x11E0, the frames a dozer takes to fade back in
	Real m_builderMoveFromNewStructureDistance; // +0x11E4, how far it steps away from the structure it leaves
};

extern GlobalData *TheWritableGlobalData;

// The dozer comes back out of a structure it was working in: it steps away
// from the target (when asked and one is given), fades back in and drops the
// model conditions Rva00489256Do set. Callers: DozerActionDoActionState::update
// (target, TRUE) and cancelTask (none, FALSE).
// (definition of Rva0048A3B9Do omitted)


// (definition of DozerAIUpdate::cancelTask omitted)


// The rowed two-bit status mask builder.
struct Rva00391F4E : public _STL::_Base_bitset<4>
{
	Rva00391F4E(int unused, int b1, int b2);
};

// What ThingFactory::newObject takes: the initial status bits.
struct CreateMask : public _STL::_Base_bitset<4>
{
	CreateMask() { memset(_M_w, 0, sizeof(_M_w)); }
};

class Team;

class ThingFactory
{
public:
	Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *statusBits, ObjectID flag);
};

extern ThingFactory *TheThingFactory;

class Rva0039B795;
class Rva0039B7AD;

struct Rva0039BAD2Input;

// The player's +0x3BC member, under its two rowed spellings.
class Rva0039BAD2
{
public:
	void rva0039BAD2(Rva0039BAD2Input *what, Int cost);
};

class Rva0039B795 : public Rva0039BAD2
{
};

// The player's money (+0x90).
class Rva003B0D7C
{
public:
	UnsignedInt withdraw(UnsignedInt amount, Rva0039B795 *stats, Bool flag);
	void rva003B0D7C(Int amount, Rva0039B7AD *stats, Bool flag);
};

enum PlayerType
{
	PLAYER_HUMAN,
	PLAYER_COMPUTER
};

class ParticleSystem { public: Bool isSaveable() const; };
class Player
{
public:
	__declspec(dllimport) PlayerType getPlayerType() const { return m_playerType; }
	Rva003B0D7C *getMoney() { return &m_money; }
	Team *getDefaultTeam() const { return m_defaultTeam; }
	Rva0039B795 *getStats() { return &m_stats; }
	Bool isLocalPlayer() const;
	// The flag after ZH's m_canBuildUnits/m_canBuildBase (+0x338/+0x339),
	// where ZH keeps m_observer.
	/* the rowed ParticleSystem::isSaveable */ __declspec(dllimport) __forceinline Bool rva002AA223() const { return ((const ParticleSystem *)this)->isSaveable(); }
	void onStructureCreated(Object *builder, Object *structure);
	void onStructureConstructionComplete(Object *builder, Object *structure, Bool isRebuild);
private:
	unsigned char m_pad000[0x5C];
	PlayerType m_playerType; // +0x5C
	unsigned char m_pad060[0x90 - 0x60];
	Rva003B0D7C m_money; // +0x90
	unsigned char m_pad091[0x2EC - 0x91];
	Team *m_defaultTeam; // +0x2EC
	unsigned char m_pad2F0[0x3BC - 0x2F0];
	Rva0039B795 m_stats; // +0x3BC
};

// The rowed add-if-missing object id lists: TheInGameUI's at +0x9C4 and the
// player's at +0x754.
class Rva002A1111
{
public:
	void rva002A1111(ObjectID id);
};

class Rva002AE3F4
{
public:
	void rva002AE3F4(ObjectID id);
};

// Dozer interface vslot 25: BFME 2 places a phantom of the structure first.
// ZH construct's creation steps (newObject, producer and builder, the cost,
// position, orientation, onStructureCreated, zero percent) with the status
// bits PENDING_CONSTRUCTION and PHANTOM_STRUCTURE and model condition
// PHANTOM_STRUCTURE (retail's name tables). Its id goes to +0x4A4, which
// vslots 27 and 29 work on, and the phantom is made inert at once.
// (definition of DozerAIUpdate::createPhantomStructure omitted)


// The status builder clears sixteen bytes and then sets one bit.
class Rva0023DA79
{
public:
	Rva0023DA79 *rva0023DA79(int reserved, int bit);
};

struct ObjectStatusMask : public _STL::_Base_bitset<4>
{
	void set(ObjectStatusTypes bit) { _M_w[bit >> 5] |= 1U << (bit & 31); }
};

enum BodyDamageType
{
	BODY_PRISTINE,
	BODY_DAMAGED,
	BODY_REALLYDAMAGED,
	BODY_RUBBLE
};

class BodyModuleInterface
{
public:
	virtual void i00(); virtual void i01(); virtual void i02(); virtual void i03();
	virtual Real getHealth() const; // +0x10
	virtual void i05();
	virtual Real getMaxHealth() const; // +0x18
	virtual void i07();
	virtual BodyDamageType getDamageState() const; // +0x20
	virtual void i09(); virtual void i10(); virtual void i11();
	virtual void i12(); virtual void i13(); virtual void i14(); virtual void i15();
	virtual void i16(); virtual void i17(); virtual void i18(); virtual void i19();
	virtual void i20(); virtual void i21(); virtual void i22(); virtual void i23();
	virtual void i24(); virtual void i25(); virtual void i26(); virtual void i27();
	virtual void i28(); virtual void i29(); virtual void i30(); virtual void i31();
	virtual void internalChangeHealth(Real delta, Int flag); // +0x80
	virtual void i33(); virtual void i34(); virtual void i35();
	virtual void evaluateVisualCondition(); // +0x90
};

enum { LBC_OK = 0 };

class BuildAssistant
{
public:
	enum
	{
		TERRAIN_RESTRICTIONS = 0x01,
		NO_OBJECT_OVERLAP = 0x04,
		SHROUD_REVEALED = 0x10
	};
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual Int isLocationLegalToBuild(const Coord3D *worldPos, const ThingTemplate *build, Real angle,
		UnsignedInt options, Object *builderObject, Player *player); // +0x40
	void clearRemovableForConstruction(const ThingTemplate *whatToBuild, const Coord3D *pos, Real angle);
	Bool moveObjectsForConstruction(const ThingTemplate *whatToBuild, const Coord3D *pos, Real angle, Player *playerToBuild);
};

extern BuildAssistant *TheBuildAssistant;

class GeometryInfo;

class TerrainLogic
{
public:
	virtual void t00(); virtual void t01(); virtual void t02(); virtual void t03();
	virtual void t04(); virtual void t05();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = 0) const; // +0x18
	// BFME 2's: it destroys what intersects the footprint, then has the
	// terrain visual (vslot 18) remove trees and props for construction.
	void rva0028449F(const Coord3D *pos, const GeometryInfo &geom, Real angle);
	void flattenTerrain(Object *obj);
};

extern TerrainLogic *TheTerrainLogic;

class Pathfinder
{
public:
	void AddObjectToPathfindMap(Object *object);
	void RemoveObjectFromPathfindMap(Object *object);
};

class AI
{
public:
	Pathfinder *pathfinder();
private:
	unsigned char m_pad00[0x10];
	void *m_groupList; // +0x10
};

extern AI *TheAI;

// The rowed guarded remove from TheInGameUI's id list at +0x9C4.
class Rva0029F93A
{
public:
	void rva0029F93A(Int id);
};

// Dozer interface vslot 26: the phantom becomes the real structure under
// construction. Unless rebuilding, a human player's (or a skirmish AI's)
// site must still be legal to build, else the phantom is dropped (vslot 27).
// Then the rest of ZH construct: clear and move what is in the way, flatten
// the terrain and settle on it, one hit point, the under-construction status
// bits, the pathfind map; the phantom bits, hiding and opacity come off.
// (definition of DozerAIUpdate::makePhantomStructureReal omitted)


// The drawable's sound record (8 bytes, a reference at +4), as
// DrawableKeyedLookup.cpp spells it.
class OpaqueRefCounted
{
public:
	void Release_Ref();
};

class Rva0036CA00Str
{
public:
	~Rva0036CA00Str() { if (m_ref) m_ref->Release_Ref(); }
	OpaqueRefCounted *m_ref;
};

class Rva002390CB
{
public:
	int m_0;
	Rva0036CA00Str m_4;
};

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot01() = 0; virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0; virtual void slot06() = 0;
	virtual void slot07() = 0; virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0; virtual void slot12() = 0;
	virtual void slot13() = 0;
	// cl 7.1 lays overloaded virtuals out in reverse declaration order:
	// fetch(const char *) is slot 15 (+0x3C), fetch(const AsciiString &) 14.
	virtual UnicodeString fetch(const char *label, Bool *exists = 0) = 0;
	virtual UnicodeString fetch(const AsciiString &label, Bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

enum RadarEventType
{
	RADAR_EVENT_INVALID = 0,
	RADAR_EVENT_CONSTRUCTION
};

class Radar
{
public:
	void createEvent(const Coord3D *world, RadarEventType type, Real secondsToLive = 4.0f);
};

extern Radar *TheRadar;

// pickAndPlayUnitVoiceResponse's parameter type. The list a caller hands it
// is a plain list<Drawable *>: retail destroys it with the base destructor
// 0x00239AF4 on the normal path and with the list<Drawable *> destructor
// thunk 0x00239BAB in the unwind funclet.
class DrawableList : public _STL::list<Drawable *>
{
};

class PickAndPlayInfo;

class GameMessage
{
public:
	enum Type
	{
		MSG_BFME2_0x7DE = 0x7DE
	};
};

bool pickAndPlayUnitVoiceResponse(const DrawableList *list, GameMessage::Type messageType,
	PickAndPlayInfo *info);

class BridgeTowerBehaviorInterface
{
public:
	virtual void setBridge(Object *bridge);
	virtual ObjectID getBridgeID(); // vslot 1
};

class BridgeTowerBehavior
{
public:
	static BridgeTowerBehaviorInterface *getBridgeTowerBehaviorInterfaceFromObject(Object *obj);
};

class CastleBehavior
{
public:
	static NameKeyType rva0003955DA();
};

// The three-bit model condition mask builder (19 dwords).
class Rva00265254
{
public:
	Rva00265254(UnsignedInt unused, UnsignedInt bit1, UnsignedInt bit2, UnsignedInt bit3);
private:
	unsigned int m_words[19];
};

class Rva0028CBFD
{
public:
	void rva0028CBFD();
};

// LOGICFRAMES_PER_SECOND.
extern int BfmeLogicFramesPerSecond;

static const Real CONSTRUCTION_COMPLETE = -1.0f;

// ZH's DozerActionDoActionState (rowed ctor 0x00488545, vtable slot 6).
//
// ?update@DozerActionDoActionState@@UAE?AW4StateReturnType@@XZ, retail
// 0x0048A69E, 2028 bytes: vtable slot 6 of the state the ctor 0x00488545
// builds. ZH DozerActionDoActionState::update's shape (task switch over
// REPAIR and BUILD, construction percent stepping, completion through the
// dozer's internalTaskComplete); BFME 2 adds the castle check, the rubble/
// damage/under-construction drawable lookups (0x00274CD8) and the voice
// response through a stack DrawableList. The BUILD branch tests the
// complete case first, and the list is STLport's own (its by-value iterator
// and temps fix the frame at 0xE0).
class DozerActionDoActionState : public State
{
public:
	virtual StateReturnType update();
private:
	DozerTask m_task; // +0x20
};

// (definition of DozerActionDoActionState::update omitted)


// Native200B 489D09..489DD1 is dozer interface slot27 (primary object +3E4).
// WB DozerAIUpdate.cpp:2794 names destroyPhantomStructure. Native fields/calls
// prove +4A4 id, +40C rebuild flag, the cost refund, stats reversal, object
// destruction and both UI/player id removals; the WB body's call order is
// identical and createPhantomStructure stores the same phantom id.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class ScoreKeeper { public: void addObjectBuilt(Object *, Int); };
class Rva002ACECC { public: void rva002ACECC(Int); };

// (definition of DozerAIUpdate::destroyPhantomStructure omitted)

