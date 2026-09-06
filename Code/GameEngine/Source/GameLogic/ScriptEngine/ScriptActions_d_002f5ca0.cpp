// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// Address-derived conversion of the 130-byte body at retail RVA 0x002F5CA0.
//
// The body resolves two team names through the BFME ScriptEngine, resolves the
// third string through the BFME ThingFactory and object-type-list virtual, then
// forwards those results plus the signed object count to the retail helper at ILT
// 0x000043F9.  The surrounding action name is not established by a caller or
// source declaration, so the exported function deliberately remains anonymous.

#include "StringInline.h"

typedef bool Bool;

class Team;
class ObjectTypes;
class ThingTemplate;

// BFME inserts its team lookup at slot 17 and its object-type-list lookup at
// slot 20.  The reference ScriptEngine header confirms the latter takes the
// name by reference; the retail body has no second temporary at that call.
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

// The retail helper is reached through the five-byte ILT at 0x000043F9.  Its
// call site sets ECX to team1 and passes (template, objectTypes, count,
// team2), so a PMF view preserves thiscall order while retaining the thunk
// relocation instead of turning it into an absolute function-pointer call.
// Retail helper checks count <= 0 and returns the number of reassigned objects.
class BfmeTeamObjectActionHelper
{
public:
	int apply(const ThingTemplate *, ObjectTypes *, int, Team *);
};

extern BfmeScriptEngineVtbl_44_50 *TheScriptEngine;
extern BfmeThingFactory *TheThingFactory;
extern void j_000043f9();

static __forceinline void bfmeApplyTeamObjectAction(Team *team,
	const ThingTemplate *thingTemplate, ObjectTypes *objectTypes,
	int count, Team *otherTeam)
{
	typedef int (BfmeTeamObjectActionHelper::*Function)(
		const ThingTemplate *, ObjectTypes *, int, Team *);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_000043f9;
	(reinterpret_cast<BfmeTeamObjectActionHelper *>(team)->*fn.member)(
		thingTemplate, objectTypes, count, otherTeam);
}

void __stdcall d_002f5ca0(const AsciiString &teamName,
	int count, const AsciiString &objectTypeName,
	const AsciiString &otherTeamName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, true);
	if (!team)
		return;

	Team *otherTeam = TheScriptEngine->getTeamNamed(otherTeamName, false);
	if (!otherTeam)
		return;

	const ThingTemplate *thingTemplate =
		TheThingFactory->findTemplate(objectTypeName);
	ObjectTypes *objectTypes = TheScriptEngine->getObjectTypes(objectTypeName);
	bfmeApplyTeamObjectAction(team, thingTemplate, objectTypes, count,
		otherTeam);
}
