struct BfmeReqZA
{
	unsigned char m_bfmeHeadZA[0xc];
	int m_bfme0CZA;
};

// The locomotor ILT resolves to this already-matched chain walker.
class Overridable
{
public:
	void *m_vtable;
	Overridable *m_nextOverride;
	const Overridable *getFinalOverride() const;
};

// Retail mangles KindOfType unsigned (W4KindOfType); VC7.1 picks the signed
// underlying type only when an enumerator is negative.
enum KindOfType
{
	KINDOF_INVALID = 0
};

#define THING_TU_MEMBERS \
	bool isKindOf( KindOfType kind ) const;
#include "../Common/Thing/thing.h"
#undef THING_TU_MEMBERS

class LocomotorOverridable
{
public:
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

extern const float g_rva01075350;
extern float g_bfmeDefaultBU;

static __forceinline LocomotorOverridable *bfmeFinalZA(LocomotorOverridable *p)
{
	if (p == 0)
		return 0;

	if (p->m_bfme04ZA == 0)
		return p;

	const Overridable *finalOverride =
		((const Overridable *)p->m_bfme04ZA)->getFinalOverride();
	return (LocomotorOverridable *)finalOverride;
}

class Drawable
{
public:
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
		&& !((const Thing *)this)->isKindOf((KindOfType)0x95)
		&& k != 4
		&& k != 5)
		return g_rva01075350;

	if ((bfmeFinalZA(m_bfme04ZA)->m_bfmeD0ZA & 0x20000000) != 0)
	{
		if (k != 6)
			return g_rva01075350;

		return g_bfmeDefaultBU;
	}

	BfmeSinkZA *s = m_bfme200ZA;

	if (s != 0)
		return s->bfmeGetZA(r);

	return g_rva01075350;
}
