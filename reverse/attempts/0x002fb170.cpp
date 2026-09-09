// ?doTeamUseCommandButtonOnNearestEnemy@ScriptActions@@IAEXABVAsciiString@@0@Z
// partial score=0.8 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline
// stlport
// TEAM_USE_COMMANDBUTTON_ON_NEAREST_ENEMY_UNIT at retail RVA 0x002FB170.
// The executeAction caller names this handler for
// TEAM_ALL_USE_COMMANDBUTTON_ON_NEAREST_ENEMY_UNIT.

#include "StringInline.h"
#include <bitset>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

class AIGroup;
class CommandButton;
class Object;
class Overridable;
class Player;
class Team;

extern void j_00009c2d();
extern void j_00018f16();
extern void j_00022ec1();
extern void j_0002369b();
extern void j_000382fd();
extern void j_00039b44();
extern void j_0003a5ad();
extern void j_0003b570();
extern void j_0003b59d();
extern void j_0003cccc();
extern void j_000478b1();
extern void j_00048c61();

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class BfmeStringArgBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringArgBase(const BfmeStringArgBase &other);
};

// ScriptEngine slot 17 passes this BFME string wrapper by value.
class BfmeAsciiStringArg
{
public:
	BfmeAsciiStringArg(const AsciiString &that)
	{
		((BfmeStringArgBase *)this)->BfmeStringArgBase::BfmeStringArgBase(
			*(const BfmeStringArgBase *)&that);
	}

	~BfmeAsciiStringArg();

private:
	char *m_text;
};

template <size_t NUMBITS>
class BitFlags
{
public:
	enum BogusInitType
	{
		kInit = 0
	};

	__declspec(nothrow) BitFlags(BogusInitType, Int bit);
	~BitFlags() {}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<192> KindOfMaskType;
extern const KindOfMaskType KINDOFMASK_NONE;

struct VptrZeroBlock24
{
	unsigned int m_dword00;
	unsigned int m_dword04;
	unsigned int m_dword08;
	unsigned int m_dword0c;
	unsigned int m_dword10;
	unsigned int m_dword14;
};

class BfmeScriptEngineVtbl_44
{
public:
	virtual void _slot00() = 0;
	virtual void _slot01() = 0;
	virtual void _slot02() = 0;
	virtual void _slot03() = 0;
	virtual void _slot04() = 0;
	virtual void _slot05() = 0;
	virtual void _slot06() = 0;
	virtual void _slot07() = 0;
	virtual void _slot08() = 0;
	virtual void _slot09() = 0;
	virtual void _slot10() = 0;
	virtual void _slot11() = 0;
	virtual void _slot12() = 0;
	virtual void _slot13() = 0;
	virtual void _slot14() = 0;
	virtual void _slot15() = 0;
	virtual void _slot16() = 0;
	virtual Team *getTeamNamed(BfmeAsciiStringArg name, Bool exact = false) = 0;
};

enum GUICommandType
{
	GUI_COMMAND_NONE = 0
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1
};

class Overridable
{
public:
	Overridable *friend_getFinalOverride()
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

	const Overridable *friend_getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

private:
	void *m_memoryPoolVTable;
	Overridable *m_nextOverride;
	Bool m_isOverride;
};

static Overridable *bfmeFinalOverride(Overridable *object)
{
	typedef Overridable *(Overridable::*FinalOverrideCall)();
	union
	{
		void *raw;
		FinalOverrideCall member;
	} function;
	function.raw = (void *)j_00048c61;
	return (object->*function.member)();
}

class SpecialPowerTemplate : public Overridable
{
public:
	UnsignedInt getID() const
	{
		return ((const SpecialPowerTemplate *)bfmeFinalOverride(
			(Overridable *)this))->m_id;
	}

	private:
	AsciiString m_name;
	UnsignedInt m_id;
};

class CommandButton
{
public:
	const SpecialPowerTemplate *getSpecialPowerTemplate() const
	{
		return m_specialPower;
	}

	GUICommandType getCommandType() const
	{
		return m_command;
	}

	UnsignedInt getOptions() const
	{
		return m_options;
	}

	Bool isReady(const Object *sourceObj) const;

private:
	unsigned char m_beforeCommand[0x10];
	GUICommandType m_command;
	unsigned char m_beforeOptions[0x04];
	UnsignedInt m_options;
	unsigned char m_beforeSpecialPower[0x18];
	const SpecialPowerTemplate *m_specialPower;
};

class Team
{
public:
	void getTeamAsAIGroup(AIGroup *group);
	Player *getControllingPlayer() const;
};

class AI
{
public:
	AIGroup *createGroup();
};

class AIGroup
{
public:
	Object *getSpecialPowerSourceObject(UnsignedInt id);
	Object *getCommandButtonSourceObject(GUICommandType type);
	Bool getCenter(Coord3D *center);
	void groupDoCommandButtonAtObject(const CommandButton *button,
		Object *object, CommandSourceType source);
};

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);
};

