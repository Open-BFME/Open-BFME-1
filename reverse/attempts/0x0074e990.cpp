// ??0WorldHeightMap@@IAE@XZ
// partial score=0.82 date=2026-09-11
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// Open-BFME: WorldHeightMap simple ctor at retail 0x0074E990.
// Layout confirmed against the landed sibling destructor
// Code/GameEngineDevice/Source/W3DDevice/GameClient/Rva0074DE60WorldHeightMapDestructor.cpp
// (0x0074DE60, matched, same vtable 0x01121b94): the eight zero-filled STL
// vectors, the two source/edge tile arrays left untouched, and the two 0x200
// TextureSlot arrays (0x28 stride) at +0x80C0/+0xD0C4 all line up field for
// field. This ctor additionally zeroes the four texture ref pointers at
// +0x120C4/CC/D4/DC that the destructor's own body never reaches.

template <class T>
class Rva0074E990Vector
{
public:
	Rva0074E990Vector(void) : m_start(0), m_finish(0), m_end_of_storage(0) {}

	T *m_start;
	T *m_finish;
	T *m_end_of_storage;
};

struct Rva0074E990BoundaryPoint { int x; int y; };
struct Rva0074E990ElementByte { char m_body[1]; };
struct Rva0074E990Element16 { char m_body[0x10]; };
struct Rva0074E990Element36 { char m_body[0x24]; };

// Forced non-trivial (declared, never defined here) so the compiler emits the
// retail array-with-unwind idiom (call to ??_L) for the two 0x200-element
// slot arrays below; the two callee addresses are pinned in reverse/symbols.csv.
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/WorldHeightMap.h
class WorldHeightMap : public Rva0074E990RefCountClass
{
protected:
	WorldHeightMap();
	virtual ~WorldHeightMap(void);

private:
	int m_width;                                                // +0x08 (untouched)
	int m_height;                                               // +0x0C (untouched)
	int m_borderSize;                                           // +0x10 (untouched)
	Rva0074E990Vector<Rva0074E990BoundaryPoint> m_boundaries;   // +0x14
	int m_dataSize;                                             // +0x20 (untouched)
	unsigned char *m_data;                                      // +0x24 (untouched)
	Rva0074E990Vector<Rva0074E990ElementByte> m_vector28;
	char m_gap34[4];
	Rva0074E990Vector<Rva0074E990ElementByte> m_vector38;
	Rva0074E990Vector<Rva0074E990ElementByte> m_vector44;
	Rva0074E990Vector<Rva0074E990ElementByte> m_vector50;
	Rva0074E990Vector<Rva0074E990ElementByte> m_vector5c;
	Rva0074E990Vector<Rva0074E990ElementByte> m_vector68;
	Rva0074E990Vector<Rva0074E990ElementByte> m_vector74;
	Rva0074E990Vector<Rva0074E990ElementByte> m_vector80;
	unsigned char *m_tileNdxes;                                 // +0x8C (untouched)
	unsigned char *m_blendTileNdxes;                            // +0x90 (untouched)
	unsigned char *m_cliffInfoNdxes;                            // +0x94 (untouched)
	unsigned char *m_extraBlendTileNdxes;                       // +0x98 (untouched)
	char m_gap9c[8];
	void *m_sourceTiles[0x1000];                                // +0xA4 (untouched)
	void *m_edgeTiles[0x1000];                                  // +0x40A4 (untouched)
	Rva0074E990Vector<Rva0074E990Element16> m_vectorA4;
	Rva0074E990Vector<Rva0074E990Element36> m_vectorB0;
	char m_gap80bc[4];
	Rva0074E990TextureSlot m_textureSlotsA[0x200];              // +0x80C0
	char m_gapD0c0[4];
	Rva0074E990TextureSlot m_textureSlotsB[0x200];              // +0xD0C4
	void *m_texture0;                                           // +0x120C4
	int m_terrainTexHeight;                                     // +0x120C8 (untouched)
	void *m_texture1;                                           // +0x120CC
	int m_alphaTexHeight;                                       // +0x120D0 (untouched)
	void *m_texture2;                                           // +0x120D4
	int m_alphaEdgeHeight;                                      // +0x120D8 (untouched)
	void *m_texture3;                                           // +0x120DC
	int m_drawOriginX;                                          // +0x120E0 (untouched)
	int m_drawOriginY;                                          // +0x120E4 (untouched)
};

// ??0WorldHeightMap@@IAE@XZ
WorldHeightMap::WorldHeightMap(void)
	: m_texture0(0), m_texture1(0), m_texture2(0), m_texture3(0)
{
}
