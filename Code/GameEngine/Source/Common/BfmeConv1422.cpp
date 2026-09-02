// cl: /Od

extern "C" void *memset(void *d, int c, unsigned n);
#pragma intrinsic(memset)

void *bfmeBigVLW(unsigned n);
void *bfmeSmallVLW(unsigned n);

struct BfmeHdrVLW
{
	unsigned m_bfmeTag : 16;
	unsigned m_bfmeVer : 16;
	unsigned m_bfmeSize;
	unsigned m_bfmePad08;
	unsigned m_bfmePad0c;
};

void *bfmeAllocVLW(unsigned n)
{
	BfmeHdrVLW *n1;
	unsigned n3;
	unsigned n2;

	n3 = n + 0x18;
	if (n3 > 0x80)
		n2 = (unsigned)bfmeBigVLW(n3);
	else
		n2 = (unsigned)bfmeSmallVLW(n3);
	n1 = (BfmeHdrVLW *)n2;
	memset(n1, 0xa3, n3);
	n1->m_bfmeTag = 0xdeba;
	n1->m_bfmeVer = 1;
	n1->m_bfmeSize = n;
	return n1 + 1;
}
