// cl: /GS
// Open-BFME5 conversions.

extern "C" int __cdecl sprintf(char *buf, const char *fmt, ...);

class BfmeMsgVJF
{
public:
	void bfmeRunVJF();
	void bfmeSetVJF(const char *k, void *v);
	void bfmeSet2VJF(const char *k, void *a, void *b);
	void bfmeSet3VJF(const char *k, int v);
	char m_bfmePad[0x1c];
	int m_bfme1c;
};

struct BfmePairVJF
{
	void *m_bfme00;
	void *m_bfme04;
};

extern void *g_bfmeVJF;

void __stdcall bfmeGoVJF(BfmeMsgVJF *m, BfmePairVJF *arr, int n)
{
	char buf[0x10];
	void *g = g_bfmeVJF;
	m->bfmeRunVJF();
	m->m_bfme1c = 0x6664626b;
	m->bfmeSetVJF("TXN", g);
	for (int i = 0; i < n; ++i)
	{
		sprintf(buf, "users.%d", i);
		m->bfmeSet2VJF(buf, arr[i].m_bfme00, arr[i].m_bfme04);
	}
	m->bfmeSet3VJF("users.[]", n);
}
