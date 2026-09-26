// BFME retail 0x006CEE30: optional prototype lookup followed by insertion
// into the same pointer set used by AssetList.
// stlport

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#define _STLP_NO_EXCEPTIONS 1
#include <set>

struct Rva001408C0Target;

typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<Rva001408C0Key, _STL::less<Rva001408C0Key>,
	_STL::allocator<Rva001408C0Key> > Rva001408C0Set;

void *bfmeGoEMEb(void *name);
typedef Rva001408C0Key (__cdecl *FindPrototypeFn)(void *name);

class Rva006CEE30PointerSet
{
public:
	Rva006CEE30PointerSet &insert(void *name);

private:
	Rva001408C0Set m_values;
	unsigned int m_treeLayoutPad;
	volatile bool m_changed;
};

#pragma optimize("t", on)
Rva006CEE30PointerSet &Rva006CEE30PointerSet::insert(void *name)
{
	if (!name)
		return *this;
	if (m_values.insert(
		((FindPrototypeFn)bfmeGoEMEb)(name)).second)
		m_changed = true;
	return *this;
}
