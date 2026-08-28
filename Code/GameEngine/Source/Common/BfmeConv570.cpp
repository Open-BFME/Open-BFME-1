class BfmeGlobalCBE
{
public:
	unsigned char m_bfmeHead[0x68];
	void *m_bfmeCur;
};

extern BfmeGlobalCBE *bfmeTheCBE;

void *bfmeNowCBE();
void bfmeSetCBE(void *what, int value);

void __stdcall bfmeGoCBE(void *spare)
{
	if (bfmeTheCBE != 0)
	{
		void *cur = bfmeTheCBE->m_bfmeCur;
		if (bfmeNowCBE() != cur)
			bfmeSetCBE(cur, 6);
	}
}
