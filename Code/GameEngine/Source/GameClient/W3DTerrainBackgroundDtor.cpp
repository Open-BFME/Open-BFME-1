// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x00728C50: W3DTerrainBackground destructor.  Calls freeTerrainBuffers
// then releases the two textures at +0x2C/+0x30 (TextureBaseClass::Release_Ref)
// the map at +0x4C (inline RefCount) and the +0xC0 block (Gen00881EF0).
// +0x2C/+0x30 have compiler-generated member dtors so the TU is /EHsc.

class TextureBaseClass
{
public:
	void Release_Ref(void);
};

class RefCountClass
{
public:
	virtual void Delete_This(void);
	void Release_Ref(void)
	{
		NumRefs--;
		if (NumRefs == 0)
			Delete_This();
	}
private:
	int NumRefs;
};

extern "C" void Gen00881EF0(void *);

struct TerrainTexPtr
{
	TextureBaseClass *p;
	~TerrainTexPtr()
	{
		if (p)
			p->Release_Ref();
	}
};

#define REF_PTR_RELEASE(x) { if (x) { x->Release_Ref(); x = 0; } }

class W3DTerrainBackground
{
public:
	~W3DTerrainBackground(void);

protected:
	void freeTerrainBuffers(void);

private:
	unsigned char m_pad00[0x2C];
	TerrainTexPtr m_terrainTexture;
	TerrainTexPtr m_terrainTexture2X;
	unsigned char m_pad34[0x4C - 0x34];
	RefCountClass *m_map;
	unsigned char m_pad50[0xC0 - 0x50];
	void *m_blockC0;
};

W3DTerrainBackground::~W3DTerrainBackground(void)
{
	freeTerrainBuffers();
	if (m_terrainTexture.p)
	{
		m_terrainTexture.p->Release_Ref();
		m_terrainTexture.p = 0;
	}
	if (m_terrainTexture2X.p)
	{
		m_terrainTexture2X.p->Release_Ref();
		m_terrainTexture2X.p = 0;
	}
	REF_PTR_RELEASE(m_map);
	if (m_blockC0)
	{
		Gen00881EF0(m_blockC0);
		m_blockC0 = 0;
	}
}
