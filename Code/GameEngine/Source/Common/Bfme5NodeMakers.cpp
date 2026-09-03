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

class MultiIniFieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINIMultiProc(void *p, void (__cdecl *proc)(MultiIniFieldParse &));
};

// Three DISTINCT vtables, one per factory. They shared a single name until
// the DIR32 check caught it resolving to three addresses -- one name
// asserting three globals are one object, which failed the gate tree-wide.
// Named after their own RVAs, following this file's Rva<hex> convention for
// something whose identity is not yet known: the name claims an address and
// nothing more. (g_bfme5RefVtable below is genuinely shared -- one base,
// two references -- and is deliberately left as one name.)
extern void *g_bfmeRva0108B1B8ParseVtable;
extern void *g_bfmeRva0108D638ParseVtable;
extern void *g_bfmeRva0108D748ParseVtable;
void __cdecl bfme5ParseProcA(MultiIniFieldParse &m);
void __cdecl bfme5ParseProcB(MultiIniFieldParse &m);

struct Bfme5ParseNode
{
	void *m_bfmeVptr;
	int m_bfme04;
};

void * __cdecl bfme5MakeParseNodeA(INI *ini)
{
	Bfme5ParseNode *q = (Bfme5ParseNode *)operator new(8);
	Bfme5ParseNode *p;

	if (q) {
		q->m_bfmeVptr = &g_bfmeRva0108B1B8ParseVtable;
		p = q;
	} else {
		p = 0;
	}

	if (ini)
		ini->initFromINIMultiProc(p, bfme5ParseProcA);

	return p;
}

void * __cdecl bfme5MakeParseNodeB(INI *ini)
{
	Bfme5ParseNode *q = (Bfme5ParseNode *)operator new(8);
	Bfme5ParseNode *p;

	if (q) {
		q->m_bfmeVptr = &g_bfmeRva0108D638ParseVtable;
		p = q;
	} else {
		p = 0;
	}

	if (ini)
		ini->initFromINIMultiProc(p, bfme5ParseProcB);

	return p;
}

struct Coord3D;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Bridge
{
public:
	bool isPointOnBridge(const Coord3D *p);

	char m_bfmePad[4];
	Bridge *m_bfmeNext;
};

class Bfme5BridgeList
{
public:
	char bfmeAnyBridgeAt(const Coord3D *p);

	char m_bfmePad[0x858];
	Bridge *m_bfmeBridges;
};

char Bfme5BridgeList::bfmeAnyBridgeAt(const Coord3D *p)
{
	for (Bridge *b = m_bfmeBridges; b != 0; b = b->m_bfmeNext)
		if (b->isPointOnBridge(p))
			return 1;

	return 0;
}

struct Bfme5ParseNode12
{
	void *m_bfmeVptr;
	int m_bfme04;
	int m_bfme08;
};

void __cdecl bfme5ParseProcC(MultiIniFieldParse &m);

void * __cdecl bfme5MakeParseNodeC(INI *ini)
{
	Bfme5ParseNode12 *q = (Bfme5ParseNode12 *)operator new(12);
	Bfme5ParseNode12 *p;

	if (q) {
		q->m_bfmeVptr = &g_bfmeRva0108D748ParseVtable;
		q->m_bfme08 = 1;
		p = q;
	} else {
		p = 0;
	}

	if (ini)
		ini->initFromINIMultiProc(p, bfme5ParseProcC);

	return p;
}
