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
extern const float g_rva01075350;

// The range test is not a recovered body: retail reaches it through the ILT
// thunk at 0x000481FD, whose only definition in the tree is the
// address-derived gen-thunk ?j_000481fd@@YAXXZ. Call it under that spelling,
// keeping this TU's own view of the signature.
extern void j_000481fd();

bool __stdcall bfmeTryGK(BfmeObjGK *obj, float range, BfmeVec3GK *out)
{
	typedef char (BfmeMgrGK::*CheckThunk)(BfmeObjGK *, int, int);
	union Check
	{
		void (*function)(void);
		CheckThunk member;
	} checkThunk;

	if (range < g_rva01075350)
		return false;

	obj->bfmeStartGK(1, 0xfa0, 1000.0f, 1000.0f, 0, 0);

	if (obj->m_bfmeFlagGK == 0)
		return false;

	obj->m_bfmeRangeGK = range;

	checkThunk.function = j_000481fd;
	if ((g_bfmeMgrGK->*checkThunk.member)(obj, 0, 0) == 0)
		return false;

	*out = obj->m_bfmeResultGK;

	return true;
}
