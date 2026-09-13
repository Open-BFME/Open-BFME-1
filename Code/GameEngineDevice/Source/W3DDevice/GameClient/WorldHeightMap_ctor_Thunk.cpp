// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// Open-BFME: real BFME WorldHeightMap constructor at retail 0x0074E990.
// Its BFME layout and texture/vector member identities are cross-checked
// against the matched WorldHeightMap destructor at 0x0074DE60.

template <class T>
class Rva0074E990AllocProxy
{
public:
	Rva0074E990AllocProxy(T *p) : m_data(p) {}

	T *m_data;
};

template <class T>
class Rva0074E990Vector
{
public:
	Rva0074E990Vector(void) : m_start(0), m_finish(0), m_end_of_storage(0) {}
	~Rva0074E990Vector(void);

	T *m_start;
	T *m_finish;
	Rva0074E990AllocProxy<T> m_end_of_storage;
};

struct Rva0074E990BoundaryPoint { int x; int y; };
struct Rva0074E990ElementByte { char m_body[1]; };
struct Rva0074E990Element16 { char m_body[0x10]; };
struct Rva0074E990Element36 { char m_body[0x24]; };

class Rva0074E990TextureClass
{
public:
	void Release_Ref(void);
};

class Rva0074E990TextureRef
{
public:
	Rva0074E990TextureRef(void) : m_ptr(0) {}
	~Rva0074E990TextureRef(void);

	Rva0074E990TextureClass *m_ptr;
};

// The two arrays use the retail array-with-unwind helper.  Their element
// constructor/destructor operands are the already pinned BFME helper chain.
class Rva0074E990TextureSlot
{
public:
	Rva0074E990TextureSlot(void);
	~Rva0074E990TextureSlot(void);

private:
	char m_body[0x28];
};

class Rva0074E990RefCountClass
{
public:
	Rva0074E990RefCountClass(void) : m_numRefs(1) {}
	virtual void Delete_This(void);

protected:
	virtual ~Rva0074E990RefCountClass(void) {}

private:
	int m_numRefs;
};

class BfmeBigJK
{
public:
	void bfmeClearJK(void);
};

class WorldHeightMap : public Rva0074E990RefCountClass
{
protected:
	WorldHeightMap();
	virtual ~WorldHeightMap(void);

public:
	static void setupAlphaTiles(void);

private:
	int m_width;                                                // +0x08
	int m_height;                                               // +0x0C
	int m_borderSize;                                           // +0x10
	Rva0074E990Vector<Rva0074E990BoundaryPoint> m_boundaries;   // +0x14
	int m_dataSize;                                             // +0x20
	unsigned char *m_data;                                      // +0x24
	Rva0074E990Vector<Rva0074E990ElementByte> m_vector28;
	char m_gap34[4];
	Rva0074E990Vector<Rva0074E990ElementByte> m_vector38;
	Rva0074E990Vector<Rva0074E990ElementByte> m_vector44;
	Rva0074E990Vector<Rva0074E990ElementByte> m_vector50;
	Rva0074E990Vector<Rva0074E990ElementByte> m_vector5c;
	Rva0074E990Vector<Rva0074E990ElementByte> m_vector68;
	Rva0074E990Vector<Rva0074E990ElementByte> m_vector74;
	Rva0074E990Vector<Rva0074E990ElementByte> m_vector80;
	unsigned char *m_tileNdxes;                                 // +0x8C
	unsigned char *m_blendTileNdxes;                            // +0x90
	unsigned char *m_cliffInfoNdxes;                            // +0x94
	unsigned char *m_extraBlendTileNdxes;                       // +0x98
	char m_gap9c[8];
	void *m_sourceTiles[0x1000];                                // +0xA4
	void *m_edgeTiles[0x1000];                                  // +0x40A4
	Rva0074E990Vector<Rva0074E990Element16> m_vectorA4;
	Rva0074E990Vector<Rva0074E990Element36> m_vectorB0;
	char m_gap80bc[4];
	Rva0074E990TextureSlot m_textureSlotsA[0x200];              // +0x80C0
	char m_gapD0c0[4];
	Rva0074E990TextureSlot m_textureSlotsB[0x200];              // +0xD0C4
	Rva0074E990TextureRef m_texture0;                           // +0x120C4
	int m_terrainTexHeight;                                     // +0x120C8
	Rva0074E990TextureRef m_texture1;                           // +0x120CC
	int m_alphaTexHeight;                                       // +0x120D0
	Rva0074E990TextureRef m_texture2;                           // +0x120D4
	int m_alphaEdgeHeight;                                      // +0x120D8
	Rva0074E990TextureRef m_texture3;                           // +0x120DC
	int m_drawOriginX;                                          // +0x120E0
	int m_drawOriginY;                                          // +0x120E4
};

// ??0WorldHeightMap@@IAE@XZ
WorldHeightMap::WorldHeightMap(void)
	: m_texture0(), m_texture1(), m_texture2(), m_texture3()
{
	reinterpret_cast<BfmeBigJK *>(this)->bfmeClearJK();
	WorldHeightMap::setupAlphaTiles();
}
