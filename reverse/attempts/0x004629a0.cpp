// ?_bfme_closeAptScreen@@YAXABVAsciiString@@@Z
// partial score=0.99 date=2026-09-08
// ?_bfme_closeAptScreen@@YAXABVAsciiString@@@Z
// This body matches retail except for the register used for the hidden result
// address before the call at 0x00462540.

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringinline
// stlport
#include <hash_map>
#include "StringInline.h"

struct BfmeAptScreenHashValue
{
	unsigned char m_padding[0x2c];
	AsciiString m_name;
};

struct BfmeAptScreenHashKey
{
	const AsciiString &operator()( const BfmeAptScreenHashValue &value ) const
	{
		return value.m_name;
	}
};

typedef _STL::hashtable<BfmeAptScreenHashValue, AsciiString,
	_STL::hash<AsciiString>, BfmeAptScreenHashKey,
	_STL::equal_to<AsciiString>, _STL::allocator<BfmeAptScreenHashValue> >
	BfmeAptScreenHashTable;

typedef BfmeAptScreenHashTable::iterator BfmeAptScreenHashIterator;

class BfmeAptScreenWindowManager
{
public:
	void findScreen( const AsciiString &name ) throw();
};

class BfmeAptScreenEraseResult : public AsciiString
{
};

BfmeAptScreenEraseResult eraseBfmeAptScreen(
	BfmeAptScreenHashIterator first, BfmeAptScreenHashIterator last,
	const AsciiString name ) throw();

BfmeAptScreenHashTable *const g_bfmeAptScreenHashTable =
	(BfmeAptScreenHashTable *)0x012F19A4;
BfmeAptScreenWindowManager *const g_bfmeAptScreenWindowManager =
	(BfmeAptScreenWindowManager *)0x012F1990;

__declspec( noinline ) void _bfme_closeAptScreen( const AsciiString &name )
{
	eraseBfmeAptScreen( g_bfmeAptScreenHashTable->begin(),
		BfmeAptScreenHashIterator( 0, g_bfmeAptScreenHashTable ),
		AsciiString( name ) );
	g_bfmeAptScreenWindowManager->findScreen( name );
}
