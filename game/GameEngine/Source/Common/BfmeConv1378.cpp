// Open-BFME5 conversions.

// retail 0x007E8AC0: ?run@Rva007E8AC0@@QAEXXZ
class Rva007E8AC0
{
public:
	void run();
};

class BfmeMsgVIT
{
public:
	void bfmeSetVIT(const char *k, void *v);
	char m_bfmePad[0x1c];
	int m_bfme1c;
};

extern void *g_bfmeVIT;
extern void *g_bfmeVIU;

void __stdcall bfmeGoVIT(BfmeMsgVIT *m, void *a, void *b)
{
	void *g = g_bfmeVIT;
	((Rva007E8AC0 *)m)->run();
	m->m_bfme1c = 0x61636374;
	m->bfmeSetVIT("TXN", g);
	m->bfmeSetVIT("password", a);
	m->bfmeSetVIT("newPassword", b);
}

void __stdcall bfmeGoVIU(BfmeMsgVIT *m, void *a, void *b, void *c)
{
	void *g = g_bfmeVIU;
	((Rva007E8AC0 *)m)->run();
	m->m_bfme1c = 0x72616e6b;
	m->bfmeSetVIT("TXN", g);
	m->bfmeSetVIT("sessionId", a);
	m->bfmeSetVIT("key", b);
	m->bfmeSetVIT("value", c);
}

extern void *g_bfmeVIV;

void __stdcall bfmeGoVIV(BfmeMsgVIT *m, char *code, char *game, char *platform, char *name, char *password, char *email)
{
	void *g = g_bfmeVIV;
	((Rva007E8AC0 *)m)->run();
	m->m_bfme1c = 0x61636374;
	m->bfmeSetVIT("TXN", g);
	m->bfmeSetVIT("code", code);
	m->bfmeSetVIT("game", game);
	m->bfmeSetVIT("platform", platform);
	if (name && *name)
		m->bfmeSetVIT("name", name);
	if (password && *password)
		m->bfmeSetVIT("password", password);
	if (email && *email)
		m->bfmeSetVIT("encryptedInfo", email);
}
