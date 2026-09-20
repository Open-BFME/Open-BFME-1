// _Rva00812690
// partial score=0.64 date=2026-09-20
// cl: /Od /GZ /GS /MD /DNDEBUG
// _Rva00812690
// partial score=0.62 date=2026-09-09
struct Rva007FD4E0Socket;
struct Rva00812220Entry
{
	char m_gap0[ 0x08 ];
	char m_nameA[ 0x20 ];
	char m_nameB[ 0x20 ];
	char m_detail[ 0xC0 ];
	char m_templates[ 0x7C ];
	char m_substitution[ 0x10 ];
	int m_value;
	int m_extra;
	int m_pending;
	char m_gap1A0[ 4 ];
};
struct Rva00812320Module
{
	char m_gap0[ 0x28 ];
	struct Rva00812220Entry *m_first;
	struct Rva00812220Entry *m_end;
	int m_ready;
	char m_gap34[ 4 ];
	struct Rva007FD4E0Socket *m_socket;
	char m_peer[ 0x10 ];
	int m_active;
};
extern char g_Rva012C499CTag[];
int Rva007FEB00( void *lock );
int Rva008125C0( struct Rva00812320Module *context );
int Rva007FDA50( struct Rva007FD4E0Socket *socket, char *buffer, int length,
	int flags, void *from, int *fromLength );
int Rva007FE310( void *host, int hostLength, const void *inet, int inetLength );
unsigned int Rva007FEA00( void );
int Rva00811CE0( const char *a, const char *b );
char *Rva007FF860( const unsigned char *address, char *destination, int size );
int Rva007FD920( struct Rva007FD4E0Socket *socket, const char *buffer,
	int length, int flags, void *to, int toLength );
void Rva007FECB0( void *list );
void bfmeGo1019C( int value );
void * __cdecl memset( void *dest, int c, unsigned int count );
void * __cdecl memcpy( void *dest, const void *src, unsigned int count );
int __cdecl memcmp( const void *left, const void *right, unsigned int count );
char * __cdecl strcpy( char *dest, const char *src );

