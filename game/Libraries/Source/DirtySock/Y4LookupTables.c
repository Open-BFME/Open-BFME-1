// cl: /Od /GZ /GS /MD /DNDEBUG

int memcmp( const void *first, const void *second, unsigned int count );

struct Rva0080D890Entry
{
	int m_value;
	int m_length;
	unsigned char m_bytes[ 0x10 ];
};

/* Retail 0x0112C8D0: nine {value, length, bytes} rows and a zero terminator.
   The byte prefixes are DER object identifiers (2.5.4.6/7/8/10/11/3 and
   1.2.840.113549.1.1.1/4/5); the reader above walks to the zero value. */
struct Rva0080D890Entry g_Rva0112C8D0[ 10 ] =
{
	{ 1, 3, { 0x55, 0x04, 0x06 } },
	{ 3, 3, { 0x55, 0x04, 0x07 } },
	{ 2, 3, { 0x55, 0x04, 0x08 } },
	{ 4, 3, { 0x55, 0x04, 0x0a } },
	{ 5, 3, { 0x55, 0x04, 0x0b } },
	{ 6, 3, { 0x55, 0x04, 0x03 } },
	{ 7, 9, { 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x01 } },
	{ 8, 9, { 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x04 } },
	{ 9, 9, { 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x05 } },
	{ 0, 0, { 0 } }
};

int Rva0080D890( const void *bytes, int length )
{
	int result;
	int index;

	result = 0;
	index = 0;
	for ( ; g_Rva0112C8D0[ index ].m_value != 0; index++ )
	{
		if ( length >= g_Rva0112C8D0[ index ].m_length
			&& memcmp( bytes, g_Rva0112C8D0[ index ].m_bytes,
				g_Rva0112C8D0[ index ].m_length ) == 0 )
		{
			result = g_Rva0112C8D0[ index ].m_value;
			break;
		}
	}

	return result;
}
