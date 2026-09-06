// ?insert_unique@?$_Rb_tree@$$CBV?$BitFlags@$0BB@@@U?$pair@$$CBV?$BitFlags@$0BB@@@PBVWeaponTemplateSet@@@_STL@@U?$_Select1st@U?$pair@$$CBV?$BitFlags@$0BB@@@PBVWeaponTemplateSet@@@_STL@@@3@UMapHelper@?$SparseMatchFinder@VWeaponTemplateSet@@V?$BitFlags@$0BB@@@@@V?$allocator@U?$pair@$$CBV?$BitFlags@$0BB@@@PBVWeaponTemplateSet@@@_STL@@@3@@_STL@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBV?$BitFlags@$0BB@@@PBVWeaponTemplateSet@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBV?$BitFlags@$0BB@@@PBVWeaponTemplateSet@@@_STL@@@2@@2@U32@ABU?$pair@$$CBV?$BitFlags@$0BB@@@PBVWeaponTemplateSet@@@2@@Z
// partial score=0.7 date=2026-09-05
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
// (SparseMatchFinderMapHelperThunks.cpp), so SparseMatchFinder is restated here
// with MapHelper::operator() DECLARED ONLY: the reference header defines it
// inline, which would fold the call away. BitFlags comes from the real header.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#define _STLP_NO_EXCEPTIONS
#include "PreRTS.h"
#include "Common/BitFlags.h"

class WeaponTemplateSet;

template <class Set, class Flags>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SparseMatchFinder.h
class SparseMatchFinder
{
public:
	struct MapHelper
	{
		bool operator()(const Flags &a, const Flags &b) const;
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
