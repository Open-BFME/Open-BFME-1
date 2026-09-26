// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Open-BFME5: STLport _Rb_tree insert_unique for TeamFactory::m_prototypes,
// retail 0x000EEE50, 192 bytes. Same tree as the already-matched _M_find at
// 0x000EE500: key pair<int,int>, mapped TeamPrototype*.

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

template _STL::pair<BfmeTeamPrototypeTree::iterator, bool>
BfmeTeamPrototypeTree::insert_unique(const BfmeTeamPrototypePair &);
