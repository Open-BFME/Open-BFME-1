// ?rva001CA7D0@Rva001CA7D0@@QAEMHPAI0@Z
// partial score=0.61 date=2026-09-24
// cl: /DNDEBUG /MD /EHs-c-
// RVA-derived type: method of the subobject at Object+0x64, slot 4 of the
// table 0x0109EE28 the Object constructor installs (slot 3 is the matched
// Rva001CA6C0 look-mask body).  For mode 0 or 1 it reports a template value
// (m_buildCost or m_threatValue), the controller's single-player mask and a
// range; anything else, no controller, or no shroud-clearing range yields the
// fixed scale and a zero value.

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short PlayerMaskType;

enum KindOfType
{
	KINDOF_STRUCTURE = 7
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Int getPlayerIndex() const { return m_playerIndex; }

private:
	unsigned char m_pad00[0x24];
	Int m_playerIndex;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Player *getControllingPlayer() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
public:
	Real getRva001CA7D0Range40C() const { return m_rva001CA7D0Range40C; }

	unsigned char m_pad00[0x3a4];
	Real m_visionRange;
	unsigned char m_pad3a8[0x40c - 0x3a8];
	Real m_rva001CA7D0Range40C;
	unsigned char m_pad410[0x47a - 0x410];
	UnsignedShort m_buildCost;
	unsigned char m_pad47c[0x47e - 0x47c];
	UnsignedShort m_threatValue;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	const ThingTemplate *getTemplate() const;
	Bool isKindOf(KindOfType kind) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	Real getShroudClearingRange() const;
	Real getVisionRange() const;
	Player *getControllingPlayer() const;
};

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

extern const Real BfmeShadowScale;
extern const Real BfmeZeroRange;

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

	Object *obj = getObject();
	if ((m_status & 4) || (m_privateStatus & 1)
		|| obj->getShroudClearingRange() <= BfmeZeroRange)
	{
		Real noRange = BfmeShadowScale;
		*value = 0;
		return noRange;
	}

	switch (mode)
	{
	case 0:
		*value = obj->getTemplate()->m_buildCost;
		*playerMask = (PlayerMaskType)(1 << obj->getControllingPlayer()->getPlayerIndex());
		return obj->getVisionRange();

	case 1:
	{
		*value = obj->getTemplate()->m_threatValue;
		*playerMask = (PlayerMaskType)(1 << obj->getControllingPlayer()->getPlayerIndex());
		Real range = obj->getTemplate()->getRva001CA7D0Range40C();
		if (BfmeShadowScale != range || obj->isKindOf(KINDOF_STRUCTURE))
			return range;

		*value = (Int)m_source200->slot04();
		return obj->getTemplate()->m_visionRange;
	}

	default:
		Real noRange = BfmeShadowScale;
		*value = 0;
		return noRange;
	}
}
