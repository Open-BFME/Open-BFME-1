// ?bfmeFinish1282@BfmeA1282@@QAEXPAVBfmeQ1282@@PBUCoord3D@@MM@Z
// partial score=0.2118 date=2026-09-28
// cl: /O2 /GR- /DNDEBUG /DWIN32 /MD /EHsc-
// stlport
// Retail 0x001B8D30, 1676 bytes, thiscall RET 0x10: the BFME locomotor
// movement finisher that the matched helper 0x001BC560
// (Locomotor_rva001BC560.cpp) calls as bfmeFinish1282 after its setup pair,
// with the object, goal position, on-path distance and desired speed. It
// ramps the locomotor's +0x3C speed toward a braking-limited goal speed
// (LocomotorTemplate m_minSpeed +0x24, m_acceleration +0x40, m_braking +0x4C),
// steers along the AI path (Path::computePointOnPath, as the matched
// Locomotor_rva001B7200.cpp calls it) or straight at the goal, writes the
// result into the transform's translation column (+0x70/+0x80/+0x90) and then
// picks the object's movement model-condition bits 27, 31 and 32. The method
// keeps the established pin name its matched caller uses.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <bitset>
#include <math.h>

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	Coord3D() {}
	Coord3D(const Coord3D &other) : x(other.x), y(other.y), z(other.z) {}
	void normalize();
};

template<int NUMBITS>
class BfmeBitFlags
{
public:
	Bool test(Int idx) const { return m_bits.test(idx); }
	void set(Int idx) { m_bits.set(idx); }
	void clear(Int idx) { m_bits.reset(idx); }

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BfmeBitFlags<288> BfmeModelConditionFlags;

// Movement model-condition bits this body drives; their names are unproven.
enum BfmeModelConditionFlagType
{
	BFME_MODELCONDITION_BIT27 = 27,
	BFME_MODELCONDITION_BIT31 = 31,
	BFME_MODELCONDITION_BIT32 = 32
};

class BfmeObjectModelCondition
{
public:
	void notifyModelConditionChanged();
};

class Object;
class Rva001B7200Locomotor;

// 36-byte out record of Path::computePointOnPath (Locomotor_rva001B7200.cpp).
struct Rva001B7200PathPoint
{
	Rva001B7200PathPoint() : m_int20(0x7fffffff) {}

	Real m_real00;
	Coord3D m_coord04;
	Real m_real10[3];
	Int m_layer;
	Int m_int20;
};

class Path
{
public:
	void computePointOnPath(Object *object, Rva001B7200Locomotor *locomotor,
		Rva001B7200PathPoint *out, Bool flag);

	void addUse() { ++m_useCount; }
	void releaseUse() { if (m_useCount) --m_useCount; }

	Int m_useCount;
};

class AIUpdateInterface
{
public:
	Path *getPath() { return m_path; }

	char m_pad000[0x140];
	Path *m_path;
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_cachedPos; }
	AIUpdateInterface *getAIUpdateInterface() { return m_ai; }

	Bool testModelConditionState(BfmeModelConditionFlagType bit) const
	{
		return m_modelConditionFlags.test(bit);
	}

	void setModelConditionState(BfmeModelConditionFlagType bit)
	{
		if (!m_modelConditionFlags.test(bit))
		{
			m_modelConditionFlags.set(bit);
			((BfmeObjectModelCondition *)this)->notifyModelConditionChanged();
		}
	}

	void clearModelConditionState(BfmeModelConditionFlagType bit)
	{
		if (m_modelConditionFlags.test(bit))
		{
			m_modelConditionFlags.clear(bit);
			((BfmeObjectModelCondition *)this)->notifyModelConditionChanged();
		}
	}

	const Coord3D *getSteerGoal178() const
	{
		return m_hasGoal186 ? &m_goal178 : getPosition();
	}

	void setSteerGoal178(const Coord3D &goal)
	{
		m_goal178 = goal;
		m_hasGoal186 = true;
	}

