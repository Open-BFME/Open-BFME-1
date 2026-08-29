// Open-BFME5 conversions.

struct BfmeSrc941B
{
	char m_bfmePad[0x50c];
	int m_bfmeVal;
};

class BfmeThing941B
{
public:
	int bfmeGo941B(void *a, void *b);
	int m_bfmePad;
	BfmeSrc941B *m_bfmeSrc;
};

int BfmeThing941B::bfmeGo941B(void *a, void *b)
{
	return (int)(float)m_bfmeSrc->m_bfmeVal;
}

class BfmeThing941F
{
public:
	void bfmeGo941F(void *a);
	void bfmeOne941F();
	void bfmeTwo941F(void *a);
};

void BfmeThing941F::bfmeGo941F(void *a)
{
	bfmeOne941F();
	bfmeTwo941F(a);
}

void __stdcall bfmeCall941G(void *a, char *b);

void *__stdcall bfmeGo941G(void *a, void *b)
{
	bfmeCall941G(a, (char *)b + 0x38);
	return a;
}

