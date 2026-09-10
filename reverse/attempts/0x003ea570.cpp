// ?isAttackViewBlockedByObstacle@Pathfinder@@QAE_NPBVObject@@ABUCoord3D@@0@Z
// partial score=0.2 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
//
// BFME's goal-position attack-view overload at retail RVA 0x003EA570.
//
// Weapon::isGoalPosWithinAttackRange reaches this body through ILT 0x000441C0
// with TheAI->pathfinder() in ecx and (source, goalPos, target) as the three
// stack arguments.  The body first asks both attack-view cell walkers for the
// ids along source -> goalPos, then applies the target-template and
// SiegeDeploySpecialPower exceptions before doing the final horizontal check.
// The object and template offsets below are the BFME layouts established by
// the neighboring attack-view and weapon range bodies.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;
typedef int NameKeyType;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Module;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	void *m_vtable;
	Overridable *m_nextOverride;
	unsigned char m_unreconstructed_008[0xC8 - 0x08];
	signed char m_flagsC8;
	unsigned char m_unreconstructed_0C9[3];
	UnsignedInt m_flagsCC;
	UnsignedInt m_flagsD0;
	unsigned char m_unreconstructed_0D4[4];
	UnsignedInt m_flagsD8;

	const Overridable *getFinalOverride(void) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void *m_vtable;
	Overridable *m_template;
	unsigned char m_unreconstructed_008[0x38 - 0x08];
	Coord3D m_position;
	unsigned char m_unreconstructed_044[0x74 - 0x44];
	UnsignedInt m_id;
	unsigned char m_unreconstructed_078[0xBC - 0x78];
	Real m_bfmeBC;

	Module *findModule(NameKeyType key) const;
};

class Pathfinder
{
public:
	Int bfmeCheckAttackView(Object *object, Coord3D *goalPos, void *cellIds);
	Int bfmeCheckAttackViewAlt(Object *object, Coord3D *goalPos, void *cellIds);
	Int bfmeCheckAttackViewHelper(Object *object, Coord3D *goalPos, void *cellIds);
	Int bfmeCheckAttackViewAltHelper(Object *object, Coord3D *goalPos, void *cellIds);

