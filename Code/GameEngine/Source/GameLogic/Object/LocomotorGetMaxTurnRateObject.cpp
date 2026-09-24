// Open-BFME: Locomotor turn-rate query, retail RVA 0x001B5860.
//
// The rotate-toward caller at 0x001B9C50 passes its Object pointer here before
// forwarding the result to the large rotation helper.  Object+0x200 and body
// vtable slot +0x20 are independently established as BodyModuleInterface and
// getDamageState.  The two template fields are angular periods: retail divides
// the 2*pi constant by them before clamping against Locomotor+0x34.

typedef float Real;

enum BodyDamageType
{
	BODY_PRISTINE,
	BODY_DAMAGED,
	BODY_REALLYDAMAGED,
	BODY_RUBBLE
};

class BodyModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual BodyDamageType getDamageState() const = 0;
};

#include "object.h"

class Overridable
{
public:
	const Overridable *getFinalOverride() const
	{
		if (this == 0)
			return this;
		if (m_nextOverride != 0)
			return m_nextOverride->getFinalOverride();
		return this;
	}

	unsigned char m_unmodelled000[4];
	const Overridable *m_nextOverride;
};

class LocomotorTemplate : public Overridable
{
public:
	unsigned char m_unmodelled008[0x20];
	unsigned int m_turnPeriod;
	unsigned int m_damagedTurnPeriod;
};

class GlobalData
{
public:
	unsigned char m_unmodelled000[0xBD8];
	BodyDamageType m_movementPenaltyDamageState;
};

extern GlobalData *TheWritableGlobalData;
extern const Real g_rva001B5860TwoPi;

class Locomotor
{
public:
	Real getMaxTurnRate(Object *object) const;

private:
	unsigned char m_unmodelled000[4];
	const LocomotorTemplate *m_template;
	unsigned char m_unmodelled008[0x2C];
	Real m_maxTurnRate;
};

// ?getMaxTurnRate@Locomotor@@QBEMPAVObject@@@Z
Real Locomotor::getMaxTurnRate(Object *object) const
{
	BodyDamageType condition = object->m_body->getDamageState();
	Real turnRate;

	if (condition < TheWritableGlobalData->m_movementPenaltyDamageState)
	{
		turnRate = g_rva001B5860TwoPi /
			(Real)static_cast<const LocomotorTemplate *>(
				m_template->getFinalOverride())->m_turnPeriod;
	}
	else
	{
		turnRate = g_rva001B5860TwoPi /
			(Real)static_cast<const LocomotorTemplate *>(
				m_template->getFinalOverride())->m_damagedTurnPeriod;
	}

	if (turnRate > m_maxTurnRate)
		turnRate = m_maxTurnRate;

	return turnRate;
}
