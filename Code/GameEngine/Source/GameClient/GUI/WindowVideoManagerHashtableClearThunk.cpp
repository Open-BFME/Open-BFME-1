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
	void clear();
};

class WindowVideoHashtableClearShim
{
public:
	void clear();
};

template <class Value, class Key, class Hash, class Extract, class Equal, class Alloc>
void hashtable<Value, Key, Hash, Extract, Equal, Alloc>::clear()
{
	((WindowVideoHashtableClearShim *)this)->clear();
}
}

typedef const GameWindow * GameWindowKey;
typedef _STL::pair<const GameWindowKey, WindowVideo *> GameWindowVideoPair;
typedef _STL::hashtable<GameWindowVideoPair, GameWindowKey, WindowVideoManager::hashConstGameWindowPtr, _STL::_Select1st<GameWindowVideoPair>, _STL::equal_to<GameWindowKey>, _STL::allocator<GameWindowVideoPair> > GameWindowVideoHashtable;
template void GameWindowVideoHashtable::clear();
