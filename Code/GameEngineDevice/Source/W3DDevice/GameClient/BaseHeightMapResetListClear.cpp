// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

class BaseHeightMapResetList;

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
		friend class ::BaseHeightMapResetList;
		void _M_erase(_Rb_tree_node<Value> *node);
	};
}

typedef _STL::pair<const int, Gen_t_0094c800_p16cd> BaseHeightMapResetPair;
typedef _STL::_Rb_tree<int, BaseHeightMapResetPair,
	_STL::_Select1st<BaseHeightMapResetPair>, _STL::less<int>,
	_STL::allocator<BaseHeightMapResetPair> > BaseHeightMapResetTree;
typedef _STL::_Rb_tree_node<BaseHeightMapResetPair> BaseHeightMapResetNode;

class BaseHeightMapResetList
{
	char m_prefix[8];
	BaseHeightMapResetNode *m_head;
	BaseHeightMapResetNode *m_tail;
	char m_padding10[12];
	bool m_changed;
	bool m_reset;

public:
	void clear(bool reset);
};

void BaseHeightMapResetList::clear(bool reset)
{
	BaseHeightMapResetTree *tree =
		reinterpret_cast<BaseHeightMapResetTree *>(&m_head);
	if (*reinterpret_cast<BaseHeightMapResetNode **>(
		reinterpret_cast<char *>(tree) + 4) != 0) {
		BaseHeightMapResetNode *node =
			*reinterpret_cast<BaseHeightMapResetNode **>(tree);
		tree->_M_erase(*reinterpret_cast<BaseHeightMapResetNode **>(
			reinterpret_cast<char *>(node) + 4));
		node = *reinterpret_cast<BaseHeightMapResetNode **>(tree);
		*reinterpret_cast<BaseHeightMapResetNode **>(
			reinterpret_cast<char *>(node) + 8) = node;
		node = *reinterpret_cast<BaseHeightMapResetNode **>(tree);
		*reinterpret_cast<BaseHeightMapResetNode **>(
			reinterpret_cast<char *>(node) + 4) = 0;
		node = *reinterpret_cast<BaseHeightMapResetNode **>(tree);
		*reinterpret_cast<BaseHeightMapResetNode **>(
			reinterpret_cast<char *>(node) + 12) = node;
		*reinterpret_cast<BaseHeightMapResetNode **>(
			reinterpret_cast<char *>(tree) + 4) = 0;
	}
	m_reset = reset;
	m_changed = true;
}
