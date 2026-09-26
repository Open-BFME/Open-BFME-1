// ?d_000fc010@@YAXXZ
// partial score=0.42 date=2026-09-26
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWMath
#include "PreRTS.h"
#undef REAL_TO_INT
#define REAL_TO_INT(x) ((Int)(x))

struct Coord3D {
public:
    Coord3D() {}
    Coord3D(const Coord3D &that) { x = that.x; y = that.y; z = that.z; }
    ~Coord3D() {}
    float length() const { return (float)sqrt((double)(x * x + y * y + z * z)); }
    void normalize();

    float x;
    float y;
    float z;
};

class ThingTemplate;
class Object;
class Player;

enum LegalBuildCode {
    LBC_OK = 0
};

class TerrainLogic {
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual Real getGroundHeight(Real x, Real y);
};

extern TerrainLogic *TheTerrainLogic;

class BuildAssistant {
public:
    struct TileBuildInfo {
        Int tilesUsed;
        Coord3D *positions;
    };

    enum LocalLegalToBuildOptions {
        TERRAIN_RESTRICTIONS = 0x00000001,
        CLEAR_PATH = 0x00000002,
        NO_OBJECT_OVERLAP = 0x00000004,
        USE_QUICK_PATHFIND = 0x00000008,
        SHROUD_REVEALED = 0x00000010
    };

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
    virtual LegalBuildCode isLocationLegalToBuild(const Coord3D *worldPos,
                                                   const ThingTemplate *build,
                                                   Real angle,
                                                   UnsignedInt options,
                                                   Object *builderObject,
                                                   Player *player);
    virtual TileBuildInfo *buildTiledLocations(const ThingTemplate *thingBeingTiled,
                                                Real angle,
                                                const Coord3D *start,
                                                const Coord3D *end,
                                                Real tilingSize,
                                                Int maxTiles,
                                                Object *builderObject);

    unsigned int baseState;
    Coord3D *m_buildPositions;
    Int m_buildPositionSize;
};

BuildAssistant::TileBuildInfo *BuildAssistant::buildTiledLocations(
    const ThingTemplate *thingBeingTiled,
    Real angle,
    const Coord3D *start,
    const Coord3D *end,
    Real tilingSize,
    Int maxTiles,
    Object *builderObject)
{
    register BuildAssistant *self = this;
    register const Coord3D *lineStart = start;
    if (lineStart == NULL || end == NULL)
        return 0;

    if (maxTiles > self->m_buildPositionSize) {
        delete [] self->m_buildPositions;
        self->m_buildPositions = NEW Coord3D[maxTiles];
        self->m_buildPositionSize = maxTiles;
    }

    Coord3D *positions = self->m_buildPositions;
    Coord3D placementVector;
    placementVector.x = end->x - lineStart->x;
    placementVector.y = end->y - lineStart->y;
    placementVector.z = 0.0f;

    Real placementLength = placementVector.length();
    Int tilesNeeded = REAL_TO_INT(placementLength / tilingSize) + 1;
    if (tilesNeeded > maxTiles)
        tilesNeeded = maxTiles;

    positions[0] = *lineStart;

    Int tilesUsed = 1;
    Coord3D pos;
    Coord3D v = placementVector;
    v.normalize();
    for (Int i = 1; i < tilesNeeded; i++) {
        pos.x = v.x * (tilingSize * i) + lineStart->x;
        pos.y = v.y * (tilingSize * i) + lineStart->y;
        pos.z = TheTerrainLogic->getGroundHeight(pos.x, pos.y);

        if (isLocationLegalToBuild(&pos, thingBeingTiled, angle,
                                   USE_QUICK_PATHFIND |
                                   TERRAIN_RESTRICTIONS |
                                   CLEAR_PATH |
                                   NO_OBJECT_OVERLAP |
                                   SHROUD_REVEALED,
                                   builderObject, NULL) != LBC_OK)
            break;

        positions[i] = pos;
        tilesUsed++;
    }

    static TileBuildInfo tileInfo;
    tileInfo.tilesUsed = tilesUsed;
    tileInfo.positions = positions;
    return &tileInfo;
}
