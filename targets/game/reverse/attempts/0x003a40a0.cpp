// ?bfmeLimitEO@BfmeHostEO@@QAEMXZ
// partial score=0.97 date=2026-09-16
extern "C" double sqrt(double x);

#pragma intrinsic(sqrt)

struct Rva006C9270GlobalData
{
	unsigned char m_bfmeHeadEO[0x90];
	char m_bfmeFlagEO;
};

extern Rva006C9270GlobalData *TheWritableGlobalData;
extern float g_bfmeDirectionWeight1285;

class BfmeKeyboardEO
{
public:
	char bfmeIsShiftEO();
};

extern BfmeKeyboardEO *g_bfmeKeyboardEO;

template<class T> inline const T &bfmeMinEO(const T &a, const T &b)
{
	return a < b ? a : b;
}

class BfmeHostEO
{
public:
	float bfmeLimitEO();

	unsigned char m_bfmeHeadEO[0xc];
	float m_bfmeX0EO;
	float m_bfmeY0EO;
	float m_bfmeX1EO;
	float m_bfmeY1EO;
	unsigned char m_bfmeGapEO[4];
	float m_bfmeCapEO;
};

float BfmeHostEO::bfmeLimitEO()
{
	float dy = *(volatile float *)&m_bfmeY1EO;
	float cap = m_bfmeCapEO;
	volatile float dx = m_bfmeX1EO - m_bfmeX0EO;
	dy -= m_bfmeY0EO;

	float len[2];
	float d2 = dx * dx + dy * dy;
	len[0] = (float)sqrt(d2);

	if (g_bfmeKeyboardEO->bfmeIsShiftEO() && TheWritableGlobalData->m_bfmeFlagEO)
		*(volatile float *)&cap = *(volatile float *)&cap * g_bfmeDirectionWeight1285;

	return bfmeMinEO(cap, len[0]);
}

