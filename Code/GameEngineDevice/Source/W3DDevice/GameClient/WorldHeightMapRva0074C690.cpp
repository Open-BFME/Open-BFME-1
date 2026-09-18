// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class TextureBaseClass
{
public:
	void Release_Ref(void);
};

class BfmeHandleCX
{
public:
	BfmeHandleCX(TextureBaseClass *texture) : m_texture(texture)
	{
		if (m_texture)
			++*(unsigned short *)((char *)m_texture + 4);
	}

	~BfmeHandleCX(void)
	{
	}

	TextureBaseClass *m_texture;
};

class TileData;

class Rva006D5280
{
public:
	Rva006D5280(unsigned, unsigned, unsigned);
	void update(TileData **, int, int, int);

	~Rva006D5280(void)
	{
		if (m_texture)
			m_texture->Release_Ref();
	}

	TextureBaseClass *m_texture;
};

__forceinline static void bfmeAssignTextureHandle(TextureBaseClass *&destination,
	const Rva006D5280 &source)
{
	if (source.m_texture)
		++*(unsigned short *)((char *)source.m_texture + 4);
	if (destination)
		destination->Release_Ref();
	destination = source.m_texture;
}

#pragma comment(linker, "/alternatename:?update@Rva006D5280@@QAEXPAPAVTileData@@HHH@Z=?j_0002279b@@YAXXZ")

struct Rva0074C690Element36
{
	char m_body[0x22];
	short m_height;
};

template <class T>
class Rva0074C690Vector
{
public:
	unsigned size(void) const
	{
		T *start = begin();
		return (unsigned)(m_finish - start);
	}

	T *begin(void) const
	{
		return m_start;
	}

	T *m_start;
	T *m_finish;
	T *m_end;
};

struct Rva0074C690TextureSlot
{
	int m_unused;
	int m_firstTile;
	int m_tileCount;
	int m_textureSize;
	char m_body[0x18];
};

class WorldHeightMap
{
public:
	BfmeHandleCX rva0074C690(int, int, int);

private:
	char m_body[0xa4];
	TileData *m_sourceTiles[0x1000];
	char m_gap40A4[0x400c];
	Rva0074C690Vector<Rva0074C690Element36> m_vectorB0;
	int m_numTextureSlots;
	Rva0074C690TextureSlot m_textureSlotsA[0x200];
	char m_gapD0C0[4];
	Rva0074C690TextureSlot m_textureSlotsB[0x200];
	BfmeHandleCX m_texture0;
	int m_texture0Height;
	BfmeHandleCX m_texture1;
	int m_texture1Height;
	BfmeHandleCX m_texture2;
	int m_texture2Height;
	BfmeHandleCX m_texture3;
};

BfmeHandleCX WorldHeightMap::rva0074C690(int, int, int)
{
	volatile int state;
	state = 0;
	_ReadWriteBarrier();
	if (m_texture3.m_texture)
		return BfmeHandleCX(m_texture3.m_texture);

	if (m_vectorB0.size() < 2)
		return BfmeHandleCX((TextureBaseClass *)0);

	{
		Rva0074C690Element36 *records = m_vectorB0.begin();
		int tileIndex;
		tileIndex = records[1].m_height;
		tileIndex >>= 2;
		int slotCount;
		slotCount = m_numTextureSlots;
		int slot = 0;
		for (; slot < slotCount; ++slot)
		{
			if (tileIndex >= m_textureSlotsA[slot].m_firstTile &&
				tileIndex < m_textureSlotsA[slot].m_firstTile +
				m_textureSlotsA[slot].m_tileCount)
				goto haveTextureSlot;
		}
		return BfmeHandleCX((TextureBaseClass *)0);

	haveTextureSlot:
		{
			int textureSize = m_textureSlotsA[slot].m_textureSize << 6;
			Rva006D5280 texture(textureSize, textureSize, 0x19);
			texture.update(m_sourceTiles, m_textureSlotsA[slot].m_firstTile,
				m_textureSlotsA[slot].m_tileCount,
				m_textureSlotsA[slot].m_textureSize);

			bfmeAssignTextureHandle(m_texture3.m_texture, texture);
			return BfmeHandleCX(m_texture3.m_texture);
		}
	}
	return BfmeHandleCX((TextureBaseClass *)0);
}
