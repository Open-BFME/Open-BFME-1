// cl: /O2 /GR- /DNDEBUG /DWIN32 /MD /EHsc-
// Retail 0x001BC820 is a second locomotor movement dispatcher.  Its named
// callees and the appearance jump table distinguish it from the already
// claimed Locomotor::locoUpdate_moveTowardsPosition at 0x002BAFB8.

// The retail compiler keeps each guarded owner load in an explicit shared
// merge: test the interface, load the owner or zero EAX, then test EAX again.
// This intrinsic is only a compiler ordering barrier used to preserve that
// source-level merge; it emits no instruction bytes.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

#include <string.h>
#pragma intrinsic(memcpy)

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
	Real m_template;
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

class Rva001B7E90Receiver
{
public:
	Real query(Object *obj);
};

class AIUpdateInterface
{
public:
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
	void move(Object *obj, const Coord3D *goalPos, Real onPathDistToGoal,
		Real desiredSpeed);
};

class Rva001BB530Mover
{
public:
	void move(Object *obj, const Coord3D *goalPos, Real onPathDistToGoal,
		Real desiredSpeed);
};

class Rva001BC560Mover
{
public:
	void move(Object *obj, const Coord3D *goalPos, Real onPathDistToGoal,
		Real desiredSpeed);
};

class Rva001BB0D0Mover
{
public:
	void move(Object *obj, const Coord3D *goalPos, Real onPathDistToGoal,
		Real desiredSpeed);
};

class Rva001BA1C0Handler
{
public:
	void behavior(Object *obj, const Coord3D *goalPos);
};

class Rva001BBBC0Mover
{
public:
	void move(Object *obj, const Coord3D *goalPos, Real onPathDistToGoal,
		Real desiredSpeed);
};

class Rva001BC510Mover
{
public:
	void move(Object *obj, const Coord3D *goalPos, Real onPathDistToGoal,
		Real desiredSpeed);
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
	// Copy the transform representation in twelve four-byte pieces. Keeping
	// the source and destination pointers materialized preserves retail codegen
	// without accessing float storage through an incompatible integer pointer.
	Matrix3D *saved = &m_savedTransform;
	const Matrix3D *live = &obj->m_transform;
	memcpy(&saved->m_cell[0], &live->m_cell[0], sizeof(Real));
	memcpy(&saved->m_cell[1], &live->m_cell[1], sizeof(Real));
	memcpy(&saved->m_cell[2], &live->m_cell[2], sizeof(Real));
	memcpy(&saved->m_cell[3], &live->m_cell[3], sizeof(Real));
	memcpy(&saved->m_cell[4], &live->m_cell[4], sizeof(Real));
	memcpy(&saved->m_cell[5], &live->m_cell[5], sizeof(Real));
	memcpy(&saved->m_cell[6], &live->m_cell[6], sizeof(Real));
	memcpy(&saved->m_cell[7], &live->m_cell[7], sizeof(Real));
	memcpy(&saved->m_cell[8], &live->m_cell[8], sizeof(Real));
	memcpy(&saved->m_cell[9], &live->m_cell[9], sizeof(Real));
	memcpy(&saved->m_cell[10], &live->m_cell[10], sizeof(Real));
	memcpy(&saved->m_cell[11], &live->m_cell[11], sizeof(Real));

	if (TheBfmeGameLogic->m_stamp <= m_stampLimit && desiredSpeed > m_maxSpeed)
		desiredSpeed = m_maxSpeed;

	Real cap = ((Rva001B7E90Receiver *)this)->query(obj);
	if (desiredSpeed > cap)
		desiredSpeed = cap;

	if (obj->m_blocker && obj->m_blocker->m_blocked)
		return;
	if (obj->m_statusBits & 0x10)
		return;

	m_moving = 0;
	BfmeOwnerJC *owner;
	if (obj->m_ai)
	{
		owner = obj->m_ai->m_owner;
	}
	else
	{
		owner = 0;
	}
	// Keep the compiler from collapsing the explicit zero/owner merge; the
	// intrinsic above has no emitted bytes.
	_ReadWriteBarrier();
	if (owner)
		m_moving = owner->bfmeNearJC();

	if (!obj->isKindOf((KindOfType)0x85) && obj->m_ai &&
		!obj->m_ai->layersCompatible(&goalPos) &&
		!((BfmeThingEGF *)obj->m_ai)->bfmeGoEGFa() &&
		((Rva00270360Query *)obj->m_ai)->test())
		return;

	LocomotorTemplate *locoTemplate = m_template;
	if (locoTemplate && locoTemplate->m_nextOverride)
		locoTemplate = (LocomotorTemplate *)locoTemplate->m_nextOverride->getFinalOverride();

	switch (locoTemplate->m_appearance)
	{
		case 0:
		case 4:
		case 7:
			((Rva001B9D00Mover *)this)->move(obj, &goalPos,
				onPathDistToGoal, desiredSpeed);
			break;
		case 6:
			((Rva001BB530Mover *)this)->move(obj, &goalPos,
				onPathDistToGoal, desiredSpeed);
			break;
		case 2:
			((Rva001BC560Mover *)this)->move(obj, &goalPos,
				onPathDistToGoal, desiredSpeed);
			break;
		case 8:
			((Rva001BB0D0Mover *)this)->move(obj, &goalPos,
				onPathDistToGoal, desiredSpeed);
			break;
		case 3:
			((Rva001BC510Mover *)this)->move(obj, &goalPos,
				onPathDistToGoal, desiredSpeed);
			break;
		case 1:
			((Rva001BB0D0Mover *)this)->move(obj, &goalPos,
				onPathDistToGoal, desiredSpeed);
			break;
		case 5:
			break;
		default:
			((Rva001BBBC0Mover *)this)->move(obj, &goalPos,
				onPathDistToGoal, desiredSpeed);
			break;
	}

	BfmeOwnerJC *tail;
	if (obj->m_ai)
	{
		tail = obj->m_ai->m_owner;
	}
	else
	{
		tail = 0;
	}
	// As above, this compiler-only barrier retains the retail shared merge and
	// contributes no machine-code instruction.
	_ReadWriteBarrier();
	if (!(tail && ((Rva001B3FE0 *)tail)->test()))
		((Rva001BA1C0Handler *)this)->behavior(obj, &goalPos);

	((Thing *)obj)->rva00132200(&m_savedTransform);
	m_moving = 0;
}
