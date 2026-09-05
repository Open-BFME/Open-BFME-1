// ?insert_unique@?$_Rb_tree@$$CBV?$BitFlags@$0BB@@@U?$pair@$$CBV?$BitFlags@$0BB@@@PBVWeaponTemplateSet@@@_STL@@U?$_Select1st@U?$pair@$$CBV?$BitFlags@$0BB@@@PBVWeaponTemplateSet@@@_STL@@@3@UMapHelper@?$SparseMatchFinder@VWeaponTemplateSet@@V?$BitFlags@$0BB@@@@@V?$allocator@U?$pair@$$CBV?$BitFlags@$0BB@@@PBVWeaponTemplateSet@@@_STL@@@3@@_STL@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBV?$BitFlags@$0BB@@@PBVWeaponTemplateSet@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBV?$BitFlags@$0BB@@@PBVWeaponTemplateSet@@@_STL@@@2@@2@U32@ABU?$pair@$$CBV?$BitFlags@$0BB@@@PBVWeaponTemplateSet@@@2@@Z
// partial score=0.2 date=2026-09-05
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x001429C0: byte-twin of ?insert_unique@?$_Rb_tree@URva0019BC70Key@@...
// at 0x0019AA50 (Rva0019AA50TreeInsertUnique.cpp), the STLport iterator-hinted
// insert_unique(iterator, const Value&), here for SparseMatchFinder<WeaponTemplateSet,
// BitFlags<17>>::MatchMap (a std::map<const BitFlags<17>, const WeaponTemplateSet *,
// MapHelper>) -- same tree already reached by the already-matched _M_find at
// 0x00042D1B (STLWeaponTemplateSetBitFlagsFindThunk.cpp) and the const-comparator
// forwarders at 0x0000A9A2/0x00010B1D (SparseMatchFinderMapHelperThunks.cpp).
//
// Two 5-byte forwarding thunks already jump here (ICF-folded aliases of the
// same real body, one per numeric-literal guess for the mangled BitFlags<N>):
//   0x00010F1E -> STLWeaponTemplateSetBitFlagsInsertUniqueThunk.cpp        ($0BB@ = BitFlags<17>)
//   0x00010F1E -> SparseMatchFinderBitFlagsTreeInsertUniqueThunk.cpp       ($0LL@)
// Landing under the $0BB@ (BitFlags<17>) spelling: it matches the already-landed
// WeaponMapHelperShim/MapHelper comparator's real bit count.
//
// Callees (in body order): the key comparator ??RMapHelper@?$SparseMatchFinder@
// VWeaponTemplateSet@@V?$BitFlags@$0BB@@@@@ (already matched, x8), the node-insert
// helper _M_insert (still a dump, x9, thunk 0x00022197 -> rva 0x00141060), the
// shared STL red-black bool increment/decrement thunks (x2/x1, already matched),
// and the single-arg insert_unique tail call (still a dump, x1, thunk 0x00015BE0
// -> rva 0x00141150).

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#define _STLP_NO_EXCEPTIONS
#include <map>

class WeaponTemplateSet;

template <int Bits>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
public:
	unsigned int m_bits;
};

template <class Set, class Flags>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SparseMatchFinder.h
class SparseMatchFinder
{
public:
	struct MapHelper
	{
		bool operator()(const Flags &, const Flags &) const;
	};
};

typedef BitFlags<17> WeaponSetFlags;
typedef _STL::pair<const WeaponSetFlags, const WeaponTemplateSet *> WeaponTemplateSetPair;
typedef SparseMatchFinder<WeaponTemplateSet, WeaponSetFlags>::MapHelper WeaponTemplateSetMapHelper;

typedef _STL::_Rb_tree<const WeaponSetFlags, WeaponTemplateSetPair,
	_STL::_Select1st<WeaponTemplateSetPair>, WeaponTemplateSetMapHelper,
	_STL::allocator<WeaponTemplateSetPair> > WeaponTemplateSetTree;

extern template _STL::pair<WeaponTemplateSetTree::iterator, bool>
WeaponTemplateSetTree::insert_unique( const WeaponTemplateSetPair & );

template WeaponTemplateSetTree::iterator
WeaponTemplateSetTree::insert_unique( WeaponTemplateSetTree::iterator,
	const WeaponTemplateSetPair & );
