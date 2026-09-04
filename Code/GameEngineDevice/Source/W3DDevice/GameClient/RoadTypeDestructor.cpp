// cl: /DNDEBUG /DLOAD_TEST_ASSETS /MD /EHsc
// readable body of ??1RoadType@@QAE@XZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DRoadBuffer.cpp
// Clean BFME RoadType cleanup with its texture-path member and base-owned texture.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureBaseClass
{
public:
	void Release_Ref();
};

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();
	void clear() { m_data = 0; }

private:
	void *m_data;
};

static void release(RefCounted *&object)
{
	if (object != 0)
	{
		object->Release_Ref();
		object = 0;
	}
}

class RoadTypeBase
{
protected:
	RoadTypeBase() : m_roadTexture(0) {}
	~RoadTypeBase()
	{
		if (m_roadTexture != 0)
			m_roadTexture->Release_Ref();
	}

	TextureBaseClass *m_roadTexture;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DRoadBuffer.h
class RoadType : public RoadTypeBase
{
public:
	RoadType();
	~RoadType();

private:
	RefCounted *m_vertexRoad;
	RefCounted *m_indexRoad;
	int m_numRoadVertices;
	int m_numRoadIndices;
	int m_uniqueID;
	bool m_isAutoLoaded;
	char m_alignment[3];
	int m_stackingOrder;
	AsciiString m_texturePath;
};

RoadType::RoadType()
{
	m_vertexRoad = 0;
	m_indexRoad = 0;
	m_numRoadVertices = 0;
	m_numRoadIndices = 0;
	m_uniqueID = -1;
	m_isAutoLoaded = false;
	m_stackingOrder = 0;
	m_texturePath.clear();
}

RoadType::~RoadType()
{
	release(m_vertexRoad);
	release(m_indexRoad);
}
