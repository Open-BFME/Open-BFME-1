struct BfmeReqZA
{
	unsigned char m_bfmeHeadZA[0xc];
	int m_bfme0CZA;
};

class LocomotorOverridable
{
public:
	LocomotorOverridable *friend_getFinalOverride();

	unsigned char m_bfmeHeadZA[4];
	LocomotorOverridable *m_bfme04ZA;
	unsigned char m_bfmeMidZA[0xc4];
	unsigned int m_bfmeCCZA;
	unsigned int m_bfmeD0ZA;
};

class BfmeSinkZA
{
public:
	virtual void bfmeV0ZA() = 0;
	virtual void bfmeV1ZA() = 0;
	virtual float bfmeGetZA(BfmeReqZA *r) = 0;
};

extern const float BfmeZeroRange;
extern float g_bfmeDefaultBU;

static __forceinline LocomotorOverridable *bfmeFinalZA(LocomotorOverridable *p)
{
	if (p == 0)
		return 0;

	if (p->m_bfme04ZA == 0)
		return p;

	return p->m_bfme04ZA->friend_getFinalOverride();
}

class Drawable
{
public:
	bool isKindOf(int kind) const;
	float bfmeRateZA(BfmeReqZA *r);

	unsigned char m_bfmeHeadZA[4];
	LocomotorOverridable *m_bfme04ZA;
	unsigned char m_bfmeMidZA[0x1f8];
	BfmeSinkZA *m_bfme200ZA;
};

float Drawable::bfmeRateZA(BfmeReqZA *r)
{
	int k = r->m_bfme0CZA;

	if (k != 7
		&& (bfmeFinalZA(m_bfme04ZA)->m_bfmeCCZA & 0x8000000) != 0
		&& !isKindOf(0x95)
		&& k != 4
		&& k != 5)
		return BfmeZeroRange;

	if ((bfmeFinalZA(m_bfme04ZA)->m_bfmeD0ZA & 0x20000000) != 0)
	{
		if (k != 6)
			return BfmeZeroRange;

		return g_bfmeDefaultBU;
	}

	BfmeSinkZA *s = m_bfme200ZA;

	if (s != 0)
		return s->bfmeGetZA(r);

	return BfmeZeroRange;
}
