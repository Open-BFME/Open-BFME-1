// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/AnimateWindowManager.h
class AnimateWindow
{
};

namespace _STL
{
template <class Type>
class allocator
{
};

template <class Type>
struct _List_node
{
};

template <class Type, class Allocator>
class list
{
protected:
	_List_node<Type> *_M_create_node(Type const &);
};

class AnimateWindowListCreateNodeShim
{
public:
	_List_node<AnimateWindow *> *create_node(AnimateWindow *const &x);
};

template <class Type, class Allocator>
_List_node<Type> *list<Type, Allocator>::_M_create_node(Type const &x)
{
	return (_List_node<Type> *)((AnimateWindowListCreateNodeShim *)this)->create_node((AnimateWindow *const &)x);
}

template _List_node<AnimateWindow *> *list<AnimateWindow *, allocator<AnimateWindow *> >::_M_create_node(AnimateWindow *const &);
}
