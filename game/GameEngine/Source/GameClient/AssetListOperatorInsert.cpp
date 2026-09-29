// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

// Open-BFME5: AssetList prototype insertion, retail 0x00141D00, 77 bytes.
// The list owns a pointer set and marks itself changed only when the prototype
// resolved from the supplied asset name was not already present.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

extern const char Rva006A16B0Empty[];

#include "ascii_string.h"

struct Rva001408C0Target;

typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<Rva001408C0Key, _STL::less<Rva001408C0Key>,
	_STL::allocator<Rva001408C0Key> > Rva001408C0Set;

// The cast supplies the recovered ABI for the prototype lookup body at
// 0x009EC0B0. Its byte-true placeholder has since been converted, so name the
// identity that now holds the address rather than the retired dump symbol.
void *bfmeGoEMEb(void *);
typedef Rva001408C0Target *(__cdecl *FindPrototypeFn)(const char *name);

class AssetList
{
public:
	AssetList &operator <<(const AssetList &other);
	AssetList &operator <<(const AsciiString &name);

private:
	Rva001408C0Set m_prototypes;
	unsigned int m_treeLayoutPad;
	bool m_changed;
};

// ??6AssetList@@QAEAAV0@ABVAsciiString@@@Z
AssetList &AssetList::operator <<(const AsciiString &name)
{
	if (m_prototypes.insert(
		((FindPrototypeFn)bfmeGoEMEb)(name.str())).second)
	{
		m_changed = true;
	}
	return *this;
}

// ??6AssetList@@QAEAAV0@ABV0@@Z
AssetList &AssetList::operator <<(const AssetList &other)
{
	m_prototypes.insert(other.m_prototypes.begin(),
		other.m_prototypes.end());
	m_changed = true;
	return *this;
}
