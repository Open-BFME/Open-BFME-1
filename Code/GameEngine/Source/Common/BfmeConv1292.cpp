// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringinline
// stlport
// Open-BFME5 conversions.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "StringInline.h"

class Rva00460A70Mapped
{
public:
	virtual void release( int deleting ) = 0;

	void *m_owner;
};

namespace rts
{
	template <class T> struct hash;
	template <class T> struct equal_to;

	template <> struct hash<AsciiString>
	{
		unsigned int operator()( AsciiString value ) const;
	};

	template <> struct equal_to<AsciiString>
	{
		int operator()( const AsciiString &left, const AsciiString &right ) const;
	};
}

typedef _STL::hash_map<AsciiString, Rva00460A70Mapped *, rts::hash<AsciiString>,
	_STL::equal_to<AsciiString> > BfmeSJAHash;

extern char g_bfmeOneSJA[];
extern char g_bfmeTwoSJA[];
extern char g_bfmeDoneSJA;

void bfmeReadSJA(void *slot, void *p, char *out)
{
	BfmeSJAHash *table = (BfmeSJAHash *)slot;
	BfmeSJAHash::iterator eraseIt;
	BfmeSJAHash::iterator it = table->begin();
	while (it != table->end())
	{
		if (it->second->m_owner == p)
		{
			eraseIt = it++;
			BfmeSJAHash::value_type *entry = &*eraseIt;
			Rva00460A70Mapped *mapped = entry->second;
			if (mapped)
				mapped->release( 1 );
			table->erase( eraseIt );
		}
		else
		{
			++it;
		}
	}
}

// The second table's mapped value is the 44-byte record the matched erase at
// 0x004609B0 instantiates; its owner is the word at +4.
struct Rva004609B0Mapped
{
	char m_body[44];
};

typedef _STL::hash_map<AsciiString, Rva004609B0Mapped, rts::hash<AsciiString>,
	_STL::equal_to<AsciiString> > BfmeSJAValueHash;

void bfmeLoadSJA(void *slot, void *p, char *out)
{
	BfmeSJAValueHash *table = (BfmeSJAValueHash *)slot;
	BfmeSJAValueHash::iterator eraseIt;
	BfmeSJAValueHash::iterator it = table->begin();
	while (it != table->end())
	{
		if (*(void **)(it->second.m_body + 4) == p)
		{
			eraseIt = it++;
			table->erase( eraseIt );
		}
		else
		{
			++it;
		}
	}
}

void bfmeGoSJA(void *p)
{
	char v;
	bfmeReadSJA(g_bfmeOneSJA, p, &v);
	bfmeLoadSJA(g_bfmeTwoSJA, p, &v);
	g_bfmeDoneSJA = 0;
}
