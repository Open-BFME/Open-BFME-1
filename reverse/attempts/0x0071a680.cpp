// ?assignShroudTextureToGlobal@@YAXXZ
// partial score=0.95 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x0071A680. Assign the shroud texture handle to the BFME global
// table and notify the texture stage.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureBaseClass
{
public:
	void Release_Ref();
	char m_vptr[4];
	unsigned short m_refs;
};

class ShroudTextureSource
{
public:
	class Handle
	{
	public:
		Handle(const Handle &other)
		{
			m_p = other.m_p;
			if (other.m_p)
				++other.m_p->m_refs;
		}

		~Handle()
		{
			if (m_p)
				m_p->Release_Ref();
		}

		const Handle &operator=(const Handle &other)
		{
			if (other.m_p)
				++other.m_p->m_refs;
			if (m_p)
				m_p->Release_Ref();
			TextureBaseClass *source = other.m_p;
			m_p = source;
			return *this;
		}

		TextureBaseClass *m_p;
	};

	Handle getTexture() const;
};

class BfmeGlobal_012f7fe0
{
	char m_pad[0x30b8];

public:
	ShroudTextureSource *m_shroud;
};

extern BfmeGlobal_012f7fe0 *TheBfmeGlobal_012f7fe0;
extern ShroudTextureSource::Handle g_bfmeTableDU[];
void bfmeTwoRB(int k, int f);

#pragma comment(linker, "/alternatename:?getTexture@ShroudTextureSource@@QBE?AVHandle@1@XZ=?j_00013bbf@@YAXXZ")

// ?assignShroudTextureToGlobal@@YAXXZ
void assignShroudTextureToGlobal(void)
{
	ShroudTextureSource *shroud = TheBfmeGlobal_012f7fe0->m_shroud;
	if (shroud)
	{
		g_bfmeTableDU[0] = shroud->getTexture();
		bfmeTwoRB(5, 0);
	}
}
