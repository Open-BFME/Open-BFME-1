// ?rva003E5010@Pathfinder@@QAEXPAVObject@@PAUCoord3D@@0PAX@Z
// partial score=0.22 date=2026-09-21
// stlport
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /I.
// Retail 0x003E5010, 1262 bytes.  The owning Pathfinder method is kept
// address-derived: the four-argument thiscall and the target-position work
// are proven, but the old adjustDestination attribution was refuted.

#include "PreRTS.h"
#include "Code/GameEngine/Include/GameLogic/TerrainLogic.h"

extern "C" __declspec(dllimport) double __cdecl floor(double);
#undef REAL_TO_INT_FLOOR
#define REAL_TO_INT_FLOOR(x) (fast_float2long_round((Real)floor((double)(x))))

typedef ICoord2D ICoord2DPair;

class PathfindCell;

class BfmeOverridable
{
public:
	void *m_vtable;
	BfmeOverridable *m_override;
};

class BfmeThingTemplate
{
public:
	char m_pad000[0x444];
	Int m_offset444;
	char m_pad448[0x4cc - 0x448];
	UnsignedByte m_offset4cc;
};

class AIUpdateInterface
{
public:
	char m_pad000[0x1b8];
	UnsignedInt m_validSurfaces;
};

class Object
{
public:
	void *m_vtable;
	BfmeOverridable *m_template;
	char m_pad008[0x38 - 0x08];
	Coord3D m_position;
	char m_pad044[0x204 - 0x44];
	AIUpdateInterface *m_ai;
	char m_pad208[0x390 - 0x208];
	UnsignedByte m_adjustHistory[8];
	Int m_adjustHistoryIndex;

	Int getLayer(void) const;
	Bool bfmeIsComputerControlled(void) const;
};

class PathfindCell
{
public:
	char m_pad000[0x0c];
	UnsignedInt m_packed;
};

class Pathfinder
{
public:
	void rva003E5010(Object *, Coord3D *, Object *, void *);

	void bfmeQuery(Object *, Int &, Bool &);
	Bool bfmeStepD4F90(void *, PathfindCell *);
	void adjustCoordToCell(Int, Int, Bool, Coord3D &, PathfindLayerEnum);

private:
	char m_pad000[0x844];
	Int m_ignoreObstacleID;
};

class Rva003E5010Calls
{
};

template<class F> static __forceinline F rva003E5010Call(void (*raw)())
{
	union { void (*raw)(); F typed; } call;
	call.raw = raw;
	return call.typed;
}

extern void j_000022bb();
extern void j_00049c56();
extern void j_0000c54a();
extern void j_0001c675();
extern void j_0003a391();
extern void j_000411d2();
extern void j_00047703();

typedef BfmeOverridable *(Rva003E5010Calls::*FinalOverrideCall)();
typedef PathfindCell *(Rva003E5010Calls::*ObjectCellCall)(Object *, ICoord2DPair *);
typedef char (Rva003E5010Calls::*ScanCall)(Int, Int);
typedef PathfindLayerEnum (Rva003E5010Calls::*DestinationLayerCall)(Object *, const Coord3D *);
typedef Int (Rva003E5010Calls::*LayerCall)() const;
typedef Int (Rva003E5010Calls::*AverageCall)() const;
typedef void (Rva003E5010Calls::*AdjustCall)(Int, Int, Bool, Coord3D &, PathfindLayerEnum);

class Rva003D86E0Scanner
{
public:
	Pathfinder *m_pathfinder;
	void *m_field04;
	Int m_resultX, m_resultY;
	PathfindLayerEnum m_layer;
	Int m_field14;
	Int m_cachedCellA, m_cachedCellB;
	Int m_originX, m_originY;
};

struct Rva003E5010State
{
	UnsignedInt m_offset00;
	UnsignedByte m_offset04;
	Bool m_computerControlled;
	UnsignedByte m_offset06[2];
	Int m_offset08;
};

