class LocomotorOverridable
{
public:
	LocomotorOverridable *friend_getFinalOverride();

	unsigned char m_bfmeHeadYE[4];
	LocomotorOverridable *m_bfme04YE;
	unsigned char m_bfmeMidYE[0xcc];
	unsigned int m_bfmeD4YE;
};

class Drawable
{
public:
	bool isKindOf(int kind) const;

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

	return p->m_bfme04YE->friend_getFinalOverride();
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

	if (m_bfme1B4YD == id || m_bfme1BCYD == id || d->isKindOf(0xb))
		return true;

	return false;
}

char __stdcall bfmeCheckYE(Drawable *d)
{
	return ((bfmeFinalYE(d->m_bfme04YE)->m_bfmeD4YE >> 25) & 1) == 0;
}
