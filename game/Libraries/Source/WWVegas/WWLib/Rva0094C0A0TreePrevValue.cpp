// cl: /O2 /Ob0

// Retail ends the body at +0x0E: a one-byte INT3 follows before the later RET.
namespace _STL
{
struct _Rb_tree_node_base;
template <class Threading>
struct _Rb_global
{
	static _Rb_tree_node_base *__cdecl _M_decrement(_Rb_tree_node_base *);
};
}

class Rva0094C0A0TreePrevValue
{
	_STL::_Rb_tree_node_base *m_node;
public:
	void *value() const;
};

void *Rva0094C0A0TreePrevValue::value() const
{
	register _STL::_Rb_tree_node_base *node = m_node;
	return reinterpret_cast<unsigned char *>(_STL::_Rb_global<bool>::_M_decrement(node)) + 0x10;
}