int __cdecl Rva00812690( struct Rva007FD4E0Socket *socket, int reason,
	void *data )
{
	int result;
	int status;
	int fromLength;
	unsigned char base[ 0x10 ];
	unsigned char from[ 0x10 ];
	struct Rva00812220Entry *entry;
	struct Rva00812220Entry *candidate;
	struct Rva00812220Entry **cursor;
	char packet[ 0x180 ];
	struct Rva00812320Module *object;
	unsigned int now;

	object = ( struct Rva00812320Module * )data;
	if ( Rva007FEB00( object ) == 0 )
	{
		return 0;
	}

	if ( object->m_socket != 0 )
	{
		for ( ; ; )
		{
			if ( object->m_ready > 0 )
			{
				object->m_ready = 0;
				Rva008125C0( object );
			}

			packet[ 8 ] = 0;
			fromLength = 0x10;
			result = Rva007FDA50( object->m_socket, packet, 0x180, 0,
				from, &fromLength );
			if ( result > 0 )
			{
				if ( packet[ 8 ] != 0 )
					goto receive_packet;
				goto receive_guard_fail;
			}
			goto receive_guard_fail;
	receive_packet:
				Rva007FE310( base, 0x10, from, 0x10 );
				status = 0;
				if ( *( unsigned short * )base == *( unsigned short * )from )
				{
					if ( *( unsigned short * )from == 2 )
					{
						status = memcmp( from + 2, base + 2, 6 ) == 0;
					}
				}

				if ( (unsigned char)packet[ 0 ] != g_Rva012C499CTag[ 0 ]
					|| (unsigned char)packet[ 1 ] != g_Rva012C499CTag[ 5 ]
					|| (unsigned char)packet[ 2 ] != g_Rva012C499CTag[ 10 ] )
				{
					continue;
				}

				if ( packet[ 8 ] == 0x3F && packet[ 9 ] == 0 )
				{
					now = Rva007FEA00() + 0x3E8;
					for ( entry = *( struct Rva00812220Entry ** )
						( ( char * )object + 0x24 ); entry != 0;
						entry = *( struct Rva00812220Entry ** )
						( ( char * )entry + 0x1A0 ) )
					{
						if ( *(int *)( ( char * )entry + 0x180 ) > now )
						{
							*(int *)( ( char * )entry + 0x180 ) = now;
						}
					}
					continue;
				}

				if ( packet[ 0x28 ] == 0 )
				{
					continue;
				}

				candidate = 0;
				for ( entry = object->m_first; entry != object->m_end;
					entry++ )
				{
					if ( candidate == 0 && entry->m_nameB[ 0 ] == 0 )
					{
						candidate = entry;
					}
					if ( Rva00811CE0( packet + 8, entry->m_nameA ) != 0 )
						continue;
					if ( Rva00811CE0( packet + 0x28, entry->m_nameB ) != 0 )
						continue;
					if ( Rva00811CE0( packet + 0x48, entry->m_detail ) != 0 )
						continue;
					if ( memcmp( packet + 4, ( char * )entry + 4, 4 ) != 0 )
						continue;
					break;
				}

				if ( entry == object->m_end && candidate != 0 )
				{
					entry = candidate;
					memset( entry, 0, 0x1A4 );
					memcpy( ( char * )entry + 4, packet + 4, 4 );
					strcpy( entry->m_nameA, packet + 8 );
					strcpy( entry->m_nameB, packet + 0x28 );
					strcpy( entry->m_detail, packet + 0x48 );
					object->m_active++;
				}

				if ( entry != object->m_end )
				{
					strcpy( packet + 8, entry->m_templates );
					now = Rva007FEA00();
					*(int *)( ( char * )entry + 0x180 ) =
						now + ( (unsigned char)packet[ 3 ] * 0x3E8 ) * 2 + 0x3E8;
					entry->m_pending = status;
					*(unsigned int *)( ( char * )entry + 0x194 ) =
						( ( ( ( (unsigned char)from[ 0 ] << 8 )
							| (unsigned char)from[ 1 ] ) << 8
							| (unsigned char)from[ 2 ] ) << 8
							| (unsigned char)from[ 3 ] );
					*(unsigned int *)( ( char * )entry + 0x198 ) =
						( ( ( ( (unsigned char)base[ 0 ] << 8 )
							| (unsigned char)base[ 1 ] ) << 8
							| (unsigned char)base[ 2 ] ) << 8
							| (unsigned char)base[ 3 ] );
					Rva007FF860( from, entry->m_substitution, 0x10 );
					object->m_active++;
				}
				continue;
	receive_guard_fail:
			goto expire;
		}

expire:
		now = Rva007FEA00();
		for ( entry = object->m_first; entry != object->m_end; entry++ )
		{
			if ( entry->m_nameB[ 0 ] != 0 && entry->m_templates[ 0 ] != 0
				&& *(int *)( ( char * )entry + 0x180 ) != 0
				&& *(int *)( ( char * )entry + 0x180 ) > now )
			{
				entry->m_nameB[ 0 ] = 0;
				entry->m_nameA[ 0 ] = 0;
				object->m_active++;
			}
		}

		cursor = ( struct Rva00812220Entry ** )
			( ( char * )object + 0x24 );
		while ( *cursor != 0 )
		{
			if ( *(int *)( ( char * )*cursor + 0x180 ) == 0 )
			{
				entry = *cursor;
				*cursor = *( struct Rva00812220Entry ** )
					( ( char * )entry + 0x1A0 );
				entry->m_templates[ 0 ] = 0;
				Rva007FD920( object->m_socket, ( const char * )entry,
					0x180, 0, object->m_peer, 0x10 );
				bfmeGo1019C( ( int )entry );
			}
			else
			{
				cursor = ( struct Rva00812220Entry ** )
					( ( char * )*cursor + 0x1A0 );
			}
		}

		now = Rva007FEA00();
		entry = *( struct Rva00812220Entry ** )
			( ( char * )object + 0x24 );
		while ( entry != 0 )
		{
			if ( *(int *)( ( char * )entry + 0x180 ) > now )
			{
				Rva007FD920( object->m_socket, ( const char * )entry,
					0x180, 0, object->m_peer, 0x10 );
				*(int *)( ( char * )entry + 0x180 ) =
					now + (unsigned char)*( ( char * )entry + 3 ) * 0x7D0;
			}
			entry = *( struct Rva00812220Entry ** )
				( ( char * )entry + 0x1A0 );
		}
	}

	Rva007FECB0( object );
	return 0;
}
