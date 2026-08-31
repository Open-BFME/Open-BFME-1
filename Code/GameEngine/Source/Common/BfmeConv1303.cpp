// cl: /Od /Gy
// Open-BFME5 conversions.

extern void *g_bfmeTableSWA[];

void bfmeWriteSWA(void *sink, int a, int b, void *tag);

void bfmeGoSWA(int a, int b, int c)
{
	bfmeWriteSWA(g_bfmeTableSWA[0], b, c, g_bfmeTableSWA[a]);
}

class BfmeThingSWA
{
public:
	void bfmePassSWA(int a);
	void bfmeFwdSWA(int a);
};

void BfmeThingSWA::bfmePassSWA(int a)
{
	char m_bfmeScratch[0x48];
	bfmeFwdSWA(a);
}
