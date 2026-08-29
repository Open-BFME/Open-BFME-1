// cl: /O2 /Ob2 /G6 /D_STLP_USE_STATIC_LIB
// stlport
// Address-derived asset-gather helper at retail RVA 0x0042C5A0.

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

void *bfmeGoEMEb( void *name );
typedef Rva001408C0Target *(__cdecl *FindPrototypeFn)( const char *name );

struct Rva001408C0AssetList
{
	Rva001408C0Set m_prototypes;
	unsigned int m_treeLayoutPad;
	bool m_changed;
};

class Rva0042C5A0Nugget
{
public:
	void bfmeGatherAssets( Rva001408C0AssetList *assets, void * ) const;

private:
	unsigned char m_prefix[0xB4];
	AsciiString m_name;
};

void Rva0042C5A0Nugget::bfmeGatherAssets(
	Rva001408C0AssetList *assets,
	void * ) const
{
	if ( assets->m_prototypes.insert(
		((FindPrototypeFn)bfmeGoEMEb)( m_name.str() )).second )
	{
		assets->m_changed = true;
	}
}
