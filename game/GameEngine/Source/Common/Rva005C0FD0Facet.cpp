// cl: /O2 /Ob0

class Rva005C0FD0
{};

namespace _STL
{
	class locale
	{
	public:
		class facet;
		class id
		{
		public:
			unsigned int m_index;
		};

		facet *_M_use_facet(const id &) const;
	};
}

_STL::locale::id g_rva005c0fd0_id;

void *rva005c0fd0(Rva005C0FD0 *obj)
{
	return reinterpret_cast<_STL::locale *>(obj)->_M_use_facet(g_rva005c0fd0_id);
}
