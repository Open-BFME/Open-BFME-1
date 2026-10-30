// cl: /O2 /GR- /DNDEBUG /DWIN32 /MD /EHsc-
// Retail 0x001BC820 is a second locomotor movement dispatcher.  Its named
// callees and the appearance jump table distinguish it from the already
// claimed Locomotor::locoUpdate_moveTowardsPosition at 0x002BAFB8. Its caller
// Locomotor::locoUpdate_moveTowardsAngle (0x001BCE20) is defined at the end of
// this unit.

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
	Coord3D() {}
	~Coord3D() {}
	Coord3D(const Coord3D &that) { x = that.x; y = that.y; z = that.z; }

	Real x;
	Real y;
	Real z;
};

// Retail copies the saved transform row by row, as WWMath's Matrix3D
// assignment does; the member names follow WWMath's Vector4/Matrix3D.
class Vector4
{
public:
	__forceinline Vector4 &operator=(const Vector4 &v)
	{
		X = v.X;
		Y = v.Y;
		Z = v.Z;
		W = v.W;
		return *this;
	}

	Real X;
	Real Y;
	Real Z;
	Real W;
};

class Matrix3D
{
public:
	__forceinline Matrix3D &operator=(const Matrix3D &m)
	{
		Row[0] = m.Row[0];
		Row[1] = m.Row[1];
		Row[2] = m.Row[2];
		return *this;
	}

	Vector4 Row[3];
};

enum KindOfType { KINDOF_FIRST };

class Object;

class Thing
{
public:
	void rva00132200(const Matrix3D *matrix);
	Bool isKindOf(KindOfType kind) const;
	const Matrix3D *getTransformMatrix() const { return &m_transform; }
	void setTransformMatrix(const Matrix3D *matrix);

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
	Real effectiveMaxSpeed(Object *obj);
};

class AIUpdateInterface
{
public:
	Bool layersCompatible(const Coord3D *pos) const;

	char m_pad000[0x140];
	BfmeOwnerJC *m_path;
};

class Rva001BC820Blocker
{
public:
	char m_pad000[0x5c];
	char m_blocked;
};

class ObjectModule;

class Object : public Thing
{
public:
	const Coord3D *getPosition() const { return &m_cachedPos; }
	Real getAngle() const { return m_angle; }

	Coord3D m_cachedPos;
	Real m_angle;
	char m_pad048[0x94 - 0x48];
	unsigned char m_statusBits;
	char m_pad095[0x1fc - 0x95];
	ObjectModule *m_module;
	char m_pad200[0x204 - 0x200];
	AIUpdateInterface *m_ai;
	Rva001BC820Blocker *m_blocker;
};

class Overridable
{
public:
	Overridable *getFinalOverride();
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

	void *m_vtable;
	Overridable *m_nextOverride;
};

class LocomotorTemplate : public Overridable
{
public:
	char m_pad008[0x70 - 0x08];
	int m_appearance;
	char m_pad074[0x80 - 0x74];
	Real m_angleThreshold001BCE20;
};

template <class T> class OVERRIDE
{
public:
	const T *operator->() const { return getFinalOverride(); }
	operator const T *() const { return getFinalOverride(); }
	const T *getFinalOverride() const
	{
		if (!m_overridable)
			return 0;
		const Overridable *overridable = m_overridable;
		return (const T *)overridable->getFinalOverride();
	}

private:
	T *m_overridable;
};

class Rva001B9D00Mover
{
public:
	void rva001B9D00(Object *obj, const Coord3D *goalPos, Real onPathDistToGoal,
		Real desiredSpeed);
};

class Rva001BB530Mover
{
public:
	void rva001BB530(Object *obj, const Coord3D *goalPos, Real onPathDistToGoal,
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
	void rva001BA1C0(Object *obj, const Coord3D *goalPos);
	Bool behavior(void *object, const Coord3D *position);
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

// The retail global at 0x012F0898 is EA's `GameLogic *TheGameLogic`, defined
// once in game/GameEngine/Source/GameLogic/System/GameLogic.cpp. Referencing it
// under the canonical spelling gives the linker one symbol; the stamp field is
// read through this TU-local view of the retail layout.
class GameLogic;

extern GameLogic *TheGameLogic;

struct LocomotorGameLogicView
{
	char m_pad000[0x3c];
	unsigned m_stamp;
};

static __forceinline LocomotorGameLogicView *locomotorGameLogic()
{
	return (LocomotorGameLogicView *)TheGameLogic;
}

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
	memcpy(&saved->Row[0].X, &live->Row[0].X, sizeof(Real));
	memcpy(&saved->Row[0].Y, &live->Row[0].Y, sizeof(Real));
	memcpy(&saved->Row[0].Z, &live->Row[0].Z, sizeof(Real));
	memcpy(&saved->Row[0].W, &live->Row[0].W, sizeof(Real));
	memcpy(&saved->Row[1].X, &live->Row[1].X, sizeof(Real));
	memcpy(&saved->Row[1].Y, &live->Row[1].Y, sizeof(Real));
	memcpy(&saved->Row[1].Z, &live->Row[1].Z, sizeof(Real));
	memcpy(&saved->Row[1].W, &live->Row[1].W, sizeof(Real));
	memcpy(&saved->Row[2].X, &live->Row[2].X, sizeof(Real));
	memcpy(&saved->Row[2].Y, &live->Row[2].Y, sizeof(Real));
	memcpy(&saved->Row[2].Z, &live->Row[2].Z, sizeof(Real));
	memcpy(&saved->Row[2].W, &live->Row[2].W, sizeof(Real));

	if (locomotorGameLogic()->m_stamp <= m_stampLimit && desiredSpeed > m_maxSpeed)
		desiredSpeed = m_maxSpeed;

	Real cap = ((Rva001B7E90Receiver *)this)->effectiveMaxSpeed(obj);
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
		owner = obj->m_ai->m_path;
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
			((Rva001B9D00Mover *)this)->rva001B9D00(obj, &goalPos,
				onPathDistToGoal, desiredSpeed);
			break;
		case 6:
			((Rva001BB530Mover *)this)->rva001BB530(obj, &goalPos,
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
		tail = obj->m_ai->m_path;
	}
	else
	{
		tail = 0;
	}
	// As above, this compiler-only barrier retains the retail shared merge and
	// contributes no machine-code instruction.
	_ReadWriteBarrier();
	if (!(tail && ((Rva001B3FE0 *)tail)->test()))
		((Rva001BA1C0Handler *)this)->rva001BA1C0(obj, &goalPos);

	((Thing *)obj)->rva00132200(&m_savedTransform);
	m_moving = 0;
}

class MotionNode;


class ObjectModule
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual MotionNode *getMotion();
};

