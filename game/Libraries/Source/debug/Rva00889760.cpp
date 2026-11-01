// cl: /DNDEBUG /MD /EHs-c- /Oy-

extern "C" void d_0088d240( void *exptr, bool fullMemory );

int d_00889760( void *a, void *b, void *c )
{
	((int (__cdecl *)(void *, void *))d_0088d240)( b, c );
	return 1;
}
