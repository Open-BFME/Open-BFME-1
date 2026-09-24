// ?effectiveMaxSpeed@BfmeSub1CC_EC3@@QAEMPAX@Z
// Retail RVA 0x001B7E90, 297 bytes.
// cl: /O2 /GR- /DNDEBUG /DWIN32 /MD /EHsc-

typedef bool Bool;
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

class AIUpdateInterface
{
public:
	unsigned char m_pad000[0x1D4];
	Real m_locomotorScale;
};

class Object
{
public:
	Real bfmeGetCrewSpeedMultiplier() const;
	Bool getAttributeModifierMultiplier(int which, Real *value) const;

	unsigned char m_pad000[0x90];
	unsigned int m_status;
	unsigned char m_pad094[0x161];
	unsigned char m_field1F5;
	unsigned char m_pad1F6[0x0A];
	BodyModuleInterface *m_body;
	AIUpdateInterface *m_ai;
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	unsigned char m_pad000[4];
	const Overridable *m_nextOverride;
};

class LocomotorTemplate : public Overridable
{
public:
	unsigned char m_pad008[0x18];
	Real m_damagedSpeedFactor;
	unsigned char m_pad024[0xC4];
	unsigned char m_speedUsesCrew;
	unsigned char m_pad0E9[0x0F];
	Real m_speed;
	unsigned char m_speedUsesCondition;
};

class BfmeSub1CC_EC3
{
public:
	Real effectiveMaxSpeed(void *value);

private:
	unsigned char m_pad000[4];
	const LocomotorTemplate *m_template;
	unsigned char m_pad008[0x20];
	Real m_maxSpeed;
};

class GlobalData
{
public:
	unsigned char m_pad000[0xBD8];
	BodyDamageType m_movementPenaltyDamageState;
};

extern GlobalData *TheWritableGlobalData;
extern volatile Real g_rva001B59ScaleConstant;
extern volatile Real g_rva001B59ScaleConstantNormalAlias;
extern volatile Real g_rva001B59ScaleConstantDamaged;
extern volatile Real g_rva001B59ScaleConstantDamagedAlias;

Real BfmeSub1CC_EC3::effectiveMaxSpeed(void *value)
{
	Object *object = static_cast<Object *>(value);
	BodyDamageType condition = object->m_body->getDamageState();
	Real scale = object->m_ai->m_locomotorScale;
	BodyDamageType penalty = TheWritableGlobalData->m_movementPenaltyDamageState;
	Real speed;

	if (condition < penalty)
	{
		const LocomotorTemplate *conditionTemplate = m_template;
		if (conditionTemplate != 0 && conditionTemplate->m_nextOverride != 0)
			conditionTemplate = static_cast<const LocomotorTemplate *>(
				conditionTemplate->m_nextOverride->getFinalOverride());
		if ((conditionTemplate->m_speedUsesCondition != 0 &&
				 (object->m_status & 0x400000) != 0) || object->m_field1F5 != 0)
		{
			const Overridable *speedTemplate = m_template;
			if (speedTemplate == 0)
			{
				speed = g_rva001B59ScaleConstantDamagedAlias * m_template->m_speed;
			}
			else if (speedTemplate->m_nextOverride != 0)
			{
				speed = g_rva001B59ScaleConstant *
					static_cast<const LocomotorTemplate *>(
						speedTemplate->m_nextOverride->getFinalOverride())->m_speed;
			}
			else
			{
				speed = g_rva001B59ScaleConstant * m_template->m_speed;
			}
		}
		else
		{
			speed = g_rva001B59ScaleConstantNormalAlias;
		}
	}
	else
	{
		const LocomotorTemplate *damagedTemplate = m_template;
		if (damagedTemplate != 0 && damagedTemplate->m_nextOverride != 0)
			damagedTemplate = static_cast<const LocomotorTemplate *>(
				damagedTemplate->m_nextOverride->getFinalOverride());
		speed = g_rva001B59ScaleConstantDamaged *
			damagedTemplate->m_damagedSpeedFactor;
	}

	speed *= scale;
	if (speed > m_maxSpeed)
		speed = m_maxSpeed;

	const LocomotorTemplate *crewTemplate = m_template;
	if (crewTemplate != 0 && crewTemplate->m_nextOverride != 0)
		crewTemplate = static_cast<const LocomotorTemplate *>(
			crewTemplate->m_nextOverride->getFinalOverride());
	if (crewTemplate->m_speedUsesCrew != 0)
		speed *= object->bfmeGetCrewSpeedMultiplier();

	Real modifier = 0.0f;
	if (object->getAttributeModifierMultiplier(7, &modifier))
		speed *= modifier;
	return speed;
}
