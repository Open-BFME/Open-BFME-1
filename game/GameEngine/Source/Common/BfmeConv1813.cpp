extern float g_bfmeDefaultBU;
extern const float BfmeZeroRange;

class BfmeThingBU
{
public:
	unsigned char m_bfmeHeadBU[0x3c];
	int m_bfmeCountBU;
};

class BfmeOwnerBU
{
public:
	float bfmeFadeBU(float amount);

	unsigned char m_bfmeHeadBU[0xc];
	BfmeThingBU *m_bfmeThingBU;
};

float BfmeOwnerBU::bfmeFadeBU(float amount)
{
	float value = g_bfmeDefaultBU - amount / (float)m_bfmeThingBU->m_bfmeCountBU;

	if (value < BfmeZeroRange)
		return BfmeZeroRange;

	if (value > g_bfmeDefaultBU)
		return g_bfmeDefaultBU;

	return value;
}
