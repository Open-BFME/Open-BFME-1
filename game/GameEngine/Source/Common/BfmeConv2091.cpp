// Retail spells this accessor ?getFinalOverride@Overridable@@QBEPBV1@XZ
// (public const, upstream Overridable.h); the TU-local stand-in carries the
// template layout this body reads, so it takes the defining class/member name.
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	unsigned char m_bfmeHeadXR[4];
	Overridable *m_nextOverride;
	unsigned char m_bfmeMidXR[0xc0];
	unsigned char m_bfmeC8XR;
	unsigned char m_bfmeGapXR[0x3eb];
	int m_bfme4B4XR;
};

// Retail ILT 0x0003251F lands on Thing::isKindOf (0x000A2CF0).
enum KindOfType { };

class Thing
{
public:
	bool isKindOf(KindOfType kind) const;
};

class Drawable
{
public:
	unsigned char m_bfmeHeadXR[4];
	Overridable *m_nextOverride;
};

static __forceinline Overridable *bfmeFinalXR(Overridable *p)
{
	if (p == 0)
		return 0;

	if (p->m_nextOverride == 0)
		return p;

	return const_cast<Overridable *>( p->m_nextOverride->getFinalOverride() );
}

int __stdcall bfmeGetXR(Drawable *d)
{
	if (d == 0)
		return 0;

	if ((bfmeFinalXR(d->m_nextOverride)->m_bfmeC8XR & 2) == 0)
		return 0;

	if (reinterpret_cast<const Thing *>(d)->isKindOf((KindOfType)7))
		return 0;

	if (reinterpret_cast<const Thing *>(d)->isKindOf((KindOfType)0x6c))
		return 0;

	return bfmeFinalXR(d->m_nextOverride)->m_bfme4B4XR;
}
