// ?bfmeCanAffect@Weapon@@QBE_NPBVObject@@0@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfmekindof /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE

#include "PreRTS.h"
#include "Common/GameType.h"
#include "Common/KindOf.h"

enum WeaponStatus
{
	RVA001E6CE0_READY_TO_FIRE = 0,
	RVA001E6CE0_OUT_OF_AMMO = 1,
	RVA001E6CE0_PRE_ATTACK = 4,
	RVA001E6CE0_STATUS_5 = 5
};

enum DistanceCalculationType
{
	RVA001E6CE0_FROM_CENTER_2D = 0
};

class Object;
class Module;

class Rva001E4160List
{
public:
	Bool any(void *first, void *second);
};

extern const Real BfmeZeroRange;

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *) = 0;
	virtual int getPlayerMask();

	PartitionFilter *m_next;
};

typedef BitFlags<192> Rva001E6CE0KindOfMask;

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	__declspec(noinline) PartitionFilterAcceptByKindOf(
		const Rva001E6CE0KindOfMask &mustBeSet,
		const Rva001E6CE0KindOfMask &mustBeClear)
		: m_mustBeSet(mustBeSet), m_mustBeClear(mustBeClear) {}
	virtual ~PartitionFilterAcceptByKindOf() {}
	virtual Bool allow(Object *);

	Rva001E6CE0KindOfMask m_mustBeSet;
	Rva001E6CE0KindOfMask m_mustBeClear;
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *position, Real maxDistance,
		DistanceCalculationType distanceCalculation, PartitionFilter *filter);
};

extern PartitionManager *ThePartitionManager;

class Rva0036E560PointerSet
{
public:
	Bool containsPointer(void *value) const;
};

class Object
{
public:
	int getLayer() const;
	Module *findModule(NameKeyType key) const;

	char m_pad_00[0x38];
	Coord3D m_position;
	char m_pad_44[0x30];
	ObjectID m_id;
};

class Rva001E6CE0WeaponTemplate
{
public:
	char m_pad_00[0x4f0];
	void *m_bfme4f0;
	char m_pad_4f4[0x3c];
	Bool m_bfme530;
};

class Weapon
{
public:
	Bool bfmeCanAffect(const Object *source, const Object *victim) const;

	void *m_vptr;
	Rva001E6CE0WeaponTemplate *m_template;

private:
	WeaponStatus bfmeComputeStatus(Bool *valid) const;

};

Bool Weapon::bfmeCanAffect(const Object *source, const Object *victim) const
{
	if (m_template == 0)
		return false;

	if (bfmeComputeStatus(0) == RVA001E6CE0_OUT_OF_AMMO
		&& m_template->m_bfme4f0 != 0)
		return false;

	if (static_cast<Real>(m_template->m_bfme530) != BfmeZeroRange)
	{
		if (victim->getLayer() >= 0x10)
			return false;

		Rva001E6CE0KindOfMask mustBeSet(
			Rva001E6CE0KindOfMask::kInit, 119);
		Object *nearObject = ThePartitionManager->getClosestObject(
			&victim->m_position, 9999.0f,
			RVA001E6CE0_FROM_CENTER_2D,
			&PartitionFilterAcceptByKindOf(
				mustBeSet,
				*reinterpret_cast<const Rva001E6CE0KindOfMask *>(
					&KINDOFMASK_NONE)));

		if (nearObject != 0)
		{
			static NameKeyType castleBehaviorKey =
				TheNameKeyGenerator->nameToKey("CastleBehavior");
			Module *module = nearObject->findModule(castleBehaviorKey);
			if (module != 0)
			{
				void *pointer = reinterpret_cast<void *>(victim->m_id);
				if (reinterpret_cast<Rva0036E560PointerSet *>(module)->containsPointer(
						pointer)
					&& *reinterpret_cast<const Bool *>(
						reinterpret_cast<const char *>(module) + 0xac))
					return false;
			}
		}
	}

	return reinterpret_cast<Rva001E4160List *>(m_template)->any(
		(void *)victim, (void *)this);
}
