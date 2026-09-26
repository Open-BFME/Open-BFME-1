// EA FESL blob-service content fetch at retail RVA 0x007F04B0.

class Rva007EFFC0Allocator
{
public:
	virtual void v0();
	virtual void v1();
	virtual void *allocate( int size, int flags );
	virtual void release( void *block, int flags );
};

extern void *bfmeGo929C();

class BfmeThingUPB
{
public:
	char bfmeGoUPB( void *a, char *b, void *c );
};

class Rva007EB810Diag
{
public:
	virtual void v0();
	virtual void v1();
	virtual void __cdecl assertValue( void *value, const char *message );
	virtual void fail( const char *expr, const char *file, int line );
};

extern int Rva007EB810Get();

// Retail calls the decoder with the encoded blob first and writes decoded bytes
// into this method's destination buffer.  Its return value is intentionally
// ignored by this caller, as in the retail body.
extern int rva007FF250Decode(
	int encodedLength, const char *encodedInput, unsigned char *decodedOutput );

class Rva007F04B0BlobService
{
public:
	bool fetchContent( char *destination, unsigned int length );

	BfmeThingUPB *m_reader;
};

bool Rva007F04B0BlobService::fetchContent( char *destination, unsigned int length )
{
	Rva007F04B0BlobService *self = this;
	Rva007EFFC0Allocator *allocator = (Rva007EFFC0Allocator *)bfmeGo929C();
	unsigned int adjustedLength = length + 2;
	unsigned int size = ( adjustedLength / 3 ) * 4 + 1;
	void *content = allocator->allocate( size, 2 );
	if( content == 0 )
	{
		Rva007EB810Diag *diag = (Rva007EB810Diag *)Rva007EB810Get();
		diag->assertValue( content, "--- out of memory\n" );
		((Rva007EB810Diag *)Rva007EB810Get())->fail(
			"false",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\blobservice.cpp",
			0x1F9 );
		return false;
	}
	if( !self->m_reader->bfmeGoUPB( (void *)"content", (char *)content, (void *)size ) )
	{
		((Rva007EFFC0Allocator *)bfmeGo929C())->release( content, 0 );
		return false;
	}
	rva007FF250Decode( ( (int)length + 2 ) / 3 * 4, (const char *)content,
		(unsigned char *)destination );
	((Rva007EFFC0Allocator *)bfmeGo929C())->release( content, 0 );
	return true;
}
