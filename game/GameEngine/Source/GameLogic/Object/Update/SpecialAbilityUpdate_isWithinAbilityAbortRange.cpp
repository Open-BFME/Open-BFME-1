// Retail 0x002A65C0 (372 bytes), SpecialAbilityUpdate abort-range predicate.
// Identity: matched continuePreparation at 0x002A71E0 calls ILT 0x0004B466
// in the ZH isWithinAbilityAbortRange position; BFME adds power type 0x27.
// Layout: module data fields 0x1D8/0x1EC/0x1F0 are FieldParse witnesses;
// receiver Object at +8 and target ID/position at +0xAC/+0xB0 are retail reads.
// Geometry helper uses the existing byte-return ABI pin at 0x0087F2F0;
// its five stack words are position, angle bits, geometry, position, angle bits.
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB

typedef float Real;
typedef int Int;
typedef bool Bool;
typedef int ObjectID;

// The zero range BFME compares against is the pooled float at retail
// 0x01075350, which holds exactly 0.0f.
#define BFME_ZERO 0.0f
#define BFME_OFFSET_DF 2.5f
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

class BfmeSubYR { public: char bfmeDoYR(void *,void *,void *,void *,int); };

class GeometryInfo {};

class Object
{
public:
	Real getDistanceSquared(const Object *) const;

	__forceinline Bool bfmeIntersectsAtZeroAngle(const Object *other) const
	{
		union { Real angle; int bits; } otherAngle;
		otherAngle.angle = other->m_orientation;
		return ((BfmeSubYR*)&m_geometryInfo)->bfmeDoYR((void*)&m_position,0,
			(void*)&other->m_geometryInfo,(void*)&other->m_position,otherAngle.bits);
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
	Int m_type;
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
	const Object *self = getObject();
	const SpecialPowerTemplate *spTemplate = data->m_specialPowerTemplate;
	range = __max(0.0f, range - UNDERSIZE);

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

		const SpecialPowerTemplate *finalTemplate;
		if (spTemplate->m_nextOverride) {
			if (spTemplate->m_nextOverride->m_nextOverride)
				finalTemplate=(const SpecialPowerTemplate*)spTemplate->m_nextOverride->m_nextOverride->friend_getFinalOverride();
			else finalTemplate=(const SpecialPowerTemplate*)spTemplate->m_nextOverride;
		} else finalTemplate=spTemplate;
		spTemplate=finalTemplate;

		if (spTemplate->m_type == 0x27)
			fDistSquared -= 400.0f;
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

