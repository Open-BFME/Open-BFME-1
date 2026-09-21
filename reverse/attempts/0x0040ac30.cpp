// ??0Rva0040AC30Owner@@QAE@HH@Z
// partial score=0.23 date=2026-09-21
// ?d_0040ac30@@YAXXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Address-derived constructor; the retail owner class is unknown.  It builds
// TWO 0x48-byte referent nodes: one (this+0x8) is a get-or-create lookup
// against the global tree at 0x012F10DC keyed by the first argument, sharing
// the refcounted node with the tree entry and incrementing its refcount at
// +0x4 on reuse; the other (this+0x4) is an always-fresh allocation, never
// tree-tracked.  See Rva0040AD80ReferenceState.cpp for the sibling
// releaseReferences()/dtor of the same referent layout and the same global
// tree, and Bfme5MatPassCtors.cpp for the shared 0x48-byte, two-int
// constructor shape retail reuses here (an ICF-shared ctor, not a real
// Bfme5MaterialPass semantically -- only the byte shape matches).  this+0xC
// is zeroed at the end.

#include <map>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/matpass.h
class MaterialPassClass
{
public:
	MaterialPassClass(void);
	virtual ~MaterialPassClass();

	char m_bfmePad[0x34];
};

extern int g_bfme5MatPassCount;

class Bfme5MaterialPass : public MaterialPassClass
{
public:
	Bfme5MaterialPass(int a, int b);
	virtual ~Bfme5MaterialPass();

	int m_bfme38;
	int m_bfme3c;
	int m_bfme40;
	int m_bfme44;
};

typedef _STL::pair<const unsigned int, Bfme5MaterialPass *> Rva0040AC30Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva0040AC30Pair,
	_STL::_Select1st<Rva0040AC30Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva0040AC30Pair> > Rva0040AC30Tree;

extern Rva0040AC30Tree g_rva012F10DCTree;	// @0x012F10DC, shared with Rva0040AD80ReferenceState.cpp

class Rva0040AC30Owner
{
public:
	Rva0040AC30Owner(int a1, int a2);

private:
	Bfme5MaterialPass *m_firstReferent;	// +0x04 (fresh, non-tree)
	Bfme5MaterialPass *m_secondReferent;	// +0x08 (tree get-or-create)
	int m_flag;				// +0x0C
};

// ?d_0040ac30@@YAXXZ
Rva0040AC30Owner::Rva0040AC30Owner(int a1, int a2)
{
	Rva0040AC30Tree::iterator it = g_rva012F10DCTree.find((unsigned int)a1);
	Bfme5MaterialPass *second;

	if (it != g_rva012F10DCTree.end())
	{
		second = it->second;
		++*(int *)((char *)second + 4);
	}
	else
	{
		second = (Bfme5MaterialPass *)::operator new(0x48);
		if (second)
			second = new(second) Bfme5MaterialPass(a1, a2);
		g_rva012F10DCTree.insert_unique(Rva0040AC30Pair((unsigned int)a1, second));
		second->m_bfme40 = 1;
	}
	m_secondReferent = second;

	Bfme5MaterialPass *first = (Bfme5MaterialPass *)::operator new(0x48);
	if (first)
		first = new(first) Bfme5MaterialPass(a1, a2);
	m_firstReferent = first;
	first->m_bfme40 = 0;

	m_flag = 0;
}
