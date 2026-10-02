// Open-BFME5 conversions.

struct BfmeNode1109
{
	char m_bfmePad[8];
	BfmeNode1109 *m_bfme08;
	char m_bfmePad1[8];
	void *m_bfme14;
};

namespace _STL
{
	struct _Rb_tree_node_base;
	template <class Dummy> struct _Rb_global
	{
		static _Rb_tree_node_base *__cdecl _M_increment(_Rb_tree_node_base *node);
	};
}

class BfmeW1109
{
public:
	char bfmeGo1109A(void *k);
	char m_bfmePad[0x24];
	BfmeNode1109 *m_bfme24;
};

char BfmeW1109::bfmeGo1109A(void *k)
{
	BfmeNode1109 *h = m_bfme24;
	BfmeNode1109 *p = h->m_bfme08;

	while (p != h) {
		if (p->m_bfme14 == k)
			return 1;
		p = reinterpret_cast<BfmeNode1109 *>(
			_STL::_Rb_global<bool>::_M_increment(
				reinterpret_cast<_STL::_Rb_tree_node_base *>(p)));
		h = m_bfme24;
	}
	return (char *)this + 0x25c == k;
}
