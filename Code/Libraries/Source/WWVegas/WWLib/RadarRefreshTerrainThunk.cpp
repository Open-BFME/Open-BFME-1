// readable body of ?refreshTerrain@Radar@@UAEXPAVTerrainLogic@@@Z: Code/GameEngine/Source/Common/System/Radar.cpp
// readable body of ?removePos@Pathfinder@@QAEXPAVObject@@@Z: Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp
class TerrainLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Radar.h
class Radar
{
public:
    virtual void refreshTerrain(TerrainLogic *);
};

class RadarRefreshTerrainShim
{
public:
    void run(TerrainLogic *terrain);
};

void Radar::refreshTerrain(TerrainLogic *terrain)
{
    ((RadarRefreshTerrainShim *)this)->run(terrain);
}
