// ?bfmeCanAttackTarget@BfmeAttackQuery@@QBE_NPBVObject@@PBUCoord3D@@0PBX@Z
// partial score=0.35 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
extern "C" int __cdecl abs( int n );
extern "C" long __cdecl _ftol2( double value );
#pragma intrinsic(abs)
//
// Retail 0x003EE2B0: BFME attack-query candidate test.  The query walks from
// a cell coordinate to an offset candidate, resolves the candidate's effective
// zone, and accepts it when the movement-zone check allows the transition.

typedef int Int;
typedef bool Bool;
typedef unsigned short zoneStorageType;

enum ObjectID
{
	INVALID_ID = 0,
	FORCE_OBJECTID_TO_LONG_SIZE = 0x7fffffff
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	Int x;
	Int y;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct PathfindMovementProfile
{
	Int acceptableSurfaces;
	Bool crusher;
	Bool terrainOnly;
	unsigned char padding[2];
	Int layer;
};

struct BfmeCellResult
{
	Int m_field00;
	Int m_field04;
	Int m_field08;
	Int m_field0c;
	Int m_field10;
};

struct BfmeCellInfo
{
	unsigned char m_pad00[0x20];
	Int m_field20;
};

class PathfindCell
{
public:
	BfmeCellInfo *m_info;
	Int m_field04;
	unsigned short m_zone;
	unsigned short m_pad0a;
	unsigned int m_packed;
};

class PathfindLayer
{
public:
	PathfindCell *getCell(Int x, Int y);

private:
	unsigned char m_unreconstructed[0x44];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindZoneManager
{
public:
	zoneStorageType getEffectiveZone(const PathfindMovementProfile &profile,
		zoneStorageType zone) const;
};

enum PathfindLayerEnum
{
	PATHFIND_LAYER_INVALID = 0,
	PATHFIND_LAYER_GROUND = 1
};

class Object;

// These are the BFME layouts touched by bfmeCanAttackTarget.  The locomotor
// set is the one object-owned copy at AIUpdateInterface+0x1a8; it is not a
// second global or a replacement for the engine's state.
class LocomotorSet
{
public:
	Int getValidSurfaces() const { return m_validSurfaces; }

private:
	unsigned char m_pad000[0x10];
	Int m_validSurfaces;
};

class AIUpdateInterface
{
public:
	const LocomotorSet &getLocomotorSet() const { return m_locomotorSet; }

private:
	unsigned char m_pad000[0x1a8];
	LocomotorSet m_locomotorSet;
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_pad008[0x444 - 0x08];
	Int m_field0444;
	unsigned char m_pad448[0x4cc - 0x448];
	unsigned char m_field04cc;
};

struct BfmeShapeE15
{
	unsigned char m_pad000[0x10];
	Coord3D m_offset;
};

class BfmeObjE15
{
public:
	BfmeShapeE15 *bfmeAtE15(Int index);
};

class Pathfinder
{
public:
	Bool worldToCell(const Coord3D *world, ICoord2D *cell);
	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y);
	Bool slowDoesPathExist(Object *object, const Coord3D *from,
		const Coord3D *to, ObjectID ignoreObject);
};

class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *object,
		const Coord3D *position);
};

extern TerrainLogic *TheTerrainLogic;

class Thing
{
protected:
	void *m_vtable;
	ThingTemplate *m_template;
};

class Object : public Thing
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	Bool bfmeIsComputerControlled() const;

	unsigned char m_pad008[0x38 - 0x08];
	Coord3D m_position;
	unsigned char m_pad044[0xbc - 0x44];
	float m_minorRadius;

private:
	unsigned char m_pad0c0[0x204 - 0xc0];
	AIUpdateInterface *m_ai;
};

class BfmeAttackQuery
{
public:
	Int fillCellAlongLine(const ICoord2D *from, const ICoord2D *to,
		Int layer, BfmeCellResult *result);
	Bool validMovement(Int layer, Int fromZone, zoneStorageType toZone,
		const void *extra);

	Bool checkCandidate(const ICoord2D *base, Int dx, Int dy, Int unused,
		Int layer, Int fromZone, BfmeCellResult *result,
		const PathfindMovementProfile *profile, const void *extra);
	Bool bfmeCanAttackTarget(const Object *source, const Coord3D *sourcePosition,
		const Object *target, const void *extra) const;

private:
	unsigned char m_pad000[0x10];
	PathfindCell **m_map;
	struct
	{
		ICoord2D lo;
		ICoord2D hi;
	} m_extent;
	unsigned char m_beforeLayers[0x85c - 0x24];
	PathfindLayer m_layers[16];
	PathfindZoneManager m_zoneManager;

