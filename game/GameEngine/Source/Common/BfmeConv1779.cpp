class BfmeAiDataDC
{
public:
	unsigned char m_bfmeHeadDC[0xc4];
	float m_bfmeScaleDC;
};

class AI
{
public:
	unsigned char m_bfmeHeadDC[0x14];
	BfmeAiDataDC *m_bfmeDataDC;
};

extern AI *TheAI;
extern float g_bfmeFactorDC;

class BfmeSubDC
{
public:
	char bfmeOkDC(void);
};

class BfmeHolderDC
{
public:
	unsigned char m_bfmeHeadDC[4];
	BfmeSubDC *m_bfmeSubDC;
};

class BfmeSrcDC
{
public:
	BfmeHolderDC *bfmeGetDC(int flag);
};

float __cdecl bfmeScaleDC(BfmeSrcDC *source)
{
	float value = TheAI->m_bfmeDataDC->m_bfmeScaleDC;

	if (source->bfmeGetDC(0) != 0 && source->bfmeGetDC(0)->m_bfmeSubDC->bfmeOkDC())
		return *(volatile float *)&value * g_bfmeFactorDC;

	return value;
}
