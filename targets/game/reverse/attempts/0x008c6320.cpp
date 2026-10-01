// ?rva008C6320@@YA_NPAVBfmeNode1220@@0PBVBfmeStrVKI@@PAPAV1@PAV2@@Z
// partial score=0.9108 date=2026-10-01
// ?rva008C6320\@\@PBVBfmeStrVKI\@\@@YA_NPAX0000@Z
// cl: /DNDEBUG /MD /EHsc

struct Rva008C6320StringData
{
	unsigned short references;
	unsigned short length;
	unsigned short capacity;
	unsigned short flags;
	char text[ 1 ];
};

extern Rva008C6320StringData g_bfmeDefaultString1284;
extern void (__cdecl **g_bfmeStringPool1284)( void * );

class BfmeStrVKI
{
public:
	BfmeStrVKI( const char *text ) { bfmeSetVKI( text ); }
	~BfmeStrVKI()
	{
		Rva008C6320StringData *block = data;
		if( --block->references == 0 )
			g_bfmeStringPool1284[ 1 ]( block );
	}
	void bfmeSetVKI( const char *text );
	const char *begin() const { return (const char *)data + 8; }
	Rva008C6320StringData * volatile data;
};

class BfmeNode1220;
bool ParsePath8C4DA0( BfmeNode1220 *inputScope, BfmeNode1220 *context,
	const BfmeStrVKI *path, BfmeNode1220 **out, char *name );

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

bool rva008C6320( BfmeNode1220 *context, BfmeNode1220 *scope,
	const BfmeStrVKI *path, BfmeNode1220 **targetOut,
	BfmeStrVKI *nameOut )
{
	_ReadWriteBarrier();
	BfmeNode1220 *scopePointer = scope;
	const BfmeStrVKI &input = *path;
	Rva008C6320StringData *inputBlock = input.data;
	const char *cursor = inputBlock->text;
	char name[ 256 ];
	char character = *cursor++;
	while( character != 0 )
	{
		if( character < '0' || character == ':' )
			goto parse;
		character = *cursor++;
	}
	if( scopePointer == 0 )
	{
		++inputBlock->references;
		Rva008C6320StringData *oldBlock = nameOut->data;
		if( --oldBlock->references == 0 )
			g_bfmeStringPool1284[ 1 ]( oldBlock );
		nameOut->data = input.data;
		*targetOut = context;
		return false;
	}

	parse:
	bool absolute = ParsePath8C4DA0( context, scopePointer, &input, targetOut, name );
	BfmeStrVKI parsedName( name );
	Rva008C6320StringData *newBlock = parsedName.data;
	++newBlock->references;
	Rva008C6320StringData *oldBlock = nameOut->data;
	if( --oldBlock->references == 0 )
		g_bfmeStringPool1284[ 1 ]( oldBlock );
	nameOut->data = newBlock;
	return absolute;
}
