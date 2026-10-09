// ?triggerAbilityEffect@ModelConditionSpecialAbilityUpdate@@MAEXXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
enum IterOrderType { ITER_FASTEST = 0 };

class Player;

#define BFME_HAVE_COORD3D 1
#define THING_TU_MEMBERS const Coord3D *getPosition() const { return &m_cachedPos; }
#define OBJECT_TU_MEMBERS Player *getControllingPlayer() const; void bfmeApplySpecialModelCondition(Int condition, const void *animation, Int frames);
#include "../object.h"
#undef OBJECT_TU_MEMBERS
#undef THING_TU_MEMBERS

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
    PartitionFilter() : m_next(0) {}
    virtual ~PartitionFilter() {}
    virtual Bool allow(Object *) = 0;
    virtual Int getPlayerMask();
    PartitionFilter *link(PartitionFilter *next);
    PartitionFilter *m_next;
};

class PartitionFilterSameMapStatus : public PartitionFilter
{
public:
    explicit PartitionFilterSameMapStatus(const Object *object) : m_object(object) {}
    virtual ~PartitionFilterSameMapStatus() {}
    virtual Bool allow(Object *);
    const Object *m_object;
};

class PartitionFilterPlayerAffiliation : public PartitionFilter
{
public:
    PartitionFilterPlayerAffiliation(Player *player, UnsignedInt affiliation, Bool match)
        : m_player(player), m_match(match), m_affiliation(affiliation) {}
    virtual ~PartitionFilterPlayerAffiliation() {}
    virtual Bool allow(Object *);
    virtual Int getPlayerMask();
    Player *m_player;
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

class Rva0025EF90Owner
{
public:
	void callAt002A9850();
};

class SpecialAbilityUpdate
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void triggerAbilityEffect() = 0;
	Object *getObject() const { return m_object; }

protected:
	Rva00298680ModuleData *m_moduleData;
	Object *m_object;
	void *m_behaviorInterface;
	void *m_updateInterface;
	unsigned int m_updateStorage[3];
	void *m_specialPowerInterface;
};

class ModelConditionSpecialAbilityUpdate : public SpecialAbilityUpdate
{
protected:
	virtual void triggerAbilityEffect();
};

// ?triggerAbilityEffect@ModelConditionSpecialAbilityUpdate@@MAEXXZ
void ModelConditionSpecialAbilityUpdate::triggerAbilityEffect()
{
	reinterpret_cast<Rva0025EF90Owner *>(this)->callAt002A9850();

	Rva00298680ModuleData *moduleData = m_moduleData;
	if (moduleData != 0 && (moduleData->m_condition6 || moduleData->m_condition5))
	{
		Rva0025ED50WideResult iterator = ThePartitionManager->iterate(
			getObject()->getPosition(), moduleData->m_radius, ITER_FASTEST,
			PartitionFilterPlayerAffiliation(getObject()->getControllingPlayer(), 4, true).link(
				&PartitionFilterSameMapStatus(getObject())), false);

		Object *candidate;
		while (iterator.next(candidate))
		{
			if (moduleData->m_condition6)
				candidate->bfmeApplySpecialModelCondition(6, getObject(), 1);
			if (moduleData->m_condition5)
				candidate->bfmeApplySpecialModelCondition(5, getObject(), 1);
		}
	}
}
