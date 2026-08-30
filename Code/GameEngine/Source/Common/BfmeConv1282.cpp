// Open-BFME5 conversions.

class BfmeQ1282
{
public:
	void bfmeBind1282(void *p);
};

extern "C" void __stdcall bfmeStep1282(BfmeQ1282 *a, int b, int c);

class BfmeA1282
{
public:
	void bfmeGo1282(BfmeQ1282 *a1, int a2, int a3, int a4);
	void bfmeFinish1282(BfmeQ1282 *a1, int a2, int a3, int a4);
	char m_bfmePad00[0x64];
	int m_bfme64;
};

void BfmeA1282::bfmeGo1282(BfmeQ1282 *a1, int a2, int a3, int a4)
{
	bfmeStep1282(a1, a2, 0);
	a1->bfmeBind1282(&m_bfme64);
	bfmeFinish1282(a1, a2, a3, a4);
}
