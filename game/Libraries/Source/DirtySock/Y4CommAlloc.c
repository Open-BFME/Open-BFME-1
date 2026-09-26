// cl: /Od /GZ /GS /MD /DNDEBUG
/* EA DirtySock -- allocation helpers for the comm layer, /Od with /GZ.  The
 * first of the 0x00800000..0x00820000 group to be converted; placement is by
 * address neighbourhood and by which allocator each body calls.
 */

/* The FESL allocator entry point at 0x007F0000.  It is OPTIMISED code -- no
 * frame pointer, a lazy global and a virtual call -- so it is pinned rather
 * than converted here; it takes a size cdecl and returns the block.  If no
 * allocator has been installed it prints "no FESL allocator defined" and then
 * dereferences the null anyway, so a missing allocator is a crash with a
 * message rather than a null return. */
void *Rva007F0000( unsigned int size );

void * __cdecl memset( void *dest, int c, unsigned int count );
void * __cdecl memcpy( void *dest, const void *source, unsigned int count );
unsigned int __cdecl strlen( const char *text );

/* 0x0080B000 ALLOCATES AND ZEROES A 0x124-BYTE OBJECT.  The size is a literal
 * in two places -- once for the allocation and once for the clear -- so the
 * two cannot disagree at run time but nothing ties them together either.
 *
 * THE ZEROING IS CONDITIONAL AND THE RETURN IS NOT.  A failed allocation
 * skips the clear and returns null, which is correct; but the allocator this
 * calls does not return null on failure, it crashes, so the guard is
 * unreachable in practice and only the shape of it survives.
 */
void *Rva0080B000( void )
{
	void *pObject;

	pObject = Rva007F0000( 0x124 );

	if ( pObject != 0 )
	{
		memset( pObject, 0, 0x124 );
	}

	return pObject;
}

void Rva0080ADE0( void *object, int releaseState );
void Rva007F0030( void *object );

void Rva0080B050( void *object )
{
	Rva0080ADE0( object, 0 );
}

void Rva0080B070( void *object )
{
	Rva0080ADE0( object, 0 );
	Rva007F0030( object );
}

struct Rva0080B000Comm
{
	void *m_socket;
	char m_gap04[ 0x104 ];
	char m_address[ 0x10 ];
	int m_addressLength;
	char m_gap11C[ 4 ];
	void *m_backend;
};

void *Rva007FD2D0( int family, int type, int protocol );
void Rva007FD3F0( void *socket );
int Rva007FD510( void *socket, const void *address, int addressLength );
int Rva007FD7A0( void *socket, int mode );
void *Rva007FD7D0( void *socket, void *address, int *addressLength );

int Rva0080B150( struct Rva0080B000Comm *comm, const void *address,
	int addressLength )
{
	if ( comm->m_socket != 0 )
	{
		Rva007FD3F0( comm->m_socket );
	}

	comm->m_socket = Rva007FD2D0( 2, 1, 0 );
	if ( comm->m_socket == 0 )
	{
		return -7;
	}

	return Rva007FD510( comm->m_socket, address, addressLength );
}

int Rva0080B460( struct Rva0080B000Comm *comm, int mode )
{
	return Rva007FD7A0( comm->m_socket, mode );
}

int Rva0080B480( struct Rva0080B000Comm *comm )
{
	Rva0080ADE0( comm, comm->m_backend != 0 );
	return 0;
}

struct Rva0080B000Comm *Rva0080B0A0( struct Rva0080B000Comm *comm,
	int unsupported, void *address, int *addressLength )
{
	struct Rva0080B000Comm *accepted;
	void *socket;

	if ( unsupported != 0 )
	{
		return 0;
	}

	socket = Rva007FD7D0( comm->m_socket, address, addressLength );
	if ( socket == 0 )
	{
		return 0;
	}

	accepted = (struct Rva0080B000Comm *)Rva0080B000();
	if ( accepted == 0 )
	{
		Rva007FD3F0( socket );
		return 0;
	}

	accepted->m_socket = socket;
	memcpy( accepted->m_address, address, *addressLength );
	accepted->m_addressLength = 0x14;
	return accepted;
}

struct Rva0080D980Backend
{
	int m_field00;
	int m_field04;
};

void Rva00810020( void *context );
void Rva00810060( void *context, const unsigned char *data, int length );
void Rva00810FF0( void *context, char *out, int outSize );
void Rva0080F300( void *state, unsigned char *data, int length );
int Rva007FD920( void *socket, const void *data, int length, int flags,
	const void *address, int addressLength );

