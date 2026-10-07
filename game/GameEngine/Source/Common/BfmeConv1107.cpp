// Open-BFME5 conversions.

struct BfmeQ1107
{
	char m_bfmePad[0xc];
	int m_bfme0c;
};

struct BfmeNode1107
{
	char m_bfmePad[8];
	BfmeNode1107 *m_bfme08;
	char m_bfmePad1[0xc];
	BfmeQ1107 *m_bfme18;
};

// The step is STLport's red-black tree increment (call target 0x0082B870,
// ?_M_increment@?$_Rb_global@_N@_STL@@...): the node is a map node.
namespace _STL { struct _Rb_tree_node_base; template <class T> class _Rb_global; template <> class _Rb_global<bool> { public: static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *); }; }

class BfmeW1107
{
public:
	BfmeQ1107 *bfmeGo1107A(int k);
	char m_bfmePad[0xc];
	BfmeNode1107 *m_bfme0c;
};

BfmeQ1107 *BfmeW1107::bfmeGo1107A(int k)
{
	BfmeNode1107 *h = m_bfme0c;
	BfmeNode1107 *p = h->m_bfme08;

	while (p != h) {
		BfmeQ1107 *q = p->m_bfme18;

		if (q->m_bfme0c == k)
			return q;
		p = (BfmeNode1107 *)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base *)p);
		h = m_bfme0c;
	}
	return 0;
}
