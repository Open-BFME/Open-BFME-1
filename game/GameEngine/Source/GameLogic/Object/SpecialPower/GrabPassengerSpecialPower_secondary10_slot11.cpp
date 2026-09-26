// Retail 0x0025F2D0..0x0025F5F6 is the 806-byte slot-11 action on the
// GrabPassengerSpecialPower secondary interface at primary +0x10. The
// original method name is not independently known, so it remains address-derived.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/bfmekindof /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#include "PreRTS.h"
#include "Common/BitFlags.h"

class Object;
class SpecialPowerModuleInterface;

typedef BitFlags<192> Rva0025F2D0KindOfMask;
typedef BitFlags<86> Rva0025F2D0ObjectStatusMask;

enum DistanceCalculationType
{
	FROM_CENTER_2D = 0,
	FROM_CENTER_3D = 1,
	FROM_BOUNDINGSPHERE_2D = 2,
	FROM_BOUNDINGSPHERE_3D = 3
};

enum SpecialPowerType
{
	RVA0025F2D0_SPECIAL_POWER_TYPE_27 = 0x27
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

// Retail table 0x010B243C. Its slot-one thunk reaches the matched 16-byte
// this+8 isAnyKindOf wrapper at 0x001DCCA0, and its independently exact
// constructor at 0x00251980 copies one 24-byte mask after the base head.
class Rva0025F2D0KindOfAnyFilter : public PartitionFilter
{
public:
	Rva0025F2D0KindOfAnyFilter(const Rva0025F2D0KindOfMask &mask)
		: m_mask(mask) {}
	virtual ~Rva0025F2D0KindOfAnyFilter() {}
	virtual Bool allow(Object *);
	Rva0025F2D0KindOfMask m_mask;
};

class PartitionFilterRejectByObjectStatus : public PartitionFilter
{
public:
	PartitionFilterRejectByObjectStatus(
		const Rva0025F2D0ObjectStatusMask &mustSet,
		const Rva0025F2D0ObjectStatusMask &mustClear)
		: m_mustSet(mustSet), m_mustClear(mustClear) {}
	virtual ~PartitionFilterRejectByObjectStatus() {}
	virtual Bool allow(Object *);
	Rva0025F2D0ObjectStatusMask m_mustSet;
	Rva0025F2D0ObjectStatusMask m_mustClear;
};

class PartitionFilterRelationship : public PartitionFilter
{
public:
	PartitionFilterRelationship(Object *object, Int flags, Bool match)
		: m_object(object), m_flags(flags), m_match(match) {}
	virtual ~PartitionFilterRelationship() {}
	virtual Bool allow(Object *);
	virtual Int getPlayerMask();
	Object *m_object;
	Int m_flags;
	Bool m_match;
};

class PartitionManager
{
public:
	// The exact 33-byte wrapper at 0x009F26A0 takes these four arguments and
	// forwards them to the manager at +0x0C with a null optional argument.
	Object *getClosestObject(const Coord3D *position, Real radius,
		DistanceCalculationType distanceType, PartitionFilter *filters);
};
extern PartitionManager *ThePartitionManager;

// The 26-byte constructor at 0x001A31B0 proves this complete 24-byte result
// layout and initialization order. It remains declaration-only here so the
// compiler cannot use constructor side effects to reschedule the exact wrapper.
struct Rva001A62D0TerrainQueryResult
{
	Coord3D m_position;
	Int m_word0C;
	Real m_bestDistanceSquared;
	Coord3D *m_result;
	Rva001A62D0TerrainQueryResult();
};

class TerrainLogic
{
public:
	Coord3D *queryPointAt001A62D0(const Coord3D *position, Real radius,
		Bool firstConstraint, Bool secondConstraint);
	void queryPointImplAt001A4630(const Coord3D *position, Real radius,
		Rva001A62D0TerrainQueryResult *result, Bool firstConstraint,
		Bool secondConstraint);
};
extern TerrainLogic *TheTerrainLogic;

// This typed wrapper independently reproduces all 58 retail bytes. Its
// constructor stays opaque here, matching the original callee visibility.
__declspec(noinline) Coord3D *TerrainLogic::queryPointAt001A62D0(
	const Coord3D *position, Real radius, Bool firstConstraint,
	Bool secondConstraint)
{
	Rva001A62D0TerrainQueryResult result;
	queryPointImplAt001A4630(position, radius, &result, firstConstraint,
		secondConstraint);
	return result.m_result;
}

class SpecialPowerModuleInterface
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C(); virtual void slot20();
	virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void doSpecialPowerAtObject(Object *, UnsignedInt options);
	virtual void doSpecialPowerAtLocation(const Coord3D *, UnsignedInt options);
};

