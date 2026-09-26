// Open-BFME5 conversions.

struct BfmeX987
{
	char m_bfmePad[0x74];
	int m_bfmeId;
};

class BfmeLook987
{
public:
	BfmeX987 *bfmeFind987(int id);
};

extern BfmeLook987 *g_bfmeLook987;

class BfmeA987
{
public:
	void bfmeGo987A();
	void bfmeGo987B();
	void bfmeBase987();

	char m_bfmePad[0x20];
	int m_bfmeId;
};

void BfmeA987::bfmeGo987A()
{
	bfmeBase987();

	BfmeX987 *x = g_bfmeLook987->bfmeFind987(m_bfmeId);

	if (x) {
		m_bfmeId = x->m_bfmeId;
		return;
	}

	m_bfmeId = 0;
}

void BfmeA987::bfmeGo987B()
{
	bfmeBase987();

	BfmeX987 *x = g_bfmeLook987->bfmeFind987(m_bfmeId);

	if (x) {
		m_bfmeId = x->m_bfmeId;
		return;
	}

	m_bfmeId = 0;
}

class BfmeDrop987
{
public:
	void bfmeClear987(int a, int b);
};

class BfmeC987
{
public:
	void bfmeGo987C();

	char m_bfmePad[0x24];
	int m_bfmeId;
};

void BfmeC987::bfmeGo987C()
{
	BfmeDrop987 *x = (BfmeDrop987 *)g_bfmeLook987->bfmeFind987(m_bfmeId);

	if (x) {
		x->bfmeClear987(8, 0);
		m_bfmeId = 0;
	}
}

class BfmeD987
{
public:
	void bfmeGo987D(int unused);

	char m_bfmePad[4];
	int m_bfmeId;
};

void BfmeD987::bfmeGo987D(int unused)
{
	BfmeDrop987 *x = (BfmeDrop987 *)g_bfmeLook987->bfmeFind987(m_bfmeId);

	if (x) {
		x->bfmeClear987(8, 0);
		m_bfmeId = 0;
	}
}
