// cl: /DNDEBUG /MD /EHs-c-
// CRT heap/import-patch shims at 0x00881D70..0x00882ED0. The loader patch
// routine (0x008821D0) redirects msvcr71/kernel32 imports at these addresses,
// so each body is a tiny forwarder: allocate/free through the pluggable
// memory-manager slots, realloc/msize through the pool slots, or a
// late-bound LoadLibrary call followed by the loader patch. All names are
// address-derived: the patch table proves the slot each body reads, and the
// loader-patch source proves the replacement address each patch call stores,
// but no caller or string names the bodies themselves.

extern "C" void *( *__cdecl __gameMemAllocPtr )( unsigned int size, int flags );
extern "C" void ( *__cdecl __gameMemFreePtr )( void *ptr, int flags );
extern "C" void *Rva01357214Onexitbegin;
extern "C" void *( *__cdecl g_rva0130E9A0 )( void *ptr, unsigned int size, int flags );
extern "C" void *( __stdcall *g_rva0130E988LoadLibraryA )( const char *name );

extern void rva008821d0LoaderPatch( void );

typedef void *( __stdcall *RvaLoadLibraryExA00881FF0 )( const char *, void *, unsigned long );
typedef void *( __stdcall *RvaLoadLibraryExW00882020 )( const unsigned short *, void *, unsigned long );

// ?d_00881d20@@YAXPAX@Z
void d_00881d20( void *ptr )
{
	if ( ptr != 0 && ptr != Rva01357214Onexitbegin )
		__gameMemFreePtr( ptr, 0 );
}


// ?d_00881d70@@YAPAXI@Z
void *d_00881d70( unsigned int size )
{
	return __gameMemAllocPtr( size, 0 );
}

// ?d_00881d90@@YAPAXI@Z
void *d_00881d90( unsigned int size )
{
	return __gameMemAllocPtr( size, 0 );
}

// ?d_00881ed0@@YAXPAX@Z
void d_00881ed0( void *ptr )
{
	if ( ptr )
		__gameMemFreePtr( ptr, 1 );
}

// ?d_00881f10@@YAXPAX@Z
void d_00881f10( void *ptr )
{
	if ( ptr )
		__gameMemFreePtr( ptr, 2 );
}

// ?d_00881f50@@YAPAXI@Z
void *d_00881f50( unsigned int size )
{
	return __gameMemAllocPtr( size, 1 );
}

// ?d_00881f90@@YAPAXI@Z
void *d_00881f90( unsigned int size )
{
	return __gameMemAllocPtr( size, 2 );
}

// ?d_00881df0@@YAPAXPAXI@Z
void *d_00881df0( void *ptr, unsigned int size )
{
	return g_rva0130E9A0( ptr, size, 0 );
}

// ?d_00882eb0@@YAPAXPAXI@Z
void *d_00882eb0( void *ptr, unsigned int size )
{
	return g_rva0130E9A0( ptr, size, 3 );
}

// ?d_00882e90@@YAPAXI@Z
void *d_00882e90( unsigned int size )
{
	return __gameMemAllocPtr( size, 3 );
}

// ?d_00882ed0@@YAXPAX@Z
void d_00882ed0( void *ptr )
{
	__gameMemFreePtr( ptr, 3 );
}

// ?d_00881fb0@@YGPAXPBD@Z
void * __stdcall d_00881fb0( const char *name )
{
	void *mod = g_rva0130E988LoadLibraryA( name );
	void *saved = mod;
	rva008821d0LoaderPatch();
	return saved;
}

// ?d_00881fd0@@YGPAXPBG@Z
void * __stdcall d_00881fd0( const unsigned short *name )
{
	void *mod = ( (void *( __stdcall * )( const unsigned short * ))*(void **)0x0130E984 )( name );
	void *saved = mod;
	rva008821d0LoaderPatch();
	return saved;
}

// ?d_00881ff0@@YGPAXPBDPAXK@Z
void * __stdcall d_00881ff0( const char *a, void *b, unsigned long c )
{
	void *mod = ( (RvaLoadLibraryExA00881FF0)*(void **)0x0130E980 )( a, b, c );
	void *saved = mod;
	rva008821d0LoaderPatch();
	return saved;
}

// ?d_00882020@@YGPAXPBGPAXK@Z
void * __stdcall d_00882020( const unsigned short *a, void *b, unsigned long c )
{
	void *mod = ( (RvaLoadLibraryExW00882020)*(void **)0x0130E97C )( a, b, c );
	void *saved = mod;
	rva008821d0LoaderPatch();
	return saved;
}
