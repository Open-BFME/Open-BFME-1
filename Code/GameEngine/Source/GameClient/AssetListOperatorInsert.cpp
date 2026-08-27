// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: AssetList prototype insertion, retail 0x00141D00, 77 bytes.
// The list owns a pointer set and marks itself changed only when the prototype
// resolved from the supplied asset name was not already present.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

class AsciiString
{
public:
	const char *str() const
	{
		return m_data ? m_data + 8 : (const char *)0x0107388B;
	}

private:
	const char *m_data;
};

struct Rva001408C0Target;

typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<Rva001408C0Key, _STL::less<Rva001408C0Key>,
	_STL::allocator<Rva001408C0Key> > Rva001408C0Set;

// The cast supplies the recovered ABI for the prototype lookup body whose
// byte-true placeholder already lives at 0x009EC0B0.
void d_009ec0b0();
typedef Rva001408C0Target *(__cdecl *FindPrototypeFn)(const char *name);

class AssetList
{
public:
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
		((FindPrototypeFn)d_009ec0b0)(name.str())).second)
	{
		m_changed = true;
	}
	return *this;
}
