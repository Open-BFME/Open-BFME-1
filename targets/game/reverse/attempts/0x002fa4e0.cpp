// ?d_002fa4e0@@YAXXZ
// partial score=0.87 date=2026-09-25
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline
// stlport
// NAMED_USE_COMMANDBUTTON_ON_NEAREST_KINDOF at retail RVA 0x002FA4E0.

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

#define MAKE_KINDOF_MASK(bit) KindOfMaskType(KindOfMaskType::kInit, (bit))

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

class CommandOptions
{
public:
	Bool isSet(unsigned int bit) const
	{
		return ((m_bits >> bit) & 1) != 0;
	}

	Bool isClear(unsigned int bit) const
	{
		return ((~(m_bits >> bit)) & 1) != 0;
	}

	unsigned int m_bits;
};

class CommandButton
{
public:
	Bool isReady(const Object *sourceObj) const;
	unsigned char m_unmodelled_000[0x18];
	CommandOptions m_options;
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

class Rva001ED510
{
public:
	Rva001ED510 &set(int a, int b, char c, int d);

private:
	void *m_dword00;
	int m_dword04;
	int m_dword08;
	int m_dword0c;
	char m_byte10;
	int m_dword14;
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

enum CommandOption
{
	NEED_TARGET_POS = 0x00000020
};

class ScriptActions
{
protected:
	void doNamedUseCommandButtonOnNearestKindof(
		const AsciiString &unitName, const AsciiString &commandAbility,
		Int kindofBit);
};

// ?doNamedUseCommandButtonOnNearestKindof@ScriptActions@@IAEXABVAsciiString@@0H@Z
void ScriptActions::doNamedUseCommandButtonOnNearestKindof(
	const AsciiString &unitName, const AsciiString &commandAbility,
	Int kindofBit)
{
	Object *unit = TheScriptEngine->getUnitNamed(unitName);
	if (!unit)
		return;

	const CommandButton *button =
		TheControlBar->findCommandButton(commandAbility);
	if (!button)
		return;

	if (!button->isReady(unit))
		return;

	if (!unit->bfmeCanUseCommandButton(button))
		return;

	if (button->m_options.isSet(5))
	{
		Object *target = 0;
		{
			PartitionFilterSameMapStatus mapFilter(unit);
			target = ThePartitionManager->getClosestObject(
				unit->getPosition(), 1000000.0f, 0,
				PartitionFilterPlayerAffiliation(
					unit->getControllingPlayer(), ALLOW_ENEMIES, true).link(
					Rva000C3DD0VptrZeroBlockObject(
						*(const VptrZeroBlock24 *)&MAKE_KINDOF_MASK(kindofBit),
						*(const VptrZeroBlock24 *)&KINDOFMASK_NONE).link(&mapFilter)));
		}
		if (target)
			unit->doCommandButtonAtPosition(button, target->getPosition(),
				CMD_FROM_SCRIPT, false);
	}
	else
	{
		Object *target = 0;
		{
			PartitionFilterSameMapStatus mapFilter(unit);
			Rva001ED510 validFilter;
			PartitionFilter *validFilterBase =
				reinterpret_cast<PartitionFilter *>(
					&validFilter.set((int)unit, (int)button, 1,
						CMD_FROM_SCRIPT));
			target = ThePartitionManager->getClosestObject(
				unit->getPosition(), 1000000.0f, 0,
				PartitionFilterPlayerAffiliation(
					unit->getControllingPlayer(), ALLOW_ENEMIES, true).link(
					Rva000C3DD0VptrZeroBlockObject(
						*(const VptrZeroBlock24 *)&MAKE_KINDOF_MASK(kindofBit),
						*(const VptrZeroBlock24 *)&KINDOFMASK_NONE).link(
						validFilterBase->link(&mapFilter))));
		}
		if (target)
			unit->doCommandButtonAtObject(button, target, CMD_FROM_SCRIPT, false);
	}
}




