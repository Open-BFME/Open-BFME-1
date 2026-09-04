// Open-BFME5 conversions.

extern char g_bfmeVft994C[];

class BfmeC994
{
public:
	BfmeC994(char *a, int b);
	void bfmeBase994C();

	char *volatile m_bfmeVft;
	volatile int m_bfme04;
	volatile int m_bfme08;
	volatile int m_bfme0c;
	char *volatile m_bfme10;
	volatile int m_bfme14;
	volatile int m_bfme18;
	volatile int m_bfme1c;
	volatile int m_bfme20;
	volatile int m_bfme24;
	volatile int m_bfme28;
	volatile int m_bfme2c;
	volatile char m_bfme30;
};

BfmeC994::BfmeC994(char *a, int b)
{
	bfmeBase994C();

	m_bfmeVft = g_bfmeVft994C;
	m_bfme08 = 0;
	m_bfme0c = 0;
	m_bfme04 = 0;
	m_bfme10 = a;
	m_bfme14 = b;
	m_bfme18 = 0;
	m_bfme28 = 0;
	m_bfme24 = 0;
	m_bfme20 = 0;
	m_bfme1c = 0;

	if (a)
		*a = 0;

	m_bfme30 = 0;
	m_bfme2c = 4;
}
