// ?locoUpdate_moveTowardsPosition@Rva001BC820Locomotor@@QAEXPAVObject@@ABUCoord3D@@MMPA_N@Z
// partial score=0.62 date=2026-09-10
// cl: /O2 /GR- /DNDEBUG /DWIN32 /MD /EHsc-
// Retail 0x001BC820 is a second locomotor move dispatcher, distinct from the
// claimed Locomotor body at 0x002BAFB8; same argument shape, own appearance switch.

typedef bool Bool;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Matrix3D
{
public:
	Real m_cell[12];
};

enum KindOfType { KINDOF_FIRST };

class Object;

class Thing
{
public:
	void rva00132200(const Matrix3D *matrix);
	Bool isKindOf(KindOfType kind) const;

	void *m_vtable;
	Real m_pad004;
	Matrix3D m_transform;
};

class BfmeOwnerJC
{
public:
	char bfmeNearJC();
};

class BfmeThingEGF
{
public:
	Bool bfmeGoEGFa();
};

class Rva00270360Query
{
public:
	Bool test();
};

class Rva001B3FE0
{
public:
	Bool test() const;
};

class AIUpdateInterface
{
public:
	Real getFormationMovementSpeed(Object *obj);
	Bool layersCompatible(const Coord3D *pos) const;

	char m_pad000[0x140];
	BfmeOwnerJC *m_owner;
};

class Rva001BC820Blocker
{
public:
	char m_pad000[0x5c];
	char m_blocked;
};

class Object : public Thing
{
public:
	AIUpdateInterface *getAI() const { return m_ai; }
	BfmeOwnerJC *getOwner() const
	{
		BfmeOwnerJC *owner;
		if (m_ai)
			owner = m_ai->m_owner;
		else
			owner = 0;
		return owner;
	}

	char m_pad038[0x94 - 0x38];
	unsigned char m_statusBits;
	char m_pad095[0x204 - 0x95];
	AIUpdateInterface *m_ai;
	Rva001BC820Blocker *m_blocker;
};

class Overridable
{
public:
	Overridable *getFinalOverride();

	void *m_vtable;
	Overridable *m_nextOverride;
};

class LocomotorTemplate : public Overridable
{
public:
	char m_pad008[0x70 - 0x08];
	int m_appearance;
};

class Rva001B9D00Mover
{
public:
	void move(void *obj, int goalPos, int onPathDistToGoal, int desiredSpeed);
};

class Rva001BB530Mover
{
public:
	void move(void *obj, int goalPos, int onPathDistToGoal, int desiredSpeed);
};

class Rva001BC560Mover
{
public:
	void move(void *obj, int goalPos, int onPathDistToGoal, int desiredSpeed);
};

class Rva001BB0D0Mover
{
public:
	void move(void *obj, int goalPos, int onPathDistToGoal, int desiredSpeed);
};

class Rva001BA1C0Handler
{
public:
	void behavior(void *obj, void *goalPos);
};

class BfmeQ1282;

class BfmeA1282
{
public:
	void bfmeGo1282(BfmeQ1282 *object, int a, int b, int c);
	void bfmeGo1286(BfmeQ1282 *object, int a, int b, int c);
};

struct Rva00367E30Logic
{
	char m_pad000[0x3c];
	unsigned m_stamp;
};

extern Rva00367E30Logic *TheBfmeGameLogic;

class Rva001BC820Locomotor
{
public:
	void locoUpdate_moveTowardsPosition(Object *obj, const Coord3D &goalPos,
		Real onPathDistToGoal, Real desiredSpeed, Bool *blocked);

private:
	void *m_vtable;
	LocomotorTemplate *m_template;
	char m_pad008[0x40 - 0x08];
	unsigned m_flags;
	char m_pad044[0x58 - 0x44];
	Real m_maxSpeed;
	unsigned m_stampLimit;
	char m_pad060[0x64 - 0x60];
	Matrix3D m_savedTransform;
	char m_pad094[1];
	char m_moving;
};

