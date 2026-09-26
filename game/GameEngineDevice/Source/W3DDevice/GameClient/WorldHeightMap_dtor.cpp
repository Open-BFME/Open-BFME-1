// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// Open-BFME5: BFME WorldHeightMap destructor at retail 0x0074DE60.
// The member offsets are the witnessed BFME layout, not the older ZH class
// declaration: the interface base is absent, the two 0x200 texture arrays
// are in-object, and the source/edge tile arrays begin at +0xA4/+0x40A4.

extern void __cdecl operator delete(void *);
extern void __cdecl operator delete[](void *);

namespace _STL
{
template <bool threads, int instance>
class __node_alloc
{
public:
	static void _M_deallocate(void *, unsigned int);
};
}

class TextureClass
{
public:
	void Release_Ref(void);
};

class Rva0074DE60TextureRef
{
public:
	~Rva0074DE60TextureRef(void)
	{
		if (m_ptr != 0)
			m_ptr->Release_Ref();
	}

	TextureClass *m_ptr;
};

class Rva0074DE60TileData
{
public:
	virtual void Delete_This(void);

	void Release_Ref(void)
	{
		if (--NumRefs == 0)
			Delete_This();
	}

	int NumRefs;
};

struct Rva0074DE60BoundaryPoint
{
	int x;
	int y;
};

struct Rva0074DE60Element16
{
	char m_body[0x10];
};

struct Rva0074DE60ElementByte
{
	char m_body[1];
};

struct Rva0074DE60Element36
{
	char m_body[0x24];
};

template <class T>
class Rva0074DE60Vector
{
public:
	~Rva0074DE60Vector(void)
	{
		if (m_start != 0)
		{
			unsigned int bytes =
				(unsigned int)(m_end_of_storage - m_start) * sizeof(T);
			if (bytes > 0x80)
				::operator delete(m_start);
			else
				_STL::__node_alloc<true, 0>::_M_deallocate(m_start, bytes);
		}
	}

	T *m_start;
	T *m_finish;
	T *m_end_of_storage;
};

// The destructor address passed to __ehvec_dtor is the retail helper
// ?j_00041b32@@YAXXZ (ILT 0x00041B32 -> 0x00749770).  Its element identity is
// not otherwise named here; the 0x28 stride and two 0x200 counts are witnessed.
class Rva0074DE60TextureSlot
{
public:
	~Rva0074DE60TextureSlot(void);

private:
	char m_body[0x28];
};

class Rva0074DE60RefCountClass
{
public:
	virtual void Delete_This(void);

protected:
	virtual ~Rva0074DE60RefCountClass(void) {}

private:
	int NumRefs;
};

class Rva0074DE60WorldHeightMap : public Rva0074DE60RefCountClass
{
public:
	virtual ~Rva0074DE60WorldHeightMap(void);

private:
	int m_width;                                             // +0x08
	int m_height;                                            // +0x0C
	int m_borderSize;                                        // +0x10
	Rva0074DE60Vector<Rva0074DE60BoundaryPoint> m_boundaries; // +0x14
	int m_dataSize;                                          // +0x20
	unsigned char *m_data;                                   // +0x24
	Rva0074DE60Vector<Rva0074DE60ElementByte> m_vector28;    // +0x28
	char m_gap34[4];                                         // +0x34
	Rva0074DE60Vector<Rva0074DE60ElementByte> m_vector38;    // +0x38
	Rva0074DE60Vector<Rva0074DE60ElementByte> m_vector44;    // +0x44
	Rva0074DE60Vector<Rva0074DE60ElementByte> m_vector50;    // +0x50
	Rva0074DE60Vector<Rva0074DE60ElementByte> m_vector5c;    // +0x5C
	Rva0074DE60Vector<Rva0074DE60ElementByte> m_vector68;    // +0x68
	Rva0074DE60Vector<Rva0074DE60ElementByte> m_vector74;    // +0x74
	Rva0074DE60Vector<Rva0074DE60ElementByte> m_vector80;    // +0x80
	unsigned char *m_tileNdxes;                              // +0x8C
	unsigned char *m_blendTileNdxes;                        // +0x90
	unsigned char *m_cliffInfoNdxes;                        // +0x94
	unsigned char *m_extraBlendTileNdxes;                   // +0x98
	char m_gap9c[8];                                         // +0x9C
	Rva0074DE60TileData *m_sourceTiles[0x1000];              // +0xA4
	Rva0074DE60TileData *m_edgeTiles[0x1000];                // +0x40A4
	Rva0074DE60Vector<Rva0074DE60Element16> m_vectorA4;      // +0x80A4
	Rva0074DE60Vector<Rva0074DE60Element36> m_vectorB0;      // +0x80B0
	char m_gap80bc[4];                                       // +0x80BC
	Rva0074DE60TextureSlot m_textureSlotsA[0x200];           // +0x80C0
	char m_gapD0c0[4];                                       // +0xD0C0
	Rva0074DE60TextureSlot m_textureSlotsB[0x200];           // +0xD0C4
	Rva0074DE60TextureRef m_texture0;                        // +0x120C4
	int m_terrainTexHeight;                                  // +0x120C8
	Rva0074DE60TextureRef m_texture1;                        // +0x120CC
	int m_alphaTexHeight;                                    // +0x120D0
	Rva0074DE60TextureRef m_texture2;                        // +0x120D4
	int m_alphaEdgeHeight;                                   // +0x120D8
	Rva0074DE60TextureRef m_texture3;                        // +0x120DC
	int m_drawOriginX;                                       // +0x120E0
	int m_drawOriginY;                                       // +0x120E4
};

// ??1WorldHeightMap@@UAE@XZ
Rva0074DE60WorldHeightMap::~Rva0074DE60WorldHeightMap(void)
{
	{
		unsigned char *p = m_data;
		::operator delete[](p);
	}
	{
		unsigned char *p = m_tileNdxes;
		::operator delete[](p);
	}
	{
		unsigned char *p = m_blendTileNdxes;
		::operator delete[](p);
	}
	{
		unsigned char *p = m_extraBlendTileNdxes;
		::operator delete[](p);
	}
	{
		unsigned char *p = m_cliffInfoNdxes;
		::operator delete[](p);
	}

	for (int i = 0; i < 0x1000; ++i)
	{
		if (m_sourceTiles[i] != 0)
		{
			m_sourceTiles[i]->Release_Ref();
			m_sourceTiles[i] = 0;
		}
		if (m_edgeTiles[i] != 0)
		{
			m_edgeTiles[i]->Release_Ref();
			m_edgeTiles[i] = 0;
		}
	}

	for (int alphaAddress = 0x01301E30;
		alphaAddress < 0x01301E60; alphaAddress += 4)
	{
		Rva0074DE60TileData **p =
			(Rva0074DE60TileData **)alphaAddress;
		if (*p != 0)
		{
			(*p)->Release_Ref();
			*p = 0;
		}
	}

}
