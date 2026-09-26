// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc /Iinputs/reference/shims/stringinline
// stlport

// Retail 0x00462710 is the STLport for_each instantiation called by the two
// mode-check setup routines at 0x00462CB0 and 0x00462D40. The table value keeps
// its hash key at offset zero, while process reads the record name at offset 0x10.

#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>
#include <hash_map>

#include "StringInline.h"

struct Rva0045F0A0Input
{
	AsciiString m_key;
	unsigned char m_padding00[0x0c];
	AsciiString m_name;
	void *m_unit;
};

class Rva0045F0A0
{
public:
	Rva0045F0A0(const Rva0045F0A0 &other)
		: m_enabled(other.m_enabled), m_name(other.m_name) {}
	~Rva0045F0A0() {}

	void process(Rva0045F0A0Input *input);
	void operator()(Rva0045F0A0Input &input)
	{
		process(&input);
	}

private:
	char m_enabled;
	unsigned char m_padding01[3];
	AsciiString m_name;
};

namespace rts
{
	template <class T> struct hash
	{
		unsigned int operator()(T value) const
		{
			const char *text = value.str();
			int result = 0;
			while (*text != 0)
			{
				result = result * 5 + *text;
				++text;
			}
			return result;
		}
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

template Rva0045F0A0 _STL::for_each<Rva0045F0A0Table::iterator,
	Rva0045F0A0>(Rva0045F0A0Table::iterator, Rva0045F0A0Table::iterator,
	Rva0045F0A0);
