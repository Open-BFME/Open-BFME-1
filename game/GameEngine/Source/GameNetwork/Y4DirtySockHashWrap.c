// cl: /Od /GZ /GS /MD /DNDEBUG
/* EA DirtySock -- one-shot MD5 and SHA-1 wrappers.  Retail names the locals
 * MD5 and Sha1 (from the /GZ frame descriptors at 0x0080D590 and 0x0080D620).
 * Init/update/finish live in Y4CommDigest.c and Y4CommSha1.c; this TU only
 * stacks a context, feeds it, and writes the digest. */

struct Rva00810060Context
{
	unsigned int m_count;
	unsigned int m_state[ 4 ];
	unsigned char m_block[ 0x40 ];
};

void Rva00810020( struct Rva00810060Context *context );
void Rva00810060( struct Rva00810060Context *context,
	const unsigned char *data, int length );
void Rva00810FF0( struct Rva00810060Context *context, char *out, int outSize );

void Rva0080D590( const unsigned char *data, int length, char *digest )
{
	struct Rva00810060Context MD5;

	Rva00810020( &MD5 );
	Rva00810060( &MD5, data, length );
	Rva00810FF0( &MD5, digest, 0x10 );
}

struct Rva008111D0Context
{
	unsigned int m_count;
	unsigned int m_fill;
	unsigned int m_state[ 5 ];
	unsigned char m_block[ 0x40 ];
};

void Rva00811180( struct Rva008111D0Context *context );
void Rva008111D0( struct Rva008111D0Context *context,
	const unsigned char *data, int length );
void Rva008116B0( struct Rva008111D0Context *context, unsigned char *out,
	unsigned int size );

void Rva0080D620( const unsigned char *data, int length, unsigned char *digest )
{
	struct Rva008111D0Context Sha1;

	Rva00811180( &Sha1 );
	Rva008111D0( &Sha1, data, length );
	Rva008116B0( &Sha1, digest, 0x14 );
}

void *memcpy( void *dest, const void *src, unsigned int count );

void Rva0080F3D0( unsigned char *state, const void *first, int firstLength,
	const void *second, int secondLength );
void Rva0080F530( void *dest, const void *src, int length );
void Rva0080F550( unsigned char *state );

struct Rva0080D6C0Owner
{
	char m_gap[ 0x18 ];
	void *m_first;
	int m_firstLength;
	char m_second[ 4 ];
};

void Rva0080D6C0( struct Rva0080D6C0Owner *object, const void *data,
	int length, void *dest, int destLength )
{
	unsigned char RSA[ 0x518 ];
	int iOffset;

	iOffset = ( length & ~1 ) - destLength;
	Rva0080F3D0( RSA, object->m_first, object->m_firstLength,
		object->m_second, 4 );
	Rva0080F530( RSA, data, length );
	Rva0080F550( RSA );
	memcpy( dest, RSA + iOffset, destLength );
}
