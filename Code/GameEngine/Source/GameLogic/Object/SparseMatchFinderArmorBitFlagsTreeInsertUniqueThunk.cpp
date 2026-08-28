template<int Bits>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
};
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ArmorSet.h
class ArmorTemplateSet
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
        _emit 049h
        _emit 02Dh
        _emit 013h
        _emit 000h
    }
}
}

typedef BitFlags<11> ArmorFlags;
typedef SparseMatchFinder<ArmorTemplateSet, ArmorFlags> ArmorFinder;
typedef ArmorFinder::MapHelper ArmorMapHelper;
typedef _STL::pair<const ArmorFlags, const ArmorTemplateSet *> ArmorPair;
typedef _STL::_Rb_tree<const ArmorFlags, ArmorPair, _STL::_Select1st<ArmorPair>, ArmorMapHelper, _STL::allocator<ArmorPair> > ArmorTree;
template _STL::_Rb_tree_iterator<ArmorPair, _STL::_Nonconst_traits<ArmorPair> > ArmorTree::insert_unique(ArmorTree::iterator, ArmorPair const &);