	__forceinline PathfindCell *getCell(Int layer, Int x, Int y)
	{
		if (x >= m_extent.lo.x && x <= m_extent.hi.x &&
			y >= m_extent.lo.y && y <= m_extent.hi.y)
		{
			if (layer > 1 && layer <= 15)
			{
				PathfindCell *cell = m_layers[layer].getCell(x, y);
				if (cell)
					return cell;
			}
			return &m_map[x][y];
		}
		return 0;
	}
};

// Retail body 0x003D6DC0; the checkCandidate caller reaches it through ILT
// 0x00042E01.  The body returns true when the line finds a cell whose owner
// differs from result->m_field04 and records that cell in result.
Int BfmeAttackQuery::fillCellAlongLine(const ICoord2D *from,
	const ICoord2D *to, Int layer, BfmeCellResult *result)
{
	const ICoord2D *from_ptr = from;
	const ICoord2D *to_ptr = to;
	Int to_x = to_ptr->x;
	Int x = from_ptr->x;
	Int delta_x = abs(to_x - x);
	Int y = from_ptr->y;
	Int to_y = to_ptr->y;
	Int delta_y = abs(to_y - y);

	Int xinc2, yinc1, xinc1, numpixels, numadd, den;
	Int yinc2, num;
	if (delta_x >= delta_y)
	{
		numpixels = delta_x + 1;
		num = 2 * delta_y - delta_x;
		numadd = delta_y << 1;
		den = 2 * (delta_y - delta_x);
		xinc2 = 1;
		yinc2 = 0;
		yinc1 = 1;
		xinc1 = 1;
	}
	else
	{
		numpixels = delta_y + 1;
		num = 2 * delta_x - delta_y;
		numadd = delta_x << 1;
		den = 2 * (delta_x - delta_y);
		yinc2 = 1;
		xinc2 = 0;
		yinc1 = 1;
		xinc1 = 1;
	}

	if (from->x > to_x)
	{
		xinc2 = -xinc2;
		xinc1 = -1;
	}
	if (from->y > to_y)
	{
		yinc2 = -yinc2;
		yinc1 = -1;
	}

	for (Int curpixel = 0; curpixel < numpixels; curpixel++)
	{
		PathfindCell *cell = getCell(layer, x, y);
		if (cell == 0)
			return false;

		BfmeCellInfo *info = cell->m_info;
		Int owner = info != 0 ? info->m_field20 : 0;
		if (owner != result->m_field04)
		{
			result->m_field08 = cell->m_zone;
			result->m_field0c = x;
			result->m_field10 = y;
			return true;
		}

		if (num < 0)
		{
			num += numadd;
			x += xinc2;
			y += yinc2;
		}
		else
		{
			num += den;
			x += xinc1;
			y += yinc1;
		}
	}

	return false;
}

Bool BfmeAttackQuery::checkCandidate(const ICoord2D *base, Int dx, Int dy,
	Int unused, Int layer, Int fromZone, BfmeCellResult *result,
	const PathfindMovementProfile *profile, const void *extra)
{
	ICoord2D candidate = *base;
	candidate.x += dx;
	candidate.y += dy;
	fillCellAlongLine(base, &candidate, layer, result);

	if (result->m_field08 != 0)
	{
		Int effectiveZone = m_zoneManager.getEffectiveZone(
			*profile, (zoneStorageType)result->m_field08);
		if (fromZone == effectiveZone ||
			validMovement(unused, fromZone, effectiveZone, extra))
			return true;
	}
	return false;
}

