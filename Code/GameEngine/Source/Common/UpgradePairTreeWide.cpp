// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Near-twin of the upgradePair tree's _M_insert (0x0064C3D0, 185B,
// Code/GameEngine/Source/Common/UpgradePairTree.cpp) at 0x005A9E60 (185B).
// Byte-identical except: the node allocation size is 0x38 instead of 0x20
// (a wider value payload), the value construct call substitutes to a
// different Construct thunk for that wider type, and the key-compare call
// substitutes to AsciiString::operator== (0x00046803, already matched in
// Code/GameEngine/Source/Common/RTS/AsciiStringEqualityThunk.cpp) instead of
// operator<. Fresh tags for the wider value type; identity of the owning
// tree/value is NOT recovered.
#define _STLP_NO_EXCEPTIONS 1
#include <map>
#include <functional>

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
	// Only the size matters here: the comparison is a call.
	void *m_data;
};

bool operator==(const AsciiString &left, const AsciiString &right);

// Node value is 0x28 bytes total (0x38 node - 0x10 header): AsciiString key
// (4B) plus 36 bytes of unmodelled payload.
struct BfmeUpgradeInfoWide
{
	void *m_bfmeFirst;
	Int m_bfmeSecond;
	Int m_bfmeThird;
	Int m_bfmeFourth;
	Int m_bfmeFifth;
	Int m_bfmeSixth;
	Int m_bfmeSeventh;
	Int m_bfmeEighth;
	Int m_bfmeNinth;
};

struct upgradePairWide
{
	typedef AsciiString first_type;
	typedef BfmeUpgradeInfoWide second_type;

	AsciiString first;
	BfmeUpgradeInfoWide second;
};

namespace _STL
{
// Not inlined in this build: the value is built through a call.
template <>
void _Construct(upgradePairWide *p, const upgradePairWide &val);
}

typedef _STL::_Rb_tree<AsciiString, upgradePairWide, _STL::_Select1st<upgradePairWide>, _STL::equal_to<AsciiString>, _STL::allocator<upgradePairWide> > BfmeUpgradeTreeWide;

void BfmeUpgradePairTreeWideAnchor(BfmeUpgradeTreeWide &tree, const upgradePairWide &value)
{
	tree.insert_unique(tree.begin(), value);
}
