// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

class GameSpyStagingRoom;

typedef _STL::_Rb_tree<GameSpyStagingRoom *,
	GameSpyStagingRoom *,
	_STL::_Identity<GameSpyStagingRoom *>,
	_STL::less<GameSpyStagingRoom *>,
	_STL::allocator<GameSpyStagingRoom *> > BuddyGameTree;

template BuddyGameTree::iterator BuddyGameTree::_M_insert(
	_STL::_Rb_tree_node_base *,
	_STL::_Rb_tree_node_base *,
	GameSpyStagingRoom *const &,
	_STL::_Rb_tree_node_base *);
