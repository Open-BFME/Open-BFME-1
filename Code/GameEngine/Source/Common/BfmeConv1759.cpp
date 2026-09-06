extern const float BfmeZeroRange;
extern float g_bfmeOffsetDF;

class BfmeSrcBT
{
public:
	float bfmeCalcBT(void *value);
};

class BfmeDataBT
{
public:
	unsigned char m_bfmeHeadBT[0x18];
	float m_bfmeHeightBT;
};

class BfmeOwnBT
{
public:
	char bfmeTestBT(BfmeSrcBT *source, void *value);

	unsigned char m_bfmeHeadBT[4];
	BfmeDataBT *m_bfmeDataBT;
};

char BfmeOwnBT::bfmeTestBT(BfmeSrcBT *source, void *value)
{
	float delta = m_bfmeDataBT->m_bfmeHeightBT - g_bfmeOffsetDF;

	if (delta < BfmeZeroRange)
		return 0;

	if (delta == BfmeZeroRange)
		return 0;

	if (source->bfmeCalcBT(value) < delta * delta)
		return 1;

	return 0;
}
