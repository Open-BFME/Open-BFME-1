// Open-BFME5 conversions.

extern "C" void *__cdecl memset(void *d, int c, unsigned int n);

class BfmeA1163
{
public:
	BfmeA1163(void);
	float m_bfme00;
	float m_bfme04;
	int m_bfme08[10];
};

BfmeA1163::BfmeA1163(void)
{
	m_bfme00 = 0.0f;
	m_bfme04 = 0.0f;
	memset(m_bfme08, 0, 0x28);
}
