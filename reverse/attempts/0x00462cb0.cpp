// ?Rva00462CB0@@YAXPBD@Z
// partial score=0.9 date=2026-09-08
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc /Ireference/shims/stringinline
// stlport

// Retail 0x00462CB0 prepares the mode-check callback and walks the shared table.

#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>
#include <hash_map>

#include "StringInline.h"

extern void j_00041afb();

struct Rva0045F0A0Input
{
	AsciiString m_key;
	unsigned char m_padding00[0x0c];
	AsciiString m_name;
	void *m_unit;
};

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() {}
	BFMERetailAsciiString(const BFMERetailAsciiString &other)
		: m_data(other.m_data) {}
	void releaseBuffer();

private:
	void *m_data;
};

class Rva0045F0A0
{
public:
	char m_enabled;
	unsigned char m_padding01[3];
	char m_name[sizeof(AsciiString)];
};

namespace rts
{
	template <class T> struct hash;
	template <class T> struct equal_to;

	template <> struct hash<AsciiString>
	{
		unsigned int operator()(AsciiString value) const;
	};

	template <> struct equal_to<AsciiString>
	{
		int operator()(const AsciiString &left, const AsciiString &right) const;
	};
}

struct Rva0045F0A0ExtractKey
{
	const AsciiString &operator()(const Rva0045F0A0Input &value) const
	{
		return value.m_key;
	}
};

typedef _STL::hashtable<Rva0045F0A0Input, AsciiString, rts::hash<AsciiString>,
	Rva0045F0A0ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva0045F0A0Input> > Rva0045F0A0Table;

extern char g_bfmeTwoSJA[];
extern char g_bfmeDoneSJA;

extern template Rva0045F0A0 _STL::for_each<Rva0045F0A0Table::iterator,
	Rva0045F0A0>(Rva0045F0A0Table::iterator, Rva0045F0A0Table::iterator,
	Rva0045F0A0);

void Rva00462CB0(const char *name)
{
	if (name != 0 && *name != 0)
	{
	Rva0045F0A0 callback;
	callback.m_enabled = 1;
	reinterpret_cast<void (__stdcall *)(AsciiString *, const char *)>(j_00041afb)(
		reinterpret_cast<AsciiString *>(callback.m_name), name);

	Rva0045F0A0Table *table =
			reinterpret_cast<Rva0045F0A0Table *>(g_bfmeTwoSJA);
		_STL::for_each(table->begin(), table->end(), callback);
		reinterpret_cast<BFMERetailAsciiString *>(callback.m_name)->releaseBuffer();
	}

	g_bfmeDoneSJA = 0;
}
