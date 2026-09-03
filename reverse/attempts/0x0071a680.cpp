// ?assignShroudTextureToGlobal@@YAXXZ
// partial score=0.95 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x0071A680. Pulls the +0x30B8 shroud object's texture handle and
// assigns it onto g_bfmeTableDU, then bfmeTwoRB(5, 0).

class TextureBaseClass
{
public:
	void Release_Ref();
	char m_vptr[4];
	unsigned short m_refs;
};

class BfmeHandleCX
{
public:
	BfmeHandleCX(const BfmeHandleCX &other)
	{
		m_p = other.m_p;
		if (other.m_p)
			++other.m_p->m_refs;
	}

	~BfmeHandleCX()
	{
		if (m_p)
			m_p->Release_Ref();
	}

	BfmeHandleCX &operator=(const BfmeHandleCX &other)
	{
		if (other.m_p)
			++other.m_p->m_refs;
		if (m_p)
			m_p->Release_Ref();
		m_p = other.m_p;
		return *this;
	}

	TextureBaseClass *m_p;
};

class ShroudTextureSource
{
public:
	BfmeHandleCX getTexture() const;
};

class BfmeGlobal_012f7fe0
{
	char m_pad[0x30b8];

public:
	ShroudTextureSource *m_shroud;
};

extern BfmeGlobal_012f7fe0 *TheBfmeGlobal_012f7fe0;
extern BfmeHandleCX g_bfmeTableDU;
void bfmeTwoRB(int k, int f);

#pragma comment(linker, "/alternatename:?getTexture@ShroudTextureSource@@QBE?AVBfmeHandleCX@@XZ=?j_00013bbf@@YAXXZ")

void assignShroudTextureToGlobal(void)
{
	ShroudTextureSource *shroud = TheBfmeGlobal_012f7fe0->m_shroud;
	if (shroud)
	{
		g_bfmeTableDU = shroud->getTexture();
		bfmeTwoRB(5, 0);
	}
}
