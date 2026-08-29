// Open-BFME5 conversions.

extern "C" char g_bfmeV1188[];

struct BfmePair1188
{
	BfmePair1188(void)
	{
		m_bfme00 = 0;
		m_bfme04 = 0;
	}
	int m_bfme00;
	int m_bfme04;
};

class BfmeBase1188
{
public:
	BfmeBase1188(void) { m_bfme00 = g_bfmeV1188; }
	char *volatile m_bfme00;
};

class BfmeA1188 : public BfmeBase1188
{
public:
	BfmeA1188(void);
	BfmePair1188 m_bfme04[8];
};

BfmeA1188::BfmeA1188(void)
{
}
