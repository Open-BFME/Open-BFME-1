// cl: /DNDEBUG /DWIN32 /MD /EHsc
// The retail body at RVA 0x00249E10 clears objects, then frees its list nodes.

namespace _STL
{
// The node allocator's pool entry points are private STLport members
// (_STL::__node_alloc<true, 0>::_M_allocate at 0x0082E540, _M_deallocate at
// 0x0082E5F0); these TU-local helpers reach them under their real names.
template <bool __threads, int __inst> class __node_alloc;
static void nodePoolDeallocate(void *block, unsigned int bytes);
template <bool __threads, int __inst>
class __node_alloc
{
	friend void nodePoolDeallocate(void *, unsigned int);
	static void *__cdecl _M_allocate(unsigned int __n);
	static void __cdecl _M_deallocate(void *__p, unsigned int __n);
};
static inline void nodePoolDeallocate(void *block, unsigned int bytes) { __node_alloc<true, 0>::_M_deallocate(block, bytes); }
}

struct Rva00249E10Node
{
	Rva00249E10Node *m_next;
	Rva00249E10Node *m_previous;
	void *m_object;
};

struct Rva00249E10Object
{
	unsigned char m_beforeFlag[0x214];
	int m_flag;
};

class Object;

class GameLogic
{
public:
	void destroyObject(Object *object);
};

class Rva00249E10Owner
{
public:
	unsigned char m_beforeList[0xec];
	Rva00249E10Node *m_list;

	void clearList();
};

extern void j_0002a05e(void);

extern GameLogic *TheGameLogic;

void Rva00249E10Owner::clearList()
{
	typedef void (Rva00249E10Owner::*DeleteBase)(void);
	union
	{
		void (*raw)(void);
		DeleteBase member;
	} deleteBase;
	deleteBase.raw = j_0002a05e;
	(this->*deleteBase.member)();

	Rva00249E10Node *node = m_list->m_next;
	while (node != m_list)
	{
		Rva00249E10Object *object =
			(Rva00249E10Object *)node->m_object;
		node = node->m_next;
		object->m_flag = 0;
		TheGameLogic->destroyObject(reinterpret_cast<Object *>(object));
	}

	node = m_list->m_next;
	while (node != m_list)
	{
		Rva00249E10Node *oldNode = node;
		node = node->m_next;
		_STL::nodePoolDeallocate(oldNode, 0xc);
	}

	m_list->m_next = m_list;
	m_list->m_previous = m_list;
}
