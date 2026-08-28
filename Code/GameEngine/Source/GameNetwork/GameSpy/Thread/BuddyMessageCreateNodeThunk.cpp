// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: list<BuddyMessage>::_M_create_node
// Retail: operator new(0x20); construct value at +8; return node.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PeerDefs.h
class BuddyMessage
{
};

void *__cdecl operator new(unsigned int);
void __cdecl constructBuddyMessageAt(void *dest, BuddyMessage const &src);

namespace _STL
{
template <class Type>
class allocator
{
};

template <class Type>
struct _List_node
{
	void *next;
	void *prev;
	// Type value at +8 (BuddyMessage sized so total node is 0x20)
	char value_space[0x18];
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
	_List_node<Type> *node =
		(_List_node<Type> *)operator new(0x20);
	constructBuddyMessageAt((char *)node + 8, (BuddyMessage const &)x);
	return node;
}

template _List_node<BuddyMessage> *list<BuddyMessage, allocator<BuddyMessage> >::_M_create_node(BuddyMessage const &);
}
