// cl: /DNDEBUG /MD /EHs-c-

extern "C" __declspec(dllimport) void * __cdecl malloc(unsigned int);
extern "C" unsigned int __cdecl strlen(const char *);
extern "C" char * __cdecl strcpy(char *, const char *);

#pragma intrinsic(strlen, strcpy)

char * d_00881e10( const char *src )
{
	if ( src )
	{
		unsigned int len = strlen( src );
		char *dst = (char *)malloc( len + 1 );
		if ( dst )
		{
			strcpy( dst, src );
			return dst;
		}
	}
	return 0;
}
