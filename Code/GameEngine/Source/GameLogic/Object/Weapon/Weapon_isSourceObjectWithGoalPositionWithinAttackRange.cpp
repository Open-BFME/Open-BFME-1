// ?isSourceObjectWithGoalPositionWithinAttackRange@Weapon@@QBE_NPBVObject@@PBUCoord3D@@01@Z

typedef float Real;
typedef bool Bool;

class Object;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct BfmePointNC;
class BfmeThingNC;

class Gen_001E24F0
{
public:
	Real bfmeGapSqAt(const BfmePointNC *point, const BfmeThingNC *thing) const;
};

struct BfmePt951;

class BfmeGap951
{
public:
	Real bfmeGapA951(const BfmePt951 *a, const BfmePt951 *b) const;
};

extern Real g_bfmeOffsetDF;
extern const Real BfmeZeroRange;

struct BfmeWeaponTemplateRangeFields
{
	char m_padding00[0x18];
	Real m_minimumAttackRange;
};

class Weapon
{
public:
	Bool isSourceObjectWithGoalPositionWithinAttackRange(const Object *source,
		const Coord3D *goalPos, const Object *target, const Coord3D *targetPos) const;
	Real getAttackRange(const Object *source, Real heightDifference) const;
};

Bool Weapon::isSourceObjectWithGoalPositionWithinAttackRange(const Object *source,
	const Coord3D *goalPos, const Object *target, const Coord3D *targetPos) const
{
	Real distSqr;
	const Coord3D *otherPos;
	if (target)
	{
		distSqr = ((const Gen_001E24F0 *)source)->bfmeGapSqAt(
			(const BfmePointNC *)goalPos, (const BfmeThingNC *)target);
		otherPos = (const Coord3D *)((const char *)target + 0x38);
	}
	else if (targetPos)
	{
		distSqr = ((const BfmeGap951 *)source)->bfmeGapA951(
			(const BfmePt951 *)goalPos, (const BfmePt951 *)targetPos);
		otherPos = targetPos;
	}
	else
	{
		return false;
	}

	Real attackRange = getAttackRange(source, otherPos->z - goalPos->z);
	Real attackRangeSqr = attackRange * attackRange;
	Real minAttackRange =
		(*(const BfmeWeaponTemplateRangeFields **)((const char *)this + 4))->m_minimumAttackRange - g_bfmeOffsetDF;
	if (minAttackRange < BfmeZeroRange)
		minAttackRange = BfmeZeroRange;
	Real minAttackRangeSqr = minAttackRange * minAttackRange;
	if (distSqr < minAttackRangeSqr)
		return false;
	return distSqr <= attackRangeSqr;
}
