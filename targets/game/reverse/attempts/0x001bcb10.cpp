// ?locoUpdate_maintainCurrentPosition@Locomotor@@QAE_NPAVObject@@@Z
// partial score=0.43 date=2026-09-10
// cl: /O2 /GR- /DNDEBUG /DWIN32 /MD /EHsc-
// Retail 0x001BCB10 is the BFME position-maintenance dispatcher.  Its
// appearance branches and post-move handler are separate retail bodies; this
// TU keeps their verified declarations local to the BFME layout.

#include <string.h>

#pragma intrinsic(memcpy)
#pragma comment(linker, "/alternatename:?behavior@Rva001BA1C0Handler@@QAE_NPAVObject@@PBUCoord3D@@@Z=?j_0000febb@@YAXXZ")
#pragma comment(linker, "/alternatename:?notifyModelConditionChanged@BfmeObjectModelCondition@@QAEXXZ=?j_0002191d@@YAXXZ")

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
	void *m_vtable;
	int m_pad004;
	Matrix3D m_transform;
	Coord3D m_position;
	char m_pad044[0x114 - 0x44];
	unsigned m_conditionA;
	char m_pad118[0x11c - 0x118];
	unsigned m_conditionB;
	unsigned m_conditionC;
	char m_pad124[0x208 - 0x124];
	void *m_physics;
};

class BfmeObjectModelCondition
{
public:
	void notifyModelConditionChanged();
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
	Matrix3D m_savedTransform;
	Bool m_wasMaintaining;
};

Bool Locomotor::locoUpdate_maintainCurrentPosition(Object *obj)
{
	register unsigned char requiresConstantCalling = 0;

	if (obj == 0)
		return requiresConstantCalling;

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
			((BfmeObjectModelCondition *)obj)->notifyModelConditionChanged();
		}
		b = obj->m_conditionB;
		if (b & 0x40000000)
		{
			b &= ~0x40000000u;
			obj->m_conditionB = b;
			((BfmeObjectModelCondition *)obj)->notifyModelConditionChanged();
		}
		if (obj->m_conditionC & 2)
		{
			unsigned c = obj->m_conditionC;
			c &= ~2u;
			obj->m_conditionC = c;
			((BfmeObjectModelCondition *)obj)->notifyModelConditionChanged();
		}
		if (obj->m_conditionC & 4)
		{
			unsigned c = obj->m_conditionC;
			c &= ~4u;
			obj->m_conditionC = c;
			((BfmeObjectModelCondition *)obj)->notifyModelConditionChanged();
		}
		b = obj->m_conditionB;
		if (b & 0x80000000)
		{
			b &= ~0x80000000u;
			obj->m_conditionB = b;
			((BfmeObjectModelCondition *)obj)->notifyModelConditionChanged();
		}
		if (obj->m_conditionC & 1)
		{
			unsigned c = obj->m_conditionC;
			c &= ~1u;
			obj->m_conditionC = c;
			((BfmeObjectModelCondition *)obj)->notifyModelConditionChanged();
		}
		b = obj->m_conditionB;
		if (b & 0x08000000)
		{
			b &= ~0x08000000u;
			obj->m_conditionB = b;
			((BfmeObjectModelCondition *)obj)->notifyModelConditionChanged();
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
					((BfmeObjectModelCondition *)obj)->notifyModelConditionChanged();
				}
			}
			requiresConstantCalling = true;
			break;
	}

	if (((Rva001BA1C0Handler *)this)->behavior(obj, &m_maintainPos))
		requiresConstantCalling = true;

	((Thing *)obj)->rva00132200(saved);
	return requiresConstantCalling;
}
