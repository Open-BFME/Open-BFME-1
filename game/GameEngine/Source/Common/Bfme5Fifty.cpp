// Four more: a flush whose count comes out of the same pointer twice, two
// block-iterator steps, and a constructor that copies a quad.

class BfmePairDT
{
public:
	int m_bfmeFirst;					// +0x00
	int m_bfmeSecond;					// +0x04
};

class Gen_0060CF20
{
public:
	void bfmeFlush(void);

private:
	char m_bfmeHead[0x3C];					// +0x00
	BfmePairDT *m_bfmeBase;					// +0x3C
	BfmePairDT *m_bfmeCursor;				// +0x40
};

// ?bfmeFlush@Gen_0060CF20@@QAEXXZ
void Gen_0060CF20::bfmeFlush(void)
{
	BfmePairDT *source = m_bfmeCursor;
	BfmePairDT *destination = m_bfmeBase;

	int count = m_bfmeCursor - source;

	if (count > 0)
	{
		do
		{
			*destination = *source;

			++source;
			++destination;
		}
		while (--count != 0);
	}

	m_bfmeCursor = destination;
}

class Gen_00643990
{
public:
	void bfmeAdvance(void);

private:
	char *m_bfmeCurrent;					// +0x00
	char *m_bfmeFirst;					// +0x04
	char *m_bfmeLast;					// +0x08
	char **m_bfmeNode;					// +0x0C
};

// ?bfmeAdvance@Gen_00643990@@QAEXXZ
void Gen_00643990::bfmeAdvance(void)
{
	m_bfmeCurrent = m_bfmeCurrent + 0x330;

	if (m_bfmeCurrent == m_bfmeLast)
	{
		m_bfmeNode = m_bfmeNode + 1;

		m_bfmeFirst = *m_bfmeNode;
		m_bfmeLast = m_bfmeFirst + 0x330;

		m_bfmeCurrent = m_bfmeFirst;
	}
}

class Gen_00651FA0
{
public:
	void bfmeAdvance(void);

private:
	char *m_bfmeCurrent;					// +0x00
	char *m_bfmeFirst;					// +0x04
	char *m_bfmeLast;					// +0x08
	char **m_bfmeNode;					// +0x0C
};

// ?bfmeAdvance@Gen_00651FA0@@QAEXXZ
void Gen_00651FA0::bfmeAdvance(void)
{
	m_bfmeCurrent = m_bfmeCurrent + 0x210;

	if (m_bfmeCurrent == m_bfmeLast)
	{
		m_bfmeNode = m_bfmeNode + 1;

		m_bfmeFirst = *m_bfmeNode;
		m_bfmeLast = m_bfmeFirst + 0x210;

		m_bfmeCurrent = m_bfmeFirst;
	}
}

class BfmeQuadDT
{
public:
	int m_bfmeFirst;					// +0x00
	int m_bfmeSecond;					// +0x04
	int m_bfmeThird;					// +0x08
	int m_bfmeFourth;					// +0x0C
};

class Gen_00122410
{
public:
	Gen_00122410(const int *value, const BfmeQuadDT *quad);

private:
	int m_bfmeValue;					// +0x00
	BfmeQuadDT m_bfmeQuad;					// +0x04
};

// ??0Gen_00122410@@QAE@PBHPBVBfmeQuadDT@@@Z
Gen_00122410::Gen_00122410(const int *value, const BfmeQuadDT *quad)
{
	m_bfmeValue = *value;

	m_bfmeQuad = *quad;
}
