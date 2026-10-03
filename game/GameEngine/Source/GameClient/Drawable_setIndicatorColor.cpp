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
// is six dwords, wider than the reference-ZH KindOfMaskType. The matched
// body at 0x00132AE0 is spelled with the BitFlags<116> view class
// (game/GameEngine/Source/Common/Thing/Thing.cpp), which is what this
// declaration must mangle to; only the reference changes, not the six-dword
// mask that is built below.
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

template <int N>
class BitFlags;

class Thing
{
public:
	bool isAnyKindOf(const BitFlags<116> &mask) const;
};

class GameLogic;
// Retail VA 0x012F0898 is the canonical pointer defined in GameLogic.cpp.
extern GameLogic *TheGameLogic;

struct BfmeGameLogicIndicator
{
	unsigned char m_unreconstructed_000[0x114];
	bool m_unreconstructed_114;
};

class Drawable
{
public:
	void setIndicatorColor(UnsignedInt color);
	Thing *getObject() const { return m_object; }

	unsigned char m_unreconstructed_000[0xfc];
	Thing *m_object;
	unsigned char m_unreconstructed_100[0x2c0];
	UnsignedInt m_indicatorColor;
};

// bfmeSetIndicatorOn is reached through the five-byte ILT thunk 0x00018CF5
// (?j_00018cf5@@YAXXZ); it jumps with the thiscall `this` in ECX.
extern void j_00018cf5();

typedef void (Drawable::*bfmeSetIndicatorOnThunk)(bool flag);

union BfmeSetIndicatorOnThunkCast
{
	void (__cdecl *freeFunction)(bool flag);
	bfmeSetIndicatorOnThunk memberFunction;
};

void Drawable::setIndicatorColor(UnsignedInt color)
{
	m_indicatorColor = color;
	Thing *object = getObject();
	bool indicatorOn = reinterpret_cast<const BfmeGameLogicIndicator *>(TheGameLogic)->m_unreconstructed_114
		|| (object && object->isAnyKindOf(*(const BitFlags<116> *)&(KindOfMaskType &)(KindOfMaskType(KindOfMaskType::kInit, 119, 179))));
	BfmeSetIndicatorOnThunkCast cast;
	cast.freeFunction = reinterpret_cast<void (__cdecl *)(bool)>(&::j_00018cf5);
	(this->*cast.memberFunction)(indicatorOn);
}
