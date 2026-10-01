// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath
// AISkirmishPlayer vtable 0x01096FB0 slot 13 points through ILT 0x0000F399
// to this body. Slot 14 dispatches repairStructure when a broken bridge is found.
#include "coord3d.h"

inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
inline Coord3D::Coord3D(const Coord3D &source) { *(Coord3DBase *)this = *(const Coord3DBase *)&source; }
inline Coord3DBase &Coord3DBase::operator=(const Coord3DBase &source)
{
    x = source.x;
    y = source.y;
    z = source.z;
    return *this;
}

class Object
{
public:
    const Coord3D *getPosition() const { return (const Coord3D *)((const char *)this + 0x38); }
    class AIUpdateInterface *getAI() const { return *(AIUpdateInterface **)((char *)this + 0x204); }
};

class AIUpdateInterface
{
public:
    const void *getLocomotorSet() const { return (const char *)this + 0x1a8; }
};

class Waypoint
{
public:
    const Coord3D *getLocation() const { return (const Coord3D *)((const char *)this + 0xc); }
    Waypoint *getNext() const { return *(Waypoint **)((const char *)this + 0x1c); }
};

typedef int Int;
typedef unsigned short zoneStorageType;

enum PathfindLayerEnum
{
    LAYER_INVALID = -1,
    LAYER_GROUND = 1,
    LAYER_FIRST_BRIDGE = 16
};

// TU-local view: this body declares only the one callee reached through the
// global, which is defined once by game/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp.
class TerrainLogic
{
public:
    PathfindLayerEnum getLayerForDestination(Object *, const Coord3D *);
};
extern TerrainLogic *TheTerrainLogic;

class LocomotorSet
{
public:
    int getValidSurfaces() const { return *(const int *)((const char *)this + 0x10); }
};

struct PathfindMovementProfile
{
    int acceptableSurfaces;
    bool crusher;
    bool terrainOnly;
    unsigned char padding[2];
    int layer;

    explicit PathfindMovementProfile(int surfaces) :
        acceptableSurfaces(surfaces), crusher(false), terrainOnly(false), layer(LAYER_INVALID) {}
};

class PathfindZoneManager
{
public:
    zoneStorageType getEffectiveZone(const PathfindMovementProfile &, zoneStorageType) const;
    zoneStorageType bfmeEffectiveTerrainZone(const PathfindMovementProfile &, zoneStorageType) const;
};

class PathfindCell
{
public:
    zoneStorageType getZone() const { return *(const zoneStorageType *)((const char *)this + 8); }
};

class Gen_003fbaa0
{
public:
    int m();
};

class PathfindLayer
{
public:
    bool isDestroyed() const { return *(const unsigned char *)((const char *)this + 0x34) != 0; }
    bool connectsZones(PathfindZoneManager *, const LocomotorSet &, int, int);
private:
    char padding[0x44];
};

struct ICoord2D { Int x; Int y; };

class Pathfinder
{
public:
    bool clientSafeQuickDoesPathExist(Object *, const Coord3D *, const Coord3D *, int);
    __declspec(noinline) int findBrokenBridge(const void *, const Coord3D *, const Coord3D *);
    bool worldToCell(const Coord3D *, ICoord2D *);
    PathfindCell *getCell(PathfindLayerEnum, int, int);
private:
    char padding[0x85c];
    PathfindLayer m_layers[16];
    PathfindZoneManager m_zoneManager;
};

class AI
{
    char padding[0xc];
    Pathfinder *m_pathfinder;
public:
    Pathfinder *pathfinder() const { return m_pathfinder; }
};
extern AI *TheAI;

class AISkirmishPlayer
{
public:
#define SKIRMISH_SLOT(n) virtual void slot##n();
    SKIRMISH_SLOT(00) SKIRMISH_SLOT(01) SKIRMISH_SLOT(02) SKIRMISH_SLOT(03)
    SKIRMISH_SLOT(04) SKIRMISH_SLOT(05) SKIRMISH_SLOT(06) SKIRMISH_SLOT(07)
    SKIRMISH_SLOT(08) SKIRMISH_SLOT(09) SKIRMISH_SLOT(10) SKIRMISH_SLOT(11)
    SKIRMISH_SLOT(12)
#undef SKIRMISH_SLOT
    virtual bool checkBridges(Object *unit, Waypoint *way);
    virtual void repairStructure(int id);
};

bool AISkirmishPlayer::checkBridges(Object *unit, Waypoint *way)
{
    Coord3D unitPos = *unit->getPosition();
    AIUpdateInterface *ai = unit->getAI();
    if (!ai) return false;
    const void *locoSet = ai->getLocomotorSet();
    for (Waypoint *curWay = way; curWay; curWay = curWay->getNext()) {
        const Coord3D *location = curWay->getLocation();
        if (TheAI->pathfinder()->clientSafeQuickDoesPathExist(unit, &unitPos, location, 0))
            continue;
        int bridge = TheAI->pathfinder()->findBrokenBridge(locoSet, &unitPos, location);
        if (bridge) {
            repairStructure(bridge);
            return true;
        }
    }
    return false;
}

int Pathfinder::findBrokenBridge(const void *locomotorSetPointer, const Coord3D *from, const Coord3D *to)
{
    const LocomotorSet &locomotorSet = *(const LocomotorSet *)locomotorSetPointer;
    PathfindLayerEnum destinationLayer = TheTerrainLogic->getLayerForDestination(0, to);
    PathfindLayerEnum fromLayer = TheTerrainLogic->getLayerForDestination(0, from);
    ICoord2D cell;
    worldToCell(from, &cell);
    PathfindCell *parentCell = getCell(fromLayer, cell.x, cell.y);
    worldToCell(to, &cell);
    PathfindCell *goalCell = getCell(destinationLayer, cell.x, cell.y);
    PathfindMovementProfile profile(locomotorSet.getValidSurfaces());
    int zone1 = m_zoneManager.getEffectiveZone(profile, parentCell->getZone());
    int zone2 = m_zoneManager.getEffectiveZone(profile, goalCell->getZone());
    zone1 = m_zoneManager.bfmeEffectiveTerrainZone(profile, zone1);
    zone2 = m_zoneManager.bfmeEffectiveTerrainZone(profile, zone2);
    zone1 = m_zoneManager.getEffectiveZone(profile, zone1);
    zone2 = m_zoneManager.getEffectiveZone(profile, zone2);
    if (zone1 == zone2)
        return 0;
    for (int i = 0; i <= 0x0f; ++i) {
        if (m_layers[i].isDestroyed() && m_layers[i].connectsZones(&m_zoneManager, locomotorSet, zone1, zone2))
            return ((Gen_003fbaa0 *)&m_layers[i])->m();
    }
    return 0;
}
