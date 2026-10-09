// ??0Rva0040AC30Owner@@QAE@HH@Z
// partial score=0.9303 date=2026-10-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <map>

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
	void method(int a1, int a2);

private:
	int m_prefix;
	Bfme5MaterialPass *m_firstReferent;	// +0x04 (fresh, non-tree)
	Bfme5MaterialPass *m_secondReferent;	// +0x08 (tree get-or-create)
	int m_flag;				// +0x0C
};

// Open BFME 2: Code/GameEngine/Source/GameClient/Rva0040AD80ReferenceState_Rva00362c9f.cpp
Rva0040AC30Owner::Rva0040AC30Owner(int a1, int a2)
{
	Rva0040AC30Tree::iterator it = g_rva012F10DCTree.find(reinterpret_cast<const unsigned int &>(a1));
	if (it == g_rva012F10DCTree.end())
	{
		Bfme5MaterialPass *material = new Bfme5MaterialPass(a1, a2);
		m_secondReferent = material;
		g_rva012F10DCTree.insert_unique(Rva0040AC30Pair(static_cast<unsigned int>(a1), material));
		m_secondReferent->m_bfme40 = 1;
	}
	else
	{
		m_secondReferent = it->second;
		++*(int *)((char *)m_secondReferent + 4);
	}
	m_firstReferent = new Bfme5MaterialPass(a1, a2);
	m_firstReferent->m_bfme40 = 0;
	m_flag = 0;
}
