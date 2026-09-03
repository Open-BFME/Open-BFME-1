// cl: /DNDEBUG /MD /EHsc
// BFME retail 0x0072F110: TerrainTracksRenderObjClass destructor at the
// retail 0x1304-byte layout (the Zero Hour header is larger).

typedef unsigned char Bool;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureClass
{
public:
	void Release_Ref();
};

class TerrainTrackRenderBase
{
public:
	virtual ~TerrainTrackRenderBase() {}

private:
	int m_refCount;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DTerrainTracks.h
class TerrainTracksRenderObjClass : public TerrainTrackRenderBase
{
public:
	virtual ~TerrainTracksRenderObjClass();

private:
	TextureClass * volatile m_stageZeroTexture;     // +0x0008
	volatile int m_topIndex;                       // +0x000C
	volatile int m_bottomIndex;                    // +0x0010
	volatile int m_activeEdgeCount;                // +0x0014
	unsigned char m_edgesAndAnchor[0x12E4 - 0x18];
	volatile int m_totalEdgesAdded;                // +0x12E4
	volatile int m_ownerState;                     // +0x12E8
	volatile Bool m_haveAnchor;                    // +0x12EC
	unsigned char m_tail[0x12F9 - 0x12ED];
	volatile Bool m_haveCap;                       // +0x12F9
};

TerrainTracksRenderObjClass::~TerrainTracksRenderObjClass()
{
	m_haveAnchor = false;
	m_haveCap = true;
	m_ownerState = 0;
	m_totalEdgesAdded = 0;
	m_topIndex = 0;
	m_bottomIndex = 0;
	m_activeEdgeCount = 0;

	if (TextureClass *texture = m_stageZeroTexture)
		texture->Release_Ref();
}
