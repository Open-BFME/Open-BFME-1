// cl: /DNDEBUG /DBFME_STLP_NODE_ALLOC /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/asciistring_downloadmanager /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// This specialization uses pooled nodes without a node-allocation catch.
// The original StringBase copy declaration retains placement construction EH.
#define _STLP_NO_EXCEPTIONS 1
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include "PreRTS.h"
#include "Common/AsciiString.h"
#include <list>
namespace _STL {
template <> struct less<AsciiString> {
 bool operator()(const AsciiString &left, const AsciiString &right) const {
  return left.compare(right) < 0;
 }
};
}
typedef _STL::pair<const AsciiString,
 _STL::list<AsciiString, _STL::allocator<AsciiString> > > AsciiStringListPair;
typedef _STL::_Rb_tree<AsciiString, AsciiStringListPair,
 _STL::_Select1st<AsciiStringListPair>, _STL::less<AsciiString>,
 _STL::allocator<AsciiStringListPair> > AsciiStringListTree;
template _STL::pair<AsciiStringListTree::iterator, bool>
 AsciiStringListTree::insert_unique(const AsciiStringListPair &);

// Full 183-byte private insertion at RVA 0x000817C0, including both allocation arms.
template AsciiStringListTree::iterator AsciiStringListTree::_M_insert(
 _STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *,
 const AsciiStringListPair &, _STL::_Rb_tree_node_base *);

// Full pair copy construction at RVA 0x00080AF0.
template _STL::pair<const AsciiString,
 _STL::list<AsciiString, _STL::allocator<AsciiString> > >::pair(
 const _STL::pair<const AsciiString,
 _STL::list<AsciiString, _STL::allocator<AsciiString> > > &);

// Full placement construction at RVA 0x00080E00.
template void _STL::_Construct<AsciiStringListPair, AsciiStringListPair>(
 AsciiStringListPair *, const AsciiStringListPair &);
