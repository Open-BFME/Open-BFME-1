class LocomotorOverridable
{
public:
	LocomotorOverridable *friend_getFinalOverride();

	unsigned char m_bfmeHeadYL[4];
	LocomotorOverridable *m_bfme04YL;
	unsigned char m_bfmeMidYL[0x124];
	float m_bfme12CYL;
};

class BfmeSubYL
{
public:
	unsigned char m_bfmeHeadYL[0x1d4];
	float m_bfme1D4YL;
};

class Object
{
public:
	unsigned char m_bfmeHeadYL[0x204];
	BfmeSubYL *m_bfme204YL;
};

extern const float BfmeZeroRange;
extern volatile float g_rva001B59ScaleConstant;

static __forceinline LocomotorOverridable *bfmeFinalYL(LocomotorOverridable *p)
{
	if (p == 0)
		return 0;

	if (p->m_bfme04YL == 0)
		return p;

	return p->m_bfme04YL->friend_getFinalOverride();
}

class BfmeHostYL
{
public:
	float bfmeRateYL(Object *obj);

	unsigned char m_bfmeHeadYL[4];
	LocomotorOverridable *m_bfme04YL;
};

float BfmeHostYL::bfmeRateYL(Object *obj)
{
	if (obj == 0)
		return BfmeZeroRange;

	BfmeSubYL *s = obj->m_bfme204YL;

	if (s == 0)
		return BfmeZeroRange;

	float w = s->m_bfme1D4YL;

	return g_rva001B59ScaleConstant * bfmeFinalYL(m_bfme04YL)->m_bfme12CYL * w;
}
