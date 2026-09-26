// Open-BFME5 conversions.

void __cdecl operator delete(void *p);

class BfmeThingVIH;

class BfmeSubVIH
{
public:
	void bfmeDropVIH(BfmeThingVIH *o);
};

extern int g_bfmeVftVIH[];

class BfmeThingVIH
{
public:
	void *bfmeDelVIH(unsigned flags);
	void *m_bfmeVfptr;
	char m_bfmePad[8];
	BfmeSubVIH *m_bfme0c;
};

void *BfmeThingVIH::bfmeDelVIH(unsigned flags)
{
	m_bfmeVfptr = g_bfmeVftVIH;
	if (m_bfme0c)
		m_bfme0c->bfmeDropVIH(this);
	if (flags & 1)
		operator delete(this);
	return this;
}
