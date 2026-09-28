// ?locoUpdate_moveTowardsAngle@Locomotor@@QAEXPAVObject@@M@Z
// partial score=0.5625 date=2026-09-28
// ?locoUpdate_moveTowardsAngle@Locomotor@@QAEXPAVObject@@M@Z
// Reworked from bank: retail uses template+0x80 as a cosine angle threshold,
// not a movement speed. m_minSpeed was disproved by the two Cos calls.
// cl: /Igame/Libraries/Source/WWVegas/WWMath /O2 /GR- /DNDEBUG /MD /EHsc-
// BFME Locomotor angle-update view.  The retail object layout is the one
// recovered by the matched 0x001BC820 movement dispatcher; this TU keeps the
// angle method's BFME fields local instead of importing the ZH Locomotor ABI.

#include <string.h>
#pragma intrinsic(memcpy)

typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

#include "coord3d.h"
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
inline Coord3D::Coord3D(const Coord3D &that) { x=that.x; y=that.y; z=that.z; }

class Matrix3D
{
public:
	Real cell[12];
};

class Overridable
{
public:
	void *m_vtable;
	Overridable *m_nextOverride;
	Overridable *getFinalOverride();
};

class LocomotorTemplate : public Overridable
{
public:
	char m_pad008[0x80 - 0x08];
	Real m_angleThreshold001BCE20;
};

class PhysicsBehavior
{
public:
	char m_pad000[0x5c];
	unsigned char m_stunned;
};

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

class Thing
{
public:
	void *m_vtable;
	char m_pad004[0x08 - 0x04];
	Matrix3D m_transform;
	void setTransformMatrix(const Matrix3D *matrix);
};

class Object : public Thing
{
public:
	Coord3D m_cachedPos;
	const Coord3D *getPosition() const { return &m_cachedPos; }
	Real m_angle;
	Real getAngle() const { return m_angle; }
	char m_pad048[0x1fc - 0x48];
	ObjectModule *m_module;
	char m_pad200[0x208 - 0x200];
	PhysicsBehavior *m_physics;
};

class Rva001B4A50Locomotor
{
public:
	void apply(Real angle);
};

class Rva00170120Object;

class Rva00170120Locomotor
{
public:
	Real check(Rva00170120Object *object);
};

class BfmeD1054;
class BfmeC1054
{
public:
	void bfmeGo1054C(BfmeD1054 *object, const Coord3D *a, int b);
};

class Rva001BA1C0Handler
{
public:
	void behavior(Object *object, const Coord3D *position);
};

Real normalizeAngle(Real angle);
Real Cos(Real angle);
Real Sin(Real angle);

class Locomotor
{
public:
	void locoUpdate_moveTowardsAngle(Object *object, Real goalAngle);
	void locoUpdate_moveTowardsPosition(Object *object, const Coord3D &goalPos,
		Real onPathDistToGoal, Real desiredSpeed, Bool *blocked);

private:
	void *m_vtable;
	LocomotorTemplate *m_template;
	char m_pad008[0x40 - 0x08];
	UnsignedInt m_flags;
	char m_pad044[0x64 - 0x44];
	Matrix3D m_savedTransform;
};

void Locomotor::locoUpdate_moveTowardsAngle(Object *object, Real goalAngle)
{
	m_flags &= ~4u;
	if (object == 0)
		return;
	if (m_template == 0)
		return;
	Locomotor *self = this;
	Object *obj = object;

	LocomotorTemplate *resolved = self->m_template;
	if (resolved->m_nextOverride) resolved = (LocomotorTemplate*)resolved->m_nextOverride->getFinalOverride();
	if (resolved == 0)
		return;

	PhysicsBehavior *physics = obj->m_physics;
	if (physics != 0 && physics->m_stunned != 0)
		return;

	Matrix3D *saved = &self->m_savedTransform;
	const Matrix3D *live = &obj->m_transform;
	memcpy(&self->m_savedTransform.cell[0], &live->cell[0], sizeof(Real));
	memcpy(&self->m_savedTransform.cell[1], &live->cell[1], sizeof(Real));
	memcpy(&self->m_savedTransform.cell[2], &live->cell[2], sizeof(Real));
	memcpy(&self->m_savedTransform.cell[3], &live->cell[3], sizeof(Real));
	memcpy(&saved->cell[4], &live->cell[4], sizeof(Real));
	memcpy(&saved->cell[5], &live->cell[5], sizeof(Real));
	memcpy(&saved->cell[6], &live->cell[6], sizeof(Real));
	memcpy(&saved->cell[7], &live->cell[7], sizeof(Real));
	memcpy(&saved->cell[8], &live->cell[8], sizeof(Real));
	memcpy(&saved->cell[9], &live->cell[9], sizeof(Real));
	memcpy(&saved->cell[10], &live->cell[10], sizeof(Real));
	memcpy(&saved->cell[11], &live->cell[11], sizeof(Real));

	Real delta = normalizeAngle(goalAngle - obj->getAngle());
	LocomotorTemplate *next = self->m_template;
	if (next && next->m_nextOverride) next = (LocomotorTemplate*)next->m_nextOverride->getFinalOverride();
	Real angleThreshold = next->m_angleThreshold001BCE20;
	Real cosDelta = Cos(delta);
	if (Cos(angleThreshold) > cosDelta) {
	ObjectModule *module = obj->m_module;
	MotionNode *motion = module != 0 ? (MotionNode *)module->getMotion() : 0;
	if (motion != 0)
	{
		motion->beforeUpdate();
		((Rva001B4A50Locomotor *)self)->apply(goalAngle);
		obj->setTransformMatrix(saved);
		motion->afterUpdate();
	}
	}
	Real scale = ((Rva00170120Locomotor *)self)->check((Rva00170120Object *)obj);
		if (scale > 0.0f)
		{
			Coord3D desired = *obj->getPosition();
			desired.x += Cos(goalAngle) * scale * 2.0f;
			desired.y += Sin(goalAngle) * scale * 2.0f;
			Bool blocked;
			self->locoUpdate_moveTowardsPosition(obj, desired, 99999.0f,
				scale, &blocked);
			return;
		}

	{
	Coord3D desired = *obj->getPosition();
	desired.x += Cos(goalAngle) * 1000.0f;
	desired.y += Sin(goalAngle) * 1000.0f;
	((BfmeC1054 *)self)->bfmeGo1054C((BfmeD1054 *)obj, &desired, 0);
	((Rva001BA1C0Handler *)self)->behavior(obj, &obj->m_cachedPos);
	}
}
