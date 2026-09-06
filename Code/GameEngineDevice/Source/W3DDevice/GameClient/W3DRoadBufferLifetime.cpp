// cl: /DNDEBUG /MD /EHsc
// readable body of ??0W3DRoadBuffer@@QAE@XZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DRoadBuffer.cpp
// readable body of ??1W3DRoadBuffer@@QAE@XZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DRoadBuffer.cpp
//
// Constructor (retail 0x0070FB70) and destructor (retail 0x0070FAF0) of one
// class, which therefore need one declaration of it. The two files this
// replaces described the same 0x58-byte layout twice and disagreed on a single
// field: the constructor only ever stores zero into m_map, so it could call the
// pointer void*, while the destructor releases a reference through it. The
// destructor's type is the one that says what the field is, so it is the one
// kept here, and the constructor still emits the same store.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Tools/Launcher/Toolkit/Support/RefCounted.h
class RefCounted
{
public:
	virtual void Delete_This() = 0;
	int m_refs;

	void Release_Ref()
	{
		--m_refs;
		if (m_refs == 0)
			Delete_This();
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureBaseClass
{
public:
	void Release_Ref();
};

class TextureRef
{
public:
	TextureRef() : m_p(0) {}
	~TextureRef()
	{
		if (m_p != 0)
			m_p->Release_Ref();
	}
	TextureBaseClass *m_p;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DRoadBuffer.h
class W3DRoadBuffer
{
public:
	W3DRoadBuffer();
	~W3DRoadBuffer();

private:
	void *m_roadTypes;
	void *m_roads;
	int m_numRoads;
	unsigned char m_initialized;
	unsigned char m_pad0d[3];
	RefCounted *m_map;
	void *m_lights;
	unsigned char m_pad18[0x14];
	int m_curRoadType;
	int m_curUniqueID;
	unsigned char m_pad34[4];
	int m_maxRoadSegments;
	int m_maxRoadVertex;
	int m_maxRoadIndex;
	int m_maxRoadTypes;
	unsigned char m_pad48[8];
	unsigned char m_updateBuffers;
	unsigned char m_secondFlag;
	unsigned char m_pad52[2];
	TextureRef m_texture;

protected:
	void allocateRoadBuffers();
	void freeRoadBuffers();
};

// ??0W3DRoadBuffer@@QAE@XZ
W3DRoadBuffer::W3DRoadBuffer()
	: m_roads(0), m_numRoads(0), m_initialized(0),
	  m_map(0), m_lights(0), m_curRoadType(0), m_curUniqueID(0),
	  m_maxRoadSegments(500), m_maxRoadVertex(1000),
	  m_maxRoadIndex(2000), m_maxRoadTypes(8),
	  m_updateBuffers(1), m_secondFlag(1), m_texture()
{
	allocateRoadBuffers();
}

// ??1W3DRoadBuffer@@QAE@XZ
W3DRoadBuffer::~W3DRoadBuffer()
{
	freeRoadBuffers();
	if (m_map != 0)
	{
		m_map->Release_Ref();
		*(volatile RefCounted **)&m_map = 0;
	}
}
