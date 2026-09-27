// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/stringinline /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWMath
// stlport
// Retail 0038A9F0: GameLogic.cpp's static placeNetworkBuildingsForPlayer.
// Identity: "Player_%d_Start"/"Player_%d_Rally" waypoint formats, the sole
// direct callee 0038A770 placeObjectAtPosition (twice), and the Zero Hour
// body order; its sole caller is GameLogic::startNewGame (0079555B).
// The landed helper is included unchanged so VC7.1 derives the same private
// static ABI (player in ECX; string then Coord3D* on the stack, caller pops).
// Its by-value AsciiString is the format(AsciiString,...) model this body needs,
// so the StringInline guard is pre-set and both share one string class.
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <bitset>
#include "Common/AsciiString.h"
#define BFME_STRING_INLINE_H
#include "ObjectPlacement0038A770.cpp"

class GeometryInfo {
public:
    char pad000[0x14]; Real m_boundingSphereRadius;
    Real getBoundingSphereRadius() const { return m_boundingSphereRadius; }
};
// upstream layout: Object+0xAC m_geometryInfo, as in ObjectGeometry.cpp.
class ObjectGeometry0038A9F0 {
public:
    char pad000[0xac]; GeometryInfo m_geometryInfo;
    const GeometryInfo &getGeometryInfo() const { return m_geometryInfo; }
};

extern void j_0003aa8f();
extern void j_00007a13();
extern void j_00004f1b();
// Player notifications, reached through their ILT thunks.
class PlayerNotify0038A9F0 : public Player {
public:
    void onStructureCreated(Object *builder, Object *structure) {
        union { void (*entry)(); void (PlayerNotify0038A9F0::*member)(Object *,Object *); } call;
        call.entry=j_0003aa8f; (this->*call.member)(builder,structure);
    }
    void onStructureConstructionComplete(Object *builder, Object *structure, Bool isRebuild) {
        union { void (*entry)(); void (PlayerNotify0038A9F0::*member)(Object *,Object *,Bool); } call;
        call.entry=j_00007a13; (this->*call.member)(builder,structure,isRebuild);
    }
    void onUnitCreated(Object *factory, Object *unit) {
        union { void (*entry)(); void (PlayerNotify0038A9F0::*member)(Object *,Object *); } call;
        call.entry=j_00004f1b; (this->*call.member)(factory,unit);
    }
};

extern void j_0003252e();
// Retail 000E0AD0 through ILT 0003252E: the ten starting-unit names at +0x38.
class Rva000E0AD0Local
{
    char m_pad[0x38];
public:
    void *get(Int index) {
        union { void (*entry)(); void *(Rva000E0AD0Local::*member)(Int); } call;
        call.entry=j_0003252e; return (this->*call.member)(index);
    }
};
class PlayerTemplate {
public:
    char pad000[0x34]; AsciiString m_startingBuilding;
    const AsciiString &getStartingBuilding() const { return m_startingBuilding; }
};

class GameSlot {
public:
    char pad000[0x10]; Int m_startPos;
    Int getStartPos() const { return m_startPos; }
};
class Waypoint {
public:
    char pad000[0xc]; Coord3D m_location;
    const Coord3D *getLocation() const { return &m_location; }
};
Waypoint *Rva00388820_FindWaypointByName(AsciiString name);

struct RvaAsciiStringView
{
    unsigned int m_data;
    Bool isEmpty() const
    {
        return m_data == 0 || *(const unsigned short *)(m_data + 4) == 0;
    }
    Bool isNotEmpty() const
    {
        return m_data != 0 && *(const unsigned short *)(m_data + 4) != 0;
    }
};

class RvaTerrainLogicView
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual float getGroundHeight(float x, float y, Coord3D *normal = 0) const;
};
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;

class PartitionManager
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void update();
};
extern PartitionManager *ThePartitionManager;

