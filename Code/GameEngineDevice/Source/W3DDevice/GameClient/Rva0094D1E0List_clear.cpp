// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Rva0094D1E0List::clear, retail 0x0094CE50: the list members of both tree buffers
// (+0xC0/+0xE8 and +0x1458/+0x1480); the constructor is at 0x0094D1E0.

class Rva0094D1E0List;

struct Gen_t_0094c800_p16cd
{
	int body[4];
};

namespace _STL
{
	template <class First, class Second> struct pair;
	template <class Value> struct _Select1st;
	template <class Key> struct less;
	template <class Value> class allocator;
	template <class Value> struct _Rb_tree_node;

	template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	class _Rb_tree
	{
		friend class ::Rva0094D1E0List;
		void _M_erase(_Rb_tree_node<Value> *node);
	};
}

typedef _STL::pair<const int, Gen_t_0094c800_p16cd> Rva0094D1E0ListPair;
typedef _STL::_Rb_tree<int, Rva0094D1E0ListPair,
	_STL::_Select1st<Rva0094D1E0ListPair>, _STL::less<int>,
	_STL::allocator<Rva0094D1E0ListPair> > Rva0094D1E0ListTree;
typedef _STL::_Rb_tree_node<Rva0094D1E0ListPair> Rva0094D1E0ListNode;

class Rva0094D1E0List
{
	char m_prefix[8];
	Rva0094D1E0ListNode *m_head;
	Rva0094D1E0ListNode *m_tail;
	char m_padding10[12];
	bool m_changed;
	bool m_reset;

public:
	void clear(bool reset);
};

void Rva0094D1E0List::clear(bool reset)
{
	Rva0094D1E0ListTree *tree =
		reinterpret_cast<Rva0094D1E0ListTree *>(&m_head);
	if (*reinterpret_cast<Rva0094D1E0ListNode **>(
		reinterpret_cast<char *>(tree) + 4) != 0) {
		Rva0094D1E0ListNode *node =
			*reinterpret_cast<Rva0094D1E0ListNode **>(tree);
		tree->_M_erase(*reinterpret_cast<Rva0094D1E0ListNode **>(
			reinterpret_cast<char *>(node) + 4));
		node = *reinterpret_cast<Rva0094D1E0ListNode **>(tree);
		*reinterpret_cast<Rva0094D1E0ListNode **>(
			reinterpret_cast<char *>(node) + 8) = node;
		node = *reinterpret_cast<Rva0094D1E0ListNode **>(tree);
		*reinterpret_cast<Rva0094D1E0ListNode **>(
			reinterpret_cast<char *>(node) + 4) = 0;
		node = *reinterpret_cast<Rva0094D1E0ListNode **>(tree);
		*reinterpret_cast<Rva0094D1E0ListNode **>(
			reinterpret_cast<char *>(node) + 12) = node;
		*reinterpret_cast<Rva0094D1E0ListNode **>(
			reinterpret_cast<char *>(tree) + 4) = 0;
	}
	m_reset = reset;
	m_changed = true;
}
