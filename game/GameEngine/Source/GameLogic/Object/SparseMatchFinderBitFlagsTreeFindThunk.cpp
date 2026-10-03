template <int Bits>
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
};
class ArmorTemplateSet;
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/WeaponSet.h
class WeaponTemplateSet
{
};

template <class Set, class Flags>
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SparseMatchFinder.h
class SparseMatchFinder
{
public:
	// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SparseMatchFinder.h
	struct MapHelper
	{
	};
};

namespace _STL
{
class ArmorTreeFindAccess;
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
	friend class ArmorTreeFindAccess;
	_Rb_tree_node<Value> *_M_find(Key const &) const;
	template <class SearchKey>
	_Rb_tree_node<Value> *_M_find(SearchKey const &) const;
};
}

typedef BitFlags<187> WeaponFlags;
typedef SparseMatchFinder<WeaponTemplateSet, WeaponFlags> WeaponFinder;
typedef WeaponFinder::MapHelper WeaponMapHelper;
typedef _STL::pair<const WeaponFlags, const WeaponTemplateSet *> WeaponPair;
typedef _STL::_Rb_tree<const WeaponFlags, WeaponPair, _STL::_Select1st<WeaponPair>, WeaponMapHelper, _STL::allocator<WeaponPair> > WeaponTree;
typedef BitFlags<11> ArmorFlags;
typedef _STL::pair<const ArmorFlags, const ArmorTemplateSet *> ArmorPair;
typedef SparseMatchFinder<ArmorTemplateSet, ArmorFlags>::MapHelper ArmorMapHelper;
typedef _STL::_Rb_tree<const ArmorFlags, ArmorPair, _STL::_Select1st<ArmorPair>, ArmorMapHelper, _STL::allocator<ArmorPair> > ArmorTree;

namespace _STL
{
class ArmorTreeFindAccess
{
public:
	static __forceinline _Rb_tree_node<::ArmorPair> *find(::ArmorTree const *tree, ::ArmorFlags const &key)
	{
		return tree->_M_find<::ArmorFlags>(key);
	}
};
}

template <class Key, class Value, class Select, class Less, class Alloc>
_STL::_Rb_tree_node<Value> *_STL::_Rb_tree<Key, Value, Select, Less, Alloc>::_M_find(Key const &k) const
{
	return (_STL::_Rb_tree_node<Value> *)_STL::ArmorTreeFindAccess::find(
		(ArmorTree const *)this, (ArmorFlags const &)k);
}

template _STL::_Rb_tree_node<WeaponPair> *WeaponTree::_M_find(WeaponFlags const &) const;
