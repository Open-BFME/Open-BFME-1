// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Open-BFME7: STLport _Rb_tree::_M_insert for TeamFactory::m_prototypes,
// retail 0x000EED60, 188 bytes -- the private helper that the landed
// insert_unique at 0x000EEE50 (TeamFactory_insert_unique.cpp) calls.
//
// Retail inlines _M_create_node: the node (0x1c bytes = 16-byte base +
// pair<int,int> + TeamPrototype*) comes straight from
// __node_alloc::_M_allocate -- the default allocator's `n > 128 ? __stl_new :
// _M_allocate` folds on the constant size -- and the value is built by an
// out-of-line _Construct with no try/catch around it.  MSVC 7.1 only inlines
// _M_create_node when it carries no EH region, which is what
// _STLP_NO_EXCEPTIONS gives (the vendor <map> is otherwise untouched).

#define _STLP_NO_EXCEPTIONS 1
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

class TeamPrototype;

typedef _STL::pair<int, int> BfmeTeamPrototypeKey;
typedef _STL::pair<const BfmeTeamPrototypeKey, TeamPrototype *> BfmeTeamPrototypePair;
typedef _STL::_Rb_tree<BfmeTeamPrototypeKey,
	BfmeTeamPrototypePair,
	_STL::_Select1st<BfmeTeamPrototypePair>,
	_STL::less<BfmeTeamPrototypeKey>,
	_STL::allocator<BfmeTeamPrototypePair> > BfmeTeamPrototypeTree;

template BfmeTeamPrototypeTree::iterator
BfmeTeamPrototypeTree::_M_insert(_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *,
	const BfmeTeamPrototypePair &, _STL::_Rb_tree_node_base *);
