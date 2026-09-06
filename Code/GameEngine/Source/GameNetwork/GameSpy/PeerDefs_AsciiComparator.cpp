// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME7: AsciiComparator::operator()(AsciiString, AsciiString) const,
// retail 0x00631350, 126 bytes -- the case-insensitive less-than of
// PeerDefs.h's PlayerInfoMap (called through the ILT thunk 0x0000B4B0 by the
// landed inserts at 0x00633E00/0x00634650).  PeerDefs.cpp's own copy is two
// bytes off because its AsciiString shim keeps the text at data+4; retail's
// string data is refcount, length, text (text at +8) and the destructor is
// the inline releaseBuffer() call.  stricmp goes through the CRT import.

#include <string.h>

extern const char g_bfmeEmptyAscii[];

struct AsciiStringData
{
	int m_refCount;
	int m_length;
	char m_text[ 1 ];
};

class AsciiString
{
public:
	AsciiString( const AsciiString &other );
	~AsciiString() { releaseBuffer(); }
	const char *str( void ) const { return m_data ? m_data->m_text : g_bfmeEmptyAscii; }
private:
	void releaseBuffer( void );
	AsciiStringData *m_data;
};

struct AsciiComparator
{
	bool operator()( AsciiString s1, AsciiString s2 ) const;
};

extern "C" __declspec(dllimport) int __cdecl _stricmp( const char *, const char * );

bool AsciiComparator::operator()( AsciiString s1, AsciiString s2 ) const
{
	return _stricmp( s1.str(), s2.str() ) < 0;
}