struct Rva001ED510
{
	unsigned int m_vptr;
	unsigned int m_next;
	unsigned int m_source;
	unsigned int m_button;
	unsigned char m_match;
	unsigned char m_padding[3];
	unsigned int m_sourceType;
};

class Rva001ED510SetCall
{
public:
	void set(int a, int b, char c, int d);
};

static AIGroup *bfmeCreateGroup(AI *object)
{
	typedef AIGroup *(AI::*CreateGroupCall)();
	union
	{
		void *raw;
		CreateGroupCall member;
	} function;
	function.raw = (void *)j_0003b570;
	return (object->*function.member)();
}

static void bfmeGetTeamAsAIGroup(Team *object, AIGroup *group)
{
	typedef void (Team::*GetTeamAsAIGroupCall)(AIGroup *);
	union
	{
		void *raw;
		GetTeamAsAIGroupCall member;
	} function;
	function.raw = (void *)j_00022ec1;
	(object->*function.member)(group);
}

static const CommandButton *bfmeFindCommandButton(
	ControlBar *object, const AsciiString &name)
{
	typedef const CommandButton *(ControlBar::*FindCommandButtonCall)(
		const AsciiString &);
	union
	{
		void *raw;
		FindCommandButtonCall member;
	} function;
	function.raw = (void *)j_0003b59d;
	return (object->*function.member)(name);
}

static Object *bfmeGetSpecialPowerSourceObject(AIGroup *object,
	UnsignedInt id)
{
	typedef Object *(AIGroup::*GetSpecialPowerSourceObjectCall)(UnsignedInt);
	union
	{
		void *raw;
		GetSpecialPowerSourceObjectCall member;
	} function;
	function.raw = (void *)j_00018f16;
	return (object->*function.member)(id);
}

static Object *bfmeGetCommandButtonSourceObject(AIGroup *object,
	GUICommandType type)
{
	typedef Object *(AIGroup::*GetCommandButtonSourceObjectCall)(
		GUICommandType);
	union
	{
		void *raw;
		GetCommandButtonSourceObjectCall member;
	} function;
	function.raw = (void *)j_0003cccc;
	return (object->*function.member)(type);
}

static Bool bfmeCommandButtonIsReady(const CommandButton *object,
	const Object *source)
{
	typedef Bool (CommandButton::*IsReadyCall)(const Object *) const;
	union
	{
		void *raw;
		IsReadyCall member;
	} function;
	function.raw = (void *)j_00039b44;
	return (object->*function.member)(source);
}

static Bool bfmeGetCenter(AIGroup *object, Coord3D *center)
{
	typedef Bool (AIGroup::*GetCenterCall)(Coord3D *);
	union
	{
		void *raw;
		GetCenterCall member;
	} function;
	function.raw = (void *)j_00009c2d;
	return (object->*function.member)(center);
}

static Player *bfmeGetControllingPlayer(const Team *object)
{
	typedef Player *(Team::*GetControllingPlayerCall)() const;
	union
	{
		void *raw;
		GetControllingPlayerCall member;
	} function;
	function.raw = (void *)j_0002369b;
	return (((Team *)object)->*function.member)();
}

static void bfmeSetValidCommandButtonTarget(Rva001ED510 *object,
	int source, int button, char match, int sourceType)
{
	typedef void (Rva001ED510SetCall::*SetCall)(int, int, char, int);
	union
	{
		void *raw;
		SetCall member;
	} function;
	function.raw = (void *)j_0003a5ad;
	(((Rva001ED510SetCall *)object)->*function.member)(
		source, button, match, sourceType);
}

static void bfmeGroupDoCommandButtonAtObject(AIGroup *object,
	const CommandButton *button, Object *target, CommandSourceType source)
{
	typedef void (AIGroup::*GroupDoCommandButtonAtObjectCall)(
		const CommandButton *, Object *, CommandSourceType);
	union
	{
		void *raw;
		GroupDoCommandButtonAtObjectCall member;
	} function;
	function.raw = (void *)j_000478b1;
	(object->*function.member)(button, target, source);
}

class PartitionFilter
{
public:
	PartitionFilter *link(PartitionFilter *next);

	unsigned int m_vptr;
	PartitionFilter *m_next;
};

struct PartitionFilterSameMapStatus
{
	unsigned int m_vptr;
	PartitionFilter *m_next;
	const Object *m_object;
};

struct PartitionFilterValidCommandButtonTarget
{
	unsigned int m_vptr;
	PartitionFilter *m_next;
	Object *m_source;
	const CommandButton *m_button;
	unsigned char m_match;
	unsigned char m_padding[3];
	unsigned int m_sourceType;
};

struct PartitionFilterPlayerAffiliation
{
	unsigned int m_vptr;
	PartitionFilter *m_next;
	const Player *m_player;
	unsigned char m_match;
	unsigned char m_padding[3];
	unsigned int m_affiliation;
};

struct Rva000C3DD0VptrZeroBlockObject
{
	unsigned int m_vptr;
	PartitionFilter *m_next;
	VptrZeroBlock24 m_first;
	VptrZeroBlock24 m_second;
};

