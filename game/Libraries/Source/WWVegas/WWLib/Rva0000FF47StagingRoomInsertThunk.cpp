// cl: /O2 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport

// Retail RVA 0x0000FF47 is a five-byte jump to the matched STLport
// _Rb_tree<GameSpyStagingRoom *, GameSortStruct>::_M_insert body at 0x0053F7E0.
class GameSpyStagingRoom;
class Rva0000FF47StagingRoomInsertThunk;

struct GameSortStruct
{
	bool operator()(GameSpyStagingRoom *left,
		GameSpyStagingRoom *right) const;
};

namespace _STL
{
template <class T>
struct _Identity
{
};

template <class T>
class allocator
{
};

template <class T>
struct _Nonconst_traits
{
};

struct _Rb_tree_node_base
{
};

template <class Value, class Traits>
struct _Rb_tree_iterator
{
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree
{
	public:
	typedef _Rb_tree_iterator<Value, _Nonconst_traits<Value> > iterator;

	friend class ::Rva0000FF47StagingRoomInsertThunk;

	private:
	iterator _M_insert(_Rb_tree_node_base *x, _Rb_tree_node_base *y,
		const Value &value, _Rb_tree_node_base *w);
};
}

typedef _STL::_Rb_tree<GameSpyStagingRoom *, GameSpyStagingRoom *,
	_STL::_Identity<GameSpyStagingRoom *>, GameSortStruct,
	_STL::allocator<GameSpyStagingRoom *> > StagingRoomTree;

class Rva0000FF47StagingRoomInsertThunk : public StagingRoomTree
{
public:
	iterator forward(_STL::_Rb_tree_node_base *x,
		_STL::_Rb_tree_node_base *y,
		GameSpyStagingRoom *const &value,
		_STL::_Rb_tree_node_base *w);
};

Rva0000FF47StagingRoomInsertThunk::iterator
Rva0000FF47StagingRoomInsertThunk::forward(
	_STL::_Rb_tree_node_base *x,
	_STL::_Rb_tree_node_base *y,
	GameSpyStagingRoom *const &value,
	_STL::_Rb_tree_node_base *w)
{
	return this->_M_insert(x, y, value, w);
}
