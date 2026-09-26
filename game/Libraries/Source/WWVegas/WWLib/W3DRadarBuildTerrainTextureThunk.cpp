// readable body of ?buildTerrainTexture@W3DRadar@@IAEXPAVTerrainLogic@@@Z: game/GameEngineDevice/Source/W3DDevice/Common/System/W3DRadar.cpp
// readable body of ?removeGoal@Pathfinder@@QAEXPAVObject@@@Z: game/GameEngine/Source/GameLogic/AI/AIPathfind.cpp
class TerrainLogic;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/Common/W3DRadar.h
class W3DRadar
{
protected:
    void buildTerrainTexture(TerrainLogic *);
};

class W3DRadarBuildTerrainTextureShim
{
public:
    void build(TerrainLogic *terrain);
};

void W3DRadar::buildTerrainTexture(TerrainLogic *terrain)
{
    ((W3DRadarBuildTerrainTextureShim *)this)->build(terrain);
}
