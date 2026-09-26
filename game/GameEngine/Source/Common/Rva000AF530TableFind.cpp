// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /Iinputs/reference/shims/asciistring_downloadmanager

// Retail RVA 0x000AF530.  The WaterTextureList parser at 0x000C2BC0 calls this
// on the global at 0x012ED648 and hands the result to INI::initFromINI, so the
// entries are the six named texture lists that block fills in.  The element is
// the class whose dump() the ledger already calls Rva000C2A30Owner: 20 bytes,
// an AsciiString name at +0 and the vector the "Texture" field appends to at
// +8.  Nothing names the table itself, so its name keeps the address.
//
// The comparison is StringBase<char>::compareNoCase spelled inline, the same
// way RvaTreeInsertUniqueNoCase.cpp spells it: both lengths as halfwords at +4
// of the header, _memicmp over the shorter of the two, the length difference as
// the tiebreak.  Retail reaches _memicmp through the import table.

#include "ascii_string.h"

extern "C" __declspec(dllimport) int __cdecl _memicmp( const void *buf1, const void *buf2, unsigned int count );

template <>
inline int StringBase<char>::compareNoCase( const StringBase<char> &str ) const
{
	int thatLen = str.m_data ? str.m_data->length : 0;
	const char *thatData = str.m_data ? &str.m_data->data[ 0 ] : (const char *)"";
	int thisLen = m_data ? m_data->length : 0;
	const char *thisData = m_data ? &m_data->data[ 0 ] : (const char *)"";
	int n = thisLen < thatLen ? thisLen : thatLen;
	int c = _memicmp( thisData, thatData, n );
	if ( c != 0 )
		return c;
	return thisLen - thatLen;
}

class Rva000C2A30Owner
{
public:
	AsciiString m_bfmeName;
	unsigned char m_bfmePad004[ 4 ];
	AsciiString *m_bfmeFirst;
	AsciiString *m_bfmeLast;
	AsciiString *m_bfmeEnd;
};

class Rva000AF530Table
{
public:
	Rva000C2A30Owner *find( const AsciiString &name );

	unsigned char m_bfmeHead[ 8 ];
	Rva000C2A30Owner m_bfmeEntries[ 6 ];
};

Rva000C2A30Owner *Rva000AF530Table::find( const AsciiString &name )
{
	for ( int i = 0; i < 6; ++i )
	{
		const StringBase<char> *entry = (const StringBase<char> *)&m_bfmeEntries[ i ].m_bfmeName;

		if ( entry->compareNoCase( *(const StringBase<char> *)&name ) == 0 )
			return &m_bfmeEntries[ i ];
	}

	return 0;
}
