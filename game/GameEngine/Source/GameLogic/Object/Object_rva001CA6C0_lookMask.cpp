// cl: /DNDEBUG /MD /EHs-c-
// RVA-derived types: methods of the subobject at Object+0x64, slots 3 and 4 of
// the table 0x0109EE28 the Object constructor installs.

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short PlayerMaskType;

enum KindOfType
{
	KINDOF_STRUCTURE = 7,
	KINDOF_RVA001CA6C0_REVEALS_TO_ALL = 0x56
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Int getPlayerIndex() const { return m_playerIndex; }

private:
	unsigned char m_pad00[0x24];
	Int m_playerIndex;
};

class Rva000C9CE0WordGetter
{
public:
	PlayerMaskType get() const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Player *getControllingPlayer() const;
};

// The singleton itself is retail's PlayerList (game/GameEngine/Source/Common/RTS/PlayerList.cpp
// defines `PlayerList *ThePlayerList`); only the member this body calls is still
// address-named, so the global keeps its real spelling and the call is cast.
class PlayerList;

struct Rva002EE330PlayerList
{
	PlayerMaskType getPlayersWithRelationship(Int playerIndex, Int allowedRelationships, Bool includeSelf);
};

extern PlayerList *ThePlayerList;	// retail [0x012ED748]

extern const Real BfmeShadowScale;
extern const Real g_rva01075350;
extern "C" const Real g_bfmeScaleBK;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
public:
	unsigned char m_pad00[0x3a4];
	Real m_visionRange;
	unsigned char m_pad3a8[0x40c - 0x3a8];
	Real m_rva001CA7D0Range40C;
	unsigned char m_pad410[0x47a - 0x410];
	UnsignedShort m_buildCost;
	unsigned char m_pad47c[0x47e - 0x47c];
	UnsignedShort m_threatValue;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	const ThingTemplate *getTemplate() const;
	Bool isKindOf(KindOfType kind) const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	Real getShroudClearingRange() const;
	Real getVisionRange() const;
	Player *getControllingPlayer() const;

	// The same body as the out-of-line getShroudClearingRange, which retail
	// inlines here once and calls once.
	Real inlineShroudClearingRange() const
	{
		unsigned char flags = m_statusFlags;
		Real shroudClearingRange = m_shroudClearingRange;
		if (flags & 4)
			shroudClearingRange = m_altShroudClearingRange;
		return shroudClearingRange;
	}

private:
	unsigned char m_pad00[0x90];
	unsigned char m_statusFlags;
	unsigned char m_pad91[0xbc - 0x91];
	Real m_altShroudClearingRange;
	unsigned char m_padc0[0x198 - 0xc0];
	Real m_shroudClearingRange;
};

class Rva001CA6C0
{
public:
	Real rva001CA6C0(UnsignedInt *lookingMask);

private:
	Object *getObject() { return (Object *)((char *)this - 0x64); }

	unsigned char m_pad00[0x2c];
	unsigned char m_status;
	unsigned char m_pad2d[0x1d8 - 0x2d];
	Team *m_team;
	unsigned char m_pad1dc[0x2e0 - 0x1dc];
	unsigned char m_privateStatus;
	unsigned char m_pad2e1[0x304 - 0x2e1];
	Bool m_flag304;
};

// ?rva001CA6C0@Rva001CA6C0@@QAEMPAI@Z
Real Rva001CA6C0::rva001CA6C0(UnsignedInt *lookingMask)
{
	if (!m_flag304)
		return BfmeShadowScale;

	Player *controller = m_team ? m_team->getControllingPlayer() : 0;
	if (!controller)
		return BfmeShadowScale;

	Object *obj = getObject();
	if (obj->inlineShroudClearingRange() <= g_rva01075350)
		return BfmeShadowScale;

	if (obj->isKindOf(KINDOF_RVA001CA6C0_REVEALS_TO_ALL))
	{
		*lookingMask = 0xffff;
	}
	else
	{
		*lookingMask = (PlayerMaskType)((Rva002EE330PlayerList *)ThePlayerList)->getPlayersWithRelationship(
				controller->getPlayerIndex(), 3, false)
			| ((Rva000C9CE0WordGetter *)controller)->get();
	}

	if ((m_status & 1) || (m_privateStatus & 1))
		return g_bfmeScaleBK;

	return obj->getShroudClearingRange();
}

// Object+0x200 holds an object whose vtable slot 4 yields a Real; its type is
// not proven.
class Rva001CA7D0Source
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual Real slot04();
};

// Slot 4: for mode 0 or 1 it reports a template value (m_buildCost or
// m_threatValue), the controller's single-player mask and a range; anything
// else, no controller, or no shroud-clearing range yields the fixed scale and
// a zero value.
class Rva001CA7D0
{
public:
	Real rva001CA7D0(Int mode, UnsignedInt *value, UnsignedInt *playerMask);

private:
	Object *getObject() { return (Object *)((char *)this - 0x64); }

	unsigned char m_pad00[0x2c];
	unsigned char m_status;
	unsigned char m_pad2d[0x19c - 0x2d];
	Rva001CA7D0Source *m_source200;
	unsigned char m_pad1a0[0x1d8 - 0x1a0];
	Team *m_team;
	unsigned char m_pad1dc[0x2e0 - 0x1dc];
	unsigned char m_privateStatus;
	unsigned char m_pad2e1[0x304 - 0x2e1];
	Bool m_flag304;
};

// ?rva001CA7D0@Rva001CA7D0@@QAEMHPAI0@Z
Real Rva001CA7D0::rva001CA7D0(Int mode, UnsignedInt *value, UnsignedInt *playerMask)
{
	if (!m_flag304)
		return BfmeShadowScale;

	if (mode < 0 || mode > 1 || !m_team)
	{
		Real noRange = BfmeShadowScale;
		*value = 0;
		return noRange;
	}
	if (!m_team->getControllingPlayer())
	{
		Real noRange = BfmeShadowScale;
		*value = 0;
		return noRange;
	}

	if ((m_status & 4) || (m_privateStatus & 1)
		|| getObject()->getShroudClearingRange() <= g_rva01075350)
	{
		Real noRange = BfmeShadowScale;
		*value = 0;
		return noRange;
	}

	switch (mode)
	{
	case 0:
		*value = getObject()->getTemplate()->m_buildCost;
		*playerMask = (PlayerMaskType)(1 << getObject()->getControllingPlayer()->getPlayerIndex());
		return getObject()->getVisionRange();

	case 1:
	{
		*value = getObject()->getTemplate()->m_threatValue;
		*playerMask = (PlayerMaskType)(1 << getObject()->getControllingPlayer()->getPlayerIndex());
		Real range = getObject()->getTemplate()->m_rva001CA7D0Range40C;
		if (range == BfmeShadowScale && !getObject()->isKindOf(KINDOF_STRUCTURE))
		{
			*value = (Int)m_source200->slot04();
			range = getObject()->getTemplate()->m_visionRange;
		}
		return range;
	}

	default:
		Real noRange = BfmeShadowScale;
		*value = 0;
		return noRange;
	}
}
