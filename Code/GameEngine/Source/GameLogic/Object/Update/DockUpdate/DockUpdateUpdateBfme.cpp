// ?update@DockUpdate@@UAE?AW4UpdateSleepTime@@XZ
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
	KINDOF_SUPPLY_SOURCE = 0x55,
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
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

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

// Preserve the reference Override.h conversion/dereference layers. Flattening
// this owning-template view to a raw pointer loses ten retail inline bytes.
template<class T> class OVERRIDE
{
	const T *m_overridable;
public:
	inline const T *operator*() const
	{
		if (!m_overridable)
			return 0;
		return (T *)m_overridable->getFinalOverride();
	}
	inline operator const T*() const { return operator*(); }
};

class Thing
{
public:
	const ThingTemplate *getTemplate() const;
	Bool isKindOf(KindOfType kind) const;

	OVERRIDE<ThingTemplate> m_template;
	UnsignedInt m_unused;
};

class ObjectVtable
{
public:
	virtual ~ObjectVtable();
};

class ObjectView : public ObjectVtable, public Thing
{
public:
	const Thing *getThing() const
	{
		return this;
	}

	const ThingTemplate *getThingTemplate() const
	{
		const Thing *thing = static_cast<const Thing *>(this);
		return thing->m_template;
	}
};

class Object : public Thing
{
public:
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

inline const ThingTemplate *Thing::getTemplate() const { return m_template; }

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
	Int positionIndex = m_activeDocker;
	if (positionIndex == 0 && !m_dockCrippled)
	{
		for (positionIndex = 0;
			positionIndex < m_approachPositionReached.size(); ++positionIndex)
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
		ObjectView *object = getObject();
		const ThingTemplate *thingTemplate = object->getTemplate();
		if (thingTemplate->isKindOf(KINDOF_SUPPLY_SOURCE))
		{
			FindObjectByIDCall findObjectByID;
			findObjectByID.freeFunction = j_0001f253;
			Object *docker = (TheBfmeGameLogic->*findObjectByID.memberFunction)(
				positionIndex);
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
	}

	return UPDATE_SLEEP_NONE;
}
