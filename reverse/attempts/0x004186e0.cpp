// ?setIndicatorColor@Drawable@@QAEXI@Z
// partial score=0.99 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc
// stlport
// ?setIndicatorColor@Drawable@@QAEXI@Z
// BFME Drawable layout and indicator gate recovered from the matched
// Drawable::changedTeam caller at 0x00418830.  This TU intentionally carries
// only the fields and ABI views used by this body.

typedef unsigned int UnsignedInt;

#include <bitset>
#include <string.h>

template <int NUMBITS>
class BitFlags
{
	public:
	BitFlags()
	{
	}

	void set(int index)
	{
		m_bits.set(index);
	}

	private:
	std::bitset<NUMBITS> m_bits;
};

typedef BitFlags<180> KindOfMaskType;

class Thing
{
public:
	bool isAnyKindOf(const KindOfMaskType &mask) const;
};

struct BfmeGameLogicIndicator
{
	unsigned char m_unreconstructed_000[0x114];
	bool m_indicatorOverride;
};

extern BfmeGameLogicIndicator *TheBfmeGameLogic;

// The retail call is Thing::isAnyKindOf at 0x004250A; the BFME mask is six
// dwords, unlike the narrower reference-ZH BitFlags type.

class Drawable
{
public:
	void setIndicatorColor(UnsignedInt color);
	void bfmeSetIndicatorOn(bool flag);
	Thing *getObject() const { return m_object; }

	unsigned char m_unreconstructed_000[0xfc];
	Thing *m_object;
	unsigned char m_unreconstructed_100[0x2c0];
	UnsignedInt m_indicatorColor;
};

void Drawable::setIndicatorColor(UnsignedInt color)
{
	Thing *object = getObject();
	bool indicatorOn;
	*((UnsignedInt *)((unsigned char *)this + 0x3c0)) = color;
	if (!*((unsigned char *)TheBfmeGameLogic + 0x114))
	{
		if (!object)
			goto indicator_off;
		KindOfMaskType mask;
		mask.set(119);
		mask.set(179);
		if (!object->isAnyKindOf(mask))
			goto indicator_off;
	}
	memset(&indicatorOn, 1, sizeof(indicatorOn));
	bfmeSetIndicatorOn(indicatorOn);
	return;

indicator_off:
	memset(&indicatorOn, 0, sizeof(indicatorOn));
	bfmeSetIndicatorOn(indicatorOn);
}
