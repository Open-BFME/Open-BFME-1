// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringinline
// The two team recruitment actions:
//
//   0x002F5BE0  doTeamRecruitUnits          arm 397, TEAM_RECRUIT_UNITS
//   0x00303AC0  doTeamRecruitUnitsFromTeam  TEAM_RECRUIT_UNITS_FROM_TEAM
//
// Both resolve the destination team through slot 17 with exact=true, ask slot 20
// for the named ObjectTypes set, and then call a recruit entry on the team.
// They part company after that: the plain form recruits from anywhere within a
// radius, so it needs the ThingTemplate and the AI's max recruit distance; the
// from-team form recruits out of a second named team instead, and falls back to
// a one-entry ObjectTypes built on the stack when the named set does not exist.

#include "StringInline.h"

typedef bool Bool;
typedef int Int;
typedef float Real;

class Team;
class ObjectTypes;
class ThingTemplate;

// Named for the two slots it reaches: getTeamNamed at +0x44 and getObjectTypes
// at +0x50.
class BfmeScriptEngineVtbl_44_50
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
	virtual Team *getTeamNamed(AsciiString name, Bool exact) = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual ObjectTypes *getObjectTypes(const AsciiString &name) = 0;
};

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

class BfmeAIData
{
public:
	unsigned char m_unreconstructed_000[0x5c];
	Real m_maxRecruitDistance;
};

class BfmeAI
{
public:
	unsigned char m_unreconstructed_000[0x14];
	BfmeAIData *m_aiData;
};

class BfmeTeamHasAnyObjects
{
public:
	Bool hasAnyObjects(Bool includeDead);
};

// Two distinct retail entries, not two readings of one: the radius form is
// reached through the ILT at 0x000439D2 and the from-team form through
// 0x0000B866.
class BfmeTeamRecruitHelper
{
public:
	void recruit(const ThingTemplate *, ObjectTypes *, Int, Real);
	int recruit(ObjectTypes *, Int, Team *);
};

extern BfmeScriptEngineVtbl_44_50 *TheScriptEngine;
extern BfmeThingFactory *TheThingFactory;
extern BfmeAI *TheAI;
extern void j_0001478b();
extern void j_000439d2();
extern void j_0000b866();
extern void j_0000534e();
extern void j_0003d415();
extern void j_0003eafe();

// The stack-built one-entry set the from-team form falls back to.
class BfmeObjectTypes
{
	unsigned char m_storage[0x14];

public:
	BfmeObjectTypes()
	{
		typedef void (BfmeObjectTypes::*Function)();
		union { void (*raw)(void); Function member; } fn;
		fn.raw = j_0003d415;
		(reinterpret_cast<BfmeObjectTypes *>(this)->*fn.member)();
	}

	~BfmeObjectTypes()
	{
		typedef void (BfmeObjectTypes::*Function)();
		union { void (*raw)(void); Function member; } fn;
		fn.raw = j_0003eafe;
		(reinterpret_cast<BfmeObjectTypes *>(this)->*fn.member)();
	}

	void addObjectType(const AsciiString &name)
	{
		typedef void (BfmeObjectTypes::*Function)(const AsciiString &);
		union { void (*raw)(void); Function member; } fn;
		fn.raw = j_0000534e;
		(reinterpret_cast<BfmeObjectTypes *>(this)->*fn.member)(name);
	}
};

static __forceinline Bool bfmeHasAnyObjects(Team *team)
{
	typedef Bool (BfmeTeamHasAnyObjects::*Function)(Bool);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0001478b;
	return (reinterpret_cast<BfmeTeamHasAnyObjects *>(team)->*fn.member)(false);
}

static __forceinline void bfmeRecruitUnits(Team *team,
	const ThingTemplate *thingTemplate, ObjectTypes *objectTypes,
	Int count, Real maxDistance)
{
	typedef void (BfmeTeamRecruitHelper::*Function)(const ThingTemplate *,
		ObjectTypes *, Int, Real);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_000439d2;
	(reinterpret_cast<BfmeTeamRecruitHelper *>(team)->*fn.member)(
		thingTemplate, objectTypes, count, maxDistance);
}

static __forceinline void bfmeRecruitUnits(Team *team,
	ObjectTypes *objectTypes, Int count, Team *sourceTeam)
{
	typedef int (BfmeTeamRecruitHelper::*Function)(ObjectTypes *, Int, Team *);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0000b866;
	(reinterpret_cast<BfmeTeamRecruitHelper *>(team)->*fn.member)(
		objectTypes, count, sourceTeam);
}

class ScriptActions
{
protected:
	void doTeamRecruitUnits(const AsciiString &, Int, const AsciiString &);
	void doTeamRecruitUnitsFromTeam(const AsciiString &, Int,
		const AsciiString &, const AsciiString &);
};

// ?doTeamRecruitUnits@ScriptActions@@IAEXABVAsciiString@@H0@Z
void ScriptActions::doTeamRecruitUnits(const AsciiString &teamName,
	Int count, const AsciiString &objectTypeName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, true);
	if (!team) {
		return;
	}

	const ThingTemplate *thingTemplate =
		TheThingFactory->findTemplate(objectTypeName);
	ObjectTypes *objectTypes = TheScriptEngine->getObjectTypes(objectTypeName);
	if (bfmeHasAnyObjects(team)) {
		bfmeRecruitUnits(team, thingTemplate, objectTypes, count,
			TheAI->m_aiData->m_maxRecruitDistance);
	} else {
		bfmeRecruitUnits(team, thingTemplate, objectTypes, count,
			1000000.0f);
	}
}

// ?doTeamRecruitUnitsFromTeam@ScriptActions@@IAEXABVAsciiString@@H00@Z
void ScriptActions::doTeamRecruitUnitsFromTeam(const AsciiString &teamName,
	Int count, const AsciiString &objectTypeName,
	const AsciiString &sourceTeamName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, true);
	if (!team) {
		return;
	}

	Team *sourceTeam = TheScriptEngine->getTeamNamed(sourceTeamName, false);
	if (!sourceTeam) {
		return;
	}

	ObjectTypes *objectTypes = TheScriptEngine->getObjectTypes(objectTypeName);
	if (objectTypes) {
		bfmeRecruitUnits(team, objectTypes, count, sourceTeam);
	} else {
		BfmeObjectTypes singleObjectType;
		singleObjectType.addObjectType(objectTypeName);
		bfmeRecruitUnits(team, (ObjectTypes *)&singleObjectType, count,
			sourceTeam);
	}
}
