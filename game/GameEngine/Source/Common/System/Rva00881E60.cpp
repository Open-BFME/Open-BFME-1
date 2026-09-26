// cl: /DNDEBUG /MD /EHs-c-

extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const unsigned short *);
extern "C" __declspec(dllimport) void * __cdecl malloc(unsigned int);
extern "C" __declspec(dllimport) unsigned short * __cdecl wcscpy(unsigned short *, const unsigned short *);

unsigned short * d_00881e60( const unsigned short *src )
{
	if ( src )
	{
		unsigned short *dst = (unsigned short *)malloc( wcslen(src) * 2 + 2 );
		if ( dst )
		{
			return wcscpy( dst, src );
		}
	}
	return 0;
}
