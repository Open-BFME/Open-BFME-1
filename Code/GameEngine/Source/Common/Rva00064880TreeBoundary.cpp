// Address-derived identity for the anonymous retail body at RVA 0x00064880.
// The body is a two-pointer STLport tree boundary check; no real owning class
// name is claimed because the available callers are still anonymous dumps.
// cl: /DNDEBUG /MD /EHs-c-

namespace _STL
{

struct _Rb_tree_node_base
{
	unsigned char m_bfmeHeadYJ[0x28];
	volatile unsigned int m_bfme28YJ;
};

template <class T>
struct _Rb_global
{
	static _Rb_tree_node_base *_M_decrement(_Rb_tree_node_base *n);
};

}

class Rva00064880Tree
{
public:
	bool atEnd(unsigned int limit);

	_STL::_Rb_tree_node_base *m_bfme00YJ;
	_STL::_Rb_tree_node_base *m_bfme04YJ;
};

bool Rva00064880Tree::atEnd(unsigned int limit)
{
	if (m_bfme04YJ == 0)
		return true;

	unsigned int value = _STL::_Rb_global<bool>::_M_decrement(m_bfme00YJ)->m_bfme28YJ;
	return value < limit;
}
