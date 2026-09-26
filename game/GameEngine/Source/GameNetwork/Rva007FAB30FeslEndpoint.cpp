// cl: /GS
// 0x007FAB30: builds a FESL endpoint string and forwards it through slot 1.

#include <string.h>

class Rva007FAB30Context
{
public:
	virtual void v0();
	virtual void dispatch( char *endpoint, void *a, void *b, void *c );

	void build( const char *first, const char *second, const char *third,
		void *a, void *b, void *c );
};

void Rva007FAB30Context::build( const char *first, const char *second,
	const char *third, void *a, void *b, void *c )
{
	char endpoint[ 0x44 ];
	endpoint[ 0 ] = 0;

	strcat( endpoint, first );
	if( second != 0 && second[ 0 ] != 0 )
	{
		strcat( endpoint, "." );
		strcat( endpoint, second );
	}
	strcat( endpoint, ".fesl" );
	if( third != 0 && third[ 0 ] != 0 )
	{
		strcat( endpoint, "." );
		strcat( endpoint, third );
	}
	strcat( endpoint, ".ea.com" );

	dispatch( endpoint, a, b, c );
}
