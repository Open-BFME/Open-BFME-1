// Open-BFME5 conversions.

class BfmeMgrTJA
{
public:
	char *bfmeFindTJA(int key);
};

extern BfmeMgrTJA *g_bfmeMgrTJA;

class BfmeThingTJA
{
public:
	char *bfmeGoTJA();
	char m_bfmePad[0xbc];
	int m_bfmeKey;
};

char *BfmeThingTJA::bfmeGoTJA()
{
	return g_bfmeMgrTJA->bfmeFindTJA(m_bfmeKey) + 8;
}
