// Open-BFME5 conversions.

struct BfmeBits1186
{
	volatile int m_bfme00;
	volatile int m_bfme04;
	volatile int m_bfme08;
	volatile int m_bfme0c;
	volatile int m_bfme10;
	unsigned char *volatile m_bfme14;
};

void bfmeInit1186(BfmeBits1186 *s, unsigned char *p)
{
	s->m_bfme10 = 0;
	s->m_bfme00 = 0;
	s->m_bfme04 = 0xff;
	s->m_bfme0c = 8;
	s->m_bfme14 = p;
	s->m_bfme08 = ((((p[0] << 8) + p[1]) << 8) + p[2]) * 256 + p[3];
	s->m_bfme10 = 4;
}
