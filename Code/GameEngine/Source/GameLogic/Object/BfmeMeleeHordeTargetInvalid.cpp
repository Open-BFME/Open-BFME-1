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

struct Rva00175820Vector2
{
	Real X;
	Real Y;
	__forceinline Rva00175820Vector2(Real x, Real y) : X(x), Y(y) {}
	__forceinline friend Real operator *(const Rva00175820Vector2 &left,
		const Rva00175820Vector2 &right)
	{
		return left.X * right.X + left.Y * right.Y;
	}
};

union Rva00175820BoolInt
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
	int queryBelowQuarter(void *value);
};

class Rva001BDFF0
{
public:
	Int get();
};

class Object
{
public:
	char m_bfmeHeadA[0x38];
	Coord3D m_position;
	char m_bfmeHeadB[0x94 - 0x44];
	unsigned char m_kindFlags;
	char m_bfmeHeadC[0x204 - 0x95];
	void *m_bfmeAI;
	char m_bfmeHeadD[0x344 - 0x208];
	unsigned char m_privateStatus;
	const Coord3D *getPosition() const { return &m_position; }
};

Bool bfmeMeleeHordeTargetInvalid(Object *source, Object *target)
{
	if (target == 0)
		goto no;
	if (target->m_privateStatus & 1)
		goto no;

	if (target->m_kindFlags & 0x20)
	{
		if (((RvaC4390Second *)target)->resolve(0) != 0)
			target = (Object *)((RvaC4390Second *)target)->resolve(0);
	}

	Coord3D delta;
	delta.set(target->getPosition());
	delta.sub(source->getPosition());
	const Coord3D *direction =
		((Thing *)target)->getUnitDirectionVector2D();
	Rva00175820Vector2 direction2(direction->x, direction->y);
	if (!(direction2 * *(const Rva00175820Vector2 *)&delta
		< BfmeZeroRange))
	{
		BfmeSub1CC_EC3 *locomotor =
			(BfmeSub1CC_EC3 *)((Rva001BDFF0 *)target)->get();
		if (locomotor != 0)
		{
			Rva00175820BoolInt result;
			result.integer = locomotor->queryBelowQuarter(target);
			return result.boolean;
		}
	}

no:
	return false;
}
