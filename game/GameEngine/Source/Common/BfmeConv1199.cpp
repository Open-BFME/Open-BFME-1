// Open-BFME5 conversions.

extern "C" char g_bfmeVA1199[];
extern "C" char g_bfmeVB1199[];

class BfmeA1199;

extern "C" BfmeA1199 *volatile g_bfmeList1199;

class BfmeBase1199
{
public:
	BfmeBase1199(void)
	{
		m_bfme00 = g_bfmeVA1199;
		m_bfme04 = g_bfmeList1199;
		g_bfmeList1199 = (BfmeA1199 *)this;
		m_bfme0c = 1;
	}
	char *volatile m_bfme00;
	BfmeA1199 *volatile m_bfme04;
	volatile int m_bfme08;
	volatile char m_bfme0c;
	char m_bfmePad[3];
};

class BfmeA1199 : public BfmeBase1199
{
public:
	BfmeA1199(void);
	int m_bfme10[8];
	int m_bfme30[8];
	int m_bfme50[8];
	int m_bfme70[8];
	int m_bfme90[8];
	volatile int m_bfmeb0;
	volatile int m_bfmeb4;
	volatile int m_bfmeb8;
};

BfmeA1199::BfmeA1199(void)
{
	int i;

	m_bfme00 = g_bfmeVB1199;
	m_bfme08 = 0;
	m_bfmeb8 = 0;

	for (i = 0; i < 8; i++) {
		m_bfme10[i] = 0;
		m_bfme30[i] = 0;
		m_bfme50[i] = 0;
		m_bfme70[i] = -1;
		m_bfme90[i] = -1;
	}

	m_bfmeb0 = 0;
	m_bfmeb4 = 0;
}
