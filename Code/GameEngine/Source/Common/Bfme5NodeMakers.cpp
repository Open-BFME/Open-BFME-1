// Open-BFME5 conversions: allocate-then-initialise bodies.

void * __cdecl operator new(unsigned int n);

namespace _STL {

class __new_alloc
{
public:
	static void *allocate(unsigned int n);
};

}

extern void *g_bfme5RefVtable;

struct Bfme5RefNode
{
	void *m_bfmeVptr;
	int m_bfmeRefCount;
	int m_bfmePad;
};

class Bfme5RefHolderA
{
public:
	Bfme5RefHolderA(int unused);

	Bfme5RefNode *m_bfmeNode;
};

Bfme5RefHolderA::Bfme5RefHolderA(int unused)
{
	Bfme5RefNode *q = (Bfme5RefNode *)operator new(12);
	Bfme5RefNode *p;

	if (q) {
		q->m_bfmeRefCount = 0;
		q->m_bfmeVptr = &g_bfme5RefVtable;
		p = q;
	} else {
		p = 0;
	}

	m_bfmeNode = p;

	if (p)
		++p->m_bfmeRefCount;
}

class Bfme5RefHolderB
{
public:
	Bfme5RefHolderB(int unused);

	Bfme5RefNode *m_bfmeNode;
};

Bfme5RefHolderB::Bfme5RefHolderB(int unused)
{
	Bfme5RefNode *q = (Bfme5RefNode *)operator new(12);
	Bfme5RefNode *p;

	if (q) {
		q->m_bfmeRefCount = 0;
		q->m_bfmeVptr = &g_bfme5RefVtable;
		p = q;
	} else {
		p = 0;
	}

	m_bfmeNode = p;

	if (p)
		++p->m_bfmeRefCount;
}

struct Bfme5RbNode
{
	char m_bfmeColour;
	char m_bfmePad[3];
	Bfme5RbNode *m_bfmeParent;
	Bfme5RbNode *m_bfmeLeft;
	Bfme5RbNode *m_bfmeRight;
	int m_bfmeValue;
};

Bfme5RbNode * __stdcall bfme5CloneRbNodeA(const Bfme5RbNode *src)
{
	Bfme5RbNode *n = (Bfme5RbNode *)_STL::__new_alloc::allocate(20);
	int *p = &n->m_bfmeValue;

	if (p)
		*p = src->m_bfmeValue;

	n->m_bfmeColour = src->m_bfmeColour;
	n->m_bfmeLeft = 0;
	n->m_bfmeRight = 0;
	return n;
}

Bfme5RbNode * __stdcall bfme5CloneRbNodeB(const Bfme5RbNode *src)
{
	Bfme5RbNode *n = (Bfme5RbNode *)_STL::__new_alloc::allocate(20);
	int *p = &n->m_bfmeValue;

	if (p)
		*p = src->m_bfmeValue;

	n->m_bfmeColour = src->m_bfmeColour;
	n->m_bfmeLeft = 0;
	n->m_bfmeRight = 0;
	return n;
}

namespace _STL {

struct _Rb_tree_node_base
{
	int m_bfmeColour;
	_Rb_tree_node_base *m_bfmeParent;
	_Rb_tree_node_base *m_bfmeLeft;
	_Rb_tree_node_base *m_bfmeRight;
	int m_bfmeValue;
};

template<class T> struct _Rb_global
{
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *n);
};

}

struct Bfme5Key
{
	int m_bfmeKey;
};

struct Bfme5TreeIterA
{
	_STL::_Rb_tree_node_base *m_bfmeNode;

	Bfme5TreeIterA(void) {}
};

Bfme5TreeIterA __cdecl bfme5SeekKeyA(Bfme5TreeIterA cur, Bfme5TreeIterA end, const Bfme5Key *k)
{
	while (cur.m_bfmeNode != end.m_bfmeNode && cur.m_bfmeNode->m_bfmeValue != k->m_bfmeKey)
		cur.m_bfmeNode = _STL::_Rb_global<bool>::_M_increment(cur.m_bfmeNode);

	return cur;
}

struct Bfme5TreeIterB
{
	_STL::_Rb_tree_node_base *m_bfmeNode;

	Bfme5TreeIterB(void) {}
};

Bfme5TreeIterB __cdecl bfme5SeekKeyB(Bfme5TreeIterB cur, Bfme5TreeIterB end, const Bfme5Key *k)
{
	while (cur.m_bfmeNode != end.m_bfmeNode && cur.m_bfmeNode->m_bfmeValue != k->m_bfmeKey)
		cur.m_bfmeNode = _STL::_Rb_global<bool>::_M_increment(cur.m_bfmeNode);

	return cur;
}
