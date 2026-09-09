// ?bfmeZonePathCheck003EDF90@Pathfinder@@QAE_NPAVObject@@PBUCoord3D@@1PBVBfmeLocomotorSet@@@Z
// partial score=0.25 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x003EDF90 (631 bytes) is a BFME extension of the quick terrain
// connectivity check.  The old slowDoesPathExist row points at this body, but
// its fourth argument is not ObjectID: retail treats it as a nullable pointer
// to a movement profile and, when it is null, takes the embedded profile from
// Object::AIUpdateInterface at +0x1a8.  The existing callers all pass zero, so
// this deliberately uses an address-derived name until a non-zero caller gives
// the function a canonical source identity.

typedef int Int;
typedef unsigned char Bool;
typedef unsigned short zoneStorageType;

struct Coord3D
{
	float x, y, z;
};

struct ICoord2D
{
	Int x, y;
};

enum PathfindLayerEnum
{
	LAYER_GROUND = 1
};

class Overridable
{
public:
	const Overridable *getFinalOverride(void) const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	char m_pad0444[0x444 - 8];
	Int m_scalar0444;
	char m_pad0448[0x4cc - 0x448];
	unsigned char m_byte04cc;
};

class BfmeLocomotorSet
{
public:
	char m_pad00[0x10];
	Int m_acceptableSurfaces;
};

class AIUpdateInterface
{
public:
	BfmeLocomotorSet *getDefaultLocomotorSet(void)
	{
		return &m_defaultLocomotorSet;
	}

	char m_pad00[0x1a8];
	BfmeLocomotorSet m_defaultLocomotorSet;
};

class Rva001BF140ByteField
{
public:
	unsigned char get(void) const;

	char m_pad00[0x3a8];
	unsigned char m_value;
};

class Object
{
public:
	bool bfmeIsComputerControlled(void) const;

	char m_pad00[4];
	ThingTemplate *m_template;
	char m_pad08[0x204 - 8];
	AIUpdateInterface *m_ai;
	char m_pad208[0x3a8 - 0x208];
};

class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *object,
		const Coord3D *destination);
};

extern TerrainLogic *TheTerrainLogic;

struct PathfindMovementProfile
{
	Int acceptableSurfaces;
	bool crusher;
	bool terrainOnly;
	unsigned char padding[2];
	Int layer;
};

struct PathfindCell
{
	char m_prefix[8];
	zoneStorageType m_zone;
	char m_pad0a[2];
	unsigned int m_packed;

	Int getType(void) const { return (Int)(m_packed & 7); }
};

class PathfindZoneManager
{
public:
	zoneStorageType getEffectiveZone(const PathfindMovementProfile &profile,
		zoneStorageType zone) const;
	zoneStorageType bfmeEffectiveTerrainZone(
		const PathfindMovementProfile &profile, zoneStorageType zone) const;

private:
	char m_opaque[0x23634];
	Int m_maxZone;
	char m_equivalencies[9 * 24];
};

class Pathfinder
{
public:
	bool worldToCell(const Coord3D *position, ICoord2D *cell);
	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y);
	bool validMovementPosition(const Coord3D *position,
		PathfindLayerEnum layer, Int acceptableSurfaces, Object *object);
	bool bfmeZoneTransition(Object *object, zoneStorageType fromZone,
		zoneStorageType toZone, const BfmeLocomotorSet *locomotorSet);

	bool bfmeZonePathCheck003EDF90(Object *object, const Coord3D *from,
		const Coord3D *to, const BfmeLocomotorSet *locomotorSet);

private:
	char m_prefix[0xc9c];
	PathfindZoneManager m_zoneManager;
};

// ?bfmeZonePathCheck003EDF90@Pathfinder@@QAE_NPAVObject@@PBUCoord3D@@1PBVBfmeLocomotorSet@@@Z
bool Pathfinder::bfmeZonePathCheck003EDF90(Object *object,
	const Coord3D *from, const Coord3D *to,
	const BfmeLocomotorSet *locomotorSet)
{
	if (((const Rva001BF140ByteField *)object)->get() == 1)
		return true;

	AIUpdateInterface *ai = object->m_ai;
	if (ai == 0 && locomotorSet == 0)
		return false;

	const BfmeLocomotorSet *selected = locomotorSet;
	if (selected == 0)
		selected = ai->getDefaultLocomotorSet();
	if ((selected->m_acceptableSurfaces & 0xf) == 0)
		return false;

	PathfindLayerEnum destinationLayer =
		TheTerrainLogic->getLayerForDestination(object, to);
	PathfindLayerEnum sourceLayer =
		TheTerrainLogic->getLayerForDestination(object, from);

	ICoord2D cell;
	worldToCell(from, &cell);
	PathfindCell *parentCell = getCell(sourceLayer, cell.x, cell.y);

	worldToCell(to, &cell);
	PathfindCell *goalCell = getCell(destinationLayer,
		cell.x, cell.y);
	if (goalCell->getType() == 2)
		return false;

	ThingTemplate *templateObject = object->m_template;
	if (templateObject != 0 && templateObject->m_nextOverride != 0)
		templateObject = (ThingTemplate *)templateObject->m_nextOverride->getFinalOverride();
	Int templateLayer = templateObject->m_scalar0444;

	templateObject = object->m_template;
	if (templateObject != 0 && templateObject->m_nextOverride != 0)
		templateObject = (ThingTemplate *)templateObject->m_nextOverride->getFinalOverride();
	unsigned char templateTerrainOnly = templateObject->m_byte04cc;

	PathfindMovementProfile profile;
	profile.acceptableSurfaces = selected->m_acceptableSurfaces;
	profile.crusher = object->bfmeIsComputerControlled();
	profile.terrainOnly = templateTerrainOnly == 0;
	profile.layer = templateLayer - 1;

	zoneStorageType parentZone =
		m_zoneManager.getEffectiveZone(profile, parentCell->m_zone);
	bool doingTerrainZone = false;
	if (parentCell->getType() == 4)
	{
		doingTerrainZone = true;
		if (parentZone == 0)
			return true;
	}
	zoneStorageType goalZone =
		m_zoneManager.getEffectiveZone(profile, goalCell->m_zone);

	if (goalCell->getType() == 4 || doingTerrainZone)
	{
		parentZone = m_zoneManager.bfmeEffectiveTerrainZone(profile,
			parentCell->m_zone);
		parentZone = m_zoneManager.getEffectiveZone(profile, parentZone);
		parentZone = m_zoneManager.bfmeEffectiveTerrainZone(profile, parentZone);
		goalZone = m_zoneManager.bfmeEffectiveTerrainZone(profile,
			goalCell->m_zone);
		goalZone = m_zoneManager.getEffectiveZone(profile, goalZone);
		goalZone = m_zoneManager.bfmeEffectiveTerrainZone(profile, goalZone);
	}

	if (!validMovementPosition(to, destinationLayer,
		selected->m_acceptableSurfaces, object))
		return false;
	if (parentZone == goalZone)
		return true;
	return bfmeZoneTransition(object, parentZone, goalZone, locomotorSet);
}