static __forceinline BfmeOverridable *rva003E5010Final(BfmeOverridable *next)
{
	return (((Rva003E5010Calls *)next)->*rva003E5010Call<FinalOverrideCall>(j_000022bb))();
}

static __forceinline BfmeOverridable *rva003E5010Template(BfmeOverridable *templateObject)
{
	if (templateObject && templateObject->m_override)
		return rva003E5010Final(templateObject->m_override);
	return templateObject;
}

static __forceinline PathfindCell *rva003E5010ObjectCell(Pathfinder *self,
	Object *object, ICoord2DPair *cell)
{
	return (((Rva003E5010Calls *)self)->*rva003E5010Call<ObjectCellCall>(j_00049c56))(object, cell);
}

static __forceinline char rva003E5010Scan(Rva003D86E0Scanner *scanner, Int x, Int y)
{
	return (((Rva003E5010Calls *)scanner)->*
		rva003E5010Call<ScanCall>(j_0000c54a))(x, y);
}

static __forceinline PathfindLayerEnum rva003E5010DestinationLayer(
	Object *object, const Coord3D *position)
{
	return (((Rva003E5010Calls *)TheTerrainLogic)->*
		rva003E5010Call<DestinationLayerCall>(j_0001c675))(object, position);
}

static __forceinline Int rva003E5010Layer(const Object *object)
{
	return (((const Rva003E5010Calls *)object)->*
		rva003E5010Call<LayerCall>(j_0003a391))();
}

static __forceinline Int rva003E5010Average(const Object *object)
{
	return (((const Rva003E5010Calls *)object)->*
		rva003E5010Call<AverageCall>(j_00047703))();
}

static __forceinline void rva003E5010Adjust(Pathfinder *self, Int x, Int y,
	Bool center, Coord3D &position, PathfindLayerEnum layer)
{
	(((Rva003E5010Calls *)self)->*
		rva003E5010Call<AdjustCall>(j_000411d2))(x, y, center, position, layer);
}

