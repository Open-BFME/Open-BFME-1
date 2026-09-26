// cl: /O2 /Oy /DNDEBUG /MD /EHsc
// Retail 0x003B92D0 clears nested red-black trees and releases their values.

namespace _STL
{

template <int Threads, int Instance>
class __node_alloc
{
public:
	static void _M_deallocate(void *node, unsigned int size);
};

struct _Rb_tree_node_base
{
	int m_color;
	_Rb_tree_node_base *m_parent;
	_Rb_tree_node_base *m_left;
	_Rb_tree_node_base *m_right;
};

template <class Dummy>
struct _Rb_global
{
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *node);
};

template <class Value>
struct _Rb_tree_node : public _Rb_tree_node_base
{
	Value m_value_field;
};

template <class Type>
struct _Identity
{
};

template <class Type>
struct less
{
};

template <class Type>
class allocator
{
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree
{
public:
	typedef _Rb_tree_node<Value> Node;

	__forceinline void clear()
	{
		if (m_node_count != 0)
		{
			Node *node = (Node *)(void *)m_header->m_parent;
			if (node != 0)
			{
				do
				{
					_M_erase((Node *)(void *)node->m_right);
					Node *left = (Node *)(void *)node->m_left;
					__node_alloc<true, 0>::_M_deallocate(node, 0x14);
					node = left;
				} while (node != 0);
			}
			m_header->m_left = m_header;
			m_header->m_parent = 0;
			m_header->m_right = m_header;
			m_node_count = 0;
		}
	}

	_Rb_tree_node_base *m_header;
	unsigned int m_node_count;
	int m_compare;

private:
	void _M_erase(Node *node);
};

}

template <class Value>
class Rva003B92D0Vector
{
public:
	unsigned int size() const { return m_finish - m_start; }
	Value *begin() const { return m_start; }

	Value *m_start;
	Value *m_finish;
	Value *m_end;
};

struct Gen_t_00234730_m4pod
{
	void *m_object;
};

class Rva003B92D0Ref
{
public:
	virtual void release();
#define RVA003B92D0_REF_SLOT(n) virtual void slot##n();
	RVA003B92D0_REF_SLOT(1)
	RVA003B92D0_REF_SLOT(2)
	RVA003B92D0_REF_SLOT(3)
	RVA003B92D0_REF_SLOT(4)
	RVA003B92D0_REF_SLOT(5)
	RVA003B92D0_REF_SLOT(6)
	RVA003B92D0_REF_SLOT(7)
	RVA003B92D0_REF_SLOT(8)
	RVA003B92D0_REF_SLOT(9)
	RVA003B92D0_REF_SLOT(10)
	RVA003B92D0_REF_SLOT(11)
	RVA003B92D0_REF_SLOT(12)
	RVA003B92D0_REF_SLOT(13)
	RVA003B92D0_REF_SLOT(14)
	RVA003B92D0_REF_SLOT(15)
	RVA003B92D0_REF_SLOT(16)
	RVA003B92D0_REF_SLOT(17)
	RVA003B92D0_REF_SLOT(18)
	RVA003B92D0_REF_SLOT(19)
	RVA003B92D0_REF_SLOT(20)
	RVA003B92D0_REF_SLOT(21)
	RVA003B92D0_REF_SLOT(22)
	RVA003B92D0_REF_SLOT(23)
	RVA003B92D0_REF_SLOT(24)
	RVA003B92D0_REF_SLOT(25)
	RVA003B92D0_REF_SLOT(26)
	RVA003B92D0_REF_SLOT(27)
	RVA003B92D0_REF_SLOT(28)
	RVA003B92D0_REF_SLOT(29)
	RVA003B92D0_REF_SLOT(30)
	RVA003B92D0_REF_SLOT(31)
	RVA003B92D0_REF_SLOT(32)
	RVA003B92D0_REF_SLOT(33)
	RVA003B92D0_REF_SLOT(34)
	RVA003B92D0_REF_SLOT(35)
	RVA003B92D0_REF_SLOT(36)
	RVA003B92D0_REF_SLOT(37)
	RVA003B92D0_REF_SLOT(38)
	RVA003B92D0_REF_SLOT(39)
	RVA003B92D0_REF_SLOT(40)
	RVA003B92D0_REF_SLOT(41)
	RVA003B92D0_REF_SLOT(42)
	RVA003B92D0_REF_SLOT(43)
	RVA003B92D0_REF_SLOT(44)
	RVA003B92D0_REF_SLOT(45)
	RVA003B92D0_REF_SLOT(46)
	RVA003B92D0_REF_SLOT(47)
	RVA003B92D0_REF_SLOT(48)
	RVA003B92D0_REF_SLOT(49)
	RVA003B92D0_REF_SLOT(50)
	RVA003B92D0_REF_SLOT(51)
	RVA003B92D0_REF_SLOT(52)
	RVA003B92D0_REF_SLOT(53)
	RVA003B92D0_REF_SLOT(54)
	RVA003B92D0_REF_SLOT(55)
	RVA003B92D0_REF_SLOT(56)
	RVA003B92D0_REF_SLOT(57)
	RVA003B92D0_REF_SLOT(58)
	RVA003B92D0_REF_SLOT(59)
	RVA003B92D0_REF_SLOT(60)
	RVA003B92D0_REF_SLOT(61)
	RVA003B92D0_REF_SLOT(62)
	RVA003B92D0_REF_SLOT(63)
	RVA003B92D0_REF_SLOT(64)
	RVA003B92D0_REF_SLOT(65)
	RVA003B92D0_REF_SLOT(66)
	RVA003B92D0_REF_SLOT(67)
	RVA003B92D0_REF_SLOT(68)
	RVA003B92D0_REF_SLOT(69)
	RVA003B92D0_REF_SLOT(70)
	RVA003B92D0_REF_SLOT(71)
	RVA003B92D0_REF_SLOT(72)
	RVA003B92D0_REF_SLOT(73)
	RVA003B92D0_REF_SLOT(74)
	RVA003B92D0_REF_SLOT(75)
	RVA003B92D0_REF_SLOT(76)
	RVA003B92D0_REF_SLOT(77)
	RVA003B92D0_REF_SLOT(78)
	RVA003B92D0_REF_SLOT(79)
	RVA003B92D0_REF_SLOT(80)
	RVA003B92D0_REF_SLOT(81)
	RVA003B92D0_REF_SLOT(82)
	RVA003B92D0_REF_SLOT(83)
	RVA003B92D0_REF_SLOT(84)
	RVA003B92D0_REF_SLOT(85)
	RVA003B92D0_REF_SLOT(86)
	RVA003B92D0_REF_SLOT(87)
	RVA003B92D0_REF_SLOT(88)
	RVA003B92D0_REF_SLOT(89)
	RVA003B92D0_REF_SLOT(90)
	RVA003B92D0_REF_SLOT(91)
	RVA003B92D0_REF_SLOT(92)
	RVA003B92D0_REF_SLOT(93)
	RVA003B92D0_REF_SLOT(94)
	RVA003B92D0_REF_SLOT(95)
	RVA003B92D0_REF_SLOT(96)
	RVA003B92D0_REF_SLOT(97)
	RVA003B92D0_REF_SLOT(98)
	RVA003B92D0_REF_SLOT(99)
	virtual void addReference(int value);
#undef RVA003B92D0_REF_SLOT

