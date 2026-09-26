// Open-BFME5 conversions.

class BfmeSink1009
{
public:
	void bfmeSend1009(int a);
};

struct BfmeOwner1009
{
	char m_bfmePad[0x258];
	int m_bfmeMode;
};

class BfmeA1009
{
public:
	void bfmeGo1009A();

	char m_bfmePad[4];
	BfmeOwner1009 *m_bfmeOwner;
	BfmeSink1009 *m_bfmeSink;
	char m_bfmePad2[0x20];
	volatile int m_bfmeVal;
};

void BfmeA1009::bfmeGo1009A()
{
	BfmeOwner1009 *o = m_bfmeOwner;

	m_bfmeVal = 0;

	int mode = o->m_bfmeMode;
	BfmeSink1009 *s = m_bfmeSink;

	if (mode == 1) {
		s->bfmeSend1009(0x12);
		return;
	}

	if (mode == 2)
		s->bfmeSend1009(0x13);
}

class BfmeSinkC1009
{
public:
	char bfmeSend1009C(void *b, void *a);
};

class BfmeC1009
{
public:
	char bfmeGo1009C(void *a, void *b);
	char bfmeTry1009(void *a, void *b);

	char m_bfmePad[0x58];
	BfmeSinkC1009 *m_bfmeSink;
};

char BfmeC1009::bfmeGo1009C(void *a, void *b)
{
	if (!bfmeTry1009(a, b))
		return 0;

	BfmeSinkC1009 *s = m_bfmeSink;

	if (!s)
		return 0;

	return s->bfmeSend1009C(b, a);
}
