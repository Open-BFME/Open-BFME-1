// Open-BFME5 conversions.

extern "C" void *__cdecl memset(void *d, int c, unsigned int n);

class BfmeA1157
{
public:
	BfmeA1157(void);
	int m_bfme00;
	char m_bfmePad[0xc];
	int m_bfme10;
	int m_bfme14;
	int m_bfme18;
	int m_bfme1c[10];
	int m_bfme44[10];
};

BfmeA1157::BfmeA1157(void)
{
	m_bfme00 = 0;
	m_bfme10 = 0;
	m_bfme14 = 0;
	m_bfme18 = 0;
	memset(m_bfme1c, 0, 0x28);
	memset(m_bfme44, 0, 0x28);
}
