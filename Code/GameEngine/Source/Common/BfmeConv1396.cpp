// Open-BFME5 conversions.

class BfmeColorVJZ
{
public:
	void bfmeCopyVJZ(const BfmeColorVJZ &o);
	void bfmeClearVJZ();
	void *m_bfme00;
};

struct BfmeSrcVJZ
{
	char m_bfmePad[0x10];
	BfmeColorVJZ m_bfme10;
};

struct BfmeYVJZ
{
	char m_bfmePad[8];
	int m_bfme08;
};

char __stdcall bfmeGoVJZ(BfmeSrcVJZ *a, BfmeYVJZ *b)
{
	BfmeColorVJZ tmp;
	tmp.bfmeCopyVJZ(a->m_bfme10);
	char r = (b->m_bfme08 <= 0);
	tmp.bfmeClearVJZ();
	return r;
}
