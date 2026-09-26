// cl: /O2 /Ob0 /MD /EHs-c-

typedef bool Bool;

class BfmeA1087
{
};

extern BfmeA1087 *g_bfmeA1087;
extern void d_0002f6fd(void);

class Rva006BE410TerrainQueryForwarder
{
public:
	Bool query( float first, float second );
};

Bool Rva006BE410TerrainQueryForwarder::query( float first, float second )
{
	typedef Bool (BfmeA1087::*MemberThunk)( float, float );
	union
	{
		void (*function)(void);
		MemberThunk member;
	} thunk;
	thunk.function = d_0002f6fd;
	return (g_bfmeA1087->*thunk.member)( first, second );
}
