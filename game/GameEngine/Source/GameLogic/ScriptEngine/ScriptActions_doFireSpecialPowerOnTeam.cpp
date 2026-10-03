// cl: /DNDEBUG /DWIN32 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// FIRE_SPECIAL_POWER_ON_TEAM at retail RVA 0x002F8340.

typedef bool Bool;
typedef float Real;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
#include "ascii_string.h"

class BfmeAsciiStringArg : public AsciiString
{
public:
	BfmeAsciiStringArg(const AsciiString &that) : AsciiString(that) {}

	~BfmeAsciiStringArg();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Coord3D *getEstimateTeamPosition(Coord3D *) const;
};

class BfmeTeamEstimatePositionCall
{
public:
	Coord3D *getEstimateTeamPosition(Coord3D *) const;
};

class SpecialPowerTemplate;

// SpecialPowerStore is a real class (the registration manifest declares it at
// Common/System/game_engine_subsystems.h:91). Only the name is needed to declare
// the global with the pointee type its own decorated name carries
// (?TheSpecialPowerStore@@3PAVSpecialPowerStore@@A), so forward-declare it
// rather than redeclare it; the read below still goes through the modelling
// class BfmeSpecialPowerStoreView by cast, which emits nothing.
class SpecialPowerStore;

// The global this TU reads is the game's TheScriptEngine, whose defining
// decorated name carries the pointee type
// (?TheScriptEngine@@3PAVScriptEngine@@A), so the pointee is declared under the
// real class name and the modelling class below is reached by cast. A cast
// between pointer types emits nothing, so the compiled bytes are unchanged.
//
// The modelling class stays a placeholder on purpose: BFME's ScriptEngine puts
// getTeamNamed at vtable slot 17 and passes the name by value, with the
// exact-match flag as its second argument. Only the slots this body needs are
// modelled.
class ScriptEngine;

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
	virtual Team *getTeamNamed(BfmeAsciiStringArg name, Bool exact) = 0;
};

class BfmeSpecialPowerStoreView
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplate(
		BfmeAsciiStringArg name);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doFireSpecialPowerOnTeam(const AsciiString &, const AsciiString &,
		const AsciiString &);
};

extern ScriptEngine *TheScriptEngine;
extern SpecialPowerStore *TheSpecialPowerStore;
extern void j_000033b4();
extern void j_000241fe();

static __forceinline Coord3D *bfmeGetEstimateTeamPosition(Team *team,
	Coord3D *position)
{
	typedef Coord3D *(BfmeTeamEstimatePositionCall::*Function)(Coord3D *) const;
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_000241fe;
	return (reinterpret_cast<const BfmeTeamEstimatePositionCall *>(team)->*
		fn.member)(position);
}

static __forceinline Bool bfmeFireSpecialPowerAtPosition(ScriptActions *actions,
	const AsciiString &player, const SpecialPowerTemplate *power,
	const Coord3D *position)
{
	// ILT 0x000033B4 -> ScriptActions::rva002F48B0 (0x002F48B0).
	typedef Bool (ScriptActions::*Function)(
		const AsciiString &, const SpecialPowerTemplate *, const Coord3D *);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_000033b4;
	return (actions->*fn.member)(player, power, position);
}

// ?doFireSpecialPowerOnTeam@ScriptActions@@IAEXABVAsciiString@@00@Z
void ScriptActions::doFireSpecialPowerOnTeam(const AsciiString &player,
	const AsciiString &specialPower, const AsciiString &teamName)
{
	Team *team = ((BfmeScriptEngineVtbl_44*)TheScriptEngine)->getTeamNamed(teamName, false);
	if (!team)
		return;

	Coord3D position;
	bfmeGetEstimateTeamPosition(team, &position);

	const SpecialPowerTemplate *power =
		((BfmeSpecialPowerStoreView *)TheSpecialPowerStore)
			->findSpecialPowerTemplate(specialPower);
	if (!power)
		return;

	bfmeFireSpecialPowerAtPosition(this, player, power, &position);
}
