// ?d_00299a80@@YAXXZ
// partial score=0.88 date=2026-09-11
class BfmePrimaryFV
{
public:
	void bfmeResetFV(void);
	void bfmeAdvanceFV(int delta);

	char m_pad00[4];
	struct BfmeCurveSet *m_curves;
	char m_pad08[0x1c];
	struct Shadow *m_shadow;
};

class U4Curve006095D0
{
public:
	float evaluate(int t) const;
};

struct BfmeCurveSet
{
	char m_pad00[0x10];
	U4Curve006095D0 m_curve10;
	char m_pad14[0x2b];
	U4Curve006095D0 m_curve3c;
	char m_pad40[0x2b];
	U4Curve006095D0 m_curve68;
};

struct ShadowValue1704
{
	char m_pad00[0x20];
	float m_value20;
	char m_pad24[0x34];
	float m_value58;
	float m_value5c;
};

struct Shadow
{
	char m_pad00[0x58];
	ShadowValue1704 *m_value58;
	ShadowValue1704 *m_value5c;
	void setOpacity(int value);
};

extern float g_bfmeUint32Scale;
extern float g_01075954;
extern float g_bfmeScaleB3;

void BfmePrimaryFV::bfmeAdvanceFV(volatile int delta)
{
	volatile float scaled_second;

	if (m_shadow == 0)
		return;

	BfmeCurveSet *curves = m_curves;
	*(float *)&delta = (float)(unsigned int)delta;
	int encoded = delta;
	float first = curves->m_curve10.evaluate(encoded);
	float doubled = first + first;
	float second = curves->m_curve68.evaluate(encoded);
	ShadowValue1704 *first_value = m_shadow->m_value58;
	first_value->m_value5c = first_value->m_value58 = doubled;
	ShadowValue1704 *second_value = m_shadow->m_value5c;
	second_value->m_value58 = doubled;
	second *= g_01075954;
	second_value->m_value5c = doubled;
	scaled_second = second;
	int opacity = (int)(curves->m_curve3c.evaluate(encoded) * g_bfmeScaleB3);
	m_shadow->setOpacity(opacity);
	m_shadow->m_value58->m_value20 = -scaled_second;
	m_shadow->m_value5c->m_value20 = scaled_second;
}

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
