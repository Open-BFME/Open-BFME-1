// cl: /DNDEBUG /MD
// readable body of ??0TerrainTracksRenderObjClass@@QAE@XZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainTracks.cpp

struct TerrainTrackEdge
{
	void Reset()
	{
		value0 = 0;
		value1 = 0;
		value2 = 0;
		value3 = 0;
		value4 = 0;
		value5 = 0;
		value6 = 0;
		value7 = 0;
		value8 = 0;
		value9 = 0;
		value10 = 0;
		value11 = 0;
	}

	int value0;
	int value1;
	int value2;
	int value3;
	int value4;
	int value5;
	int value6;
	int value7;
	int value8;
	int value9;
	int value10;
	int value11;
};

class TerrainTrackBase
{
public:
	TerrainTrackBase()
	{
		refCount = 1;
		vtable = 0x011212a4;
		listLink = 0;
	}

private:
	unsigned int vtable;
	int refCount;
	int listLink;
};

struct TerrainTrackVector3
{
	TerrainTrackVector3(float xValue, float yValue, float zValue)
	{
		x = xValue;
		y = yValue;
		z = zValue;
	}

	float x;
	float y;
	float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DTerrainTracks.h
class TerrainTracksRenderObjClass : private TerrainTrackBase
{
public:
	TerrainTracksRenderObjClass();

private:
	int topIndex;
	int bottomIndex;
	int activeEdgeCount;
	TerrainTrackEdge edges[100];
	TerrainTrackVector3 lastAnchor;
	int totalEdgesAdded;
	int ownerState;
	bool haveAnchor;
	bool haveCap;
	char pad0[2];
	int field12f0;
	int field12f4;
	bool bound;
	bool airborne;
	char pad1[2];
	void *nextSystem;
	void *prevSystem;
};

TerrainTracksRenderObjClass::TerrainTracksRenderObjClass()
	: lastAnchor(0.0f, 1.0f, 2.25f)
{
	airborne = true;
	haveAnchor = false;
	ownerState = 0;
	totalEdgesAdded = 0;
	topIndex = 0;
	bottomIndex = 0;
	haveCap = false;
	activeEdgeCount = 0;

	for (int i = 0; i < 100; ++i)
		edges[i].Reset();

	field12f0 = 0;
	field12f4 = 0;
	bound = false;
	nextSystem = 0;
	prevSystem = 0;
}
