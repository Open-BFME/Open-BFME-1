// Open-BFME5 conversions.

extern "C" char g_bfmeV1187[];

struct BfmePair1187
{
	BfmePair1187(void)
	{
		m_bfme00 = 0;
		m_bfme04 = 0;
	}
	int m_bfme00;
	int m_bfme04;
};

class BfmeBase1187
{
public:
	BfmeBase1187(void) { m_bfme00 = g_bfmeV1187; }
	char *volatile m_bfme00;
	volatile int m_bfme04;
};

class BfmeA1187 : public BfmeBase1187
{
public:
	BfmeA1187(void);
	BfmePair1187 m_bfme08[8];
};

BfmeA1187::BfmeA1187(void)
{
	m_bfme04 = 0;
}
