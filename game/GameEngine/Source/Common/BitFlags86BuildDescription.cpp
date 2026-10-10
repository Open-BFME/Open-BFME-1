// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME7: the 86-bit (object status) instantiation of the buildDescription
// twin at 0x001B9980 (BitFlags304BuildDescription.cpp): same template with the
// status name table at VA 0x012A6670 (BitFlags<86>::s_bitNameList) -- retail
// 0x00209130 165 B.

#include <bitset>
#include <string.h>

typedef int Int;
typedef bool Bool;


#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

template <size_t NUMBITS>
class BitFlags
{
public:
	void buildDescription( AsciiString *str, Int maxPerLine ) const;

private:
	static const char *s_bitNameList[];
	_STL::bitset<NUMBITS> m_bits;
};

template <size_t NUMBITS>
void BitFlags<NUMBITS>::buildDescription( AsciiString *str, Int maxPerLine ) const
{
	if ( str == 0 )
		return;

	str->StringBase<char>::clear();
	Bool first = true;
	Int count = 0;
	for ( Int i = 0; i < static_cast<Int>( NUMBITS ); ++i )
	{
		if ( !m_bits._Unchecked_test( i ) )
			continue;

		const char *bitName = s_bitNameList[i];
		if ( bitName == 0 )
			continue;

		if ( !first )
			str->StringBase<char>::concat( ", ", 2 );
		if ( count >= maxPerLine )
		{
			count = 0;
			str->StringBase<char>::concat( "\n", 1 );
		}
		first = false;
		str->StringBase<char>::concat( bitName, strlen( bitName ) );
		++count;
	}
}

// ?buildDescription@?$BitFlags@$0FG@@@QBEXPAVAsciiString@@H@Z
template void BitFlags<86>::buildDescription( AsciiString *, Int ) const;
