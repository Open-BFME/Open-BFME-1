// Open-BFME5 conversions.

struct BfmeNodeVLI
{
	char m_bfmePad[0x14];
	const void *m_bfme14;
};

class BfmeMapVLI
{
public:
	BfmeNodeVLI *bfmeFindVLI(unsigned short *k);
	BfmeNodeVLI *m_bfme00;
};

class BfmeFontVLI
{
public:
	const void *bfmeGetCharVLI(unsigned short ch);
	const void *bfmeLoadVLI(unsigned short ch);
	char m_bfmePad00[8];
	BfmeFontVLI *m_bfme08;
	char m_bfmePad0c[0x444];
	BfmeMapVLI m_bfme450;
};

const void *BfmeFontVLI::bfmeGetCharVLI(unsigned short ch)
{
	unsigned short c = ch;
	BfmeFontVLI *f = this;
	for (;;)
	{
		BfmeMapVLI *m = &f->m_bfme450;
		const void *r;
		BfmeNodeVLI *n = m->bfmeFindVLI(&ch);
		if (n == m->m_bfme00 || (r = n->m_bfme14) == 0)
			r = f->bfmeLoadVLI(c);
		if (r != (const void *)-1)
			return r;
		BfmeFontVLI *nx = f->m_bfme08;
		if (nx == 0 || f == nx)
			return 0;
		f = nx;
	}
}
