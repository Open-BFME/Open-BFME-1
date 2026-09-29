// cl: /DNDEBUG /MD /EHsc
// Retail 0x007B4E40, 251 bytes: W3DProjectedShadowManager::~W3DProjectedShadowManager.
//
// Identity: the exact constructor at 0x007AF5A0 installs vtable 0x01128404, whose
// slot zero is the scalar-deleting wrapper at 0x007B4FB0 (W3DProjectedShadowManagerDeletingDestructor.cpp),
// and that wrapper calls this body through ILT 0x0001412D.
//
// Body: it resets the two shadow lists (ILT 0x00033D70 and 0x0001C9A9, the same
// pair BfmeThing928F::bfmeGo928F runs), releases the container at +0x24C, the two
// static buffers at 0x01306E08 and 0x01306E04 as ReleaseResources does, drops the
// reference to the render target at +0x20, deletes the texture manager at +0x24C
// (freeAllTextures, then its two hash tables), destroys the light environment at +0x24
// and restores the base vtable 0x011283AC.

class HashTableClass
{
public:
	~HashTableClass();
};

class BfmeSub928F
{
public:
	void bfmeTail928F();

	~BfmeSub928F()
	{
		bfmeTail928F();
		delete m_texturePtrTable;
		m_texturePtrTable = 0;
		delete m_missingTextureTable;
		m_missingTextureTable = 0;
	}

	HashTableClass *m_texturePtrTable;
	HashTableClass *m_missingTextureTable;
};

class W3DShadowContainerShim
{
public:
	void release(void);
};

class BfmeThing928F
{
public:
	void bfmeOne928F();
	void bfmeTwo928F();
};

class RefCounted
{
public:
	virtual void deleteThis(void);
	void releaseRef(void)
	{
		m_refs--;
		if (m_refs == 0)
			deleteThis();
	}

	int m_refs;
};

class Gen_0094a880
{
public:
	void m(void);
};

class ShadowLightEnvironment
{
public:
	~ShadowLightEnvironment() { ((Gen_0094a880 *)this)->m(); }

private:
	unsigned char m_data[0x228];
};

class ShadowBuffer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void __stdcall release();
};

extern ShadowBuffer *g_01306E04;
extern ShadowBuffer *g_01306E08;

class ProjectedShadowManager
{
public:
	virtual ~ProjectedShadowManager() {}
};

class W3DProjectedShadowManager : public ProjectedShadowManager
{
public:
	virtual ~W3DProjectedShadowManager();

private:
	void *m_shadowList;		// +0x04
	void *m_decalList;		// +0x08
	void *m_simpleDecalList;	// +0x0C
	void *m_10;
	void *m_14;
	void *m_18;
	void *m_1C;
	RefCounted *m_renderTarget;	// +0x20
	ShadowLightEnvironment m_lightEnvironment;	// +0x24
	BfmeSub928F *m_textureManager;	// +0x24C
	void *m_250;
};

W3DProjectedShadowManager::~W3DProjectedShadowManager()
{
	((BfmeThing928F *)this)->bfmeOne928F();
	((BfmeThing928F *)this)->bfmeTwo928F();

	((W3DShadowContainerShim *)m_textureManager)->release();
	if (g_01306E08)
		g_01306E08->release();
	if (g_01306E04)
		g_01306E04->release();
	g_01306E08 = 0;
	g_01306E04 = 0;

	if (m_renderTarget)
	{
		m_renderTarget->releaseRef();
		m_renderTarget = 0;
	}

	if (m_textureManager)
		delete m_textureManager;
	m_textureManager = 0;
}