// Retail body 0x003EE360: BFME attack-query visibility/path test.  The first
// branch asks the ordinary pathfinder about the target cell; a type-4 cell is
// handled by the fallback candidate scan below.  The object, template,
// locomotor, terrain and Pathfinder views above are all TU-local views of
// fields/callees proven by the retail operands and the named caller at
// 0x001C77B0.
Bool BfmeAttackQuery::bfmeCanAttackTarget(const Object *source,
	const Coord3D *sourcePosition, const Object *target,
	const void *extra) const
{
	register const Object *sourceObject = source;
	register const Object *targetObject = target;
	const AIUpdateInterface *sourceAI = sourceObject->getAIUpdateInterface();
	if (sourceAI == 0)
	{
		if (extra == 0)
			return false;
	}
	else if (extra != 0)
	{
	}
	else
	{
		extra = &sourceAI->getLocomotorSet();
	}

	if ((reinterpret_cast<const LocomotorSet *>(extra)->getValidSurfaces() & 0x0f) == 0)
		return false;

	Pathfinder *pathfinder = reinterpret_cast<Pathfinder *>(
		const_cast<BfmeAttackQuery *>(this));
	Coord3D targetPosition = targetObject->m_position;
	PathfindLayerEnum targetLayer = TheTerrainLogic->getLayerForDestination(
		const_cast<Object *>(sourceObject), &targetPosition);
	PathfindLayerEnum sourceLayer = TheTerrainLogic->getLayerForDestination(
		const_cast<Object *>(sourceObject), sourcePosition);

	ICoord2D sourceCell;
	ICoord2D targetCell;
	pathfinder->worldToCell(sourcePosition, &sourceCell);
	PathfindCell *sourcePathCell = pathfinder->getCell(sourceLayer,
		sourceCell.x, sourceCell.y);
	pathfinder->worldToCell(&targetPosition, &targetCell);
	PathfindCell *targetPathCell = pathfinder->getCell(targetLayer,
		targetCell.x, targetCell.y);
	if ((targetPathCell->m_packed & 7) != 4)
	{
		BfmeObjE15 *geometry = reinterpret_cast<BfmeObjE15 *>(
			const_cast<unsigned char *>(reinterpret_cast<const unsigned char *>(target) + 0xac));
		const BfmeShapeE15 *shape = geometry->bfmeAtE15(0);
		targetPosition.x += shape->m_offset.x;
		targetPosition.y += shape->m_offset.y;
		targetPosition.z += shape->m_offset.z;
		pathfinder->worldToCell(&targetPosition, &targetCell);
		targetPathCell = pathfinder->getCell(targetLayer,
			targetCell.x, targetCell.y);
		if ((targetPathCell->m_packed & 7) != 4)
			return pathfinder->slowDoesPathExist(
				const_cast<Object *>(sourceObject), sourcePosition, &targetPosition,
				static_cast<ObjectID>(reinterpret_cast<unsigned int>(extra)));
	}

	BfmeCellInfo *cellInfo = targetPathCell->m_info;
	const LocomotorSet *fallbackLocomotors = cellInfo != 0
		? reinterpret_cast<const LocomotorSet *>(cellInfo->m_field20) : 0;
	extra = fallbackLocomotors;
	pathfinder->worldToCell(&targetPosition, &targetCell);

	const ThingTemplate *sourceTemplate = sourceObject->getTemplate();
	Int sourceLayerProfile;
	if (sourceTemplate != 0 && sourceTemplate->m_nextOverride != 0)
		sourceTemplate = reinterpret_cast<const ThingTemplate *>(
			sourceTemplate->m_nextOverride->getFinalOverride());
	if (sourceTemplate != 0)
		sourceLayerProfile = sourceTemplate->m_field0444;

	unsigned char sourceAttackFlag = 0;
	const ThingTemplate *sourceTemplateAgain = sourceObject->getTemplate();
	if (sourceTemplateAgain != 0 && sourceTemplateAgain->m_nextOverride != 0)
		sourceTemplateAgain = reinterpret_cast<const ThingTemplate *>(
			sourceTemplateAgain->m_nextOverride->getFinalOverride());
	if (sourceTemplateAgain != 0)
		sourceAttackFlag = sourceTemplateAgain->m_field04cc;

	PathfindMovementProfile profile;
	profile.acceptableSurfaces = reinterpret_cast<const LocomotorSet *>(extra)->getValidSurfaces();
	profile.crusher = sourceAttackFlag == 0;
	profile.terrainOnly = sourceObject->bfmeIsComputerControlled();
	profile.layer = sourceLayerProfile - 1;

	zoneStorageType sourceZone = sourcePathCell->m_zone;
	zoneStorageType effectiveZone = m_zoneManager.getEffectiveZone(
		profile, sourceZone);
	Int radius = 2 - (Int)_ftol2((double)(targetObject->m_minorRadius *
		*reinterpret_cast<const float *>(0x010c2e78)));

	BfmeCellResult result;
	result.m_field00 = reinterpret_cast<Int>(this);
	result.m_field04 = reinterpret_cast<Int>(extra);
	result.m_field08 = 0;
	result.m_field0c = -1;
	result.m_field10 = -1;
	BfmeAttackQuery *query = const_cast<BfmeAttackQuery *>(this);
	if (query->checkCandidate(&targetCell, radius, 0, reinterpret_cast<Int>(source),
		reinterpret_cast<Int>(source), effectiveZone, &result, &profile,
		extra))
		return true;
	if (query->checkCandidate(&targetCell, -radius, 0, reinterpret_cast<Int>(source),
		reinterpret_cast<Int>(source), effectiveZone, &result, &profile,
		extra))
		return true;
	return query->checkCandidate(&targetCell, radius, 0, reinterpret_cast<Int>(source),
		reinterpret_cast<Int>(source), effectiveZone, &result, &profile,
		extra);
}
