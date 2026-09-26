// Open-BFME5 conversion.

struct BfmeNode1109B
{
	char m_bfmePad[8];
	BfmeNode1109B *m_bfme08;
	char m_bfmePad1[4];
	void *m_bfme10;
};

namespace _STL
{
struct _Rb_tree_node_base
{
	char m_color;
	_Rb_tree_node_base *m_parent;
	_Rb_tree_node_base *m_left;
	_Rb_tree_node_base *m_right;
};

template <class T>
struct _Rb_global
{
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *node);
};
}

class BfmeD975
{
public:
	char bfmeUse975D(void *p);
};

__forceinline char bfmeCheck1109B(BfmeD975 *checker, int value)
{
	return checker->bfmeUse975D((void *)value);
}

class BfmeW1109
{
public:
	int bfmeGo1109B(int a);

private:
	char m_bfmePad[0x144];
	BfmeNode1109B *m_bfmeTree;
};

int BfmeW1109::bfmeGo1109B(int a)
{
	BfmeNode1109B *head = m_bfmeTree;
	BfmeNode1109B *node = head->m_bfme08;
	int count = 0;

	while (node != head) {
		if (bfmeCheck1109B((BfmeD975 *)node->m_bfme10, a))
			++count;
		node = (BfmeNode1109B *)_STL::_Rb_global<bool>::_M_increment(
			(_STL::_Rb_tree_node_base *)node);
		head = m_bfmeTree;
	}

	return count;
}
