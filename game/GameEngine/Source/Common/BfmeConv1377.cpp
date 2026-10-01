// Open-BFME5 conversions.

class BfmeMsgVIR
{
public:
	void bfmeSetVIR(const char *a, void *b);
	char m_bfmePad[0x1c];
	int m_bfme1c;
};

// retail 0x007E8AC0
class Rva007E8AC0 { public: void run(); };

struct BfmeOwnerVIR;

extern void *g_bfmeVIR;

class BfmeThingVIR
{
public:
	void bfmeGoVIR(BfmeMsgVIR *m, const BfmeOwnerVIR *o, const char *const *n, int a, int b, int c);
	void bfmeSendVIR(BfmeMsgVIR *m, const BfmeOwnerVIR *o, const char *const *n, int a, int b, int c);
};

void BfmeThingVIR::bfmeGoVIR(BfmeMsgVIR *m, const BfmeOwnerVIR *o, const char *const *n, int a, int b, int c)
{
	void *g = g_bfmeVIR;
	((Rva007E8AC0*)m)->run();
	m->m_bfme1c = 0x72616e6b;
	m->bfmeSetVIR("TXN", g);
	bfmeSendVIR(m, o, n, a, b, c);
}

extern void *g_bfmeVIS;

class BfmeThingVIS
{
public:
	void bfmeGoVIS(BfmeMsgVIR *m, const BfmeOwnerVIR *o, const char *const *n, int a, int b, int c);
	void bfmeSendVIS(BfmeMsgVIR *m, const BfmeOwnerVIR *o, const char *const *n, int a, int b, int c);
};

void BfmeThingVIS::bfmeGoVIS(BfmeMsgVIR *m, const BfmeOwnerVIR *o, const char *const *n, int a, int b, int c)
{
	void *g = g_bfmeVIS;
	((Rva007E8AC0*)m)->run();
	m->m_bfme1c = 0x72616e6b;
	m->bfmeSetVIR("TXN", g);
	bfmeSendVIS(m, o, n, a, b, c);
}