class MotionNode
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void beforeUpdate();
	virtual void afterUpdate();
};

class Rva001B4A50
{
public:
	void method(Real angle);
};

struct Rva001B59ScaleContext;

class Rva001B59FloatView
{
public:
	float getScaledFirst(const Rva001B59ScaleContext *context) const;
};

class BfmeD1054;
class BfmeC1054
{
public:
	void bfmeGo1054C(BfmeD1054 *p, int b, int c);
};





Real normalizeAngle(Real angle);
Real Cos(Real angle);
Real Sin(Real angle);

class Locomotor
{
public:
	void locoUpdate_moveTowardsAngle(Object *obj, Real goalAngle);

private:
	enum LocoFlag { MAINTAIN_POS_IS_VALID = 2 };
	void setFlag(LocoFlag f, Bool set)
	{
		if (set)
			m_flags |= (1 << f);
		else
			m_flags &= ~(1 << f);
	}

	void *m_vtable;
	OVERRIDE<LocomotorTemplate> m_template;
	char m_pad008[0x40 - 0x08];
	unsigned m_flags;
	char m_pad044[0x64 - 0x44];
	Matrix3D m_savedTransform;
};

// Locomotor::locoUpdate_moveTowardsAngle, retail 0x001BCE20 (542 B, thiscall
// ret 8): Zero Hour's body with BFME's callees; ilt_oracle CONFIRMS the name at
// the address. It lives beside 0x001BC820 because retail's schedule of the
// desiredPos copy needs that callee's body visible in the same unit: compiled
// elsewhere it keeps twelve register bytes off (goalAngle loaded before the
// position copy).
void Locomotor::locoUpdate_moveTowardsAngle(Object *obj, Real goalAngle)
{
	setFlag(MAINTAIN_POS_IS_VALID, false);

	if (obj == 0 || m_template == 0)
		return;

	Rva001BC820Blocker *blocker = obj->m_blocker;
	if (blocker != 0 && blocker->m_blocked != 0)
		return;

	m_savedTransform = *obj->getTransformMatrix();

	Real delta = normalizeAngle(goalAngle - obj->getAngle());
	Real angleThreshold = m_template->m_angleThreshold001BCE20;
	Real cosDelta = Cos(delta);
	if (Cos(angleThreshold) > cosDelta)
	{
		ObjectModule *module = obj->m_module;
		MotionNode *motion = module != 0 ? (MotionNode *)module->getMotion() : 0;
		if (motion != 0)
		{
			motion->beforeUpdate();
			((Rva001B4A50 *)this)->method(goalAngle);
			obj->setTransformMatrix(&m_savedTransform);
			motion->afterUpdate();
		}
	}

	Real minSpeed = ((const Rva001B59FloatView *)this)->getScaledFirst((const Rva001B59ScaleContext *)obj);
	if (minSpeed > 0)
	{
		Coord3D desiredPos = *obj->getPosition();
		desiredPos.x += Cos(goalAngle) * minSpeed * 2;
		desiredPos.y += Sin(goalAngle) * minSpeed * 2;
		const Real onPathDistToGoal = 99999.0f;
		Bool blocked;
		((Rva001BC820Locomotor *)this)->locoUpdate_moveTowardsPosition(obj, desiredPos, onPathDistToGoal, minSpeed, &blocked);
		return;
	}
	else
	{
		Coord3D desiredPos = *obj->getPosition();
		desiredPos.x += Cos(goalAngle) * 1000.0f;
		desiredPos.y += Sin(goalAngle) * 1000.0f;
		((BfmeC1054 *)this)->bfmeGo1054C((BfmeD1054 *)obj, (int)&desiredPos, 0);
		((Rva001BA1C0Handler *)this)->behavior(obj, obj->getPosition());
	}
}
