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
struct less
{
};

template<class T>
class allocator
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
        _emit 0D4h
        _emit 0A2h
        _emit 065h
        _emit 000h
    }
}
}

typedef _STL::pair<const unsigned short, unsigned char> UnsignedShortBytePair;
typedef _STL::_Rb_tree<unsigned short, UnsignedShortBytePair, _STL::_Select1st<UnsignedShortBytePair>, _STL::less<unsigned short>, _STL::allocator<UnsignedShortBytePair> > UnsignedShortByteTree;
template _STL::_Rb_tree_iterator<UnsignedShortBytePair, _STL::_Nonconst_traits<UnsignedShortBytePair> > UnsignedShortByteTree::insert_unique(_STL::_Rb_tree_iterator<UnsignedShortBytePair, _STL::_Nonconst_traits<UnsignedShortBytePair> >, const UnsignedShortBytePair &);