struct FindPositionOptions {
    unsigned flags; Real minRadius, maxRadius, startAngle, maxZDelta;
    Object *ignoreObject; const Object *sourceToPathToDest; Object *relationshipObject;
    FindPositionOptions() : flags(0), minRadius(0), maxRadius(0), startAngle(-99999.9f),
        maxZDelta(1e10f), ignoreObject(0), sourceToPathToDest(0), relationshipObject(0) {}
};
// Free cdecl, pinned at ILT 00026C4C (body 001AF610).
bool findPositionAround(const Coord3D *center, const FindPositionOptions *options, Coord3D *result);

static void placeNetworkBuildingsForPlayer(Int slotNum, const GameSlot *pSlot,
    Player *pPlayer, const PlayerTemplate *pTemplate)
{
    Int startPos = pSlot->getStartPos();
    AsciiString waypointName;
    waypointName.format("Player_%d_Start", startPos + 1);
    AsciiString rallyWaypointName;
    rallyWaypointName.format("Player_%d_Rally", startPos + 1);
    Waypoint *waypoint = Rva00388820_FindWaypointByName(waypointName);
    Waypoint *rallyWaypoint = Rva00388820_FindWaypointByName(rallyWaypointName);
    if (!waypoint)
        return;

    Coord3D pos;
    const float *waypointCoords = reinterpret_cast<const float *>(reinterpret_cast<const char *>(waypoint) + 0xc);
    pos.x = waypointCoords[0];
    pos.y = waypointCoords[1];
    pos.z = waypointCoords[2];
    pos.z = ((RvaTerrainLogicView *)TheTerrainLogic)->getGroundHeight(pos.x, pos.y);
    AsciiString buildingTemplateName(pTemplate->getStartingBuilding());
    if (((const RvaAsciiStringView *)&buildingTemplateName)->isEmpty())
        return;

    Object *conYard = placeObjectAtPosition(slotNum, buildingTemplateName, pos, pPlayer, pTemplate);
    if (!conYard)
        return;

    PlayerNotify0038A9F0 *notify = static_cast<PlayerNotify0038A9F0 *>(pPlayer);
    const GeometryInfo &geometry = ((const ObjectGeometry0038A9F0 *)conYard)->getGeometryInfo();
    notify->onStructureCreated(NULL, conYard);
    notify->onStructureConstructionComplete(NULL, conYard, FALSE);
    pos.y -= geometry.getBoundingSphereRadius() * 0.5f;
    pos.z = ((RvaTerrainLogicView *)TheTerrainLogic)->getGroundHeight(pos.x, pos.y);
    if (rallyWaypoint)
    {
        pos = *rallyWaypoint->getLocation();
        pos.z = ((RvaTerrainLogicView *)TheTerrainLogic)->getGroundHeight(pos.x, pos.y);
    }

    for (Int i = 0; i < 10; ++i)
    {
        AsciiString objName(*(const AsciiString *)
            ((Rva000E0AD0Local *)pTemplate)->get(i));
        if (((const RvaAsciiStringView *)&objName)->isNotEmpty())
        {
            Coord3D objPos = pos;
            FindPositionOptions options;
            options.minRadius = geometry.getBoundingSphereRadius() * 0.7f;
            options.maxRadius = geometry.getBoundingSphereRadius() * 1.3f;
            ThePartitionManager->update();
            Bool foundPos = findPositionAround(&pos, &options, &objPos);
            if (foundPos)
            {
                Object *unit = placeObjectAtPosition(slotNum, objName, objPos, pPlayer, pTemplate);
                if (unit)
                    notify->onUnitCreated(NULL, unit);
            }
        }
    }
}

// Emission anchor keeping the static body and its four-argument frame.
void emitPlaceNetworkBuildingsForPlayer(Int slotNum, const GameSlot *pSlot,
    Player *pPlayer, const PlayerTemplate *pTemplate)
{
    placeNetworkBuildingsForPlayer(slotNum, pSlot, pPlayer, pTemplate);
}
