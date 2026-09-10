// ?rva00591b60@AptPalantirStore@@QAEXXZ
// partial score=0.40 date=2026-09-10
// cl: /O2 /Oy /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
//
// Same field layout as the already-landed AptPalantirStore::clear (0x005918F0):
// m_secondTree at +0x1C, m_firstTree at +0x10, flag at +4, guard fields on a
// global campaign object at +0x2C/+0x2D. When the guard fails it tail-calls
// the real clear().

void clearValue(int value);

namespace _STL
{

template <class Type> class allocator {};
template <class Type> struct _Identity {};
template <class Type> struct less {};

void nodeDeallocate(void *block, unsigned int bytes);

struct _Rb_tree_node_base
{
	int m_color;
	_Rb_tree_node_base *m_parent;
	_Rb_tree_node_base *m_left;
	_Rb_tree_node_base *m_right;
};

template <class Value>
struct _Rb_tree_node : public _Rb_tree_node_base
{
	Value m_value_field;
};

template <class Dummy>
struct _Rb_global
{
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *node);
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree
{
public:
	typedef _Rb_tree_node<Value> Node;

	__forceinline void clear()
	{
		Node *node = (Node *)(void *)m_header->m_left;
		while (node != m_header)
		{
			clearValue(node->m_value_field.m_pod);
			node = (Node *)_Rb_global<bool>::_M_increment(node);
		}

		if (m_node_count != 0)
		{
			_M_erase((Node *)(void *)m_header->m_parent);
			m_header->m_left = m_header;
			m_header->m_parent = 0;
			m_header->m_right = m_header;
			m_node_count = 0;
		}
	}

	unsigned int size() const { return m_node_count; }

private:
	__forceinline void _M_erase(Node *node);

	_Rb_tree_node_base *m_header;
	unsigned int m_node_count;
	Compare m_key_compare;
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
__forceinline void _Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::_M_erase(Node *node)
{
	while (node != 0)
	{
		_M_erase((Node *)(void *)node->m_right);
		Node *left = (Node *)(void *)node->m_left;
		nodeDeallocate(node, sizeof(Node));
		node = left;
	}
}

}

struct Gen_t_00234730_m4pod
{
	int m_pod;
};

typedef _STL::_Rb_tree<
	Gen_t_00234730_m4pod,
	Gen_t_00234730_m4pod,
	_STL::_Identity<Gen_t_00234730_m4pod>,
	_STL::less<Gen_t_00234730_m4pod>,
	_STL::allocator<Gen_t_00234730_m4pod> > AptPalantirStoreTree;

struct Rva00591B60Guard
{
	unsigned char m_pad[0x2C];
	unsigned char m_flag2C;
	unsigned char m_flag2D;
};

extern Rva00591B60Guard *g_rva00591b60Guard;

class AptPalantirStore
{
public:
	void clear();
	void rva00591b60();

private:
	unsigned int m_value00;
	bool m_flag04;
	unsigned char m_padding05[3];
	int m_value08;
	int m_value0c;
	AptPalantirStoreTree m_firstTree;
	AptPalantirStoreTree m_secondTree;
};

void AptPalantirStore::rva00591b60()
{
	if (!m_flag04)
		return;

	Rva00591B60Guard *guard = g_rva00591b60Guard;
	if (guard == 0 || !guard->m_flag2C || !guard->m_flag2D)
	{
		clear();
		return;
	}

	m_secondTree.clear();

	bool notEmpty = (m_value08 != 0) || (m_firstTree.size() != 0);
	m_flag04 = notEmpty;
	if (!notEmpty)
		m_value00 = 0;
}
