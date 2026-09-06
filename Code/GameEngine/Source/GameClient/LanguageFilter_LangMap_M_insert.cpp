// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/languagefilter /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Open-BFME7: STLport _Rb_tree<UnicodeString, pair<const UnicodeString, Bool>,
// UnicodeStringLessThan>::_M_insert for LanguageFilter's LangMap, retail
// 0x0044D810, 262 bytes.  LanguageFilter.cpp holds the tree's insert_unique;
// retail inlined _M_create_node here, which MSVC 7.1 only does when the helper
// has no try/catch -- _STLP_NO_EXCEPTIONS.  The EH frame that remains guards
// the two by-value UnicodeString copies the comparator takes.
#define _STLP_NO_EXCEPTIONS 1
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE
#include <map>	// before PreRTS.h so the default node allocator is chosen
#include "PreRTS.h"
#include "GameClient/LanguageFilter.h"

typedef _STL::_Rb_tree<UnicodeString, _STL::pair<const UnicodeString, Bool>,
	_STL::_Select1st<_STL::pair<const UnicodeString, Bool> >, UnicodeStringLessThan,
	_STL::allocator<_STL::pair<const UnicodeString, Bool> > > BfmeLangMapTree;

template BfmeLangMapTree::iterator
BfmeLangMapTree::_M_insert(_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *,
	const _STL::pair<const UnicodeString, Bool> &, _STL::_Rb_tree_node_base *);
