// ??1TerrainTracksRenderObjClass@@UAE@XZ
// partial score=1.0 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
// BFME retail 0x0072F110: TerrainTracksRenderObjClass destructor at the
// retail 0x1304-byte layout (the Zero Hour header is larger).

typedef unsigned char Bool;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

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
