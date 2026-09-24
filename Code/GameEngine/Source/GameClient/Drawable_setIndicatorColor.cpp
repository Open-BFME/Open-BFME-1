// cl: /DNDEBUG /MD /EHsc
// stlport
// ?setIndicatorColor@Drawable@@QAEXI@Z
// BFME Drawable::setIndicatorColor (0x004186E0, 143 bytes): stores the colour
// at +0x3C0, then turns the house-colour indicator on when the game-logic flag
// at +0x114 is set or the bound thing at +0xFC is any of kinds 119 and 179.
// Identity: the matched Drawable::changedTeam at 0x00418830 calls it through
// ILT 0x00028C09. This TU carries only the fields and ABI views the body uses.

typedef unsigned int UnsignedInt;

#include <bitset>

// The retail call is Thing::isAnyKindOf through ILT 0x0004250A; the BFME mask
// is six dwords, wider than the reference-ZH KindOfMaskType.
struct KindOfMask
{
	enum BogusInitType
	{
		kInit = 0
	};

	KindOfMask(BogusInitType k, int idx1, int idx2)
	{
		m_bits.set(idx1);
		m_bits.set(idx2);
	}

	std::bitset<180> m_bits;
};

typedef KindOfMask KindOfMaskType;

class Thing
{
public:
	bool isAnyKindOf(const KindOfMaskType &mask) const;
};

class GameLogic;
extern GameLogic *TheBfmeGameLogic;

struct BfmeGameLogicIndicator
{
	unsigned char m_unreconstructed_000[0x114];
	bool m_indicatorOverride;
};

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
	m_indicatorColor = color;
	Thing *object = getObject();
	bool indicatorOn = reinterpret_cast<const BfmeGameLogicIndicator *>(TheBfmeGameLogic)->m_indicatorOverride
		|| (object && object->isAnyKindOf(KindOfMaskType(KindOfMaskType::kInit, 119, 179)));
	bfmeSetIndicatorOn(indicatorOn);
}
