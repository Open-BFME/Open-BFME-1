// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// These three STLport bodies are kept under honest RVA-scoped owners.  Their
// destroy loop uses BfmeOwnVUG; the erase bodies use a separate 20-byte
// element and its proven copy/destructor routes. The old donor names conflated them.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef bool Bool;

class BfmeOwnVUG
{
public:
	unsigned char m_data[20];
	~BfmeOwnVUG();
};

class Rva001417F0ModuleInfo
{
public:
	struct Nugget
	{
		unsigned char m_data[20];
		~Nugget();
	};
};

// @?Rva0013C1D0Destroy@@YAXPAVBfmeOwnVUG@@0@Z 0x0013C1D0
void Rva0013C1D0Destroy(BfmeOwnVUG *first, BfmeOwnVUG *last)
{
	while (first != last)
	{
		first->~BfmeOwnVUG();
		++first;
	}
}

class Rva001401A0NuggetVector
{
public:
	typedef Rva001417F0ModuleInfo::Nugget Nugget;

	Nugget *erase(Nugget *position);

private:
	Nugget *m_start;
	Nugget *m_finish;
	Nugget *m_end_of_storage;
};

// @?erase@Rva001401A0NuggetVector@@QAEPAUNugget@Rva001417F0ModuleInfo@@PAU23@@Z 0x001401A0
Rva001401A0NuggetVector::Nugget *Rva001401A0NuggetVector::erase(Nugget *position)
{
	Nugget *finish = m_finish;
	Nugget *next = position + 1;
	if (next != finish)
	{
		_STL::random_access_iterator_tag category;
		_STL::__copy(next, finish, position, category, (int *)0);
	}
	--m_finish;
	m_finish->~Nugget();
	return position;
}

typedef _STL::vector<Rva001417F0ModuleInfo::Nugget> Rva00142350NuggetVector;

// The retail body is STLport's range erase instantiation.  The anchor keeps
// the vector method emitted while leaving its standard identity visible.
void Rva00142350EraseAnchor(Rva00142350NuggetVector &target,
	Rva001417F0ModuleInfo::Nugget *first,
	Rva001417F0ModuleInfo::Nugget *last)
{
	target.erase(first, last);
}
