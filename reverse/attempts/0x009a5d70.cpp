// ?bfmeInitD70@@YAXPAX0@Z
// partial score=0.7 date=2026-09-02
// cl: /DNDEBUG /MD /O2

struct BfmeBlock14
{
	int m_word[14];
};

struct BfmeHolderD70
{
	unsigned char m_lead[0x40];
	unsigned int m_at40;
	unsigned int m_at44;
	unsigned int m_at48;
	unsigned int m_at4C;
	unsigned char m_gap[0x78 - 0x50];
	unsigned int m_at78;
	unsigned int m_at7C;
	unsigned int m_at80;
	unsigned int m_at84;
	unsigned int m_at88;
	unsigned int m_at8C;
	unsigned int m_at90;
	unsigned int m_at94;
	unsigned int m_at98;
	unsigned int m_at9C;
	unsigned char m_gap2[0xB4 - 0xA0];
	unsigned int m_atB4;
};

// ?bfmeInitD70@@YAXPAX0@Z
void __cdecl bfmeInitD70(void *self, void *src)
{
	BfmeHolderD70 *dst = (BfmeHolderD70 *)self;

	*(BfmeBlock14 *)((unsigned char *)dst + 0x40) = *(BfmeBlock14 *)src;

	unsigned int a = dst->m_at40 >> 3;
	unsigned int b = dst->m_at44 >> 3;
	unsigned int c = dst->m_at48;

	dst->m_at94 = b;
	unsigned int d;
	unsigned int ab = b * a;
	unsigned int hold = ab;
	dst->m_at84 = ab;
	d = dst->m_at4C;
	unsigned int ab4 = hold >> 2;
	dst->m_at8C = ab + ab4 * 2;
	dst->m_at90 = a;

	unsigned int e = (c - (a * 8)) >> 1;
	dst->m_at78 = (c + 1) * e;
	unsigned int f = (dst->m_at44 + e * 2) * c;
	dst->m_at98 = c;

	unsigned int e2 = e >> 1;
	unsigned int g = ((dst->m_at44 >> 1) + e) * d;
	dst->m_atB4 = e;
	dst->m_at88 = ab4;
	dst->m_at7C = (d + 1) * e2 + f;
	dst->m_at9C = d;
	dst->m_at80 = e2 * d + g + e2 + f;
}