void Pathfinder::rva003E5010(Object *source, Coord3D *destination,
	Object *target, void *)
{
	ICoord2DPair targetCell;
	m_ignoreObstacleID = 0;
	if (!rva003E5010ObjectCell(this, target, &targetCell))
		return;

	Int radius;
	Bool center;
	bfmeQuery(source, radius, center);

	BfmeThingTemplate *firstTemplate = (BfmeThingTemplate *)
		rva003E5010Template(source->m_template);
	Int maxLayer = firstTemplate->m_offset444 - 1;
	BfmeThingTemplate *secondTemplate = (BfmeThingTemplate *)
		rva003E5010Template(source->m_template);
	AIUpdateInterface *ai = source->m_ai;
	UnsignedInt validSurfaces = ai->m_validSurfaces;
	Bool computerControlled = source->bfmeIsComputerControlled();
	Bool allowAircraftGoal = secondTemplate->m_offset4cc == 0;

	ICoord2DPair sourceCell;
	if (center)
		sourceCell.x = REAL_TO_INT_FLOOR(destination->x * *(const Real *)0x01075c70);
	else
		sourceCell.x = REAL_TO_INT_FLOOR(*(const Real *)0x0107533c +
			destination->x * *(const Real *)0x01075c70);
	if (center)
		sourceCell.y = REAL_TO_INT_FLOOR(destination->y * *(const Real *)0x01075c70);
	else
		sourceCell.y = REAL_TO_INT_FLOOR(*(const Real *)0x0107533c +
			destination->y * *(const Real *)0x01075c70);

	Int average = rva003E5010Average(source);
	Int targetLayer = rva003E5010Layer(target);
	Int sourceLayer = rva003E5010Layer(source);
	Rva003E5010State state;
	state.m_offset00 = validSurfaces;
	state.m_offset04 = allowAircraftGoal;
	state.m_computerControlled = computerControlled;
	state.m_offset08 = maxLayer;

	Rva003D86E0Scanner scanner;
	scanner.m_pathfinder = this;
	scanner.m_field04 = &state;
	scanner.m_layer = (PathfindLayerEnum)sourceLayer;
	scanner.m_field14 = targetLayer;
	scanner.m_cachedCellA = targetCell.x;
	scanner.m_cachedCellB = targetCell.y;
	scanner.m_originX = radius;
	scanner.m_originY = radius + (center != 0);
	if (average == 0 && rva003E5010Scan(&scanner, sourceCell.x, sourceCell.y))
		return;

	Int lastX = -1;
	Int lastY = -1;
	Real fraction = 0.0f;
	do
	{
		Real inverse = *(const Real *)0x01075334 - fraction;
		Real candidateX = inverse * destination->x + fraction * target->m_position.x;
		Real candidateY = inverse * destination->y + fraction * target->m_position.y;
		Int cellX;
		Int cellY;
		if (center)
			cellX = REAL_TO_INT_FLOOR(candidateX * *(const Real *)0x01075c70);
		else
			cellX = REAL_TO_INT_FLOOR(*(const Real *)0x0107533c +
				candidateX * *(const Real *)0x01075c70);
		if (center)
			cellY = REAL_TO_INT_FLOOR(candidateY * *(const Real *)0x01075c70);
		else
			cellY = REAL_TO_INT_FLOOR(*(const Real *)0x0107533c +
				candidateY * *(const Real *)0x01075c70);
		if (cellX != lastX || cellY != lastY)
		{
			lastX = cellX;
			lastY = cellY;
			if (rva003E5010Scan(&scanner, cellX, cellY))
			{
				destination->x = candidateX;
				destination->y = candidateY;
				Int sample = (Int)(fraction * *(const Real *)0x0108885c);
				source->m_adjustHistory[source->m_adjustHistoryIndex] = (UnsignedByte)sample;
				++source->m_adjustHistoryIndex;
				if (source->m_adjustHistoryIndex == 8)
					source->m_adjustHistoryIndex = 0;
				Real weight = (Real)average * *(const Real *)0x010888f4;
				Real blend = *(const Real *)0x01075334 - weight;
				Real extraX = blend * destination->x + weight * target->m_position.x;
				Real extraY = blend * destination->y + weight * target->m_position.y;
				Int extraCellX;
				Int extraCellY;
				if (center)
					extraCellX = REAL_TO_INT_FLOOR(extraX * *(const Real *)0x01075c70);
				else
					extraCellX = REAL_TO_INT_FLOOR(*(const Real *)0x0107533c +
						extraX * *(const Real *)0x01075c70);
				if (center)
					extraCellY = REAL_TO_INT_FLOOR(extraY * *(const Real *)0x01075c70);
				else
					extraCellY = REAL_TO_INT_FLOOR(*(const Real *)0x0107533c +
						extraY * *(const Real *)0x01075c70);
				scanner.m_originX = 0;
				scanner.m_originY = 1;
				if (rva003E5010Scan(&scanner, extraCellX, extraCellY))
				{
					destination->x = extraX;
					destination->y = extraY;
				}
				PathfindLayerEnum layer = (PathfindLayerEnum)
					rva003E5010DestinationLayer(source, destination);
				destination->z = TheTerrainLogic->getLayerHeight(
					destination->x, destination->y, layer, 0, true);
				return;
			}
		}
		fraction += *(const Real *)0x010EEB2C;
	}
	while (fraction <= *(const Real *)0x01075334);

	source->m_adjustHistory[source->m_adjustHistoryIndex] = 0x80;
	++source->m_adjustHistoryIndex;
	if (source->m_adjustHistoryIndex == 8)
		source->m_adjustHistoryIndex = 0;
	PathfindLayerEnum layer = (PathfindLayerEnum)rva003E5010Layer(target);
	rva003E5010Adjust(this, targetCell.x, targetCell.y, center, *destination, layer);
}
