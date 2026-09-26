// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Observed 20-byte string/vector record: string +0, vector<AsciiString> +4,
// word +0x10. Original class identity is unknown. Its constructor 0x770D60,
// destructor 0x7701C0 and copy/erase callers prove this is a different family
// from the reference-bearing record in Rva0013B8F0Vector.cpp and the records
// behind the inherited ModuleInfo::Nugget pins. No shared semantic pins change.
// The actual owner at 0x77BC20 searches these records in its vector at +0x78.
#include "ascii_string.h"
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <string.h>

// Canonical inline definition from string_base.cpp, visible here for the
// retail lookup loop's guarded character-buffer access.
template <typename T>
inline const T *StringBase<T>::str() const
{
	return m_data ? &m_data->data[0] : (const T *)"";
}

struct Rva007701C0Element
{
	AsciiString m_string00;
	_STL::vector<AsciiString> m_strings04;
	int m_word10;

	Rva007701C0Element()
		: m_string00(""), m_word10(0) {}
	__declspec(noinline) Rva007701C0Element(const Rva007701C0Element &other);
	~Rva007701C0Element();
};

Rva007701C0Element::Rva007701C0Element(const Rva007701C0Element &other)
	: m_string00(other.m_string00), m_strings04(other.m_strings04),
	  m_word10(other.m_word10)
{
}

Rva007701C0Element::~Rva007701C0Element()
{
}

// These three retail copies are STLport destroy-range helpers over the same
// observed 20-byte record.  Their calls enter the element destructor through
// ILT 0x000454A3; the original class identity remains address-qualified.
void Rva00774A60Destroy(Rva007701C0Element *first,
	Rva007701C0Element *last)
{
	while (first != last)
	{
		first->~Rva007701C0Element();
		++first;
	}
}

void Rva007762D0Destroy(Rva007701C0Element *first,
	Rva007701C0Element *last)
{
	while (first != last)
	{
		first->~Rva007701C0Element();
		++first;
	}
}

void Rva00777FA0Destroy(Rva007701C0Element *first,
	Rva007701C0Element *last)
{
	while (first != last)
	{
		first->~Rva007701C0Element();
		++first;
	}
}

// Emit the actual STLport operations without synthetic forwarding wrappers.
template void _STL::_Construct<Rva007701C0Element, Rva007701C0Element>(
	Rva007701C0Element *, const Rva007701C0Element &);

template Rva007701C0Element *
_STL::vector<Rva007701C0Element>::erase(
	Rva007701C0Element *, Rva007701C0Element *);
template void _STL::vector<Rva007701C0Element>::clear();
template void _STL::vector<Rva007701C0Element>::push_back(
	const Rva007701C0Element &);
template Rva007701C0Element *
_STL::__uninitialized_copy<const Rva007701C0Element *, Rva007701C0Element *>(
	const Rva007701C0Element *, const Rva007701C0Element *,
	Rva007701C0Element *, const _STL::__false_type &);

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);

class Rva0077BC20Owner
{
public:
	Rva007701C0Element *findOrCreateRecord(const AsciiString &name);

private:
	unsigned char m_prefix[0x78];
	_STL::vector<Rva007701C0Element> m_info;
};

// ?findOrCreateRecord@Rva0077BC20Owner@@QAEPAURva007701C0Element@@ABVAsciiString@@@Z
Rva007701C0Element *Rva0077BC20Owner::findOrCreateRecord(const AsciiString &name)
{
	Rva007701C0Element *it = m_info.begin();
	int (__cdecl *compare)(const char *, const char *) = _strcmpi;
	if (it == m_info.end())
		goto create_record;
	for (; it != m_info.end(); ++it)
	{
		if (compare(it->m_string00.str(), name.str()) == 0)
			return it;
	}

	create_record:
	Rva007701C0Element *record = new Rva007701C0Element;
	record->m_string00 = name;
	m_info.push_back(*record);
	delete record;

	return &m_info[m_info.size() - 1];
}

// ?Rva0001F735CopyThunk@@YAPAURva007701C0Element@@PAU1@00ABUrandom_access_iterator_tag@_STL@@PAH@Z
Rva007701C0Element *Rva0001F735CopyThunk(
	Rva007701C0Element *first, Rva007701C0Element *last,
	Rva007701C0Element *result,
	const _STL::random_access_iterator_tag &tag, int *distance)
{
	return _STL::__copy(first, last, result, tag, distance);
}