	int m_references;
};

class Rva003B92D0Owner
{
public:
#define RVA003B92D0_OWNER_SLOT(n) virtual void slot##n();
	RVA003B92D0_OWNER_SLOT(0)
	RVA003B92D0_OWNER_SLOT(1)
	RVA003B92D0_OWNER_SLOT(2)
	RVA003B92D0_OWNER_SLOT(3)
	RVA003B92D0_OWNER_SLOT(4)
	RVA003B92D0_OWNER_SLOT(5)
	RVA003B92D0_OWNER_SLOT(6)
	RVA003B92D0_OWNER_SLOT(7)
	RVA003B92D0_OWNER_SLOT(8)
	RVA003B92D0_OWNER_SLOT(9)
	RVA003B92D0_OWNER_SLOT(10)
	RVA003B92D0_OWNER_SLOT(11)
	RVA003B92D0_OWNER_SLOT(12)
	RVA003B92D0_OWNER_SLOT(13)
	RVA003B92D0_OWNER_SLOT(14)
	RVA003B92D0_OWNER_SLOT(15)
	RVA003B92D0_OWNER_SLOT(16)
	RVA003B92D0_OWNER_SLOT(17)
	RVA003B92D0_OWNER_SLOT(18)
	RVA003B92D0_OWNER_SLOT(19)
	RVA003B92D0_OWNER_SLOT(20)
	RVA003B92D0_OWNER_SLOT(21)
	RVA003B92D0_OWNER_SLOT(22)
	RVA003B92D0_OWNER_SLOT(23)
	RVA003B92D0_OWNER_SLOT(24)
	RVA003B92D0_OWNER_SLOT(25)
	RVA003B92D0_OWNER_SLOT(26)
	RVA003B92D0_OWNER_SLOT(27)
	RVA003B92D0_OWNER_SLOT(28)
	virtual Rva003B92D0Ref *releaseValue(void *value);
#undef RVA003B92D0_OWNER_SLOT
};

typedef _STL::_Rb_tree<
	Gen_t_00234730_m4pod,
	Gen_t_00234730_m4pod,
	_STL::_Identity<Gen_t_00234730_m4pod>,
	_STL::less<Gen_t_00234730_m4pod>,
	_STL::allocator<Gen_t_00234730_m4pod> > Rva003B92D0TreeType;

struct Rva003B92D0Element
{
	int m_key;
	Rva003B92D0Owner *m_owner;
	Rva003B92D0TreeType m_tree;
};

class Rva003B92D0
{
public:
	void clear(bool force);

private:
	char m_pad00[0x14];
	Rva003B92D0Vector<Rva003B92D0Element> m_items;
	bool m_active;
	bool m_initialized;
};

void Rva003B92D0::clear(bool force)
{
	m_active = false;
	if (!m_initialized && !force)
		return;

	int index;
	index = 0;
	if (m_items.size() != 0)
	{
		do
		{
			_STL::_Rb_tree_node_base *node =
				m_items.begin()[index].m_tree.m_header->m_left;
			while (node != m_items.begin()[index].m_tree.m_header)
			{
				Rva003B92D0Ref *value =
					m_items.begin()[index].m_owner->releaseValue(
						((_STL::_Rb_tree_node<Gen_t_00234730_m4pod> *)node)->m_value_field.m_object);
				if (value != 0)
				{
					value->addReference(1);
					if (--value->m_references == 0)
						value->release();
				}
				node = _STL::_Rb_global<bool>::_M_increment(node);
			}
			m_items.begin()[index].m_tree.clear();
			++index;
		} while (index < m_items.size());
	}
}
