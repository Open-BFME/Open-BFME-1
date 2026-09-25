// ?placeNetworkBuildingsForPlayer@@YAXHPBVGameSlot@@PAVPlayer@@PBVPlayerTemplate@@@Z
// partial score=0.66 date=2026-09-25
// ?placeNetworkBuildingsForPlayer@@YAXHPBVGameSlot@@PAVPlayer@@PBVPlayerTemplate@@@Z
// Experiment: same-TU static-helper visibility, direct waypoint fields and BFME constants.
// cl: /D_STLP_USE_STATIC_LIB /Ireference/shims/stringbaseascii /Ireference/shims/multiplayer /Ireference/shims/sweep /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib
// stlport
#define placeNetworkBuildingsForPlayer placeNetworkBuildingsForPlayer_original
#include "../../Code/GameEngine/Source/GameLogic/System/GameLogic.cpp"
#undef placeNetworkBuildingsForPlayer

extern const float Rva0107533C;
extern const float Rva01075C6C;
extern const float Rva010EB40C;

class Rva000E0AD0Local
{
    char m_pad[0x38];
public:
    void *get(Int index);
};

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

static void placeNetworkBuildingsForPlayer(Int slotNum, const GameSlot *pSlot,
    Player *pPlayer, const PlayerTemplate *pTemplate)
{
    Int startPos = pSlot->getStartPos();
    AsciiString waypointName;
    waypointName.format("Player_%d_Start", startPos + 1);
    AsciiString rallyWaypointName;
    rallyWaypointName.format("Player_%d_Rally", startPos + 1);
    Waypoint *waypoint = findNamedWaypoint(waypointName);
    Waypoint *rallyWaypoint = findNamedWaypoint(rallyWaypointName);
    if (!waypoint)
        return;

    Coord3D pos;
    const float *waypointCoords = reinterpret_cast<const float *>(reinterpret_cast<const char *>(waypoint) + 0xc);
    pos.x = waypointCoords[0];
    pos.y = waypointCoords[1];
    pos.z = waypointCoords[2];
    pos.z = ((RvaTerrainLogicView *)TheTerrainLogic)->getGroundHeight(pos.x, pos.y);
    AsciiString buildingTemplateName(
        *(const AsciiString *)((const char *)pTemplate + 0x34));
    if (((const RvaAsciiStringView *)&buildingTemplateName)->isEmpty())
        return;

    Object *conYard = placeObjectAtPosition(slotNum, buildingTemplateName, pos, pPlayer, pTemplate);
    if (!conYard)
        return;

    pPlayer->onStructureCreated(NULL, conYard);
    pPlayer->onStructureConstructionComplete(NULL, conYard, FALSE);
    pos.y -= conYard->getGeometryInfo().getBoundingSphereRadius() * Rva0107533C;
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
            options.minRadius = conYard->getGeometryInfo().getBoundingSphereRadius() * Rva01075C6C;
            options.maxRadius = conYard->getGeometryInfo().getBoundingSphereRadius() * Rva010EB40C;
            ThePartitionManager->update();
            Bool foundPos = ThePartitionManager->findPositionAround(&pos, &options, &objPos);
            if (foundPos)
            {
                Object *unit = placeObjectAtPosition(slotNum, objName, objPos, pPlayer, pTemplate);
                if (unit)
                    pPlayer->onUnitCreated(NULL, unit);
            }
        }
    }
}

void emitPlaceNetworkBuildingsForPlayer(Int slotNum, const GameSlot *pSlot,
    Player *pPlayer, const PlayerTemplate *pTemplate)
{
    placeNetworkBuildingsForPlayer(slotNum, pSlot, pPlayer, pTemplate);
}
