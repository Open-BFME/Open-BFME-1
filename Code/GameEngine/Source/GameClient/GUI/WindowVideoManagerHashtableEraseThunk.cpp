// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WindowVideoManager.h
class WindowVideo
{
};

namespace WindowVideoManager
{
struct hashConstGameWindowPtr
{
};
}

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
struct _Const_traits
{
};

template <class Value, class Traits>
struct _Ht_iterator
{
};

template <class T>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/STLTypedefs.h
struct equal_to
{
};

template <class T>
class allocator
{
};

template <class Value, class Key, class Hash, class Extract, class Equal, class Alloc>
class hashtable
{
public:
	void erase(const _Ht_iterator<Value, _Const_traits<Value> > &);
};

class WindowVideoHashtableEraseShim
{
public:
	void erase(const void *it);
};

template <class Value, class Key, class Hash, class Extract, class Equal, class Alloc>
void hashtable<Value, Key, Hash, Extract, Equal, Alloc>::erase(const _Ht_iterator<Value, _Const_traits<Value> > &it)
{
	((WindowVideoHashtableEraseShim *)this)->erase((const void *)&it);
}
}

typedef const GameWindow * GameWindowKey;
typedef _STL::pair<const GameWindowKey, WindowVideo *> GameWindowVideoPair;
typedef _STL::hashtable<GameWindowVideoPair, GameWindowKey, WindowVideoManager::hashConstGameWindowPtr, _STL::_Select1st<GameWindowVideoPair>, _STL::equal_to<GameWindowKey>, _STL::allocator<GameWindowVideoPair> > GameWindowVideoHashtable;
template void GameWindowVideoHashtable::erase(const _STL::_Ht_iterator<GameWindowVideoPair, _STL::_Const_traits<GameWindowVideoPair> > &);
