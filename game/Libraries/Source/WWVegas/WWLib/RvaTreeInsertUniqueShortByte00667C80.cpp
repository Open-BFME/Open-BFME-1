// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Pair-byte body at 0x00667C80; address row preserves its distinct relocation.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

typedef _STL::pair<const unsigned short, unsigned char>
	RvaTreeInsertUniqueShortByte00667C80Pair;
typedef _STL::_Rb_tree<unsigned short,
	RvaTreeInsertUniqueShortByte00667C80Pair,
	_STL::_Select1st<RvaTreeInsertUniqueShortByte00667C80Pair>,
	_STL::less<unsigned short>,
	_STL::allocator<RvaTreeInsertUniqueShortByte00667C80Pair> >
	RvaTreeInsertUniqueShortByte00667C80Tree;

// ?insert_unique@?$_Rb_tree@GU?$pair@$$CBGE@_STL@@U?$_Select1st@U?$pair@$$CBGE@_STL@@@2@U?$less@G@2@V?$allocator@U?$pair@$$CBGE@_STL@@@2@@_STL@@QAE?AU?$pair@U?$_Rb_tree_iterator@U?$pair@$$CBGE@_STL@@U?$_Nonconst_traits@U?$pair@$$CBGE@_STL@@@2@@_STL@@_N@2@ABU?$pair@$$CBGE@2@@Z
template _STL::pair<
	RvaTreeInsertUniqueShortByte00667C80Tree::iterator, bool>
RvaTreeInsertUniqueShortByte00667C80Tree::insert_unique(
	const RvaTreeInsertUniqueShortByte00667C80Pair &);
