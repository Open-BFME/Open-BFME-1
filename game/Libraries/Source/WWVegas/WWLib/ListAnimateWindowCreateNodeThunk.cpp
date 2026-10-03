// The mangled name types the return as a node pointer but retail's 5-byte
// body is a bare tail jump to the void push-back below, so the missing
// return has to be allowed through rather than invented.
#pragma warning(disable : 4716)

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/AnimateWindowManager.h
class AnimateWindow
{
};

// Retail 0x0045DAE0 (game/GameEngine/Source/GameClient/GUI/AnimateWindowManager.cpp):
// BFME compiled list<AnimateWindow*>::push_back out-of-line in that TU under
// this derived-wrapper name; this thunk (retail 0x00022D36) tail-jumps to it.
struct BFMEAnimateWindowListPush
{
	void bfmePushBack(AnimateWindow *const &x);
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

template <class Type, class Allocator>
_List_node<Type> *list<Type, Allocator>::_M_create_node(Type const &x)
{
	((BFMEAnimateWindowListPush *)this)->bfmePushBack((AnimateWindow *const &)x);
}

template _List_node<AnimateWindow *> *list<AnimateWindow *, allocator<AnimateWindow *> >::_M_create_node(AnimateWindow *const &);
}
