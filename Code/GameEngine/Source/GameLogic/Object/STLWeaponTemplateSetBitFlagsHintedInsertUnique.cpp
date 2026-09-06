// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/asciistring_downloadmanager /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
//
// Retail 0x001429C0 (629 B): STLport _Rb_tree::insert_unique(iterator hint,
// const value&) for SparseMatchFinder<WeaponTemplateSet, BitFlags<17>>::MatchMap,
// a byte-twin (tools/twin_scan.py) of the hinted insert_unique at 0x0019AA50
// (Rva0019AA50TreeInsertUnique.cpp): same compile chain (PreRTS.h,
// _BFME_RETAIL_TREE_INSERT_LAYOUT, _STLP_NO_EXCEPTIONS), only the comparator
// and node-insert callees differ. The comparator is the already-matched
// out-of-line ??RMapHelper@?$SparseMatchFinder@VWeaponTemplateSet@@V?$BitFlags@$0BB@@@@@
// (SparseMatchFinderMapHelperThunks.cpp). SparseMatchFinder is restated here with
// MapHelper::operator() given a VISIBLE body under __declspec(noinline): a
// declared-only comparator is opaque to MSVC 7.1, which then assumes the call may
// write the tree, reloads the header pointer after it and cannot cross-jump the
// three `return insert_unique(v).first;` tails (661 B). With the body visible the
// call is still emitted out of line (and pinned), but the compiler knows it is
// side-effect free and produces retail's 629 B layout. See docs/shape_levers.md.
// The reference BitFlags template is renamed away with a macro so a one-word
// stand-in can carry the mangled name; the body only compares keys by reference.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#define _STLP_NO_EXCEPTIONS
#define BitFlags RealBitFlags   // keep the reference header's template out of the way
#include "PreRTS.h"
#include "Common/AsciiString.h"
#undef BitFlags

class WeaponTemplateSet;

template <int Bits>
class BitFlags
{
public:
	unsigned int m_bits;
};

template <class Set, class Flags>
class SparseMatchFinder
{
public:
	struct MapHelper
	{
		__declspec(noinline) bool operator()(const Flags &a, const Flags &b) const
		{
			return a.m_bits < b.m_bits;
		}
	};
};

typedef BitFlags<17> WeaponSetFlags;
typedef SparseMatchFinder<WeaponTemplateSet, WeaponSetFlags>::MapHelper WeaponTemplateSetMapHelper;
typedef _STL::pair<const WeaponSetFlags, const WeaponTemplateSet *> WeaponTemplateSetPair;
typedef _STL::_Rb_tree<const WeaponSetFlags, WeaponTemplateSetPair,
	_STL::_Select1st<WeaponTemplateSetPair>, WeaponTemplateSetMapHelper,
	_STL::allocator<WeaponTemplateSetPair> > WeaponTemplateSetTree;

template WeaponTemplateSetTree::iterator
WeaponTemplateSetTree::insert_unique( WeaponTemplateSetTree::iterator,
	const WeaponTemplateSetPair & );
