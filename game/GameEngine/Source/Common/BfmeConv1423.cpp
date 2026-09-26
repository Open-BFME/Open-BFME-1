// cl: /Od

extern "C" void *memset(void *d, int c, unsigned n);
#pragma intrinsic(memset)

void bfmeBigFreeVLX(void *p);
void bfmeSmallFreeVLX(void *p, unsigned n);

struct BfmeHdrVLX
{
	unsigned m_bfmeTag : 16;
	unsigned m_bfmeVer : 16;
	unsigned m_bfmeSize;
	unsigned m_bfmePad08;
	unsigned m_bfmePad0c;
};

void bfmeFreeVLX(void *p, unsigned n)
{
	BfmeHdrVLX *n1;
	unsigned n2;
	unsigned n3;

	n1 = (BfmeHdrVLX *)((char *)p - 0x10);
	for (n2 = (unsigned)n1 + 8; n2 < (unsigned)p; ++n2)
	{
	}
	n3 = n + 0x18;
	for (n2 = (unsigned)p + n; n2 < (unsigned)n1 + n3; ++n2)
	{
	}
	n1->m_bfmeTag = 0xdebd;
	memset(p, 0xa3, n);
	if (n3 > 0x80)
		bfmeBigFreeVLX(n1);
	else
		bfmeSmallFreeVLX(n1, n3);
}
