// cl: /DNDEBUG /MD /EHs-c-
// RVA-derived type: method of the subobject at Object+0x64, slot 3 of the
// table 0x0109EE28 the Object constructor installs (slot 2 is the matched
// Rva001CA550::getGhostObject).  The body echoes Zero Hour's Object::look():
// no range without a controlling player or a positive shroud-clearing range,
// every player for kind 0x56, otherwise the controller's relationship-3
// players plus the controller's own mask.  It returns the range, or the
// fixed scale for a flagged or effectively dead object.

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short PlayerMaskType;

enum KindOfType
{
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

struct Rva002EE330PlayerList
{
	PlayerMaskType getPlayersWithRelationship(Int playerIndex, Int allowedRelationships, Bool includeSelf);
};

extern Rva002EE330PlayerList *Rva002EE330ThePlayers;

extern const Real BfmeShadowScale;
extern const Real BfmeZeroRange;
extern "C" const Real g_bfmeScaleBK;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	Bool isKindOf(KindOfType kind) const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	Real getShroudClearingRange() const;

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
	if (obj->inlineShroudClearingRange() <= BfmeZeroRange)
		return BfmeShadowScale;

	if (obj->isKindOf(KINDOF_RVA001CA6C0_REVEALS_TO_ALL))
	{
		*lookingMask = 0xffff;
	}
	else
	{
		*lookingMask = (PlayerMaskType)Rva002EE330ThePlayers->getPlayersWithRelationship(
				controller->getPlayerIndex(), 3, false)
			| ((Rva000C9CE0WordGetter *)controller)->get();
	}

	if ((m_status & 1) || (m_privateStatus & 1))
		return g_bfmeScaleBK;

	return obj->getShroudClearingRange();
}
