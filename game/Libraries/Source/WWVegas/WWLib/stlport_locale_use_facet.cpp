// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::locale::_M_use_facet, retail 0x008321D0, 27 bytes. The body
// carried only a machine byte-dump row; targets/game/reverse/reloc_names.csv holds the name
// with identity=real.
//
// The id carries its index as its one member. The impl the locale holds keeps
// the facet table at +4 and its length at +8, past the vtable pointer the
// constructor at 0x00832120 and the destructor at 0x00832170 both go through.
// An index at or past the length gives a null; there is no check on the entry
// itself.
//
// The impl is read before the argument, and the bound test is unsigned.

namespace _STL
{

class _Locale_impl;

class locale
{
public:
	class facet;

	class id
	{
	public:
		unsigned int m_bfmeIndex;			// +0x00
	};

	facet *_M_use_facet(const id &facetId) const;

private:
	_Locale_impl *_M_impl;
};

class _Locale_impl
{
public:
	virtual void _bfme_slot0(void) = 0;

	locale::facet **m_bfmeFacets;				// +0x04
	unsigned int m_bfmeCount;				// +0x08
};

// ?_M_use_facet@locale@_STL@@QBEPAVfacet@12@ABVid@12@@Z
locale::facet *locale::_M_use_facet(const id &facetId) const
{
	_Locale_impl *impl = _M_impl;

	// The test is written the way round that keeps the lookup falling through
	// and puts the null out of line, which is how retail has it.
	if (facetId.m_bfmeIndex < impl->m_bfmeCount)
		return impl->m_bfmeFacets[facetId.m_bfmeIndex];

	return 0;
}

}
