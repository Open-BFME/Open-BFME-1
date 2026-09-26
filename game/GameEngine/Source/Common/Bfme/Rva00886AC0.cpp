// cl: /DNDEBUG /MD /EHs-c-

char * d_00886ac0( const char *start, const char *end, char *dst, int ( *func )( int ) )
{
	for ( ; start != end; ++start, ++dst )
	{
		*dst = (char)func( *start );
	}
	return dst;
}
