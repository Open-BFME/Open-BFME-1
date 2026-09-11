// cl: /DNDEBUG /MD /O2 /EHsc /Ireference/shims/stringinline
// Readable recovery of ScriptActions::doTeamIdleForFramecount at retail RVA
// 0x002F5040.  The body resolves a team, creates an AIGroup, gets its center,
// idles the group, and schedules the team for either framecount or seconds.
// The action templates name TEAM_IDLE_FOR_FRAMECOUNT and TEAM_IDLE_FOR_SECONDS,
// while the retail body proves the shared Bool seconds parameter.

#include "StringInline.h"

typedef bool Bool;
typedef int Int;

class BfmeStringArgBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringArgBase(const BfmeStringArgBase &);
	~BfmeStringArgBase();
};

// ScriptEngine passes AsciiString by value through its retail vtable.  This
// wrapper preserves the in-place copy construction used by the BFME ABI.
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
	float x;
	float y;
	float z;
};

class Team;

class AIGroup
{
public:
	Bool getCenter(Coord3D *center);
	void groupIdle(Int commandSource);
};

class AI
{
public:
	AIGroup *createGroup();
};

class Team
{
public:
	void getTeamAsAIGroup(AIGroup *group);
};

class ScriptEngine
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual Team *getTeamNamed(BfmeAsciiStringArg name, Bool exact) = 0;

	void setSequentialTimer(Team *team, Int frames);
};

extern ScriptEngine *TheScriptEngine;
extern AI *TheAI;

class ScriptActions
{
protected:
	void doTeamIdleForFramecount(const AsciiString &, Int, Bool);
};

// ?doTeamIdleForFramecount@ScriptActions@@IAEXABVAsciiString@@H_N@Z
void ScriptActions::doTeamIdleForFramecount(
	const AsciiString &teamName, Int framecount, Bool seconds)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (!theTeam)
		return;

	AIGroup *theGroup = TheAI->createGroup();
	if (!theGroup)
		return;

	theTeam->getTeamAsAIGroup(theGroup);
	Coord3D center;
	theGroup->getCenter(&center);
	theGroup->groupIdle(1);

	if (seconds)
		TheScriptEngine->setSequentialTimer(theTeam, framecount * 5);
	else
		TheScriptEngine->setSequentialTimer(theTeam, framecount);
}
