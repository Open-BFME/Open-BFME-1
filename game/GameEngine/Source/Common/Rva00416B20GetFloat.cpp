// cl: /O2 /Ob0

class BfmeOverridable
{
public:
	BfmeOverridable *friend_getFinalOverride();

	char m_vptr[4];
	BfmeOverridable *m_nextOverride;
};

struct Rva00416B20Head
{
	char m_pad[0x108];
	char *m_108;
};

class Rva00416B20Sub
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s44(); virtual void s45(); virtual void s46();
	virtual float extra();
};

class Rva00416B20
{
	int m_00;
	BfmeOverridable *m_04;
	char m_pad[0xF4];
	Rva00416B20Head *m_fc;
	char m_pad2[0x50];
	Rva00416B20Sub **m_150;

public:
	float get();
};

struct Rva00416B20Chunk
{
	char m_pad[0x14];
	float m_14;
};

float Rva00416B20::get()
{
	char *p;
	if (m_fc)
		p = m_fc->m_108;
	else
	{
		BfmeOverridable *o = m_04;
		if (o && o->m_nextOverride)
			o = o->m_nextOverride->friend_getFinalOverride();
		p = (char *)o + 0x60;
	}
	float f = ((Rva00416B20Chunk *)p)->m_14;
	Rva00416B20Sub **pp = m_150;
	if (pp)
	{
		Rva00416B20Sub *s = *pp;
		if (s)
			f += s->extra();
	}
	return f;
}
