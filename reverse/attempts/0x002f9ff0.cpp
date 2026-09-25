// ?d_002f9ff0@@YAXXZ
// partial score=0.42 date=2026-09-25
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline
// stlport
// NAMED_USE_COMMANDBUTTON_ON_NEAREST_ENEMY_UNIT at retail RVA 0x002F9FF0.

#include "StringInline.h"
#include <bitset>

typedef bool Bool;
typedef int Int;
typedef float Real;

class Object;
class Player;
class CommandButton;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
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
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual Object *getUnitNamed(const AsciiString &name) = 0;
};

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);
};

class CommandButton
{
public:
	Bool isReady(const Object *sourceObj) const;

	unsigned char m_beforeOptions[0x18];
	unsigned int m_options;
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1
};

class Object
{
public:
	const Coord3D *getPosition() const
	{
		return &m_position;
	}

	Player *getControllingPlayer() const;
	Bool bfmeCanUseCommandButton(const CommandButton *button) const;
	void doCommandButtonAtPosition(const CommandButton *button,
		const Coord3D *position, CommandSourceType source, Bool playVoiceResponse);
	void doCommandButtonAtObject(const CommandButton *button, Object *target,
		CommandSourceType source, Bool playVoiceResponse);

private:
	unsigned char m_beforePosition[0x38];
	Coord3D m_position;
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

class PartitionFilterSameMapStatus : public PartitionFilter
{
public:
	PartitionFilterSameMapStatus(const Object *object) : m_object(object) {}

protected:
	virtual Bool allow(Object *object);

private:
	const Object *m_object;
};

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
	Rva000C3DD0VptrZeroBlockObject(
		const VptrZeroBlock24 &first, const VptrZeroBlock24 &second);
	virtual Bool allow(Object *object);

	VptrZeroBlock24 m_first;
	VptrZeroBlock24 m_second;
};

class PartitionFilterPlayerAffiliation : public PartitionFilter
{
public:
	PartitionFilterPlayerAffiliation(const Player *player, unsigned int affiliation,
		Bool match)
		: m_player(player), m_match(match), m_affiliation(affiliation) {}

protected:
	virtual Bool allow(Object *object);

private:
	const Player *m_player;
	Bool m_match;
	unsigned int m_affiliation;
};

class Rva001ED510
{
public:
	Rva001ED510 &set(int a, int b, char c, int d);

private:
	unsigned char m_unmodelled[0x18];
};

class PartitionFilterValidCommandButtonTarget
{
public:
	PartitionFilterValidCommandButtonTarget(Object *source,
		const CommandButton *button, Bool match, CommandSourceType sourceType)
	{
		((Rva001ED510 *)this)->set((int)source, (int)button, match, sourceType);
	}

	PartitionFilter *link(PartitionFilter *next)
	{
		return ((PartitionFilter *)this)->link(next);
	}

private:
	unsigned char m_unmodelled[0x18];
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *position, Real maxDistance,
		Int distanceCalculation, PartitionFilter *filters);
};

extern ScriptEngine *TheScriptEngine;
extern ControlBar *TheControlBar;
extern PartitionManager *ThePartitionManager;

enum AllowPlayerRelationship
{
	ALLOW_SAME_PLAYER = 0x01,
	ALLOW_ALLIES = 0x02,
	ALLOW_ENEMIES = 0x04,
	ALLOW_NEUTRAL = 0x08
};

struct Rva002F9FF0KindOfMask
{
	unsigned int m_dwords[6];

	Rva002F9FF0KindOfMask()
	{
		m_dwords[0] = 0;
		m_dwords[1] = 0;
		m_dwords[2] = 0;
		m_dwords[3] = 0;
		m_dwords[4] = 0;
		m_dwords[5] = 0;
		set(53);
		set(88);
		set(97);
	}

	void set(unsigned int bit)
	{
		m_dwords[bit >> 5] |= 1u << (bit & 31);
	}
};

class ScriptActions
{
protected:
	void doNamedUseCommandButtonOnNearestEnemyUnit(
		const AsciiString &unitName, const AsciiString &commandAbility);
};

// ?doNamedUseCommandButtonOnNearestEnemyUnit@ScriptActions@@IAEXABVAsciiString@@0@Z
void ScriptActions::doNamedUseCommandButtonOnNearestEnemyUnit(
	const AsciiString &unitName, const AsciiString &commandAbility)
{
	Object *unit = TheScriptEngine->getUnitNamed(unitName);
	if (!unit)
		return;

	const CommandButton *button =
		TheControlBar->findCommandButton(commandAbility);
	if (!button)
		return;

	if (!unit->bfmeCanUseCommandButton(button))
		return;

	if (!button->isReady(unit))
		return;

	{
		Rva002F9FF0KindOfMask kindMask;
		PartitionFilterSameMapStatus mapFilter(unit);
		unsigned int options = button->m_options;
		unsigned char targetFlag = (unsigned char)(options >> 5);
		if ((targetFlag & 1) != 0)
		{
			Rva000C3DD0VptrZeroBlockObject kindFilter(
				*(const VptrZeroBlock24 *)&kindMask,
				*(const VptrZeroBlock24 *)&KINDOFMASK_NONE);
			PartitionFilterPlayerAffiliation playerFilter(
				unit->getControllingPlayer(), ALLOW_ENEMIES, true);
			Object *target = ThePartitionManager->getClosestObject(
				unit->getPosition(), 1000000.0f, 0,
				playerFilter.link(kindFilter.link(&mapFilter)));
			if (target)
				unit->doCommandButtonAtPosition(button, target->getPosition(),
					CMD_FROM_SCRIPT, false);
		}
		else
		{
			PartitionFilterValidCommandButtonTarget validFilter(
				unit, button, true, CMD_FROM_SCRIPT);
			Rva000C3DD0VptrZeroBlockObject kindFilter(
				*(const VptrZeroBlock24 *)&kindMask,
				*(const VptrZeroBlock24 *)&KINDOFMASK_NONE);
			PartitionFilterPlayerAffiliation playerFilter(
				unit->getControllingPlayer(), ALLOW_ENEMIES, true);
			Object *target = ThePartitionManager->getClosestObject(
				unit->getPosition(), 1000000.0f, 0,
				playerFilter.link(
					validFilter.link(
						kindFilter.link(&mapFilter))));
			if (target)
				unit->doCommandButtonAtObject(button, target,
					CMD_FROM_SCRIPT, false);
		}
	}
}
