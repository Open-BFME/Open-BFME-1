// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME7: the 86-bit (object status) instantiation of the buildDescription
// twin at 0x001B9980 (BitFlags304BuildDescription.cpp): same template with the
// status name table at VA 0x012A6670 (address-derived extern) -- retail
// 0x00209130 165 B.

#include <bitset>
#include <string.h>

typedef int Int;
typedef bool Bool;

extern const char *const Rva00209130StatusNames[];

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	void clear();
	void concat( const char *text, Int length );
};

template <size_t NUMBITS>
class BitFlags
{
public:
	void buildDescription( AsciiString *str, Int maxPerLine ) const;

private:
	_STL::bitset<NUMBITS> m_bits;
};

template <size_t NUMBITS>
void BitFlags<NUMBITS>::buildDescription( AsciiString *str, Int maxPerLine ) const
{
	if ( str == 0 )
		return;

	str->clear();
	Bool first = true;
	Int count = 0;
	for ( Int i = 0; i < static_cast<Int>( NUMBITS ); ++i )
	{
		if ( !m_bits._Unchecked_test( i ) )
			continue;

		const char *bitName = Rva00209130StatusNames[i];
		if ( bitName == 0 )
			continue;

		if ( !first )
			str->concat( ", ", 2 );
		if ( count >= maxPerLine )
		{
			count = 0;
			str->concat( "\n", 1 );
		}
		first = false;
		str->concat( bitName, strlen( bitName ) );
		++count;
	}
}

// ?buildDescription@?$BitFlags@$0FG@@@QBEXPAVAsciiString@@H@Z
template void BitFlags<86>::buildDescription( AsciiString *, Int ) const;
