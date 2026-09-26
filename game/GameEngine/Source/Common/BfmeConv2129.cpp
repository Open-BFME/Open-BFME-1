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
extern int g_bfmeTableDJb;
extern unsigned char g_bfmeGuardByteABF;
extern unsigned int g_bfmeGuardDwordABF;

void bfmeBuildABF(MultiIniFieldParse *p);

void bfmeBuildABF(MultiIniFieldParse *p)
{
	p->add(g_bfmeBaseTableABF, 8);

	unsigned int mask = 1;
	unsigned int zero = 0;

	if ((g_bfmeGuardByteABF & mask) == 0)
	{
		g_bfmeGuardDwordABF |= mask;

		g_bfmeTableABF[2].m_bfmeUserABF = &g_bfmeTableDJb;
		g_bfmeTableABF[2].m_bfmeOffsetABF = 0x74;
		g_bfmeTableABF[3].m_bfmeTokenABF = (const char *)zero;
		g_bfmeTableABF[3].m_bfmeProcABF = (void (*)())zero;
		g_bfmeTableABF[3].m_bfmeUserABF = (const void *)zero;
		g_bfmeTableABF[3].m_bfmeOffsetABF = zero;
	}

	p->add(g_bfmeTableABF, zero);
}
