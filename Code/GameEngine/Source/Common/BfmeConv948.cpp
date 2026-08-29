// Open-BFME5 conversions.

class BfmeClamp948A
{
public:
	int bfmeGo948A(int a, int sel);
	char m_bfmePad[0x18];
	int m_bfmeCur;
	int m_bfmeMax;
};

int BfmeClamp948A::bfmeGo948A(int a, int sel)
{
	int v;
	switch (sel) {
	case 2:
		v = m_bfmeMax + a;
		break;
	case 1:
		v = m_bfmeCur + a;
		break;
	case 0:
		v = a;
		break;
	default:
		return -1;
	}
	if (v < 0)
		v = 0;
	else if (v > m_bfmeMax)
		v = m_bfmeMax;
	m_bfmeCur = v;
	return v;
}

class BfmeClamp948B
{
public:
	int bfmeGo948B(int a, int sel);
	char m_bfmePad[0x1c];
	int m_bfmeMax;
	char m_bfmePad2[8];
	int m_bfmeCur;
};

int BfmeClamp948B::bfmeGo948B(int a, int sel)
{
	int v;
	switch (sel) {
	case 2:
		v = m_bfmeMax + a;
		break;
	case 1:
		v = m_bfmeCur + a;
		break;
	case 0:
		v = a;
		break;
	default:
		return -1;
	}
	if (v < 0)
		v = 0;
	else if (v > m_bfmeMax)
		v = m_bfmeMax;
	m_bfmeCur = v;
	return v;
}

struct BfmeDim948
{
	char m_bfmePad[8];
	int m_bfmeW;
	int m_bfmeH;
};

class BfmeGrid948C
{
public:
	bool bfmeGet948C(int i);
	int m_bfmeData;
};

class BfmeMap948C
{
public:
	bool bfmeGo948C(int x, int y);
	char m_bfmePad[0x2ff4];
	BfmeDim948 *m_bfmeDim;
	char m_bfmePad2[0x28];
	BfmeGrid948C m_bfmeGrid;
};

bool BfmeMap948C::bfmeGo948C(int x, int y)
{
	BfmeDim948 *d = m_bfmeDim;
	int w = d->m_bfmeW;
	if (x >= 0 && y >= 0 && y < d->m_bfmeH && x < w)
		return m_bfmeGrid.bfmeGet948C(w * y + x);
	return false;
}

class BfmeGrid948D
{
public:
	bool bfmeGet948D(int i);
	int m_bfmeData;
};

class BfmeMap948D
{
public:
	bool bfmeGo948D(int x, int y);
	char m_bfmePad[0x2ff4];
	BfmeDim948 *m_bfmeDim;
	char m_bfmePad2[0x3c];
	BfmeGrid948D m_bfmeGrid;
};

bool BfmeMap948D::bfmeGo948D(int x, int y)
{
	BfmeDim948 *d = m_bfmeDim;
	int w = d->m_bfmeW;
	if (x >= 0 && y >= 0 && y < d->m_bfmeH && x < w)
		return m_bfmeGrid.bfmeGet948D(w * y + x);
	return false;
}
