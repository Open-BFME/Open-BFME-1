// ?locoUpdate_maintainCurrentPosition@Locomotor@@QAE_NPAVObject@@@Z
// partial score=0.4 date=2026-09-10
// cl: /O2 /GR- /DNDEBUG /DWIN32 /MD /EHsc-
// ?locoUpdate_maintainCurrentPosition@Locomotor@@QAE_NPAVObject@@@Z
// Retail 0x001BCB10; the appearance switch reaches the matched wings branch at 0x001BC670.

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

class Object;

class Thing
{
public:
	void rva00132200(const Matrix3D *matrix);
};

class Object : public Thing
{
public:
	void notifyModelConditionChanged();

	void *m_vtable;
	int m_pad004;
	int m_transform[12];
	Coord3D m_position;
	char m_pad044[0x114 - 0x44];
	unsigned m_conditionA;
	char m_pad118[0x11c - 0x118];
	unsigned m_conditionB;
	unsigned m_conditionC;
	char m_pad124[0x208 - 0x124];
	void *m_physics;
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

class Rva001B9A90Branch
{
public:
	void maintain(Object *obj);
};

class Rva001B9AC0Branch
{
public:
	void maintain(Object *obj);
};

class Rva001B9AF0Branch
{
public:
	void maintain(Object *obj);
};

class Rva001B9B20Branch
{
public:
	void maintain(Object *obj);
};

class Rva001BA1C0Handler
{
public:
	Bool behavior(void *obj, const Coord3D *pos);
};

class Locomotor
{
public:
	Bool locoUpdate_maintainCurrentPosition(Object *obj);

protected:
	void maintainCurrentPositionWings(Object *obj);

private:
	void *m_vtable;
	LocomotorTemplate *m_template;
	Coord3D m_maintainPos;
	char m_pad014[0x3c - 0x14];
	int m_donutTimer;
	unsigned m_flags;
	char m_pad044[0x64 - 0x44];
	int m_savedTransform[12];
	Bool m_wasMaintaining;
};

Bool Locomotor::locoUpdate_maintainCurrentPosition(Object *obj)
{
	Bool requiresConstantCalling = false;

	if (obj == 0)
		return requiresConstantCalling;

	int *saved = m_savedTransform;
	saved[0] = obj->m_transform[0];
	saved[1] = obj->m_transform[1];
	saved[2] = obj->m_transform[2];
	saved[3] = obj->m_transform[3];
	saved[4] = obj->m_transform[4];
	saved[5] = obj->m_transform[5];
	saved[6] = obj->m_transform[6];
	saved[7] = obj->m_transform[7];
	saved[8] = obj->m_transform[8];
	saved[9] = obj->m_transform[9];
	saved[10] = obj->m_transform[10];
	saved[11] = obj->m_transform[11];

	unsigned flags = m_flags;
	if (((flags >> 2) & 1) == 0)
	{
		m_maintainPos = obj->m_position;
		flags |= 4;
		m_flags = flags;
	}

	if ((obj->m_conditionA & 0x10000000) == 0)
	{
		unsigned b = obj->m_conditionB;
		if (b & 0x20000000)
		{
			b &= ~0x20000000u;
			obj->m_conditionB = b;
			obj->notifyModelConditionChanged();
		}
		b = obj->m_conditionB;
		if (b & 0x40000000)
		{
			b &= ~0x40000000u;
			obj->m_conditionB = b;
			obj->notifyModelConditionChanged();
		}
		if (obj->m_conditionC & 2)
		{
			unsigned c = obj->m_conditionC;
			c &= ~2u;
			obj->m_conditionC = c;
			obj->notifyModelConditionChanged();
		}
		if (obj->m_conditionC & 4)
		{
			unsigned c = obj->m_conditionC;
			c &= ~4u;
			obj->m_conditionC = c;
			obj->notifyModelConditionChanged();
		}
		b = obj->m_conditionB;
		if (b & 0x80000000)
		{
			b &= ~0x80000000u;
			obj->m_conditionB = b;
			obj->notifyModelConditionChanged();
		}
		if (obj->m_conditionC & 1)
		{
			unsigned c = obj->m_conditionC;
			c &= ~1u;
			obj->m_conditionC = c;
			obj->notifyModelConditionChanged();
		}
		b = obj->m_conditionB;
		if (b & 0x08000000)
		{
			b &= ~0x08000000u;
			obj->m_conditionB = b;
			obj->notifyModelConditionChanged();
		}
	}

	unsigned braking = m_flags;
	braking &= ~1u;
	m_wasMaintaining = requiresConstantCalling;
	m_flags = braking;

	if (obj->m_physics == 0)
		return true;

	LocomotorTemplate *locoTemplate;
	if (m_template == 0)
		locoTemplate = 0;
	else if (m_template->m_nextOverride == 0)
		locoTemplate = m_template;
	else
		locoTemplate = (LocomotorTemplate *)m_template->m_nextOverride->getFinalOverride();

	switch (locoTemplate->m_appearance)
	{
		case 0:
		case 4:
		case 7:
			m_donutTimer = 0;
			((Rva001B9A90Branch *)this)->maintain(obj);
			break;
		case 1:
			m_donutTimer = 0;
			((Rva001B9AC0Branch *)this)->maintain(obj);
			break;
		case 6:
			m_donutTimer = 0;
			((Rva001B9AF0Branch *)this)->maintain(obj);
			break;
		case 8:
			((Rva001B9B20Branch *)this)->maintain(obj);
			break;
		case 2:
		case 5:
			m_donutTimer = 0;
			requiresConstantCalling = true;
			break;
		case 3:
			maintainCurrentPositionWings(obj);
			requiresConstantCalling = true;
			break;
		default:
			m_donutTimer = 0;
			{
				unsigned a = obj->m_conditionA;
				if (a & 0x10000000)
				{
					a &= ~0x10000000u;
					obj->m_conditionA = a;
					obj->notifyModelConditionChanged();
				}
			}
			requiresConstantCalling = true;
			break;
	}

	if (((Rva001BA1C0Handler *)this)->behavior(obj, &m_maintainPos))
		requiresConstantCalling = true;

	((Thing *)obj)->rva00132200((const Matrix3D *)saved);
	return requiresConstantCalling;
}
