// Open-BFME5 conversions.

struct BfmeArg1002;

struct BfmeSub1002
{
	char m_bfmePad[0x10];
	int m_bfmeVal;
};

struct BfmeX1002
{
	char m_bfmePad[4];
	BfmeSub1002 *m_bfmeSub;
};

class BfmeA1002
{
public:
	void bfmeGo1002A(BfmeArg1002 *a);
	BfmeX1002 *bfmeFind1002(BfmeArg1002 *a);

	char m_bfmePad[0x1b4];
	int m_bfmeA;
	char m_bfmePad2[4];
	int m_bfmeB;
	char m_bfmePad3[0xc];
	int m_bfmeC;
};

struct BfmeArg1002
{
	char m_bfmePad[0x74];
	int m_bfmeId;
};

void BfmeA1002::bfmeGo1002A(BfmeArg1002 *a)
{
	int id = a->m_bfmeId;

	if (m_bfmeA == id) {
		m_bfmeA = 0;
		return;
	}

	if (m_bfmeB != id)
		return;

	m_bfmeB = 0;

	BfmeX1002 *x = bfmeFind1002(a);

	if (x)
		m_bfmeC = x->m_bfmeSub->m_bfmeVal;
}

class BfmeMid1002
{
public:
	void *bfmeGet1002();
};

struct BfmeVal1002
{
	char m_bfmePad[4];
	BfmeMid1002 *m_bfmeMid;
	char m_bfmePad2[0xcc];
	int m_bfmeFlags;
};

struct BfmeHold1002
{
	char m_bfmePad[4];
	BfmeVal1002 *m_bfmeVal;
};

class BfmeB1002
{
public:
	char bfmeGo1002B(BfmeHold1002 *a, int b);
	char bfmeSend1002(BfmeHold1002 *a, int b);
};

char BfmeB1002::bfmeGo1002B(BfmeHold1002 *a, int b)
{
	BfmeVal1002 *p = a->m_bfmeVal;

	if (p && p->m_bfmeMid)
		p = (BfmeVal1002 *)p->m_bfmeMid->bfmeGet1002();

	if (p->m_bfmeFlags & 0x1000)
		return 0;

	return bfmeSend1002(a, b);
}
