// ?locoUpdate_maintainCurrentPosition@Locomotor@@QAE_NPAVObject@@@Z
// partial score=0.8648 date=2026-10-09
// cl: /O2 /GR- /DNDEBUG /DWIN32 /MD /EHsc- /Igame/Libraries/Include /Igame/GameEngine/Source/GameLogic/Object /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib

typedef bool Bool;
typedef float Real;

#include "Lib/Coord3D.h"

#include "matrix3d.h"

class Object;

struct ModelConditionFlags
{
    unsigned test(int bit) const { return m_bits[bit >> 5] & (1u << (bit & 31)); }
    void clear(int bit) { m_bits[bit >> 5] &= ~(1u << (bit & 31)); }
    unsigned m_bits[10];
};
#define BFME_HAVE_MODELCONDITIONFLAGS
#define BFME_HAVE_COORD3D
#define THING_TU_MEMBERS void rva00132200(const Matrix3D *matrix);
#define OBJECT_TU_MEMBERS \
    void notifyModelConditionChanged(); \
    void clearModelConditionState(int bit) { \
        if (m_modelConditionFlags.test(bit)) { m_modelConditionFlags.clear(bit); notifyModelConditionChanged(); } \
    }
#include "object.h"
#undef OBJECT_TU_MEMBERS
#undef THING_TU_MEMBERS

class BfmeObjectModelCondition
{
public:
	void notifyModelConditionChanged();
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

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
	if (obj == 0)
		return false;

	Matrix3D *saved = &m_savedTransform;
	const Matrix3D *live = &obj->m_transform;
	*saved = *live;

	unsigned flags = m_flags;
	Bool maintainPosIsValid = ((flags >> 2) & 1) != 0;
	if (!maintainPosIsValid)
	{
		m_maintainPos = obj->m_cachedPos;
		flags |= 4;
		m_flags = flags;
	}

	if (!obj->m_modelConditionFlags.test(60))
    {
        obj->clearModelConditionState(125);
        obj->clearModelConditionState(126);
        obj->clearModelConditionState(129);
        obj->clearModelConditionState(130);
        obj->clearModelConditionState(127);
        obj->clearModelConditionState(128);
        obj->clearModelConditionState(123);
    }

	unsigned braking = m_flags;
	braking &= ~1u;
	m_wasMaintaining = false;
	m_flags = braking;

	if (obj->m_physics == 0)
		return true;

	Bool requiresConstantCalling = true;
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
			requiresConstantCalling = false;
			break;
		case 1:
			m_donutTimer = 0;
			((Rva001B9AC0Branch *)this)->maintain(obj);
			requiresConstantCalling = false;
			break;
		case 6:
			m_donutTimer = 0;
			((Rva001B9AF0Branch *)this)->maintain(obj);
			requiresConstantCalling = false;
			break;
		case 8:
			((Rva001B9B20Branch *)this)->maintain(obj);
			requiresConstantCalling = false;
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
                unsigned a = obj->m_modelConditionFlags.m_bits[1];
                if (a & 0x10000000)
                {
                    a &= ~0x10000000u;
                    obj->m_modelConditionFlags.m_bits[1] = a;
                    obj->notifyModelConditionChanged();
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
