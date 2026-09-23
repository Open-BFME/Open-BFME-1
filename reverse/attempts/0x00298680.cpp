// ?update@ModelConditionSpecialAbilityUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.29 date=2026-09-24
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "PreRTS.h"
#include "Common/GameType.h"
#include "GameLogic/ObjectIter.h"

enum UpdateSleepTime
{
	UPDATE_SLEEP_INVALID = 0,
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class Player;

class Object
{
public:
	Player *getControllingPlayer() const;
	void bfmeApplySpecialModelCondition(Int condition, const void *animation, Int frames);

	unsigned char m_unmodelled_00_to_38[0x38];
	Coord3D m_position;
};

class Rva00298680ModuleData
{
public:
	unsigned char m_00_to_258[0x258];
	Bool m_condition6;
	Bool m_condition5;
	unsigned char m_25a_to_25b[2];
	Real m_radius;
};

class PartitionFilter
{
public:
	void *m_vptr;
	PartitionFilter *m_next;
	PartitionFilter *link(PartitionFilter *next);
};

class PartitionFilterSameMapStatus : public PartitionFilter
{
public:
	explicit PartitionFilterSameMapStatus(const Object *object)
	{
		m_vptr = (void *)0x01085DD0;
		m_next = 0;
		m_object = object;
	}

	~PartitionFilterSameMapStatus()
	{
		m_vptr = (void *)0x01083B5C;
	}

private:
	const Object *m_object;
};

class PartitionFilterPlayerAffiliation : public PartitionFilter
{
public:
	PartitionFilterPlayerAffiliation(const Player *player, UnsignedInt affiliation, Bool match)
	{
		m_vptr = (void *)0x0109689C;
		m_next = 0;
		m_player = player;
		m_match = match;
		m_affiliation = affiliation;
	}

	~PartitionFilterPlayerAffiliation()
	{
		m_vptr = (void *)0x01083B5C;
	}

private:
	const Player *m_player;
	Bool m_match;
	UnsignedInt m_affiliation;
};

struct Rva00298680Entry
{
	Int m_valueBits;
	Int m_rawDistanceBits;
};

struct Rva00298680ResultData
{
	_STL::vector<Rva00298680Entry> m_entries;
	Rva00298680Entry *m_current;
	Int m_references;
};

struct Rva0025ED50WideResult
{
	Rva00298680ResultData *value;

	Rva0025ED50WideResult();
	Rva0025ED50WideResult(const Rva0025ED50WideResult &that);
	~Rva0025ED50WideResult()
	{
		if (--value->m_references == 0)
			delete value;
	}

	Object *next(Object *&object)
	{
		if (value->m_current == value->m_entries.end())
			return 0;
		object = (Object *)(value->m_current++)->m_valueBits;
		return object;
	}
};

class PartitionManager
{
public:
	Rva0025ED50WideResult iterate(const Coord3D *position, Real range,
		IterOrderType order, PartitionFilter *filter, Bool includeSelf);
};

extern PartitionManager *ThePartitionManager;

class Rva002A9850Call
{
public:
	void callAt002A9850();
};
#pragma comment(linker, "/alternatename:?callAt002A9850@Rva002A9850Call@@QAEXXZ=?j_0003fa30@@YAXXZ")

class SpecialAbilityUpdate
{
public:
	virtual UpdateSleepTime update() = 0;

protected:
	Rva00298680ModuleData *m_moduleData;
	Object *m_object;
};

class ModelConditionSpecialAbilityUpdate : public SpecialAbilityUpdate
{
public:
	virtual UpdateSleepTime update();
};

// ?update@ModelConditionSpecialAbilityUpdate@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime ModelConditionSpecialAbilityUpdate::update()
{
	UpdateSleepTime returnValue;
	reinterpret_cast<Rva002A9850Call *>(this)->callAt002A9850();

	Rva00298680ModuleData *moduleData = m_moduleData;
	if (moduleData != 0 && (moduleData->m_condition6 || moduleData->m_condition5))
	{
		Object *object = m_object;
		Rva0025ED50WideResult iterator = ThePartitionManager->iterate(
			&object->m_position, moduleData->m_radius, ITER_FASTEST,
			PartitionFilterPlayerAffiliation(object->getControllingPlayer(), 4, true).link(
				&PartitionFilterSameMapStatus(object)), false);

		Object *candidate;
		while (iterator.next(candidate))
		{
			if (moduleData->m_condition6)
				candidate->bfmeApplySpecialModelCondition(6, moduleData, 1);
			if (moduleData->m_condition5)
				candidate->bfmeApplySpecialModelCondition(5, moduleData, 1);
		}
	}
	return returnValue;
}
