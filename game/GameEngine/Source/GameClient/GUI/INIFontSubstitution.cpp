// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/asciistring_downloadmanager

// The INI block registry names this body. BFME keeps that registry as a linked
// list of 12-byte rows whose head is the global at VA 0x0130CE50, and the row
// at 0x012B5928 pairs the block name 'FontSubstitution' with this address.
//
// The body reads the tree at TheFontLibrary + 0x1C, which is keyed by
// AsciiString. It looks the block's name up, creates an empty 12-byte vector
// under that key when the name is new, fills the vector from a FieldParse table
// it builds on the stack with one field named "Size", and sorts the result.
//
// Three callees are already converted and are reached here through declarations
// the linker aliases onto their ledger names. The tree lookup is the STLport
// _M_find at 0x00475680, the insert is the STLport map operator[] at
// 0x00476F70, and the sort is the introsort driver at 0x00477960 over 16-byte
// elements. The element type stays address-derived because nothing in this body
// reads a field of it.
//
// The "Size" field parser is still an unconverted dump at 0x008776E0, so the
// FieldParse row carries the address of its ILT thunk rather than a name.
//
// Retail zeroes all four bytes of the comparator before parsing and writes its
// first byte afterwards, so the comparator is written here as a union of an int
// and a char. Nothing in this body reads the comparator, and the sort driver
// takes it by value.

#include "ascii_string.h"

class FontLibrary;
extern FontLibrary *TheFontLibrary;

struct FieldParse
{
	const char *m_token;
	void *m_parse;
	const void *m_userData;
	int m_offset;
};

struct Q3SortElem16 { int m_a, m_b, m_c, m_d; };
struct Q3SortCompare { union { int m_word; char m_flag; }; };

void Rva00477960( Q3SortElem16 *first, Q3SortElem16 *last, Q3SortCompare comp );

class Rva004779C0Vector
{
public:
	Rva004779C0Vector() : m_first( 0 ), m_last( 0 ), m_end( 0 ) {}

	Q3SortElem16 *m_first;
	Q3SortElem16 *m_last;
	Q3SortElem16 *m_end;
};

struct Rva00475680Node
{
	int m_color;
	Rva00475680Node *m_parent;
	Rva00475680Node *m_left;
	Rva00475680Node *m_right;
	AsciiString m_key;
	Rva004779C0Vector *m_value;
};

class Rva00475680Tree
{
public:
	Rva00475680Node *find( const AsciiString &key ) const;
	Rva004779C0Vector **at( const AsciiString &key );

	Rva00475680Node *m_header;
};

class INI
{
public:
	AsciiString getNextQuotedAsciiString( void );
	void initFromINI( void *what, const FieldParse *parseTable );
};

void __cdecl parseFontSubstitution( INI *ini )
{
	Q3SortCompare compare;
	compare.m_word = 0;

	AsciiString name = ini->getNextQuotedAsciiString();

	Rva00475680Tree *tree = (Rva00475680Tree *)( (char *)TheFontLibrary + 0x1C );

	Rva00475680Node *node = tree->find( name );
	if ( node == tree->m_header )
	{
		Rva004779C0Vector *created = new Rva004779C0Vector;
		*tree->at( name ) = created;
		node = tree->find( name );
	}

	Rva004779C0Vector *list = node->m_value;

	const FieldParse fieldParse[ 2 ] =
	{
		{ "Size", (void *)0x0041EB4B, 0, 0 },
		{ 0, 0, 0, 0 }
	};

	ini->initFromINI( list, fieldParse );

	Q3SortElem16 *last = list->m_last;
	Q3SortElem16 *first = list->m_first;
	compare.m_flag = 0;
	Rva00477960( first, last, compare );
}
