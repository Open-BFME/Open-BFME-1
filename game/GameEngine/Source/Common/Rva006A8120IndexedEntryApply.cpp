// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport
// Retail 006A8120, 164 bytes. Dispatcher 006A8210 passes this subobject at
// entry +0xB8, with (value, index); the body returns with ret 8.
// Native STLport push_back reuses the dead first-argument slot for its trait tag.
// The positive list guard preserves the observed load/store schedule.
// Element identity is opaque: 0069C300 copies two dwords without string lifetime
// work. See identity_evidence/006a8120-element-contracts.md for both callee ABIs.
#define _STLP_NO_EXCEPTIONS 1

#include <vector>

struct Rva0069C300Element
{
	Rva0069C300Element() {}
	Rva0069C300Element(const Rva0069C300Element &other);
	int m_field0;
	int m_field1;
};

namespace _STL
{
	template <> void __cdecl _Construct<Rva0069C300Element, Rva0069C300Element>(
		Rva0069C300Element *destination,
		const Rva0069C300Element &source);
}

typedef _STL::vector<Rva0069C300Element> Rva006A8120Vector;

struct Rva006A8120Record
{
	int m_field0;
	int m_field1;
};

class Rva00699430Owner
{
public:
	void productClamp(int index);
};

class Rva00699180Owner
{
public:
	void refreshPair(int list, int index);
};

class Rva006A8210Entry
{
public:
	void applyEntryList(int value, int index);

private:
	char m_body[0x4C];
	Rva006A8120Vector m_lists[6];
};

void Rva006A8210Entry::applyEntryList(int value, int index)
{
	const Rva006A8120Record *const *range =
		(const Rva006A8120Record *const *)(*(const int *)value + 0x8C);
	const Rva006A8120Record *it = range[0];
	const Rva006A8120Record *end = range[1];

	for (; it != end; ++it)
	{
		const int list = it->m_field0;

		if (list != -1)
		{
			Rva0069C300Element entry;
			entry.m_field0 = it->m_field1;
			entry.m_field1 = index;
			m_lists[list].push_back(entry);

			((Rva00699430Owner *)this)->productClamp(list);

			for (int i = 0; i < 2; ++i)
				((Rva00699180Owner *)this)->refreshPair(list, i);
		}
	}
}
