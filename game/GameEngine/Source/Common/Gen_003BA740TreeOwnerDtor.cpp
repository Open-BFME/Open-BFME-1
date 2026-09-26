// stlport

// Open-BFME: tree owner destructor, retail 0x003BA740, 156 bytes.
// The body deletes each mapped object before it clears its STLport tree.

#include <map>

class Gen_003BA740Object
{
public:
	virtual ~Gen_003BA740Object();
};

struct Gen_t_003b9fa0_p4pod
{
	Gen_003BA740Object *m_value;
};

typedef _STL::pair<const int, Gen_t_003b9fa0_p4pod> Gen_003BA740Pair;
typedef _STL::_Rb_tree<int, Gen_003BA740Pair,
	_STL::_Select1st<Gen_003BA740Pair>, _STL::less<int>,
	_STL::allocator<Gen_003BA740Pair> > Gen_003BA740Tree;

struct Gen_003BA740NodeBase
{
	int m_color;
	Gen_003BA740NodeBase *m_parent;
	Gen_003BA740NodeBase *m_left;
	Gen_003BA740NodeBase *m_right;
};

struct Gen_003BA740TreeLayout
{
	Gen_003BA740NodeBase *m_header;
	unsigned int m_nodeCount;
	int m_compare;
};

class Gen_003BA740 : public Gen_003BA740Tree
{
public:
	~Gen_003BA740();
};

Gen_003BA740::~Gen_003BA740()
{
	register Gen_003BA740 *self = this;
	Gen_003BA740TreeLayout *tree = (Gen_003BA740TreeLayout *)self;
	_STL::_Rb_tree_node<Gen_003BA740Pair> *node =
		(_STL::_Rb_tree_node<Gen_003BA740Pair> *)tree->m_header->
			m_left;
	while ((Gen_003BA740NodeBase *)node != tree->m_header)
	{
		Gen_003BA740Object *value = node->_M_value_field.second.m_value;
		if (value)
			delete value;
		node = (_STL::_Rb_tree_node<Gen_003BA740Pair> *)
			_STL::_Rb_global<bool>::_M_increment(node);
	}
	if (tree->m_nodeCount)
		self->clear();
}
