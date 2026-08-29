// Open-BFME5 conversions.

extern "C" void *__cdecl memset(void *d, int c, unsigned int n);

class BfmeA1165
{
public:
	BfmeA1165(int tag, unsigned int a02, unsigned int a03, unsigned int a04, unsigned int a05, unsigned int a06, unsigned int a07, unsigned int a08, unsigned int a09, unsigned int a10, unsigned int a11, unsigned int a12, unsigned int a13, unsigned int a14, unsigned int a15, unsigned int a16);
	unsigned int m_bfme00[10];
};

BfmeA1165::BfmeA1165(int tag, unsigned int a02, unsigned int a03, unsigned int a04, unsigned int a05, unsigned int a06, unsigned int a07, unsigned int a08, unsigned int a09, unsigned int a10, unsigned int a11, unsigned int a12, unsigned int a13, unsigned int a14, unsigned int a15, unsigned int a16)
{
	memset(m_bfme00, 0, 0x28);
	m_bfme00[a02 >> 5] |= 1u << (a02 & 0x1f);
	m_bfme00[a03 >> 5] |= 1u << (a03 & 0x1f);
	m_bfme00[a04 >> 5] |= 1u << (a04 & 0x1f);
	m_bfme00[a05 >> 5] |= 1u << (a05 & 0x1f);
	m_bfme00[a06 >> 5] |= 1u << (a06 & 0x1f);
	m_bfme00[a07 >> 5] |= 1u << (a07 & 0x1f);
	m_bfme00[a08 >> 5] |= 1u << (a08 & 0x1f);
	m_bfme00[a09 >> 5] |= 1u << (a09 & 0x1f);
	m_bfme00[a10 >> 5] |= 1u << (a10 & 0x1f);
	m_bfme00[a11 >> 5] |= 1u << (a11 & 0x1f);
	m_bfme00[a12 >> 5] |= 1u << (a12 & 0x1f);
	m_bfme00[a13 >> 5] |= 1u << (a13 & 0x1f);
	m_bfme00[a14 >> 5] |= 1u << (a14 & 0x1f);
	m_bfme00[a15 >> 5] |= 1u << (a15 & 0x1f);
	m_bfme00[a16 >> 5] |= 1u << (a16 & 0x1f);
}
