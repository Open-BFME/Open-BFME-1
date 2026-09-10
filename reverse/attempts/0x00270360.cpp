// ?test@Rva00270360Query@@QAE_NXZ
// partial score=0.82 date=2026-09-10
// Retail 0x00270360: the AI update predicate reached directly from the
// matched Rva001BC820 locomotor dispatcher.

typedef bool Bool;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class AIUpdateInterface
{
public:
	void destroyPath();
};

class Thing
{
public:
	void setOrientation(Real angle);
	const Coord3D *getUnitDirectionVector2D() const;
	void setPosition(const Coord3D *position);

	unsigned char m_head[0x38];
	Real m_x;
	Real m_y;
	Real m_z;
	Real m_orientation;
	unsigned char m_pad048[0x204 - 0x48];
	AIUpdateInterface *m_ai;
	unsigned char m_pad208[0x214 - 0x208];
	Thing *m_containedBy;
};

extern Real __cdecl normalizeAngle(Real);

#define BfmePi (*(const Real *)0x01087B14)
#define BfmeDirectionScale (*(const Real *)0x01095F8C)

class Rva00270360Query
{
public:
	Bool test();

	unsigned char m_head[8];
	Thing *m_object;
	unsigned char m_pad00C[0x33C - 0x0C];
	int m_queryCount;
};

Bool Rva00270360Query::test()
{
	Thing *target = m_object;
	if (target == 0)
		return false;

	int queryCount = m_queryCount;
	m_queryCount = queryCount + 1;
	if (queryCount > 3)
		return false;

	Thing *contained = target->m_containedBy;
	if (contained != 0)
	{
		target = contained;
		if (target->m_ai == 0)
			return false;
	}

	target->setOrientation(normalizeAngle(target->m_orientation + BfmePi));

	const Coord3D *direction = target->getUnitDirectionVector2D();
	Coord3D position;
	position.x = direction->x;
	position.y = direction->y;
	position.z = direction->z;
	position.x *= BfmeDirectionScale;
	position.y *= BfmeDirectionScale;
	position.z *= BfmeDirectionScale;
	position.x += target->m_x;
	position.y += target->m_y;
	position.z += target->m_z;
	target->setPosition(&position);

	target->m_ai->destroyPath();
	return true;
}
