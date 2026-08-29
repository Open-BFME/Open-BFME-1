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
