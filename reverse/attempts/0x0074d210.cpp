// ?getAlpha@Rva0074D210Owner@@QAE?AVRva0074D210Handle@@XZ
// partial score=0.92 date=2026-09-02
// cl: /O2 /GX-
// ?getAlphaTerrainTexture@WorldHeightMap@@QAE?AVRva0074D210Handle@@XZ
// ?getEdgeTerrainTexture@WorldHeightMap@@QAE?AVRva0074D210Handle@@XZ

class TextureBaseClass
{
public:
	void Release_Ref();
	int m_unreconstructed_00;
	unsigned short m_numRefs;
};

class Rva0074D210Handle
{
public:
	Rva0074D210Handle(TextureBaseClass *p);
	TextureBaseClass *m_p;
};

inline Rva0074D210Handle::Rva0074D210Handle(TextureBaseClass *p) : m_p(p)
{
	if (m_p)
		++m_p->m_numRefs;
}

class Rva0074D210Owner
{
public:
	Rva0074D210Handle getTerrain();
	Rva0074D210Handle getAlpha();

private:
	char m_pad[0x120CC];
	TextureBaseClass *m_alpha;
};

Rva0074D210Handle Rva0074D210Owner::getAlpha()
{
	volatile int guard = 0;
	if (m_alpha == 0)
	{
		Rva0074D210Handle tmp = getTerrain();
		if (tmp.m_p)
			tmp.m_p->Release_Ref();
	}
	return Rva0074D210Handle(m_alpha);
}

class Rva0074D270Owner
{
public:
	Rva0074D210Handle getTerrain();
	Rva0074D210Handle getEdge();

private:
	char m_pad[0x120D4];
	TextureBaseClass *m_edge;
};

Rva0074D210Handle Rva0074D270Owner::getEdge()
{
	volatile int guard = 0;
	if (m_edge == 0)
	{
		Rva0074D210Handle tmp = getTerrain();
		if (tmp.m_p)
			tmp.m_p->Release_Ref();
	}
	return Rva0074D210Handle(m_edge);
}
