class LocomotorOverridable
{
public:
	LocomotorOverridable *friend_getFinalOverride();

	unsigned char m_bfmeHeadXR[4];
	LocomotorOverridable *m_bfme04XR;
	unsigned char m_bfmeMidXR[0xc0];
	unsigned char m_bfmeC8XR;
	unsigned char m_bfmeGapXR[0x3eb];
	int m_bfme4B4XR;
};

class Drawable
{
public:
	bool isKindOf(int kind) const;

	unsigned char m_bfmeHeadXR[4];
	LocomotorOverridable *m_bfme04XR;
};

static __forceinline LocomotorOverridable *bfmeFinalXR(LocomotorOverridable *p)
{
	if (p == 0)
		return 0;

	if (p->m_bfme04XR == 0)
		return p;

	return p->m_bfme04XR->friend_getFinalOverride();
}

int __stdcall bfmeGetXR(Drawable *d)
{
	if (d == 0)
		return 0;

	if ((bfmeFinalXR(d->m_bfme04XR)->m_bfmeC8XR & 2) == 0)
		return 0;

	if (d->isKindOf(7))
		return 0;

	if (d->isKindOf(0x6c))
		return 0;

	return bfmeFinalXR(d->m_bfme04XR)->m_bfme4B4XR;
}
