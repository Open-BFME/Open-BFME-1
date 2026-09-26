// ?bfmeResetJQ@BfmeThingJQ@@QAEXXZ
// partial score=0.97 date=2026-09-08
void __cdecl operator delete(void *p);

class BfmeThingJQ
{
public:
	void bfmeResetJQ();

	int m_bfme00JQ;
	int m_bfme04JQ;
	volatile char m_bfme08JQ;
	unsigned char m_bfmePadJQ[3];
	volatile int m_bfme0cJQ;
	volatile int m_bfme10JQ;
	volatile int m_bfme14JQ;
	volatile int m_bfme18JQ;
	int m_bfme1cJQ;
	void *m_bfme20JQ;
	void *m_bfme24JQ;
};

void BfmeThingJQ::bfmeResetJQ()
{
	m_bfme08JQ = 0;
	m_bfme0cJQ = -2;
	m_bfme10JQ = -2;
	m_bfme14JQ = -2;
	m_bfme18JQ = 0;

	void *p = *(void *volatile *)&m_bfme20JQ;

	if (p != 0)
		operator delete(p);

	*(void *volatile *)&m_bfme20JQ = 0;

	void *q = *(void *volatile *)&m_bfme24JQ;

	operator delete(q);

	*(void *volatile *)&m_bfme24JQ = 0;
	m_bfme00JQ = 0;
	m_bfme04JQ = 0;
	m_bfme1cJQ = 0;
}
