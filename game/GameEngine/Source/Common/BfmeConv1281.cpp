// Open-BFME5 conversions.

class BfmeE1281
{
public:
	void bfmeClose1281();
	BfmeE1281 *m_bfme00;
};

struct BfmeR1281
{
	char m_bfmePad00[0x10];
	BfmeE1281 *m_bfme10;
};

extern "C" void bfmeFree1281(void *p);

class BfmeA1281
{
public:
	void bfmeRemove1281(int i);
	void bfmeNotify1281(int i);
	char m_bfmePad00[0x0c];
	BfmeR1281 *m_bfme0c;
};

void BfmeA1281::bfmeRemove1281(int i)
{
	BfmeE1281 *e;
	BfmeR1281 *r;

	r = &m_bfme0c[i];
	e = r->m_bfme10;
	r->m_bfme10 = e->m_bfme00;
	e->bfmeClose1281();
	bfmeFree1281(e);
	bfmeNotify1281(i);
}
