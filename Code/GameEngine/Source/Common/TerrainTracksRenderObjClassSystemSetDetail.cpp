// cl: /DNDEBUG /MD

struct GlobalData
{
	char pad[0x1f4];
	int maxTankTrackEdges;
	int maxTankTrackOpaqueEdges;
	int maxTankTrackFadeDelay;
};

extern GlobalData *TheGlobalData;

class RefCountedResource
{
public:
	virtual void Delete_This();
	void Release_Ref()
	{
		--refCount;
		if (refCount == 0)
			Delete_This();
	}
	int refCount;
};

class TerrainTracksRenderObjClassSystem
{
public:
	void setDetail();
	void ReAcquireResources();

protected:
	void clearTracks();

	private:
	RefCountedResource *indexBuffer;
	RefCountedResource *vertexMaterialClass;
	RefCountedResource *vertexBuffer;
	int shaderClass;
	void *usedModules;
	void *freeModules;
	void *terrainTracksScene;
	int maxTankTrackEdges;
	int maxTankTrackOpaqueEdges;
	int maxTankTrackFadeDelay;
};

void TerrainTracksRenderObjClassSystem::setDetail()
{
	clearTracks();

	RefCountedResource *resource = vertexMaterialClass;
	if (resource) {
		resource->Release_Ref();
		*(RefCountedResource * volatile *)&vertexMaterialClass = 0;
	}
	resource = indexBuffer;
	if (resource) {
		resource->Release_Ref();
		*(RefCountedResource * volatile *)&indexBuffer = 0;
	}

	maxTankTrackEdges = TheGlobalData->maxTankTrackEdges;
	maxTankTrackOpaqueEdges = TheGlobalData->maxTankTrackOpaqueEdges;
	maxTankTrackFadeDelay = TheGlobalData->maxTankTrackFadeDelay;

	ReAcquireResources();
}
