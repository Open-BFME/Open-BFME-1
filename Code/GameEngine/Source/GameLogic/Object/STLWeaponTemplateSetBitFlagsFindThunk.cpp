// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/WeaponSet.h
class WeaponTemplateSet
{
};

template <int Bits>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
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

template <class T>
struct _Select1st
{
};

template <class T>
class allocator
{
};

template <class T>
struct _Rb_tree_node
{
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree
{
	template <class SearchKey>
	_Rb_tree_node<Value> *_M_find(const SearchKey &) const;
};

class WeaponTemplateBitFlagsFindShim
{
public:
	_Rb_tree_node<pair<const BitFlags<17>, const WeaponTemplateSet *> > *find(const BitFlags<17> &k) const;
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
template <class SearchKey>
_Rb_tree_node<Value> *_Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::_M_find(const SearchKey &k) const
{
	return (_Rb_tree_node<Value> *)((WeaponTemplateBitFlagsFindShim const *)this)->find((const BitFlags<17> &)k);
}
}

typedef BitFlags<17> WeaponSetFlags;
typedef _STL::pair<const WeaponSetFlags, const WeaponTemplateSet *> WeaponTemplateSetPair;
typedef SparseMatchFinder<WeaponTemplateSet, WeaponSetFlags>::MapHelper WeaponTemplateSetMapHelper;
typedef _STL::_Rb_tree<const WeaponSetFlags, WeaponTemplateSetPair, _STL::_Select1st<WeaponTemplateSetPair>, WeaponTemplateSetMapHelper, _STL::allocator<WeaponTemplateSetPair> > WeaponTemplateSetTree;
template _STL::_Rb_tree_node<WeaponTemplateSetPair> *WeaponTemplateSetTree::_M_find<WeaponSetFlags>(const WeaponSetFlags &) const;
