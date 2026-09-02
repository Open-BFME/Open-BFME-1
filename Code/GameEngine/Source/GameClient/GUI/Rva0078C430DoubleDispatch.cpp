// cl: /O2 /Ob1 /GF /Gy /MD /EHsc /GR /DNDEBUG /DWIN32 /D_WINDOWS

void __fastcall rva0078C300Dispatch( void *, int value );

void __fastcall rva0078C430DoubleDispatch( void *context, int value )
{
	(void)context;
	rva0078C300Dispatch( context, value * 2 );
}
