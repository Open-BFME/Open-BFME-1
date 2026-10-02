// Shared float at retail VA 0x01075334 (RVA 0x00C75334): 00 00 80 3F.
// Keep the existing caller symbol; no original EA name is proven.
float g_bfmeDefaultBU = 1.0f;
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
