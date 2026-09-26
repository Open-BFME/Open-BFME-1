// ?locoUpdate_moveTowardsAngle@Locomotor@@QAEXPAVObject@@M@Z
// partial score=0.22 date=2026-09-10
// cl: /O2 /GR- /DNDEBUG /MD /EHsc-
// BFME Locomotor angle-update view.  The retail object layout is the one
// recovered by the matched 0x001BC820 movement dispatcher; this TU keeps the
// angle method's BFME fields local instead of importing the ZH Locomotor ABI.

typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct Matrix3D
{
	UnsignedInt cell[12];
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
	Real m_minSpeed;
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
	char m_pad038[0x44 - 0x38];
	Real m_angle;
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
	void bfmeGo1054C(BfmeD1054 *object, int a, int b);
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
	UnsignedInt flags = m_flags;
	if (object == 0)
		return;
	m_flags = flags & ~4u;
	if (m_template == 0)
		return;
	Locomotor *self = this;
	Object *obj = object;

	if (self->m_template->m_nextOverride != 0 &&
		self->m_template->m_nextOverride->getFinalOverride() == 0)
		return;

	PhysicsBehavior *physics = obj->m_physics;
	if (physics == 0 || physics->m_stunned != 0)
		return;

	Matrix3D *saved = &self->m_savedTransform;
	const Matrix3D *live = &obj->m_transform;
	saved->cell[0] = live->cell[0];
	saved->cell[1] = live->cell[1];
	saved->cell[2] = live->cell[2];
	saved->cell[3] = live->cell[3];
	saved->cell[4] = live->cell[4];
	saved->cell[5] = live->cell[5];
	saved->cell[6] = live->cell[6];
	saved->cell[7] = live->cell[7];
	saved->cell[8] = live->cell[8];
	saved->cell[9] = live->cell[9];
	saved->cell[10] = live->cell[10];
	saved->cell[11] = live->cell[11];

	Real delta = normalizeAngle(goalAngle - obj->m_angle);
	ObjectModule *module = obj->m_module;
	MotionNode *motion = module != 0 ? (MotionNode *)module->getMotion() : 0;
	if (motion != 0)
	{
		motion->beforeUpdate();
		((Rva001B4A50Locomotor *)self)->apply(goalAngle);
		obj->setTransformMatrix(saved);
		Real scale = ((Rva00170120Locomotor *)self)->check((Rva00170120Object *)obj);
		motion->afterUpdate();
		if (scale > 0.0f)
		{
			Coord3D desired = *(Coord3D *)&obj->m_transform;
			desired.x += Cos(goalAngle) * self->m_template->m_minSpeed * 2.0f;
			desired.y += Sin(goalAngle) * self->m_template->m_minSpeed * 2.0f;
			Bool blocked = 0;
			self->locoUpdate_moveTowardsPosition(obj, desired, 99999.0f,
				self->m_template->m_minSpeed, &blocked);
			return;
		}
	}

	Coord3D desired = *(Coord3D *)&obj->m_transform;
	desired.x += Cos(goalAngle) * 1000.0f;
	desired.y += Sin(goalAngle) * 1000.0f;
	((BfmeC1054 *)self)->bfmeGo1054C((BfmeD1054 *)obj, 0, 0);
	((Rva001BA1C0Handler *)self)->behavior(obj, &desired);
	(void)delta;
}
