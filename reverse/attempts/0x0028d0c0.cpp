// ?rva0028D0C0@@YAHXZ
// partial score=0.23 date=2026-09-20
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfmekindof /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "PreRTS.h"
#include "Common/KindOf.h"

class Object;
typedef BitFlags<192> Rva0028D0C0KindOfMask;

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *) = 0;
	virtual Int getPlayerMask();
	PartitionFilter *m_next;
};

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	PartitionFilterAcceptByKindOf(const Rva0028D0C0KindOfMask &,
		const Rva0028D0C0KindOfMask &);
	virtual ~PartitionFilterAcceptByKindOf() {}
	virtual Bool allow(Object *);
	Rva0028D0C0KindOfMask m_mustBeSet;
	Rva0028D0C0KindOfMask m_mustBeClear;
};

class BehaviorModuleInterface
{
public:
	virtual void *slot00() = 0; virtual void *slot01() = 0;
	virtual void *slot02() = 0; virtual void *slot03() = 0;
	virtual void *slot04() = 0; virtual void *slot05() = 0;
	virtual void *slot06() = 0; virtual void *slot07() = 0;
	virtual void *slot08() = 0; virtual void *slot09() = 0;
	virtual void *slot10() = 0; virtual void *slot11() = 0;
	virtual void *slot12() = 0; virtual void *slot13() = 0;
	virtual void *slot14() = 0; virtual void *slot15() = 0;
	virtual void *slot16() = 0; virtual void *slot17() = 0;
	virtual void *slot18() = 0; virtual void *slot19() = 0;
	virtual void *slot20() = 0; virtual void *slot21() = 0;
	virtual void *slot22() = 0; virtual void *slot23() = 0;
	virtual void *slot24() = 0; virtual void *slot25() = 0;
	virtual void *slot26() = 0; virtual void *slot27() = 0;
	virtual void *slot28() = 0; virtual void *slot29() = 0;
	virtual void *slot30() = 0;
};

class BehaviorModulePrimary
{
	virtual void primarySlot();
	unsigned int word04;
	unsigned int word08;
};

class BehaviorModule : public BehaviorModulePrimary, public BehaviorModuleInterface
{
};

class Object
{
public:
	unsigned char prefix[0x74];
	UnsignedInt id;
	unsigned char middle[0x1f0 - 0x78];
	BehaviorModule **behaviors;
};

struct Rva0028D0C0IterEntry
{
	Object *object;
	UnsignedInt word04;
};

struct Rva0028D0C0IterData
{
	std::vector<Rva0028D0C0IterEntry> entries;
	Rva0028D0C0IterEntry *current;
	Int references;
};

struct BfmeResultA
{
	Rva0028D0C0IterData *value;
	BfmeResultA();
	BfmeResultA(const BfmeResultA &);
	~BfmeResultA()
	{
		if (--value->references == 0)
			delete value;
	}
	Object *next()
	{
		if (value->current == value->entries.end())
			return 0;
		return (value->current++)->object;
	}
};

class PartitionManager
{
public:
	BfmeResultA iterateAllAt0028D0C0(PartitionFilter *filter);
};

extern PartitionManager *ThePartitionManager;

int __cdecl rva0028D0C0()
{
	BfmeResultA iterator = ThePartitionManager->iterateAllAt0028D0C0(
		&PartitionFilterAcceptByKindOf(
			Rva0028D0C0KindOfMask(Rva0028D0C0KindOfMask::kInit, 100),
			*reinterpret_cast<const Rva0028D0C0KindOfMask *>(&KINDOFMASK_NONE)));

	for (Object *object = iterator.next(); object; object = iterator.next())
	{
		for (BehaviorModule **module = object->behaviors; *module; ++module)
		{
			if ((*module)->slot30())
				return object->id;
		}
	}
	return 0;
}