class Object
{
public:
	SpecialPowerModuleInterface *findSpecialPowerModuleInterface(
		SpecialPowerType type) const;
	unsigned char m_00_to_38[0x38];
	Coord3D m_position;
};

struct Rva0025F2D0Data
{
	unsigned char m_00_to_210[0x210];
	Real m_radius;
	Bool m_queryTerrainPoint;
};

class Rva0025F2D0SecondaryAction
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C(); virtual void slot20();
	virtual void slot24(); virtual void slot28();
	virtual void actionAt0025F2D0(UnsignedInt options);
};

void Rva0025F2D0SecondaryAction::actionAt0025F2D0(UnsignedInt options)
{
	Object *object = *reinterpret_cast<Object **>(
		reinterpret_cast<unsigned char *>(this) - 8);
	Rva0025F2D0Data *data = *reinterpret_cast<Rva0025F2D0Data **>(
		reinterpret_cast<unsigned char *>(this) - 12);
	Coord3D origin = object->m_position;
	Bool usePosition = false;
	Object *target = 0;
	Coord3D selectedPosition;

	if (options & 0x8000)
	{
		Coord3D *terrainPoint = 0;
		if (data->m_queryTerrainPoint)
			terrainPoint = TheTerrainLogic->queryPointAt001A62D0(
				&origin, data->m_radius, true, true);

		target = ThePartitionManager->getClosestObject(
			&origin, data->m_radius, FROM_CENTER_2D,
			&Rva0025F2D0KindOfAnyFilter(
				Rva0025F2D0KindOfMask(
					Rva0025F2D0KindOfMask::kInit, 96, 135)));

		if (terrainPoint)
		{
			if (target)
			{
				selectedPosition.x = terrainPoint->x;
				Real terrainX = origin.x - selectedPosition.x;
				selectedPosition.y = terrainPoint->y;
				Real terrainY = origin.y - selectedPosition.y;
				selectedPosition.z = terrainPoint->z;
				Real terrainZ = origin.z - selectedPosition.z;
				Real terrainDistance = (Real)sqrt(
					terrainX * terrainX + terrainY * terrainY +
					terrainZ * terrainZ);
				Coord3D targetDelta;
				targetDelta.x = origin.x - target->m_position.x;
				targetDelta.y = origin.y - target->m_position.y;
				targetDelta.z = origin.z - target->m_position.z;
				// Retail tests only x87 C0 after comparing target distance to
				// terrain distance; unordered therefore skips the assignment.
				if (terrainDistance <= targetDelta.length())
					usePosition = true;
			}
			else
			{
				// Retail sets the position flag without copying terrainPoint here.
				usePosition = true;
			}
		}
	}
	else if ((options & 0x2000) == 0)
	{
		target = ThePartitionManager->getClosestObject(
			&origin, data->m_radius, FROM_CENTER_2D,
			Rva0025F2D0KindOfAnyFilter(
				Rva0025F2D0KindOfMask(Rva0025F2D0KindOfMask::kInit, 8))
				.link(&PartitionFilterRejectByObjectStatus(
					Rva0025F2D0ObjectStatusMask(
						Rva0025F2D0ObjectStatusMask::kInit, 3),
					Rva0025F2D0ObjectStatusMask()))
				->link(&PartitionFilterRelationship(object, 1, false)));
	}
	else
	{
		target = ThePartitionManager->getClosestObject(
			&origin, data->m_radius, FROM_CENTER_2D,
			&Rva0025F2D0KindOfAnyFilter(
				Rva0025F2D0KindOfMask(
					Rva0025F2D0KindOfMask::kInit, 135)));
	}

	Object *ownerObject = *reinterpret_cast<Object **>(
		reinterpret_cast<unsigned char *>(this) - 8);
	SpecialPowerModuleInterface *interfacePtr =
		ownerObject->findSpecialPowerModuleInterface(
			RVA0025F2D0_SPECIAL_POWER_TYPE_27);
	if (interfacePtr)
	{
		if (usePosition)
			interfacePtr->doSpecialPowerAtLocation(&selectedPosition, 0x2000);
		else if (target)
			interfacePtr->doSpecialPowerAtObject(target, 0x2000);
	}
}
