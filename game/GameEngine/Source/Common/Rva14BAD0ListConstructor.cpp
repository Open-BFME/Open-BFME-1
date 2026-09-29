namespace _STL
{
// The node allocator's pool entry points are private STLport members
// (_STL::__node_alloc<true, 0>::_M_allocate at 0x0082E540, _M_deallocate at
// 0x0082E5F0); these TU-local helpers reach them under their real names.
template <bool __threads, int __inst> class __node_alloc;
static void *vectorSmallAllocate(unsigned int bytes);
template <bool __threads, int __inst>
class __node_alloc
{
	friend void *vectorSmallAllocate(unsigned int);
	static void *__cdecl _M_allocate(unsigned int __n);
	static void __cdecl _M_deallocate(void *__p, unsigned int __n);
};
static inline void *vectorSmallAllocate(unsigned int bytes) { return __node_alloc<true, 0>::_M_allocate(bytes); }
}

struct Rva14BAD0ListNode
{
    Rva14BAD0ListNode *next;
    Rva14BAD0ListNode *previous;
    int value;
};

struct Rva14BAD0List
{
    Rva14BAD0ListNode *head;

    Rva14BAD0List(int unused);
    Rva14BAD0List *initialize(char *flag, int value);
};

// ?d_0014bad0@@YAXXZ
Rva14BAD0List::Rva14BAD0List(int)
{
    char flag;
    initialize(&flag, 0);

    Rva14BAD0ListNode *sentinel = static_cast<Rva14BAD0ListNode *>(_STL::vectorSmallAllocate(12));
    sentinel->next = sentinel;
    sentinel->previous = sentinel;
    head = sentinel;
}
