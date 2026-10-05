// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport
struct FieldParse
{
	const char *m_bfmeTokenABF;
	void (*m_bfmeProcABF)();
	const void *m_bfmeUserABF;
	unsigned int m_bfmeOffsetABF;
};

class MultiIniFieldParse
{
public:
	void add(const FieldParse *fields, unsigned int extra);
};

extern const FieldParse g_bfmeBaseTableABF[];
extern FieldParse g_bfmeTableABF[];
#include "Common/BitFlags.h"

unsigned int g_bfmeGuardDwordABF = 0;

void bfmeBuildABF(MultiIniFieldParse *p);

void bfmeBuildABF(MultiIniFieldParse *p)
{
	p->add(g_bfmeBaseTableABF, 8);

	unsigned int mask = 1;
	unsigned int zero = 0;

	if ((g_bfmeGuardDwordABF & mask) == 0)
	{
		g_bfmeGuardDwordABF |= mask;

		g_bfmeTableABF[2].m_bfmeUserABF = BitFlags<11>::getBitNames();
		g_bfmeTableABF[2].m_bfmeOffsetABF = 0x74;
		g_bfmeTableABF[3].m_bfmeTokenABF = (const char *)zero;
		g_bfmeTableABF[3].m_bfmeProcABF = (void (*)())zero;
		g_bfmeTableABF[3].m_bfmeUserABF = (const void *)zero;
		g_bfmeTableABF[3].m_bfmeOffsetABF = zero;
	}

	p->add(g_bfmeTableABF, zero);
}
