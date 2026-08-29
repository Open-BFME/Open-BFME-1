// Open-BFME5 conversions.

extern "C" char g_bfmeV1196[];

struct BfmeSrc1196
{
	char m_bfmePad0[0x38];
	int m_bfme38;
	int m_bfme3c;
	int m_bfme40;
	char m_bfmePad1[0x78];
	float m_bfmebc;
};

struct BfmeG1196
{
	char m_bfmePad[0x1bc];
	float m_bfme1bc;
};

extern "C" BfmeG1196 *volatile g_bfmeG1196;

class BfmeA1196
{
public:
	BfmeA1196(BfmeSrc1196 *a, char b);
	char *volatile m_bfme00;
	volatile int m_bfme04;
	volatile int m_bfme08;
	volatile int m_bfme0c;
	volatile int m_bfme10;
	volatile float m_bfme14;
	volatile char m_bfme18;
};

BfmeA1196::BfmeA1196(BfmeSrc1196 *a, char b)
{
	float v;

	m_bfme04 = 0;
	m_bfme00 = g_bfmeV1196;
	m_bfme08 = a->m_bfme38;
	m_bfme0c = a->m_bfme3c;
	m_bfme10 = a->m_bfme40;
	m_bfme18 = b;

	v = a->m_bfmebc;
	m_bfme14 = v;
	m_bfme14 = g_bfmeG1196->m_bfme1bc * 0.70710677f + v;
}
