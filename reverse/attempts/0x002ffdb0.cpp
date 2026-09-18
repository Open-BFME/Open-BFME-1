// ?doUpgradeNearestWall@ScriptActions@@IAEXPAVScriptActionParameter@@0000@Z
// partial score=0.78 date=2026-09-18
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmekindof /Ireference/shims/stringinline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// UPGRADE_NEAREST_WALL action 489 at retail RVA 0x002FFDB0.
// ScriptEngine::init names the five parameters, and executeAction passes five
// ScriptActionParameter pointers through the thunk at ILT 0x00037961.

#include "StringInline.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

template <unsigned int NUMBITS>
class BitFlags
{
public:
	enum BogusInitType { kInit = 0 };
	BitFlags(BogusInitType, Int bit);

private:
	unsigned char m_bits[NUMBITS / 8];
};

typedef BitFlags<192> Rva002FFDB0KindOfMask;
extern const Rva002FFDB0KindOfMask KINDOFMASK_NONE;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object;
class Player;
class Module;
class ThingTemplate;
class UpgradeTemplate;

class ScriptActionParameter
{
public:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
};

class ObjectTypes
{
public:
	virtual ~ObjectTypes() {}
	AsciiString getNthInList(Int index) const;

	Int getListSize() const
	{
		const char *begin = *(const char * const *)((const char *)this + 8);
		const char *end = *(const char * const *)((const char *)this + 12);
		return (Int)((end - begin) / sizeof(AsciiString));
	}
};

class ScriptEngine
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual ObjectTypes *getObjectTypes(const AsciiString &name) = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual Object *resolveUnit(ScriptActionParameter *parameter) = 0;

	void assignUnitReference(const AsciiString &name, Object *object);
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class CastleBehavior
{
};

extern void j_0002ae23(void);
extern void j_00026deb(void);
extern void j_0003add7(void);

class Object
{
public:
	virtual void slot00() = 0;
	Module *findModule(NameKeyType key) const;
	Bool affectedByUpgrade(const UpgradeTemplate *upgrade) const;
	Bool hasUpgrade(const UpgradeTemplate *upgrade) const;
	void giveUpgrade(const UpgradeTemplate *upgrade);

	void *m_vptr;
	ThingTemplate *m_template;
	unsigned char m_beforePosition[0x30];
	Coord3D m_position;
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *j_0002f95a(const AsciiString &name) const;
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

class Overridable
{
public:
	Overridable *m_nextOverride;
	const Overridable *getFinalOverride() const;
};

class ThingTemplate : public Overridable
{
public:
	Bool isEquivalentTo(const ThingTemplate *other) const;
};

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *) = 0;
	virtual Int getPlayerMask();
	PartitionFilter *link(PartitionFilter *next);

	PartitionFilter *m_next;
};

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	__declspec(noinline) PartitionFilterAcceptByKindOf(
		const BitFlags<192> &mustBeSet, const BitFlags<192> &mustBeClear)
		: m_mustBeSet(mustBeSet), m_mustBeClear(mustBeClear) {}
	virtual ~PartitionFilterAcceptByKindOf() {}
	virtual Bool allow(Object *);

	BitFlags<192> m_mustBeSet;
	BitFlags<192> m_mustBeClear;
};

class Rva0025ED50RootFilter : public PartitionFilter
{
public:
	Rva0025ED50RootFilter() {}
	virtual ~Rva0025ED50RootFilter() {}
	virtual Bool allow(Object *);
};

struct Rva0025ED50Entry
{
	Object *object;
	UnsignedInt word04;
};

struct Rva0025ED50ResultData
{
	Rva0025ED50Entry *begin;
	Rva0025ED50Entry *end;
	Rva0025ED50Entry *capacity;
	Rva0025ED50Entry *current;
	Int references;
};

struct Rva0025ED50WideResult
{
	Rva0025ED50ResultData *value;

	Rva0025ED50WideResult();
	Rva0025ED50WideResult(const Rva0025ED50WideResult &);
	__forceinline ~Rva0025ED50WideResult()
	{
		if (--value->references == 0)
			delete value;
	}

