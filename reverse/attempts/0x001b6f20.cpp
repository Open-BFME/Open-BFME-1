// ??1Rva001B6F20@@UAE@XZ
// partial score=0.35 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: the destructor at 0x001B6F20 (209 B).  Own vtable 0x0109DF10
// installed at entry; base ??1SubsystemInterface@@UAE@XZ (already matched,
// 0x009A1A40) called at the tail through ecx=this (no offset) -- confirms
// SubsystemInterface as the real base (see SubsystemLegend.cpp for the
// sibling "explicit container clear then implicit base dtor" shape).  The
// body manually walks a map<int, T*> red-black tree at +8 (real STL
// _Rb_tree, matched real-name element/erase helpers ?_M_increment@?$_Rb_
// global@_N@_STL@@... and _M_deallocate) deleting each non-null value
// through its own vtable slot 0 (virtual deleting destructor), then
// manually frees the data nodes via a hand-rolled recursive _M_erase-style
// walk and resets the header to the empty state; the tree's own real
// out-of-line destructor (ILT 0x00027115, target 0x001B6AD0, the matched
// _Rb_tree<int,pair<const int,Gen_t_p4pod>> destructor -- frees the header
// node only, since the data nodes are already gone) then runs.  This
// attempt models the tree as an opaque address-derived shell with an
// out-of-line destructor and reproduces the value-delete loop and node
// walk in C++ closely but not yet byte-exactly; banked as a partial.

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
};

class Rva001B6F20Elem
{
public:
	virtual ~Rva001B6F20Elem();
};

extern "C" void *_M_increment_Rb_global_bool( void *node );
extern "C" void _M_deallocate_node_alloc_18( void *node, unsigned int size );

struct Rva001B6F20Node
{
	void *m_color;
	void *m_parent;
	Rva001B6F20Node *m_left;
	Rva001B6F20Node *m_right;
	int m_key;
	Rva001B6F20Elem *m_value;
};

class Rva001B6F20Tree
{
public:
	~Rva001B6F20Tree();

private:
	char m_body[ 8 ];
};

class Rva001B6F20 : public SubsystemInterface
{
public:
	virtual ~Rva001B6F20();

private:
	Rva001B6F20Node **m_header;
	Rva001B6F20Tree m_tree;
};

// ??1Rva001B6F20@@UAE@XZ
Rva001B6F20::~Rva001B6F20()
{
	Rva001B6F20Node *header = *(Rva001B6F20Node **)&m_header;
	Rva001B6F20Node *node = header->m_left;

	while ( node != header )
	{
		if ( node->m_value )
			delete node->m_value;

		node = (Rva001B6F20Node *)_M_increment_Rb_global_bool( node );
	}
}
