// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ArmorSet.h
class ArmorTemplateSet
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
        _emit 049h
        _emit 02Dh
        _emit 013h
        _emit 000h
    }
}
}

typedef BitFlags<11> ArmorSetFlags;
typedef _STL::pair<const ArmorSetFlags, const ArmorTemplateSet *> ArmorTemplateSetPair;
typedef SparseMatchFinder<ArmorTemplateSet, ArmorSetFlags>::MapHelper ArmorTemplateSetMapHelper;
typedef _STL::_Rb_tree<const ArmorSetFlags, ArmorTemplateSetPair, _STL::_Select1st<ArmorTemplateSetPair>, ArmorTemplateSetMapHelper, _STL::allocator<ArmorTemplateSetPair> > ArmorTemplateSetTree;
template _STL::_Rb_tree_iterator<ArmorTemplateSetPair, _STL::_Nonconst_traits<ArmorTemplateSetPair> > ArmorTemplateSetTree::insert_unique(_STL::_Rb_tree_iterator<ArmorTemplateSetPair, _STL::_Nonconst_traits<ArmorTemplateSetPair> >, const ArmorTemplateSetPair &);