	Object *next(Object *&object)
	{
		if (value->current == value->end)
			return 0;
		object = (value->current++)->object;
		return object;
	}
};

enum IterOrderType
{
	ITER_FASTEST = 0
};

class PartitionManager
{
public:
	Rva0025ED50WideResult iterate(const Coord3D *, Real,
		IterOrderType, PartitionFilter *, Bool);
};

extern ScriptEngine *TheScriptEngine;
extern NameKeyGenerator *TheNameKeyGenerator;
extern UpgradeCenter *TheUpgradeCenter;
extern ThingFactory *TheThingFactory;
extern PartitionManager *ThePartitionManager;

extern void j_000022bb(void);

extern void j_000077b6(void);
extern void j_0000ba37(void);
extern void j_0001a97e(void);
extern void j_00028560(void);
extern void j_0002f95a(void);
extern void j_0003e80b(void);

typedef const ThingTemplate *(ThingFactory::*Rva002FFDB0FindTemplateCall)(
	const AsciiString &);
typedef Bool (Object::*Rva002FFDB0UpgradeTestCall)(
	const UpgradeTemplate *) const;
typedef void (Object::*Rva002FFDB0GiveUpgradeCall)(const UpgradeTemplate *);
typedef const Overridable *(Overridable::*Rva002FFDB0FinalOverrideCall)() const;
typedef Bool (ThingTemplate::*Rva002FFDB0EquivalentCall)(
	const ThingTemplate *) const;

static __forceinline const ThingTemplate *rva002FFDB0FindTemplate(
	ThingFactory *factory, const AsciiString &name)
{
	union { void (*raw)(void); Rva002FFDB0FindTemplateCall member; } call;
	call.raw = j_00028560;
	return (factory->*call.member)(name);
}

static __forceinline Bool rva002FFDB0AffectedByUpgrade(
	Object *object, const UpgradeTemplate *upgrade)
{
	union { void (*raw)(void); Rva002FFDB0UpgradeTestCall member; } call;
	call.raw = j_000077b6;
	return (object->*call.member)(upgrade);
}

static __forceinline Bool rva002FFDB0HasUpgrade(
	Object *object, const UpgradeTemplate *upgrade)
{
	union { void (*raw)(void); Rva002FFDB0UpgradeTestCall member; } call;
	call.raw = j_0000ba37;
	return (object->*call.member)(upgrade);
}

static __forceinline void rva002FFDB0GiveUpgrade(
	Object *object, const UpgradeTemplate *upgrade)
{
	union { void (*raw)(void); Rva002FFDB0GiveUpgradeCall member; } call;
	call.raw = j_0001a97e;
	(object->*call.member)(upgrade);
}

static __forceinline const Overridable *rva002FFDB0FinalOverride(
	const Overridable *overridable)
{
	union { void (*raw)(void); Rva002FFDB0FinalOverrideCall member; } call;
	call.raw = j_000022bb;
	return (overridable->*call.member)();
}

static __forceinline Bool rva002FFDB0Equivalent(
	const ThingTemplate *left, const ThingTemplate *right)
{
	union { void (*raw)(void); Rva002FFDB0EquivalentCall member; } call;
	call.raw = j_0003e80b;
	return (left->*call.member)(right);
}

typedef NameKeyType (NameKeyGenerator::*Rva002FFDB0NameToKeyCall)(const char *);
typedef Module *(Object::*Rva002FFDB0FindModuleCall)(NameKeyType) const;

static __forceinline NameKeyType rva002FFDB0NameToKey(
	NameKeyGenerator *generator, const char *name)
{
	union { void (*raw)(void); Rva002FFDB0NameToKeyCall member; } call;
	call.raw = j_0003add7;
	return (generator->*call.member)(name);
}

static __forceinline Module *rva002FFDB0FindModule(
	const Object *object, NameKeyType key)
{
	union { void (*raw)(void); Rva002FFDB0FindModuleCall member; } call;
	call.raw = j_0002ae23;
	return (object->*call.member)(key);
}

class ScriptActions
{
protected:
	void doUpgradeNearestWall(ScriptActionParameter *, ScriptActionParameter *,
		ScriptActionParameter *, ScriptActionParameter *, ScriptActionParameter *);
};

