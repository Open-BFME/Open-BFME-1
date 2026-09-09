// _Rva0080ADE0
// partial score=0.57 date=2026-09-09
// cl: /Od /GZ /MD /DNDEBUG

/* Address-derived DirtySock comm-state release/reset helper.  The matched
 * callers at 0x0080B050, 0x0080B070 and 0x0080B480 all pass the same object;
 * the object offsets and backend stores below are taken from this body's
 * retail boundary, not from a guessed semantic class. */

void *Rva007F0000( unsigned int size );
void Rva007FD3F0( void *socket );
void Rva0080AD00( unsigned char *data, int length, void *state );
void * __cdecl memset( void *dest, int c, unsigned int count );
void bfmeGo1019C( int value );
void __RTC_CheckEsp( void );

struct Rva0080ADE0Object
{
	void *m_socket;
	void **m_callbackTable;
	char m_gap08[ 0x110 ];
	int m_state;
	int m_mode;
	void *m_backend;
};

/* VC7.1 reserves __thiscall in a free-function-pointer typedef.  A fastcall
 * cast with the table pointer duplicated gives the same ECX object and stack
 * argument; the extra EDX copy is harmless to the target's thiscall ABI. */
typedef void ( __fastcall *Rva0080ADE0Callback )( void *object,
	void **ignored, void **callbackTable );

int Rva0080ADE0( struct Rva0080ADE0Object *object, int releaseState )
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
		/* VC7.1 C cannot spell a free __thiscall pointer type.  This is the
		 * proven compiler-machinery shim for the one indirect callback call;
		 * the surrounding body remains ordinary C. */
		__asm
		{
			mov esi, esp
			mov edx, object
			mov eax, [ edx + 4 ]
			push eax
			mov ecx, object
			mov edx, [ ecx + 4 ]
			call dword ptr [ edx + 0Ch ]
			add esp, 4
			cmp esi, esp
			call __RTC_CheckEsp
		}
		__asm
		{
			mov eax, object
			mov dword ptr [ eax + 4 ], 0
		}
	}

	__asm
	{
		mov ecx, object
		mov dword ptr [ ecx + 118h ], 0
		mov edx, object
		mov dword ptr [ edx + 11Ch ], 1
	}

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
				Rva0080AD00( (unsigned char *)object->m_backend + 0x86BC, 0, 0 );
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
