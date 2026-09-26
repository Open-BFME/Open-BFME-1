extern const float BfmeZeroRange;
extern volatile float g_rva001B59ScaleConstant;
extern const float g_bfmeFallbackET;

class BfmeCfgET
{
public:
	unsigned char m_bfmeHeadET[0x1d4];
	float m_bfmeKET;
};

class BfmeThingET
{
public:
	unsigned char m_bfmeHeadET[0x204];
	BfmeCfgET *m_bfmeCfgET;
};

class BfmeTmplET
{
public:
	const BfmeTmplET *bfmeFinalET() const;

	void *m_bfmeVfET;
	BfmeTmplET *m_bfmeOverET;
	unsigned char m_bfmeHeadET[0x1c];
	float m_bfmeFactorET;
};

class BfmeHostET
{
public:
	float bfmeMaxTurnET(BfmeThingET *t) const;
	float bfmeComputeET(BfmeThingET *t, float *out);

	void *m_bfmeVfET;
	BfmeTmplET *m_bfmeTmplET;
};

float BfmeHostET::bfmeComputeET(BfmeThingET *t, float *out)
{
	float k = t->m_bfmeCfgET->m_bfmeKET;
	BfmeTmplET *o = m_bfmeTmplET;
	const BfmeTmplET *r;

	if (o != 0 && o->m_bfmeOverET != 0)
		r = o->m_bfmeOverET->bfmeFinalET();
	else
		r = o;

	k = g_rva001B59ScaleConstant * r->m_bfmeFactorET * k;

	float v = bfmeMaxTurnET(t);
	float x;

	if (v > BfmeZeroRange)
		x = k / v;
	else
		x = g_bfmeFallbackET;

	if (out != 0)
	{
		*out = k > BfmeZeroRange ? x / k : BfmeZeroRange;
	}

	return x;
}
