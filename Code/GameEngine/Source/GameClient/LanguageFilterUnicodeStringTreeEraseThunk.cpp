// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/LanguageFilter.h
struct UnicodeStringLessThan
{
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
	void _M_erase(_Rb_tree_node<Value> *);
};

class UnicodeStringTreeEraseShim
{
public:
	void erase(_Rb_tree_node<pair<const UnicodeString, bool> > *node);
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
void _Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::_M_erase(_Rb_tree_node<Value> *node)
{
	((UnicodeStringTreeEraseShim *)this)->erase((_Rb_tree_node<pair<const UnicodeString, bool> > *)node);
}
}

typedef _STL::pair<const UnicodeString, bool> UnicodeStringBoolPair;
typedef _STL::_Rb_tree<UnicodeString, UnicodeStringBoolPair, _STL::_Select1st<UnicodeStringBoolPair>, UnicodeStringLessThan, _STL::allocator<UnicodeStringBoolPair> > UnicodeStringTree;
template void UnicodeStringTree::_M_erase(_STL::_Rb_tree_node<UnicodeStringBoolPair> *);
