// cl: /DNDEBUG /MD
// readable body of ??0TerrainTracksRenderObjClassSystem@@QAE@XZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainTracks.cpp

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
struct GlobalData
{
	char pad[0x1f4];
	int maxTankTrackEdges;
	int maxTankTrackOpaqueEdges;
	int maxTankTrackFadeDelay;
};

extern GlobalData *TheGlobalData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/shader.h
class ShaderClass
{
public:
	ShaderClass() : shaderBits(0x0010441b) {}

private:
	unsigned int shaderBits;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DTerrainTracks.h
class TerrainTracksRenderObjClassSystem
{
public:
	TerrainTracksRenderObjClassSystem();

private:
	void * volatile indexBuffer;
	void * volatile vertexMaterialClass;
	void * volatile vertexBuffer;
	ShaderClass shaderClass;
	void * volatile usedModules;
	void * volatile freeModules;
	void * volatile terrainTracksScene;
	int maxTankTrackEdges;
	int maxTankTrackOpaqueEdges;
	int maxTankTrackFadeDelay;
};

TerrainTracksRenderObjClassSystem::TerrainTracksRenderObjClassSystem()
{
	usedModules = 0;
	freeModules = 0;
	terrainTracksScene = 0;
	vertexMaterialClass = 0;
	vertexBuffer = 0;
	indexBuffer = 0;
	maxTankTrackEdges = TheGlobalData->maxTankTrackEdges;
	maxTankTrackOpaqueEdges = TheGlobalData->maxTankTrackOpaqueEdges;
	maxTankTrackFadeDelay = TheGlobalData->maxTankTrackFadeDelay;
}
