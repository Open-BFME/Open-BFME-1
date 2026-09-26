// cl: /Od /RTC1
// Clean reconstruction of the 32-bit byte-order reversal at retail RVA 0x007FFAD0.

unsigned int Rva007FFAD0( unsigned int value )
{
	unsigned char result[ 4 ];

	result[ 3 ] = static_cast<unsigned char>( value );
	value >>= 8;
	result[ 2 ] = static_cast<unsigned char>( value );
	value >>= 8;
	result[ 1 ] = static_cast<unsigned char>( value );
	value >>= 8;
	result[ 0 ] = static_cast<unsigned char>( value );

	return *reinterpret_cast<unsigned int *>( result );
}
