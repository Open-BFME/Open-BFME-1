// cl: /DNDEBUG /MD /EHs-c-

namespace _STL
{
	struct _Rb_tree_node_base;
	template <class Dummy> struct _Rb_global
	{
		static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *node);
	};
}

struct Rva009EC200TreeIterator
{
	_STL::_Rb_tree_node_base *node;
};

int Rva009EC200(const Rva009EC200TreeIterator *first,
                const Rva009EC200TreeIterator *last)
{
	_STL::_Rb_tree_node_base *node = first->node;
	int count = 0;
	while (node != last->node)
	{
		node = _STL::_Rb_global<bool>::_M_increment(node);
		++count;
	}
	return count;
}

int Rva009EC2E0(const Rva009EC200TreeIterator *first,
                const Rva009EC200TreeIterator *last)
{
	_STL::_Rb_tree_node_base *node = first->node;
	int count = 0;
	while (node != last->node)
	{
		node = _STL::_Rb_global<bool>::_M_increment(node);
		++count;
	}
	return count;
}
