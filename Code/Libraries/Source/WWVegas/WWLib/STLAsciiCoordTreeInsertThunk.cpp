// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
};
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
};

namespace _STL
{
template<class First, class Second> struct pair { };
template<class Value> struct _Rb_tree_node_base { };
template<class Value> struct _Nonconst_traits { };
template<class Value, class Traits> struct _Rb_tree_iterator { };
template<class T> struct _Select1st { };
template<class T> struct less { };
template<class T> class allocator { };

template<class Key, class Value, class Select, class Less, class Alloc>
class _Rb_tree
{
    _Rb_tree_iterator<Value, _Nonconst_traits<Value> > _M_insert(_Rb_tree_node_base<Value> *, _Rb_tree_node_base<Value> *, Value const &, _Rb_tree_node_base<Value> *);
    _Rb_tree_iterator<Value, _Nonconst_traits<Value> > _bfme_insert_impl(_Rb_tree_node_base<Value> *, _Rb_tree_node_base<Value> *, Value const &, _Rb_tree_node_base<Value> *);
};

template<class Key, class Value, class Select, class Less, class Alloc>
_Rb_tree_iterator<Value, _Nonconst_traits<Value> > _Rb_tree<Key, Value, Select, Less, Alloc>::_M_insert(_Rb_tree_node_base<Value> *parent, _Rb_tree_node_base<Value> *child, Value const &value, _Rb_tree_node_base<Value> *root)
{
	return _bfme_insert_impl(parent, child, value, root);
}
}

typedef _STL::pair<const AsciiString, Coord3D> AsciiCoordPair;
typedef _STL::_Rb_tree<AsciiString, AsciiCoordPair, _STL::_Select1st<AsciiCoordPair>, _STL::less<AsciiString>, _STL::allocator<AsciiCoordPair> > AsciiCoordTree;
template _STL::_Rb_tree_iterator<AsciiCoordPair, _STL::_Nonconst_traits<AsciiCoordPair> > AsciiCoordTree::_M_insert(_STL::_Rb_tree_node_base<AsciiCoordPair> *, _STL::_Rb_tree_node_base<AsciiCoordPair> *, AsciiCoordPair const &, _STL::_Rb_tree_node_base<AsciiCoordPair> *);
