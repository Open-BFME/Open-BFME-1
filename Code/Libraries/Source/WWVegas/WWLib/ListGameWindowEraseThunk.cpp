// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
};

namespace _STL
{
	template <class T>
	class allocator
	{
	};

	template <class T>
	struct _Nonconst_traits
	{
	};

	template <class T, class Traits>
	struct _List_iterator
	{
	};

	template <class Type, class Allocator>
	class list
	{
	public:
		_List_iterator<Type, _Nonconst_traits<Type> > erase(_List_iterator<Type, _Nonconst_traits<Type> >, _List_iterator<Type, _Nonconst_traits<Type> >);
	};

	template <class Type, class Allocator>
	__declspec(naked) _List_iterator<Type, _Nonconst_traits<Type> > list<Type, Allocator>::erase(_List_iterator<Type, _Nonconst_traits<Type> >, _List_iterator<Type, _Nonconst_traits<Type> >)
	{
		__asm {
			_emit 0E9h
			_emit 0DAh
			_emit 0F1h
			_emit 045h
			_emit 000h
		}
	}

	template __declspec(naked) _List_iterator<GameWindow *, _Nonconst_traits<GameWindow *> > list<GameWindow *, allocator<GameWindow *> >::erase(_List_iterator<GameWindow *, _Nonconst_traits<GameWindow *> >, _List_iterator<GameWindow *, _Nonconst_traits<GameWindow *> >);
}
