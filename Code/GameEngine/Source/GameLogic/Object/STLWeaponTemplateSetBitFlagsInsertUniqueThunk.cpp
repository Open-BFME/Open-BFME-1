// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/WeaponSet.h
class WeaponTemplateSet
{
};

template<int Bits>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
};

template<class Set, class Flags>
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
template<class First, class Second>
struct pair
{
};

template<class T>
struct _Select1st
{
};

template<class T>
struct _Nonconst_traits
{
};

template<class Value, class Traits>
struct _Rb_tree_iterator
{
};

template<class T>
class allocator
{
};

template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree
{
public:
    _Rb_tree_iterator<Value, _Nonconst_traits<Value> > insert_unique(_Rb_tree_iterator<Value, _Nonconst_traits<Value> >, const Value &);
};

template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
__declspec(naked) _Rb_tree_iterator<Value, _Nonconst_traits<Value> > _Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_unique(_Rb_tree_iterator<Value, _Nonconst_traits<Value> >, const Value &)
{
    __asm {
        _emit 0E9h
        _emit 09Dh
        _emit 01Ah
        _emit 013h
        _emit 000h
    }
}
}

typedef BitFlags<17> WeaponSetFlags;
typedef _STL::pair<const WeaponSetFlags, const WeaponTemplateSet *> WeaponTemplateSetPair;
typedef SparseMatchFinder<WeaponTemplateSet, WeaponSetFlags>::MapHelper WeaponTemplateSetMapHelper;
typedef _STL::_Rb_tree<const WeaponSetFlags, WeaponTemplateSetPair, _STL::_Select1st<WeaponTemplateSetPair>, WeaponTemplateSetMapHelper, _STL::allocator<WeaponTemplateSetPair> > WeaponTemplateSetTree;
template _STL::_Rb_tree_iterator<WeaponTemplateSetPair, _STL::_Nonconst_traits<WeaponTemplateSetPair> > WeaponTemplateSetTree::insert_unique(_STL::_Rb_tree_iterator<WeaponTemplateSetPair, _STL::_Nonconst_traits<WeaponTemplateSetPair> >, const WeaponTemplateSetPair &);
