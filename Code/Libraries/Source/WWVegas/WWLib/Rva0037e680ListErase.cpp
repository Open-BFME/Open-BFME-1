// cl: /DNDEBUG /MD /EHsc
// Retail 0x0037E680: STLport list::erase(first, last) over a 12-byte element
// with a virtual destructor. Pin names the Gen_t_00381e80_p12cd instantiation.

namespace _STL
{

struct _List_node_base
{
	_List_node_base *_M_next;
	_List_node_base *_M_prev;
};

struct Gen_t_00381e80_p12cd
{
	virtual ~Gen_t_00381e80_p12cd();
	int a[2];
};

struct _List_node : public _List_node_base
{
	Gen_t_00381e80_p12cd _M_data;
};

struct iterator
{
	iterator() {}
	iterator(_List_node_base *node) : _M_node(node) {}
	_List_node_base *_M_node;
};

class list
{
public:
	iterator erase(iterator first, iterator last);
};

iterator list::erase(iterator first, iterator last)
{
	_List_node_base *l = last._M_node;
	_List_node_base *f = first._M_node;
	while (f != l)
	{
		_List_node_base *node = f;
		f = f->_M_next;
		_List_node_base *n = node->_M_next;
		_List_node_base *p = node->_M_prev;
		p->_M_next = n;
		n->_M_prev = p;
		((_List_node *)node)->_M_data.~Gen_t_00381e80_p12cd();
		::operator delete(node);
	}
	return iterator(l);
}

}
