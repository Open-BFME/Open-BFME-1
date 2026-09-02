// cl: /DNDEBUG /MD

struct GlobalData
{
	char pad[0x1f4];
	int maxTankTrackEdges;
	int maxTankTrackOpaqueEdges;
	int maxTankTrackFadeDelay;
};

extern GlobalData *TheGlobalData;

class ShaderClass
{
public:
	ShaderClass() : shaderBits(0x0010441b) {}

private:
	unsigned int shaderBits;
};

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
