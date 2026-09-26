// Open-BFME5 conversions: flat constructors.

static void bfme5ZeroFour(int *p)
{
	p[0] = 0;
	p[1] = 0;
	p[2] = 0;
	p[3] = 0;
}

class Bfme5CtorA0
{
public:
	Bfme5CtorA0(void);
	virtual ~Bfme5CtorA0();

	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
	int m_bfme18;
	int m_bfme1c;
	int m_bfme20;
	char m_bfme24;
	char m_bfmePad[3];
	int m_bfme28;
};

Bfme5CtorA0::Bfme5CtorA0(void)
{
	bfme5ZeroFour(&m_bfme04);
	m_bfme14 = 0;
	m_bfme18 = -1;
	m_bfme1c = 0;
	m_bfme20 = -1;
	m_bfme24 = 0;
	m_bfme28 = 0;
}
