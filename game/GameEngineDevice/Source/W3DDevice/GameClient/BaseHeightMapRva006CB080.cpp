// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x006CB080, complete boundary [0x006CB080,0x006CB199).
// BaseHeightMapRenderObjClass::initHeightData at 0x006D0590 calls this
// protected helper through ILT 0x00034D56.  The +0xD0/+0xD4/+0xD8 fields and
// the counters beyond the 500-entry scorch array agree with the original
// BaseHeightMap layout and with freeScorchBuffers at 0x006C7E10.

typedef int Int;

enum MipCountType
{
	MIP_LEVELS_3 = 3
};

class DX8VertexBufferClass
{
public:
	enum UsageType { USAGE_DEFAULT = 0, USAGE_DYNAMIC = 1 };

	DX8VertexBufferClass(unsigned fvf, unsigned short count, UsageType usage,
		unsigned vertexSize);

private:
	unsigned char m_body[0x20];
};

class DX8IndexBufferClass
{
public:
	enum UsageType { USAGE_DEFAULT = 0, USAGE_DYNAMIC = 1 };

	DX8IndexBufferClass(unsigned short count, UsageType usage);

private:
	unsigned char m_body[0x18];
};

class BFMETextureRelease
{
public:
	virtual void Delete_This(void);
	void Release_Ref(void);

	void Add_Ref(void)
	{
		++m_refCount;
	}

private:
	unsigned short m_refCount;
};

// Retail 0x006D65B0 initializes this one-pointer owning handle from the scorch
// texture tag and returns this.  Its MipCountType argument is present in the
// original TerrainTex API even though this BFME body does not inspect it.
class Rva006D65B0ScorchHandle
{
public:
	Rva006D65B0ScorchHandle(MipCountType mipCount);

	~Rva006D65B0ScorchHandle(void)
	{
		if (m_texture)
			m_texture->Release_Ref();
	}

	Rva006D65B0ScorchHandle &operator=(const Rva006D65B0ScorchHandle &other)
	{
		if (other.m_texture)
			other.m_texture->Add_Ref();
		if (m_texture)
			m_texture->Release_Ref();
		m_texture = other.m_texture;
		return *this;
	}

private:
	BFMETextureRelease *m_texture;
};

class BaseHeightMapRenderObjClass
{
protected:
	void allocateScorchBuffers(void);

private:
	void freeScorchBuffers(void);

	unsigned char m_beforeScorchBuffers[0xd0];
	DX8VertexBufferClass *m_vertexScorch;
	DX8IndexBufferClass *m_indexScorch;
	Rva006D65B0ScorchHandle m_scorchTexture;
	Int m_curNumScorchVertices;
	Int m_curNumScorchIndices;
	unsigned char m_scorchesAndCount[0x2fc8 - 0xe4];
	Int m_scorchesInBuffer;
};

void BaseHeightMapRenderObjClass::allocateScorchBuffers(void)
{
	if (m_vertexScorch || m_indexScorch)
		freeScorchBuffers();

	m_vertexScorch = new DX8VertexBufferClass(
		0x142, 8194, DX8VertexBufferClass::USAGE_DEFAULT, 0);
	m_indexScorch = new DX8IndexBufferClass(
		6 * 8194, DX8IndexBufferClass::USAGE_DEFAULT);
	m_scorchTexture = Rva006D65B0ScorchHandle(MIP_LEVELS_3);
	m_scorchesInBuffer = 0;
	m_curNumScorchVertices = 0;
	m_curNumScorchIndices = 0;
}
