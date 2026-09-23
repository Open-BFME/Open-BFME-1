// ?d_0024aba0@@YAXXZ
// partial score=0.12 date=2026-09-23
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

struct Object
{
	unsigned char m_unmodelled[0x74];
	unsigned int m_dword74;
};

struct Rva0024ABA0Pair
{
	unsigned char m_first;
	unsigned char m_second;
};

class Rva0024ABA0Target
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual bool slot08();
	virtual void slot0c();
	virtual bool slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28(Rva0024ABA0Pair *pair);
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3c();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4c();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5c();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void slot6c();
	virtual void slot70();
	virtual void value74(void *value);
	virtual void value78(void *value);
	virtual void slot7c();
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void value8c(void *value);
};

class Rva0024ABA0ListNode
{
public:
	Rva0024ABA0ListNode *m_next;
	Rva0024ABA0ListNode *m_prev;
	Object *m_object;
};

class Rva0024ABA0ValueNode
{
public:
	Rva0024ABA0ValueNode *m_next;
	Rva0024ABA0ValueNode *m_prev;
	int m_value;
};

class Rva0024ABA0List
{
public:
	void clear();
	Rva0024ABA0ListNode *m_head;
};

#pragma comment(linker, "/alternatename:?clear@Rva0024ABA0List@@QAEXXZ=?j_0002fb8a@@YAXXZ")

namespace _STL
{
struct _Rb_tree_node_base
{
	bool color;
	_Rb_tree_node_base *parent;
	_Rb_tree_node_base *left;
	_Rb_tree_node_base *right;
};

template <class Dummy>
struct _Rb_global
{
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *node);
};

template <bool Threads, int Instance>
class __node_alloc
{
public:
	static void _M_deallocate(void *node, unsigned int bytes);
};

class __new_alloc
{
public:
	static void *allocate(unsigned int bytes);
};
}

class Rva0024ABA0MapNode
{
public:
	_STL::_Rb_tree_node_base m_base;
	int m_first;
	int m_second;
};

class Rva0024ABA0Map
{
public:
	int &lookup(const int &key);
	_STL::_Rb_tree_node_base *m_header;
	unsigned int m_count;
	unsigned int m_compare;
};

#pragma comment(linker, "/alternatename:?lookup@Rva0024ABA0Map@@QAEAAHABH@Z=?j_0001f91f@@YAXXZ")

class Rva00367E30Logic
{
public:
	void destroyObject(Object *object);
};

extern Rva00367E30Logic *TheBfmeGameLogic;

#pragma comment(linker, "/alternatename:?destroyObject@Rva00367E30Logic@@QAEXPAVObject@@@Z=?j_0001d0de@@YAXXZ")

void Rva0024ABA0Dispatch(Rva0024ABA0Target *target, void *context);

#pragma comment(linker, "/alternatename:?Rva0024ABA0Dispatch@@YAXPAVRva0024ABA0Target@@PAX@Z=?j_0000c9b4@@YAXXZ")

class Rva0024ABA0
{
public:
	void seed(Rva0024ABA0Target *target);
	void method(Rva0024ABA0Target *target);

	char m_unmodelled000[0xec];
	Rva0024ABA0List m_listA;
	int m_valueF0;
	unsigned char m_valueF4;
	unsigned char m_unmodelledF5[3];
	Rva0024ABA0Map m_map;
	Rva0024ABA0ValueNode *m_listB;
};

#pragma comment(linker, "/alternatename:?seed@Rva0024ABA0@@QAEXPAVRva0024ABA0Target@@@Z=?j_00038596@@YAXXZ")

void Rva0024ABA0::method(Rva0024ABA0Target *target)
{
	seed(target);
	if (target->slot10())
		return;
	if (target->slot08())
	{
		target->value74(&m_valueF0);
		Rva0024ABA0ListNode *head = m_listA.m_head;
		for (Rva0024ABA0ListNode *node = head->m_next; node != head; node = node->m_next)
		{
			unsigned int value = node->m_object->m_dword74;
			Rva0024ABA0Dispatch(target, &value);
		}
	}
	else
	{
		Rva0024ABA0ListNode *head = m_listA.m_head;
		if (head->m_next != head)
		{
			m_valueF0 = 0;
			Rva0024ABA0ListNode *node = head->m_next;
			while (node != head)
			{
				Object *object = node->m_object;
				Rva0024ABA0ListNode *next = node->m_next;
				Rva0024ABA0ListNode *previous = node->m_prev;
				previous->m_next = next;
				next->m_prev = previous;
				_STL::__node_alloc<false, 10>::_M_deallocate(node, 12);
				TheBfmeGameLogic->destroyObject(object);
				node = next;
			}
		}

		m_listA.clear();
		target->value74(&m_valueF0);
		if (m_valueF0 > 0)
		{
			for (int i = 0; i < m_valueF0; ++i)
			{
				int value;
				Rva0024ABA0Dispatch(target, &value);
				Rva0024ABA0ValueNode *node = (Rva0024ABA0ValueNode *)_STL::__new_alloc::allocate(12);
				if (&node->m_value != 0)
					node->m_value = value;
				Rva0024ABA0ValueNode *headB = m_listB;
				Rva0024ABA0ValueNode *tail = headB->m_prev;
				node->m_next = headB;
				node->m_prev = tail;
				tail->m_next = node;
				headB->m_prev = node;
			}
		}
	}

	target->value8c(&m_valueF4);
	if (target->slot08())
	{
		target->value78(&m_map.m_count);
		_STL::_Rb_tree_node_base *sentinel = m_map.m_header;
		_STL::_Rb_tree_node_base *base = sentinel->left;
		while (base != sentinel)
		{
			Rva0024ABA0MapNode *node = (Rva0024ABA0MapNode *)base;
			int values[2];
			values[0] = node->m_first;
			values[1] = node->m_second;
			Rva0024ABA0Dispatch(target, values);
			target->value78(&values[1]);
			m_map.lookup(values[1]) = values[0];
			base = _STL::_Rb_global<bool>::_M_increment(base);
		}
	}
	else
	{
		target->value78(&m_map.m_count);
		if (m_map.m_count <= 0)
			return;
		for (unsigned int i = 0; i < m_map.m_count; ++i)
		{
			int key;
			Rva0024ABA0Dispatch(target, &key);
			int value;
			target->value78(&value);
			m_map.lookup(key) = value;
		}
	}
}
