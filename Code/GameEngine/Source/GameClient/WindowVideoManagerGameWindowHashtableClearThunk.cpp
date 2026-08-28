// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
};
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WindowVideoManager.h
class WindowVideo
{
};
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WindowVideoManager.h
class WindowVideoManager
{
public:
	struct hashConstGameWindowPtr
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
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/STLTypedefs.h
struct equal_to
{
};
template <class T>
class allocator
{
};

template <class Value, class Key, class Hash, class Select, class Equal, class Alloc>
class hashtable
{
private:
	void clear();
};

class GameWindowHashtableClearShim
{
public:
	void clear();
};

template <class Value, class Key, class Hash, class Select, class Equal, class Alloc>
void hashtable<Value, Key, Hash, Select, Equal, Alloc>::clear()
{
	((GameWindowHashtableClearShim *)this)->clear();
}
}

typedef _STL::pair<const GameWindow *, WindowVideo *> GameWindowVideoPair;
typedef _STL::hashtable<GameWindowVideoPair, const GameWindow *, WindowVideoManager::hashConstGameWindowPtr, _STL::_Select1st<GameWindowVideoPair>, _STL::equal_to<const GameWindow *>, _STL::allocator<GameWindowVideoPair> > GameWindowVideoHashtable;
template void GameWindowVideoHashtable::clear();
