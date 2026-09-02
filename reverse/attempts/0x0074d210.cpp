// ?d_0074d210@@YAXXZ
// partial score=0.92 date=2026-09-02
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
	Rva0074D210Handle();
	Rva0074D210Handle(TextureBaseClass *p);
	TextureBaseClass *m_p;
};

inline Rva0074D210Handle::Rva0074D210Handle() : m_p(0) {}

inline Rva0074D210Handle::Rva0074D210Handle(TextureBaseClass *p) : m_p(p)
{
	if (m_p)
		++m_p->m_numRefs;
}

class Rva0074D210Owner
{
public:
	Rva0074D210Handle getAlpha();
	void getTerrain(Rva0074D210Handle *out);

private:
	char m_pad[0x120CC];
	TextureBaseClass *m_alpha;
};

Rva0074D210Handle Rva0074D210Owner::getAlpha()
{
	Rva0074D210Handle tmp;
	tmp.m_p = 0;
	TextureBaseClass *p = m_alpha;
	if (!p)
	{
		getTerrain(&tmp);
		if (tmp.m_p)
			tmp.m_p->Release_Ref();
	}
	return Rva0074D210Handle(m_alpha);
}
