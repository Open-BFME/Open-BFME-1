// Retail 0x00175820: BFME melee-horde target predicate.

typedef float Real;
typedef int Int;
typedef bool Bool;

extern const Real BfmeZeroRange;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
	void set(const Coord3D *value)
	{
		x = value->x;
		y = value->y;
		z = value->z;
	}
	void sub(const Coord3D *value)
	{
		x -= value->x;
		y -= value->y;
		z -= value->z;
	}
};

struct MeleeHordeVector2
{
	Real X;
	Real Y;
	__forceinline MeleeHordeVector2(Real x, Real y) : X(x), Y(y) {}
	__forceinline friend Real operator *(const MeleeHordeVector2 &left,
		const MeleeHordeVector2 &right)
	{
		return left.X * right.X + left.Y * right.Y;
	}
};

union IntegerBackedBoolResult
{
	int integer;
	Bool boolean;
};

class Thing
{
public:
	const Coord3D *getUnitDirectionVector2D() const;
};

struct RvaC4390First;

class RvaC4390Second
{
public:
	char m_bfmeHead[0x94];
	RvaC4390First *resolve(Int kind);
};

class BfmeSub1CC_EC3
{
public:
	int queryBelowQuarter(void *target);
};

class Rva001BDFF0
{
public:
	Int get();
};

typedef Rva001BDFF0 ObjectCurrentLocomotorFieldGetter;

class Object
{
public:
	char m_bfmeHeadA[0x38];
	Coord3D m_position;
	char m_bfmeHeadB[0x94 - 0x44];
	unsigned char m_statusByteAt0x94;
	char m_bfmeHeadC[0x204 - 0x95];
	void *m_bfmeAI;
	char m_bfmeHeadD[0x344 - 0x208];
	unsigned char m_privateStatus;
	const Coord3D *getPosition() const { return &m_position; }
};

Bool bfmeMeleeHordeTargetInvalid(Object *attacker, Object *candidateVictim)
{
	if (candidateVictim == 0)
		goto no;
	// Retail checks this before member resolution, so the incoming object's bit
	// controls whether any facing or locomotor data is read.
	if (candidateVictim->m_privateStatus & 1)
		goto no;

	// Resolve only after the status check: geometry below may describe a member,
	// while the early-out above always observes the machine's original target.
	// Object+0x94 is a byte view of the status dword; bit 0x20 selects the
	// BFME relation resolver and is separate from any KindOfType value.
	if (candidateVictim->m_statusByteAt0x94 & 0x20)
	{
		if (((RvaC4390Second *)candidateVictim)->resolve(0) != 0)
			candidateVictim = (Object *)((RvaC4390Second *)candidateVictim)->resolve(0);
	}

	Coord3D attackerToVictim;
	attackerToVictim.set(candidateVictim->getPosition());
	attackerToVictim.sub(attacker->getPosition());
	const Coord3D *victimFacingDirection =
		((Thing *)candidateVictim)->getUnitDirectionVector2D();
	MeleeHordeVector2 victimFacingVector2D(
		victimFacingDirection->x, victimFacingDirection->y);
	if (!(victimFacingVector2D * *(const MeleeHordeVector2 *)&attackerToVictim
		< BfmeZeroRange))
	{
		// The guarded getter reads Object+0x204, then AIUpdate+0x1CC; its
		// recovered runtime accessor identity remains unknown.
		BfmeSub1CC_EC3 *currentLocomotor =
			(BfmeSub1CC_EC3 *)((ObjectCurrentLocomotorFieldGetter *)candidateVictim)->get();
		if (currentLocomotor != 0)
		{
			IntegerBackedBoolResult integerBackedBoolResult;
			integerBackedBoolResult.integer = currentLocomotor->queryBelowQuarter(candidateVictim);
			return integerBackedBoolResult.boolean;
		}
	}

no:
	return false;
}
