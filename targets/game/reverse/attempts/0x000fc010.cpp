// ?d_000fc010@@YAXXZ
// partial score=0.50867 date=2026-09-26
// cl: /DNDEBUG /DWIN32 /MD /EHsc
#include "../../../../Libraries/Source/WWVegas/WWMath/coord3d.h"
#include <math.h>

typedef int Int;
typedef float Real;
class Object;
class ThingTemplate;
class TerrainLogic
{
public:
    virtual void reserved00();
    virtual void reserved01();
    virtual void reserved02();
    virtual void reserved03();
    virtual void reserved04();
    virtual void reserved05();
    virtual Real getGroundHeight(Real x, Real y, Int unused);
};
extern TerrainLogic *TheTerrainLogic;

class BuildAssistant
{
public:
    struct TileBuildInfo {
        Int tilesUsed;
        Coord3D *positions;
    };
    virtual void reserved00();
    virtual void reserved01();
    virtual void reserved02();
    virtual void reserved03();
    virtual void reserved04();
    virtual void reserved05();
    virtual void reserved06();
    virtual void reserved07();
    virtual void reserved08();
    virtual void reserved09();
    virtual Int isLocationLegalToBuild(const Coord3D *pos,
        const ThingTemplate *what, Real angle, unsigned int options,
        Object *builder, void *player);

    TileBuildInfo *buildTiledLocations(const ThingTemplate *thingBeingTiled,
        Real angle, const Coord3D *start, const Coord3D *end,
        Real tilingSize, Int maxTiles, Object *builderObject);
private:
    void *m_unmodelled04;
    Coord3D *m_buildPositions;
    Int m_buildPositionSize;
};

// ?buildTiledLocations@BuildAssistant@@UAEPAUTileBuildInfo@1@PBVThingTemplate@@MPBUCoord3D@@1MHPAVObject@@@Z
BuildAssistant::TileBuildInfo *BuildAssistant::buildTiledLocations(
    const ThingTemplate *thingBeingTiled, Real angle, const Coord3D *start,
    const Coord3D *end, Real tilingSize, Int maxTiles, Object *builderObject)
{
    if (start == 0 || end == 0)
        return 0;
    if (maxTiles > m_buildPositionSize) {
        delete [] m_buildPositions;
        m_buildPositions = new Coord3D[maxTiles];
        m_buildPositionSize = maxTiles;
    }
    Coord3D *positions = m_buildPositions;
    Coord3DBase placementVector;
    placementVector.x = end->x - start->x;
    placementVector.y = end->y - start->y;
    placementVector.z = 0.0f;
    Real placementLength = (Real)sqrt(placementVector.x * placementVector.x + placementVector.y * placementVector.y);
    Int tilesNeeded = (Int)(placementLength / tilingSize) + 1;
    if (tilesNeeded > maxTiles)
        tilesNeeded = maxTiles;
    positions[0].x = start->x;
    positions[0].y = start->y;
    positions[0].z = start->z;
    Int tilesUsed = 1;
    Coord3DBase pos;
    ((Coord3D *)&placementVector)->normalize();
    for (Int i = 1; i < tilesNeeded; ++i) {
        pos.x = placementVector.x * (tilingSize * i) + start->x;
        pos.y = placementVector.y * (tilingSize * i) + start->y;
        pos.z = TheTerrainLogic->getGroundHeight(pos.x, pos.y, 0);
        if (isLocationLegalToBuild((Coord3D *)&pos,
            thingBeingTiled, angle, 0x1f, builderObject, 0) != 0)
            break;
        positions[i].x = pos.x;
        positions[i].y = pos.y;
        positions[i].z = pos.z;
        ++tilesUsed;
    }
    static TileBuildInfo tileInfo;
    tileInfo.tilesUsed = tilesUsed;
    tileInfo.positions = positions;
    return &tileInfo;
}
