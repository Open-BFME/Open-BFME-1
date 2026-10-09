// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Open-BFME7: retail 0x00144100 (53 bytes) is the twin of
// BfmeExperienceLevelSystem::addScalarTable (INIExperienceScalarTable.cpp): the same
// inline vector<T*>::push_back on a holder whose vector sits at +0x18 instead of +0x20.
// This opaque receiver view only needs vector. The native STLport policy
// matches the verified overflow sibling; the broad game typedef header
// selects a different allocator implementation.
#include <vector>

class Rva00144100Item;

class Rva00144100Holder
{
public:
	void addItem( Rva00144100Item *item );
	unsigned char m_unmodelled_00[ 0x18 ];
	std::vector<Rva00144100Item *> m_items;	// +0x18
};

void Rva00144100Holder::addItem( Rva00144100Item *item )
{
	m_items.push_back( item );
}
