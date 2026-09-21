// ?bfmeSetupXA@BfmePoolXA@@QAEXPAVBfmeSpecXA@@@Z
// partial score=0.97 date=2026-09-08
extern "C" void *__cdecl memset(void *d, int c, unsigned int n);

extern void *(__cdecl *Rva008C5D70Alloc)(unsigned int n);

class BfmeSpecXA
{
public:
	unsigned char m_bfmeHeadXA[0x20];
	int m_bfme20XA;
	int m_bfme24XA;
	int m_bfme28XA;
	int m_bfme2CXA;
	int m_bfme30XA;
	int m_bfme34XA;
	int m_bfme38XA;
	int m_bfme3CXA;
	int m_bfme40XA;
	int m_bfme44XA;
};

class BfmePoolXA
{
public:
	void bfmeSetupXA(BfmeSpecXA *s);

	int m_bfme00XA;
	int m_bfme04XA;
	int *m_bfme08XA;
	int m_bfme0CXA;
	int m_bfme10XA;
	int *m_bfme14XA;
	int m_bfme18XA;
	int m_bfme1CXA;
	int *m_bfme20XA;
	int m_bfme24XA;
	int m_bfme28XA;
	int *m_bfme2CXA;
	int m_bfme30XA;
	int m_bfme34XA;
	int *m_bfme38XA;
	int m_bfme3CXA;
	int m_bfme40XA;
	int *m_bfme44XA;
	int m_bfme48XA;
	int m_bfme4CXA;
	int m_bfme50XA;
	int *m_bfme54XA;
	int *m_bfme58XA;
	unsigned char m_bfmeTailXA[0x24];
	int m_bfme80XA;
};

void BfmePoolXA::bfmeSetupXA(BfmeSpecXA *s)
{
	int a = s->m_bfme20XA;

	m_bfme04XA = a;
	m_bfme08XA = (int *)Rva008C5D70Alloc(a * 4);

	int b = s->m_bfme24XA;

	m_bfme10XA = b;
	m_bfme14XA = (int *)Rva008C5D70Alloc(b * 4);

	int c = s->m_bfme28XA;

	m_bfme1CXA = c;
	m_bfme20XA = (int *)Rva008C5D70Alloc(c * 4);

	int d = s->m_bfme2CXA;

	m_bfme28XA = d;
	m_bfme2CXA = (int *)Rva008C5D70Alloc(d * 4);

	int e = s->m_bfme30XA;

	m_bfme34XA = e;
	m_bfme38XA = (int *)Rva008C5D70Alloc(e * 4);

	int f = s->m_bfme3CXA;

	m_bfme40XA = f;
	m_bfme44XA = (int *)Rva008C5D70Alloc(f * 4);

	int g = s->m_bfme44XA;
	int h = s->m_bfme40XA;

	m_bfme50XA = g;
	m_bfme4CXA = h;
	int *base = (int *)Rva008C5D70Alloc(h * g * 4);

	m_bfme54XA = base;

	memset(base, 0, m_bfme50XA * m_bfme4CXA * 4);

	int *p = m_bfme54XA + m_bfme50XA * m_bfme48XA;

	m_bfme48XA = m_bfme48XA + 1;
	m_bfme58XA = p;
	m_bfme80XA = 0;
}
