// cl: /Od /Gy
// Open-BFME5 conversions.

extern void *g_bfmeTableSWA[];

// Defines bfmeFormatToBuffer88A640 (RVA 0x88A640), matched in
// game/GameEngine/Source/Common/BfmeFormatBuffer88A640.cpp.
void bfmeFormatToBuffer88A640(const char *format, ...);

void bfmeGoSWA(int a, int b, int c)
{
	bfmeFormatToBuffer88A640((const char *)g_bfmeTableSWA[0], b, c, g_bfmeTableSWA[a]);
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
