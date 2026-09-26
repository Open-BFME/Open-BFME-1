// ?bfmeFalloffBU@BfmeHostBU@@QBEMPBVBfmePosBU@@PBVBfmeThingBU@@@Z
// partial score=0.80 date=2026-09-08
extern "C" double sqrt(double x);

#pragma intrinsic(sqrt)

extern float g_bfmeDefaultBU;
extern const float BfmeZeroRange;

class BfmePosBU
{
public:
	float m_bfmeXBU;
	float m_bfmeYBU;
	float m_bfmeZBU;
};

class BfmeThingBU
{
public:
	unsigned char m_bfmeHeadBU[0x38];
	float m_bfmeXBU;
	float m_bfmeYBU;
	float m_bfmeZBU;
};

class BfmeInfoBU
{
public:
	unsigned char m_bfmeHeadBU[8];
	float m_bfmeRangeBU;
	float m_bfmeScaleBU;
};

class BfmeHostBU
{
public:
	float bfmeFalloffBU(const BfmePosBU *from, const BfmeThingBU *to) const;

	void *m_bfmeVfBU;
	BfmeInfoBU *m_bfmeInfoBU;
};

float BfmeHostBU::bfmeFalloffBU(const BfmePosBU *from, const BfmeThingBU *to) const
{
	if (m_bfmeInfoBU->m_bfmeScaleBU == 1.0f)
	{
		volatile BfmePosBU d;

		d.m_bfmeXBU = to->m_bfmeXBU - from->m_bfmeXBU;
		d.m_bfmeYBU = to->m_bfmeYBU - from->m_bfmeYBU;
		d.m_bfmeZBU = to->m_bfmeZBU - from->m_bfmeZBU;

		float v = g_bfmeDefaultBU - (float)sqrt(d.m_bfmeXBU * d.m_bfmeXBU + d.m_bfmeYBU * d.m_bfmeYBU + d.m_bfmeZBU * d.m_bfmeZBU) / m_bfmeInfoBU->m_bfmeRangeBU;

		if (v < BfmeZeroRange)
			return BfmeZeroRange;

		return v;
	}

	return g_bfmeDefaultBU;
}