// ?doUpgradeNearestWall@ScriptActions@@IAEXPAVScriptActionParameter@@0000@Z
void ScriptActions::doUpgradeNearestWall(
	ScriptActionParameter *baseParameter,
	ScriptActionParameter *upgradeParameter,
	ScriptActionParameter *objectTypeParameter,
	ScriptActionParameter *objectTypeListParameter,
	ScriptActionParameter *referenceParameter)
{
	Object *zeroObject = 0;
	Object *baseObject = TheScriptEngine->resolveUnit(baseParameter);
	if (baseObject == zeroObject)
		return;

	static volatile NameKeyType castleBehaviorKey =
		rva002FFDB0NameToKey(TheNameKeyGenerator, "CastleBehavior");
	CastleBehavior *castle = (CastleBehavior *)rva002FFDB0FindModule(
		baseObject,
		castleBehaviorKey);
	if (castle == (CastleBehavior *)zeroObject)
		return;

	typedef Object *(CastleBehavior::*FindObjectCall)(const AsciiString &);
	union
	{
		void (*raw)(void);
		FindObjectCall member;
	} findObject;
	findObject.raw = j_00026deb;
	Object *anchor = (castle->*findObject.member)(
		objectTypeParameter->m_string);
	if (anchor == zeroObject)
		return;

	const UpgradeTemplate *upgrade = TheUpgradeCenter->j_0002f95a(
		upgradeParameter->m_string);
	if (upgrade == (const UpgradeTemplate *)zeroObject)
		return;

	ObjectTypes *objectTypes = TheScriptEngine->getObjectTypes(
		objectTypeListParameter->m_string);
	const ThingTemplate *requestedType =
		(const ThingTemplate *)zeroObject;
	if (objectTypes == (ObjectTypes *)zeroObject)
	{
		requestedType = rva002FFDB0FindTemplate(TheThingFactory,
			objectTypeListParameter->m_string);
		if (requestedType == (const ThingTemplate *)zeroObject)
			return;
	}

	BitFlags<192> kindMask(BitFlags<192>::kInit, 7);
	Rva0025ED50WideResult iterator = ThePartitionManager->iterate(
		&anchor->m_position, 1000.0f, ITER_FASTEST,
		PartitionFilterAcceptByKindOf(kindMask, KINDOFMASK_NONE).link(
			Rva0025ED50RootFilter().link((PartitionFilter *)zeroObject)), true);

	Object *candidate;
	while (iterator.next(candidate))
	{
		if (candidate == zeroObject)
			continue;
		if (!rva002FFDB0AffectedByUpgrade(candidate, upgrade))
			continue;
		if (rva002FFDB0HasUpgrade(candidate, upgrade))
			continue;

		ThingTemplate *candidateType = candidate->m_template;
		if (candidateType != (ThingTemplate *)zeroObject &&
			candidateType->m_nextOverride != 0)
			candidateType = (ThingTemplate *)rva002FFDB0FinalOverride(
				candidateType->m_nextOverride);

		if (objectTypes != (ObjectTypes *)zeroObject)
		{
			for (Int index = 0; index < objectTypes->getListSize(); ++index)
			{
				AsciiString typeName = objectTypes->getNthInList(index);
				const ThingTemplate *type = rva002FFDB0FindTemplate(
					TheThingFactory, typeName);
				if (type != (const ThingTemplate *)zeroObject &&
					candidateType != (ThingTemplate *)zeroObject &&
					rva002FFDB0Equivalent(candidateType, type))
				{
					rva002FFDB0GiveUpgrade(candidate, upgrade);
					TheScriptEngine->assignUnitReference(
						referenceParameter->m_string, candidate);
					return;
				}
			}
		}
		else if (candidateType != (ThingTemplate *)zeroObject &&
			rva002FFDB0Equivalent(candidateType, requestedType))
		{
			rva002FFDB0GiveUpgrade(candidate, upgrade);
			TheScriptEngine->assignUnitReference(
				referenceParameter->m_string, candidate);
			return;
		}
	}
}
