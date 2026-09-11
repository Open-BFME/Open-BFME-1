// ?update@DockUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.93 date=2026-09-10
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// DockUpdate::update, reconstructed from the retail body at 0x002CCEC0.
// The body uses the BFME object layout, where model-condition flags live on
// Object at +0x110.

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_NEWALLOC 1
#define _STLP_USE_STATIC_LIB 1
#include <vector>

typedef unsigned int UnsignedInt;
typedef int Int;
typedef int ObjectID;
typedef bool Bool;

enum UpdateSleepTime
{
	UPDATE_SLEEP_INVALID = 0,
	UPDATE_SLEEP_NONE = 1
};

enum KindOfType
{
	KINDOF_DOZER = 0x0e,
	KINDOF_HARVESTER = 0x10,
	KINDOF_SUPPLY_SOURCE = 0x51,
	MODELCONDITION_DOCKING_BEGINNING = 0x51,
	MODELCONDITION_MOVING = 0x3c
};

template <int Bits>
class BitFlags
{
public:
	void set(Int bit)
	{
		m_bits[static_cast<UnsignedInt>(bit) >> 5] |=
			1U << (static_cast<UnsignedInt>(bit) & 0x1f);
	}

	UnsignedInt m_bits[Bits / 32];
};

typedef BitFlags<320> ModelConditionFlags;

class Overridable
{
public:
	virtual ~Overridable();

	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	Bool isKindOf(KindOfType kind) const
	{
		return (m_kindOf[static_cast<UnsignedInt>(kind) >> 5] &
			(1U << (static_cast<UnsignedInt>(kind) & 0x1f))) != 0;
	}

	unsigned char m_pad08[0xc0];
	UnsignedInt m_kindOf[3];
};

class Thing
{
public:
	const ThingTemplate *getTemplate() const;
	const ThingTemplate *getTemplatePointer() const
	{
		return m_template;
	}
	Bool isKindOf(KindOfType kind) const;

	ThingTemplate *m_template;
	UnsignedInt m_unused;
};

class ObjectVtable
{
public:
	virtual ~ObjectVtable();
};

class ObjectView : public ObjectVtable, public Thing
{
};

class Object
{
public:
	void *m_vtable;
	ThingTemplate *m_template;

	const ModelConditionFlags &getModelConditionFlags() const
	{
		return m_modelConditionFlags;
	}

	unsigned char m_pad08[0x108];
	ModelConditionFlags m_modelConditionFlags;
};

class Rva00170C70BitSet
{
public:
	UnsignedInt m_words[10];
};

struct Rva00367E30Logic
{
public:
};

extern Rva00367E30Logic *TheBfmeGameLogic;

class DockUpdate
{
public:
	virtual UpdateSleepTime update();

	unsigned char m_pad04[0x4c];
	_STL::vector<ObjectID> m_approachPositionOwners;
	_STL::vector<bool> m_approachPositionReached;
	ObjectID m_activeDocker;
	Bool m_dockerInside;
	Bool m_dockCrippled;

	ObjectView *getObject() const
	{
		return *reinterpret_cast<ObjectView *const *>(
			reinterpret_cast<const char *>(this) - 8);
	}
};

extern void j_0000156e();
extern void j_000022bb();
extern void j_0000b95b();
extern void j_0001f253();
extern void j_00026f62();
extern void j_0003251f();
extern void j_0003d424();

typedef const Overridable *(Overridable::*GetFinalOverride)() const;
typedef Bool (BitFlags<320>::*AnyIntersectionWith)(
	const BitFlags<320> &) const;
typedef BitFlags<320> *(BitFlags<320>::*ConstructFlags)();
typedef void (Object::*ClearModelConditionFlags)(const ModelConditionFlags &);
typedef Object *(Rva00367E30Logic::*FindObjectByID)(ObjectID);
typedef Bool (Thing::*IsKindOf)(KindOfType) const;
typedef Rva00170C70BitSet *(Rva00170C70BitSet::*ConstructBitSet)(
	void *, UnsignedInt);

union GetFinalOverrideCall
{
	void (*freeFunction)();
	GetFinalOverride memberFunction;
};

