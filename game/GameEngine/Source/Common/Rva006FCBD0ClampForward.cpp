// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

typedef float Real;

void Rva00739900Forward( void *object, Real value );

void __stdcall Rva006FCBD0ClampForward( void *object, Real value )
{
	if( value <= 0.0f )
	{
		value = 0.0f;
	}

	if( object != 0 )
	{
		Rva00739900Forward( object, value );
	}
}
