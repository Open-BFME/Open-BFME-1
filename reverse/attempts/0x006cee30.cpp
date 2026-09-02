// ?insert@Rva006CEE30PointerSet@@QAEAAV1@PAX@Z
// partial score=0.88 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: clean C++ conversion of the optional prototype-set insertion.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

struct Rva0013FA60Target;

typedef Rva0013FA60Target *Rva006CEE30Key;
typedef _STL::set<Rva006CEE30Key, _STL::less<Rva006CEE30Key>,
	_STL::allocator<Rva006CEE30Key> > Rva006CEE30Set;

void *bfmeGoEMEb(void *name);

class Rva006CEE30PointerSet
{
public:
	Rva006CEE30PointerSet &insert(void *name);

private:
	Rva006CEE30Set m_values;
	unsigned int m_treeLayoutPad;
	bool m_changed;
};

Rva006CEE30PointerSet &Rva006CEE30PointerSet::insert(void *name)
{
	if (name && m_values.insert(
		static_cast<Rva006CEE30Key>(bfmeGoEMEb(name))).second)
	{
		m_changed = true;
	}
	return *this;
}
