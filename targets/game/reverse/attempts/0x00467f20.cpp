// ?d_00467f20@@YAXXZ
// partial score=0.682594 date=2026-09-25
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// Address-derived owner/member: caller 0x0046E850 reaches this body via an ILT
// thunk. Retail accepts an index below twelve and operates on the APT string
// stored at owner+0xA8+index*0x14.
#include "ascii_string.h"
#include <string.h>

template <> inline const char *StringBase<char>::str() const
{
	return m_data ? m_data->data : "";
}

typedef unsigned int UnsignedInt;
typedef int Int;

struct BfmeAptSlot467F20
{
	AsciiString m_value;
	unsigned char m_padding[0x0C];
	unsigned char m_flags;
	unsigned char m_tail[3];
};

class Rva00467F20Owner
{
public:
	bool aptSlotUpdate( UnsignedInt index );
};

extern void bfmeApplyESP( const char *first, const char *second );

bool Rva00467F20Owner::aptSlotUpdate( UnsignedInt index )
{
	if ( index >= 12 )
		return false;

	BfmeAptSlot467F20 *slots = reinterpret_cast<BfmeAptSlot467F20 *>(
		reinterpret_cast<unsigned char *>( this ) + 0xA8 );
	BfmeAptSlot467F20 *slot = &slots[index];

	if ( ( slot->m_flags & 1 ) == 0 || ( slot->m_flags & 2 ) != 0 )
		return false;

	AsciiString path( slot->m_value );
	const char *dot = path.find( '.' );
	if ( dot != 0 )
	{
		UnsignedInt charsFromDot = strlen(dot);
		while ( charsFromDot != 0 )
		{
			path.removeLastChar();
			--charsFromDot;
		}
	}

	AsciiString levelSuffix;
	levelSuffix.format( AsciiString( "/_level%d" ), index );
	bfmeApplyESP( path.str(), levelSuffix.str() );

	slot->m_flags = ( slot->m_flags & 0xFE ) | 2;
	return true;
}
