// Open-BFME5 conversions.

class Gen001C9AC0
{
public:
	void handle(int player);					// retail 0x001C9AC0 via ILT 0x000122AB
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
	Gen001C9AC0 *m_bfmeSink;
	char m_bfmePad2[0x20];
	volatile int m_bfmeVal;
};

void BfmeA1009::bfmeGo1009A()
{
	BfmeOwner1009 *o = m_bfmeOwner;

	m_bfmeVal = 0;

	int mode = o->m_bfmeMode;
	Gen001C9AC0 *s = m_bfmeSink;

	if (mode == 1) {
		s->handle(0x12);
		return;
	}

	if (mode == 2)
		s->handle(0x13);
}

class Rva001E4160List
{
public:
	bool any(void *first, void *second);				// retail 0x001E4160 via ILT 0x00004633
};

class Rva002DF120
{
public:
	unsigned char test(void *first, void *second);			// retail 0x002DF120 via ILT 0x0001D813
};

class BfmeC1009
{
public:
	char bfmeGo1009C(void *a, void *b);

	char m_bfmePad[0x58];
	Rva001E4160List *m_bfmeSink;
};

char BfmeC1009::bfmeGo1009C(void *a, void *b)
{
	if (!((Rva002DF120 *)this)->test(a, b))
		return 0;

	Rva001E4160List *s = m_bfmeSink;

	if (!s)
		return 0;

	return s->any(b, a);
}
