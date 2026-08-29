// Open-BFME5 conversions.

class BfmeT1126
{
public:
	virtual void *bfmeV01126(void *a1, int a2, int a3, int a4, int a5) = 0;
	virtual void *bfmeV11126(void *a1, int a2, int a3, int a4, int a5) = 0;
	virtual void *bfmeV21126(void *a1, int a2, int a3, int a4, int a5) = 0;
};

class BfmeA1126
{
public:
	void *bfmeGo1126(void *a1, int a2, int a3, int a4, int a5);
	char m_bfmePad[0xc];
	BfmeT1126 *m_bfme0c;
};

void *BfmeA1126::bfmeGo1126(void *a1, int a2, int a3, int a4, int a5)
{
	volatile int x = 0;

	m_bfme0c->bfmeV21126(a1, a2, a3, a4, a5);
	return a1;
}

class BfmeB1126
{
public:
	void *bfmeGo1126(void *a1, int a2, int a3, int a4, int a5);
	char m_bfmePad[0xc];
	BfmeT1126 *m_bfme0c;
};

void *BfmeB1126::bfmeGo1126(void *a1, int a2, int a3, int a4, int a5)
{
	volatile int x = 0;

	m_bfme0c->bfmeV11126(a1, a2, a3, a4, a5);
	return a1;
}
