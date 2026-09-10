// ?d_007e8b00@@YAXXZ
// partial score=0.9 date=2026-09-10
// cl: /O2 /TC /GR- /EHs-c- /GS /MD
// Retail 0x007E8B00 is the optimized FESL record-field replacer.  Its named
// caller chain is BfmeThingVIY::bfmeSubVIY (0x007F1400) -> the record writer
// at 0x007E8EF0 -> 0x007E8D30 -> this helper.  The body is address-derived:
// the FESL table and separator are distinct from the later Y4 copy at
// 0x007EC780, so no existing DirtySock global is aliased here.

extern void * __cdecl memmove( void *dest, const void *src,
	unsigned int count );
extern int __cdecl memcmp( const void *left, const void *right,
	unsigned int count );
extern void * __cdecl memcpy( void *dest, const void *src,
	unsigned int count );

extern unsigned char Rva007E8B00ClassTable[];
extern char Rva007E8B00Separator;

int Rva007E8B00( unsigned char *buffer, int size,
	const char *field )
{
	int iDelta;
	unsigned char *p;
	unsigned char *pTail;
	register unsigned char *pValue;
	unsigned char cClassBuffer;
	unsigned char cClassField;
	unsigned int i;
	unsigned int iLength;
	unsigned char *pBuffer;

	pBuffer = buffer;

	if( pBuffer == 0 )
	{
		return -1;
	}

	if( field == 0 || ( unsigned int )*field <= ' ' )
	{
		return -1;
	}

	if( *field == '~' )
	{
		for( p = pBuffer; *p != 0; p++ )
		{
		}

		if( p != pBuffer && p[ -1 ] >= ' '
			&& p[ -1 ] != Rva007E8B00Separator
			&& p < pBuffer + size - 1 )
		{
			*p = Rva007E8B00Separator;
			p++;
			*p = 0;
		}

		pValue = p;
		pTail = pValue;
	}
	else
	{
		p = pBuffer;

		for( ;; )
		{
			if( *p == 0 )
			{
				if( p != pBuffer && p[ -1 ] >= ' '
					&& p[ -1 ] != Rva007E8B00Separator
					&& p < pBuffer + size - 1 )
				{
					*p = Rva007E8B00Separator;
					p++;
					*p = 0;
				}

				pValue = p;
				pTail = pValue;
				break;
			}

			if( *p <= ' ' )
			{
				p++;
				continue;
			}

			if( Rva007E8B00ClassTable[ *p ] == 1 )
			{
				pValue = p;
				pTail = pValue;
				break;
			}

			for( i = 0; ; i++ )
			{
				cClassBuffer = Rva007E8B00ClassTable[ p[ i ] ];
				cClassField = Rva007E8B00ClassTable[ ( unsigned char )field[ i ] ];

				if( cClassBuffer != cClassField || cClassBuffer < 2 )
				{
					break;
				}
			}

			if( cClassBuffer + cClassField == 2 )
			{
				pValue = p;
				pTail = pValue;

				for( ; *pTail >= ' '; pTail++ )
				{
				}

				if( *pTail > 0 )
				{
					pTail++;
				}

				break;
			}

			do
			{
				p++;
			}
			while( *p >= ' ' );
		}
	}

	for( iLength = 0; ( unsigned int )field[ iLength ] >= ' '; iLength++ )
	{
	}

	iLength++;

	iDelta = iLength - ( pTail - pValue );

	for( p = pTail; *p != 0; p++ )
	{
	}

	p++;

	if( iDelta > 0 && pBuffer + size - p < iDelta )
	{
		return -1;
	}

	if( iDelta == 0 && memcmp( pValue, field, iLength ) == 0 )
	{
		return 0;
	}

	if( iDelta > 0 )
	{
		memmove( pTail + iDelta, pTail, p - pTail );
	}

	if( iDelta < 0 )
	{
		memmove( pValue, pValue - iDelta, p - ( pValue - iDelta ) );
	}

	memcpy( pValue, field, iLength );

	if( pValue[ iLength ] == 0 && Rva007E8B00Separator != '\n' )
	{
		pValue[ iLength - 1 ] = 0;
	}
	else
	{
		pValue[ iLength - 1 ] = Rva007E8B00Separator;
	}

	return iLength - 1;
}