	Bool isAttackViewBlockedByObstacle(const Object *source,
		const Coord3D &goalPos, const Object *target);
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class SiegeDeploySpecialPower
{
};

class MemoryPool
{
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern float g_Va010977E0;

// Exact retail ILTs, used through typed member-pointer views where the owning
// C++ class name has not yet been recovered.  The views preserve the observed
// ecx receiver and stack argument order without inventing a fallback symbol.
extern void j_0001d31d();
extern void j_00034a0e();
extern void j_00037196();
extern void j_00048112();
extern void j_00049cb5();
extern MemoryPool *SiegeDeploySpecialPower_getPool(Object *object);

static __forceinline Bool isSiegeAttached(SiegeDeploySpecialPower *module)
{
	typedef Bool (SiegeDeploySpecialPower::*Function)() const;
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_00048112;
	return (module->*fn.member)();
}

static __forceinline Real targetAttackMetric(const Object *target,
	const Coord3D *targetPos, const Object *source, const Coord3D *goalPos)
{
	typedef Real (Object::*Function)(const Coord3D *, const Object *,
		const Coord3D *) const;
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0001d31d;
	return (const_cast<Object *>(target)->*fn.member)(targetPos, source, goalPos);
}

static __forceinline Bool pathHasTarget(Pathfinder *pathfinder,
	Int (Pathfinder::*scan)(Object *, Coord3D *, void *),
	const Object *source, const Coord3D *goalPos, const Object *target)
{
	UnsignedInt cellIds[16];
	Int count = (pathfinder->*scan)(const_cast<Object *>(source),
		const_cast<Coord3D *>(goalPos), cellIds);
	for (Int i = 0; i < count; ++i)
	{
		if (cellIds[i] == target->m_id)
			return true;
	}
	return false;
}

// ?isAttackViewBlockedByObstacle@Pathfinder@@QAE_NPBVObject@@ABUCoord3D@@0@Z
Bool Pathfinder::isAttackViewBlockedByObstacle(const Object *source,
	const Coord3D &goalPos, const Object *target)
{
	Coord3D *goal = const_cast<Coord3D *>(&goalPos);
	if (!pathHasTarget(this, &Pathfinder::bfmeCheckAttackViewHelper,
			source, goal, target))
	{
		Real dx = source->m_position.x - goal->x;
		Real dy = source->m_position.y - goal->y;
		Real dz = source->m_position.z - goal->z;
		Real distanceSquared = dx * dx + dy * dy + dz * dz;
		if (distanceSquared < 1.0f)
			goto checkTemplate;
	}

	if (pathHasTarget(this, &Pathfinder::bfmeCheckAttackViewAltHelper,
		source, goal, target))
		return false;
	return true;

checkTemplate:
	if (target->m_template)
	{
		Overridable *template_ = target->m_template;
		if (template_->m_nextOverride)
		{
			const Overridable *finalOverride =
				template_->m_nextOverride->getFinalOverride();
			if (finalOverride->m_flagsC8 < 0)
				return false;
		}
	}

	if (target->m_template)
	{
		Overridable *template_ = target->m_template;
		if (template_->m_nextOverride)
		{
			const Overridable *finalOverride =
				template_->m_nextOverride->getFinalOverride();
			if ((finalOverride->m_flagsCC & 0x08000000) == 0)
				goto finalViewCheck;
		}
	}

	{
		Real limit = source->m_bfmeBC;
		if (target->m_template)
		{
			Overridable *template_ = target->m_template;
			if (template_->m_nextOverride)
			{
				const Overridable *finalOverride =
					template_->m_nextOverride->getFinalOverride();
				if (finalOverride->m_flagsD8 & 0x00200000)
					limit = 0.0f;
			}
		}

		Real metric = targetAttackMetric(target, &target->m_position,
			source, goal);
		if (metric * metric > (limit + g_Va010977E0) *
			(limit + g_Va010977E0))
			goto finalViewCheck;
	}

finalViewCheck:
	{
		typedef Bool (Pathfinder::*Function)(const Object *, const Coord3D *);
		union { void (*raw)(void); Function member; } fn;
		fn.raw = j_00037196;
		if ((this->*fn.member)(source, goal))
			return true;
	}

	if (target->m_template)
	{
		Overridable *template_ = target->m_template;
		if (template_->m_nextOverride)
		{
			const Overridable *finalOverride =
				template_->m_nextOverride->getFinalOverride();
			if (finalOverride->m_flagsD0 & 0x10000000)
			{
				MemoryPool *pool = SiegeDeploySpecialPower_getPool(
					const_cast<Object *>(target));
				static volatile NameKeyType key =
					TheNameKeyGenerator->nameToKey("SiegeDeploySpecialPower");
				Module *module = target->findModule(key);
				if (pool && module &&
					isSiegeAttached((SiegeDeploySpecialPower *)module))
				{
					Coord3D poolPosition;
					typedef void (MemoryPool::*PositionFunction)(Coord3D *);
					union { void (*raw)(void); PositionFunction member; } positionFn;
					positionFn.raw = j_00034a0e;
					(pool->*positionFn.member)(&poolPosition);

					Real dx = poolPosition.x - goal->x;
					Real dy = poolPosition.y - goal->y;
					Real dz = poolPosition.z - goal->z;
					Real range = source->m_bfmeBC;
					typedef Real (MemoryPool::*RangeFunction)() const;
					union { void (*raw)(void); RangeFunction member; } rangeFn;
					rangeFn.raw = j_00049cb5;
					Real poolRange = (pool->*rangeFn.member)();
					if (dx < 0.0f) dx = -dx;
					if (dy < 0.0f) dy = -dy;
					if (dx <= poolRange + range && dy <= poolRange + range &&
						(dz < 0.0f ? -dz : dz) <= g_Va010977E0)
						return true;
				}
			}
		}
	}

	return false;
}
