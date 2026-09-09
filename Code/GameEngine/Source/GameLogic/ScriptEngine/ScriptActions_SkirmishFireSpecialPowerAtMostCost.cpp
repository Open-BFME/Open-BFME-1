// cl: /DNDEBUG /DWIN32 /MD /EHsc /ICode
// Retail 0x002F81F0 is the short, mask-walking implementation reached by
// executeAction's SKIRMISH_FIRE_SPECIAL_POWER_AT_MOST_COST arm (template 255).
// The matched dispatcher identifies this ScriptActions method. BFME walks
// the selected-player mask instead of the older reference team loop.

typedef bool Bool;
typedef int Int;
typedef float Real;
typedef unsigned short UnsignedShort;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

#include "Libraries/Source/WWVegas/WWLib/string_base.h"

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
};

class Player;
class SpecialPowerTemplate;
class SpecialPowerStore;

// Slot +0x48 is getSkirmishEnemyPlayer in the ScriptEngine vtable used by
// this action.  The non-virtual mask view below is the existing 0x0004B290
// ILT selected by its named reverse binding.
class ScriptEngine
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual Player *getSkirmishEnemyPlayer();
};

class BfmeScriptEngine_getPlayerMaskFromAsciiString
{
public:
	UnsignedShort getPlayerMaskFromAsciiString(const AsciiString &name,
		Bool *found);
};

// The retail object stores its player index at +0x24 and dispatches
// computeSuperweaponTarget through vtable slot 4 (+0x10).
class Player
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual Bool computeSuperweaponTarget(const SpecialPowerTemplate *power,
		Coord3D *location, Int enemyIndex, Real radius);

	public:
	unsigned char m_beforePlayerIndex[0x20];
	Int m_playerIndex;
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(UnsignedShort &mask);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();

	Overridable *friend_getFinalOverride(void)
	{
		if (m_nextOverride)
		{
			Overridable *next = m_nextOverride;
			if (next->m_nextOverride)
				return next->m_nextOverride->friend_getFinalOverride();
			return next;
		}
		return this;
	}

protected:
	Overridable *m_nextOverride;
	bool m_isOverride;
};

// The BFME layout places RadiusCursorRadius at +0x110 in this retail
// SpecialPowerTemplate view.  The inline override walk is deliberately kept
// at the proven two-level VC7 shape used by the existing accessor family.
#pragma inline_recursion(on)
#pragma inline_depth(2)
class SpecialPowerTemplate : public Overridable
{
public:
	Real getRadiusCursorRadius(void) const
	{
		const SpecialPowerTemplate *self =
			(const SpecialPowerTemplate *)
			const_cast<SpecialPowerTemplate *>(this)->friend_getFinalOverride();
		return self->m_radiusCursorRadius;
	}

private:
	unsigned char m_unreconstructed_00[0x110 - 0x0c];
	Real m_radiusCursorRadius;
};

class SpecialPowerStore
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplate(
		AsciiString name);
};

class BfmeFireSpecialPowerHelper
{
public:
	Bool fire(const AsciiString &, const SpecialPowerTemplate *,
		const Coord3D *);
};

class ScriptActions
{
protected:
	void doSkirmishFireSpecialPowerAtMostCost(const AsciiString &player,
		const AsciiString &specialPower);
};

extern ScriptEngine *TheScriptEngine;
extern SpecialPowerStore *TheSpecialPowerStore;
extern PlayerList *ThePlayerList;
extern void j_000033b4();

static __forceinline Bool bfmeFireSpecialPowerAtPosition(
	ScriptActions *actions, const AsciiString &player,
	const SpecialPowerTemplate *power, const Coord3D *position)
{
	typedef Bool (BfmeFireSpecialPowerHelper::*Function)(
		const AsciiString &, const SpecialPowerTemplate *, const Coord3D *);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_000033b4;
	return (reinterpret_cast<BfmeFireSpecialPowerHelper *>(actions)->*
		fn.member)(player, power, position);
}

// ?doSkirmishFireSpecialPowerAtMostCost@ScriptActions@@IAEXABVAsciiString@@0@Z
void ScriptActions::doSkirmishFireSpecialPowerAtMostCost(
	const AsciiString &player, const AsciiString &specialPower)
{
	Player *enemyPlayer = TheScriptEngine->getSkirmishEnemyPlayer();
	if (enemyPlayer == 0)
		return;

	Int enemyIndex = enemyPlayer->m_playerIndex;
	const SpecialPowerTemplate *power =
		((SpecialPowerStore *)TheSpecialPowerStore)
			->findSpecialPowerTemplate(specialPower);
	if (power == 0)
		return;

	Real radius = 50.0f;
	if (power->getRadiusCursorRadius() > 50.0f)
		radius = power->getRadiusCursorRadius();

	UnsignedShort playerMask =
		((BfmeScriptEngine_getPlayerMaskFromAsciiString *)TheScriptEngine)
			->getPlayerMaskFromAsciiString(player, 0);

	while (playerMask != 0)
	{
		Player *pPlayer = ThePlayerList->getEachPlayerFromMask(playerMask);
		if (pPlayer != 0)
		{
			Coord3D location;
			pPlayer->computeSuperweaponTarget(power, &location, enemyIndex,
				radius);
			if (bfmeFireSpecialPowerAtPosition(this, player, power, &location))
				return;
		}
	}
}
