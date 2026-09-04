// cl: /DNDEBUG /DWIN32 /MD /EHsc
// BFME retail 0x00708030: RoadType::loadTexture.

typedef int Int;
typedef unsigned char Bool;
typedef unsigned short UnsignedShort;
typedef char Char;

class TextureClass
{
public:
	void Release_Ref(void);
};

class BFMEWaterTrackTexture
{
public:
	void Release_Ref(void);
};

class BFMEWaterTrackTextureHandle
{
public:
	TextureClass *m_texture;

	~BFMEWaterTrackTextureHandle(void)
	{
		if (m_texture)
			((BFMEWaterTrackTexture *)m_texture)->Release_Ref();
	}
};

extern BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(
	Char *name, Int mipCount, Int format);

static inline void BFMEAssignWaterTrackTexture(
	TextureClass *&destination,
	const BFMEWaterTrackTextureHandle &texture)
{
	if (texture.m_texture)
		++*(UnsignedShort *)((Char *)texture.m_texture + 4);
	if (destination)
		((BFMEWaterTrackTexture *)destination)->Release_Ref();
	destination = texture.m_texture;
}

class AsciiString
{
public:
	AsciiString &operator=(const AsciiString &other);
	~AsciiString(void);

	Char *str(void) const
	{
		if (m_data)
			return m_data + 8;
		return (Char *)0x0107388b;
	}

	Char *m_data;
};

class Gen_00920a60
{
public:
	void m(Int value);

	Char m_pad00[0x0c];
	Int m_uAddress;
	Int m_vAddress;
};

class ShroudFilter : public Gen_00920a60
{
};

class ShroudTexture
{
public:
	ShroudFilter *getFilter(void);

	TextureClass *m_texture;
};

class BfmeDX8VertexBuffer
{
public:
	enum UsageType
	{
		USAGE_DEFAULT = 0,
		USAGE_DYNAMIC = 1
	};

	BfmeDX8VertexBuffer(unsigned fvf, UnsignedShort count,
		UsageType usage, unsigned size);

private:
	Char m_body[0x20];
};

class DX8IndexBufferClass
{
public:
	enum UsageType
	{
		USAGE_DEFAULT = 0,
		USAGE_DYNAMIC = 1
	};

	DX8IndexBufferClass(unsigned count, UsageType usage);

private:
	Char m_body[0x18];
};

class GlobalData
{
private:
	Char m_pad00[0xa60];

public:
	UnsignedShort m_maxRoadVertex;
	UnsignedShort m_padA62;
	Int m_maxRoadIndex;
};

#define BFME_GLOBAL_DATA (*(GlobalData **)0x012ed5c8)

#define BFME_ROAD_DYNAMIC (*(volatile Bool *)0x012f9c31)

class RoadType
{
public:
	void loadTexture(AsciiString path, Int id);

private:
	TextureClass *m_roadTexture;
	BfmeDX8VertexBuffer *m_vertexRoad;
	DX8IndexBufferClass *m_indexRoad;
	Int m_numRoadVertices;
	Int m_numRoadIndices;
	Int m_uniqueID;
	Bool m_isAutoLoaded;
	Char m_pad19[3];
	Int m_stackingOrder;
	AsciiString m_texturePath;
};

void RoadType::loadTexture(AsciiString path, Int id)
{
	BFMEAssignWaterTrackTexture(m_roadTexture,
		BFMEGetWaterTrackTexture(path.str(), 3, 0));

	((ShroudTexture *)this)->getFilter()->m(2);
	((ShroudTexture *)this)->getFilter()->m_uAddress = 0;
	((ShroudTexture *)this)->getFilter()->m_vAddress = 0;

	m_vertexRoad = new BfmeDX8VertexBuffer(
		0x142, (UnsignedShort)(BFME_GLOBAL_DATA->m_maxRoadVertex + 4),
		(BFME_ROAD_DYNAMIC ? BfmeDX8VertexBuffer::USAGE_DYNAMIC :
		 BfmeDX8VertexBuffer::USAGE_DEFAULT), 0);
	m_indexRoad = new DX8IndexBufferClass(
		BFME_GLOBAL_DATA->m_maxRoadIndex + 4,
		(BFME_ROAD_DYNAMIC ? DX8IndexBufferClass::USAGE_DYNAMIC :
		 DX8IndexBufferClass::USAGE_DEFAULT));

	m_numRoadVertices = 0;
	m_numRoadIndices = 0;
	AsciiString *texturePath = &m_texturePath;
	texturePath->operator=(path);
	m_uniqueID = id;
}