void Rva001BC820Locomotor::locoUpdate_moveTowardsPosition(Object *obj,
	const Coord3D &goalPos, Real onPathDistToGoal, Real desiredSpeed, Bool *blocked)
{
	unsigned flags = m_flags;
	flags &= ~4u;
	m_flags = flags;
	int *saved = (int *)&m_savedTransform;
	const int *live = (const int *)&obj->m_transform;
	saved[0] = live[0];
	saved[1] = live[1];
	saved[2] = live[2];
	saved[3] = live[3];
	saved[4] = live[4];
	saved[5] = live[5];
	saved[6] = live[6];
	saved[7] = live[7];
	saved[8] = live[8];
	saved[9] = live[9];
	saved[10] = live[10];
	saved[11] = live[11];

	if (TheBfmeGameLogic->m_stamp <= m_stampLimit && desiredSpeed > m_maxSpeed)
		desiredSpeed = m_maxSpeed;

	Real cap = ((AIUpdateInterface *)this)->getFormationMovementSpeed(obj);
	if (desiredSpeed > cap)
		desiredSpeed = cap;

	if (obj->m_blocker && obj->m_blocker->m_blocked)
		return;
	if (obj->m_statusBits & 0x10)
		return;

	m_moving = 0;
	BfmeOwnerJC *owner = obj->getOwner();
	if (owner)
		m_moving = owner->bfmeNearJC();

	if (!obj->isKindOf((KindOfType)0x85) && obj->getAI() &&
		!obj->getAI()->layersCompatible(&goalPos) &&
		!((BfmeThingEGF *)obj->getAI())->bfmeGoEGFa() &&
		((Rva00270360Query *)obj->getAI())->test())
		return;

	LocomotorTemplate *locoTemplate = m_template;
	if (locoTemplate && locoTemplate->m_nextOverride)
		locoTemplate = (LocomotorTemplate *)locoTemplate->m_nextOverride->getFinalOverride();

	switch (locoTemplate->m_appearance)
	{
		case 0:
		case 4:
		case 7:
			((Rva001B9D00Mover *)this)->move(obj, (int)&goalPos,
				*(int *)&onPathDistToGoal, *(int *)&desiredSpeed);
			break;
		case 6:
			((Rva001BB530Mover *)this)->move(obj, (int)&goalPos,
				*(int *)&onPathDistToGoal, *(int *)&desiredSpeed);
			break;
		case 2:
			((Rva001BC560Mover *)this)->move(obj, (int)&goalPos,
				*(int *)&onPathDistToGoal, *(int *)&desiredSpeed);
			break;
		case 8:
			((Rva001BB0D0Mover *)this)->move(obj, (int)&goalPos,
				*(int *)&onPathDistToGoal, *(int *)&desiredSpeed);
			break;
		case 3:
			((BfmeA1282 *)this)->bfmeGo1286((BfmeQ1282 *)obj, (int)&goalPos,
				*(int *)&onPathDistToGoal, *(int *)&desiredSpeed);
			break;
		case 1:
			((Rva001BB0D0Mover *)this)->move(obj, (int)&goalPos,
				*(int *)&onPathDistToGoal, *(int *)&desiredSpeed);
			break;
		case 5:
			break;
		default:
			((BfmeA1282 *)this)->bfmeGo1282((BfmeQ1282 *)obj, (int)&goalPos,
				*(int *)&onPathDistToGoal, *(int *)&desiredSpeed);
			break;
	}

	BfmeOwnerJC *tail = obj->getOwner();
	if (!(tail && ((Rva001B3FE0 *)tail)->test()))
		((Rva001BA1C0Handler *)this)->behavior(obj, (void *)&goalPos);

	((Thing *)obj)->rva00132200(&m_savedTransform);
	m_moving = 0;
}
