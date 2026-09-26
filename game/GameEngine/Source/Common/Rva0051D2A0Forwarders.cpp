// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

extern "C" void Rva0051D1E0Forward( int mode, void *first, void *second );

extern "C" void Rva0051D2A0ForwardEnabled( void *first, void *second )
{
	Rva0051D1E0Forward( 1, first, second );
}

extern "C" void Rva0051D2C0ForwardDisabled( void *first, void *second )
{
	Rva0051D1E0Forward( 0, first, second );
}
