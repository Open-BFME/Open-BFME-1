// cl: /DNDEBUG /MD /EHsc

// ??1W3DVolumetricShadowManager@@QAE@XZ, retail 0x007BDE90, 286 bytes.
//
// De-lifted from the __emit dump. The call chain is the already-matched
// W3DRadarResetLock/bfmeUnlock1179 scoped-lock pair (BfmeConv1696.cpp),
// GenAlpha::h00024D2A (GenAlpha_h00024D2A.cpp), the geometry manager's two
// HashTableClass tables, TheBfmeReleaseOwner's real W3DBufferManager
// teardown, and two BFME-only shadow vertex/index buffer pools absent from
// the Zero Hour source, which only frees D3D resources and the geometry
// manager.

void W3DRadarResetLock(void);
char bfmeUnlock1179(void);
void __cdecl operator delete(void *);
void __cdecl operator delete[](void *);

class BfmeScopedFM
{
public:
	BfmeScopedFM(void) {}
	~BfmeScopedFM(void) { bfmeUnlock1179(); }
	int m_bfmePadFM;
};

class GenAlpha
{
public:
	void h00024D2A();
};

class HashTableClass
{
public:
	~HashTableClass();
};

class HAnimManagerClass
{
public:
	void Free_All_Anims();
};

class W3DBufferManager
{
public:
	~W3DBufferManager();
};

extern W3DBufferManager *TheBfmeReleaseOwner;	// 0x01306DE8

struct BfmeShadowPoolFM
{
	void *ptr;
	int size;
	char reserved;
	bool inUse;
	int count;
};

extern BfmeShadowPoolFM g_bfmeShadowPoolA;	// 0x01306F40
extern BfmeShadowPoolFM g_bfmeShadowPoolB;	// 0x01306F58

class W3DShadowGeometryManagerFM
{
public:
	HashTableClass *GeomPtrTable;
	HashTableClass *MissingGeomTable;
};

class W3DVolumetricShadowManager
{
	void *m_shadowList;
	void *m_dynamicShadowVolumesToRender;
	W3DShadowGeometryManagerFM *m_W3DShadowGeometryManager;
public:
	~W3DVolumetricShadowManager();
};

// ??1W3DVolumetricShadowManager@@QAE@XZ
W3DVolumetricShadowManager::~W3DVolumetricShadowManager()
{
	W3DRadarResetLock();
	BfmeScopedFM scope;

	reinterpret_cast<GenAlpha *>(this)->h00024D2A();

	W3DShadowGeometryManagerFM *mgr = m_W3DShadowGeometryManager;
	if (mgr)
	{
		reinterpret_cast<HAnimManagerClass *>(mgr)->Free_All_Anims();

		HashTableClass *geomTable = mgr->GeomPtrTable;
		if (geomTable)
		{
			geomTable->~HashTableClass();
			operator delete(geomTable);
		}
		mgr->GeomPtrTable = 0;

		HashTableClass *missingTable = mgr->MissingGeomTable;
		if (missingTable)
		{
			missingTable->~HashTableClass();
			operator delete(missingTable);
		}
		mgr->MissingGeomTable = 0;

		operator delete(mgr);
	}
	m_W3DShadowGeometryManager = 0;

	delete TheBfmeReleaseOwner;
	TheBfmeReleaseOwner = 0;

	g_bfmeShadowPoolA.count = 0;
	if (g_bfmeShadowPoolA.ptr)
	{
		if (g_bfmeShadowPoolA.inUse)
		{
			operator delete[](g_bfmeShadowPoolA.ptr);
			g_bfmeShadowPoolA.ptr = 0;
		}
	}
	g_bfmeShadowPoolA.inUse = false;
	g_bfmeShadowPoolA.size = 0;

	g_bfmeShadowPoolB.count = 0;
	if (g_bfmeShadowPoolB.ptr)
	{
		if (g_bfmeShadowPoolB.inUse)
		{
			operator delete[](g_bfmeShadowPoolB.ptr);
			g_bfmeShadowPoolB.ptr = 0;
		}
	}
	g_bfmeShadowPoolB.inUse = false;
	g_bfmeShadowPoolB.size = 0;
}
