// cl: /O2 /Ob1 /GF /Gy /MD /EHsc /GR /DNDEBUG /DWIN32 /D_WINDOWS

void j_00031a52();

void __fastcall rva0078C430DoubleDispatch( void *context, int value )
{
	(void)context;
	((void (__fastcall *)(void *, int))j_00031a52)(context, value * 2);
}
