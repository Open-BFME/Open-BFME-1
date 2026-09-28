// ?isAttackViewBlockedByObstacle@Pathfinder@@QAE_NPBVObject@@ABUCoord3D@@0@Z
// partial score=0.94 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x003EA570 (ILT 0x000441C0): the BFME three-argument
// Pathfinder::isAttackViewBlockedByObstacle(source, goalPos, target) that
// Weapon::isGoalPosWithinAttackRange calls.  It scans the cells between the
// source and the goal for the target's ID, then gives walls, wall upgrades and
// deployed siege towers their own reach tests.  KindOf bit numbers come from
// the retail KindOf name table at 0x012AA068.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

extern "C" double fabs(double);
#pragma intrinsic(fabs)

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum KindOfType
{
	KINDOF_STRUCTURE = 7,
	KINDOF_WALK_ON_TOP_OF_WALL = 59,
	KINDOF_SIEGE_TOWER = 92,
	KINDOF_WALL_UPGRADE = 149
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;

	void set(const Coord3D *p)
	{
		x = p->x;
		y = p->y;
		z = p->z;
	}

	void sub(const Coord3D *p)
	{
		x -= p->x;
		y -= p->y;
		z -= p->z;
	}

	Real lengthSqr() const
	{
		return x * x + y * y + z * z;
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();

	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

private:
	Overridable *m_nextOverride;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Override.h
template <class T>
class OVERRIDE
{
public:
	const T *operator*() const
	{
		if (!m_overridable)
			return 0;
		return (T *)m_overridable->getFinalOverride();
	}

	operator const T *() const
	{
		return operator*();
	}

private:
	const T *m_overridable;
};

class ThingTemplate : public Overridable
{
public:
	Bool isKindOf(KindOfType kind) const
	{
		return (m_kindof[(UnsignedInt)kind >> 5] & (1 << ((UnsignedInt)kind & 31))) != 0;
	}

private:
	unsigned char m_unreconstructed_08[0xC8 - 0x08];
	UnsignedInt m_kindof[6];
};

class Module;

class Thing
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_cachedPos; }

protected:
	virtual ~Thing();

	OVERRIDE<ThingTemplate> m_template;
	char m_unreconstructed_008[0x38 - 0x08];
	Coord3D m_cachedPos;
};

class Object : public Thing
{
public:
	UnsignedInt getID() const { return m_id; }
	Module *findModule(NameKeyType key) const;

	// Retail 0x001C2380 (ILT 0x0001D31D); its semantic name is not evidenced.
	Real rva001C2380(const Coord3D *pos, const Object *other, const Coord3D *goalPos) const;

	char m_unreconstructed_044[0x74 - 0x44];
	UnsignedInt m_id;
	char m_unreconstructed_078[0xbc - 0x78];
	Real m_bfmeBC;
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

// The deployed-siege helper object the pinned 0x0002FC7A lookup returns; the
// pin keeps its historical MemoryPool spelling.
class MemoryPool
{
public:
	// Retail 0x001F8E20 (ILT 0x00034A0E).
	void rva001F8E20(Coord3D *out);
};

MemoryPool *SiegeDeploySpecialPower_getPool(Object *object);

class Rva00266340
{
public:
	bool is() const;
};

class Rva001F8DC0
{
public:
	float get() const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	Int bfmeCheckAttackViewHelper(Object *object, Coord3D *pos, void *ids);
	Int bfmeCheckAttackViewAltHelper(Object *object, Coord3D *pos, void *ids);
	// Retail 0x003E4DA0 (ILT 0x00037196).
	Bool rva003E4DA0(const Object *source, const Coord3D *goalPos);

	Bool isAttackViewBlockedByObstacle(const Object *source, const Coord3D &goalPos,
		const Object *target);
};

Bool Pathfinder::isAttackViewBlockedByObstacle(const Object *source, const Coord3D &goalPos,
	const Object *target)
{
	UnsignedInt ids[16];
	Int count = bfmeCheckAttackViewHelper(const_cast<Object *>(source),
		const_cast<Coord3D *>(&goalPos), ids);
	Int i;
	for (i = 0; i < count; ++i)
	{
		if (ids[i] == target->getID())
		{
			count = bfmeCheckAttackViewAltHelper(const_cast<Object *>(source),
				const_cast<Coord3D *>(&goalPos), ids);
			for (i = 0; i < count; ++i)
			{
				if (ids[i] == target->getID())
					return false;
			}
			return true;
		}
	}

	Coord3D delta;
	delta.set(source->getPosition());
	delta.sub(&goalPos);
	if (delta.lengthSqr() < 1.0f && !target->getTemplate()->isKindOf(KINDOF_STRUCTURE))
	{
		count = bfmeCheckAttackViewAltHelper(const_cast<Object *>(target),
			const_cast<Coord3D *>(target->getPosition()), ids);
		for (i = 0; i < count; ++i)
		{
			if (ids[i] == source->getID())
				return true;
		}
	}

	if (target->getTemplate()->isKindOf(KINDOF_WALK_ON_TOP_OF_WALL))
	{
		Real range = source->m_bfmeBC;
		if (target->getTemplate()->isKindOf(KINDOF_WALL_UPGRADE))
			range = 0.0f;
		range += 20.0f;
		Real metric = target->rva001C2380(target->getPosition(), source, &goalPos);
		if (metric < range * range)
		{
			if (target->getTemplate()->isKindOf(KINDOF_WALL_UPGRADE))
				return true;
			if (rva003E4DA0(source, &goalPos))
				return true;
		}
	}

	if (target->getTemplate()->isKindOf(KINDOF_SIEGE_TOWER))
	{
		MemoryPool *tower = SiegeDeploySpecialPower_getPool(const_cast<Object *>(target));
		static NameKeyType key = TheNameKeyGenerator->nameToKey("SiegeDeploySpecialPower");
		Module *module = target->findModule(key);
		if (tower && module && ((const Rva00266340 *)module)->is())
		{
			Coord3D offset;
			tower->rva001F8E20(&offset);
			offset.sub(&goalPos);
			if ((Real)fabs(offset.z) < 20.0f)
			{
				Real range = source->m_bfmeBC;
				Real reach = ((const Rva001F8DC0 *)tower)->get() + range;
				if ((Real)fabs(offset.x) < reach && (Real)fabs(offset.y) < reach)
					return true;
			}
		}
	}

	return false;
}
