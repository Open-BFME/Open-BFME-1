// ?locoUpdate_maintainCurrentPosition@Locomotor@@QAE_NPAVObject@@@Z
// Decoded BFME member offsets are accessed through an address-derived view.
// cl: /O2 /GR- /DNDEBUG /DWIN32 /MD /EHsc- /Igame/Libraries/Include /Igame/GameEngine/Source/GameLogic/Object /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib

#include "../../../Include/Common/ScalarTypes.h"


#include "Lib/Coord3D.h"

#include "matrix3d.h"

class Object;

struct ModelConditionFlags
{
	// ?test@ModelConditionFlags@@QBEIH@Z absent-from-retail
	unsigned test(int bit) const { return m_bits[bit >> 5] & (1u << (bit & 31)); }
	// ?clear@ModelConditionFlags@@QAEXH@Z absent-from-retail
	void clear(int bit) { m_bits[bit >> 5] &= ~(1u << (bit & 31)); }
	unsigned m_bits[10];
};
#define BFME_HAVE_MODELCONDITIONFLAGS
#define BFME_HAVE_COORD3D
#define THING_TU_MEMBERS void rva00132200(const Matrix3D *matrix);
// ?clearModelConditionState@Object@@QAEXH@Z absent-from-retail
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
};

// This view follows decoded offsets where the Locomotor field witness conflicts.
// Evidence: targets/game/reverse/identity_evidence/001bcb10-layout-view.md.
struct Rva001BCB10LocomotorLayout
{
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

//-------------------------------------------------------------------------------------------------
/*
	return true if we can maintain the position without being called every frame (eg, we are
	resting on the ground), false if not (eg, we are hovering or circling)
*/
// ?locoUpdate_maintainCurrentPosition@Locomotor@@QAE_NPAVObject@@@Z
Bool Locomotor::locoUpdate_maintainCurrentPosition(Object *obj)
{
	if (obj == 0)
		return false;

	Rva001BCB10LocomotorLayout *state = (Rva001BCB10LocomotorLayout *)this;
	Matrix3D *saved = &state->m_savedTransform;
	const Matrix3D *live = &obj->m_transform;
	*saved = *live;

	unsigned flags = state->m_flags;
	Bool maintainPosIsValid = ((flags >> 2) & 1) != 0;
	if (!maintainPosIsValid)
	{
		state->m_maintainPos = obj->m_cachedPos;
		flags |= 4;
		state->m_flags = flags;
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

	unsigned braking = state->m_flags;
	braking &= ~1u;
	state->m_wasMaintaining = false;
	state->m_flags = braking;

	if (obj->m_physics == 0)
		return true;

#ifdef DEBUG_OBJECT_ID_EXISTS
//	DEBUG_ASSERTLOG(obj->getID() != TheObjectIDToDebug, ("locoUpdate_maintainCurrentPosition %f %f %f, speed %f (%f)\n",m_maintainPos.x,m_maintainPos.y,m_maintainPos.z,physics->getSpeed(),physics->getForwardSpeed2D()));
#endif

	Bool requiresConstantCalling = true;	// assume the worst.
	LocomotorTemplate *locoTemplate;
	if (state->m_template == 0)
		locoTemplate = 0;
	else if (state->m_template->m_nextOverride == 0)
		locoTemplate = state->m_template;
	else
		locoTemplate = (LocomotorTemplate *)state->m_template->m_nextOverride->getFinalOverride();

	switch (locoTemplate->m_appearance)
	{
		case 0:
		case 4:
		case 7:
			state->m_donutTimer = 0;
			((Rva001B9A90Branch *)this)->maintain(obj);
			requiresConstantCalling = false;
			break;
		case 1:
			state->m_donutTimer = 0;
			((Rva001B9AC0Branch *)this)->maintain(obj);
			requiresConstantCalling = false;
			break;
		case 6:
			state->m_donutTimer = 0;
			((Rva001B9AF0Branch *)this)->maintain(obj);
			requiresConstantCalling = false;
			break;
		case 8:
			((Rva001B9B20Branch *)this)->maintain(obj);
			requiresConstantCalling = false;
			break;
		case 2:
		case 5:
			state->m_donutTimer = 0;
			requiresConstantCalling = true;
			break;
		case 3:
			maintainCurrentPositionWings(obj);
			requiresConstantCalling = true;
			break;
		default:
			state->m_donutTimer = 0;
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

	// but we do need to do this even if not moving, for hovering/Thrusting things.
	if (((Rva001BA1C0Handler *)this)->behavior(obj, &state->m_maintainPos))
		requiresConstantCalling = true;

	((Thing *)obj)->rva00132200(saved);
	return requiresConstantCalling;
}