	char m_pad000[0x38];
	Coord3D m_cachedPos;
	char m_pad044[0x11c - 0x44];
	BfmeModelConditionFlags m_modelConditionFlags;
	char m_pad140[0x178 - 0x140];
	Coord3D m_goal178;
	char m_pad184[2];
	Bool m_hasGoal186;
	char m_pad187[0x204 - 0x187];
	AIUpdateInterface *m_ai;
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	unsigned char m_pad000[4];
	const Overridable *m_nextOverride;
};

class LocomotorTemplate : public Overridable
{
public:
	unsigned char m_pad008[0x24 - 0x08];
	Real m_minSpeed;
	unsigned char m_pad028[0x40 - 0x28];
	UnsignedInt m_acceleration;
	unsigned char m_pad044[0x4c - 0x44];
	UnsignedInt m_braking;
	unsigned char m_pad050[0x78 - 0x50];
	Real m_real78;
	Real m_real7C;
};

class BfmeSub1CC_EC3
{
public:
	Real effectiveMaxSpeed(void *objectArgument);
	Real queryDivMin40(void *objectArgument);
	Real queryDivMin4C(void *objectArgument);
};

class BfmeQ1282
{
};

class BfmeA1282
{
public:
	void bfmeFinish1282(BfmeQ1282 *item, const Coord3D *goal,
		Real onPathDistToGoal, Real desiredSpeed);

private:
	BfmeSub1CC_EC3 *query() { return (BfmeSub1CC_EC3 *)this; }

	const LocomotorTemplate *finalTemplate() const
	{
		const LocomotorTemplate *t = m_template;
		if (t != 0 && t->m_nextOverride != 0)
			t = static_cast<const LocomotorTemplate *>(
				t->m_nextOverride->getFinalOverride());
		return t;
	}

	enum LocoFlag
	{
		FLAG_BRAKING = 0,
		FLAG_4 = 4
	};

	Bool getFlag(LocoFlag flag) const { return (m_flags >> flag) & 1; }

	void setFlag(LocoFlag flag, Bool value)
	{
		if (value)
			m_flags |= (1 << flag);
		else
			m_flags &= ~(1 << flag);
	}

	void setTranslation(Real x, Real y, Real z)
	{
		m_transform[0][3] = x;
		m_transform[1][3] = y;
		m_transform[2][3] = z;
	}

	void *m_vtable;
	const LocomotorTemplate *m_template;
	char m_pad008[0x2c - 0x08];
	Real m_real2C;
	Real m_real30;
	char m_pad034[0x3c - 0x34];
	Real m_speed;
	UnsignedInt m_flags;
	char m_pad044[0x64 - 0x44];
	Real m_transform[3][4];
	Bool m_byte94;
};

