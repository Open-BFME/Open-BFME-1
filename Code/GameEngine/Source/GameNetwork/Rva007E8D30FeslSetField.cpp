// cl: /GS
// 0x007E8D30: the FESL message TU's private copy of the escaped string-field
// writer (compare the DirtySock copy Rva007ECE60 at 0x007ECE60).  It is a
// file-static helper whose only caller, 0x007E8EF0, hands it the field name in
// ECX and the value in EAX: MSVC's private register convention for a static
// function, reproduced here by compiling it with that caller.

class Rva007EFFC0Allocator
{
public:
	virtual void v0();
	virtual void v1();
	virtual void *allocate( int size, int flags );
	virtual void release( void *block, int flags );
};

extern void *bfmeGo929C();

// 0x007EC030: deletes the named field from the record.
int Rva007EC030( char *text, const char *tag );

// 0x007E8B00: replaces or appends one field in the record; still a dump.
extern void d_007e8b00( void );
typedef int ( __cdecl *Rva007E8B00Replace )( char *record, int size, char *field );

extern char g_Rva011293A0HexFirst[];
extern char g_Rva011294A8HexSecond[];

// The record's "name=" prefix, as the DirtySock copy's Rva007EC730 writes it:
// a null name empties the record instead.
static char *Rva007E8D30Name( char *empty, char *dest, const char *src )
{
	if( src == 0 )
	{
		*empty = 0;
	}
	else
	{
		while( *src != 0 )
		{
			*dest = *src;
			dest++;
			src++;
		}

		*dest = '=';
		dest++;
	}

	return dest;
}

static int Rva007E8D30( const char *name, const char *value, char *record, int size )
{
	char *item;
	char *p;
	const unsigned char *pScan;
	const unsigned char *pSrc;
	unsigned int iLeft;
	int iResult;

	item = ( char * )( ( Rva007EFFC0Allocator * )bfmeGo929C() )->allocate( 0x32200, 2 );
	pSrc = ( const unsigned char * )value;

	if( pSrc == 0 )
	{
		Rva007EC030( record, name );
		return 0;
	}

	p = Rva007E8D30Name( record, item, name );

	// Retail starts the unsigned budget at 4 (add esi,4): sizeof the item
	// POINTER, so it wraps and never limits the 0x32200-byte block.
	iLeft = sizeof( item );
	iLeft -= p - item;

	for( pScan = pSrc; *pScan != 0 && *pScan != ' '; pScan++ )
	{
	}

	if( *pScan == ' ' )
	{
		*p = '"';
		p++;
		iLeft--;
	}

	for( ; *pSrc != 0 && iLeft > 0; pSrc++ )
	{
		if( *pSrc < ' ' || *pSrc == 0x7F || *pSrc == '=' || *pSrc == '"'
			|| *pSrc == ':' || *pSrc == '%' || *pSrc == '^' )
		{
			if( iLeft >= 3 )
			{
				*p = '%';
				p++;
				*p = g_Rva011293A0HexFirst[ *pSrc ];
				p++;
				*p = g_Rva011294A8HexSecond[ *pSrc ];
				p++;
			}

			iLeft -= 3;
		}
		else
		{
			*p = *pSrc;
			p++;
			iLeft--;
		}
	}

	if( iLeft <= 0 )
	{
		return -1;
	}

	if( *pScan == ' ' )
	{
		*p = '"';
		p++;
	}

	*p = 0;

	iResult = ( ( Rva007E8B00Replace )d_007e8b00 )( record, size, item );
	( ( Rva007EFFC0Allocator * )bfmeGo929C() )->release( item, 0 );
	return iResult;
}

// 0x007E8EF0, the helper's only caller: stores the escaped field into the
// message record at +0x10 (size +0x14) and records -100 at +0x24 on failure.
class Rva007E8810Message
{
public:
	void rva007E8EF0( const char *key, const char *value );

private:
	char m_pad[0x10];
	char *m_10;
	int m_14;
	char m_pad18[0x0c];
	int m_24;
};

void Rva007E8810Message::rva007E8EF0( const char *key, const char *value )
{
	if( Rva007E8D30( key, value, m_10, m_14 ) < 0 )
		m_24 = -100;
}
