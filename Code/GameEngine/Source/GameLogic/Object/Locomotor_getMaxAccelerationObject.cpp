// ?getMaxAcceleration@Locomotor@@QBEMPAVObject@@W4BodyDamageType@@@Z
// Retail RVA 0x001B5A30, 148 bytes.

typedef float Real;

enum BodyDamageType
{
	BODY_OK,
	BODY_DAMAGED,
};

class Overridable
{
public:
	const Overridable *getFinalOverride(void) const
	{
		if (this == 0)
			return this;
		if (m_nextOverride != 0)
			return m_nextOverride->getFinalOverride();
		return this;
	}

	char m_head[4];
	const Overridable *m_nextOverride;
};

struct LocomotorTemplate : Overridable
{
	char m_pad0c[0x3c];
	Real m_acceleration;
	Real m_accelerationDamaged;
};

struct AIUpdateInterface
{
	char m_head[0x1d4];
	Real m_locomotorScale;
};

#include "object.h"

class GlobalData
{
public:
	char m_head[0xbd8];
	BodyDamageType m_movementPenaltyDamageState;
};

extern volatile Real g_rva001B59ScaleConstant;

// Distinct external identities keep MSVC 7.1 from factoring the two x87
// multiplies into the shared tail. All four names resolve to the same retail
// field at 0x00EACFE0.
extern volatile Real g_rva001B59ScaleConstantNormalAlias;
extern volatile Real g_rva001B59ScaleConstantDamaged;
extern volatile Real g_rva001B59ScaleConstantDamagedAlias;
extern GlobalData *TheWritableGlobalData;

class Locomotor
{
public:
	Real getMaxAcceleration(Object *object, BodyDamageType condition) const;

private:
	char m_head[4];
	const LocomotorTemplate *m_template;
	char m_pad0c[0x1c];
	Real m_maxAcceleration;
};

Real Locomotor::getMaxAcceleration(Object *object, BodyDamageType condition) const
{
	Real scale = object->m_ai->m_locomotorScale;
	Real result;
	if (condition < TheWritableGlobalData->m_movementPenaltyDamageState)
		result = (g_rva001B59ScaleConstant * g_rva001B59ScaleConstantNormalAlias) *
			static_cast<const LocomotorTemplate *>(m_template->getFinalOverride())->m_acceleration;
	else
		result = (g_rva001B59ScaleConstantDamaged * g_rva001B59ScaleConstantDamagedAlias) *
			static_cast<const LocomotorTemplate *>(m_template->getFinalOverride())->m_accelerationDamaged;

	result *= scale;
	if (result > m_maxAcceleration)
		result = m_maxAcceleration;
	return result;
}
