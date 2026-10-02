// Open-BFME5 conversions.

// retail 0x007E8AC0: ?run@Rva007E8AC0@@QAEXXZ
class Rva007E8AC0
{
public:
	void run();
};

class BfmeMsgVIW
{
public:
	void bfmeSetVIW(const char *k, void *v);
	void bfmeSet3VIW(const char *k, int v);
	void bfmeSet4VIW(const char *k, void *v);
	char m_bfmePad[0x1c];
	int m_bfme1c;
};

typedef __int64 FeslInt64;

// retail 0x007E8E90
class Rva007E8810Message
{
public:
	void addInt64(const char *key, FeslInt64 value);
};

// Retail hands addInt64 the "blobId" key as a single 64-bit value, while the
// transaction builders below receive that value split over two adjacent stack
// parameters (the low half first). Reading the frame keeps the byte-identical
// pair of pushes: nothing is shifted or combined at the call site.

extern void *g_bfmeAVIW;
extern void *g_bfmeBVIW;
extern void *g_bfmeCVIW;
extern void *g_bfmeDVIW;
extern void *g_bfmeEVIW;

void __stdcall bfmeGoAVIW(BfmeMsgVIW *m, void *a, void *b)
{
	void *g = g_bfmeAVIW;
	((Rva007E8AC0 *)m)->run();
	m->m_bfme1c = 0x626c6f62;
	m->bfmeSetVIW("TXN", g);
	((Rva007E8810Message *)m)->addInt64("blobId", *reinterpret_cast<const FeslInt64 *>(&a));
}

void __stdcall bfmeGoBVIW(BfmeMsgVIW *m, void *a, void *b)
{
	void *g = g_bfmeBVIW;
	((Rva007E8AC0 *)m)->run();
	m->m_bfme1c = 0x626c6f62;
	m->bfmeSetVIW("TXN", g);
	((Rva007E8810Message *)m)->addInt64("blobId", *reinterpret_cast<const FeslInt64 *>(&a));
}

void __stdcall bfmeGoCVIW(BfmeMsgVIW *m, void *a, void *b)
{
	void *g = g_bfmeCVIW;
	((Rva007E8AC0 *)m)->run();
	m->m_bfme1c = 0x626c6f62;
	m->bfmeSetVIW("TXN", g);
	((Rva007E8810Message *)m)->addInt64("blobId", *reinterpret_cast<const FeslInt64 *>(&a));
}

void __stdcall bfmeGoDVIW(BfmeMsgVIW *m, void *a, void *b, int r)
{
	void *g = g_bfmeDVIW;
	((Rva007E8AC0 *)m)->run();
	m->m_bfme1c = 0x626c6f62;
	m->bfmeSetVIW("TXN", g);
	((Rva007E8810Message *)m)->addInt64("blobId", *reinterpret_cast<const FeslInt64 *>(&a));
	m->bfmeSet3VIW("rating", r);
}

void __stdcall bfmeGoEVIW(BfmeMsgVIW *m, void *a, void *b)
{
	void *g = g_bfmeEVIW;
	((Rva007E8AC0 *)m)->run();
	m->m_bfme1c = 0x61636374;
	m->bfmeSetVIW("TXN", g);
	m->bfmeSet4VIW("eaMailFlag", a);
	m->bfmeSet4VIW("thirdPartyMailFlag", b);
}
