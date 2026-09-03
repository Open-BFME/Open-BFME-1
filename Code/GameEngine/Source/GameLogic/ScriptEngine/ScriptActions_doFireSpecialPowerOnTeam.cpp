// cl: /DNDEBUG /DWIN32 /MD /EHsc
// FIRE_SPECIAL_POWER_ON_TEAM at retail RVA 0x002F8340.

typedef bool Bool;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class AsciiString
{
private:
	char *m_text;
};

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

// This helper is the retail routine at ILT 0x000033B4.  It walks the named
// player's objects, selects one able to use the power, and fires it at the
// supplied team position.  The body is shared by the action cluster.
class BfmeFireSpecialPowerHelper
{
public:
	Bool fire(const AsciiString &, const SpecialPowerTemplate *,
		const Coord3D *);
};

class ScriptActions
{
protected:
	void doFireSpecialPowerOnTeam(const AsciiString &, const AsciiString &,
		const AsciiString &);
};

extern BfmeScriptEngineVtbl_44 *TheScriptEngine;
extern void *TheSpecialPowerStore;
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
	typedef Bool (BfmeFireSpecialPowerHelper::*Function)(
		const AsciiString &, const SpecialPowerTemplate *, const Coord3D *);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_000033b4;
	return (reinterpret_cast<BfmeFireSpecialPowerHelper *>(actions)->*fn.member)(
		player, power, position);
}

// ?doFireSpecialPowerOnTeam@ScriptActions@@IAEXABVAsciiString@@00@Z
void ScriptActions::doFireSpecialPowerOnTeam(const AsciiString &player,
	const AsciiString &specialPower, const AsciiString &teamName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
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
