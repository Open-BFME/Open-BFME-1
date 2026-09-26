// cl: /Od /GZ /GS /MD /DNDEBUG

int memcmp( const void *first, const void *second, unsigned int count );

struct Rva0080D890Entry
{
	int m_value;
	int m_length;
	unsigned char m_bytes[ 0x10 ];
};

extern struct Rva0080D890Entry g_Rva0112C8D0[];

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
