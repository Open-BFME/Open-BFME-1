class BfmePrimaryFV
{
public:
	void bfmeResetFV(void);
	void bfmeAdvanceFV(int delta);
};

class BfmeLogicFV
{
public:
	unsigned char m_bfmeHeadFV[0x3c];
	int m_bfmeFrameFV;
};

extern BfmeLogicFV *g_bfmeGameLogicFV;

class BfmeSecondFV
{
public:
	int bfmeStepFV(void);

	unsigned char m_bfmeHeadFV[0x10];
	int m_bfmeStampFV;
};

int BfmeSecondFV::bfmeStepFV(void)
{
	char *base = (char *)this;

	if (*(void **)(base - 0xc) == 0)
		return 0x3fffffff;

	int delta = g_bfmeGameLogicFV->m_bfmeFrameFV - m_bfmeStampFV;

	if (delta == 0)
		((BfmePrimaryFV *)(base - 0x10))->bfmeResetFV();

	((BfmePrimaryFV *)(base - 0x10))->bfmeAdvanceFV(delta);
	return 1;
}
