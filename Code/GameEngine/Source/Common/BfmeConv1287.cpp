// Open-BFME5 conversions.

class BfmeThingSA
{
public:
	void *bfmeGetSA(void *a, void *b);
};

class BfmeSinkSA
{
public:
	void bfmeUseSA(void *a, void *b);
};

class BfmeHostSA
{
public:
	void bfmeGoSA(BfmeThingSA *r);
	char m_bfmePad[0x18];
	BfmeSinkSA *m_bfmeSink;
};

void BfmeHostSA::bfmeGoSA(BfmeThingSA *r)
{
	void *a = r->bfmeGetSA((void *)"TID", 0);
	void *b = r->bfmeGetSA((void *)"PID", 0);
	m_bfmeSink->bfmeUseSA(a, b);
}

class BfmeThingSB
{
public:
	void *bfmeGetSB(void *a, void *b);
};

class BfmeSinkSB
{
public:
	void bfmeUseSB(void *a, void *b);
};

class BfmeHostSB
{
public:
	void bfmeGoSB(BfmeThingSB *r);
	char m_bfmePad[0x18];
	BfmeSinkSB *m_bfmeSink;
};

void BfmeHostSB::bfmeGoSB(BfmeThingSB *r)
{
	void *a = r->bfmeGetSB((void *)"TID", 0);
	void *b = r->bfmeGetSB((void *)"PID", 0);
	m_bfmeSink->bfmeUseSB(a, b);
}