int Rva0080C390( struct Rva0080B000Comm *comm, const void *data, int length )
{
	int payloadLength;
	int headerOffset;
	int writeOffset;
	int baseOffset;
	int padding;
	unsigned char context[ 0x54 ];
	unsigned char header[ 4 ];
	unsigned char *state;
	int remainder;

	state = (unsigned char *)comm->m_backend;
	if ( length < 1 || length > 0x3E80 )
		return -1;

	writeOffset = 4;
	headerOffset = writeOffset;
	if ( *(int *)( state + 0x812C ) > 0 )
		writeOffset += 0x10;
	baseOffset = writeOffset;

	memcpy( state + writeOffset + 8, data, length );
	writeOffset += length;

	if ( *(int *)( state + 0x81B0 ) > 0 )
	{
		remainder = ( *(int *)( state + 0x81B0 )
			- ( length % *(int *)( state + 0x81B0 ) ) )
			% *(int *)( state + 0x81B0 );
	}
	else
		remainder = 0;
	padding = remainder;

	memset( state + writeOffset + 8, 0, padding );
	writeOffset += padding;

	if ( *(int *)( state + 0x812C ) > 0 )
	{
		header[ 0 ] = (unsigned char)( ( *(unsigned int *)( state + 0x4008 ) >> 24 ) & 0xff );
		header[ 1 ] = (unsigned char)( ( *(unsigned int *)( state + 0x4008 ) >> 16 ) & 0xff );
		header[ 2 ] = (unsigned char)( ( *(unsigned int *)( state + 0x4008 ) >> 8 ) & 0xff );
		header[ 3 ] = (unsigned char)( *(unsigned int *)( state + 0x4008 ) & 0xff );

		Rva00810020( context );
		Rva00810060( context, state + 0x8130,
			*(int *)( state + 0x812C ) );
		Rva00810060( context, state + baseOffset + 8,
			writeOffset - baseOffset );
		Rva00810060( context, header, 4 );
		Rva00810FF0( context, (char *)( state + headerOffset + 8 ), 0x10 );
	}

	payloadLength = writeOffset - headerOffset;
	if ( *(int *)( state + 0x812C ) > 0 )
	{
		Rva0080F300( state + 0x87BE, state + headerOffset + 8,
			payloadLength );
	}
	if ( padding > 0 )
	{
		headerOffset--;
		state[ headerOffset + 8 ] = (unsigned char)( padding & 0xff );
	}
	headerOffset--;
	state[ headerOffset + 8 ] = (unsigned char)( payloadLength & 0xff );
	headerOffset--;
	state[ headerOffset + 8 ] =
		(unsigned char)( ( payloadLength >> 8 ) & 0xff );
	if ( padding == 0 )
	{
		state[ headerOffset + 8 ] |= 0x80;
	}

	*(int *)state = headerOffset;
	*(int *)( state + 4 ) = writeOffset;
	*(unsigned int *)( state + 0x4008 ) += 1;
	return 0;
}

int Rva0080D980( struct Rva0080B000Comm *comm, const char *data, int length )
{
	int result;
	struct Rva0080D980Backend *backend;

	result = -1;
	backend = (struct Rva0080D980Backend *)comm->m_backend;
	if ( length < 0 )
	{
		length = strlen( data );
	}
	if ( length > 16000 )
	{
		length = 16000;
	}

	if ( comm->m_addressLength == 0x10 )
	{
		result = 0;
		if ( backend->m_field04 == 0 )
		{
			result = Rva0080C390( comm, data, length );
			if ( result >= 0 )
			{
				result = length;
			}
		}
	}

	if ( comm->m_addressLength == 0x14 )
	{
		result = Rva007FD920( comm->m_socket, data, length, 0, 0, 0 );
	}
	return result;
}

struct Rva00812320Module;

struct Rva00812320Module *Rva00812320( int iEntries );
int Rva00812220( struct Rva00812320Module *module, const char *keyA,
	const char *keyB, int *pExtra, int iDefault );
int Rva00811E20( struct Rva00812320Module *module, const char *keyA,
	const char *keyB, char *out, int outSize, int bIncludePending );

/* Uninitialised data.  Whatever filter string this holds is written at run
 * time, so it is not recoverable from the image; it sits two bytes below the
 * module's reference count, which is why the group of globals reads as one
 * small block rather than three unrelated addresses. */
extern char g_Rva0130ACFAFilter[];

/* The caller's own object.  Only the two fields these wrappers touch are
 * named -- a default key at +0x04 and the module pointer at +0x64. */
struct Rva0080F100Object
{
	char m_gap0[ 4 ];
	char m_defaultKey[ 0x60 ];		/* +0x04 */
	struct Rva00812320Module *m_module;	/* +0x64 */
};

/* 0x0080F100 AND 0x0080F180 ARE THE SAME WRAPPER TWICE, differing only in
 * which of the two table functions they end in -- the value lookup or the
 * text listing.  Both CREATE THE MODULE ON FIRST USE, both substitute the
 * object's own key when the caller passes none, and both then re-test the
 * module pointer.
 *
 * THAT SECOND TEST IS NOT REDUNDANT-LOOKING BY ACCIDENT.  The constructor can
 * fail and return null, so the field may still be null after the first branch
 * assigned it -- the code reads as a doubled check and is really a
 * create-then-verify.  The failure result is 0, which the lookup also returns
 * for "no match", so a caller cannot tell a construction failure from an empty
 * table.
 *
 * SIXTEEN ENTRIES IS HARDCODED at both sites rather than passed in, so the
 * table size is decided by whichever of these two happens to run first and
 * neither caller can influence it.
 */
int Rva0080F100( struct Rva0080F100Object *object, const char *keyA,
	const char *keyB )
{
	int iResult;

	if ( object->m_module == 0 )
	{
		object->m_module = Rva00812320( 0x10 );
	}

	if ( keyA == 0 )
	{
		keyA = object->m_defaultKey;
	}

	if ( object->m_module == 0 )
	{
		iResult = 0;
	}
	else
	{
		iResult = Rva00812220( object->m_module, keyA, keyB, 0, 0 );
	}

	return iResult;
}

int Rva0080F180( struct Rva0080F100Object *object, const char *keyA,
	char *out, int outSize )
{
	int iResult;

	if ( object->m_module == 0 )
	{
		object->m_module = Rva00812320( 0x10 );
	}

	if ( keyA == 0 )
	{
		keyA = object->m_defaultKey;
	}

	if ( object->m_module == 0 )
	{
		iResult = 0;
	}
	else
	{
		iResult = Rva00811E20( object->m_module, keyA, g_Rva0130ACFAFilter,
			out, outSize, 0 );
	}

	return iResult;
}
