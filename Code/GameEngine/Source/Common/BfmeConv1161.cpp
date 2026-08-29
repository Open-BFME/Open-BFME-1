// Open-BFME5 conversions.

extern "C" void *__cdecl memset(void *d, int c, unsigned int n);

class BfmeA1161
{
public:
	BfmeA1161(void);
	float m_bfme00;
	float m_bfme04;
	int m_bfme08[10];
	int m_bfme30[10];
};

BfmeA1161::BfmeA1161(void)
{
	m_bfme00 = 0.0f;
	m_bfme04 = 0.0f;
	memset(m_bfme08, 0, 0x28);
	memset(m_bfme30, 0, 0x28);
}
