// ?rva008C6320@@YA_NPAVBfmeNode1220@@0PBVBfmeStrVKI@@PAPAV1@PAV2@@Z
// cl: /DNDEBUG /MD /EHsc

struct Rva008C6320StringData
{
	unsigned short references;
	unsigned short length;
	unsigned short capacity;
	unsigned short flags;
	char text[ 1 ];
};

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
	Rva008C6320StringData *data;
};

class BfmeNode1220;
bool ParsePath8C4DA0( BfmeNode1220 *inputScope, BfmeNode1220 *context,
	const BfmeStrVKI *path, BfmeNode1220 **out, char *name );

bool rva008C6320( BfmeNode1220 *context, BfmeNode1220 *scope,
	const BfmeStrVKI *path, BfmeNode1220 **targetOut,
	BfmeStrVKI *nameOut )
{
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
	++parsedName.data->references;
	Rva008C6320StringData *oldBlock = nameOut->data;
	if( --oldBlock->references == 0 )
		g_bfmeStringPool1284[ 1 ]( oldBlock );
	nameOut->data = parsedName.data;
	return absolute;
}
