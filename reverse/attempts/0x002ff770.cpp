// ?doSkirmishCommandButtonOnMostValuable@ScriptActions@@IAEXABVAsciiString@@0M_N@Z
// partial score=0.55 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline
// stlport
// Clean C++ recovery of ScriptActions::doSkirmishCommandButtonOnMostValuable.
// Retail boundary: 0x002FF770, 795 bytes.  The executeAction
// SKIRMISH_PERFORM_COMMANDBUTTON_ON_MOST_VALUABLE_OBJECT arm names this
// four-argument body.  BFME keeps the reference action's group/filter flow,
// with the BFME ScriptEngine by-value string ABI and the retail filter views.

#include "StringInline.h"
#include <bitset>

typedef bool Bool;
typedef int Int;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object;
class Player;
class CommandButton;
class SpecialPowerTemplate;

class ScriptEngine
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual class Team *getTeamNamed(AsciiString name, Bool exact) = 0;
};

class Player
{
};

class Team
{
public:
	void getTeamAsAIGroup(class AIGroup *group);
	Player *getControllingPlayer() const;
};

class AIGroup
{
public:
	Object *getSpecialPowerSourceObject(Int id);
	Object *getCommandButtonSourceObject(Int commandType);
	void getCenter(Coord3D *center);
	void groupDoCommandButtonAtObject(const CommandButton *button,
		Object *object, Int source);
};

class AI
{
public:
	AIGroup *createGroup();
};

class SpecialPowerTemplate
{
public:
	Int getID() const;
};

class CommandButton
{
public:
	SpecialPowerTemplate *getSpecialPowerTemplate() const
	{
		return *(SpecialPowerTemplate **)((char *)this + 0x34);
	}
	Int getCommandType() const
	{
		return *(const Int *)((const char *)this + 0x10);
	}
	Int getOptions() const
	{
		return *(const Int *)((const char *)this + 0x18);
	}
};

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);
};

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *object) = 0;
	PartitionFilter *link(PartitionFilter *next);

	PartitionFilter *m_next;
};

class PartitionFilterPlayerAffiliation : public PartitionFilter
{
public:
	PartitionFilterPlayerAffiliation(const Player *player,
		unsigned int affiliation, Bool match)
		: m_player(player), m_match(match), m_affiliation(affiliation) {}

protected:
	virtual Bool allow(Object *object);

private:
	const Player *m_player;
	Bool m_match;
	unsigned int m_affiliation;
};

class PartitionFilterValidCommandButtonTarget : public PartitionFilter
{
public:
	PartitionFilterValidCommandButtonTarget(Object *source,
		const CommandButton *button, Bool match, Int sourceType)
		: m_source(source), m_button(button), m_match(match),
		  m_sourceType(sourceType) {}

protected:
	virtual Bool allow(Object *object);

private:
	Object *m_source;
	const CommandButton *m_button;
	Bool m_match;
	Int m_sourceType;
};

class PartitionFilterSameMapStatus : public PartitionFilter
{
public:
	PartitionFilterSameMapStatus(const Object *object) : m_object(object) {}

protected:
	virtual Bool allow(Object *object);

private:
	const Object *m_object;
};

template <size_t NUMBITS>
class BitFlags
{
public:
	enum BogusInitType { kInit = 0 };
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

class Rva000C3DD0VptrZeroBlockObject : public PartitionFilter
{
public:
	__declspec(nothrow) Rva000C3DD0VptrZeroBlockObject(
		const VptrZeroBlock24 &first, const VptrZeroBlock24 &second);
	virtual Bool allow(Object *object);

	VptrZeroBlock24 m_first;
	VptrZeroBlock24 m_second;
};

struct BfmeWideResult
{
	void *m_value;
	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &that);
	~BfmeWideResult();
};

class BfmeWideResultSource
{
public:
	BfmeWideResult bfmeMakeWideResult(Int a, Int b, Int c, Int d, Int e, Int f);
};

class BfmeWideForwardC
{
	char m_pad[0x0c];
	BfmeWideResultSource *m_source;

public:
	BfmeWideResult bfmeForwardWideC(Int a, Int b, Int c, Int d, Int e);
};

extern ScriptEngine *TheScriptEngine;
extern AI *TheAI;
extern ControlBar *TheControlBar;
extern BfmeWideForwardC *ThePartitionManager;

enum
{
	ALLOW_ENEMIES = 4,
	CMD_FROM_SCRIPT = 1,
	FROM_CENTER_2D = 0,
	ITER_SORTED_EXPENSIVE_TO_CHEAP = 3
};

class ScriptActions
{
protected:
	void doSkirmishCommandButtonOnMostValuable(const AsciiString &teamName,
		const AsciiString &ability, Real range, Bool allTeamMembers);
};

// ?doSkirmishCommandButtonOnMostValuable@ScriptActions@@IAEXABVAsciiString@@0M_N@Z
void ScriptActions::doSkirmishCommandButtonOnMostValuable(
	const AsciiString &teamName, const AsciiString &ability, Real range,
	Bool allTeamMembers)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;

	AIGroup *theGroup = TheAI->createGroup();
	team->getTeamAsAIGroup(theGroup);

	Player *player = team->getControllingPlayer();
	if (!player)
		return;

	const CommandButton *commandButton =
		TheControlBar->findCommandButton(ability);
	if (!commandButton)
		return;

	Object *srcObj = 0;
	if (commandButton->getSpecialPowerTemplate())
	{
		srcObj = theGroup->getSpecialPowerSourceObject(
			commandButton->getSpecialPowerTemplate()->getID());
	}
	else
	{
		srcObj = theGroup->getCommandButtonSourceObject(
			commandButton->getCommandType());
	}

	if (!srcObj)
		return;

	Coord3D pos;
	theGroup->getCenter(&pos);

	PartitionFilterSameMapStatus mapFilter(srcObj);
	Object *target = 0;
	if (((commandButton->getOptions() >> 5) & 1) != 0)
	{
		BfmeWideResult result = ThePartitionManager->bfmeForwardWideC(
			(Int)&pos, (Int)1000000.0f, FROM_CENTER_2D,
			(Int)(PartitionFilterPlayerAffiliation(
				team->getControllingPlayer(), ALLOW_ENEMIES, true).link(
				&mapFilter)), ITER_SORTED_EXPENSIVE_TO_CHEAP);
		target = (Object *)result.m_value;
	}
	else
	{
		BfmeWideResult result = ThePartitionManager->bfmeForwardWideC(
			(Int)&pos, (Int)1000000.0f, FROM_CENTER_2D,
			(Int)(PartitionFilterPlayerAffiliation(
				team->getControllingPlayer(), ALLOW_ENEMIES, true).link(
			PartitionFilterValidCommandButtonTarget(
				srcObj, commandButton, true, CMD_FROM_SCRIPT).link(
				&mapFilter))), ITER_SORTED_EXPENSIVE_TO_CHEAP);
		target = (Object *)result.m_value;
	}

	if (target)
		theGroup->groupDoCommandButtonAtObject(
			commandButton, target, CMD_FROM_SCRIPT);

	(void)allTeamMembers;
}
