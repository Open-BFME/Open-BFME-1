// ?insert_unique@?$_Rb_tree@$$CBV?$BitFlags@$0L@@@U?$pair@$$CBV?$BitFlags@$0L@@@PBVArmorTemplateSet@@@_STL@@U?$_Select1st@U?$pair@$$CBV?$BitFlags@$0L@@@PBVArmorTemplateSet@@@_STL@@@3@UMapHelper@?$SparseMatchFinder@VArmorTemplateSet@@V?$BitFlags@$0L@@@@@V?$allocator@U?$pair@$$CBV?$BitFlags@$0L@@@PBVArmorTemplateSet@@@_STL@@@3@@_STL@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBV?$BitFlags@$0L@@@PBVArmorTemplateSet@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBV?$BitFlags@$0L@@@PBVArmorTemplateSet@@@_STL@@@2@@2@U32@ABU?$pair@$$CBV?$BitFlags@$0L@@@PBVArmorTemplateSet@@@2@@Z
// partial score=0.3 date=2026-09-05
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/asciistring_downloadmanager /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
//
// Retail 0x001426A0 (629B). Identity is proved by a matched caller: the ILT
// thunk in Code/GameEngine/Source/GameLogic/Object/SparseMatchFinderArmorBitFlagsTreeInsertUniqueThunk.cpp
// (0x0000F952) jumps directly here, and its decorated name is the real
// std::map<const BitFlags<ARMORSET_COUNT>, const ArmorTemplateSet*,
// SparseMatchFinder<ArmorTemplateSet,BitFlags<ARMORSET_COUNT>>::MapHelper>'s
// _Rb_tree::insert_unique (reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SparseMatchFinder.h,
// GameLogic/ArmorSet.h). MapHelper is private in the real SparseMatchFinder,
// so it cannot be named from outside; this TU reproduces the exact template
// shape and MapHelper's real comparison body locally (matching the existing
// sibling thunk file's identity-preserving skeleton convention) with public
// access, using the real BitFlags<N> for correct storage layout.
#define _STLP_NO_EXCEPTIONS
#include "PreRTS.h"
#include "Common/BitFlags.h"

class ArmorTemplateSet; // forward-declared: only used as a pointer here.

template<class MATCHABLE, class BITSET>
class SparseMatchFinder
{
public:
	struct MapHelper
	{
		bool operator()( const BITSET &a, const BITSET &b ) const
		{
			int i;
			if( a.size() < b.size() )
				return true;
			for( i = 0; i < a.size(); ++i )
			{
				bool aVal = a.test( i );
				bool bVal = b.test( i );
				if( aVal && bVal ) continue;
				if( !aVal && !bVal ) continue;
				if( !aVal ) return true;
				return false;
			}
			return false;
		}
	};
};

typedef BitFlags<11> ArmorSetFlagsLocal;
typedef SparseMatchFinder<ArmorTemplateSet, ArmorSetFlagsLocal> ArmorTemplateSetFinderLocal;
typedef ArmorTemplateSetFinderLocal::MapHelper ArmorMapHelper;
typedef _STL::pair<const ArmorSetFlagsLocal, const ArmorTemplateSet *> ArmorPair;
typedef _STL::_Rb_tree<const ArmorSetFlagsLocal, ArmorPair, _STL::_Select1st<ArmorPair>,
	ArmorMapHelper, _STL::allocator<ArmorPair> > ArmorTree;

template ArmorTree::iterator
ArmorTree::insert_unique( ArmorTree::iterator, const ArmorPair & );
