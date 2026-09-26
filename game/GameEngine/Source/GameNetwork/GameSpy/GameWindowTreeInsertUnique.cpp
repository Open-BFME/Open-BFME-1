// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

class GameWindow;

typedef _STL::_Rb_tree<GameWindow *,
	GameWindow *,
	_STL::_Identity<GameWindow *>,
	_STL::less<GameWindow *>,
	_STL::allocator<GameWindow *> > GameWindowTree;

template _STL::pair<GameWindowTree::iterator, bool>
GameWindowTree::insert_unique(GameWindow *const &);
