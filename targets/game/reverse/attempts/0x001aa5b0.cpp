// ?resolve@TerrainLogicFireSpreadHelper@@QAEPAVObject@@PAVTerrainLogicFireSpreadRecord@@@Z
// partial score=0.4005 date=2026-09-26
// ?resolve@TerrainLogicFireSpreadHelper@@QAEPAVObject@@PAVTerrainLogicFireSpreadRecord@@@Z
// experiment: canonical query, status-mask and kind-mask declarations
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWLib
// stlport
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#include "PreRTS.h"
#include "Common/BitFlags.h"

class Object;
class Team;
class ThingTemplate;

typedef BitFlags<192> BfmeKindOfMaskType;
typedef BitFlags<86> BfmeObjectStatusMaskType;

class TerrainLogicFireSpreadRecord
{
	public:
	Coord3D position;
	int key;
	int field10;
	const ThingTemplate *thingTemplate;
	unsigned char field18;
	unsigned char padding19[15];
	int field28;
	unsigned char field2C;
	unsigned char field2D;
};

struct Rva001A62D0TerrainQueryResult;

class TerrainLogic
{
public:
	void queryPointImplAt001A4630(const Coord3D *, Real,
		Rva001A62D0TerrainQueryResult *, Bool, Bool);
};

class TerrainLogicP48Clear
{
public:
	void clear(Int key);
};

extern TerrainLogic *TheTerrainLogic;

struct Rva002EE330PlayerList
{
	char prefix[0x14];
	struct State
	{
		char prefix[0x230];
		Team *team;
	} *state;
};

extern Rva002EE330PlayerList *Rva002EE330ThePlayers;

class ThingFactory
{
public:
	Object *newObject(const ThingTemplate *, Team *,
		const BfmeObjectStatusMaskType &, unsigned int);
};

extern ThingFactory *TheThingFactory;

class BfmePosTP;
class BfmeHostTP
{
public:
	void bfmeSetPositionTP(const TerrainLogicFireSpreadRecord *, Bool);
};

class PartitionFilter
{
public:
	PartitionFilter() : next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *) = 0;
	virtual Int getPlayerMask();
	PartitionFilter *link(PartitionFilter *);
	PartitionFilter *next;
};

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	__declspec(noinline) PartitionFilterAcceptByKindOf(
		const BfmeKindOfMaskType &mustSet,
		const BfmeKindOfMaskType &mustClear)
		: m_mustSet(mustSet), m_mustClear(mustClear) {}
	virtual ~PartitionFilterAcceptByKindOf() {}
	virtual Bool allow(Object *);
	BfmeKindOfMaskType m_mustSet;
	BfmeKindOfMaskType m_mustClear;
};

class PartitionFilterFlammable : public PartitionFilter
{
public:
	PartitionFilterFlammable() {}
	virtual Bool allow(Object *);
};

enum DistanceCalculationType
{
	FROM_CENTER_2D = 0,
	FROM_CENTER_3D = 1
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *, Real,
		DistanceCalculationType, PartitionFilter *);
};

extern PartitionManager *ThePartitionManager;

struct Rva001A62D0TerrainQueryResult
{
	Coord3D position;
	Int field0C;
	Real bestDistanceSquared;
	Coord3D *result;
	Rva001A62D0TerrainQueryResult()
		: field0C(0), bestDistanceSquared(10000000.0f), result(0)
	{
		position.x = 0;
		position.y = 0;
		position.z = 0;
	}
};

class TerrainLogicFireSpreadHelper : public TerrainLogic
{
public:
	Object *resolve(TerrainLogicFireSpreadRecord *record);
};

Object *TerrainLogicFireSpreadHelper::resolve(TerrainLogicFireSpreadRecord *record)
{
	TerrainLogicFireSpreadRecord *found;
	{
		Rva001A62D0TerrainQueryResult query;
		queryPointImplAt001A4630((const Coord3D *)record, 10.0f,
			&query, false, false);
		found = (TerrainLogicFireSpreadRecord *)query.result;
	}
	Object *object = 0;
	if (found != 0)
	{
		if (found->thingTemplate != 0)
		{
			Rva002EE330PlayerList *players = Rva002EE330ThePlayers;
			Team *team = players->state->team;
			object = TheThingFactory->newObject(
				found->thingTemplate, team, BfmeObjectStatusMaskType(), 0);
			((BfmeHostTP *)object)->bfmeSetPositionTP(
				found, false);
		}

		Int key = found->key;
		found->position.x = 0;
		found->position.y = 0;
		found->position.z = 0;
		found->key = 0;
		found->field10 = 0;
		found->thingTemplate = 0;
		found->field28 = 1;
		found->field18 = 0;
		found->field2C = 1;
		found->field2D = 1;
		((TerrainLogicP48Clear *)TheTerrainLogic)->clear(key);
		return object;
	}

	BfmeKindOfMaskType wanted(BfmeKindOfMaskType::kInit, 117);
	PartitionFilterAcceptByKindOf kind(
		wanted,
		*reinterpret_cast<const BfmeKindOfMaskType *>(&KINDOFMASK_NONE));
	PartitionFilterFlammable flammable;
	flammable.link(&kind);
	return ThePartitionManager->getClosestObject(
		(const Coord3D *)record, 10.0f, FROM_CENTER_3D, &flammable);
}
