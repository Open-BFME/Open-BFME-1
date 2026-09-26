// _Rva0080ADE0
// cl: /Od /GZ /MD /DNDEBUG

/* Address-derived DirtySock comm-state release and reset helper. The matched
 * callers at 0x0080B050, 0x0080B070 and 0x0080B480 all pass the same object.
 * The object offsets and the backend stores below come from this body's
 * retail boundary, not from a guessed semantic class.
 *
 * The definition has to be `extern "C" int __cdecl`, because the pinned
 * caller symbol is `_Rva0080ADE0` and a plain C++ signature does not even
 * produce that name.
 *
 * `Rva0080AD00` takes its state pointer last, not first. Retail pushes the
 * pointer expression before the two zero literals, and a cdecl call pushes
 * right to left, so the pointer has to be the rightmost parameter.
 *
 * The callback slot is an ordinary cdecl function pointer, so the call needs
 * no inline assembly. Two earlier banks used an __asm block here and another
 * for the two state stores below, and each one moved the /Od temp-register
 * rotation a step and drifted the whole tail. Writing both in C matches every
 * byte.
 */

extern "C" void *Rva007F0000( unsigned int size );
extern "C" void Rva007FD3F0( void *socket );
extern "C" void Rva0080AD00( int a, int b, unsigned char *state );
extern "C" void * __cdecl memset( void *dest, int c, unsigned int count );
extern "C" void bfmeGo1019C( int value );
extern "C" void __RTC_CheckEsp( void );

struct Rva0080ADE0Object
{
	void *m_socket;
	void **m_callbackTable;
	char m_gap08[ 0x110 ];
	int m_state;
	int m_mode;
	void *m_backend;
};

typedef void ( __cdecl *Rva0080ADE0Shutdown )( void **callbackTable );

extern "C" int __cdecl Rva0080ADE0( struct Rva0080ADE0Object *object, int releaseState )
{
	int i;
	unsigned char *backend;
	int result;

	if ( object->m_socket != 0 )
	{
		Rva007FD3F0( object->m_socket );
		object->m_socket = 0;
	}

	if ( object->m_callbackTable != 0 )
	{
		( (Rva0080ADE0Shutdown)object->m_callbackTable[ 3 ] )(
			object->m_callbackTable );
		object->m_callbackTable = 0;
	}

	object->m_state = 0;
	object->m_mode = 1;

	if ( releaseState == 0 )
	{
		if ( object->m_backend != 0 )
		{
			bfmeGo1019C( ( int )object->m_backend );
			object->m_backend = 0;
		}
	}

	if ( releaseState != 0 )
	{
		if ( object->m_backend == 0 )
		{
			object->m_backend = Rva007F0000( 0x88C0 );
			if ( object->m_backend != 0 )
			{
				memset( object->m_backend, 0, 0x88C0 );
				Rva0080AD00( 0, 0, (unsigned char *)object->m_backend + 0x86BC );
			}
		}
	}

	backend = (unsigned char *)object->m_backend;
	if ( backend != 0 )
	{
		*(int *)( backend + 0x81B4 ) = 0x10;
		for ( i = 0; i < *(int *)( backend + 0x81B4 ); i++ )
		{
			backend[ 0x81B8 + i ] = (unsigned char )( i + 0x30 );
		}
		*(int *)( backend + 0x00 ) = 0;
		*(int *)( backend + 0x04 ) = 0;
		*(int *)( backend + 0x4008 ) = 0;
		*(int *)( backend + 0x400C ) = 0;
		*(int *)( backend + 0x4010 ) = 0;
		*(int *)( backend + 0x8018 ) = 0;
		*(int *)( backend + 0x801C ) = 0;
		*(int *)( backend + 0x8024 ) = 0;
		*(int *)( backend + 0x80A8 ) = 0;
		*(int *)( backend + 0x812C ) = 0;
	}

	if ( releaseState != 0 && backend == 0 )
		result = -8;
	else
		result = 0;

	return result;
}
