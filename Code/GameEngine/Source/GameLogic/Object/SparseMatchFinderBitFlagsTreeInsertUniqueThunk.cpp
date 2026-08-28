template<int Bits>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
};
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/WeaponSet.h
class WeaponTemplateSet
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
template<class First, class Second> struct pair { };
template<class T> struct _Select1st { };
template<class T> class allocator { };
template<class T> struct _Nonconst_traits { };
template<class T, class Traits> struct _Rb_tree_iterator { };

template<class Key, class Value, class Select, class Compare, class Allocator>
class _Rb_tree
{
public:
    typedef _Rb_tree_iterator<Value, _Nonconst_traits<Value> > iterator;
    iterator insert_unique(iterator, Value const &);
};

template<class Key, class Value, class Select, class Compare, class Allocator>
__declspec(naked) typename _Rb_tree<Key, Value, Select, Compare, Allocator>::iterator _Rb_tree<Key, Value, Select, Compare, Allocator>::insert_unique(iterator, Value const &)
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

typedef BitFlags<187> WeaponFlags;
typedef SparseMatchFinder<WeaponTemplateSet, WeaponFlags> WeaponFinder;
typedef WeaponFinder::MapHelper WeaponMapHelper;
typedef _STL::pair<const WeaponFlags, const WeaponTemplateSet *> WeaponPair;
typedef _STL::_Rb_tree<const WeaponFlags, WeaponPair, _STL::_Select1st<WeaponPair>, WeaponMapHelper, _STL::allocator<WeaponPair> > WeaponTree;
template _STL::_Rb_tree_iterator<WeaponPair, _STL::_Nonconst_traits<WeaponPair> > WeaponTree::insert_unique(WeaponTree::iterator, WeaponPair const &);
