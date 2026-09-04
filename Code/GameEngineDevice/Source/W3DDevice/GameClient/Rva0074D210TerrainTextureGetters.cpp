// ?getAlpha@Rva0074D210Owner@@QAE?AVRva0074D210Handle@@XZ
// ?getEdge@Rva0074D270Owner@@QAE?AVRva0074D210Handle@@XZ
// cl: /O2 /GX-

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
	TextureBaseClass * volatile m_alpha;
};

Rva0074D210Handle Rva0074D210Owner::getAlpha()
{
	volatile int guard = 0;
	TextureBaseClass *alpha = m_alpha;
	if (alpha == 0)
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
	Rva0074D210Handle getEdge();

private:
	char m_pad[0x120D4];
	TextureBaseClass * volatile m_edge;
};

Rva0074D210Handle Rva0074D270Owner::getEdge()
{
	volatile int guard = 0;
	if (m_edge == 0)
	{
		Rva0074D210Handle tmp = ((Rva0074D210Owner *)this)->getTerrain();
		if (tmp.m_p)
			tmp.m_p->Release_Ref();
	}
	return Rva0074D210Handle(m_edge);
}
