class BfmeVec3GK
{
public:
	float m_bfmeXGK;
	float m_bfmeYGK;
	float m_bfmeZGK;
};

class BfmeObjGK
{
public:
	virtual void bfmeVt0GK();
	virtual void bfmeVt1GK();
	virtual void bfmeStartGK(int a, int b, float c, float d, int e, int f);

	unsigned char m_bfmeGapGK[0x14];
	float m_bfmeRangeGK;
	unsigned char m_bfmeGap2GK[8];
	char m_bfmeFlagGK;
	unsigned char m_bfmeGap3GK[0x23];
	BfmeVec3GK m_bfmeResultGK;
};

class BfmeMgrGK
{
public:
	char bfmeCheckGK(BfmeObjGK *o, int a, int b);
};

extern BfmeMgrGK *g_bfmeMgrGK;
extern const float BfmeZeroRange;

bool __stdcall bfmeTryGK(BfmeObjGK *obj, float range, BfmeVec3GK *out)
{
	if (range < BfmeZeroRange)
		return false;

	obj->bfmeStartGK(1, 0xfa0, 1000.0f, 1000.0f, 0, 0);

	if (obj->m_bfmeFlagGK == 0)
		return false;

	obj->m_bfmeRangeGK = range;

	if (g_bfmeMgrGK->bfmeCheckGK(obj, 0, 0) == 0)
		return false;

	*out = obj->m_bfmeResultGK;

	return true;
}
