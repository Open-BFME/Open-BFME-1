extern const float g_bfmeZeroXJ;

struct BfmeSubXJ
{
	unsigned char m_bfmeBytesXJ[4];
};

class BfmeThingXJ
{
public:
	unsigned char m_bfmeHeadXJ[0x38];
	BfmeSubXJ m_bfmeSubXJ;
};

class BfmeOwnerXJ
{
public:
	virtual void bfmeV0XJ();
	virtual bool bfmeTestXJ(void *a, BfmeThingXJ *b);
	virtual void bfmeV2XJ();
	virtual void bfmeV3XJ();
	virtual void bfmeV4XJ();
	virtual void bfmeV5XJ();
	virtual void bfmeDoneXJ(void *a, BfmeSubXJ *sub);

	void bfmeApplyXJ(void *a, BfmeThingXJ *b);
	void bfmeStepXJ(void *a, BfmeThingXJ *b);

	unsigned char m_bfmeHeadXJ[0x58];
	float m_bfmeValueXJ;
};

void BfmeOwnerXJ::bfmeStepXJ(void *a, BfmeThingXJ *b)
{
	if (m_bfmeValueXJ == g_bfmeZeroXJ && bfmeTestXJ(a, b))
		bfmeApplyXJ(a, b);

	if (m_bfmeValueXJ > g_bfmeZeroXJ)
		bfmeDoneXJ(a, &b->m_bfmeSubXJ);
}
