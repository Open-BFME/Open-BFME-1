// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: the upgradePair tree's _M_insert (185B at 0x0064C3D0) and
// insert_unique (292B at 0x0064C4C0).
//
// The ledger had both under a map<AsciiString, Coord3D> name, but the element
// is not that pair: the construct call at 0x0064C412 resolves to
// ??$_Construct@UupgradePair@@, and the node the tree allocates is 0x20 bytes
// -- sixteen of header and sixteen of value. So the tree is keyed on
// AsciiString through _Select1st over a sixteen-byte upgradePair, which is the
// shape modelled here.
//
// The comparison is a call, not inline code: both bodies push the two keys and
// call operator<(const AsciiString &, const AsciiString &) through the thunk at
// 0x00015898.
#define _STLP_NO_EXCEPTIONS 1
#include <map>

typedef int Int;
typedef float Real;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
	// Only the size matters here: the comparison is a call.
	void *m_data;
};

bool operator<(const AsciiString &left, const AsciiString &right);

// Twelve bytes behind the key: what the 0x20-byte node leaves after the
// sixteen of header and the key's pointer.
struct BfmeUpgradeInfo
{
	void *m_bfmeFirst;
	Int m_bfmeSecond;
	Int m_bfmeThird;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AutoDepositUpdate.h
struct upgradePair
{
	typedef AsciiString first_type;
	typedef BfmeUpgradeInfo second_type;

	AsciiString first;
	BfmeUpgradeInfo second;
};

namespace _STL
{
// Not inlined in this build: the value is built through a call.
template <>
void _Construct(upgradePair *p, const upgradePair &val);
}

typedef _STL::_Rb_tree<AsciiString, upgradePair, _STL::_Select1st<upgradePair>, _STL::less<AsciiString>, _STL::allocator<upgradePair> > BfmeUpgradeTree;

void BfmeUpgradePairTreeAnchor(BfmeUpgradeTree &tree, const upgradePair &value)
{
	tree.insert_unique(tree.begin(), value);
}
