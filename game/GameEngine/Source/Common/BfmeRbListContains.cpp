// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport

struct BfmeNode1108
{
	char m_pad00[8];
	BfmeNode1108 *m_next;
	char m_pad0c[4];
	int m_value;
};

namespace _STL
{
struct _Rb_tree_node_base;

template <class _Dummy>
class _Rb_global
{
public:
	static _Rb_tree_node_base *__cdecl _M_increment(_Rb_tree_node_base *node);
};
}

class BfmeW1108
{
public:
	bool bfmeGo1108A(int value);

private:
	char m_pad00[0x58];
	BfmeNode1108 *m_head;
};

// ?bfmeGo1108A@BfmeW1108@@QAE_NH@Z
bool BfmeW1108::bfmeGo1108A(int value)
{
	BfmeNode1108 *head = m_head;
	BfmeNode1108 *node = head->m_next;

	while (node != head)
	{
		if (node->m_value == value)
			break;
		node = (BfmeNode1108 *)_STL::_Rb_global<bool>::_M_increment(
			(_STL::_Rb_tree_node_base *)node);
	}

	return node != m_head;
}
