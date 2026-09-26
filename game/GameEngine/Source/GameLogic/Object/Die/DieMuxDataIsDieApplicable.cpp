// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef bool Bool;
typedef float Real;
typedef int ObjectID;

extern "C" double __cdecl atan2(double y, double x);
extern "C" double __cdecl fabs(double value);
#pragma intrinsic(atan2, fabs)

extern const Real BfmeZeroRange;
extern const Real g_bfmeK1253;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

template <int BitCount> class BitFlags
{
public:
	Bool testSetAndClear(
		const BitFlags &required,
		const BitFlags &exempt) const;

private:
	unsigned int m_words[3];
};

typedef BitFlags<86> ObjectStatusMaskType;

class Object
{
public:
	// Typed semantic view of the BFME-only planar-delta helper. Its retail body
	// subtracts this Object's cached position from the argument's position.
	Coord3D getPlanarDirectionTo(const Object *other) const;

	const ObjectStatusMaskType &getStatusBits() const
	{
		return m_statusBits;
	}

	Real getOrientation() const
	{
		return m_orientation;
	}

private:
	unsigned char m_unreconstructed_000[0x38];
	Coord3D m_position;
	Real m_orientation;
	unsigned char m_unreconstructed_048[0x90 - 0x48];
	ObjectStatusMaskType m_statusBits;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheBfmeGameLogic;
extern Real normalizeAngle(Real angle);

class DamageInfo
{
public:
	unsigned char m_unreconstructed_000[8];
	ObjectID m_sourceID;
	unsigned char m_unreconstructed_00c[0x18 - 0x0c];
	int m_deathType;
	Real m_damageAmount;
};

class DieMuxData
{
public:
	Bool isDieApplicable(const Object *obj, const DamageInfo *damageInfo) const;

private:
	unsigned int m_deathTypes;
	unsigned int m_veterancyLevels;
	ObjectStatusMaskType m_exemptStatus;
	ObjectStatusMaskType m_requiredStatus;
	Real m_damageAmountRequired;
	Real m_minKillerAngle;
	Real m_maxKillerAngle;
};

Bool DieMuxData::isDieApplicable(
	const Object *obj, const DamageInfo *damageInfo) const
{
	if ((m_deathTypes & (1 << (damageInfo->m_deathType - 1))) == 0)
		return false;

	if (!obj->getStatusBits().testSetAndClear(m_requiredStatus, m_exemptStatus))
		return false;

	if (m_damageAmountRequired >= BfmeZeroRange &&
		damageInfo->m_damageAmount < m_damageAmountRequired)
		return false;

	if (!(m_minKillerAngle < m_maxKillerAngle))
		return true;

	Object *killer = TheBfmeGameLogic->findObjectByID(damageInfo->m_sourceID);
	if (killer == 0)
		return false;

	Coord3D killerDirection = obj->getPlanarDirectionTo(killer);
	const Real killerAngle = normalizeAngle(
		obj->getOrientation() - (Real)atan2(killerDirection.y, killerDirection.x));
	const Real midpoint = (m_maxKillerAngle + m_minKillerAngle) * g_bfmeK1253;
	const Real halfRange = m_maxKillerAngle - midpoint;
	const Real relativeAngle = normalizeAngle(killerAngle - midpoint);
	if ((Real)fabs(relativeAngle) > halfRange)
		return false;

	return true;
}
