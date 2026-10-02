// cl: /O2 /Ob0

namespace _STL
{
class locale
{
public:
	class facet;
	class id;
	facet *_M_use_facet(const id &) const;
};
}

class Rva005380A0
{
};

char g_rva005380a0_id;

void *rva005380a0(Rva005380A0 *obj)
{
	const _STL::locale::id *facetId =
		reinterpret_cast<const _STL::locale::id *>(&g_rva005380a0_id);
	return reinterpret_cast<_STL::locale *>(obj)->_M_use_facet(*facetId);
}
