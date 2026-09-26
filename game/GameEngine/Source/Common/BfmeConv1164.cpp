// Open-BFME5 conversions.

extern "C" void *__cdecl memset(void *d, int c, unsigned int n);

class BfmeA1164
{
public:
	BfmeA1164(void);
	char m_bfmePad[0x14];
	int m_bfme14[6];
	int m_bfme2c[6];
};

BfmeA1164::BfmeA1164(void)
{
	memset(m_bfme14, 0, 0x18);
	memset(m_bfme2c, 0, 0x18);
}
