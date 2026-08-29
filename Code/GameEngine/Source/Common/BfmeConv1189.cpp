// Open-BFME5 conversions.

extern "C" char g_bfmeV1189[];

struct BfmeQuad1189
{
	BfmeQuad1189(void)
	{
		m_bfme08 = 0;
		m_bfme04 = 0;
		m_bfme00 = 0;
		m_bfme0c = 0;
	}
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
};

class BfmeBase1189
{
public:
	BfmeBase1189(void) { m_bfme00 = g_bfmeV1189; }
	char *volatile m_bfme00;
};

class BfmeA1189 : public BfmeBase1189
{
public:
	BfmeA1189(void);
	BfmeQuad1189 m_bfme04[8];
	int m_bfme84;
};

BfmeA1189::BfmeA1189(void)
{
	m_bfme84 = 0;
}
