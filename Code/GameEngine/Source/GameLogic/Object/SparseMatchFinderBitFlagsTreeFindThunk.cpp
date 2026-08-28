template <int Bits>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
};
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/WeaponSet.h
class WeaponTemplateSet
{
};

template <class Set, class Flags>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SparseMatchFinder.h
class SparseMatchFinder
{
public:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SparseMatchFinder.h
	struct MapHelper
	{
	};
};

namespace _STL
{
template <class First, class Second>
struct pair
{
};
template <class Value>
struct _Rb_tree_node
{
};
template <class T>
struct _Select1st
{
};
template <class T>
class allocator
{
};

template <class Key, class Value, class Select, class Less, class Alloc>
class _Rb_tree
{
	_Rb_tree_node<Value> *_M_find(Key const &) const;
};

class SparseBitFlagsTreeFindShim
{
public:
	_Rb_tree_node<pair<const BitFlags<187>, const WeaponTemplateSet *> > *find(BitFlags<187> const &k) const;
};

template <class Key, class Value, class Select, class Less, class Alloc>
_Rb_tree_node<Value> *_Rb_tree<Key, Value, Select, Less, Alloc>::_M_find(Key const &k) const
{
	return (_Rb_tree_node<Value> *)((SparseBitFlagsTreeFindShim const *)this)->find((BitFlags<187> const &)k);
}
}

typedef BitFlags<187> WeaponFlags;
typedef SparseMatchFinder<WeaponTemplateSet, WeaponFlags> WeaponFinder;
typedef WeaponFinder::MapHelper WeaponMapHelper;
typedef _STL::pair<const WeaponFlags, const WeaponTemplateSet *> WeaponPair;
typedef _STL::_Rb_tree<const WeaponFlags, WeaponPair, _STL::_Select1st<WeaponPair>, WeaponMapHelper, _STL::allocator<WeaponPair> > WeaponTree;
template _STL::_Rb_tree_node<WeaponPair> *WeaponTree::_M_find(WeaponFlags const &) const;
