// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// The four experience and level actions:
//
//   0x002F11E0  doUnitGainLevel            UNIT_GAIN_LEVEL
//   0x002F5760  doTeamGiveExperienceLevel  TEAM_GIVE_EXPERIENCE_LEVEL
//   0x002F57D0  doTeamGiveExperiencePoints TEAM_GIVE_EXPERIENCE_POINTS
//   0x002F5820  doTeamSetExperiencePoints  TEAM_SET_EXPERIENCE_POINTS
//
// The three team actions all resolve the team at slot 17 and then push the work
// out to every member through the same visitor entry, differing only in which
// __cdecl visitor they hand it and whether they follow up with the refresh
// pass. doUnitGainLevel skips the walk and calls the experience subsystem on one
// object, which is the same subsystem the level lookup comes from.

typedef bool Bool;
typedef int Int;

class Object;
class Team;
class ScriptActionParameter;
class ExperienceLevel;

#include "ascii_string.h"

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

typedef void (__cdecl *BfmeObjectVisitor)(Object *, void *);

// The team seen as its member list: one entry that runs a visitor over every
// member. All three team actions reach it by casting the Team pointer.
class BfmeInnerIterable
{
public:
	Int bfmeVisit(BfmeObjectVisitor, void *);
};

// The visitor pointers in these actions are retail ILTs 0x25301,
// 0x1ACB7, 0xA95C and 0x29CD, reaching the existing providers below.
// Each is cdecl and returns 1 in EAX. BfmeInnerIterable::bfmeVisit casts
// its opaque callback slot back to an int-returning callback before calling
// it; it supplies two dwords, of which the refresh callback uses only one.
class BfmeAgentBS;
class BfmeInfoBS;
struct BfmeObjectD120;
struct BfmeObjectD150;
struct BfmeOwnerBHE;
extern int __cdecl bfmeApplyBS(BfmeAgentBS *, BfmeInfoBS *);
extern int __cdecl bfmeRva0037D120AddExperience(BfmeObjectD120 *, int);
extern int __cdecl bfmeRva0037D150Apply(BfmeObjectD150 *, int);
extern int __cdecl bfmeGoBHE(BfmeOwnerBHE *);

class ExperienceLevelSystem
{
public:
	ExperienceLevel *findLevel(const AsciiString &);
	void gainLevel(Object *, Bool);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
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
	virtual Team *getTeamNamed(BfmeAsciiStringArg, Bool) = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual Object *resolveUnit(ScriptActionParameter *) = 0;
};

extern ScriptEngine *TheScriptEngine;
extern ExperienceLevelSystem *TheExperienceLevelSystem;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doUnitGainLevel(ScriptActionParameter *, Bool);
	void doTeamGiveExperienceLevel(const AsciiString &, const AsciiString &);
	void doTeamGiveExperiencePoints(const AsciiString &, Int);
	void doTeamSetExperiencePoints(const AsciiString &, Int);
};

// ?doUnitGainLevel@ScriptActions@@IAEXPAVScriptActionParameter@@_N@Z
void ScriptActions::doUnitGainLevel(
	ScriptActionParameter *parameter, Bool showExperienceFX)
{
	Object *object = TheScriptEngine->resolveUnit(parameter);
	if (object) {
		TheExperienceLevelSystem->gainLevel(object, showExperienceFX);
	}
}

// ?doTeamGiveExperienceLevel@ScriptActions@@IAEXABVAsciiString@@0@Z
void ScriptActions::doTeamGiveExperienceLevel(
	const AsciiString &teamName, const AsciiString &levelName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team) {
		return;
	}

	ExperienceLevel *level =
		TheExperienceLevelSystem->findLevel(levelName);
	if (!level) {
		return;
	}

	BfmeInnerIterable *members = (BfmeInnerIterable *)team;
	members->bfmeVisit(reinterpret_cast<BfmeObjectVisitor>(bfmeApplyBS), level);
	members->bfmeVisit(reinterpret_cast<BfmeObjectVisitor>(bfmeGoBHE), 0);
}

// ?doTeamGiveExperiencePoints@ScriptActions@@IAEXABVAsciiString@@H@Z
void ScriptActions::doTeamGiveExperiencePoints(
	const AsciiString &teamName, Int points)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team) {
		return;
	}

	((BfmeInnerIterable *)team)->bfmeVisit(
		reinterpret_cast<BfmeObjectVisitor>(bfmeRva0037D120AddExperience), (void *)points);
}

// ?doTeamSetExperiencePoints@ScriptActions@@IAEXABVAsciiString@@H@Z
void ScriptActions::doTeamSetExperiencePoints(
	const AsciiString &teamName, Int points)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team) {
		return;
	}

	BfmeInnerIterable *members = (BfmeInnerIterable *)team;
	members->bfmeVisit(reinterpret_cast<BfmeObjectVisitor>(bfmeRva0037D150Apply), (void *)points);
	members->bfmeVisit(reinterpret_cast<BfmeObjectVisitor>(bfmeGoBHE), 0);
}
