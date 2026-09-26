// ?d_002a65c0@@YAXXZ
// partial score=0.2473 date=2026-09-26
// ?isWithinAbilityAbortRange@SpecialAbilityUpdate@@QAE_NXZ
// hypothesis h1: preserve the retail position-only override path and explicit squared-range local
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB

typedef float Real;
typedef int Int;
typedef bool Bool;
typedef int ObjectID;

#define BFME_ZERO (*(const Real *)0x01075350)
#define BFME_OFFSET_DF (*(const Real *)0x01098ad4)
#define __max(a, b) (((a) > (b)) ? (a) : (b))

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct BfmePt951
{
	Real x;
	Real y;
};

class GeometryInfo
{
public:
	Bool bfmeIntersects(const Coord3D &, Real, const GeometryInfo &,
		const Coord3D &, Real) const;
};

class Object
{
public:
	Real getDistanceSquared(const Object *) const;

	__forceinline Bool bfmeIntersectsAtZeroAngle(const Object *other) const
	{
		Real otherAngle = other->m_orientation;
		return m_geometryInfo.bfmeIntersects(m_position, 0.0f,
			other->m_geometryInfo, other->m_position, otherAngle);
	}

private:
	unsigned char m_unmodelled_000[0x38];
	Coord3D m_position;
	Real m_orientation;
	unsigned char m_unmodelled_048[0xac - 0x48];
	GeometryInfo m_geometryInfo;
};

class BfmeGap951
{
public:
	Real bfmeGapB951(const BfmePt951 *) const;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class Overridable
{
public:
	virtual ~Overridable();
	Overridable *friend_getFinalOverride();
	Overridable *m_nextOverride;
};

class SpecialPowerTemplate : public Overridable
{
public:
	unsigned char m_unmodelled_008[0x14 - 8];
	Int m_specialPowerType;
};

class SpecialAbilityUpdateModuleData
{
public:
	unsigned char m_unmodelled_000[0x1d8];
	const SpecialPowerTemplate *m_specialPowerTemplate;
	unsigned char m_unmodelled_1dc[0x1ec - 0x1dc];
	Real m_startAbilityRange;
	Real m_abilityAbortRange;
};

class SpecialAbilityUpdate
{
public:
	Bool isWithinAbilityAbortRange();
	__forceinline const SpecialAbilityUpdateModuleData *getSpecialAbilityUpdateModuleData() const
	{
		return m_moduleData;
	}
	__forceinline Object *getObject() const { return m_object; }

private:
	void *m_vtable;
	SpecialAbilityUpdateModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_unmodelled_00c[0xac - 0x0c];
	ObjectID m_targetID;
	Coord3D m_targetPos;
};

// ?isWithinAbilityAbortRange@SpecialAbilityUpdate@@QAE_NXZ
Bool SpecialAbilityUpdate::isWithinAbilityAbortRange()
{
	const SpecialAbilityUpdateModuleData *data = getSpecialAbilityUpdateModuleData();
	Real range = data->m_startAbilityRange;
	const Real UNDERSIZE = BFME_OFFSET_DF;
	range = __max(0.0f, range - UNDERSIZE);
	const SpecialPowerTemplate *spTemplate = data->m_specialPowerTemplate;
	const Object *self = getObject();

	Real fDistSquared = 0.0f;
	const ObjectID targetID = m_targetID;
	Object *target = 0;
	if (targetID != 0)
	{
		target = TheGameLogic->findObjectByID(targetID);
		if (target)
			fDistSquared = self->getDistanceSquared(target);
	}
	else if (m_targetPos.x || m_targetPos.y || m_targetPos.z)
	{
		fDistSquared = ((const BfmeGap951 *)self)->bfmeGapB951(
			(const BfmePt951 *)&m_targetPos);

		Overridable *override = spTemplate->m_nextOverride;
		if (override)
		{
			if (override->m_nextOverride)
				override = override->m_nextOverride->friend_getFinalOverride();
			spTemplate = (const SpecialPowerTemplate *)override;
		}

		if (spTemplate->m_specialPowerType != 0x27)
			fDistSquared -= *(const Real *)0x010c2d4c;
	}
	else
	{
		return true;
	}

	Real fStartRangeSquared = data->m_abilityAbortRange * data->m_abilityAbortRange;
	if (fDistSquared <= fStartRangeSquared)
	{
		if (range == BFME_ZERO && targetID != 0)
			return self->bfmeIntersectsAtZeroAngle(target);
		return true;
	}
	return false;
}
