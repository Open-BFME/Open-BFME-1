// cl: /O2 /Ob0 /MD /EHs-c-

namespace _STL
{

struct _Rb_tree_node_base
{
};

template <class Dummy>
struct _Rb_global
{
	static _Rb_tree_node_base *_M_decrement( _Rb_tree_node_base *node );
};

}

class Rva004E2EF0ReverseIterator
{
public:
	void *getValue() const;

private:
	_STL::_Rb_tree_node_base *m_current;
};

void *Rva004E2EF0ReverseIterator::getValue() const
{
	_STL::_Rb_tree_node_base *node = m_current;
	node = _STL::_Rb_global<bool>::_M_decrement( node );
	return (char *)node + 0x10;
}