void BfmeA1282::bfmeFinish1282(BfmeQ1282 *item, const Coord3D *goalPos,
	Real onPathDistToGoal, Real desiredSpeed)
{
	Object *obj = (Object *)item;

	Real maxSpeed = query()->effectiveMaxSpeed(obj);
	if (desiredSpeed > maxSpeed)
		desiredSpeed = maxSpeed;
	Real goalSpeed = desiredSpeed;
	Real oldSpeed = m_speed;

	Real brakeRate = query()->effectiveMaxSpeed(obj);
	brakeRate /= (Real)finalTemplate()->m_braking;
	if (brakeRate > m_real30)
		brakeRate = m_real30;

	Real minSpeed = finalTemplate()->m_minSpeed;
	Real excess = oldSpeed - minSpeed;
	Real brakeDist;
	if (excess <= 0.0f)
		brakeDist = 0.0f;
	else
		brakeDist = (excess / brakeRate + 1.0f) * (excess * 0.5f + minSpeed) * 1.05f;

	if (3.0f * brakeDist < onPathDistToGoal)
		setFlag(FLAG_BRAKING, false);

	Real slowed = m_speed - brakeRate;
	if (desiredSpeed < slowed)
	{
		goalSpeed = slowed;
		if (goalSpeed < brakeRate)
			goalSpeed = brakeRate;
	}

	if (onPathDistToGoal < brakeDist)
	{
		if (!getFlag(FLAG_4))
		{
			setFlag(FLAG_BRAKING, true);
			goalSpeed = m_speed - query()->queryDivMin4C(obj);
			if (goalSpeed < brakeRate)
				goalSpeed = brakeRate;
		}
	}

	Coord3D goal = *goalPos;
	Rva001B7200PathPoint point;
	const Coord3D *pos = obj->getPosition();

	if (goalSpeed > m_speed && !getFlag(FLAG_BRAKING))
		m_speed += query()->queryDivMin40(obj);

	if (m_speed > goalSpeed)
	{
		m_speed -= brakeRate;
		if (m_speed < goalSpeed)
			m_speed = goalSpeed;
	}

	Real speed = m_speed;
	AIUpdateInterface *ai = obj->getAIUpdateInterface();
	Path *path = ai ? ai->getPath() : 0;
	Coord3D moveTo;
	if (path)
	{
		path->addUse();
		path->computePointOnPath(obj, (Rva001B7200Locomotor *)this, &point, true);
		moveTo = point.m_coord04;
		path->computePointOnPath(obj, (Rva001B7200Locomotor *)this, &point, false);
		path->releaseUse();
		goal = point.m_coord04;
		obj->setSteerGoal178(goal);
	}
	else
	{
		moveTo = *pos;
		goal.x -= pos->x;
		goal.y -= pos->y;
		goal.z = 0.0f;
		Real dist = (Real)sqrt(goal.x * goal.x + goal.y * goal.y);
		if (speed < 2.0f)
			speed = 2.0f;
		if (speed > dist)
			speed = dist;
		if (dist > 0.001f)
		{
			goal.normalize();
			moveTo.x += goal.x * speed;
			moveTo.y += goal.y * speed;
		}
	}

	const Coord3D *steer = obj->getSteerGoal178();
	goal.x = steer->x;
	goal.y = steer->y;
	goal.z = pos->z;
	obj->setSteerGoal178(goal);
	setTranslation(moveTo.x, moveTo.y, pos->z);

	Real speedDelta = m_speed - oldSpeed;
	Real threshold = maxSpeed * finalTemplate()->m_real78;
	Real accelRate = query()->effectiveMaxSpeed(obj) / (Real)finalTemplate()->m_acceleration;
	if (accelRate > m_real2C)
		accelRate = m_real2C;

	if (speedDelta > 0.4f * accelRate && oldSpeed < threshold)
	{
		obj->clearModelConditionState(BFME_MODELCONDITION_BIT32);
		if (onPathDistToGoal < finalTemplate()->m_real7C)
		{
			obj->clearModelConditionState(BFME_MODELCONDITION_BIT31);
			obj->setModelConditionState(BFME_MODELCONDITION_BIT27);
		}
		else
		{
			obj->clearModelConditionState(BFME_MODELCONDITION_BIT27);
			obj->setModelConditionState(BFME_MODELCONDITION_BIT31);
		}
		return;
	}

	if (getFlag(FLAG_BRAKING) && m_speed < threshold)
	{
		obj->clearModelConditionState(BFME_MODELCONDITION_BIT31);
		if (m_byte94)
		{
			obj->clearModelConditionState(BFME_MODELCONDITION_BIT27);
			obj->setModelConditionState(BFME_MODELCONDITION_BIT32);
		}
		else
		{
			obj->clearModelConditionState(BFME_MODELCONDITION_BIT32);
			obj->setModelConditionState(BFME_MODELCONDITION_BIT27);
		}
		return;
	}

	obj->clearModelConditionState(BFME_MODELCONDITION_BIT31);
	obj->clearModelConditionState(BFME_MODELCONDITION_BIT32);
	if (oldSpeed > threshold)
	{
		if (onPathDistToGoal > finalTemplate()->m_real7C)
			obj->clearModelConditionState(BFME_MODELCONDITION_BIT27);
		if (!obj->testModelConditionState(BFME_MODELCONDITION_BIT27))
			m_byte94 = true;
	}
}
