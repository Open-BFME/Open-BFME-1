// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

// The 0x009D76F0 owner is a STLport hash table whose key is the C string
// stored at node+4 and whose mapped value is the pointer at node+8.  The
// surrounding Gen009D76F0 insert (0x009D7AF0) names this resize entry and
// proves the node/table layout.  Keep the four-byte leading owner padding so
// the embedded STLport table starts at this+4, as it does in retail.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

struct Rva009D78B0Value
{
	const char *first;
	void *second;
};

struct Rva009D78B0ExtractKey
{
	const char *const &operator()( const Rva009D78B0Value &value ) const
	{
		return value.first;
	}
};

struct Rva009D78B0Hash
{
	unsigned int operator()( const char *text ) const
	{
		unsigned int value = 0;
		char ch = *text;
		if ( ch != 0 )
		{
			do
			{
				value = value * 5 + static_cast<signed char>( ch );
				ch = *++text;
			}
			while ( ch != 0 );
		}
		return value;
	}
};

typedef _STL::hashtable<Rva009D78B0Value, const char *, Rva009D78B0Hash,
	Rva009D78B0ExtractKey, _STL::equal_to<const char *>,
	_STL::allocator<Rva009D78B0Value> > Rva009D78B0Table;

// retail RVA 0x009D78B0; the existing named caller is
// Gen009D76F0::bfmeInsert at 0x009D7AF0.  The caller's embedded table has
// the same STLport hashtable layout (its three empty policy objects occupy
// the leading four bytes), so the emitted resize specialization receives
// the original owner pointer directly.
void BfmeHashResizeAnchor009D78B0( Rva009D78B0Table &table,
	unsigned int newCount )
{
	table.resize( newCount );
}
