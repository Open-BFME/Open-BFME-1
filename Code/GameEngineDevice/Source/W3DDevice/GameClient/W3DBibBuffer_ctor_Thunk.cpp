// cl: /DNDEBUG /MD /EHsc
// W3DBibBuffer constructor, retail RVA 0x006D73C0 (331 bytes).
// Identity: TBBib.tga / TBRedBib.tga and the adjacent matched bib methods.
// BFME replaces the ZH raw texture pointers with owning four-byte handles.
// Handle ABI follows RoadTypeLoadTexture.cpp: 16-bit retain at +4,
// Release_Ref at RVA 0x009EB7A0, and getFilter at RVA 0x0090DD50.
// The allocation call goes through ILT RVA 0x00024D66 to 0x006D69D0.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DBibBuffer.h

class BFMEWaterTrackTexture
{
public:
	void Release_Ref();
};

class BFMEWaterTrackTextureHandle
{
public:
	BFMEWaterTrackTexture *m_texture;

	~BFMEWaterTrackTextureHandle()
	{
		if (m_texture)
			m_texture->Release_Ref();
	}
};

BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(char *name, int mipCount, int format);

class ShroudFilter
{
public:
	char m_pad[12];
	int m_uAddress;
	int m_vAddress;
};

class ShroudTexture
{
public:
	ShroudTexture() : m_texture(0) {}

	~ShroudTexture()
	{
		if (m_texture)
			m_texture->Release_Ref();
	}

	void operator=(const BFMEWaterTrackTextureHandle &other)
	{
		if (other.m_texture)
			++*(unsigned short *)((char *)other.m_texture + 4);
		if (m_texture)
			m_texture->Release_Ref();
		m_texture = other.m_texture;
	}

	ShroudFilter *getFilter();
	BFMEWaterTrackTexture *m_texture;
};

class W3DBibBuffer
{
public:
	W3DBibBuffer();

protected:
	void allocateBibBuffers();

private:
	void *m_vertexBib;
	int m_vertexBibSize;
	void *m_indexBib;
	int m_indexBibSize;
	ShroudTexture m_bibTexture;
	ShroudTexture m_highlightBibTexture;
	int m_curNumBibVertices;
	int m_curNumBibIndices;
	// Remaining counters and 1000 retail TBib records; not accessed here.
	char m_bibsAndCounters[0x109c8 - 0x20];
	int m_numBibs;
	bool m_anythingChanged;
	bool m_updateAllKeys;
	bool m_initialized;
};

W3DBibBuffer::W3DBibBuffer()
{
	m_initialized = false;
	m_vertexBib = 0;
	m_indexBib = 0;
	m_curNumBibVertices = 0;
	m_curNumBibIndices = 0;
	m_numBibs = 0;
	m_anythingChanged = true;
	m_indexBibSize = 384;
	m_vertexBibSize = 256;
	allocateBibBuffers();

	m_bibTexture = BFMEGetWaterTrackTexture("TBBib.tga", 0, 0);
	m_highlightBibTexture = BFMEGetWaterTrackTexture("TBRedBib.tga", 0, 0);
	m_bibTexture.getFilter()->m_uAddress = 1;
	m_bibTexture.getFilter()->m_vAddress = 1;
	m_highlightBibTexture.getFilter()->m_uAddress = 1;
	m_highlightBibTexture.getFilter()->m_vAddress = 1;
	m_initialized = true;
}
