// cl: /DNDEBUG /DLOAD_TEST_ASSETS /MD /EHsc
// Clean BFME RoadType cleanup with its texture-path member and base-owned texture.

class TextureBaseClass
{
public:
	void Release_Ref();
};

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

class AsciiString
{
public:
	~AsciiString();

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

class RoadType : public RoadTypeBase
{
public:
	~RoadType();

private:
	RefCounted *m_vertexRoad;
	RefCounted *m_indexRoad;
	char m_fields[0x14];
	AsciiString m_texturePath;
};

RoadType::~RoadType()
{
	release(m_vertexRoad);
	release(m_indexRoad);
}