union AnyIntersectionWithCall
{
	void (*freeFunction)();
	AnyIntersectionWith memberFunction;
};

union ConstructFlagsCall
{
	void (*freeFunction)();
	ConstructFlags memberFunction;
};

union ClearModelConditionFlagsCall
{
	void (*freeFunction)();
	ClearModelConditionFlags memberFunction;
};

union FindObjectByIDCall
{
	void (*freeFunction)();
	FindObjectByID memberFunction;
};

union IsKindOfCall
{
	void (*freeFunction)();
	IsKindOf memberFunction;
};

union ConstructBitSetCall
{
	void (*freeFunction)();
	ConstructBitSet memberFunction;
};

inline const ThingTemplate *Thing::getTemplate() const
{
	const ThingTemplate *thingTemplate = m_template;
	if (thingTemplate == 0)
		return 0;
	if (thingTemplate->m_nextOverride != 0)
	{
		GetFinalOverrideCall getFinalOverride;
		getFinalOverride.freeFunction = j_000022bb;
		thingTemplate = (const ThingTemplate *)
			(thingTemplate->m_nextOverride->*
				getFinalOverride.memberFunction)();
	}
	return thingTemplate;
}

inline Bool Thing::isKindOf(KindOfType kind) const
{
	return getTemplate()->isKindOf(kind);
}

static __forceinline Bool isSupplySource(ObjectView *object)
{
	return object->isKindOf(KINDOF_SUPPLY_SOURCE);
}

static __forceinline Bool hasDockingBeginning(Object *docker)
{
	ModelConditionFlags test;
	ConstructFlagsCall constructFlags;
	constructFlags.freeFunction = j_0000156e;
	(test.*constructFlags.memberFunction)();
	test.m_bits[2] |= 0x20000;
	AnyIntersectionWithCall anyIntersectionWith;
	anyIntersectionWith.freeFunction = j_00026f62;
	return (docker->getModelConditionFlags().*
		anyIntersectionWith.memberFunction)(test);
}

UpdateSleepTime DockUpdate::update()
{
	register ObjectID activeDocker = m_activeDocker;
	if (activeDocker == 0 && !m_dockCrippled)
	{
		for (Int positionIndex = 0;
			positionIndex < m_approachPositionReached.size();
			++positionIndex)
		{
			if (m_approachPositionReached[positionIndex])
			{
				m_activeDocker = m_approachPositionOwners[positionIndex];
				return UPDATE_SLEEP_NONE;
			}
		}
	}
	else
	{
		volatile unsigned char *thing =
			(volatile unsigned char *)*reinterpret_cast<ObjectView *const *>(
				reinterpret_cast<const char *>(this) - 8);
		thing += 4;
		const ThingTemplate *thingTemplate =
			*(const ThingTemplate * volatile *)thing;
		if ((*(const UnsignedInt *)((const char *)thingTemplate + 0xd0) &
			0x200000) == 0)
			return UPDATE_SLEEP_NONE;

		FindObjectByIDCall findObjectByID;
		findObjectByID.freeFunction = j_0001f253;
		Object *docker = (TheBfmeGameLogic->*findObjectByID.memberFunction)(
			activeDocker);
		IsKindOfCall isKindOf;
		isKindOf.freeFunction = j_0003251f;
		if (docker != 0 &&
			((Thing *)docker->*isKindOf.memberFunction)(KINDOF_DOZER) &&
			((Thing *)docker->*isKindOf.memberFunction)(KINDOF_HARVESTER))
		{
			if (hasDockingBeginning(docker))
			{
				Rva00170C70BitSet clearMask;
				ConstructBitSetCall constructBitSet;
				constructBitSet.freeFunction = j_0003d424;
				const ModelConditionFlags &clearFlags =
					*(const ModelConditionFlags *)(const void *)
					(clearMask.*constructBitSet.memberFunction)(
						0, MODELCONDITION_MOVING);
				ClearModelConditionFlagsCall clearModelConditionFlags;
				clearModelConditionFlags.freeFunction = j_0000b95b;
				(docker->*clearModelConditionFlags.memberFunction)(clearFlags);
			}
		}
	}

	return UPDATE_SLEEP_NONE;
}
