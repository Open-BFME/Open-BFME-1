// Open-BFME5 conversions: an INI field parser that takes a name and an
// optional count.

extern "C" unsigned int __cdecl strlen(const char *s);

class RetailLayoutString
{
public:
	void set(const char *s, int n);
};

class INI
{
public:
	const char *getNextToken(const char *seps);
	const char *getNextTokenOrNull(const char *seps);
	static int scanInt(const char *s);
};

class Bfme5NamedValueA
{
public:
	char m_bfmePad[0x22c];
	RetailLayoutString m_bfmeName;
	int m_bfmeValue;
};

void __cdecl bfme5ParseNamedValueA(INI *ini, Bfme5NamedValueA *t)
{
	const char *name = ini->getNextToken(0);
	const char *num = ini->getNextTokenOrNull(0);
	int v = num ? INI::scanInt(num) : 1;
	int len = name ? (int)strlen(name) : 0;

	t->m_bfmeName.set(name, len);
	t->m_bfmeValue = v;
}

class Bfme5NamedValueB
{
public:
	char m_bfmePad[0x22c];
	RetailLayoutString m_bfmeName;
	int m_bfmeValue;
};

void __cdecl bfme5ParseNamedValueB(INI *ini, Bfme5NamedValueB *t)
{
	const char *name = ini->getNextToken(0);
	const char *num = ini->getNextTokenOrNull(0);
	int v = num ? INI::scanInt(num) : 1;
	int len = name ? (int)strlen(name) : 0;

	t->m_bfmeName.set(name, len);
	t->m_bfmeValue = v;
}
