// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringinline
// Open-BFME: TEAM_CAPTURE_NEAREST_UNOWNED_FACTION_UNIT at retail RVA
// 0x002F55C0.  executeAction arm 274 names this action; the body is the
// ScriptActions source family with BFME's linked partition-filter ABI.

#include "StringInline.h"

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef float Real;

class Object;
class Player;

// The BFME ScriptEngine takes this one-word string view by value.  Keeping
// the forwarding copy constructor and declared-only destructor visible gives
// MSVC 7.1 the retail EH saved-esp/string-copy shape at the call site.
class BfmeStringArgBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringArgBase(const BfmeStringArgBase &);
	~BfmeStringArgBase();
};

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

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1
};

enum AllowPlayerRelationship
{
	ALLOW_SAME_PLAYER = 0x01,
	ALLOW_ALLIES = 0x02,
	ALLOW_ENEMIES = 0x04,
	ALLOW_NEUTRAL = 0x08
};

class PartitionFilter
{
public:
	PartitionFilter(void) : m_next(0) {}
	virtual ~PartitionFilter(void) {}
	virtual Bool allow(Object *object) = 0;
	PartitionFilter *link(PartitionFilter *next);
	PartitionFilter *m_next;
};

class PartitionFilterPlayerAffiliation : public PartitionFilter
{
public:
	PartitionFilterPlayerAffiliation(const Player *player,
		UnsignedInt affiliation, Bool match)
		: m_player(player), m_match(match), m_affiliation(affiliation) {}

	virtual Bool allow(Object *object);

private:
	const Player *m_player;
	Bool m_match;
	UnsignedInt m_affiliation;
};

class PartitionFilterUnmannedObject : public PartitionFilter
{
public:
	PartitionFilterUnmannedObject(Bool match) : m_match(match) {}

	virtual Bool allow(Object *object);

private:
	Bool m_match;
};

class PartitionFilterOnMap : public PartitionFilter
{
public:
	PartitionFilterOnMap(void) {}
	virtual Bool allow(Object *object);
};

class AIGroup
{
public:
	Bool getCenter(Coord3D *center);
	void groupEnter(Object *object, CommandSourceType commandSource);
};

class Team
{
public:
	void getTeamAsAIGroup(AIGroup *group);
	Player *getControllingPlayer(void) const;
};

class AI
{
public:
	AIGroup *createGroup(void);
};

class ScriptEngine
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual Team *getTeamNamed(BfmeAsciiStringArg name, Bool exact) = 0;
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *position, Real maxDistance,
		int distanceCalculation, PartitionFilter *filters);
};

extern ScriptEngine *TheScriptEngine;
extern AI *TheAI;
extern PartitionManager *ThePartitionManager;

class ScriptActions
{
protected:
	void doTeamCaptureNearestUnownedFactionUnit(const AsciiString &teamName);
};

// ?doTeamCaptureNearestUnownedFactionUnit@ScriptActions@@IAEXABVAsciiString@@@Z
void ScriptActions::doTeamCaptureNearestUnownedFactionUnit(
	const AsciiString &teamName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;

	AIGroup *theGroup = TheAI->createGroup();
	team->getTeamAsAIGroup(theGroup);

	Coord3D pos;
	theGroup->getCenter(&pos);

	Object *obj;
	{
		PartitionFilterOnMap filterMapStatus;
		PartitionFilterUnmannedObject f2(true);
		PartitionFilterPlayerAffiliation f1(team->getControllingPlayer(),
			ALLOW_ENEMIES | ALLOW_NEUTRAL, true);

		obj = ThePartitionManager->getClosestObject(&pos, 1000000.0f,
			0, f1.link(f2.link(&filterMapStatus)));
	}
	if (!obj)
		return;

	theGroup->groupEnter(obj, CMD_FROM_SCRIPT);
}
