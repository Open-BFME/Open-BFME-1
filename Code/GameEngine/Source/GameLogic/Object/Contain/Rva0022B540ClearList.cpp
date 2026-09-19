// cl: /DNDEBUG /DWIN32 /MD /EHsc
// The retail body at RVA 0x0022B540 clears objects, then frees its list nodes.

namespace _STL
{
template<int A, int B> class __node_alloc
{
public:
	static void _M_deallocate(void *node, unsigned int size);
};
}

struct Rva0022B540Node
{
	Rva0022B540Node *m_next;
	Rva0022B540Node *m_previous;
	void *m_object;
};

struct Rva0022B540Object
{
	unsigned char m_beforeFlag[0x214];
	int m_flag;
};

class BfmeGlob940E
{
public:
	void bfmeCall940E(void *object);
};

class Rva0022B540Owner
{
public:
	unsigned char m_beforeList[0xe4];
	Rva0022B540Node *m_list;

	void clearList();
};

extern void j_0002a05e(void);

#define TheGameLogic (*(BfmeGlob940E **)0x012F0898)

void Rva0022B540Owner::clearList()
{
	typedef void (Rva0022B540Owner::*DeleteBase)(void);
	union
	{
		void (*raw)(void);
		DeleteBase member;
	} deleteBase;
	deleteBase.raw = j_0002a05e;
	(this->*deleteBase.member)();

	Rva0022B540Node *node = m_list->m_next;
	while (node != m_list)
	{
		Rva0022B540Object *object =
			(Rva0022B540Object *)node->m_object;
		node = node->m_next;
		object->m_flag = 0;
		TheGameLogic->bfmeCall940E(object);
	}

	node = m_list->m_next;
	while (node != m_list)
	{
		Rva0022B540Node *oldNode = node;
		node = node->m_next;
		_STL::__node_alloc<1, 0>::_M_deallocate(oldNode, 0xc);
	}

	m_list->m_next = m_list;
	m_list->m_previous = m_list;
}
