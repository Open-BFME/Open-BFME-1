// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class AptValue
{
public:
	int toInteger() const;
};

class BfmeA1243
{
public:
	void bfmeApply1243(void *a, void *b, void *c);
};

class Rva008B7040Object
{
public:
	char m_pad00[0x20];
	int m_value20;
	char m_pad24[0x1c];
	int m_value40;
	char m_pad44[0xc];
	int m_value50;
	int m_value54;
	int m_value58;
	char m_pad5c[4];
	int m_value60;
};

extern AptValue **g_bfmeArr1243;
extern int g_bfmeCount1243;
extern void *g_bfmeResult1243;

extern "C" void *bfmeMake1243(int n);

void *rva008B7040Build(Rva008B7040Object *a, int n)
{
	if (n < 1)
		return g_bfmeResult1243;

	a->m_value58 = g_bfmeArr1243[g_bfmeCount1243 - 1]->toInteger();
	if (n > 1)
		a->m_value54 = g_bfmeArr1243[g_bfmeCount1243 - 2]->toInteger();
	if (n > 2)
		a->m_value50 = g_bfmeArr1243[g_bfmeCount1243 - 3]->toInteger();

	((BfmeA1243 *)a)->bfmeApply1243(
		&a->m_value40, &a->m_value20,
		reinterpret_cast<void *>(-a->m_value60));
	return bfmeMake1243(0);
}
