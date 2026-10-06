typedef bool Bool;

enum KindOfType
{
	KINDOF_INVALID = 0
};

// The kind query this TU calls is Thing::isKindOf(KindOfType) const; the real
// header declares the class, this TU only adds the member it calls.
#define THING_TU_MEMBERS \
	Bool isKindOf(KindOfType t) const;
#include "Thing/thing.h"
#undef THING_TU_MEMBERS

// ILT 0x000022BB reaches the matched override-chain walker at 0x00087A80,
// ?getFinalOverride@Overridable@@QBEPBV1@XZ (public, const, const result).
class Overridable
{
public:
	const Overridable *getFinalOverride(void) const;
};

class LocomotorOverridable
{
public:
	unsigned char m_bfmeHeadYE[4];
	LocomotorOverridable *m_bfme04YE;
	unsigned char m_bfmeMidYE[0xcc];
	unsigned int m_bfmeD4YE;
};

class Drawable
{
public:
	unsigned char m_bfmeHeadYD[4];
	LocomotorOverridable *m_bfme04YE;
	unsigned char m_bfmeGap2YD[0x6c];
	int m_bfme74YD;
};

static __forceinline LocomotorOverridable *bfmeFinalYE(LocomotorOverridable *p)
{
	if (p == 0)
		return 0;

	if (p->m_bfme04YE == 0)
		return p;

	return (LocomotorOverridable *)((Overridable *)p->m_bfme04YE)->getFinalOverride();
}

class BfmeHostYD
{
public:
	bool bfmeCheckYD(Drawable *d);

	unsigned char m_bfmeHeadYD[0x1b4];
	int m_bfme1B4YD;
	unsigned char m_bfmeGapYD[4];
	int m_bfme1BCYD;
};

bool BfmeHostYD::bfmeCheckYD(Drawable *d)
{
	int id = d->m_bfme74YD;

	if (m_bfme1B4YD == id || m_bfme1BCYD == id || ((Thing *)d)->isKindOf((KindOfType)0xb))
		return true;

	return false;
}

char __stdcall bfmeCheckYE(Drawable *d)
{
	return ((bfmeFinalYE(d->m_bfme04YE)->m_bfmeD4YE >> 25) & 1) == 0;
}
