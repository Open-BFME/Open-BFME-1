// Open-BFME5 conversions.

class BfmeChunkUQB
{
public:
	unsigned bfmeWriteUQB(void *p, unsigned n);
};

char __stdcall bfmeGoUQB(BfmeChunkUQB *c, void *p)
{
	char r = 0;
	if (c->bfmeWriteUQB(p, 0x40) == 0x40)
		r = 1;
	return r;
}

void *bfmeAllocUQC(unsigned n);

inline void *operator new(unsigned, void *p) { return p; }

struct BfmeNodeUQC
{
	void *m_bfmeNext;
	void *m_bfmePrev;
	unsigned short m_bfmeValue;
};

BfmeNodeUQC *__stdcall bfmeGoUQC(const unsigned short *v)
{
	BfmeNodeUQC *n = (BfmeNodeUQC *)bfmeAllocUQC(0xc);
	new ((void *)&n->m_bfmeValue) unsigned short(*v);
	return n;
}
