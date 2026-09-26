#include <string.h>

extern const char g_Rva0107301CEmptyString[];

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *s) throw();
	__forceinline ~BFMERetailAsciiString() throw() { releaseBuffer(); }

	void set(const char *s, int n) throw();

private:
	void releaseBuffer() throw();

	char *m_bfmeDataZH;
};

class INI
{
public:
	const char *getNextSubToken(const char *sep) throw();
	const char *getNextTokenOrNull(const char *sep) throw();

	static float scanReal(const char *s) throw();
};

struct BfmeVecZH
{
	float m_bfmeXZH;
	float m_bfmeYZH;
	float m_bfmeZZH;
};

class BfmeObjZH
{
public:
	void bfmeSetZH(const BfmeVecZH *v, const BFMERetailAsciiString *s) throw();

	unsigned char m_bfmeHeadZH[0x44];
	BfmeVecZH m_bfme44ZH;
};

void bfmeApplyZH(BfmeObjZH *o) throw();

void bfmeParseZH(INI *ini, void *instance, void *store, const void *userData)
{
	BFMERetailAsciiString s(g_Rva0107301CEmptyString);
	BfmeVecZH v;

	v.m_bfmeXZH = INI::scanReal(ini->getNextSubToken("X"));
	v.m_bfmeYZH = INI::scanReal(ini->getNextSubToken("Y"));
	v.m_bfmeZZH = INI::scanReal(ini->getNextSubToken("Z"));

	const char *tok = ini->getNextTokenOrNull(0);

	if (tok != 0)
		s.set(tok, strlen(tok));

	BfmeObjZH *o = (BfmeObjZH *)store;

	o->bfmeSetZH(&v, &s);

	if (o->m_bfme44ZH.m_bfmeZZH < v.m_bfmeZZH)
		o->m_bfme44ZH = v;

	bfmeApplyZH(o);
}