class Rva000C3DD0ConstructorCall
{
public:
	void construct(const VptrZeroBlock24 &first,
		const VptrZeroBlock24 &second);
};

static void bfmeConstructRva000C3DD0(
	Rva000C3DD0VptrZeroBlockObject *object,
	const VptrZeroBlock24 &first, const VptrZeroBlock24 &second)
{
	typedef void (Rva000C3DD0ConstructorCall::*ConstructCall)(
		const VptrZeroBlock24 &, const VptrZeroBlock24 &);
	union
	{
		void *raw;
		ConstructCall member;
	} function;
	function.raw = (void *)j_000382fd;
	(((Rva000C3DD0ConstructorCall *)object)->*function.member)(first, second);
}

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *position, Real maxDistance,
		Int distanceCalculation, PartitionFilter *filters);
};

extern AI *TheAI;
extern BfmeScriptEngineVtbl_44 *TheScriptEngine;
extern ControlBar *TheControlBar;
extern PartitionManager *ThePartitionManager;

enum AllowPlayerRelationship
{
	ALLOW_ENEMIES = 0x04
};

class ScriptActions
{
protected:
	void doTeamUseCommandButtonOnNearestEnemy(
		const AsciiString &teamName, const AsciiString &commandAbility);
};

// ?doTeamUseCommandButtonOnNearestEnemy@ScriptActions@@IAEXABVAsciiString@@0@Z
void ScriptActions::doTeamUseCommandButtonOnNearestEnemy(
	const AsciiString &teamName, const AsciiString &commandAbility)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName);
	if (!team)
		return;

	AIGroup *theGroup = bfmeCreateGroup(TheAI);
	bfmeGetTeamAsAIGroup(team, theGroup);

	const CommandButton *commandButton =
		bfmeFindCommandButton(TheControlBar, commandAbility);
	if (!commandButton)
		return;

	Object *srcObj;
	if (commandButton->getSpecialPowerTemplate()) {
		srcObj = bfmeGetSpecialPowerSourceObject(theGroup,
			commandButton->getSpecialPowerTemplate()->getID());
	} else {
		srcObj = bfmeGetCommandButtonSourceObject(theGroup,
			commandButton->getCommandType());
	}

	if (!srcObj)
		return;
	if (!bfmeCommandButtonIsReady(commandButton, srcObj))
		return;

	Coord3D center;
	bfmeGetCenter(theGroup, &center);

	// The retail body carries the BFME "unit" kind mask as an inline
	// VptrZeroBlock24 value.  These are the six words used by the
	// Rva000C3DD0 filter constructor; the surrounding filters give it the
	// enemy-unit meaning of this action.
	VptrZeroBlock24 enemyUnitMask =
		{ 0, 0x00200000, 0x01000000, 0, 2, 0 };
	const VptrZeroBlock24 &emptyMask =
		*(const VptrZeroBlock24 *)&KINDOFMASK_NONE;
	PartitionFilterSameMapStatus mapFilter =
		{ 0x01085DD0, 0, srcObj };
	Object *target;

	if (((commandButton->getOptions() >> 5) & 1) != 0) {
		Rva000C3DD0VptrZeroBlockObject kindFilter;
		bfmeConstructRva000C3DD0(&kindFilter, emptyMask, enemyUnitMask);
		PartitionFilterPlayerAffiliation affiliationFilter =
			{ 0x0109689C, 0, bfmeGetControllingPlayer(team),
			  true, { 0, 0, 0 }, ALLOW_ENEMIES };
		((PartitionFilter *)&kindFilter)->link(
			(PartitionFilter *)&mapFilter);
		((PartitionFilter *)&affiliationFilter)->link(
			(PartitionFilter *)&kindFilter);
		target = ThePartitionManager->getClosestObject(
			&center, 1000000.0f, 0,
			(PartitionFilter *)&affiliationFilter);
	} else {
		Rva000C3DD0VptrZeroBlockObject kindFilter;
		bfmeConstructRva000C3DD0(&kindFilter, emptyMask, enemyUnitMask);
		PartitionFilterValidCommandButtonTarget validFilter;
		bfmeSetValidCommandButtonTarget((Rva001ED510 *)&validFilter,
			(int)srcObj, (int)commandButton, 1, CMD_FROM_SCRIPT);
		PartitionFilterPlayerAffiliation affiliationFilter =
			{ 0x0109689C, 0, bfmeGetControllingPlayer(team),
			  true, { 0, 0, 0 }, ALLOW_ENEMIES };
		((PartitionFilter *)&kindFilter)->link(
			(PartitionFilter *)&mapFilter);
		((PartitionFilter *)&validFilter)->link(
			(PartitionFilter *)&kindFilter);
		((PartitionFilter *)&affiliationFilter)->link(
			(PartitionFilter *)&validFilter);
		target = ThePartitionManager->getClosestObject(
			&center, 1000000.0f, 0,
			(PartitionFilter *)&affiliationFilter);
	}

	if (target)
		bfmeGroupDoCommandButtonAtObject(theGroup,
			commandButton, target, CMD_FROM_SCRIPT);
}
